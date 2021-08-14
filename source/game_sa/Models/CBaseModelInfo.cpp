/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

void CBaseModelInfo::InjectHooks()
{
// Vtable
    ReversibleHooks::Install("CBaseModelInfo", "AsAtomicModelInfoPtr", 0x4C4A80, &CBaseModelInfo::AsAtomicModelInfoPtr_Reversed);
    ReversibleHooks::Install("CBaseModelInfo", "AsDamageAtomicModelInfoPtr", 0x4C4A90, &CBaseModelInfo::AsDamageAtomicModelInfoPtr_Reversed);
    ReversibleHooks::Install("CBaseModelInfo", "AsLodAtomicModelInfoPtr", 0x4C4AA0, &CBaseModelInfo::AsLodAtomicModelInfoPtr_Reversed);
    ReversibleHooks::Install("CBaseModelInfo", "GetTimeInfo", 0x4C4AB0, &CBaseModelInfo::GetTimeInfo_Reversed);
    ReversibleHooks::Install("CBaseModelInfo", "Init", 0x4C4B10, &CBaseModelInfo::Init_Reversed);
    ReversibleHooks::Install("CBaseModelInfo", "Shutdown", 0x4C4D50, &CBaseModelInfo::Shutdown_Reversed);
    ReversibleHooks::Install("CBaseModelInfo", "SetAnimFile", 0x4C4AC0, &CBaseModelInfo::SetAnimFile_Reversed);
    ReversibleHooks::Install("CBaseModelInfo", "ConvertAnimFileIndex", 0x4C4AD0, &CBaseModelInfo::ConvertAnimFileIndex_Reversed);
    ReversibleHooks::Install("CBaseModelInfo", "GetAnimFileIndex", 0x4C4AE0, &CBaseModelInfo::GetAnimFileIndex_Reversed);

// Class methods
    ReversibleHooks::Install("CBaseModelInfo", "SetTexDictionary", 0x4C4B40, &CBaseModelInfo::SetTexDictionary);
    ReversibleHooks::Install("CBaseModelInfo", "ClearTexDictionary", 0x4C4B70, &CBaseModelInfo::ClearTexDictionary);
    ReversibleHooks::Install("CBaseModelInfo", "AddTexDictionaryRef", 0x4C4B80, &CBaseModelInfo::AddTexDictionaryRef);
    ReversibleHooks::Install("CBaseModelInfo", "RemoveTexDictionaryRef", 0x4C4B90, &CBaseModelInfo::RemoveTexDictionaryRef);
    ReversibleHooks::Install("CBaseModelInfo", "AddRef", 0x4C4BA0, &CBaseModelInfo::AddRef);
    ReversibleHooks::Install("CBaseModelInfo", "RemoveRef", 0x4C4BB0, &CBaseModelInfo::RemoveRef);
    ReversibleHooks::Install("CBaseModelInfo", "SetColModel", 0x4C4BC0, &CBaseModelInfo::SetColModel);
    ReversibleHooks::Install("CBaseModelInfo", "Init2dEffects", 0x4C4C20, &CBaseModelInfo::Init2dEffects);
    ReversibleHooks::Install("CBaseModelInfo", "DeleteCollisionModel", 0x4C4C40, &CBaseModelInfo::DeleteCollisionModel);
    ReversibleHooks::Install("CBaseModelInfo", "Get2dEffect", 0x4C4C70, &CBaseModelInfo::Get2dEffect);
    ReversibleHooks::Install("CBaseModelInfo", "Add2dEffect", 0x4C4D20, &CBaseModelInfo::Add2dEffect);

// Helpers
    ReversibleHooks::Install("CBaseModelInfo", "GetIsDrawLast", 0x5328C0, &CBaseModelInfo::GetIsDrawLast);
    ReversibleHooks::Install("CBaseModelInfo", "HasBeenPreRendered", 0x5328B0, &CBaseModelInfo::HasBeenPreRendered);
    ReversibleHooks::Install("CBaseModelInfo", "HasComplexHierarchy", 0x4C4E00, &CBaseModelInfo::HasComplexHierarchy);
    ReversibleHooks::Install("CBaseModelInfo", "IsBackfaceCulled", 0x5328F0, &CBaseModelInfo::IsBackfaceCulled);
    ReversibleHooks::Install("CBaseModelInfo", "IsLod", 0x4C4A00, &CBaseModelInfo::IsLod);
    ReversibleHooks::Install("CBaseModelInfo", "IsRoad", 0x4C4DF0, &CBaseModelInfo::IsRoad);
    ReversibleHooks::Install("CBaseModelInfo", "SetHasBeenPreRendered", 0x4C42F0, &CBaseModelInfo::SetHasBeenPreRendered);
    ReversibleHooks::Install("CBaseModelInfo", "SetIsLod", 0x4C4A10, &CBaseModelInfo::SetIsLod);
    ReversibleHooks::Install("CBaseModelInfo", "SetOwnsColModel", 0x5328D0, &CBaseModelInfo::SetOwnsColModel);
    ReversibleHooks::Install("CBaseModelInfo", "IncreaseAlpha", 0x532900, &CBaseModelInfo::IncreaseAlpha);

    ReversibleHooks::Install("CBaseModelInfo", "IsBreakableStatuePart", 0x59F090, &CBaseModelInfo::IsBreakableStatuePart);
    ReversibleHooks::Install("CBaseModelInfo", "IsTagModel", 0x49CC20, &CBaseModelInfo::IsTagModel);
    // Hooking SwaysInWind function causes side effects
    //ReversibleHooks::Install("CBaseModelInfo", "SwaysInWind", 0x4212C0, &CBaseModelInfo::SwaysInWind);

// Other
    ReversibleHooks::Install("CBaseModelInfo", "SetBaseModelInfoFlags", 0x5B3AD0, &SetBaseModelInfoFlags);
}

