/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void CClumpModelInfo::InjectHooks()
{
// VTABLE
    Install("CClumpModelInfo", "GetModelType", 0x4C5720, &CClumpModelInfo::GetModelType_Reversed);
    Install("CClumpModelInfo", "Init", 0x4C4E40, &CClumpModelInfo::Init_Reversed);
    Install("CClumpModelInfo", "Shutdown", 0x4C4E60, &CClumpModelInfo::Shutdown_Reversed);
    Install("CClumpModelInfo", "DeleteRwObject", 0x4C4E70, &CClumpModelInfo::DeleteRwObject_Reversed);
    Install("CClumpModelInfo", "GetRwModelType", 0x4C5730, &CClumpModelInfo::GetRwModelType_Reversed);
    Install("CClumpModelInfo", "CreateInstance_void", 0x4C5140, (RwObject * (CClumpModelInfo::*)())(&CClumpModelInfo::CreateInstance_Reversed));
    Install("CClumpModelInfo", "CreateInstance_mat", 0x4C5110, static_cast<RwObject * (CClumpModelInfo::*)(RwMatrix*)>(&CClumpModelInfo::CreateInstance_Reversed));
    Install("CClumpModelInfo", "SetAnimFile", 0x4C5200, &CClumpModelInfo::SetAnimFile_Reversed);
    Install("CClumpModelInfo", "ConvertAnimFileIndex", 0x4C5250, &CClumpModelInfo::ConvertAnimFileIndex_Reversed);
    Install("CClumpModelInfo", "GetAnimFileIndex", 0x4C5740, &CClumpModelInfo::GetAnimFileIndex_Reversed);
    Install("CClumpModelInfo", "GetBoundingBox", 0x4C5710, &CClumpModelInfo::GetBoundingBox_Reversed);
    Install("CClumpModelInfo", "SetClump", 0x4C4F70, &CClumpModelInfo::SetClump_Reversed);

// CLASS FUNCTIONS
    Install("CClumpModelInfo", "SetFrameIds", 0x4C5460, &CClumpModelInfo::SetFrameIds);

// STATICS
    Install("CClumpModelInfo", "SetHierarchyForSkinAtomic", 0x4C4EF0, &CClumpModelInfo::SetHierarchyForSkinAtomic);
    Install("CClumpModelInfo", "AtomicSetupLightingCB", 0x4C4F30, &CClumpModelInfo::AtomicSetupLightingCB);
    Install("CClumpModelInfo", "SetAtomicRendererCB", 0x4C5280, &CClumpModelInfo::SetAtomicRendererCB);
    Install("CClumpModelInfo", "FindFrameFromNameCB", 0x4C52A0, &CClumpModelInfo::FindFrameFromNameCB);
    Install("CClumpModelInfo", "FindFrameFromNameWithoutIdCB", 0x4C52F0, &CClumpModelInfo::FindFrameFromNameWithoutIdCB);
    Install("CClumpModelInfo", "FindFrameFromIdCB", 0x4C5350, &CClumpModelInfo::FindFrameFromIdCB);
    Install("CClumpModelInfo", "FillFrameArrayCB", 0x4C5390, &CClumpModelInfo::FillFrameArrayCB);
    Install("CClumpModelInfo", "GetFrameFromId", 0x4C53C0, &CClumpModelInfo::GetFrameFromId);
    Install("CClumpModelInfo", "GetFrameFromName", 0x4C5400, &CClumpModelInfo::GetFrameFromName);
    Install("CClumpModelInfo", "FillFrameArray", 0x4C5440, &CClumpModelInfo::FillFrameArray);

// Other
    Install("CBaseModelInfo", "SetClumpModelInfoFlags", 0x5B3C30, &SetClumpModelInfoFlags);
}

ModelInfoType CClumpModelInfo::GetModelType()
{
    return CClumpModelInfo::GetModelType_Reversed();
}
ModelInfoType CClumpModelInfo::GetModelType_Reversed()
{
    return ModelInfoType::MODEL_INFO_CLUMP;
}

void CClumpModelInfo::Init()
{
    CClumpModelInfo::Init_Reversed();
}
void CClumpModelInfo::Init_Reversed()
{
    CBaseModelInfo::Init();
    m_dwAnimFileIndex = -1;
}

void CClumpModelInfo::Shutdown()
{
    return CClumpModelInfo::Shutdown_Reversed();
}
void CClumpModelInfo::Shutdown_Reversed()
{
    CBaseModelInfo::Shutdown();
}

