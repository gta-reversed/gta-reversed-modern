#include "StdInc.h"

#include "InteriorManager_c.h"
#include "FurnitureManager_c.h"

#include <TaskTypes/TaskSimpleCarDrive.h>

void InteriorManager_c::InjectHooks() {
    RH_ScopedClass(InteriorManager_c);
    RH_ScopedCategory("Interior");

    RH_ScopedGlobalInstall(AddSameGroupEffectInfos, 0x598430, { .reversed = false });
    RH_ScopedGlobalInstall(AreAnimsLoaded, 0x5980F0);
    RH_ScopedInstall(PruneVisibleEffects, 0x598A60, { .reversed = false });
    RH_ScopedInstall(Exit, 0x598010);
    RH_ScopedInstall(GetVisibleEffects, 0x598D80, { .reversed = false });
    RH_ScopedInstall(IsInteriorEffectVisible, 0x598690, { .reversed = false });
    RH_ScopedInstall(GetPedsInterior, 0x598620);
    RH_ScopedInstall(ReturnInteriorToPool, 0x5984B0);
    RH_ScopedInstall(GetInteriorFromPool, 0x5984A0);
    RH_ScopedInstall(GetVectorsInterior, 0x5983D0);
    RH_ScopedInstall(SetStealableObjectStolen, 0x598390);
    RH_ScopedOverloadedInstall(FindStealableObjectId, "1", 0x598360,  int32(InteriorManager_c::*)(CEntity *) const);
    RH_ScopedOverloadedInstall(FindStealableObjectId, "2", 0x5982F0,  int32(InteriorManager_c::*)(int32, int32, CVector) const);
    RH_ScopedInstall(HasInteriorHadStealDataSetup, 0x5982B0);
    RH_ScopedInstall(IsGroupActive, 0x598280);
    RH_ScopedInstall(GetPedsInteriorGroup, 0x598240);
    RH_ScopedInstall(SetEntryExitPtr, 0x598180);
    RH_ScopedInstall(GetBoundingBox, 0x598090);
    RH_ScopedInstall(ActivatePeds, 0x598080);
    RH_ScopedInstall(inlined_prune_visible_effects, 0x598070, { .reversed = false });
    RH_ScopedInstall(Update, 0x598F50);
    RH_ScopedInstall(Init, 0x5C0500);
}

// 0x5C0500
void InteriorManager_c::Init() {
    m_IsFrozen       = false;
    m_IsActive       = true;
    m_ArePedsEnabled = true;
    for (auto& i : m_Interiors) {
        m_InteriorPool.AddItem(&i);
    }
    for (auto&& [i, g] : notsa::enumerate(m_InteriorGroups)) {
        g.m_id = (uint8)i;
        m_InteriorGroupPool.AddItem(&g);
    }
    g_furnitureMan.Init();
    m_EnEx          = nullptr;
    m_InteriorCount = 0;
    m_ObjectCount   = 0;
    rng::fill(m_InteriorPedsAliveState, true);
    m_TimeLastPickupsGenerated = UINT32_MAX;
}

