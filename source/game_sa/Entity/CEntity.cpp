/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CEntity.h"

#include "CPointLights.h"
#include "CEscalators.h"
#include "CCustomBuildingDNPipeline.h"
#include "COcclusion.h"

void CEntity::InjectHooks()
{
//Virtual
    ReversibleHooks::Install("CEntity", "Add", 0x533020, (void(CEntity::*)())(&CEntity::Add_Reversed));
    ReversibleHooks::Install("CEntity", "Add_rect", 0x5347D0, (void(CEntity::*)(const CRect&))(&CEntity::Add_Reversed));
    ReversibleHooks::Install("CEntity", "Remove", 0x534AE0, &CEntity::Remove_Reversed);
    ReversibleHooks::Install("CEntity", "SetIsStatic", 0x403E20, &CEntity::SetIsStatic_Reversed);
    ReversibleHooks::Install("CEntity", "SetModelIndexNoCreate", 0x533700, &CEntity::SetModelIndexNoCreate_Reversed);
    ReversibleHooks::Install("CEntity", "CreateRwObject", 0x533D30, &CEntity::CreateRwObject_Reversed);
    ReversibleHooks::Install("CEntity", "DeleteRwObject", 0x534030, &CEntity::DeleteRwObject_Reversed);
    ReversibleHooks::Install("CEntity", "GetBoundRect", 0x534120, &CEntity::GetBoundRect_Reversed);
    ReversibleHooks::Install("CEntity", "ProcessControl", 0x403E40, &CEntity::ProcessControl_Reversed);
    ReversibleHooks::Install("CEntity", "ProcessCollision", 0x403E50, &CEntity::ProcessCollision_Reversed);
    ReversibleHooks::Install("CEntity", "ProcessShift", 0x403E60, &CEntity::ProcessShift_Reversed);
    ReversibleHooks::Install("CEntity", "TestCollision", 0x403E70, &CEntity::TestCollision_Reversed);
    ReversibleHooks::Install("CEntity", "Teleport", 0x403E80, &CEntity::Teleport_Reversed);
    ReversibleHooks::Install("CEntity", "SpecialEntityPreCollisionStuff", 0x403E90, &CEntity::SpecialEntityPreCollisionStuff_Reversed);
    ReversibleHooks::Install("CEntity", "SpecialEntityCalcCollisionSteps", 0x403EA0, &CEntity::SpecialEntityCalcCollisionSteps_Reversed);
    ReversibleHooks::Install("CEntity", "PreRender", 0x535FA0, &CEntity::PreRender_Reversed);
    ReversibleHooks::Install("CEntity", "Render", 0x534310, &CEntity::Render_Reversed);
    ReversibleHooks::Install("CEntity", "SetupLighting", 0x553DC0, &CEntity::SetupLighting_Reversed);
    ReversibleHooks::Install("CEntity", "RemoveLighting", 0x553370, &CEntity::RemoveLighting_Reversed);
    ReversibleHooks::Install("CEntity", "FlagToDestroyWhenNextProcessed", 0x533240, &CEntity::FlagToDestroyWhenNextProcessed_Reversed);

//Class
    ReversibleHooks::Install("CEntity", "UpdateRwFrame", 0x532B00, &CEntity::UpdateRwFrame);
    ReversibleHooks::Install("CEntity", "UpdateRpHAnim", 0x532B20, &CEntity::UpdateRpHAnim);
    ReversibleHooks::Install("CEntity", "HasPreRenderEffects", 0x532B70, &CEntity::HasPreRenderEffects);
    ReversibleHooks::Install("CEntity", "DoesNotCollideWithFlyers", 0x532D40, &CEntity::DoesNotCollideWithFlyers);
    ReversibleHooks::Install("CEntity", "ModifyMatrixForPoleInWind", 0x532DB0, &CEntity::ModifyMatrixForPoleInWind);
    ReversibleHooks::Install("CEntity", "LivesInThisNonOverlapSector", 0x533050, &CEntity::LivesInThisNonOverlapSector);
    ReversibleHooks::Install("CEntity", "SetupBigBuilding", 0x533150, &CEntity::SetupBigBuilding);
    ReversibleHooks::Install("CEntity", "ModifyMatrixForCrane", 0x533170, &CEntity::ModifyMatrixForCrane);
    ReversibleHooks::Install("CEntity", "PreRenderForGlassWindow", 0x533170, &CEntity::PreRenderForGlassWindow);
    ReversibleHooks::Install("CEntity", "SetRwObjectAlpha", 0x5332C0, &CEntity::SetRwObjectAlpha);
    ReversibleHooks::Install("CEntity", "FindTriggerPointCoors", 0x533380, &CEntity::FindTriggerPointCoors);
    ReversibleHooks::Install("CEntity", "GetRandom2dEffect", 0x533410, &CEntity::GetRandom2dEffect);
    ReversibleHooks::Install("CEntity", "TransformFromObjectSpace_ref", 0x5334F0, (CVector(CEntity::*)(CVector const&)) (&CEntity::TransformFromObjectSpace));
    ReversibleHooks::Install("CEntity", "TransformFromObjectSpace_ptr", 0x533560, (CVector*(CEntity::*)(CVector&, CVector const&)) (&CEntity::TransformFromObjectSpace));
    ReversibleHooks::Install("CEntity", "CreateEffects", 0x533790, &CEntity::CreateEffects);
    ReversibleHooks::Install("CEntity", "DestroyEffects", 0x533BF0, &CEntity::DestroyEffects);
    ReversibleHooks::Install("CEntity", "AttachToRwObject", 0x533ED0, &CEntity::AttachToRwObject);
    ReversibleHooks::Install("CEntity", "DetachFromRwObject", 0x533FB0, &CEntity::DetachFromRwObject);
    ReversibleHooks::Install("CEntity", "GetBoundCentre_ptr", 0x534250, (CVector*(CEntity::*)(CVector*)) (&CEntity::GetBoundCentre));
    ReversibleHooks::Install("CEntity", "GetBoundCentre_ref", 0x534290, (void(CEntity::*)(CVector&)) (&CEntity::GetBoundCentre));
    ReversibleHooks::Install("CEntity", "RenderEffects", 0x5342B0, &CEntity::RenderEffects);
    ReversibleHooks::Install("CEntity", "GetIsTouching_ent", 0x5343F0, (bool(CEntity::*)(CEntity*)) (&CEntity::GetIsTouching));
    ReversibleHooks::Install("CEntity", "GetIsTouching_vec", 0x5344B0, (bool(CEntity::*)(CVector const&, float)) (&CEntity::GetIsTouching));
    ReversibleHooks::Install("CEntity", "GetIsOnScreen", 0x534540, &CEntity::GetIsOnScreen);
    ReversibleHooks::Install("CEntity", "GetIsBoundingBoxOnScreen", 0x5345D0, &CEntity::GetIsBoundingBoxOnScreen);
    ReversibleHooks::Install("CEntity", "ModifyMatrixForTreeInWind", 0x534E90, &CEntity::ModifyMatrixForTreeInWind);
    ReversibleHooks::Install("CEntity", "ModifyMatrixForBannerInWind", 0x535040, &CEntity::ModifyMatrixForBannerInWind);
    ReversibleHooks::Install("CEntity", "GetColModel", 0x535300, &CEntity::GetColModel);
    ReversibleHooks::Install("CEntity", "CalculateBBProjection", 0x535340, &CEntity::CalculateBBProjection);
    ReversibleHooks::Install("CEntity", "UpdateAnim", 0x535F00, &CEntity::UpdateAnim);
    ReversibleHooks::Install("CEntity", "IsVisible", 0x536BC0, &CEntity::IsVisible);
    ReversibleHooks::Install("CEntity", "GetDistanceFromCentreOfMassToBaseOfModel", 0x536BE0, &CEntity::GetDistanceFromCentreOfMassToBaseOfModel);
    ReversibleHooks::Install("CEntity", "CleanUpOldReference", 0x571A00, &CEntity::CleanUpOldReference);
    ReversibleHooks::Install("CEntity", "ResolveReferences", 0x571A40, &CEntity::ResolveReferences);
    ReversibleHooks::Install("CEntity", "PruneReferences", 0x571A90, &CEntity::PruneReferences);
    ReversibleHooks::Install("CEntity", "RegisterReference", 0x571B70, &CEntity::RegisterReference);
    ReversibleHooks::Install("CEntity", "ProcessLightsForEntity", 0x6FC7A0, &CEntity::ProcessLightsForEntity);
    ReversibleHooks::Install("CEntity", "RemoveEscalatorsForEntity", 0x717900, &CEntity::RemoveEscalatorsForEntity);
    ReversibleHooks::Install("CEntity", "IsEntityOccluded", 0x71FAE0, &CEntity::IsEntityOccluded);
    ReversibleHooks::Install("CEntity", "GetModellingMatrix", 0x46A2D0, &CEntity::GetModellingMatrix);
    ReversibleHooks::Install("CEntity", "UpdateRW", 0x446F90, &CEntity::UpdateRW);
    ReversibleHooks::Install("CEntity", "SetAtomicAlphaCB", 0x533290, &CEntity::SetAtomicAlphaCB);
    ReversibleHooks::Install("CEntity", "SetMaterialAlphaCB", 0x533280, &CEntity::SetMaterialAlphaCB);

//Statics
    ReversibleHooks::Install("CEntity", "MaterialUpdateUVAnimCB", 0x532D70, &MaterialUpdateUVAnimCB);
    ReversibleHooks::Install("CEntity", "IsEntityPointerValid", 0x533310, &IsEntityPointerValid);
}

CEntity::CEntity() : CPlaceable()
{
    m_nStatus = eEntityStatus::STATUS_PLAYER;
    m_nType = eEntityType::ENTITY_TYPE_BUILDING;

    m_nFlags = 0;
    m_bIsVisible = true;
    m_bBackfaceCulled = true;

    m_nScanCode = 0;
    m_nAreaCode = 0;
    m_nModelIndex = 0xFFFF;
    m_pRwObject = nullptr;
    m_nIplIndex = 0;
    m_nRandomSeed = rand();
    m_pReferences = nullptr;
    m_pStreamingLink = nullptr;
    m_nNumLodChildren = 0;
    m_nNumLodChildrenRendered = 0;
    m_pLod = nullptr;
}

CEntity::~CEntity()
{
    if (m_pLod)
        m_pLod->m_nNumLodChildren--;

    CEntity::DeleteRwObject();
    CEntity::ResolveReferences();
}

void CEntity::Add()
{
    CEntity::Add_Reversed();
}
void CEntity::Add_Reversed()
{
    auto rect = CRect();
    GetBoundRect(&rect);
    Add(rect);
}

void CEntity::Add(CRect const& rect)
{
    CEntity::Add_Reversed(rect);
}
void CEntity::Add_Reversed(CRect const& rect)
{
    CRect usedRect = rect;
    if (usedRect.left < -3000.0F)
        usedRect.left = -3000.0F;

    if (usedRect.right >= 3000.0F)
        usedRect.right = 2999.0F;

    if (usedRect.top < -3000.0F)
        usedRect.top = -3000.0F;

    if (usedRect.bottom >= 3000.0F)
        usedRect.bottom = 2999.0F;

    if (m_bIsBIGBuilding) {
        int32 startSectorX = CWorld::GetLodSectorX(usedRect.left);
        int32 startSectorY = CWorld::GetLodSectorY(usedRect.top);
        int32 endSectorX = CWorld::GetLodSectorX(usedRect.right);
        int32 endSectorY = CWorld::GetLodSectorY(usedRect.bottom);
        for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
            for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
                auto& pLodListEntry = CWorld::GetLodPtrList(sectorX, sectorY);
                pLodListEntry.AddItem(this);
            }
        }
    }
    else {
        int32 startSectorX = CWorld::GetSectorX(usedRect.left);
        int32 startSectorY = CWorld::GetSectorY(usedRect.top);
        int32 endSectorX = CWorld::GetSectorX(usedRect.right);
        int32 endSectorY = CWorld::GetSectorY(usedRect.bottom);
        for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
            for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
                CPtrListDoubleLink* pDoubleLinkList = nullptr;
                auto pRepeatSector = GetRepeatSector(sectorX, sectorY);
                auto pSector = GetSector(sectorX, sectorY);

                if (IsBuilding()) { //Buildings are treated as single link here, needs checking if the list is actually single or double
                    reinterpret_cast<CPtrListSingleLink*>(&pSector->m_buildings)->AddItem(this);
                    continue;
                }

                switch (m_nType)
                {
                case ENTITY_TYPE_DUMMY:
                    pDoubleLinkList = &pSector->m_dummies;
                    break;
                case ENTITY_TYPE_VEHICLE:
                    pDoubleLinkList = &pRepeatSector->m_lists[REPEATSECTOR_VEHICLES];
                    break;
                case ENTITY_TYPE_PED:
                    pDoubleLinkList = &pRepeatSector->m_lists[REPEATSECTOR_PEDS];
                    break;
                case ENTITY_TYPE_OBJECT:
                    pDoubleLinkList = &pRepeatSector->m_lists[REPEATSECTOR_OBJECTS];
                    break;
                }

                pDoubleLinkList->AddItem(this);
            }
        }
    }
}