void CClumpModelInfo::DeleteRwObject()
{
    CClumpModelInfo::DeleteRwObject_Reversed();
}
void CClumpModelInfo::DeleteRwObject_Reversed()
{
    if (!m_pRwObject)
        return;

    auto pAtomic = Get2DEffectAtomic(m_pRwClump);
    if (pAtomic)
        m_n2dfxCount -= RpGeometryGet2dFxCount(RpAtomicGetGeometry(pAtomic));

    RpClumpDestroy(m_pRwClump);
    m_pRwObject = nullptr;

    CBaseModelInfo::RemoveTexDictionaryRef();
    auto iAnimIndex = GetAnimFileIndex();
    if (iAnimIndex != -1)
        CAnimManager::RemoveAnimBlockRef(iAnimIndex);

    if (bOwnsCollisionModel)
        CBaseModelInfo::DeleteCollisionModel();
}

uint32 CClumpModelInfo::GetRwModelType()
{
    return CClumpModelInfo::GetRwModelType_Reversed();
}
uint32 CClumpModelInfo::GetRwModelType_Reversed()
{
    return rpCLUMP;
}

RwObject* CClumpModelInfo::CreateInstance()
{
    return CClumpModelInfo::CreateInstance_Reversed();
}
RwObject* CClumpModelInfo::CreateInstance_Reversed()
{
    if (!m_pRwObject)
        return nullptr;

    CBaseModelInfo::AddRef();
    auto pClonedClump = RpClumpClone(m_pRwClump);
    auto pAtomic = GetFirstAtomic(pClonedClump);
    if (pAtomic && RpSkinGeometryGetSkin(RpAtomicGetGeometry(pAtomic)) && !bHasComplexHierarchy) {
        auto pHierarchy = GetAnimHierarchyFromClump(pClonedClump);
        RpClumpForAllAtomics(pClonedClump, CClumpModelInfo::SetHierarchyForSkinAtomic, pHierarchy);
        auto pAnim = RpAnimBlendCreateAnimationForHierarchy(pHierarchy);
        RtAnimInterpolatorSetCurrentAnim(pHierarchy->currentAnim, pAnim);
        pHierarchy->flags = rpHANIMHIERARCHYUPDATEMODELLINGMATRICES | rpHANIMHIERARCHYUPDATELTMS;
    }

    if (bHasAnimBlend) {
        RpAnimBlendClumpInit(pClonedClump);
        auto pAnimBlend = CAnimManager::GetAnimation(m_nKey, &CAnimManager::ms_aAnimBlocks[m_dwAnimFileIndex]);
        if (pAnimBlend)
            CAnimManager::BlendAnimation(pClonedClump, pAnimBlend, eAnimationFlags::ANIM_FLAG_LOOPED, 1.0F);
    }

    CBaseModelInfo::RemoveRef();
    return reinterpret_cast<RwObject*>(pClonedClump);
}

RwObject* CClumpModelInfo::CreateInstance(RwMatrix* matrix)
{
    return CClumpModelInfo::CreateInstance_Reversed(matrix);
}
RwObject* CClumpModelInfo::CreateInstance_Reversed(RwMatrix* matrix)
{
    if (!m_pRwObject)
        return nullptr;

    auto pClump = CreateInstance();
    memcpy(RpClumpGetFrame(pClump), matrix, sizeof(RwMatrix));
    return pClump;
}

void CClumpModelInfo::SetAnimFile(char const* filename)
{
    CClumpModelInfo::SetAnimFile_Reversed(filename);
}
void CClumpModelInfo::SetAnimFile_Reversed(char const* filename)
{
    if (!strcmp(filename, "null"))
        return;

    auto pName = new char[strlen(filename) + 1];
    strcpy(pName, filename);
    m_animFileName = pName;
}

void CClumpModelInfo::ConvertAnimFileIndex()
{
    CClumpModelInfo::ConvertAnimFileIndex_Reversed();
}
void CClumpModelInfo::ConvertAnimFileIndex_Reversed()
{
    if (m_dwAnimFileIndex == -1)
        return;

    auto iIndex = CAnimManager::GetAnimationBlockIndex(m_animFileName);
    delete[] m_animFileName;
    m_dwAnimFileIndex = iIndex;
}

signed int CClumpModelInfo::GetAnimFileIndex()
{
    return CClumpModelInfo::GetAnimFileIndex_Reversed();
}
signed int CClumpModelInfo::GetAnimFileIndex_Reversed()
{
    return m_dwAnimFileIndex;
}

