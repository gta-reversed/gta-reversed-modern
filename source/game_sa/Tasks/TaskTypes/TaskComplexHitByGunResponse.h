#pragma once

#include "TaskComplex.h"

class CTaskComplexHitByGunResponse : public CTaskComplex {
public:
    int32 m_Direction;

public:
    static constexpr auto Type = TASK_COMPLEX_HIT_BY_GUN_RESPONSE;

    explicit CTaskComplexHitByGunResponse(int32 direction);
    ~CTaskComplexHitByGunResponse() override = default; // 0x631E30

    eTaskType GetTaskType() const override { return Type; } // 0x631DF0
    CTask* Clone() const override { return new CTaskComplexHitByGunResponse(m_Direction); } // 0x636640
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    CTask* CreateNextSubTask(CPed* ped) override { return nullptr; } // 0x631E40
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override { return m_pSubTask; } // 0x631F70

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexHitByGunResponse* Constructor(int32 a1) { this->CTaskComplexHitByGunResponse::CTaskComplexHitByGunResponse(a1); return this; }
    CTaskComplexHitByGunResponse* Destructor() { this->CTaskComplexHitByGunResponse::~CTaskComplexHitByGunResponse(); return this; }
};