void CEntity::Remove()
{
    CEntity::Remove_Reversed();
}
void CEntity::Remove_Reversed()
{
    auto usedRect = CRect();
    GetBoundRect(&usedRect);

    if (usedRect.left < -3000.0F)
        usedRect.left = -3000.0F;

    if (usedRect.right >= 3000.0F)
        usedRect.right = 2999.0F;

    if (usedRect.top < -3000.0F)
        usedRect.top = -3000.0F;

    if (usedRect.bottom >= 3000.0F)
        usedRect.bottom = 2999.0F;

    if (m_bIsBIGBuilding) {
        int32 startSectorX = CWorld::GetLodSectorX(usedRect.left);
        int32 startSectorY = CWorld::GetLodSectorY(usedRect.top);
        int32 endSectorX = CWorld::GetLodSectorX(usedRect.right);
        int32 endSectorY = CWorld::GetLodSectorY(usedRect.bottom);
        for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
            for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
                auto& pLodListEntry = CWorld::GetLodPtrList(sectorX, sectorY);
                pLodListEntry.DeleteItem(this);
            }
        }
    }
    else {
        int32 startSectorX = CWorld::GetSectorX(usedRect.left);
        int32 startSectorY = CWorld::GetSectorY(usedRect.top);
        int32 endSectorX = CWorld::GetSectorX(usedRect.right);
        int32 endSectorY = CWorld::GetSectorY(usedRect.bottom);
        for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
            for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
                CPtrListDoubleLink* pDoubleLinkList = nullptr;
                auto pRepeatSector = GetRepeatSector(sectorX, sectorY);
                auto pSector = GetSector(sectorX, sectorY);

                if (IsBuilding()) { //Buildings are treated as single link here
                    reinterpret_cast<CPtrListSingleLink*>(&pSector->m_buildings)->DeleteItem(this);
                    continue;
                }

                switch (m_nType)
                {
                case ENTITY_TYPE_DUMMY:
                    pDoubleLinkList = &pSector->m_dummies;
                    break;
                case ENTITY_TYPE_VEHICLE:
                    pDoubleLinkList = &pRepeatSector->m_lists[REPEATSECTOR_VEHICLES];
                    break;
                case ENTITY_TYPE_PED:
                    pDoubleLinkList = &pRepeatSector->m_lists[REPEATSECTOR_PEDS];
                    break;
                case ENTITY_TYPE_OBJECT:
                    pDoubleLinkList = &pRepeatSector->m_lists[REPEATSECTOR_OBJECTS];
                    break;
                }

                pDoubleLinkList->DeleteItem(this);
            }
        }
    }
}

void CEntity::SetIsStatic(bool isStatic)
{
    return CEntity::SetIsStatic_Reversed(isStatic);
}
void CEntity::SetIsStatic_Reversed(bool isStatic)
{
    m_bIsStatic = isStatic;
}

void CEntity::SetModelIndex(uint32 index)
{
    return CEntity::SetModelIndex_Reversed(index);
}
void CEntity::SetModelIndex_Reversed(uint32 index)
{
    CEntity::SetModelIndexNoCreate(index);
    CEntity::CreateRwObject();
}

void CEntity::SetModelIndexNoCreate(uint32 index)
{
    return CEntity::SetModelIndexNoCreate_Reversed(index);
}
void CEntity::SetModelIndexNoCreate_Reversed(uint32 index)
{
    auto pModelInfo = CModelInfo::GetModelInfo(index);
    m_nModelIndex = index;
    m_bHasPreRenderEffects = CEntity::HasPreRenderEffects();

    if (pModelInfo->GetIsDrawLast())
        m_bDrawLast = true;

    if (!pModelInfo->IsBackfaceCulled())
        m_bBackfaceCulled = false;

    auto pAtomicInfo = pModelInfo->AsAtomicModelInfoPtr();
    if (pAtomicInfo && !pAtomicInfo->bTagDisabled && pAtomicInfo->IsTagModel())
        CTagManager::AddTag(this);
}

void CEntity::CreateRwObject()
{
    return CEntity::CreateRwObject_Reversed();
}
void CEntity::CreateRwObject_Reversed()
{
    if (!m_bIsVisible)
        return;

    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (m_bRenderDamaged) {
        CDamageAtomicModelInfo::ms_bCreateDamagedVersion = true;
        m_pRwObject = pModelInfo->CreateInstance();
        CDamageAtomicModelInfo::ms_bCreateDamagedVersion = false;
    }
    else {
        m_pRwObject = pModelInfo->CreateInstance();
    }

    if (!m_pRwObject)
        return;

    if (IsBuilding())
        ++gBuildings;

    CEntity::UpdateRW();
    if (RwObjectGetType(m_pRwObject) == rpATOMIC) {
        if (CTagManager::IsTag(this))
            CTagManager::ResetAlpha(this);

        CCustomBuildingDNPipeline::PreRenderUpdate(m_pRwAtomic, true);
    }
    else if (RwObjectGetType(m_pRwObject) == rpCLUMP && pModelInfo->bIsRoad) {
        if (IsObject()) {
            auto pObj = static_cast<CObject*>(this);
            if (!pObj->m_pMovingList)
                pObj->AddToMovingList();

            pObj->SetIsStatic(false);
        }
        else {
            CWorld::ms_listMovingEntityPtrs.AddItem(this);
        }

        if (m_pLod && m_pLod->m_pRwObject && RwObjectGetType(m_pLod->m_pRwObject) == rpCLUMP) {
            auto pLodAssoc = RpAnimBlendClumpGetFirstAssociation(m_pLod->m_pRwClump);
            if (pLodAssoc) {
                auto pAssoc = RpAnimBlendClumpGetFirstAssociation(m_pRwClump);
                if (pAssoc)
                    pAssoc->SetCurrentTime(pLodAssoc->m_fCurrentTime);
            }
        }
    }

    pModelInfo->AddRef();
    m_pStreamingLink = CStreaming::AddEntity(this);
    CEntity::CreateEffects();

    auto pUsedAtomic = m_pRwAtomic;
    if (RwObjectGetType(m_pRwObject) != rpATOMIC)
        pUsedAtomic = GetFirstAtomic(m_pRwClump);

    if (!CCustomBuildingRenderer::IsCBPCPipelineAttached(pUsedAtomic))
        m_bLightObject = true;
}

void CEntity::DeleteRwObject()
{
    CEntity::DeleteRwObject_Reversed();
}
void CEntity::DeleteRwObject_Reversed()
{
    if (!m_pRwObject)
        return;

    if (RwObjectGetType(m_pRwObject) == rpATOMIC) {
        auto pFrame = RpAtomicGetFrame(m_pRwAtomic);
        RpAtomicDestroy(m_pRwAtomic);
        RwFrameDestroy(pFrame);
    }
    else if (RwObjectGetType(m_pRwObject) == rpCLUMP) {
        auto pFirstAtomic = GetFirstAtomic(m_pRwClump);
        if (pFirstAtomic && RpSkinGeometryGetSkin(RpAtomicGetGeometry(pFirstAtomic)))
            RpClumpForAllAtomics(m_pRwClump, AtomicRemoveAnimFromSkinCB, nullptr);

        RpClumpDestroy(m_pRwClump);
    }
    m_pRwObject = nullptr;
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    pModelInfo->RemoveRef();
    CStreaming::RemoveEntity(m_pStreamingLink);
    m_pStreamingLink = nullptr;

    if (IsBuilding())
        --gBuildings;

    if (pModelInfo->GetModelType() == MODEL_INFO_CLUMP
        && pModelInfo->IsRoad()
        && !IsObject()) {

        CWorld::ms_listMovingEntityPtrs.DeleteItem(this);
    }

    CEntity::DestroyEffects();
    CEntity::RemoveEscalatorsForEntity();
}

CRect* CEntity::GetBoundRect(CRect* pRect)
{
    return CEntity::GetBoundRect_Reversed(pRect);
}
CRect* CEntity::GetBoundRect_Reversed(CRect* pRect)
{
    CColModel* colModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();
    CVector vecMin = colModel->m_boundBox.m_vecMin;
    CVector vecMax = colModel->m_boundBox.m_vecMax;
    CRect rect;
    CVector point;
    TransformFromObjectSpace(point, vecMin);
    rect.StretchToPoint(point.x, point.y);
    TransformFromObjectSpace(point, vecMax);
    rect.StretchToPoint(point.x, point.y);
    float maxX = vecMax.x;
    vecMax.x = vecMin.x;
    vecMin.x = maxX;
    TransformFromObjectSpace(point, vecMin);
    rect.StretchToPoint(point.x, point.y);
    TransformFromObjectSpace(point, vecMax);
    rect.StretchToPoint(point.x, point.y);
    *pRect = rect;
    return pRect;
}

void CEntity::ProcessControl()
{
    CEntity::ProcessControl_Reversed();
}
void CEntity::ProcessControl_Reversed()
{
    return;
}

void CEntity::ProcessCollision()
{
    CEntity::ProcessCollision_Reversed();
}
void CEntity::ProcessCollision_Reversed()
{
    return;
}

void CEntity::ProcessShift()
{
    CEntity::ProcessShift_Reversed();
}
void CEntity::ProcessShift_Reversed()
{
    return;
}

bool CEntity::TestCollision(bool bApplySpeed)
{
    return CEntity::TestCollision_Reversed(bApplySpeed);
}
bool CEntity::TestCollision_Reversed(bool bApplySpeed)
{
    return false;
}

void CEntity::Teleport(CVector destination, bool resetRotation)
{
    CEntity::Teleport_Reversed(destination, resetRotation);
}
void CEntity::Teleport_Reversed(CVector destination, bool resetRotation)
{
    return;
}

void CEntity::SpecialEntityPreCollisionStuff(CEntity *colEntity, bool bIgnoreStuckCheck, bool* bCollisionDisabled, bool* bCollidedEntityCollisionIgnored, bool* bCollidedEntityUnableToMove, bool* bThisOrCollidedEntityStuck)
{
    CEntity::SpecialEntityPreCollisionStuff_Reversed(colEntity, bIgnoreStuckCheck, bCollisionDisabled, bCollidedEntityCollisionIgnored, bCollidedEntityUnableToMove, bThisOrCollidedEntityStuck);
}
void CEntity::SpecialEntityPreCollisionStuff_Reversed(CEntity* colEntity, bool bIgnoreStuckCheck, bool* bCollisionDisabled, bool* bCollidedEntityCollisionIgnored, bool* bCollidedEntityUnableToMove, bool* bThisOrCollidedEntityStuck)
{
    return;
}

uint8 CEntity::SpecialEntityCalcCollisionSteps(bool * bProcessCollisionBeforeSettingTimeStep, bool* unk2)
{
    return CEntity::SpecialEntityCalcCollisionSteps_Reversed(bProcessCollisionBeforeSettingTimeStep, unk2);
}
uint8 CEntity::SpecialEntityCalcCollisionSteps_Reversed(bool* bProcessCollisionBeforeSettingTimeStep, bool* unk2)
{
    return 1;
}

