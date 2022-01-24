#include "StdInc.h"

#include "TagManager.h"

tTagDesc (&CTagManager::ms_tagDesc)[MAX_TAGS] = *(tTagDesc(*)[MAX_TAGS])0xA9A8C0;
int32& CTagManager::ms_numTags = *(int32*)0xA9AD70;
int32& CTagManager::ms_numTagged = *(int32*)0xA9AD74;
RxPipeline* &CTagManager::ms_pPipeline = *(RxPipeline**)0xA9AD78;

void CTagManager::InjectHooks()
{
    ReversibleHooks::Install("CTagManager", "Init", 0x49CC50, &CTagManager::Init);
    ReversibleHooks::Install("CTagManager", "ShutdownForRestart", 0x49CC60, &CTagManager::ShutdownForRestart);
    ReversibleHooks::Install("CTagManager", "GetTagPos", 0x49CEA0, &CTagManager::GetTagPos);
    ReversibleHooks::Install("CTagManager", "AddTag", 0x49CC90, &CTagManager::AddTag);
    ReversibleHooks::Install("CTagManager", "FindTagDesc", 0x49CCB0, &CTagManager::FindTagDesc);
    ReversibleHooks::Install("CTagManager", "IsTag", 0x49CCE0, &CTagManager::IsTag);
    ReversibleHooks::Install("CTagManager", "SetAlpha_RpAtomic", 0x49CD30, (void(*)(RpAtomic*, uint8))(&CTagManager::SetAlpha));
    ReversibleHooks::Install("CTagManager", "GetAlpha_RpAtomic", 0x49CD40, (uint8(*)(RpAtomic*))(&CTagManager::GetAlpha));
    ReversibleHooks::Install("CTagManager", "GetAlpha_Entity", 0x49CF90, (uint8(*)(CEntity*))(&CTagManager::GetAlpha));
    ReversibleHooks::Install("CTagManager", "GetPercentageTagged", 0x49CDA0, &CTagManager::GetPercentageTagged);
    ReversibleHooks::Install("CTagManager", "GetPercentageTaggedInArea", 0x49D0B0, &CTagManager::GetPercentageTaggedInArea);
    ReversibleHooks::Install("CTagManager", "UpdateNumTagged", 0x49CDE0, &CTagManager::UpdateNumTagged);
    ReversibleHooks::Install("CTagManager", "SetAlphaInArea", 0x49CFE0, &CTagManager::SetAlphaInArea);
    ReversibleHooks::Install("CTagManager", "SetAlpha_Entity", 0x49CEC0, (void(*)(CEntity*, uint8))(&CTagManager::SetAlpha));
    ReversibleHooks::Install("CTagManager", "GetNearestTag", 0x49D160, &CTagManager::GetNearestTag);
    ReversibleHooks::Install("CTagManager", "SetupAtomic", 0x49CE10, &CTagManager::SetupAtomic);
    ReversibleHooks::Install("CTagManager", "RenderTagForPC", 0x49CE40, &CTagManager::RenderTagForPC);
    ReversibleHooks::Install("CTagManager", "Save", 0x5D3D60, &CTagManager::Save);
    ReversibleHooks::Install("CTagManager", "Load", 0x5D3DA0, &CTagManager::Load);
}

void CTagManager::Init()
{
    ms_numTags = 0;
    ms_numTagged = 0;
}

void CTagManager::ShutdownForRestart()
{
    for (int32 i = ms_numTags; i > 0; --i)
        ms_tagDesc[i].m_nAlpha = 0;

    ms_numTagged = 0;
}

CVector& CTagManager::GetTagPos(int32 iTag)
{
    return ms_tagDesc[iTag].m_pEntity->GetPosition();
}

void CTagManager::AddTag(CEntity* entity)
{
    auto& tag = ms_tagDesc[ms_numTags];
    tag.m_pEntity = entity;
    tag.m_nAlpha = 0;

    ms_numTags++;
}

tTagDesc* CTagManager::FindTagDesc(CEntity* entity)
{
    if (!ms_numTags)
        return nullptr;

    for (int32 i = ms_numTags - 1; i >= 0; --i) {
        auto tagDesc = &ms_tagDesc[i];
        if (tagDesc->m_pEntity == entity)
            return tagDesc;
    }

    return nullptr;
}

bool CTagManager::IsTag(const CEntity* entity)
{
    auto mi = CModelInfo::GetModelInfo(entity->m_nModelIndex);
    if (mi->GetRwModelType() != rpATOMIC)
        return false;

    return mi->IsTagModel() && !mi->AsAtomicModelInfoPtr()->bTagDisabled;
}

void CTagManager::SetAlpha(RpAtomic* atomic, uint8 ucAlpha)
{
    CVisibilityPlugins::SetUserValue(atomic, ucAlpha);
}

uint8 CTagManager::GetAlpha(RpAtomic* atomic)
{
    return CVisibilityPlugins::GetUserValue(atomic);
}

uint8 CTagManager::GetAlpha(CEntity* entity)
{
    if (entity->m_pRwAtomic)
        return CVisibilityPlugins::GetUserValue(entity->m_pRwAtomic);

    auto tag = FindTagDesc(entity);
    assert(tag); // Originally the function would access unitialized memory, by clearing EAX and dereferencing pointer to [EAX + 0x4] right after that

    return tag->m_nAlpha;
}

