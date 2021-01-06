#include "StdInc.h"

tTagDesc(&CTagManager::ms_tagDesc)[MAX_TAGS] = *(tTagDesc(*)[MAX_TAGS])0xA9A8C0;
int& CTagManager::ms_numTags = *(int*)0xA9AD70;
int& CTagManager::ms_numTagged = *(int*)0xA9AD74;
RxPipeline* &CTagManager::ms_pPipeline = *(RxPipeline**)0xA9AD78;

void CTagManager::InjectHooks()
{
    ReversibleHooks::Install("CTagManager", "Init", 0x49CC50, &CTagManager::Init);
    ReversibleHooks::Install("CTagManager", "ShutdownForRestart", 0x49CC60, &CTagManager::ShutdownForRestart);
    ReversibleHooks::Install("CTagManager", "GetTagPos", 0x49CEA0, &CTagManager::GetTagPos);
    ReversibleHooks::Install("CTagManager", "AddTag", 0x49CC90, &CTagManager::AddTag);
    ReversibleHooks::Install("CTagManager", "FindTagDesc", 0x49CCB0, &CTagManager::FindTagDesc);
    ReversibleHooks::Install("CTagManager", "IsTag", 0x49CCE0, &CTagManager::IsTag);
    ReversibleHooks::Install("CTagManager", "SetAlpha_RpAtomic", 0x49CD30, (void(*)(RpAtomic*, unsigned char))(&CTagManager::SetAlpha));
    ReversibleHooks::Install("CTagManager", "GetAlpha_RpAtomic", 0x49CD40, (unsigned char(*)(RpAtomic*))(&CTagManager::GetAlpha));
    ReversibleHooks::Install("CTagManager", "GetAlpha_Entity", 0x49CF90, (unsigned char(*)(CEntity*))(&CTagManager::GetAlpha));
    ReversibleHooks::Install("CTagManager", "GetPercentageTagged", 0x49CDA0, &CTagManager::GetPercentageTagged);
    ReversibleHooks::Install("CTagManager", "GetPercentageTaggedInArea", 0x49D0B0, &CTagManager::GetPercentageTaggedInArea);
    ReversibleHooks::Install("CTagManager", "UpdateNumTagged", 0x49CDE0, &CTagManager::UpdateNumTagged);
    ReversibleHooks::Install("CTagManager", "SetAlphaInArea", 0x49CFE0, &CTagManager::SetAlphaInArea);
    ReversibleHooks::Install("CTagManager", "SetAlpha_Entity", 0x49CEC0, (void(*)(CEntity*, unsigned char))(&CTagManager::SetAlpha));
    ReversibleHooks::Install("CTagManager", "GetNearestTag", 0x49D160, &CTagManager::GetNearestTag);
    ReversibleHooks::Install("CTagManager", "SetupAtomic", 0x49CE10, &CTagManager::SetupAtomic);
    ReversibleHooks::Install("CTagManager", "RenderTagForPC", 0x49CE40, &CTagManager::RenderTagForPC);
    ReversibleHooks::Install("CTagManager", "Save", 0x5D3D60, &CTagManager::Save);
    ReversibleHooks::Install("CTagManager", "Load", 0x5D3DA0, &CTagManager::Load);
}

void CTagManager::Init()
{
    CTagManager::ms_numTags = 0;
    CTagManager::ms_numTagged = 0;
}

void CTagManager::ShutdownForRestart()
{
    for (int32_t i = CTagManager::ms_numTags; i > 0; --i)
        CTagManager::ms_tagDesc[i].m_nAlpha = 0;

    CTagManager::ms_numTagged = 0;
}

CVector& CTagManager::GetTagPos(int iTag)
{
    return CTagManager::ms_tagDesc[iTag].m_pEntity->GetPosition();
}

void CTagManager::AddTag(CEntity* pEntity)
{
    auto& pTag = CTagManager::ms_tagDesc[CTagManager::ms_numTags];
    pTag.m_pEntity = pEntity;
    pTag.m_nAlpha = 0;

    ++CTagManager::ms_numTags;
}