//0x4C4A80
CBaseModelInfo::CBaseModelInfo()
{
    m_nRefCount = 0;
    CBaseModelInfo::ClearTexDictionary();
}

CAtomicModelInfo* CBaseModelInfo::AsAtomicModelInfoPtr()
{
    return CBaseModelInfo::AsAtomicModelInfoPtr_Reversed();
}
CAtomicModelInfo* CBaseModelInfo::AsAtomicModelInfoPtr_Reversed()
{
    return nullptr;
}

CDamageAtomicModelInfo* CBaseModelInfo::AsDamageAtomicModelInfoPtr()
{
    return CBaseModelInfo::AsDamageAtomicModelInfoPtr_Reversed();
}
CDamageAtomicModelInfo* CBaseModelInfo::AsDamageAtomicModelInfoPtr_Reversed()
{
    return nullptr;
}

CLodAtomicModelInfo *CBaseModelInfo::AsLodAtomicModelInfoPtr()
{
    return CBaseModelInfo::AsLodAtomicModelInfoPtr_Reversed();
}
CLodAtomicModelInfo* CBaseModelInfo::AsLodAtomicModelInfoPtr_Reversed()
{
    return nullptr;
}

CTimeInfo *CBaseModelInfo::GetTimeInfo()
{
    return CBaseModelInfo::GetTimeInfo_Reversed();
}
CTimeInfo* CBaseModelInfo::GetTimeInfo_Reversed()
{
    return nullptr;
}

void CBaseModelInfo::Init()
{
    CBaseModelInfo::Init_Reversed();
}
void CBaseModelInfo::Init_Reversed()
{
    m_nRefCount = 0;
    m_pColModel = nullptr;
    CBaseModelInfo::ClearTexDictionary();
    CBaseModelInfo::Init2dEffects();
    m_nObjectInfoIndex = -1;
    m_fDrawDistance = 2000.0F;
    m_pRwObject = nullptr;

    m_nFlags = 0;
    bIsBackfaceCulled = true;
    bIsLod = true;
}

void CBaseModelInfo::Shutdown()
{
    CBaseModelInfo::Shutdown_Reversed();
}
void CBaseModelInfo::Shutdown_Reversed()
{
    DeleteRwObject();
    CBaseModelInfo::DeleteCollisionModel();

    bIsLod = true;
    m_nObjectInfoIndex = -1;
    CBaseModelInfo::ClearTexDictionary();
    CBaseModelInfo::Init2dEffects();
}

void CBaseModelInfo::SetAnimFile(char const* filename)
{
    CBaseModelInfo::SetAnimFile_Reversed(filename);
}
void CBaseModelInfo::SetAnimFile_Reversed(char const* filename)
{}