void CEntity::PreRender()
{
    CEntity::PreRender_Reversed();
}
void CEntity::PreRender_Reversed()
{
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    auto pAtomicInfo = pModelInfo->AsAtomicModelInfoPtr();

    if (pModelInfo->m_n2dfxCount)
        CEntity::ProcessLightsForEntity();

    if (!pModelInfo->HasBeenPreRendered()) {
        pModelInfo->SetHasBeenPreRendered(true);

        if (pAtomicInfo && pAtomicInfo->m_pRwObject) {
            if (RpMatFXAtomicQueryEffects(pAtomicInfo->m_pRwAtomic) && RpAtomicGetGeometry(pAtomicInfo->m_pRwAtomic)) {
                RpGeometryForAllMaterials(RpAtomicGetGeometry(pAtomicInfo->m_pRwAtomic), MaterialUpdateUVAnimCB, nullptr);
            }
        }

        pModelInfo->IncreaseAlpha();

        if (pAtomicInfo) {
            CCustomBuildingDNPipeline::PreRenderUpdate(pAtomicInfo->m_pRwAtomic, false);
        }
        else if (pModelInfo->GetModelType() == MODEL_INFO_CLUMP) {
            RpClumpForAllAtomics(pModelInfo->m_pRwClump, CCustomBuildingDNPipeline::PreRenderUpdateRpAtomicCB, false);
        }
    }

    if (!m_bHasPreRenderEffects)
        return;

    if (pAtomicInfo && pAtomicInfo->SwaysInWind()
        && (!IsObject() || !static_cast<CObject*>(this)->objectFlags.bIsExploded)) {

        auto vecCamPos = CVector2D(TheCamera.GetPosition());
        auto vecEntPos = CVector2D(GetPosition());
        auto fDist = DistanceBetweenPoints2D(vecCamPos, vecEntPos);
        CObject::fDistToNearestTree = std::min(CObject::fDistToNearestTree, fDist);
        CEntity::ModifyMatrixForTreeInWind();
    }

    if (IsBuilding()) {
        if (pAtomicInfo && pAtomicInfo->IsCrane())
            CEntity::ModifyMatrixForCrane();

        return;
    }

    if (!IsObject() && !IsDummy())
        return;

    if (IsObject() && !IsDummy()) {
        auto pObject = reinterpret_cast<CObject*>(this);
        if(m_nModelIndex == ModelIndices::MI_COLLECTABLE1) {
            CPickups::DoCollectableEffects(this);
            CEntity::UpdateRW();
            CEntity::UpdateRwFrame();
        }
        else if (m_nModelIndex == ModelIndices::MI_MONEY) {
            CPickups::DoMoneyEffects(this);
            CEntity::UpdateRW();
            CEntity::UpdateRwFrame();
        }
        else if (m_nModelIndex == ModelIndices::MI_CARMINE
            || m_nModelIndex == ModelIndices::MI_NAUTICALMINE
            || m_nModelIndex == ModelIndices::MI_BRIEFCASE) {

            if (pObject->objectFlags.bIsPickup) {
                CPickups::DoMineEffects(this);
                CEntity::UpdateRW();
                CEntity::UpdateRwFrame();
            }
        }
        else if (m_nModelIndex == eModelID::MODEL_MISSILE) {
            if (CReplay::Mode != REPLAY_MODE_1) {
                CVector vecPos = GetPosition();
                auto fRand = static_cast<float>(rand() % 16) / 16.0F;
                CShadows::StoreShadowToBeRendered(eShadowTextureType::SHADOWTEX_PED,
                                                  gpShadowExplosionTex,
                                                  &vecPos,
                                                  8.0F,
                                                  0.0F,
                                                  0.0F,
                                                  -8.0F,
                                                  255,
                                                  static_cast<uint8>(fRand * 200.0F),
                                                  static_cast<uint8>(fRand * 160.0F),
                                                  static_cast<uint8>(fRand * 120.0F),
                                                  20.0F,
                                                  false,
                                                  1.0F,
                                                  nullptr,
                                                  false);

                CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT,
                                       vecPos,
                                       CVector(0.0F, 0.0F, 0.0F),
                                       8.0F,
                                       fRand,
                                       fRand * 0.8F,
                                       fRand * 0.6F,
                                       RwFogType::rwFOGTYPENAFOGTYPE,
                                       true,
                                       nullptr);

                CCoronas::RegisterCorona(reinterpret_cast<uint32>(this),
                                         nullptr,
                                         static_cast<uint8>(fRand * 255.0F),
                                         static_cast<uint8>(fRand * 220.0F),
                                         static_cast<uint8>(fRand * 190.0F),
                                         255,
                                         vecPos,
                                         fRand * 6.0F,
                                         300.0F,
                                         gpCoronaTexture[0],
                                         eCoronaFlareType::FLARETYPE_NONE,
                                         true,
                                         false,
                                         0,
                                         0.0F,
                                         false,
                                         1.5F,
                                         0,
                                         15.0F,
                                         false,
                                         false);
            }
        }
        else if (m_nModelIndex == ModelIndices::MI_FLARE) {
            CVector vecPos = GetPosition();
            auto fRand = static_cast<float>(rand() % 16) / 16.0F;
            fRand = std::max(fRand, 0.5F);
            CShadows::StoreShadowToBeRendered(eShadowTextureType::SHADOWTEX_PED,
                                              gpShadowExplosionTex,
                                              &vecPos,
                                              8.0F,
                                              0.0F,
                                              0.0F,
                                              -8.0F,
                                              255,
                                              static_cast<uint8>(fRand * 200.0F),
                                              static_cast<uint8>(fRand * 200.0F),
                                              static_cast<uint8>(fRand * 200.0F),
                                              20.0F,
                                              false,
                                              1.0F,
                                              nullptr,
                                              false);

            CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT,
                                   vecPos,
                                   CVector(0.0F, 0.0F, 0.0F),
                                   32.0F,
                                   fRand,
                                   fRand,
                                   fRand,
                                   RwFogType::rwFOGTYPENAFOGTYPE,
                                   true,
                                   nullptr);

            CCoronas::RegisterCorona(reinterpret_cast<uint32>(this),
                                     nullptr,
                                     static_cast<uint8>(fRand * 255.0F),
                                     static_cast<uint8>(fRand * 255.0F),
                                     static_cast<uint8>(fRand * 255.0F),
                                     255,
                                     vecPos,
                                     fRand * 6.0F,
                                     300.0F,
                                     gpCoronaTexture[0],
                                     eCoronaFlareType::FLARETYPE_NONE,
                                     true,
                                     false,
                                     0,
                                     0.0F,
                                     false,
                                     1.5F,
                                     0,
                                     15.0F,
                                     false,
                                     false);
        }
        else if (IsGlassModel(this)) {
            CEntity::PreRenderForGlassWindow();
        }
        else if (pObject->objectFlags.bIsPickup) {
            CPickups::DoPickUpEffects(this);
            CEntity::UpdateRW();
            CEntity::UpdateRwFrame();
        }
        else if (m_nModelIndex == eModelID::MODEL_GRENADE) {
            auto const& vecPos = GetPosition();
            auto vecScaledCam = TheCamera.m_mCameraMatrix.GetRight() * 0.07F;
            auto vecStreakStart = vecPos - vecScaledCam;
            auto vecStreakEnd = vecPos + vecScaledCam;
            if (CVector2D(pObject->m_vecMoveSpeed).Magnitude() > 0.03F) {
                CMotionBlurStreaks::RegisterStreak(reinterpret_cast<uint32>(this),
                                                   100,
                                                   100,
                                                   100,
                                                   255,
                                                   vecStreakStart,
                                                   vecStreakEnd);
            }
        }
        else if (m_nModelIndex == eModelID::MODEL_MOLOTOV) {
            auto const& vecPos = GetPosition();
            auto vecScaledCam = TheCamera.m_mCameraMatrix.GetRight() * 0.07F;
            auto vecStreakStart = vecPos - vecScaledCam;
            auto vecStreakEnd = vecPos + vecScaledCam;
            if (CVector2D(pObject->m_vecMoveSpeed).Magnitude() > 0.03F) {
                float fWaterLevel;
                if (!CWaterLevel::GetWaterLevelNoWaves(vecPos.x, vecPos.y, vecPos.z, &fWaterLevel, nullptr, nullptr) || vecPos.z > fWaterLevel) {
                    CMotionBlurStreaks::RegisterStreak(reinterpret_cast<uint32>(this),
                                                   255,
                                                   160,
                                                   100,
                                                   255,
                                                   vecStreakStart,
                                                   vecStreakEnd);
                }
            }
        }
        else if (m_nModelIndex == ModelIndices::MI_BEACHBALL) {
            if (DistanceBetweenPoints(GetPosition(), TheCamera.GetPosition()) < 50.0F) {
                auto ucShadowStrength = static_cast<uint8>(CTimeCycle::m_CurrentColours.m_nShadowStrength);
                CShadows::StoreShadowToBeRendered(eShadowType::SHADOW_DEFAULT,
                                                  gpShadowPedTex,
                                                  &GetPosition(),
                                                  0.4F,
                                                  0.0F,
                                                  0.0F,
                                                  -0.4F,
                                                  ucShadowStrength,
                                                  ucShadowStrength,
                                                  ucShadowStrength,
                                                  ucShadowStrength,
                                                  20.0F,
                                                  false,
                                                  1.0F,
                                                  nullptr,
                                                  false);
            }
        }
        else if (m_nModelIndex == ModelIndices::MI_MAGNOCRANE_HOOK
            || m_nModelIndex == ModelIndices::MI_WRECKING_BALL
            || m_nModelIndex == ModelIndices::MI_CRANE_MAGNET
            || m_nModelIndex == ModelIndices::MI_MINI_MAGNET
            || m_nModelIndex == ModelIndices::MI_CRANE_HARNESS) {

            if (DistanceBetweenPoints(GetPosition(), TheCamera.GetPosition()) < 100.0F) {
                CShadows::StoreShadowToBeRendered(eShadowType::SHADOW_DEFAULT,
                                                  gpShadowPedTex,
                                                  &GetPosition(),
                                                  2.0F,
                                                  0.0F,
                                                  0.0F,
                                                  -2.0F,
                                                  128,
                                                  128,
                                                  128,
                                                  128,
                                                  50.0F,
                                                  false,
                                                  1.0F,
                                                  nullptr,
                                                  false);
            }
        }
        else if (m_nModelIndex == ModelIndices::MI_WINDSOCK) {
            CEntity::ModifyMatrixForPoleInWind();
        }
    }

    if (m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS) {
        CTrafficLights::DisplayActualLight(this);
        CShadows::StoreShadowForPole(this, 2.957F, 0.147F, 0.0F, 16.0F, 0.4F, 0);
        return;
    }
    if (m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_VERTICAL)
        CTrafficLights::DisplayActualLight(this);
    if (m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_MIAMI) {
        CTrafficLights::DisplayActualLight(this);
        CShadows::StoreShadowForPole(this, 4.81F, 0.0F, 0.0F, 16.0F, 0.4F, 0);
        return;
    }
    if (m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_TWOVERTICAL) {
        CTrafficLights::DisplayActualLight(this);
        CShadows::StoreShadowForPole(this, 7.503F, 0.0F, 0.0F, 16.0F, 0.4F, 0);
        return;
    }
    if (m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_3
        || m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_4
        || m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_5
        || m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_GAY) {

        CTrafficLights::DisplayActualLight(this);
    }
    else if (m_nModelIndex == ModelIndices::MI_SINGLESTREETLIGHTS1)
        CShadows::StoreShadowForPole(this, 7.744F, 0.0F, 0.0F, 16.0F, 0.4F, 0);
    else if (m_nModelIndex == ModelIndices::MI_SINGLESTREETLIGHTS2)
        CShadows::StoreShadowForPole(this, 0.043F, 0.0F, 0.0F, 16.0F, 0.4F, 0);
    else if (m_nModelIndex == ModelIndices::MI_SINGLESTREETLIGHTS3)
        CShadows::StoreShadowForPole(this, 1.143F, 0.145F, 0.0F, 16.0F, 0.4F, 0);
    else if (m_nModelIndex == ModelIndices::MI_DOUBLESTREETLIGHTS)
        CShadows::StoreShadowForPole(this, 0.0F, -0.048F, 0.0F, 16.0F, 0.4F, 0);
    else if (m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_VEGAS) {
        CTrafficLights::DisplayActualLight(this);
        CShadows::StoreShadowForPole(this, 7.5F, 0.2F, 0.0F, 16.0F, 0.4F, 0);
    }
}

void CEntity::Render()
{
    CEntity::Render_Reversed();
}
void CEntity::Render_Reversed()
{
    if (!m_pRwObject)
        return;

    if (RwObjectGetType(m_pRwObject) == rpATOMIC && CTagManager::IsTag(this)) {
        CTagManager::RenderTagForPC(m_pRwAtomic);
        return;
    }

    uint32 savedAlphaRef;
    if (m_nModelIndex == ModelIndices::MI_JELLYFISH || m_nModelIndex == ModelIndices::MI_JELLYFISH01) {
        RwRenderStateGet(rwRENDERSTATEALPHATESTFUNCTIONREF, &savedAlphaRef);
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, 0u);
    }

    m_bImBeingRendered = true;

    if (RwObjectGetType(m_pRwObject) == rpATOMIC)
        RpAtomicRender(m_pRwAtomic);
    else
        RpClumpRender(m_pRwClump);

    CStreaming::RenderEntity(m_pStreamingLink);
    CEntity::RenderEffects();

    m_bImBeingRendered = false;

    if (m_nModelIndex == ModelIndices::MI_JELLYFISH || m_nModelIndex == ModelIndices::MI_JELLYFISH01) {
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void*)savedAlphaRef);
    }
}

bool CEntity::SetupLighting()
{
    return CEntity::SetupLighting_Reversed();
}
bool CEntity::SetupLighting_Reversed()
{
    if (!m_bLightObject)
        return false;

    ActivateDirectional();
    const auto& vecPos = GetPosition();
    auto fLight = CPointLights::GenerateLightsAffectingObject(&vecPos, nullptr, this) * 0.5F;
    SetLightColoursForPedsCarsAndObjects(fLight);

    return true;
}

