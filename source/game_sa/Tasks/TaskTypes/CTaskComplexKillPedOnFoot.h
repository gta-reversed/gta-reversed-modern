/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplex.h"
#include "CTaskTimer.h"
#include "CTaskComplex.h"

class CTaskComplexKillPedOnFoot : public CTaskComplex {
public:
    std::uint8_t m_bit_1 : 1;
    std::uint8_t m_bit_2 : 1;
    std::uint8_t m_bit_3 : 1;
    std::uint8_t m_bit_4 : 1;
    std::uint8_t m_bit_5 : 1;
    std::uint8_t m_bit_6 : 1;
    std::uint8_t m_bit_7 : 1;
    std::uint8_t m_bit_8 : 1;
    std::uint8_t _pad0[3];
    CPed* m_target;
    std::uint32_t m_pedFlags;
    std::int32_t m_actionDelay;
    std::int32_t m_actionChance;
    std::uint8_t field_20;
    std::uint8_t _pad1[3];
    std::uint32_t m_startTime;
    std::uint32_t m_time;
    CTaskTimer m_timer;

    static void InjectHooks();

    CTaskComplexKillPedOnFoot(CPed* target, std::int32_t time, std::uint32_t pedFlags, std::int32_t delay, std::int32_t chance, std::int8_t a7);
    ~CTaskComplexKillPedOnFoot();
private:
    CTaskComplexKillPedOnFoot* Constructor(CPed* target, std::int32_t time, std::uint32_t pedFlags, std::int32_t delay, std::int32_t chance, std::int8_t a7);
public:
    CTask* Clone() override { return new CTaskComplexKillPedOnFoot(m_target, m_time, m_pedFlags, m_actionDelay, m_actionChance, field_20); }
    eTaskType GetId() override { return TASK_COMPLEX_KILL_PED_ON_FOOT; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    void* CreateSubTask(std::int32_t taskId, CPed* ped);
};

VALIDATE_SIZE(CTaskComplexKillPedOnFoot, 0x38);