// 0x598F50
bool InteriorManager_c::Update() {
    ZoneScoped;

    if (m_IsFrozen) {
        return false;
    }

    const auto plyr = FindPlayerPed();

    InteriorEffectInfo_t visibleIntFxBuf[32];
    const auto numVisibleIntFx = plyr->m_nAreaCode != eAreaCodes::AREA_CODE_NORMAL_WORLD && m_IsActive && !plyr->GetTaskManager().GetActiveTaskAs<CTaskSimpleCarDrive>()
        ? GetVisibleEffects(visibleIntFxBuf, std::size(visibleIntFxBuf))
        : 0;
    PruneVisibleEffects(visibleIntFxBuf, numVisibleIntFx, 8, 20.f);
    const auto visibleIntFx = visibleIntFxBuf | rng::views::take(numVisibleIntFx);

    const auto IsFxAssociatedWithGroup = [](InteriorEffectInfo_t& fx, InteriorGroup_c& g) {
        return fx.entity == g.GetEntity() && fx.effects[0]->m_groupId == g.GetId();
    };

    // Remove interiors that are associated with effects that aren't visible anymore
    for (auto it = m_InteriorGroupList.begin(); it != m_InteriorGroupList.end();) {
        auto& g = *it;
        it++; // `RemoveItem` below invalidates the iterator, so increment here
        if (rng::none_of(visibleIntFx, [&](InteriorEffectInfo_t& fx) {
            return IsFxAssociatedWithGroup(fx, g) && !fx.culled;
        })) {
            g.Exit();
            m_InteriorGroupList.RemoveItem(&g);
            m_InteriorGroupPool.AddItem(&g);
        }
    }

    bool hasAddedAnyInteriors{};
    for (auto& intFx : visibleIntFx) {
        //> 0x599071 - Not visible?
        if (intFx.culled) {
            continue;
        }

        //> 0x59909F - Check if there's an existing interior group for this effect
        if (rng::any_of(m_InteriorGroupList, [&](InteriorGroup_c& g) { return IsFxAssociatedWithGroup(intFx, g); })) {
            continue;
        }

        //> 0x5990B8 - Make an interior group for this effect
        const auto grp = m_InteriorGroupPool.RemoveHead();
        assert(grp);
        grp->Init(intFx.entity, intFx.effects[0]->m_groupId);
        grp->m_enex = m_EnEx;
        m_InteriorGroupList.AddItem(grp);

        //> 0x59910C - Create interiors for it
        for (auto k = 0u; k < intFx.numFx; k++) {
            const auto i = m_InteriorPool.RemoveHead();
            if (!i) { // No more interiors to allocate
                break;
            }
            const auto& fxPos = intFx.entity->GetPosition();

            i->m_box        = intFx.effects[k];
            i->m_interiorId = (uint32)(fxPos.x * fxPos.y * fxPos.z) + intFx.fxIds[k];
            i->m_areaCode   = intFx.entity->m_nAreaCode;
            i->m_pGroup     = grp;

            i->Init(intFx.effects[k]->m_pos);
            grp->AddInterior(i);

            hasAddedAnyInteriors = true;
        }

        grp->Setup();

        m_TimeLastPickupsGenerated = CTimer::GetTimeInMS();
    }

    // Update all created groups
    for (auto& g : m_InteriorGroupList) {
        g.Update();
    }

    return hasAddedAnyInteriors;
}

// 0x598A60
void InteriorManager_c::PruneVisibleEffects(InteriorEffectInfo_t* pInteriorEffectInfos, int32 numInfos, int32 reqdNumInfos, float maxDis) {
    plugin::CallMethod<0x598A60, InteriorManager_c*, InteriorEffectInfo_t*, int32, int32, float>(this, pInteriorEffectInfos, numInfos, reqdNumInfos, maxDis);
}

// 0x598430
void InteriorManager_c::AddSameGroupEffectInfos(InteriorEffectInfo_t* intFxInfo, int32 a2) {
    const auto mi = intFxInfo->entity->GetModelInfo();
    for (size_t i = 0; i < mi->m_n2dfxCount; i++) {
        if (intFxInfo->numFx >= std::size(intFxInfo->effects)) {
            return; // NOTE/BUGFIX: It's really pointless to keep going at this point
        }
        if (i == intFxInfo->fxIds[0]) {
            continue;
        }
        const auto fx = C2dEffect::DynCast<C2dEffectInterior>(mi->Get2dEffect(i));
        if (!fx || intFxInfo->effects[0]->m_groupId != fx->m_groupId) {
            continue;
        }
        const auto j = intFxInfo->numFx++;
        intFxInfo->effects[j] = fx;
        intFxInfo->fxIds[j] = i;
    }
}

// 0x5980F0
bool InteriorManager_c::AreAnimsLoaded(int32 animBlock) {
    animBlock = [&] {
        switch (animBlock) {
        case 0:  return CAnimManager::GetAnimationBlockIndex("int_house");
        case 1:  return CAnimManager::GetAnimationBlockIndex("int_shop");
        case 2:  return CAnimManager::GetAnimationBlockIndex("int_office");
        default: return animBlock;
        }
    }();
    return CAnimManager::GetAnimationBlock((AssocGroupId)animBlock)->IsLoaded;
}

// 0x598010
void InteriorManager_c::Exit() {
    for (auto& g : m_InteriorGroupList) {
        g.Exit();
    }
    m_InteriorGroupList.RemoveAll();
    m_InteriorPool.RemoveAll();
    m_InteriorGroupPool.RemoveAll();
    g_furnitureMan.Exit();
}