void CEntity::RemoveLighting(bool bRemove)
{
    CEntity::RemoveLighting_Reversed(bRemove);
}
void CEntity::RemoveLighting_Reversed(bool bRemove)
{
    if (!bRemove)
        return;

    SetAmbientColours();
    DeActivateDirectional();
    CPointLights::RemoveLightsAffectingObject();
}

void CEntity::FlagToDestroyWhenNextProcessed()
{
    CEntity::FlagToDestroyWhenNextProcessed_Reversed();
}

void CEntity::FlagToDestroyWhenNextProcessed_Reversed()
{
    return;
}

// 0x532B00
void CEntity::UpdateRwFrame()
{
    if (!m_pRwObject)
        return;

    RwFrameUpdateObjects(static_cast<RwFrame*>(rwObjectGetParent(m_pRwObject)));
}

// 0x532B20
void CEntity::UpdateRpHAnim()
{
    auto* pFirstAtomic = GetFirstAtomic(m_pRwClump);
    if (!pFirstAtomic)
        return;

    if (RpSkinGeometryGetSkin(RpAtomicGetGeometry(pFirstAtomic)) && !m_bDontUpdateHierarchy) {
        auto* pAnimHierarchy = GetAnimHierarchyFromSkinClump(m_pRwClump);
        RpHAnimHierarchyUpdateMatrices(pAnimHierarchy);
    }
}

// 0x532B70
bool CEntity::HasPreRenderEffects()
{
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (!pModelInfo->SwaysInWind()
        && !pModelInfo->IsCrane()
        && m_nModelIndex != ModelIndices::MI_COLLECTABLE1
        && m_nModelIndex != ModelIndices::MI_MONEY
        && m_nModelIndex != ModelIndices::MI_CARMINE
        && m_nModelIndex != ModelIndices::MI_NAUTICALMINE
        && m_nModelIndex != ModelIndices::MI_BRIEFCASE
        && m_nModelIndex != eModelID::MODEL_MISSILE
        && m_nModelIndex != eModelID::MODEL_GRENADE
        && m_nModelIndex != eModelID::MODEL_MOLOTOV
        && m_nModelIndex != ModelIndices::MI_BEACHBALL
        && m_nModelIndex != ModelIndices::MI_MAGNOCRANE_HOOK
        && m_nModelIndex != ModelIndices::MI_WRECKING_BALL
        && m_nModelIndex != ModelIndices::MI_CRANE_MAGNET
        && m_nModelIndex != ModelIndices::MI_MINI_MAGNET
        && m_nModelIndex != ModelIndices::MI_CRANE_HARNESS
        && m_nModelIndex != ModelIndices::MI_WINDSOCK
        && m_nModelIndex != ModelIndices::MI_FLARE
        && !IsGlassModel(this)
        && (!IsObject() || !reinterpret_cast<CObject*>(this)->objectFlags.bIsPickup)
        && !CTrafficLights::IsMITrafficLight(m_nModelIndex)
        && m_nModelIndex != ModelIndices::MI_SINGLESTREETLIGHTS1
        && m_nModelIndex != ModelIndices::MI_SINGLESTREETLIGHTS2
        && m_nModelIndex != ModelIndices::MI_SINGLESTREETLIGHTS3
        && m_nModelIndex != ModelIndices::MI_DOUBLESTREETLIGHTS) {

        if (!pModelInfo->m_n2dfxCount)
            return false;

        for (int32 i = 0; i < pModelInfo->m_n2dfxCount; ++i) {
            if (pModelInfo->Get2dEffect(i)->m_nType == e2dEffectType::EFFECT_LIGHT)
                return true;
        }

        return false;
    }
    return true;
}

// 0x532D40
bool CEntity::DoesNotCollideWithFlyers()
{
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (pModelInfo->SwaysInWind())
        return true;

    return pModelInfo->bDontCollideWithFlyer;
}

// 0x532D70
RpMaterial* MaterialUpdateUVAnimCB(RpMaterial* material, void* data)
{
    if (!RpMaterialUVAnimExists(material))
        return material;

    auto fTimeStep = CTimer::ms_fTimeStep / 50.0F;
    RpMaterialUVAnimAddAnimTime(material, fTimeStep);
    RpMaterialUVAnimApplyUpdate(material);
    return material;
}

// 0x532DB0
void CEntity::ModifyMatrixForPoleInWind()
{
    auto vecWindDir = CVector(CWeather::WindDir.x + 0.01F, CWeather::WindDir.y + 0.01F, 0.1F);
    auto vecNormalisedDir = vecWindDir;
    vecNormalisedDir.Normalise();

    auto vecCross = CrossProduct(CVector(0.0F, 0.0F, 1.0F), vecNormalisedDir);
    vecCross.Normalise();
    auto vecCross2 = CrossProduct(vecNormalisedDir, vecCross);

    CMatrix& matrix = GetMatrix();
    matrix.GetRight() = vecCross;
    matrix.GetForward() = vecNormalisedDir;
    matrix.GetUp() = vecCross2;
    CEntity::UpdateRW();
    CEntity::UpdateRwFrame();
}

// 0x533050
bool CEntity::LivesInThisNonOverlapSector(int32 sectorX, int32 sectorY)
{
    auto rect = CRect();
    GetBoundRect(&rect);
    float xCenter, yCenter;
    rect.GetCenter(&xCenter, &yCenter);
    auto xEntSector = CWorld::GetSectorX(xCenter);
    auto yEntSector = CWorld::GetSectorY(yCenter);

    return sectorX == xEntSector && sectorY == yEntSector;

}

// 0x533150
void CEntity::SetupBigBuilding()
{
    m_bUsesCollision = false;
    m_bIsBIGBuilding = true;
    m_bStreamingDontDelete = true;

    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    pModelInfo->bDoWeOwnTheColModel = true;
}

// 0x533170
void CEntity::ModifyMatrixForCrane()
{
    if (CTimer::GetIsPaused())
        return;

    if (!m_pRwObject)
        return;

    auto pRwMat = CEntity::GetModellingMatrix();
    if (!pRwMat)
        return;

    auto tempMat = CMatrix(pRwMat, 0);
    auto fRot = (CTimer::m_snTimeInMilliseconds & 0x3FF) * (PI / 512.26F);
    tempMat.SetRotateZOnly(fRot);
    tempMat.UpdateRW();
    CEntity::UpdateRwFrame();

}

// 0x533240
void CEntity::PreRenderForGlassWindow()
{
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (pModelInfo->IsGlassType2())
        return;

    CGlass::AskForObjectToBeRenderedInGlass(this);
    m_bIsVisible = false;
}

// 0x5332C0
void CEntity::SetRwObjectAlpha(int32 alpha)
{
    if (!m_pRwObject)
        return;

    if (RwObjectGetType(m_pRwObject) == rpATOMIC) {
        CEntity::SetAtomicAlphaCB(m_pRwAtomic, (void*)alpha);
    }
    else if (RwObjectGetType(m_pRwObject) == rpCLUMP) {
        RpClumpForAllAtomics(m_pRwClump, CEntity::SetAtomicAlphaCB, (void*)alpha);
    }
}

// 0x533310
bool IsEntityPointerValid(CEntity* entity)
{
    if (!entity)
        return false;

    switch (entity->m_nType) {
    case eEntityType::ENTITY_TYPE_BUILDING:
        return IsBuildingPointerValid(reinterpret_cast<CBuilding*>(entity));
    case eEntityType::ENTITY_TYPE_VEHICLE:
        return IsVehiclePointerValid(reinterpret_cast<CVehicle*>(entity));
    case eEntityType::ENTITY_TYPE_PED:
        return IsPedPointerValid(reinterpret_cast<CPed*>(entity));
    case eEntityType::ENTITY_TYPE_OBJECT:
        return IsObjectPointerValid(reinterpret_cast<CObject*>(entity));
    case eEntityType::ENTITY_TYPE_DUMMY:
        return IsDummyPointerValid(reinterpret_cast<CDummy*>(entity));
    case eEntityType::ENTITY_TYPE_NOTINPOOLS:
        return true;
    }

    return false;
}

// 0x533380
CVector* CEntity::FindTriggerPointCoors(CVector* pOutVec, int32 triggerIndex)
{
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    for (int32 iFxInd = 0; iFxInd < pModelInfo->m_n2dfxCount; ++iFxInd) {
        auto pEffect = pModelInfo->Get2dEffect(iFxInd);
        if (pEffect->m_nType == e2dEffectType::EFFECT_SLOTMACHINE_WHEEL && pEffect->iSlotMachineIndex == triggerIndex) {
            *pOutVec = GetMatrix() * pEffect->m_vecPosn;
            return pOutVec;
        }
    }

    pOutVec->Set(0.0F, 0.0F, 0.0F);
    return pOutVec;
}

/**
 * Returns a random effect with the given effectType among all the effects of the entity.
 * @param effectType Type of effect. See e2dEffectType. (Always EFFECT_ATTRACTOR)
 * @param bCheckForEmptySlot Should check for empty slot. (Always true)
 * @return Random effect
 * @addr 0x533410
 */
C2dEffect* CEntity::GetRandom2dEffect(int32 effectType, bool bCheckForEmptySlot)
{
    C2dEffect* apArr[32];
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    int32 iFoundCount = 0;
    for (int32 iFxInd = 0; iFxInd < pModelInfo->m_n2dfxCount; ++iFxInd) {
        auto pEffect = pModelInfo->Get2dEffect(iFxInd);
        if (pEffect->m_nType != effectType)
            continue;

        if (bCheckForEmptySlot && !GetPedAttractorManager()->HasEmptySlot(pEffect, this))
            continue;

        if (iFoundCount < 32) {
            apArr[iFoundCount] = pEffect;
            ++iFoundCount;
        }
    }

    if (iFoundCount) {
        auto iRandInd = CGeneral::GetRandomNumberInRange(0, iFoundCount);
        return apArr[iRandInd];
    }

    return nullptr;
}

// 0x5334F0
CVector CEntity::TransformFromObjectSpace(CVector const& offset)
{
    auto result = CVector();
    if (m_matrix) {
        result = *m_matrix * offset;
        return result;
    }

    TransformPoint(result, m_placement, offset);
    return result;
}

// 0x533560
CVector* CEntity::TransformFromObjectSpace(CVector& outPosn, CVector const& offset)
{
    auto result = CEntity::TransformFromObjectSpace(offset);
    outPosn = result;
    return &outPosn;
}

