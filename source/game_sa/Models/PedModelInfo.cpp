#include "StdInc.h"

#include "PedModelInfo.h"

RwObjectNameIdAssocation(&CPedModelInfo::m_pPedIds)[NUM_PED_NAME_ID_ASSOC] = *(RwObjectNameIdAssocation(*)[NUM_PED_NAME_ID_ASSOC])0x8A6268;
tPedColNodeInfo(&CPedModelInfo::m_pColNodeInfos)[NUM_PED_COL_NODE_INFOS] = *(tPedColNodeInfo(*)[NUM_PED_COL_NODE_INFOS])0x8A6308;

void CPedModelInfo::InjectHooks()
{
    RH_ScopedClass(CPedModelInfo);
    RH_ScopedCategory("Models");

    RH_ScopedInstall(GetModelType_Reversed, 0x4C57C0);
    RH_ScopedInstall(DeleteRwObject_Reversed, 0x4C6C50);
    RH_ScopedInstall(SetClump_Reversed, 0x4C7340);
    RH_ScopedInstall(AddXtraAtomics, 0x4C6D40);
    RH_ScopedInstall(SetFaceTexture, 0x4C6D50);
    RH_ScopedInstall(CreateHitColModelSkinned, 0x4C6D90);
    RH_ScopedInstall(AnimatePedColModelSkinned, 0x4C6F70);
    RH_ScopedInstall(AnimatePedColModelSkinnedWorld, 0x4C7170);
    RH_ScopedInstall(IncrementVoice, 0x4C7300);
}

ModelInfoType CPedModelInfo::GetModelType()
{
    return CPedModelInfo::GetModelType_Reversed();
}
ModelInfoType CPedModelInfo::GetModelType_Reversed()
{
    return ModelInfoType::MODEL_INFO_PED;
}

void CPedModelInfo::DeleteRwObject()
{
    CPedModelInfo::DeleteRwObject_Reversed();
}
void CPedModelInfo::DeleteRwObject_Reversed()
{
    CClumpModelInfo::DeleteRwObject();
    if (m_pHitColModel)
        delete m_pHitColModel;

    m_pHitColModel = nullptr;
}

void CPedModelInfo::SetClump(RpClump* clump)
{
    CPedModelInfo::SetClump_Reversed(clump);
}
void CPedModelInfo::SetClump_Reversed(RpClump* clump)
{
    CClumpModelInfo::SetClump(clump);
    CClumpModelInfo::SetFrameIds(CPedModelInfo::m_pPedIds);

    if (!m_pHitColModel)
        CPedModelInfo::CreateHitColModelSkinned(clump);

    RpClumpForAllAtomics(m_pRwClump, CClumpModelInfo::SetAtomicRendererCB, CVisibilityPlugins::RenderPedCB);
    GetAnimHierarchyFromClump(m_pRwClump); //Unused? Or indirectly passes through EAX somehow?
}

void CPedModelInfo::AddXtraAtomics(RpClump* clump)
{}

void CPedModelInfo::SetFaceTexture(RwTexture* texture)
{}

void CPedModelInfo::CreateHitColModelSkinned(RpClump* clump)
{
    auto hierarchy = GetAnimHierarchyFromSkinClump(clump);
    auto cm = new CColModel();

    cm->AllocateData(12, 0, 0, 0, 0, false);
    RwMatrixInvert(CGame::m_pWorkingMatrix1, RwFrameGetMatrix(RpClumpGetFrame(clump)));
    for (int32 i = 0; i < NUM_PED_COL_NODE_INFOS; ++i) {
        auto& sphere = cm->m_pColData->m_pSpheres[i];
        auto& nodeInfo = m_pColNodeInfos[i];
        memcpy(CGame::m_pWorkingMatrix2, CGame::m_pWorkingMatrix1, sizeof(RwMatrix));

        CVector vecCenter = nodeInfo.m_vecCenter;
        auto animId = RpHAnimIDGetIndex(hierarchy, nodeInfo.m_nBoneID);
        auto pAnimMat = &RpHAnimHierarchyGetMatrixArray(hierarchy)[animId];
        RwMatrixTransform(CGame::m_pWorkingMatrix2, pAnimMat, RwOpCombineType::rwCOMBINEPRECONCAT);
        RwV3dTransformPoints(&vecCenter, &vecCenter, 1, CGame::m_pWorkingMatrix2);

        sphere.m_vecCenter = vecCenter;
        sphere.m_fRadius = nodeInfo.m_fRadius;
        sphere.m_nMaterial = eSurfaceType::SURFACE_PED;
        sphere.m_nFlags = nodeInfo.m_nFlags;
    }

    cm->m_boundSphere.Set(1.5F, CVector(0.0F, 0.0F, 0.0F));
    cm->m_boundBox.Set(CVector(-0.5F, -0.5F, -1.2F), CVector(0.5F, 0.5F, 1.2F));
    cm->m_nColSlot = 0;

    m_pHitColModel = cm;
}

