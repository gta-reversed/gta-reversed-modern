#include "StdInc.h"
#include "TaskComplexSeekEntity.h"

// 0x493730
template<typename T>
CTaskComplexSeekEntity<T>::CTaskComplexSeekEntity(
    CEntity* entity, // May be null
    int32    taskTimer2Interval,
    int32    taskTimer1Interval,
    float    maxEntityDist2D,
    float    unk1,
    float    unk2,
    bool     flag0,
    bool     flag1
) :
    m_entity{entity},
    m_taskIntervals{taskTimer1Interval, taskTimer2Interval},
    m_unk1{unk1},
    m_unk2{unk2},
    m_flag0{flag0},
    m_flag1{flag1}
{
    CEntity::SafeRegisterRef(m_entity);
}

// 0x493890
template<typename T>
CTaskComplexSeekEntity<T>::~CTaskComplexSeekEntity() {
    CEntity::SafeCleanUpRef(m_entity);
}

template<typename T>
CTask* CTaskComplexSeekEntity<T>::CreateSubTask(eTaskType type, CPed* ped) {
    return nullptr;
}

// 0x495FB0
template<typename T>
CTask* CTaskComplexSeekEntity<T>::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x495FB0, CTaskComplexSeekEntity<T>*>(this);
}

// 0x493800
template<typename T>
eTaskType CTaskComplexSeekEntity<T>::GetTaskType() {
    return plugin::CallMethodAndReturn<eTaskType, 0x493800, CTaskComplexSeekEntity<T>*>(this);
}

// 0x493810
template<typename T>
bool CTaskComplexSeekEntity<T>::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x493810, CTaskComplexSeekEntity<T>*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x496080
template<typename T>
CTask* CTaskComplexSeekEntity<T>::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x496080, CTaskComplexSeekEntity<T>*, CPed*>(this, ped);
}

// 0x496600
template<typename T>
CTask* CTaskComplexSeekEntity<T>::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x496600, CTaskComplexSeekEntity<T>*, CPed*>(this, ped);
}

// 0x496760
template<typename T>
CTask* CTaskComplexSeekEntity<T>::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x496760, CTaskComplexSeekEntity<T>*, CPed*>(this, ped);
}

void CTaskComplexSeekEntity_CEntitySeekPosCalculatorRadiusAngleOffset::InjectHooks() {
    RH_ScopedNamedClass(CTaskComplexSeekEntity_CEntitySeekPosCalculatorRadiusAngleOffset, "<CEntitySeekPosCalculatorRadiusAngleOffset>");
    RH_ScopedCategory("Tasks/TaskTypes/CTaskComplexSeekEntity");

    RH_ScopedInstall(Constructor, 0x493730);
    RH_ScopedInstall(Destructor, 0x493890);

    RH_ScopedInstall(Constructor, 0x493730);
    RH_ScopedInstall(Destructor, 0x493890);

    RH_ScopedVirtualInstall2(Clone, 0x495FB0, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(GetTaskType, 0x493800, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(MakeAbortable, 0x493810, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(CreateNextSubTask, 0x496080, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(CreateFirstSubTask, 0x496600, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(ControlSubTask, 0x496760, { .enabled = false, .locked = true });
}

void CTaskComplexSeekEntity_CEntitySeekPosCalculatorStandard::InjectHooks() {
    RH_ScopedNamedClass(CTaskComplexSeekEntity_CEntitySeekPosCalculatorStandard, "<CEntitySeekPosCalculatorStandard>");
    RH_ScopedCategory("Tasks/TaskTypes/CTaskComplexSeekEntity");


    RH_ScopedInstall(Constructor, 0x46AC10, { .enabled = false, .locked = true });
    RH_ScopedInstall(Destructor, 0x46AD50, { .enabled = false, .locked = true });

    RH_ScopedVirtualInstall2(Clone, 0x46EF50, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(GetTaskType, 0x46ACE0, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(MakeAbortable, 0x46ACF0, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(CreateNextSubTask, 0x46EFF0, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(CreateFirstSubTask, 0x46F6A0, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(ControlSubTask, 0x46F800, { .enabled = false, .locked = true });
}

void CTaskComplexSeekEntity_CEntitySeekPosCalculatorXYOffset::InjectHooks() {
    RH_ScopedNamedClass(CTaskComplexSeekEntity_CEntitySeekPosCalculatorXYOffset, "<CEntitySeekPosCalculatorXYOffset>");
    RH_ScopedCategory("Tasks/TaskTypes/CTaskComplexSeekEntity");

    RH_ScopedInstall(Constructor, 0x661DC0, { .enabled = false, .locked = true });
    RH_ScopedInstall(Destructor, 0x661F30, { .enabled = false, .locked = true });

    RH_ScopedInstall(CreateSubTask, 0x496270, { .enabled = false, .locked = true });

    RH_ScopedVirtualInstall2(Clone, 0x664AF0, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(GetTaskType, 0x661EA0, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(MakeAbortable, 0x661EB0, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(CreateNextSubTask, 0x665080, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(CreateFirstSubTask, 0x665600, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(ControlSubTask, 0x665760, { .enabled = false, .locked = true });

}