void CBaseModelInfo::ConvertAnimFileIndex()
{
    CBaseModelInfo::ConvertAnimFileIndex_Reversed();
}
void CBaseModelInfo::ConvertAnimFileIndex_Reversed() {
    // NOP
}

signed int CBaseModelInfo::GetAnimFileIndex()
{
    return CBaseModelInfo::GetAnimFileIndex_Reversed();
}
signed int CBaseModelInfo::GetAnimFileIndex_Reversed()
{
    return -1;
}

void CBaseModelInfo::SetTexDictionary(char const* txdName)
{
    m_nTxdIndex = CTxdStore::FindTxdSlot(txdName);
    if (m_nTxdIndex == -1)
        m_nTxdIndex = CTxdStore::AddTxdSlot(txdName);
}

void CBaseModelInfo::ClearTexDictionary()
{
    m_nTxdIndex = -1;
}

void CBaseModelInfo::AddTexDictionaryRef()
{
    CTxdStore::AddRef(m_nTxdIndex);
}

void CBaseModelInfo::RemoveTexDictionaryRef()
{
    CTxdStore::RemoveRef(m_nTxdIndex);
}

void CBaseModelInfo::AddRef()
{
    ++m_nRefCount;
    CBaseModelInfo::AddTexDictionaryRef();
}

void CBaseModelInfo::RemoveRef()
{
    --m_nRefCount;
    CBaseModelInfo::RemoveTexDictionaryRef();
}

void CBaseModelInfo::SetColModel(CColModel *colModel, bool bIsLodModel)
{
    m_pColModel = colModel;
    if (!bIsLodModel) {
        bIsLod = false;
        return;
    }

    bIsLod = true;
    auto pTimeInfo = GetTimeInfo();
    if (!pTimeInfo)
        return;

    if (pTimeInfo->GetOtherTimeModel() == -1)
        return;

    auto pLodInfo = CModelInfo::GetModelInfo(pTimeInfo->GetOtherTimeModel());
    pLodInfo->m_pColModel = colModel;
    pLodInfo->bIsLod = false;
}

void CBaseModelInfo::Init2dEffects()
{
    m_n2dEffectIndex = -1;
    m_n2dfxCount = 0;
}

void CBaseModelInfo::DeleteCollisionModel()
{
    if (m_pColModel && bIsLod)
        delete m_pColModel;

    m_pColModel = nullptr;
}

C2dEffect *CBaseModelInfo::Get2dEffect(int index)
{
    auto uiStoredEffectsCount = m_n2dfxCount;
    RpGeometry* pGeometry = nullptr;
    if (m_pRwObject) {
        if (GetRwModelType() == rpATOMIC) {
            pGeometry = RpAtomicGetGeometry(m_pRwAtomic);
        }
        else if (GetRwModelType() == rpCLUMP) {
            auto pAtomic = Get2DEffectAtomic(m_pRwClump);
            if (pAtomic) {
                pGeometry = RpAtomicGetGeometry(pAtomic);
            }
        }

        if (pGeometry)
            uiStoredEffectsCount -= RpGeometryGet2dFxCount(pGeometry);
    }

    if (index < uiStoredEffectsCount)
        return &CModelInfo::Get2dEffectStore()->GetItemAtIndex(index + m_n2dEffectIndex);
    else
        return RpGeometryGet2dFxAtIndex(pGeometry, index - uiStoredEffectsCount);
}

void CBaseModelInfo::Add2dEffect(C2dEffect *effect)
{
    if (m_n2dEffectIndex >= 0)
        ++m_n2dfxCount;
    else {
        m_n2dEffectIndex = (effect - &CModelInfo::Get2dEffectStore()->m_aObjects[0]);
        m_n2dfxCount = 1;
    }
}

void SetBaseModelInfoFlags(CBaseModelInfo* modelInfo, unsigned int dwFlags)
{
    auto flagsStruct = sItemDefinitionFlags(dwFlags);
    modelInfo->bDrawLast = flagsStruct.bDrawLast | flagsStruct.bDrawLast;
    modelInfo->bAdditiveRender = flagsStruct.bAdditive;
    modelInfo->bDontWriteZBuffer = flagsStruct.bNoZBufferWrite;
    modelInfo->bDontCastShadowsOn = flagsStruct.bDontReceiveShadows;
    modelInfo->bIsBackfaceCulled = !flagsStruct.bDisableBackfaceCulling;
}
