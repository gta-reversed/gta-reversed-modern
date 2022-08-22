#pragma once

#include "TaskTimer.h"
#include "TaskSimple.h"

class CPed;
class CEvent;
class CTaskSimplePlayerOnFire;

class NOTSA_EXPORT_VTABLE CTaskSimplePlayerOnFire : public CTaskSimple {

public:
    CTaskTimer m_Timer;
    bool m_bAddedDamageEvent;

public:
    constexpr static auto Type = TASK_SIMPLE_PLAYER_ON_FIRE;

    CTaskSimplePlayerOnFire() = default;  // 0x633560;
    ~CTaskSimplePlayerOnFire() = default; // 0x6335B0

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimplePlayerOnFire(); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return false; }
    bool ProcessPed(CPed* ped) override;

    static void InjectHooks();
    CTaskSimplePlayerOnFire* Constructor() { this->CTaskSimplePlayerOnFire::CTaskSimplePlayerOnFire(); return this; }
    CTaskSimplePlayerOnFire* Destructor() { this->CTaskSimplePlayerOnFire::~CTaskSimplePlayerOnFire(); return this; }
};
VALIDATE_SIZE(CTaskSimplePlayerOnFire, 0x18);
