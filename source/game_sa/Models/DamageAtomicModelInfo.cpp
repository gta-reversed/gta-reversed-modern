#include "StdInc.h"

#include "DamageAtomicModelInfo.h"
#include "CustomBuildingRenderer.h"
#include "CarFXRenderer.h"

bool& CDamageAtomicModelInfo::ms_bCreateDamagedVersion = *(bool*)0xA9B0B0;

void CDamageAtomicModelInfo::InjectHooks()
{
    RH_ScopedClass(CDamageAtomicModelInfo);
    RH_ScopedCategory("Models");

    RH_ScopedVirtualInstall(Init, 0x4C48B0);
    RH_ScopedVirtualInstall(AsDamageAtomicModelInfoPtr, 0x4C55C0);
    RH_ScopedVirtualInstall(DeleteRwObject, 0x4C49D0);
    // clang moment: RH_ScopedVirtualOverloadedInstall(CreateInstance, "void", 0x4C4960, RwObject * (CDamageAtomicModelInfo::*)());
    // clang moment: RH_ScopedVirtualOverloadedInstall(CreateInstance, "rwmat", 0x4C4910, RwObject * (CDamageAtomicModelInfo::*)(RwMatrix*));

    RH_ScopedInstall(SetDamagedAtomic, 0x4C48D0);
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
        auto frame = RpAtomicGetFrame(m_pDamagedAtomic);
        RpAtomicDestroy(m_pDamagedAtomic);
        RwFrameDestroy(frame);
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

    auto atomic = RpAtomicClone(m_pDamagedAtomic);
    auto frame = RwFrameCreate();
    RpAtomicSetFrame(atomic, frame);
    return reinterpret_cast<RwObject*>(atomic);
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

    auto atomic = RpAtomicClone(m_pDamagedAtomic);
    auto frame = RwFrameCreate();
    memcpy(RwFrameGetMatrix(frame), matrix, sizeof(*RwFrameGetMatrix(frame)));
    RpAtomicSetFrame(atomic, frame);
    return reinterpret_cast<RwObject*>(atomic);
}

void CDamageAtomicModelInfo::SetDamagedAtomic(RpAtomic* atomic)
{
    m_pDamagedAtomic = atomic;
    if (CCustomBuildingRenderer::IsCBPCPipelineAttached(atomic))
    {
        CCustomBuildingRenderer::AtomicSetup(atomic);
    }
    else if (CCarFXRenderer::IsCCPCPipelineAttached(atomic))
    {
        CCarFXRenderer::SetCustomFXAtomicRenderPipelinesVMICB(atomic, nullptr);
    }
}
