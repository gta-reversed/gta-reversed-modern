#pragma once

#include "TaskComplex.h"

class CPed;
class CTaskComplexKillPedFromBoat;

class NOTSA_EXPORT_VTABLE CTaskComplexKillPedFromBoat : public CTaskComplex {
public:
    CPed* m_Ped{};
public:
    static void InjectHooks();

    static constexpr auto Type = eTaskType::TASK_KILL_PED_FROM_BOAT;

    CTaskComplexKillPedFromBoat(CPed * ped);
    ~CTaskComplexKillPedFromBoat();

    virtual CTask* Clone() const override;
    virtual eTaskType GetTaskType() const override { return Type; }
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);
 
private: // Wrappers for hooks
    // 0x6227C0
    CTaskComplexKillPedFromBoat* Constructor(CPed* ped) {
        this->CTaskComplexKillPedFromBoat::CTaskComplexKillPedFromBoat(ped);
        return this;
    }
    // 0x622830
    CTaskComplexKillPedFromBoat* Destructor() {
        this->CTaskComplexKillPedFromBoat::~CTaskComplexKillPedFromBoat();
        return this;
    }
};
