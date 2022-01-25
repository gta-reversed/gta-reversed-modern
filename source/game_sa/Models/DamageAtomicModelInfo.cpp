#include "StdInc.h"

bool& CDamageAtomicModelInfo::ms_bCreateDamagedVersion = *(bool*)0xA9B0B0;

void CDamageAtomicModelInfo::InjectHooks()
{
    ReversibleHooks::Install("CDamageAtomicModelInfo", "Init", 0x4C48B0, &CDamageAtomicModelInfo::Init_Reversed);
    ReversibleHooks::Install("CDamageAtomicModelInfo", "AsDamageAtomicModelInfoPtr", 0x4C55C0, &CDamageAtomicModelInfo::AsDamageAtomicModelInfoPtr_Reversed);
    ReversibleHooks::Install("CDamageAtomicModelInfo", "DeleteRwObject", 0x4C49D0, &CDamageAtomicModelInfo::DeleteRwObject_Reversed);
    ReversibleHooks::Install("CDamageAtomicModelInfo", "CreateInstance_void", 0x4C4960, (RwObject * (CDamageAtomicModelInfo::*)())(&CDamageAtomicModelInfo::CreateInstance_Reversed));
    ReversibleHooks::Install("CDamageAtomicModelInfo", "CreateInstance_rwmat", 0x4C4910, static_cast<RwObject * (CDamageAtomicModelInfo::*)(RwMatrix*)>(&CDamageAtomicModelInfo::CreateInstance_Reversed));

    ReversibleHooks::Install("CDamageAtomicModelInfo", "SetDamagedAtomic", 0x4C48D0, &CDamageAtomicModelInfo::SetDamagedAtomic);
}

CDamageAtomicModelInfo* CDamageAtomicModelInfo::AsDamageAtomicModelInfoPtr()
{
    return CDamageAtomicModelInfo::AsDamageAtomicModelInfoPtr_Reversed();
}
CDamageAtomicModelInfo* CDamageAtomicModelInfo::AsDamageAtomicModelInfoPtr_Reversed()
{
    return this;
}

void CDamageAtomicModelInfo::Init()
{
    CDamageAtomicModelInfo::Init_Reversed();
}
void CDamageAtomicModelInfo::Init_Reversed()
{
    CBaseModelInfo::Init();
    m_pDamagedAtomic = nullptr;
}

void CDamageAtomicModelInfo::DeleteRwObject()
{
    CDamageAtomicModelInfo::DeleteRwObject_Reversed();
}
void CDamageAtomicModelInfo::DeleteRwObject_Reversed()
{
    if (m_pDamagedAtomic) {
        auto pFrame = RpAtomicGetFrame(m_pDamagedAtomic);
        RpAtomicDestroy(m_pDamagedAtomic);
        RwFrameDestroy(pFrame);
        m_pDamagedAtomic = nullptr;
    }

    CAtomicModelInfo::DeleteRwObject();
}

RwObject* CDamageAtomicModelInfo::CreateInstance()
{
    return CDamageAtomicModelInfo::CreateInstance_Reversed();
}
RwObject* CDamageAtomicModelInfo::CreateInstance_Reversed()
{
    if (!CDamageAtomicModelInfo::ms_bCreateDamagedVersion)
        return CAtomicModelInfo::CreateInstance();

    if (!m_pDamagedAtomic)
        return nullptr;

    auto pAtomic = RpAtomicClone(m_pDamagedAtomic);
    auto pFrame = RwFrameCreate();
    RpAtomicSetFrame(pAtomic, pFrame);
    return reinterpret_cast<RwObject*>(pAtomic);
}

RwObject* CDamageAtomicModelInfo::CreateInstance(RwMatrix* matrix)
{
    return CDamageAtomicModelInfo::CreateInstance_Reversed(matrix);
}
RwObject* CDamageAtomicModelInfo::CreateInstance_Reversed(RwMatrix* matrix)
{
    if (!CDamageAtomicModelInfo::ms_bCreateDamagedVersion)
        return CAtomicModelInfo::CreateInstance(matrix);

    if (!m_pDamagedAtomic)
        return nullptr;

    auto pAtomic = RpAtomicClone(m_pDamagedAtomic);
    auto pFrame = RwFrameCreate();
    memcpy(RwFrameGetMatrix(pFrame), matrix, sizeof(*RwFrameGetMatrix(pFrame)));
    RpAtomicSetFrame(pAtomic, pFrame);
    return reinterpret_cast<RwObject*>(pAtomic);
}

void CDamageAtomicModelInfo::SetDamagedAtomic(RpAtomic* atomic)
{
    m_pDamagedAtomic = atomic;
    if (CCustomBuildingRenderer::IsCBPCPipelineAttached(atomic))
        CCustomBuildingRenderer::AtomicSetup(atomic);
    else if (CCarFXRenderer::IsCCPCPipelineAttached(atomic))
        CCarFXRenderer::SetCustomFXAtomicRenderPipelinesVMICB(atomic, nullptr);
}