// 0x533790
void CEntity::CreateEffects()
{
    m_bHasRoadsignText = false;
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (!pModelInfo->m_n2dfxCount)
        return;

    for (int32 iFxInd = 0; iFxInd < pModelInfo->m_n2dfxCount; ++iFxInd) {
        auto pEffect = pModelInfo->Get2dEffect(iFxInd);
        if (pEffect->m_nType == e2dEffectType::EFFECT_LIGHT) {
            m_bHasPreRenderEffects = true;
        }
        else if (pEffect->m_nType == e2dEffectType::EFFECT_PARTICLE) {
            auto pMatrix = CEntity::GetModellingMatrix();
            g_fx.CreateEntityFx(this, pEffect->particle.m_szName, &pEffect->m_vecPosn, pMatrix);
        }
        else if (pEffect->m_nType == e2dEffectType::EFFECT_ATTRACTOR) {
            if (pEffect->pedAttractor.m_nAttractorType == ePedAttractorType::PED_ATTRACTOR_TRIGGER_SCRIPT)
                CTheScripts::ScriptsForBrains.RequestAttractorScriptBrainWithThisName(pEffect->pedAttractor.m_szScriptName);
        }
        else if (pEffect->m_nType == e2dEffectType::EFFECT_ENEX) {
            auto vecExit = pEffect->m_vecPosn + pEffect->enEx.m_vecExitPosn;
            auto vecWorldEffect = CEntity::TransformFromObjectSpace(pEffect->m_vecPosn);
            auto vecWorldExit = CEntity::TransformFromObjectSpace(vecExit);

            if (pEffect->enEx.bTimedEffect) {
                auto ucDays = CClock::ms_nGameClockDays;
                if (pEffect->enEx.m_nTimeOn > pEffect->enEx.m_nTimeOff && CClock::ms_nGameClockHours < pEffect->enEx.m_nTimeOff)
                    ucDays--;

                srand(reinterpret_cast<uint32>(this) + ucDays);
            }

            auto fHeading = GetHeading();
            auto fExitRot = pEffect->enEx.m_fExitAngle + RadiansToDegrees(fHeading);
            auto fEnterRot = pEffect->enEx.m_fEnterAngle + RadiansToDegrees(fHeading);
            auto iEnExId = CEntryExitManager::AddOne(vecWorldEffect.x,
                                                     vecWorldEffect.y,
                                                     vecWorldEffect.z,
                                                     fEnterRot,
                                                     pEffect->enEx.m_vecRadius.x,
                                                     pEffect->enEx.m_vecRadius.y,
                                                     0,
                                                     vecWorldExit.x,
                                                     vecWorldExit.y,
                                                     vecWorldExit.z,
                                                     fExitRot,
                                                     pEffect->enEx.m_nInteriorId,
                                                     pEffect->enEx.m_nFlags1 + (pEffect->enEx.m_nFlags2 << 8),
                                                     pEffect->enEx.m_nSkyColor,
                                                     pEffect->enEx.m_nTimeOn,
                                                     pEffect->enEx.m_nTimeOff,
                                                     0,
                                                     pEffect->enEx.m_szInteriorName);

            if (iEnExId != -1) {
                auto pAddedEffect = CEntryExitManager::mp_poolEntryExits->GetAt(iEnExId);
                if (pAddedEffect->m_pLink && !pAddedEffect->m_pLink->m_nFlags.bEnableAccess)
                    pAddedEffect->m_nFlags.bEnableAccess = false;
            }
        }
        else if (pEffect->m_nType == e2dEffectType::EFFECT_ROADSIGN) {
            m_bHasRoadsignText = true;
            auto uiPalleteId = C2dEffect::Roadsign_GetPaletteIDFromFlags(pEffect->roadsign.m_nFlags);
            auto uiLettersPerLine = C2dEffect::Roadsign_GetNumLettersFromFlags(pEffect->roadsign.m_nFlags);
            auto uiNumLines = C2dEffect::Roadsign_GetNumLinesFromFlags(pEffect->roadsign.m_nFlags);

            auto pSignAtomic = CCustomRoadsignMgr::CreateRoadsignAtomic(pEffect->roadsign.m_vecSize.x,
                pEffect->roadsign.m_vecSize.y,
                uiNumLines,
                &pEffect->roadsign.m_pText[0],
                &pEffect->roadsign.m_pText[16],
                &pEffect->roadsign.m_pText[32],
                &pEffect->roadsign.m_pText[48],
                uiLettersPerLine,
                uiPalleteId);

            auto pFrame = RpAtomicGetFrame(pSignAtomic);
            RwFrameSetIdentity(pFrame);

            const CVector axis0{1.0F, 0.0F, 0.0F}, axis1{0.0F, 1.0F, 0.0F}, axis2{0.0F, 0.0F, 1.0F};
            RwFrameRotate(pFrame, &axis2, pEffect->roadsign.m_vecRotation.z, RwOpCombineType::rwCOMBINEREPLACE);
            RwFrameRotate(pFrame, &axis0, pEffect->roadsign.m_vecRotation.x, RwOpCombineType::rwCOMBINEPOSTCONCAT);
            RwFrameRotate(pFrame, &axis1, pEffect->roadsign.m_vecRotation.y, RwOpCombineType::rwCOMBINEPOSTCONCAT);
            RwFrameTranslate(pFrame, &pEffect->m_vecPosn, RwOpCombineType::rwCOMBINEPOSTCONCAT);
            RwFrameUpdateObjects(pFrame);
            pEffect->roadsign.m_pAtomic = pSignAtomic;
        }
        else if (pEffect->m_nType == e2dEffectType::EFFECT_ESCALATOR) {
            auto vecStart = CEntity::TransformFromObjectSpace(pEffect->m_vecPosn);
            auto vecBottom = CEntity::TransformFromObjectSpace(pEffect->escalator.m_vecBottom);
            auto vecTop = CEntity::TransformFromObjectSpace(pEffect->escalator.m_vecTop);
            auto vecEnd = CEntity::TransformFromObjectSpace(pEffect->escalator.m_vecEnd);
            auto bMovingDown = pEffect->escalator.m_nDirection == 0;

            CEscalators::AddOne(vecStart, vecBottom, vecTop, vecEnd, bMovingDown, this);
        }
    }
}

// 0x533BF0
void CEntity::DestroyEffects()
{
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (!pModelInfo->m_n2dfxCount)
        return;

    for (int32 iFxInd = 0; iFxInd < pModelInfo->m_n2dfxCount; ++iFxInd) {
        auto pEffect = pModelInfo->Get2dEffect(iFxInd);

        if (pEffect->m_nType == e2dEffectType::EFFECT_ATTRACTOR) {
            if (pEffect->pedAttractor.m_nAttractorType == ePedAttractorType::PED_ATTRACTOR_TRIGGER_SCRIPT)
                CTheScripts::ScriptsForBrains.MarkAttractorScriptBrainWithThisNameAsNoLongerNeeded(pEffect->pedAttractor.m_szScriptName);
        }
        else if (pEffect->m_nType == e2dEffectType::EFFECT_PARTICLE) {
            g_fx.DestroyEntityFx(this);
        }
        else if (pEffect->m_nType == e2dEffectType::EFFECT_ROADSIGN) {
            C2dEffect::DestroyAtomic(pEffect->roadsign.m_pAtomic);
            pEffect->roadsign.m_pAtomic = nullptr;
        }
        else if (pEffect->m_nType == e2dEffectType::EFFECT_ENEX) {
            auto vecWorld = CEntity::TransformFromObjectSpace(pEffect->m_vecPosn);
            auto iNearestEnex = CEntryExitManager::FindNearestEntryExit(vecWorld, 1.5F, -1);
            if (iNearestEnex != -1) {
                auto enex = CEntryExitManager::mp_poolEntryExits->GetAt(iNearestEnex);
                if (enex->m_nFlags.bEnteredWithoutExit)
                    enex->m_nFlags.bDeleteEnex = true;
                else
                    CEntryExitManager::DeleteOne(iNearestEnex);
            }
        }
    }
}

// 0x533ED0
void CEntity::AttachToRwObject(RwObject* object, bool updateEntityMatrix)
{
    if (!m_bIsVisible)
        return;

    m_pRwObject = object;
    if (!m_pRwObject)
        return;

    if (updateEntityMatrix) {
        CMatrix& matrix = GetMatrix();
        auto pRwMatrix = CEntity::GetModellingMatrix();
        matrix.UpdateMatrix(pRwMatrix);
    }

    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (RwObjectGetType(m_pRwObject) == rpCLUMP && pModelInfo->IsRoad()) {
        if (IsObject())
        {
            reinterpret_cast<CObject*>(this)->AddToMovingList();
            SetIsStatic(false);
        }
        else {
            CWorld::ms_listMovingEntityPtrs.AddItem(this);
        }
    }
    

    pModelInfo->AddRef();
    m_pStreamingLink = CStreaming::AddEntity(this);
    CEntity::CreateEffects();
}

// 0x533FB0
void CEntity::DetachFromRwObject()
{
    if (!m_pRwObject)
        return;

    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    pModelInfo->RemoveRef();
    CStreaming::RemoveEntity(m_pStreamingLink);
    m_pStreamingLink = nullptr;

    if (pModelInfo->GetModelType() == ModelInfoType::MODEL_INFO_CLUMP
        && pModelInfo->IsRoad()
        && !IsObject()) {

        CWorld::ms_listMovingEntityPtrs.DeleteItem(this);
    }

    CEntity::DestroyEffects();
    m_pRwObject = nullptr;
}

// 0x534250
CVector* CEntity::GetBoundCentre(CVector* pOutCentre)
{
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    const auto& pColCenter = pModelInfo->GetColModel()->GetBoundCenter();
    return CEntity::TransformFromObjectSpace(*pOutCentre, pColCenter);
}

// 0x534290
void CEntity::GetBoundCentre(CVector& outCentre)
{
    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    const auto& pColCenter = pModelInfo->GetColModel()->GetBoundCenter();
    CEntity::TransformFromObjectSpace(outCentre, pColCenter);
}

CVector CEntity::GetBoundCentre()
{
    CVector v;
    GetBoundCentre(v);
    return v;
}

// 0x5342B0
void CEntity::RenderEffects()
{
    if (!m_bHasRoadsignText)
        return;

    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (!pModelInfo->m_n2dfxCount)
        return;

    for (int32 iFxInd = 0; iFxInd < pModelInfo->m_n2dfxCount; ++iFxInd) {
        auto pEffect = pModelInfo->Get2dEffect(iFxInd);
        if (pEffect->m_nType != e2dEffectType::EFFECT_ROADSIGN)
            continue;

        CCustomRoadsignMgr::RenderRoadsignAtomic(pEffect->roadsign.m_pAtomic, TheCamera.GetPosition());
    }
}

// 0x5343F0
bool CEntity::GetIsTouching(CEntity* entity)
{
    CVector thisVec;
    CEntity::GetBoundCentre(thisVec);

    CVector otherVec;
    entity->GetBoundCentre(otherVec);

    auto fThisRadius = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundRadius();
    auto fOtherRadius = CModelInfo::GetModelInfo(entity->m_nModelIndex)->GetColModel()->GetBoundRadius();

    return (thisVec - otherVec).Magnitude() <= (fThisRadius + fOtherRadius);
}

// 0x5344B0
bool CEntity::GetIsTouching(CVector const& centre, float radius)
{
    CVector thisVec;
    CEntity::GetBoundCentre(thisVec);
    auto fThisRadius = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundRadius();

    return (thisVec - centre).Magnitude() <= (fThisRadius + radius);
}

// 0x534540
bool CEntity::GetIsOnScreen()
{
    CVector thisVec;
    CEntity::GetBoundCentre(thisVec);
    auto fThisRadius = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundRadius();

    if (TheCamera.IsSphereVisible(thisVec, fThisRadius, reinterpret_cast<RwMatrixTag*>(&TheCamera.m_mMatInverse)))
        return true;

    if (TheCamera.m_bMirrorActive)
        return TheCamera.IsSphereVisible(thisVec, fThisRadius, reinterpret_cast<RwMatrixTag*>(&TheCamera.m_mMatMirrorInverse));

    return false;
}

// 0x5345D0
bool CEntity::GetIsBoundingBoxOnScreen()
{
    auto pColModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();
    CVector vecBnd[2]{ pColModel->m_boundBox.m_vecMin, pColModel->m_boundBox.m_vecMax };

    RwV3d vecNormals[2];
    if (m_matrix) {
        auto tempMat = CMatrix();
        Invert(*m_matrix, tempMat);
        TransformVectors(&vecNormals[0], 2, tempMat, &TheCamera.m_avecFrustumWorldNormals[0]);
    }
    else {
        auto tempTrans = CSimpleTransform();
        tempTrans.Invert(m_placement);
        TransformVectors(&vecNormals[0], 2, tempTrans, &TheCamera.m_avecFrustumWorldNormals[0]);
    }

    for (int32 i = 0; i < 2; ++i) {
        CVector vecUsed;
        vecUsed.x = vecBnd[signbit(vecNormals[i].x)].x;
        vecUsed.y = vecBnd[signbit(vecNormals[i].y)].y;
        vecUsed.z = vecBnd[signbit(vecNormals[i].z)].z;

        auto vecWorld = CEntity::TransformFromObjectSpace(vecUsed);
        if (DotProduct(vecWorld, TheCamera.m_avecFrustumWorldNormals[i]) > TheCamera.m_fFrustumPlaneOffsets[i]
            && (!TheCamera.m_bMirrorActive
                || DotProduct(vecWorld, TheCamera.m_avecFrustumWorldNormals_Mirror[i]) > TheCamera.m_fFrustumPlaneOffsets_Mirror[i])) {

            ++numBBFailed;
            return false;
        }
    }
    return true;
}

// 0x534E90
void CEntity::ModifyMatrixForTreeInWind()
{
    if (CTimer::GetIsPaused())
        return;

    auto pRwMat = CEntity::GetModellingMatrix();
    if (!pRwMat)
        return;

    auto pAt = RwMatrixGetAt(pRwMat);

    float fWindOffset;
    if (CWeather::Wind >= 0.5F) {
        auto uiOffset1 = (((m_nRandomSeed + CTimer::m_snTimeInMilliseconds * 8) & 0xFFFF) / 4096) & 0xF;
        auto uiOffset2 = (uiOffset1 + 1) & 0xF;
        auto fContrib = static_cast<float>(((m_nRandomSeed + CTimer::m_snTimeInMilliseconds * 8) & 0xFFF)) / 4096.0F;

        fWindOffset = (1.0F - fContrib) * CWeather::saTreeWindOffsets[uiOffset1];
        fWindOffset += 1.0F + fContrib * CWeather::saTreeWindOffsets[uiOffset2];
        fWindOffset *= CWeather::Wind;
        fWindOffset *= 0.015F;

    }
    else {
        auto uiTimeOffset = (reinterpret_cast<uint32>(this) + CTimer::m_snTimeInMilliseconds) & 0xFFF;
        
        fWindOffset = sin(uiTimeOffset * 0.0015332032F) * 0.005F;
        if (CWeather::Wind >= 0.2F)
            fWindOffset *= 1.6F;
    }

    pAt->x = fWindOffset;
    if (CModelInfo::GetModelInfo(m_nModelIndex)->IsSwayInWind2())
        pAt->x += CWeather::Wind * 0.03F;

    pAt->y = pAt->x;    
    pAt->x *= CWeather::WindDir.x;
    pAt->y *= CWeather::WindDir.y;

    CWindModifiers::FindWindModifier(GetPosition(), &pAt->x, &pAt->y);
    CEntity::UpdateRwFrame();

}

