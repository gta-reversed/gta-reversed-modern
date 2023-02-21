/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "TaskTimer.h"
#include "TaskComplex.h"

class NOTSA_EXPORT_VTABLE CTaskComplexKillPedOnFoot : public CTaskComplex {
public:
    uint8      m_bit_1 : 1;
    uint8      m_bit_2 : 1;
    uint8      m_bit_3 : 1;
    uint8      m_bit_4 : 1;
    uint8      m_bit_5 : 1;
    uint8      m_bit_6 : 1;
    uint8      m_bit_7 : 1;
    uint8      m_bit_8 : 1;
    CPed*      m_target;
    int32      m_pedFlags;
    int32      m_actionDelay;
    int32      m_actionChance;
    uint8      field_20;
    uint32     m_startTime;
    uint32     m_time;
    CTaskTimer m_timer;

public:
    static constexpr auto Type = TASK_COMPLEX_KILL_PED_ON_FOOT;

    CTaskComplexKillPedOnFoot(CPed* target, int32 time = -1, int32 pedFlags = 0, int32 delay = 0, int32 chance = 0, int8 a7 = true);
    ~CTaskComplexKillPedOnFoot() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexKillPedOnFoot(m_target, m_time, m_pedFlags, m_actionDelay, m_actionChance, field_20); }
    bool   MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(int32 taskId, CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexKillPedOnFoot* Constructor(CPed* target, int32 time, int32 pedFlags, int32 delay, int32 chance, int8 a7);
};

VALIDATE_SIZE(CTaskComplexKillPedOnFoot, 0x38);
