#pragma once

#include "TaskSimple.h"

class CTask;
class CEvent;
class CPed;
class CTaskSimpleAffectSecondaryBehaviour;

/*!
 *  Keep trying until the given secondary task is done/can be aborted
 *  using `ABORT_PRIORITY_URGENT` and then add the given task as a
 *  secondary task as the specified type.
 */
class NOTSA_EXPORT_VTABLE CTaskSimpleAffectSecondaryBehaviour : public CTaskSimple {
public:
    bool           m_bAdd;
    eSecondaryTask m_SecTaskType;
    CTask*         m_Task;

public:
    constexpr static auto Type = TASK_SIMPLE_AFFECT_SECONDARY_BEHAVIOUR;

    CTaskSimpleAffectSecondaryBehaviour(bool add, eSecondaryTask secondaryTaskType, CTask* task);

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleAffectSecondaryBehaviour(m_bAdd, m_SecTaskType, m_Task); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return false; }
    bool ProcessPed(CPed* ped) override;

    static void InjectHooks();
    CTaskSimpleAffectSecondaryBehaviour* Constructor(bool add, eSecondaryTask secondaryTaskType, CTask* a4) { this->CTaskSimpleAffectSecondaryBehaviour::CTaskSimpleAffectSecondaryBehaviour(add, secondaryTaskType, a4); return this; }
};