CColModel* CPedModelInfo::AnimatePedColModelSkinned(RpClump* clump)
{
    if (!m_pHitColModel) {
        CreateHitColModelSkinned(clump);
        return m_pHitColModel;
    }

    auto hierarchy = GetAnimHierarchyFromSkinClump(clump);
    RwMatrixInvert(CGame::m_pWorkingMatrix1, RwFrameGetMatrix(RpClumpGetFrame(clump)));
    for (int32 i = 0; i < NUM_PED_COL_NODE_INFOS; ++i) {
        auto& sphere = m_pHitColModel->m_pColData->m_pSpheres[i];
        auto& nodeInfo = m_pColNodeInfos[i];
        memcpy(CGame::m_pWorkingMatrix2, CGame::m_pWorkingMatrix1, sizeof(RwMatrix));

        CVector vecCenter = nodeInfo.m_vecCenter;
        auto animId = RpHAnimIDGetIndex(hierarchy, nodeInfo.m_nBoneID);
        auto pAnimMat = &RpHAnimHierarchyGetMatrixArray(hierarchy)[animId];
        RwMatrixTransform(CGame::m_pWorkingMatrix2, pAnimMat, RwOpCombineType::rwCOMBINEPRECONCAT);
        RwV3dTransformPoints(&vecCenter, &vecCenter, 1, CGame::m_pWorkingMatrix2);

        sphere.m_vecCenter = vecCenter;
    }

    memcpy(CGame::m_pWorkingMatrix2, CGame::m_pWorkingMatrix1, sizeof(RwMatrix));
    auto animId = RpHAnimIDGetIndex(hierarchy, ePedBones::BONE_SPINE1);
    auto pAnimMat = &RpHAnimHierarchyGetMatrixArray(hierarchy)[animId];
    RwMatrixTransform(CGame::m_pWorkingMatrix2, pAnimMat, RwOpCombineType::rwCOMBINEPRECONCAT);
    auto vecSpine = CVector(0.0F, 0.0F, 0.0F);
    RwV3dTransformPoints(&vecSpine, &vecSpine, 1, CGame::m_pWorkingMatrix2);
    m_pHitColModel->m_boundSphere.Set(1.5F, vecSpine);
    m_pHitColModel->m_boundBox.Set(
        CVector(vecSpine.x - 1.2F, vecSpine.y - 1.2F, vecSpine.z - 1.2F),
        CVector(vecSpine.x + 1.2F, vecSpine.y + 1.2F, vecSpine.z + 1.2F)
    );

    return m_pHitColModel;
}

CColModel* CPedModelInfo::AnimatePedColModelSkinnedWorld(RpClump* clump)
{
    if (!m_pHitColModel)
        CreateHitColModelSkinned(clump);

    auto hierarchy = GetAnimHierarchyFromSkinClump(clump);
    for (int32 i = 0; i < NUM_PED_COL_NODE_INFOS; ++i) {
        auto& sphere = m_pHitColModel->m_pColData->m_pSpheres[i];
        auto& nodeInfo = m_pColNodeInfos[i];

        CVector vecCenter = nodeInfo.m_vecCenter;
        auto animId = RpHAnimIDGetIndex(hierarchy, nodeInfo.m_nBoneID);
        auto pAnimMat = &RpHAnimHierarchyGetMatrixArray(hierarchy)[animId];
        RwV3dTransformPoints(&vecCenter, &vecCenter, 1, pAnimMat);

        sphere.m_vecCenter = vecCenter;
    }

    auto animId = RpHAnimIDGetIndex(hierarchy, ePedBones::BONE_SPINE1);
    auto pAnimMat = &RpHAnimHierarchyGetMatrixArray(hierarchy)[animId];
    auto vecSpine = CVector(0.0F, 0.0F, 0.0F);
    RwV3dTransformPoints(&vecSpine, &vecSpine, 1, pAnimMat);
    m_pHitColModel->m_boundSphere.Set(1.5F, vecSpine);
    m_pHitColModel->m_boundBox.Set(CVector(vecSpine.x - 1.2F, vecSpine.y - 1.2F, vecSpine.z - 1.2F),
                                   CVector(vecSpine.x + 1.2F, vecSpine.y + 1.2F, vecSpine.z + 1.2F));

    return m_pHitColModel;
}

void CPedModelInfo::IncrementVoice()
{
    if (m_nVoiceMin < 0 || m_nVoiceMax < 0) {
        m_nVoiceId = -1;
        return;
    }

    ++m_nVoiceId;
    if (m_nVoiceId > m_nVoiceMax || m_nVoiceId < m_nVoiceMin)
        m_nVoiceId = m_nVoiceMin;
}