// 0x535040
void CEntity::ModifyMatrixForBannerInWind()
{
    if (CTimer::GetIsPaused())
        return;

    auto vecPos = CVector2D(GetPosition());
    auto uiOffset = static_cast<uint16>(16 * (CTimer::m_snTimeInMilliseconds + (static_cast<uint16>(vecPos.x + vecPos.y) * 64)));

    auto fWind = 0.2F;
    if (CWeather::Wind >= 0.1F) {
        if (CWeather::Wind < 0.8F)
            fWind = 0.43F;
        else
            fWind = 0.66F;
    }

    auto fContrib = static_cast<float>(uiOffset & 0x7FF) / 2048.0F;
    uint32 uiIndex = uiOffset / 2048;
    auto fWindOffset = (1.0F - fContrib) * CWeather::saBannerWindOffsets[uiIndex];
    fWindOffset += fContrib * CWeather::saBannerWindOffsets[(uiIndex + 1) & 0x1F];
    fWindOffset *= CWeather::Wind;

    auto fZPos = sqrt(1.0F - pow(fWindOffset, 2.0F));

    CMatrix& matrix = GetMatrix();
    auto vecCross = CrossProduct(matrix.GetForward(), matrix.GetUp());
    vecCross.z = 0.0F;
    vecCross.Normalise();

    auto vecWind = CVector(vecCross.x * fWindOffset, vecCross.y * fWindOffset, fZPos);
    auto vecCross2 = CrossProduct(matrix.GetForward(), vecWind);

    matrix.GetRight() = vecCross2;
    matrix.GetUp() = vecWind;

    CEntity::UpdateRW();
    CEntity::UpdateRwFrame();

}

RwMatrix* CEntity::GetModellingMatrix()
{
    if (!m_pRwObject)
        return nullptr;

    return RwFrameGetMatrix((RwFrame*)rwObjectGetParent(m_pRwObject));
}

// 0x535300
CColModel* CEntity::GetColModel()
{
    if (IsVehicle() && static_cast<CVehicle*>(this)->m_vehicleSpecialColIndex > -1)
        return &CVehicle::m_aSpecialColModel[static_cast<CVehicle*>(this)->m_vehicleSpecialColIndex];
    else
        return CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();
}

// 0x535340
//https://gamedev.stackexchange.com/a/35948
//https://gamedev.stackexchange.com/questions/153326/how-to-rotate-directional-billboard-particle-sprites-toward-the-direction-the-pa/153814#153814
void CEntity::CalculateBBProjection(CVector* pVecCorner1, CVector* pVecCorner2, CVector* pVecCorner3, CVector* pVecCorner4)
{
    CMatrix& matrix = GetMatrix();
    auto fMagRight = CVector2D(matrix.GetRight()).Magnitude();
    auto fMagForward = CVector2D(matrix.GetForward()).Magnitude();
    auto fMagUp = CVector2D(matrix.GetUp()).Magnitude();

    auto pColModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();
    auto fMaxX = std::max(-pColModel->m_boundBox.m_vecMin.x, pColModel->m_boundBox.m_vecMax.x);
    auto fMaxY = std::max(-pColModel->m_boundBox.m_vecMin.y, pColModel->m_boundBox.m_vecMax.y);
    auto fMaxZ = std::max(-pColModel->m_boundBox.m_vecMin.z, pColModel->m_boundBox.m_vecMax.z);

    auto fXSize = fMaxX * fMagRight * 2.0F;
    auto fYSize = fMaxY * fMagForward * 2.0F;
    auto fZSize = fMaxZ * fMagUp * 2.0F;

    CVector vecDir, vecNormalized, vecTransformed;
    float fMult1, fMult2, fMult3, fMult4;
    if (fXSize > fYSize && fXSize > fZSize) {
        vecDir = matrix.GetRight();
        vecDir.z = 0.0F;

        vecNormalized = vecDir;
        vecNormalized.Normalise();

        auto vecScaled = vecDir * fMaxX;
        vecTransformed = vecScaled + GetPosition();

        auto vecTemp = GetPosition() - vecScaled;
        vecDir = vecTemp;

        fMult1 = (vecNormalized.x * matrix.GetForward().x + vecNormalized.y * matrix.GetForward().y) * fMaxY;
        fMult2 = (vecNormalized.x * matrix.GetForward().y - vecNormalized.y * matrix.GetForward().x) * fMaxY;
        fMult3 = (vecNormalized.x * matrix.GetUp().x + vecNormalized.y * matrix.GetUp().y) * fMaxZ;
        fMult4 = (vecNormalized.x * matrix.GetUp().y - vecNormalized.y * matrix.GetUp().x) * fMaxZ;
    }
    else if (fYSize > fZSize) {
        vecDir = matrix.GetForward();
        vecDir.z = 0.0F;

        vecNormalized = vecDir;
        vecNormalized.Normalise();

        auto vecScaled = vecDir * fMaxY;
        vecTransformed = vecScaled + GetPosition();

        auto vecTemp = GetPosition() - vecScaled;
        vecDir = vecTemp;

        fMult1 = (vecNormalized.x * matrix.GetRight().x + vecNormalized.y * matrix.GetRight().y) * fMaxX;
        fMult2 = (vecNormalized.x * matrix.GetRight().y - vecNormalized.y * matrix.GetRight().x) * fMaxX;
        fMult3 = (vecNormalized.x * matrix.GetUp().x + vecNormalized.y * matrix.GetUp().y) * fMaxZ;
        fMult4 = (vecNormalized.x * matrix.GetUp().y - vecNormalized.y * matrix.GetUp().x) * fMaxZ;
    }
    else {
        vecDir = matrix.GetUp();
        vecDir.z = 0.0F;

        vecNormalized = vecDir;
        vecNormalized.Normalise();

        auto vecScaled = vecDir * fMaxZ;
        vecTransformed = vecScaled + GetPosition();

        auto vecTemp = GetPosition() - vecScaled;
        vecDir = vecTemp;

        fMult1 = (vecNormalized.x * matrix.GetRight().x + vecNormalized.y * matrix.GetRight().y) * fMaxX;
        fMult2 = (vecNormalized.x * matrix.GetRight().y - vecNormalized.y * matrix.GetRight().x) * fMaxX;
        fMult3 = (vecNormalized.x * matrix.GetForward().x + vecNormalized.y * matrix.GetForward().y) * fMaxY;
        fMult4 = (vecNormalized.x * matrix.GetForward().y - vecNormalized.y * matrix.GetForward().x) * fMaxY;
    }

    auto fNegX = -vecNormalized.x;
    fMult1 = fabs(fMult1);
    fMult2 = fabs(fMult2);
    fMult3 = fabs(fMult3);
    fMult4 = fabs(fMult4);

    auto fMult13 = fMult1 + fMult3;
    auto fMult24 = fMult2 + fMult4;

    CVector vecCorner1;
    vecCorner1.x = vecTransformed.x + (vecNormalized.x * fMult13) - (vecNormalized.y * fMult24);
    vecCorner1.y = vecTransformed.y + (vecNormalized.y * fMult13) - (-vecNormalized.x * fMult24);
    vecCorner1.z = vecTransformed.z + (vecNormalized.z * fMult13) - (vecNormalized.z * fMult24);
    *pVecCorner1 = vecCorner1;

    CVector vecCorner2;
    vecCorner2.x = vecTransformed.x + (vecNormalized.x * fMult13) + (vecNormalized.y * fMult24);
    vecCorner2.y = vecTransformed.y + (vecNormalized.y * fMult13) + (-vecNormalized.x * fMult24);
    vecCorner2.z = vecTransformed.z + (vecNormalized.z * fMult13) + (vecNormalized.z * fMult24);
    *pVecCorner2 = vecCorner2;

    CVector vecCorner3;
    vecCorner3.x = vecDir.x - (vecNormalized.x * fMult13) + (vecNormalized.y * fMult24);
    vecCorner3.y = vecDir.y - (vecNormalized.y * fMult13) + (-vecNormalized.x * fMult24);
    vecCorner3.z = vecDir.z - (vecNormalized.z * fMult13) + (vecNormalized.z * fMult24);
    *pVecCorner3 = vecCorner3;

    CVector vecCorner4;
    vecCorner4.x = vecDir.x - (vecNormalized.x * fMult13) - (vecNormalized.y * fMult24);
    vecCorner4.y = vecDir.y - (vecNormalized.y * fMult13) - (-vecNormalized.x * fMult24);
    vecCorner4.z = vecDir.z - (vecNormalized.z * fMult13) - (vecNormalized.z * fMult24);
    *pVecCorner4 = vecCorner4;

    const auto& vecPos = GetPosition();
    pVecCorner1->z = vecPos.z;
    pVecCorner2->z = vecPos.z;
    pVecCorner3->z = vecPos.z;
    pVecCorner4->z = vecPos.z;

}

// 0x535F00
void CEntity::UpdateAnim()
{
    m_bDontUpdateHierarchy = false;
    if (!m_pRwObject || RwObjectGetType(m_pRwObject) != rpCLUMP)
        return;

    if (!RpAnimBlendClumpGetFirstAssociation(m_pRwClump))
        return;


    bool bOnScreen;
    float fStep;
    if (IsObject() && static_cast<CObject*>(this)->m_nObjectType == eObjectType::OBJECT_TYPE_CUTSCENE) {
        bOnScreen = true;
        fStep = CTimer::ms_fTimeStepNonClipped / 50.0F;
    }
    else {
        if (!m_bOffscreen)
            m_bOffscreen = !CEntity::GetIsOnScreen();

        bOnScreen = !m_bOffscreen;
        fStep = CTimer::ms_fTimeStep / 50.0F;
    }

    RpAnimBlendClumpUpdateAnimations(m_pRwClump, fStep, bOnScreen);
}

// 0x536BC0
bool CEntity::IsVisible()
{
    if (!m_pRwObject || !m_bIsVisible)
        return false;

    return CEntity::GetIsOnScreen();
}

// 0x536BE0
float CEntity::GetDistanceFromCentreOfMassToBaseOfModel()
{
    auto pColModel = CEntity::GetColModel();
    return -pColModel->m_boundBox.m_vecMin.z;
}

// 0x571A00
void CEntity::CleanUpOldReference(CEntity** entity)
{
    if (!m_pReferences)
        return;

    auto pRef = m_pReferences;
    auto ppPrev = &m_pReferences;
    while (pRef->m_ppEntity != entity) {
        ppPrev = &pRef->m_pNext;
        pRef = pRef->m_pNext;
        if (!pRef)
            return;
    }

    *ppPrev = pRef->m_pNext;
    pRef->m_pNext = CReferences::pEmptyList;
    pRef->m_ppEntity = nullptr;
    CReferences::pEmptyList = pRef;
}

// 0x571A40
void CEntity::ResolveReferences()
{
    auto pRef = m_pReferences;
    while (pRef) {
        if (*pRef->m_ppEntity == this)
            *pRef->m_ppEntity = nullptr;

        pRef = pRef->m_pNext;
    }

    pRef = m_pReferences;
    if (!pRef)
        return;

    pRef->m_ppEntity = nullptr;
    while (pRef->m_pNext)
        pRef = pRef->m_pNext;

    pRef->m_pNext = CReferences::pEmptyList;
    CReferences::pEmptyList = m_pReferences;
    m_pReferences = nullptr;
}

// 0x571A90
void CEntity::PruneReferences()
{
    if (!m_pReferences)
        return;

    auto pRef = m_pReferences;
    auto ppPrev = &m_pReferences;
    while (pRef) {
        if (*pRef->m_ppEntity == this) {
            ppPrev = &pRef->m_pNext;
            pRef = pRef->m_pNext;
        }
        else {
            auto pRefTemp = pRef->m_pNext;
            *ppPrev = pRef->m_pNext;
            pRef->m_pNext = CReferences::pEmptyList;
            CReferences::pEmptyList = pRef;
            pRef->m_ppEntity = nullptr;
            pRef = pRefTemp;
        }
    }
}

