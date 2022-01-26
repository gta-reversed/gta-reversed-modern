#include "StdInc.h"

void CHandObject::InjectHooks()
{
    RH_ScopedClass(CHandObject);
    RH_ScopedCategory("Entity/Object");

// VIRTUAL
    RH_ScopedInstall(ProcessControl_Reversed, 0x59EC40);
    RH_ScopedInstall(PreRender_Reversed, 0x59ECD0);
    RH_ScopedInstall(Render_Reversed, 0x59EE80);
}

CHandObject::CHandObject(int32 handModelIndex, CPed* pPed, bool bLeftHand) : CObject()
{
    auto* pAnimHierarchy = GetAnimHierarchyFromSkinClump(pPed->m_pRwClump);
    m_pPed = pPed;
    pPed->UpdateRpHAnim();

    if (bLeftHand)
        m_nBoneIndex = RpHAnimIDGetIndex(pAnimHierarchy, ePedBones::BONE_L_FORE_ARM);
    else
        m_nBoneIndex = RpHAnimIDGetIndex(pAnimHierarchy, ePedBones::BONE_R_FORE_ARM);

    CEntity::SetModelIndex(handModelIndex);
    RpAnimBlendClumpInit(m_pRwClump);

    auto* pPedModelInfo = CModelInfo::GetModelInfo(pPed->m_nModelIndex);
    auto* pTxd = CTxdStore::ms_pTxdPool->GetAt(pPedModelInfo->m_nTxdIndex);
    m_pTexture = RwTexDictionaryFindHashNamedTexture(pTxd->m_pRwDictionary, pPedModelInfo->m_nKey);
    if (!m_pTexture)
        m_pTexture = GetFirstTexture(pTxd->m_pRwDictionary);

    m_nStatus = eEntityStatus::STATUS_SIMPLE;
    m_bUsesCollision = false;
    m_bLightObject = true;
    m_bStreamingDontDelete = true;
    m_nObjectType = eObjectType::OBJECT_TYPE_DECORATION;

    CObject::SetIsStatic(false);
    CModelInfo::GetModelInfo(handModelIndex)->m_nAlpha = 0xFF;
    m_bUpdatedMatricesArray = true;

}

void CHandObject::ProcessControl()
{
    CHandObject::ProcessControl_Reversed();
}
void CHandObject::ProcessControl_Reversed()
{
    auto* pAnimHierarchy = GetAnimHierarchyFromSkinClump(m_pPed->m_pRwClump);
    auto* pMatArr = RpHAnimHierarchyGetMatrixArray(pAnimHierarchy);
    const auto boneMat = CMatrix(&pMatArr[m_nBoneIndex], false);
    *static_cast<CMatrix*>(m_matrix) = boneMat;

    m_bIsInSafePosition = true;
    CPhysical::RemoveAndAdd();
}

void CHandObject::PreRender()
{
    CHandObject::PreRender_Reversed();
}
void CHandObject::PreRender_Reversed()
{
    auto* pAnimHierarchy = GetAnimHierarchyFromSkinClump(m_pPed->m_pRwClump);
    m_pPed->UpdateRpHAnim();
    m_pPed->m_bDontUpdateHierarchy = true;

    auto* pMatArr = RpHAnimHierarchyGetMatrixArray(pAnimHierarchy);
    const auto boneMat = CMatrix(&pMatArr[m_nBoneIndex], false);
    *static_cast<CMatrix*>(m_matrix) = boneMat;

    if (m_bUpdatedMatricesArray)
        m_bUpdatedMatricesArray = false;
    else
    {
        auto nBoneInd = m_nBoneIndex + 1;
        auto iStackCounter = 0;
        while (iStackCounter >= 0)
        {
            auto* pBoneMat = &pMatArr[nBoneInd];
            *RwMatrixGetAt(pBoneMat) = { 0.0F, 0.0F, 0.0F };
            *RwMatrixGetUp(pBoneMat) = { 0.0F, 0.0F, 0.0F };
            *RwMatrixGetRight(pBoneMat) = { 0.0F, 0.0F, 0.0F };

            const auto unFlags = static_cast<uint32>(pAnimHierarchy->pNodeInfo[nBoneInd].flags);
            if ((unFlags & rpHANIMPUSHPARENTMATRIX) != 0)
                ++iStackCounter;
            else if ((unFlags & rpHANIMPOPPARENTMATRIX) != 0)
                --iStackCounter;

            ++nBoneInd;
        }
    }

    m_fContactSurfaceBrightness = m_pPed->m_fContactSurfaceBrightness;
    CEntity::UpdateRW();
    CEntity::UpdateRwFrame();
    CEntity::UpdateRpHAnim();
}

void CHandObject::Render()
{
    CHandObject::Render_Reversed();
}
void CHandObject::Render_Reversed()
{
    auto* pFirstAtomic = GetFirstAtomic(m_pRwClump);
    RpMaterialSetTexture(RpGeometryGetMaterial(RpAtomicGetGeometry(pFirstAtomic), 0), m_pTexture);
    CObject::Render();
}