// 0x598D80
int32 InteriorManager_c::GetVisibleEffects(InteriorEffectInfo_t* effectInfo, int32 totalEffects) {
    return plugin::CallMethodAndReturn<int32, 0x598D80, InteriorManager_c*, InteriorEffectInfo_t*, int32>(this, effectInfo, totalEffects);
}

// 0x598690
int32 InteriorManager_c::IsInteriorEffectVisible(C2dEffect* effect, CEntity* entity) {
    return plugin::CallMethodAndReturn<int32, 0x598690, InteriorManager_c*, C2dEffect*, CEntity*>(this, effect, entity);
}

// 0x598620
Interior_c* InteriorManager_c::GetPedsInterior(const CPed* ped) {
    return GetVectorsInterior(ped->GetPosition());
}

// 0x5984B0
void InteriorManager_c::ReturnInteriorToPool(Interior_c* interior) {
    m_InteriorPool.AddItem(interior);
}

// 0x5984A0
Interior_c* InteriorManager_c::GetInteriorFromPool() {
    return m_InteriorPool.RemoveHead();
}

// 0x5983D0
Interior_c* InteriorManager_c::GetVectorsInterior(const CVector& pt) { // TODO: Name is shit, should be `GetInteriorOfPoint` or something similar
    for (auto& g : m_InteriorGroupList) {
        for (auto& i : g.GetInteriors()) {
            if (i && i->IsPtInside(pt)) {
                return i;
            }
        }
    }
    return nullptr;
}

// 0x598390
void InteriorManager_c::SetStealableObjectStolen(CEntity* entity, uint8 isStolen) {
    if (const auto idx = FindStealableObjectId(entity); idx != -1) {
        m_Objects[idx].wasStolen = isStolen;
    }
}

// 0x598360
int32 InteriorManager_c::FindStealableObjectId(CEntity* entity) const {
    for (auto&& [i, v] : notsa::enumerate(GetObjects())) {
        if (v.entity == entity) {
            return i;
        }
    }
    return -1;
}

// 0x5982F0
int32 InteriorManager_c::FindStealableObjectId(int32 interiorId, int32 modelId, CVector point) const {
    for (auto&& [i, v] : notsa::enumerate(GetObjects())) {
        if (v.interiorId == interiorId && v.modelId == modelId && v.pos == point) {
            return i;
        }
    }
    return -1;
}

// 0x5982B0
bool InteriorManager_c::HasInteriorHadStealDataSetup(Interior_c* interior) {
    return m_InteriorCount && notsa::contains(GetInteriorIds(), interior->m_interiorId);
}

// 0x598280
int8 InteriorManager_c::IsGroupActive(int32 groupType) {
    return rng::any_of(m_InteriorGroupList, [&](InteriorGroup_c& g) {
        return g.m_groupType == groupType;
    });
}

// 0x598240
InteriorGroup_c* InteriorManager_c::GetPedsInteriorGroup(const CPed* ped) {
    for (auto& grp : m_InteriorGroupList) {
        if (notsa::contains(grp.GetPeds(), ped)) {
            return &grp;
        }
    }
    return nullptr;
}

// 0x598180
void InteriorManager_c::SetEntryExitPtr(CEntryExit* enex) {
    if ((enex->m_pLink ? enex->m_pLink : enex)->m_nArea == eAreaCodes::AREA_CODE_NORMAL_WORLD) {
        return;
    }
    if (enex->m_recEntrance == m_EnExRect) {
        return;
    }

    m_ObjectCount   = 0;
    m_InteriorCount = 0;

    rng::fill(m_InteriorPedsAliveState, true);

    m_EnEx     = enex;
    m_EnExRect = enex->m_recEntrance;
}

// 0x598090
bool InteriorManager_c::GetBoundingBox(FurnitureEntity_c* entity, CVector* pos) {
    for (auto& grp : m_InteriorGroupList) {
        for (const auto i : grp.GetInteriors()) {
            if (i) {
                return i->GetBoundingBox(entity, pos);
            }
        }
    }
    return false;
}

// 0x598080
void InteriorManager_c::ActivatePeds(bool enable) {
    m_ArePedsEnabled = enable;
}