tTagDesc* CTagManager::FindTagDesc(CEntity* pEntity)
{
    if (!CTagManager::ms_numTags)
        return nullptr;

    for (int32_t i = CTagManager::ms_numTags - 1; i >= 0; --i) {
        auto pTagDesc = &CTagManager::ms_tagDesc[i];
        if (pTagDesc->m_pEntity == pEntity)
            return pTagDesc;
    }

    return nullptr;
}

bool CTagManager::IsTag(CEntity const* pEntity)
{
    auto pModelInfo = CModelInfo::GetModelInfo(pEntity->m_nModelIndex);
    if (pModelInfo->GetRwModelType() != rpATOMIC)
        return false;

    return pModelInfo->IsTagModel() && !pModelInfo->AsAtomicModelInfoPtr()->bTagDisabled;
}

void CTagManager::SetAlpha(RpAtomic* pAtomic, unsigned char ucAlpha)
{
    CVisibilityPlugins::SetUserValue(pAtomic, ucAlpha);
}

unsigned char CTagManager::GetAlpha(RpAtomic* pAtomic)
{
    return CVisibilityPlugins::GetUserValue(pAtomic);
}

unsigned char CTagManager::GetAlpha(CEntity* pEntity)
{
    if (pEntity->m_pRwAtomic)
        return CVisibilityPlugins::GetUserValue(pEntity->m_pRwAtomic);

    auto pTag = CTagManager::FindTagDesc(pEntity);
    assert(pTag); // Originally the function would access unitialized memory, by clearing EAX and dereferencing pointer to [EAX + 0x4] right after that

    return pTag->m_nAlpha;
}

void CTagManager::ResetAlpha(CEntity* pEntity)
{
    if (!pEntity->m_pRwAtomic)
        return;

    auto pTagDesc = CTagManager::FindTagDesc(pEntity);
    CTagManager::SetAlpha(pEntity->m_pRwAtomic, pTagDesc->m_nAlpha);
}

int64_t CTagManager::GetPercentageTagged()
{
    return static_cast<int64_t>(static_cast<double>(CTagManager::ms_numTagged) / static_cast<double>(CTagManager::ms_numTags) * 100.0F);
}

int64_t CTagManager::GetPercentageTaggedInArea(CRect* pArea)
{
    int iTotalTags = 0;
    int iTagged = 0;
    for (int32_t i = CTagManager::ms_numTags - 1; i >= 0; --i) {
        auto& pTagDesc = CTagManager::ms_tagDesc[i];
        auto vecPos = CVector2D(pTagDesc.m_pEntity->GetPosition());
        if (pArea->IsPointInside(vecPos)) {
            ++iTotalTags;
            if (pTagDesc.m_nAlpha > CTagManager::ALPHA_TAGGED)
                ++iTagged;
        }
    }

    return static_cast<int64_t>(static_cast<double>(iTagged) / static_cast<double>(iTotalTags) * 100.0F);
}

void CTagManager::UpdateNumTagged()
{
    CTagManager::ms_numTagged = 0;
    if (!CTagManager::ms_numTags)
        return;

    for (int32_t i = CTagManager::ms_numTags - 1; i >= 0; --i) {
        auto& pTagDesc = CTagManager::ms_tagDesc[i];
        if (pTagDesc.m_nAlpha > CTagManager::ALPHA_TAGGED)
            ++CTagManager::ms_numTagged;
    }
}

void CTagManager::SetAlphaInArea(CRect* pArea, unsigned char ucAlpha)
{
    for (int32_t i = CTagManager::ms_numTags - 1; i >= 0; --i) {
        auto& pTagDesc = CTagManager::ms_tagDesc[i];
        auto vecPos = CVector2D(pTagDesc.m_pEntity->GetPosition());
        if (pArea->IsPointInside(vecPos) && pTagDesc.m_pEntity->m_pRwAtomic) {
            CTagManager::SetAlpha(pTagDesc.m_pEntity->m_pRwAtomic, ucAlpha);
            pTagDesc.m_nAlpha = ucAlpha;
        }
    }

    CTagManager::UpdateNumTagged();
}

