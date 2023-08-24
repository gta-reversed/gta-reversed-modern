#include "StdInc.h"
#include "TaskInteriorUseInfo.h"
#include <InteriorInfo_t.h>
#include <Interior_c.h>

void CTaskInteriorUseInfo::InjectHooks() {
    RH_ScopedVirtualClass(CTaskInteriorUseInfo, 0x8702e8, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x675A50);
    RH_ScopedInstall(Destructor, 0x675A90);

    RH_ScopedVMTInstall(Clone, 0x675AB0);
    RH_ScopedVMTInstall(GetTaskType, 0x675A80);
    RH_ScopedVMTInstall(MakeAbortable, 0x675B30);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x676880, {.reversed = false});
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x675B60, {.reversed = false});
    RH_ScopedVMTInstall(ControlSubTask, 0x675C00);
}

// 0x675A50
CTaskInteriorUseInfo::CTaskInteriorUseInfo(InteriorInfo_t* iinfo, Interior_c* i, int32 duration, bool bDoInstantly) :
    m_Int{i},
    m_IntInfo{iinfo},
    m_Dur{duration},
    m_bDoInstantly{bDoInstantly}
{
}

// 0x675AB0
CTaskInteriorUseInfo::CTaskInteriorUseInfo(const CTaskInteriorUseInfo& o) :
    CTaskInteriorUseInfo{
        o.m_IntInfo,
        o.m_Int,
        o.m_Dur,
        o.m_bDoInstantly
    }
{
}

// 0x675A90
CTaskInteriorUseInfo::~CTaskInteriorUseInfo() {
    if (m_IntInfo) {
        m_IntInfo->m_goToInfoTaskCreated = false;
    }
}

// 0x675B30
bool CTaskInteriorUseInfo::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    if (m_IntInfo->m_entityIgnoredCollision) {
        ped->m_pEntityIgnoredCollision = nullptr;
    }
    return m_pSubTask->MakeAbortable(ped, priority, event);
}

// 0x676880
CTask* CTaskInteriorUseInfo::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x676880, CTaskInteriorUseInfo*, CPed*>(this, ped);
}

// 0x675B60
CTask* CTaskInteriorUseInfo::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn< CTask *, 0x675B60, CTaskInteriorUseInfo*, CPed *>(this, ped);

    //if (!m_IntInfo) {
    //    return nullptr;
    //}
    //m_IntInfo->m_goToInfoTaskCreated = true;
    //return new CTaskInteriorGoToInfo{}; // TODO: Missing `CTaskInteriorGoToInfo`
}

// 0x675C00
CTask* CTaskInteriorUseInfo::ControlSubTask(CPed* ped) {
    if (m_IntInfo) {
        if (const auto e = m_IntInfo->m_entityIgnoredCollision) {
            ped->m_pEntityIgnoredCollision = e;
        }
    }
    return m_pSubTask;
}