// 0x571B70
void CEntity::RegisterReference(CEntity** entity)
{
    if (IsBuilding() && !m_bIsTempBuilding && !m_bIsProcObject && !m_nIplIndex)
        return;

    auto pRef = m_pReferences;
    while (pRef) {
        if (pRef->m_ppEntity == entity) {
            return;
        }
        pRef = pRef->m_pNext;
    }

    if (!m_pReferences && !CReferences::pEmptyList) {
        auto iPedsSize = CPools::ms_pPedPool->GetSize();
        for (int32 i = 0; i < iPedsSize; ++i) {
            auto pPed = CPools::ms_pPedPool->GetAt(i);
            if (pPed) {
                pPed->PruneReferences();
                if (CReferences::pEmptyList)
                    break;
            }

        }

        if (!CReferences::pEmptyList) {
            auto iVehsSize = CPools::ms_pVehiclePool->GetSize();
            for (int32 i = 0; i < iVehsSize; ++i) {
                auto pVeh = CPools::ms_pVehiclePool->GetAt(i);
                if (pVeh) {
                    pVeh->PruneReferences();
                    if (CReferences::pEmptyList)
                        break;
                }

            }
        }

        if (!CReferences::pEmptyList) {
            auto iObjectsSize = CPools::ms_pObjectPool->GetSize();
            for (int32 i = 0; i < iObjectsSize; ++i) {
                auto pObj = CPools::ms_pObjectPool->GetAt(i);
                if (pObj) {
                    pObj->PruneReferences();
                    if (CReferences::pEmptyList)
                        break;
                }
            }
        }
    }

    if (CReferences::pEmptyList) {
        auto pEmptyRef = CReferences::pEmptyList;
        CReferences::pEmptyList = pEmptyRef->m_pNext;
        pEmptyRef->m_pNext = m_pReferences;
        m_pReferences = pEmptyRef;
        pEmptyRef->m_ppEntity = entity;
    }
}

// 0x6FC7A0
void CEntity::ProcessLightsForEntity()
{
    auto fBalance = GetDayNightBalance();
    if (m_bRenderDamaged || !m_bIsVisible)
        return;

    if (IsVehicle()) {
        if (static_cast<CVehicle*>(this)->physicalFlags.bDestroyed)
            return;
    }
    else {
        if (m_matrix && m_matrix->GetUp().z < 0.96F)
            return;
    }

    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (!pModelInfo->m_n2dfxCount)
        return;

    for (int32 iFxInd = 0; iFxInd < pModelInfo->m_n2dfxCount; ++iFxInd) {
        auto pEffect = pModelInfo->Get2dEffect(iFxInd);
        auto fIntensity = 1.0F;
        auto uiRand = m_nRandomSeed ^ CCoronas::ms_aEntityLightsOffsets[iFxInd & 0x7];

        if (pEffect->m_nType == e2dEffectType::EFFECT_SUN_GLARE && CWeather::SunGlare >= 0.0F) {
            auto vecEffPos = CEntity::TransformFromObjectSpace(pEffect->m_vecPosn);

            auto vecDir = vecEffPos - GetPosition();
            vecDir.Normalise();

            auto vecCamDir = TheCamera.GetPosition() - vecEffPos;
            auto fCamDist = vecCamDir.Magnitude();
            auto fScale = 2.0F / fCamDist;
            auto vecScaledCam = (vecCamDir * fScale);
            vecDir += vecScaledCam;
            vecDir.Normalise();

            auto fDot = -DotProduct(vecDir, CTimeCycle::m_VectorToSun[CTimeCycle::m_CurrentStoredValue]);
            if (fDot <= 0.0F)
                continue;

            auto fGlare = sqrt(fDot) * CWeather::SunGlare;
            auto fRadius = sqrt(fCamDist) * CWeather::SunGlare * 0.5F;
            vecEffPos += vecScaledCam;

            auto ucRed = static_cast<uint8>((CTimeCycle::m_CurrentColours.m_nSunCoreRed + 510) * fGlare / 3.0F);
            auto ucGreen = static_cast<uint8>((CTimeCycle::m_CurrentColours.m_nSunCoreGreen + 510) * fGlare / 3.0F);
            auto ucBlue = static_cast<uint8>((CTimeCycle::m_CurrentColours.m_nSunCoreBlue + 510) * fGlare / 3.0F);
            CCoronas::RegisterCorona(m_nRandomSeed + iFxInd + 1,
                                     nullptr,
                                     ucRed,
                                     ucGreen,
                                     ucBlue,
                                     255,
                                     vecEffPos,
                                     fRadius,
                                     120.0F,
                                     gpCoronaTexture[0],
                                     eCoronaFlareType::FLARETYPE_NONE,
                                     false,
                                     false,
                                     0,
                                     0.0F,
                                     false,
                                     1.5F,
                                     0,
                                     15.0F,
                                     false,
                                     false);

            continue;
        }

        if (pEffect->m_nType != e2dEffectType::EFFECT_LIGHT)
            continue;

        auto vecEffPos = CEntity::TransformFromObjectSpace(pEffect->m_vecPosn);
        auto bDoColorLight = false;
        auto bDoNoColorLight = false;
        auto bCoronaVisible = false;
        bool bUpdateCoronaCoors = false;
        auto fDayNight = 1.0F;
        if (pEffect->light.m_bAtDay && pEffect->light.m_bAtNight) {
            bCoronaVisible = true;
        }
        else if (pEffect->light.m_bAtDay && fBalance < 1.0F) {
            bCoronaVisible = true;
            fDayNight = 1.0F - fBalance;
        }
        else if (pEffect->light.m_bAtNight && fBalance > 0.0F) {
            bCoronaVisible = true;
            fDayNight = fBalance;
        }

        const auto& vecPos = GetPosition();
        auto iFlashType = pEffect->light.m_nCoronaFlashType;
        float fBalance;
        uint32 uiMode, uiOffset;
        if (iFlashType == e2dCoronaFlashType::FLASH_RANDOM_WHEN_WET && CWeather::WetRoads > 0.5F || bCoronaVisible) {
            switch (iFlashType) {
            case e2dCoronaFlashType::FLASH_DEFAULT:
                bDoColorLight = true;
                break;

            case e2dCoronaFlashType::FLASH_RANDOM:
            case e2dCoronaFlashType::FLASH_RANDOM_WHEN_WET:
                if ((CTimer::m_snTimeInMilliseconds ^ uiRand) & 0x60)
                    bDoColorLight = true;
                else
                    bDoNoColorLight = true;

                if ((uiRand ^ (CTimer::m_snTimeInMilliseconds / 4096)) & 0x3)
                    bDoColorLight = true;

                break;

            case e2dCoronaFlashType::FLASH_ANIM_SPEED_4X:
                if (((CTimer::m_snTimeInMilliseconds + iFxInd * 256) & 0x200) == 0)
                    bUpdateCoronaCoors = true;
                else
                    bDoColorLight = true;

                break;

            case e2dCoronaFlashType::FLASH_ANIM_SPEED_2X:
                if (((CTimer::m_snTimeInMilliseconds + iFxInd * 512) & 0x400) == 0)
                    bUpdateCoronaCoors = true;
                else
                    bDoColorLight = true;

                break;

            case e2dCoronaFlashType::FLASH_ANIM_SPEED_1X:
                if (((CTimer::m_snTimeInMilliseconds + iFxInd * 1024) & 0x800) == 0)
                    bUpdateCoronaCoors = true;
                else
                    bDoColorLight = true;

                break;

            case e2dCoronaFlashType::FLASH_UNKN:
                if (static_cast<uint8>(uiRand) > 0x10) {
                    bDoColorLight = true;
                    break;
                }

                if ((CTimer::m_snTimeInMilliseconds ^ (uiRand * 8)) & 0x60)
                    bDoColorLight = true;
                else
                    bDoNoColorLight = true;

                if ((uiRand ^ (CTimer::m_snTimeInMilliseconds / 4096)) & 0x3)
                    bDoColorLight = true;

                break;

            case e2dCoronaFlashType::FLASH_TRAINCROSSING:
                if (IsObject() && static_cast<CObject*>(this)->objectFlags.bTrainCrossEnabled) {
                    if (CTimer::m_snTimeInMilliseconds & 0x400)
                        bDoColorLight = true;

                    if (iFxInd & 1)
                        bDoColorLight = !bDoColorLight;
                }

                if (iFxInd >= 4)
                    bDoColorLight = false;

                break;

            case e2dCoronaFlashType::FLASH_UNUSED:
                if (CBridge::ShouldLightsBeFlashing() && (CTimer::m_snTimeInMilliseconds & 0x1FF) < 0x3C)
                    bDoColorLight = true;

                break;

            case e2dCoronaFlashType::FLASH_ONLY_RAIN:
                if (CWeather::Rain > 0.0001F) {
                    fIntensity = CWeather::Rain;
                    bDoColorLight = true;
                }
                break;

            case e2dCoronaFlashType::FLASH_5ON_5OFF:
            case e2dCoronaFlashType::FLASH_6ON_4OFF:
            case e2dCoronaFlashType::FLASH_4ON_6OFF:

                bDoColorLight = true;

                uiOffset = CTimer::m_snTimeInMilliseconds + 3333 * (iFlashType - 11);
                uiOffset += static_cast<uint32>(vecPos.x * 20.0F);
                uiOffset += static_cast<uint32>(vecPos.y * 10.0F);

                uiMode = 9 * ((uiOffset % 10000) / 10000);
                fBalance = ((uiOffset % 10000) - (1111 * uiMode)) * 0.0009F;
                switch (uiMode) {
                case 0:
                    fIntensity = fBalance;
                    break;
                case 1:
                case 2:
                    fIntensity = 1.0F;
                    break;
                case 3:
                    fIntensity = 1.0F - fBalance;
                    break;
                default:
                    bDoColorLight = false;
                }

                break;

            default:
                break;
            }
        }

// CORONAS
        auto bSkipCoronaChecks = false;
        if (CGameLogic::LaRiotsActiveHere()) {
            bool bLightsOn = bDoColorLight;
            bLightsOn &= !IsVehicle();
            bLightsOn &= ((uiRand & 3) == 0 || (uiRand & 3) == 1 && (CTimer::m_snTimeInMilliseconds ^ (uiRand * 8)) & 0x60);

            if (bLightsOn) {
                bDoColorLight = false;
                bDoNoColorLight = true;
                bSkipCoronaChecks = true;

                CCoronas::RegisterCorona(reinterpret_cast<uint32>(this) + iFxInd,
                                         nullptr,
                                         0,
                                         0,
                                         0,
                                         255,
                                         vecEffPos,
                                         pEffect->light.m_fCoronaSize,
                                         pEffect->light.m_fCoronaFarClip,
                                         pEffect->light.m_pCoronaTex,
                                         static_cast<eCoronaFlareType>(pEffect->light.m_nCoronaFlareType),
                                         pEffect->light.m_bCoronaEnableReflection,
                                         pEffect->light.m_bCheckObstacles,
                                         0,
                                         0.0F,
                                         pEffect->light.m_bOnlyLongDistance,
                                         1.5F,
                                         0,
                                         15.0F,
                                         false,
                                         false);
            }
        }

        if (!bSkipCoronaChecks && bDoColorLight) {
            auto bCanCreateLight = true;
            if (pEffect->light.m_bCheckDirection) {
                const auto& camPos = TheCamera.GetPosition();
                CVector lightOffset{static_cast<float>(pEffect->light.offsetX),
                                    static_cast<float>(pEffect->light.offsetY),
                                    static_cast<float>(pEffect->light.offsetZ)};
                auto vecLightPos = Multiply3x3(GetMatrix(), lightOffset);

                auto fDot = DotProduct(vecLightPos, (camPos - vecEffPos));
                bCanCreateLight = fDot >= 0.0F;
            }

            if (bCanCreateLight) {
                bSkipCoronaChecks = true;
                auto fBrightness = fIntensity;
                if (pEffect->light.m_bBlinking1)
                    fBrightness = (1.0F - (rand() % 32) * 0.012F) * fIntensity;

                if (pEffect->light.m_bBlinking2 && (CTimer::m_FrameCounter + uiRand) & 3)
                    fBrightness = 0.0F;

                if (pEffect->light.m_bBlinking3 && (CTimer::m_FrameCounter + uiRand) & 0x3F) {
                    if (((CTimer::m_FrameCounter + uiRand) & 0x3F) == 1)
                        fBrightness *= 0.5F;
                    else
                        fBrightness = 0.0F;
                }

                auto fSizeMult = 1.0F;
                if (m_nModelIndex == eModelID::MODEL_RCBARON) {
                    fBrightness *= 1.9F;
                    fSizeMult = 2.0F;
                }

                fIntensity = CTimeCycle::m_CurrentColours.m_fSpriteBrightness * fBrightness * 0.1F;
                auto fSize = pEffect->light.m_fCoronaSize * fSizeMult;

                auto ucRed = static_cast<uint8>(static_cast<float>(pEffect->light.m_color.red) * fIntensity);
                auto ucGreen = static_cast<uint8>(static_cast<float>(pEffect->light.m_color.green) * fIntensity);
                auto ucBlue = static_cast<uint8>(static_cast<float>(pEffect->light.m_color.blue) * fIntensity);

                CCoronas::RegisterCorona(reinterpret_cast<uint32>(this) + iFxInd,
                                         nullptr,
                                         ucRed,
                                         ucGreen,
                                         ucBlue,
                                         static_cast<uint8>(fDayNight * 255.0F),
                                         vecEffPos,
                                         fSize,
                                         pEffect->light.m_fCoronaFarClip,
                                         pEffect->light.m_pCoronaTex,
                                         static_cast<eCoronaFlareType>(pEffect->light.m_nCoronaFlareType),
                                         pEffect->light.m_bCoronaEnableReflection,
                                         pEffect->light.m_bCheckObstacles,
                                         0,
                                         0.0F,
                                         pEffect->light.m_bOnlyLongDistance,
                                         0.8F,
                                         0,
                                         15.0F,
                                         pEffect->light.m_bOnlyFromBelow,
                                         pEffect->light.m_bUpdateHeightAboveGround);

            }
            else {
                bDoColorLight = false;
                bUpdateCoronaCoors = true;
            }
        }

        if (!bSkipCoronaChecks && bDoNoColorLight) {
            bSkipCoronaChecks = true;
            CCoronas::RegisterCorona(reinterpret_cast<uint32>(this) + iFxInd,
                                        nullptr,
                                        0,
                                        0,
                                        0,
                                        255,
                                        vecEffPos,
                                        pEffect->light.m_fCoronaSize,
                                        pEffect->light.m_fCoronaFarClip,
                                        pEffect->light.m_pCoronaTex,
                                        static_cast<eCoronaFlareType>(pEffect->light.m_nCoronaFlareType),
                                        pEffect->light.m_bCoronaEnableReflection,
                                        pEffect->light.m_bCheckObstacles,
                                        0,
                                        0.0F,
                                        pEffect->light.m_bOnlyLongDistance,
                                        1.5F,
                                        0,
                                        15.0F,
                                        false,
                                        false);
        }

        if (!bSkipCoronaChecks && bUpdateCoronaCoors) {
            CCoronas::UpdateCoronaCoors(reinterpret_cast<uint32>(this) + iFxInd, vecEffPos, pEffect->light.m_fCoronaFarClip, 0.0F);
        }

// POINT LIGHTS
        bool bSkipLights = false;
        if (pEffect->light.m_fPointlightRange != 0.0F && bDoColorLight) {
            auto color = pEffect->light.m_color;
            if (color.red || color.green || color.blue) {
                auto fColorMult = fDayNight * fIntensity / 256.0F;

                bSkipLights = true;
                CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT,
                                       vecEffPos,
                                       CVector(0.0F, 0.0F, 0.0F),
                                       pEffect->light.m_fPointlightRange,
                                       static_cast<float>(color.red) * fColorMult,
                                       static_cast<float>(color.green) * fColorMult,
                                       static_cast<float>(color.blue) * fColorMult,
                                       pEffect->light.m_nFogType,
                                       true,
                                       nullptr);
            }
            else {
                CPointLights::AddLight(ePointLightType::PLTYPE_DARKLIGHT,
                                       vecEffPos,
                                       CVector(0.0F, 0.0F, 0.0F),
                                       pEffect->light.m_fPointlightRange,
                                       0.0F,
                                       0.0F,
                                       0.0F,
                                       RwFogType::rwFOGTYPENAFOGTYPE,
                                       true,
                                       nullptr);
            }
        }

        if (!bSkipLights) {
            if (pEffect->light.m_nFogType & RwFogType::rwFOGTYPEEXPONENTIAL) {
                auto color = pEffect->light.m_color;
                CPointLights::AddLight((ePointLightType)3u, //Enum doesn't contain all types?
                                        vecEffPos,
                                        CVector(0.0F, 0.0F, 0.0F),
                                        0.0F,
                                        color.red / 256.0F,
                                        color.green / 256.0F,
                                        color.blue / 256.0F,
                                        RwFogType::rwFOGTYPEEXPONENTIAL,
                                        true,
                                        nullptr);
            }
            else if (pEffect->light.m_nFogType & RwFogType::rwFOGTYPELINEAR && bDoColorLight && pEffect->light.m_fPointlightRange == 0.0F) {
                auto color = pEffect->light.m_color;
                CPointLights::AddLight((ePointLightType)4u, //Enum doesn't contain all types?
                                        vecEffPos,
                                        CVector(0.0F, 0.0F, 0.0F),
                                        0.0F,
                                        color.red / 256.0F,
                                        color.green / 256.0F,
                                        color.blue / 256.0F,
                                        RwFogType::rwFOGTYPELINEAR,
                                        true,
                                        nullptr);
            }
        }

// SHADOWS
        if (pEffect->light.m_fShadowSize != 0.0F) {
            auto fShadowZ = 15.0F;
            if (pEffect->light.m_nShadowZDistance)
                fShadowZ = static_cast<float>(pEffect->light.m_nShadowZDistance);

            if (bDoColorLight) {
                auto color = pEffect->light.m_color;
                auto fColorMult = pEffect->light.m_nShadowColorMultiplier * fIntensity / 256.0F;
                color.red    = static_cast<uint8>(static_cast<float>(color.red) * fColorMult);
                color.green  = static_cast<uint8>(static_cast<float>(color.green) * fColorMult);
                color.blue   = static_cast<uint8>(static_cast<float>(color.blue) * fColorMult);

                CShadows::StoreStaticShadow(reinterpret_cast<uint32>(this) + iFxInd,
                                            eShadowType::SHADOW_ADDITIVE,
                                            pEffect->light.m_pShadowTex,
                                            &vecEffPos,
                                            pEffect->light.m_fShadowSize,
                                            0.0F,
                                            0.0F,
                                            -pEffect->light.m_fShadowSize,
                                            128,
                                            color.red,
                                            color.green,
                                            color.blue,
                                            fShadowZ,
                                            1.0F,
                                            40.0F,
                                            false,
                                            0.0F);
            }
            else if (bDoNoColorLight) {
                CShadows::StoreStaticShadow(reinterpret_cast<uint32>(this) + iFxInd,
                                            eShadowType::SHADOW_ADDITIVE,
                                            pEffect->light.m_pShadowTex,
                                            &vecEffPos,
                                            pEffect->light.m_fShadowSize,
                                            0.0F,
                                            0.0F,
                                            -pEffect->light.m_fShadowSize,
                                            0,
                                            0,
                                            0,
                                            0,
                                            fShadowZ,
                                            1.0F,
                                            40.0F,
                                            false,
                                            0.0F);
            }
        }

    }
}