CBox* CClumpModelInfo::GetBoundingBox()
{
    return CClumpModelInfo::GetBoundingBox_Reversed();
}
CBox* CClumpModelInfo::GetBoundingBox_Reversed()
{
    return &GetColModel()->GetBoundingBox();
}

void CClumpModelInfo::SetClump(RpClump* clump)
{
    CClumpModelInfo::SetClump_Reversed(clump);
}
void CClumpModelInfo::SetClump_Reversed(RpClump* clump)
{
    if (m_pRwObject) {
        auto pAtomic = Get2DEffectAtomic(m_pRwClump);
        if (pAtomic)
            m_n2dfxCount -= RpGeometryGet2dFxCount(RpAtomicGetGeometry(pAtomic));
    }

    m_pRwClump = clump;
    if (m_pRwClump) {
        auto pAtomic = Get2DEffectAtomic(m_pRwClump);
        if (pAtomic)
            m_n2dfxCount += RpGeometryGet2dFxCount(RpAtomicGetGeometry(pAtomic));
    }

    CVisibilityPlugins::SetClumpModelInfo(m_pRwClump, this);
    CBaseModelInfo::AddTexDictionaryRef();

    auto iAnimIndex = GetAnimFileIndex();
    if (iAnimIndex != -1)
        CAnimManager::AddAnimBlockRef(iAnimIndex);

    RpClumpForAllAtomics(m_pRwClump, CClumpModelInfo::AtomicSetupLightingCB, this);
    auto pFirstAtomic = GetFirstAtomic(m_pRwClump);
    if (pFirstAtomic && RpSkinGeometryGetSkin(RpAtomicGetGeometry(pFirstAtomic))) {
        if (bHasComplexHierarchy) {
            RpClumpForAllAtomics(m_pRwClump, CClumpModelInfo::SetHierarchyForSkinAtomic, nullptr);
        }
        else {
            auto sphere = RpMorphTargetGetBoundingSphere(RpGeometryGetMorphTarget(RpAtomicGetGeometry(pFirstAtomic), 0));
            sphere->radius *= 1.2F;

            auto pHierarchy = GetAnimHierarchyFromClump(m_pRwClump);
            RpClumpForAllAtomics(m_pRwClump, CClumpModelInfo::SetHierarchyForSkinAtomic, pHierarchy);

            auto pGeometry = RpAtomicGetGeometry(pFirstAtomic);
            auto pSkin = RpSkinGeometryGetSkin(pGeometry);
            for (int32 i = 0; i < RpGeometryGetNumVertices(pGeometry); ++i) {
                auto& pWeight = RpSkinGetVertexBoneWeights(pSkin)[i];
                auto fRecip = 1.0F / (pWeight.w0 + pWeight.w1 + pWeight.w2 + pWeight.w3);
                pWeight.w0 *= fRecip;
                pWeight.w1 *= fRecip;
                pWeight.w2 *= fRecip;
                pWeight.w3 *= fRecip;
            }

            pHierarchy->flags = rpHANIMHIERARCHYUPDATEMODELLINGMATRICES | rpHANIMHIERARCHYUPDATELTMS;
        }
    }
}

// 0x4C5460
void CClumpModelInfo::SetFrameIds(RwObjectNameIdAssocation* data) {
    if (!data->m_pName)
        return;

    auto pCurComponent = data;
    while (pCurComponent->m_pName) {
        if ((pCurComponent->m_dwFlags & 1) == 0) {
            auto searchInfo = tCompSearchStructByName(pCurComponent->m_pName, nullptr);
            RwFrameForAllChildren(RpClumpGetFrame(m_pRwClump), CClumpModelInfo::FindFrameFromNameWithoutIdCB, &searchInfo);
            if (searchInfo.m_pFrame)
                CVisibilityPlugins::SetFrameHierarchyId(searchInfo.m_pFrame, pCurComponent->m_dwHierarchyId);
        }

        pCurComponent++;
    }
}

void CClumpModelInfo::SetClumpModelInfoFlags(uint32 flags) {
    ::SetClumpModelInfoFlags(this, flags);
}

RpAtomic* CClumpModelInfo::SetAtomicRendererCB(RpAtomic* atomic, void* renderFunc)
{
    CVisibilityPlugins::SetAtomicRenderCallback(atomic, reinterpret_cast<RpAtomicCallBackRender>(renderFunc));
    return atomic;
}