void CTagManager::ResetAlpha(CEntity* entity)
{
    if (!entity->m_pRwAtomic)
        return;

    auto tagDesc = FindTagDesc(entity);
    SetAlpha(entity->m_pRwAtomic, tagDesc->m_nAlpha);
}

int64 CTagManager::GetPercentageTagged()
{
    return static_cast<int64>(static_cast<float>(ms_numTagged) / static_cast<float>(ms_numTags) * 100.0F);
}

int64_t CTagManager::GetPercentageTaggedInArea(CRect* area)
{
    int32 iTotalTags = 0;
    int32 iTagged = 0;
    for (int32 i = ms_numTags - 1; i >= 0; --i) {
        auto& tagDesc = ms_tagDesc[i];
        auto vecPos = CVector2D(tagDesc.m_pEntity->GetPosition());
        if (area->IsPointInside(vecPos)) {
            ++iTotalTags;
            if (tagDesc.m_nAlpha > ALPHA_TAGGED)
                ++iTagged;
        }
    }

    return static_cast<int64>(static_cast<double>(iTagged) / static_cast<double>(iTotalTags) * 100.0F);
}

void CTagManager::UpdateNumTagged()
{
    ms_numTagged = 0;
    if (!ms_numTags)
        return;

    for (int32 i = ms_numTags - 1; i >= 0; --i) {
        auto& tagDesc = ms_tagDesc[i];
        if (tagDesc.m_nAlpha > ALPHA_TAGGED)
            ms_numTagged++;
    }
}

void CTagManager::SetAlphaInArea(CRect* area, uint8 ucAlpha)
{
    for (int32 i = ms_numTags - 1; i >= 0; --i) {
        auto& tagDesc = ms_tagDesc[i];
        auto vecPos = CVector2D(tagDesc.m_pEntity->GetPosition());
        if (area->IsPointInside(vecPos) && tagDesc.m_pEntity->m_pRwAtomic) {
            SetAlpha(tagDesc.m_pEntity->m_pRwAtomic, ucAlpha);
            tagDesc.m_nAlpha = ucAlpha;
        }
    }

    UpdateNumTagged();
}

void CTagManager::SetAlpha(CEntity* entity, uint8 ucAlpha)
{
    if (entity->m_pRwAtomic)
        CVisibilityPlugins::SetUserValue(entity->m_pRwAtomic, ucAlpha);

    auto tagDesc = FindTagDesc(entity);
    auto bChangedState = false;
    if (ucAlpha > ALPHA_TAGGED && tagDesc->m_nAlpha <= ALPHA_TAGGED)
        bChangedState = true;

    tagDesc->m_nAlpha = ucAlpha;
    UpdateNumTagged();

    if (bChangedState && !TheCamera.m_bWideScreenOn) {
        if (ms_numTagged == ms_numTags)
            CGarages::TriggerMessage("TAG_ALL", -1, 5000, -1);
        else
            CGarages::TriggerMessage("TAG_ONE", ms_numTagged, 5000, ms_numTags);
    }
}

CEntity* CTagManager::GetNearestTag(const CVector & vecPos)
{
    auto vecPosUsed = CVector2D(vecPos.x, vecPos.y);
    int32 iClosestInd = -1;
    float fMinDist = RwRealMAXVAL;
    for (int32 i = ms_numTags - 1; i >= 0; --i) {
        auto& tagDesc = ms_tagDesc[i];
        auto vecTagPos = CVector2D(tagDesc.m_pEntity->GetPosition());
        auto fDist = (vecPosUsed - vecTagPos).SquaredMagnitude();
        if (fDist < fMinDist) {
            fMinDist = fDist;
            iClosestInd = i;
        }
    }

    assert(iClosestInd != -1);
    return ms_tagDesc[iClosestInd].m_pEntity;
}

void CTagManager::SetupAtomic(RpAtomic* atomic)
{
    auto geometry = RpAtomicGetGeometry(atomic);
    auto material = RpGeometryGetMaterial(geometry, 1);
    material->pipeline = ms_pPipeline;
    RpGeometrySetFlags(geometry, RpGeometryGetFlags(geometry) | rpGEOMETRYMODULATEMATERIALCOLOR);
    SetAlpha(atomic, 0);
}

void CTagManager::RenderTagForPC(RpAtomic* pAtomic)
{
    auto geometry = RpAtomicGetGeometry(pAtomic);
    auto material = RpGeometryGetMaterial(geometry, 1);
    material->color.alpha = GetAlpha(pAtomic);
    RpAtomicRender(pAtomic);
}

void CTagManager::Save()
{
    CGenericGameStorage::SaveDataToWorkBuffer(&ms_numTags, 4);
    if (!ms_numTags)
        return;

    for (auto i = 0; i < ms_numTags; ++i) {
        CGenericGameStorage::SaveDataToWorkBuffer(&ms_tagDesc[i].m_nAlpha, 1);
    }
}

void CTagManager::Load()
{
    CGenericGameStorage::SaveDataToWorkBuffer(&ms_numTags, 4); // Yeah, original also saves into buffer instead of loading
    if (!ms_numTags)
        return;

    for (auto i = 0; i < ms_numTags; ++i) {
        CGenericGameStorage::LoadDataFromWorkBuffer(&ms_tagDesc[i].m_nAlpha, 1);
    }
}