void CTagManager::SetAlpha(CEntity* pEntity, unsigned char ucAlpha)
{
    if (pEntity->m_pRwAtomic)
        CVisibilityPlugins::SetUserValue(pEntity->m_pRwAtomic, ucAlpha);

    auto pTag = CTagManager::FindTagDesc(pEntity);
    auto bChangedState = false;
    if (ucAlpha > CTagManager::ALPHA_TAGGED && pTag->m_nAlpha <= CTagManager::ALPHA_TAGGED)
        bChangedState = true;

    pTag->m_nAlpha = ucAlpha;
    CTagManager::UpdateNumTagged();

    if (bChangedState && !TheCamera.m_bWideScreenOn) {
        if (CTagManager::ms_numTagged == CTagManager::ms_numTags)
            CGarages::TriggerMessage("TAG_ALL", -1, 5000, -1);
        else
            CGarages::TriggerMessage("TAG_ONE", CTagManager::ms_numTagged, 5000, CTagManager::ms_numTags);
    }
}

CEntity* CTagManager::GetNearestTag(CVector const& vecPos)
{
    auto vecPosUsed = CVector2D(vecPos.x, vecPos.y);
    int32_t iClosestInd = -1;
    float fMinDist = RwRealMAXVAL;
    for (int32_t i = CTagManager::ms_numTags - 1; i >= 0; --i) {
        auto& pTagDesc = CTagManager::ms_tagDesc[i];
        auto vecTagPos = CVector2D(pTagDesc.m_pEntity->GetPosition());
        auto fDist = (vecPosUsed - vecTagPos).SquaredMagnitude();
        if (fDist < fMinDist) {
            fMinDist = fDist;
            iClosestInd = i;
        }
    }

    assert(iClosestInd != -1);
    return CTagManager::ms_tagDesc[iClosestInd].m_pEntity;
}

void CTagManager::SetupAtomic(RpAtomic* pAtomic)
{
    auto pGeo = RpAtomicGetGeometry(pAtomic);
    auto pRwMat = RpGeometryGetMaterial(pGeo, 1);
    pRwMat->pipeline = CTagManager::ms_pPipeline;

    auto dwFlags = RpGeometryGetFlags(pGeo);
    dwFlags |= rpGEOMETRYMODULATEMATERIALCOLOR;
    RpGeometrySetFlags(pGeo, dwFlags);

    CTagManager::SetAlpha(pAtomic, 0);
}

void CTagManager::RenderTagForPC(RpAtomic* pAtomic)
{
    auto pGeo = RpAtomicGetGeometry(pAtomic);
    auto pRwMat = RpGeometryGetMaterial(pGeo, 1);
    pRwMat->color.alpha = CTagManager::GetAlpha(pAtomic);
    RpAtomicRender(pAtomic);
}

void CTagManager::Save()
{
    CGenericGameStorage::SaveDataToWorkBuffer(&CTagManager::ms_numTags, 4);
    if (!CTagManager::ms_numTags)
        return;

    for (int32_t i = 0; i < CTagManager::ms_numTags; +i) {
        auto& pTagDesc = CTagManager::ms_tagDesc[i];
        CGenericGameStorage::SaveDataToWorkBuffer(&pTagDesc.m_nAlpha, 1);
    }
}

void CTagManager::Load()
{
    CGenericGameStorage::SaveDataToWorkBuffer(&CTagManager::ms_numTags, 4); // Yeah, original also saves into buffer instead of loading
    if (!CTagManager::ms_numTags)
        return;

    for (int32_t i = 0; i < CTagManager::ms_numTags; +i) {
        auto& pTagDesc = CTagManager::ms_tagDesc[i];
        CGenericGameStorage::LoadDataFromWorkBuffer(&pTagDesc.m_nAlpha, 1);
    }
}