RpAtomic* CClumpModelInfo::AtomicSetupLightingCB(RpAtomic* atomic, void* data)
{
    if (CCustomBuildingRenderer::IsCBPCPipelineAttached(atomic))
        CCustomBuildingRenderer::AtomicSetup(atomic);
    else if (CCarFXRenderer::IsCCPCPipelineAttached(atomic))
        CCarFXRenderer::CustomCarPipeAtomicSetup(atomic);

    return atomic;
}

RpAtomic* CClumpModelInfo::SetHierarchyForSkinAtomic(RpAtomic* pAtomic, void* data)
{
    if (data) {
        RpSkinAtomicSetHAnimHierarchy(pAtomic, reinterpret_cast<RpHAnimHierarchy*>(data));
        return nullptr;
    }

    auto pHierarchy = GetAnimHierarchyFromFrame(RpAtomicGetFrame(pAtomic));
    RpSkinAtomicSetHAnimHierarchy(pAtomic, pHierarchy);
    return pAtomic;
}

RwFrame* CClumpModelInfo::FindFrameFromNameCB(RwFrame* frame, void* searchData)
{
    auto searchInfo = reinterpret_cast<tCompSearchStructByName*>(searchData);
    auto pName = GetFrameNodeName(frame);
    if (!strcmp(searchInfo->m_pName, pName)) {
        searchInfo->m_pFrame = frame;
        return nullptr;
    }

    RwFrameForAllChildren(frame, CClumpModelInfo::FindFrameFromNameCB, searchData);
    if (searchInfo->m_pFrame)
        return nullptr;
    else
        return frame;
}

RwFrame* CClumpModelInfo::FindFrameFromNameWithoutIdCB(RwFrame* frame, void* searchData)
{
    auto searchInfo = reinterpret_cast<tCompSearchStructByName*>(searchData);
    auto pName = GetFrameNodeName(frame);
    if (!CVisibilityPlugins::GetFrameHierarchyId(frame) && !strcmp(searchInfo->m_pName, pName)) {
        searchInfo->m_pFrame = frame;
        return nullptr;
    }

    RwFrameForAllChildren(frame, CClumpModelInfo::FindFrameFromNameWithoutIdCB, searchData);
    if (searchInfo->m_pFrame)
        return nullptr;
    else
        return frame;
}

RwFrame* CClumpModelInfo::FindFrameFromIdCB(RwFrame* frame, void* searchData)
{
    auto searchInfo = reinterpret_cast<tCompSearchStructById*>(searchData);
    if (searchInfo->m_nId == CVisibilityPlugins::GetFrameHierarchyId(frame)) {
        searchInfo->m_pFrame = frame;
        return nullptr;
    }

    RwFrameForAllChildren(frame, CClumpModelInfo::FindFrameFromIdCB, searchData);
    if (searchInfo->m_pFrame)
        return nullptr;
    else
        return frame;
}

RwFrame* CClumpModelInfo::FillFrameArrayCB(RwFrame* frame, void* data)
{
    auto iId = CVisibilityPlugins::GetFrameHierarchyId(frame);
    if (iId > 0)
        reinterpret_cast<RwFrame**>(data)[iId] = frame;

    RwFrameForAllChildren(frame, CClumpModelInfo::FillFrameArrayCB, data);
    return frame;
}

RwFrame* CClumpModelInfo::GetFrameFromId(RpClump* clump, int32 id)
{
    auto searchInfo = tCompSearchStructById(id, nullptr);
    RwFrameForAllChildren(RpClumpGetFrame(clump), CClumpModelInfo::FindFrameFromIdCB, &searchInfo);
    return searchInfo.m_pFrame;
}

RwFrame* CClumpModelInfo::GetFrameFromName(RpClump* clump, const char* name)
{
    auto searchInfo = tCompSearchStructByName(name, nullptr);
    RwFrameForAllChildren(RpClumpGetFrame(clump), CClumpModelInfo::FindFrameFromNameCB, &searchInfo);
    return searchInfo.m_pFrame;
}

void CClumpModelInfo::FillFrameArray(RpClump* clump, RwFrame** frames)
{
    RwFrameForAllChildren(RpClumpGetFrame(clump), CClumpModelInfo::FillFrameArrayCB, frames);
}

void SetClumpModelInfoFlags(CClumpModelInfo* modelInfo, uint32 dwFlags)
{
    SetBaseModelInfoFlags(modelInfo, dwFlags);

    auto flagsStruct = sItemDefinitionFlags(dwFlags);
    modelInfo->bAnimSomething = flagsStruct.bAnimSomething;
}