// 0x717900
void CEntity::RemoveEscalatorsForEntity()
{
    for (auto& pEscalator : CEscalators::aEscalators) {
        if (!pEscalator.m_bExist)
            continue;

        if (pEscalator.m_pEntity != this)
            continue;

        pEscalator.SwitchOff();
        pEscalator.m_bExist = false;
    }
}

// 0x71FAE0
bool CEntity::IsEntityOccluded()
{
    CVector vecCenter;
    CEntity::GetBoundCentre(vecCenter);

    CVector vecScreenPos;
    float fScreenX, fScreenY;
    if (!COcclusion::NumActiveOccluders || !CalcScreenCoors(vecCenter, &vecScreenPos, &fScreenX, &fScreenY))
        return false;

    auto pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    auto fLongEdge = std::max(fScreenX, fScreenY);
    auto fBoundRadius = pModelInfo->GetColModel()->GetBoundRadius();
    auto fUsedRadius = fBoundRadius * fLongEdge * 0.9F;
    if (COcclusion::NumActiveOccluders <= 0)
        return false;

    for (int32 iOccInd = 0; iOccInd < COcclusion::NumActiveOccluders; ++iOccInd) {
        auto& pActiveOccluder = COcclusion::aActiveOccluders[iOccInd];
        auto fDepth = vecScreenPos.z - fBoundRadius;
        if (static_cast<float>(pActiveOccluder.m_wDepth) >= fDepth)
            continue;

        if (pActiveOccluder.IsPointWithinOcclusionArea(vecScreenPos.x, vecScreenPos.y, fUsedRadius)) {
            if (pActiveOccluder.IsPointBehindOccluder(vecCenter, fBoundRadius)) {
                return true;
            }
        }

        if (pActiveOccluder.IsPointWithinOcclusionArea(vecScreenPos.x, vecScreenPos.y, 0.0F)) {
            auto bInView = false;
            const auto& pBounding = pModelInfo->GetColModel()->GetBoundingBox();
            CVector vecScreen;

            auto vecMin = CEntity::GetMatrix() * pBounding.m_vecMin;
            if (!CalcScreenCoors(vecMin, &vecScreen)
                || !pActiveOccluder.IsPointWithinOcclusionArea(vecScreen.x, vecScreen.y, 0.0F)
                || !pActiveOccluder.IsPointBehindOccluder(vecMin, 0.0F)) {

                bInView = true;
            }

            auto vecMax = CEntity::GetMatrix() * pBounding.m_vecMax;
            if (bInView
                || !CalcScreenCoors(vecMax, &vecScreen)
                || !pActiveOccluder.IsPointWithinOcclusionArea(vecScreen.x, vecScreen.y, 0.0F)
                || !pActiveOccluder.IsPointBehindOccluder(vecMax, 0.0F)) {

                bInView = true;
            }

            auto vecDiag1 = CEntity::GetMatrix() * CVector(pBounding.m_vecMin.x, pBounding.m_vecMax.y, pBounding.m_vecMax.z);
            if (bInView
                || !CalcScreenCoors(vecDiag1, &vecScreen)
                || !pActiveOccluder.IsPointWithinOcclusionArea(vecScreen.x, vecScreen.y, 0.0F)
                || !pActiveOccluder.IsPointBehindOccluder(vecDiag1, 0.0F)) {

                bInView = true;
            }

            auto vecDiag2 = CEntity::GetMatrix() * CVector(pBounding.m_vecMax.x, pBounding.m_vecMin.y, pBounding.m_vecMin.z);
            if (!bInView
                && CalcScreenCoors(vecDiag2, &vecScreen)
                && pActiveOccluder.IsPointWithinOcclusionArea(vecScreen.x, vecScreen.y, 0.0F)
                && pActiveOccluder.IsPointBehindOccluder(vecDiag2, 0.0F)) {

                if (pBounding.m_vecMax.x - pBounding.m_vecMin.x <= 60.0F)
                    return true;

                if (pBounding.m_vecMax.y - pBounding.m_vecMin.y <= 60.0F)
                    return true;

                if (pBounding.m_vecMax.z - pBounding.m_vecMin.z <= 30.0F)
                    return true;

                auto vecDiag3 = CEntity::GetMatrix() * CVector(pBounding.m_vecMin.x, pBounding.m_vecMin.y, pBounding.m_vecMax.z);
                if (!CalcScreenCoors(vecDiag3, &vecScreen)
                    || !pActiveOccluder.IsPointWithinOcclusionArea(vecScreen.x, vecScreen.y, 0.0F)
                    || !pActiveOccluder.IsPointBehindOccluder(vecDiag3, 0.0F)) {

                    bInView = true;
                }

                auto vecDiag4 = CEntity::GetMatrix() * CVector(pBounding.m_vecMax.x, pBounding.m_vecMin.y, pBounding.m_vecMax.z);
                if (!bInView
                    && CalcScreenCoors(vecDiag4, &vecScreen)
                    && pActiveOccluder.IsPointWithinOcclusionArea(vecScreen.x, vecScreen.y, 0.0F)
                    && pActiveOccluder.IsPointBehindOccluder(vecDiag4, 0.0F)) {

                    return true;
                }
            }
        }
    }

    return false;
}

bool CEntity::IsCurrentAreaOrBarberShopInterior()
{
    return m_nAreaCode == CGame::currArea || m_nAreaCode == AREA_CODE_13;
}

void CEntity::UpdateRW() {
    if (!m_pRwObject)
        return;

    auto pRwMatrix = CEntity::GetModellingMatrix();
    if (m_matrix)
        m_matrix->UpdateRwMatrix(pRwMatrix);
    else
        m_placement.UpdateRwMatrix(pRwMatrix);
}

RpAtomic* CEntity::SetAtomicAlphaCB(RpAtomic* pAtomic, void* pData)
{
    auto pGeometry = RpAtomicGetGeometry(pAtomic);
    RpGeometrySetFlags(pGeometry, rpGEOMETRYMODULATEMATERIALCOLOR);
    RpGeometryForAllMaterials(pGeometry, CEntity::SetMaterialAlphaCB, pData);
    return pAtomic;
}

RpMaterial* CEntity::SetMaterialAlphaCB(RpMaterial* pMaterial, void* pData)
{
    pMaterial->color.alpha = (RwUInt8)pData;
    return pMaterial;
}
