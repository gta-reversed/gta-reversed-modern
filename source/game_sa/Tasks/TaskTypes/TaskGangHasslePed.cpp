#include "StdInc.h"

#include "TaskGangHasslePed.h"

void CTaskGangHasslePed::InjectHooks() {
    RH_ScopedClass(CTaskGangHasslePed);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x65FED0);
    RH_ScopedInstall(Destructor, 0x65FF60);
    // RH_ScopedInstall(CreateNextSubTask_Reversed, 0x6642C0);
    // RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x664380);
    // RH_ScopedInstall(ControlSubTask_Reversed, 0x65FFE0);
}

// 0x65FED0
CTaskGangHasslePed::CTaskGangHasslePed(CPed* ped, int32 a3, int32 a4, int32 a5) : CTaskComplex() {
    m_nTime = 0;
    m_nSomeRandomShit = 0;
    m_bFirstSubTaskInitialised = 0;
    byte29 = 0;
    dword10 = a3;
    dword14 = a4;
    m_Ped = ped;
    dword18 = a5;
    m_bAnimationNotDeleted = false;
    CEntity::SafeRegisterRef(m_Ped);
}

// 0x65FF60
CTaskGangHasslePed::~CTaskGangHasslePed() {
    CEntity::SafeCleanUpRef(m_Ped);

    if (m_bAnimationNotDeleted) {
        CAnimManager::RemoveAnimBlockRef(CAnimManager::GetAnimationBlockIndex("gangs"));
        m_bAnimationNotDeleted = false;
    }
}

// 0x6642C0
CTask* CTaskGangHasslePed::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6642C0, CTaskGangHasslePed*, CPed*>(this, ped);
}

// 0x664380
CTask* CTaskGangHasslePed::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x664380, CTaskGangHasslePed*, CPed*>(this, ped);
}

// 0x65FFE0
CTask* CTaskGangHasslePed::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x65FFE0, CTaskGangHasslePed*, CPed*>(this, ped);
}
