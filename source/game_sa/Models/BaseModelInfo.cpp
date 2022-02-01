/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

void CBaseModelInfo::InjectHooks()
{
    RH_ScopedClass(CBaseModelInfo);
    RH_ScopedCategory("Models");

// Vtable
    RH_ScopedInstall(AsAtomicModelInfoPtr_Reversed, 0x4C4A80);
    RH_ScopedInstall(AsDamageAtomicModelInfoPtr_Reversed, 0x4C4A90);
    RH_ScopedInstall(AsLodAtomicModelInfoPtr_Reversed, 0x4C4AA0);
    RH_ScopedInstall(GetTimeInfo_Reversed, 0x4C4AB0);
    RH_ScopedInstall(Init_Reversed, 0x4C4B10);
    RH_ScopedInstall(Shutdown_Reversed, 0x4C4D50);
    RH_ScopedInstall(SetAnimFile_Reversed, 0x4C4AC0);
    RH_ScopedInstall(ConvertAnimFileIndex_Reversed, 0x4C4AD0);
    RH_ScopedInstall(GetAnimFileIndex_Reversed, 0x4C4AE0);

// Class methods
    RH_ScopedInstall(SetTexDictionary, 0x4C4B40);
    RH_ScopedInstall(ClearTexDictionary, 0x4C4B70);
    RH_ScopedInstall(AddTexDictionaryRef, 0x4C4B80);
    RH_ScopedInstall(RemoveTexDictionaryRef, 0x4C4B90);
    RH_ScopedInstall(AddRef, 0x4C4BA0);
    RH_ScopedInstall(RemoveRef, 0x4C4BB0);
    RH_ScopedInstall(SetColModel, 0x4C4BC0);
    RH_ScopedInstall(Init2dEffects, 0x4C4C20);
    RH_ScopedInstall(DeleteCollisionModel, 0x4C4C40);
    RH_ScopedInstall(Get2dEffect, 0x4C4C70);
    RH_ScopedInstall(Add2dEffect, 0x4C4D20);

// Helpers
    RH_ScopedInstall(GetIsDrawLast, 0x5328C0);
    RH_ScopedInstall(HasBeenPreRendered, 0x5328B0);
    RH_ScopedInstall(HasComplexHierarchy, 0x4C4E00);
    RH_ScopedInstall(IsBackfaceCulled, 0x5328F0);
    RH_ScopedInstall(IsLod, 0x4C4A00);
    RH_ScopedInstall(IsRoad, 0x4C4DF0);
    RH_ScopedInstall(SetHasBeenPreRendered, 0x4C42F0);
    RH_ScopedInstall(SetIsLod, 0x4C4A10);
    RH_ScopedInstall(SetOwnsColModel, 0x5328D0);
    RH_ScopedInstall(IncreaseAlpha, 0x532900);

    RH_ScopedInstall(IsBreakableStatuePart, 0x59F090);
    RH_ScopedInstall(IsTagModel, 0x49CC20);
    // Hooking SwaysInWind function causes side effects
    //RH_ScopedInstall(SwaysInWind, 0x4212C0);

// Other
    RH_ScopedInstall(SetBaseModelInfoFlags, 0x5B3AD0);
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

C2dEffect *CBaseModelInfo::Get2dEffect(int32 index)
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

void SetBaseModelInfoFlags(CBaseModelInfo* modelInfo, uint32 dwFlags)
{
    auto flagsStruct = sItemDefinitionFlags(dwFlags);
    modelInfo->bDrawLast = flagsStruct.bDrawLast | flagsStruct.bDrawLast;
    modelInfo->bAdditiveRender = flagsStruct.bAdditive;
    modelInfo->bDontWriteZBuffer = flagsStruct.bNoZBufferWrite;
    modelInfo->bDontCastShadowsOn = flagsStruct.bDontReceiveShadows;
    modelInfo->bIsBackfaceCulled = !flagsStruct.bDisableBackfaceCulling;
}

void CBaseModelInfo::SetBaseModelInfoFlags(uint32 flags) {
    ::SetBaseModelInfoFlags(this, flags);
}
