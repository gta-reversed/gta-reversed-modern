#pragma once

#include "Vector.h"
#include "TaskComplex.h"
#include "Vehicle.h"

class CTask;
class CEvent;
class CPed;
class CEntity;

class NOTSA_EXPORT_VTABLE CTaskComplexEvasiveDiveAndGetUp : public CTaskComplex {
public:
    static constexpr auto Type = eTaskType::TASK_COMPLEX_EVASIVE_DIVE_AND_GET_UP;

    static void InjectHooks();

    CTaskComplexEvasiveDiveAndGetUp(CVehicle* diveFrom, int32 unconsciousTime, const CVector& diveDir, bool bAchieveHeadingFirst);
    CTaskComplexEvasiveDiveAndGetUp(const CTaskComplexEvasiveDiveAndGetUp&);
    ~CTaskComplexEvasiveDiveAndGetUp() override = default;

    CTask* CreateSubTask(eTaskType taskType);

    CTask*    Clone() const override { return new CTaskComplexEvasiveDiveAndGetUp{ *this }; }
    eTaskType GetTaskType() const override { return Type; }
    bool      MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, CEvent const* event = nullptr) final override;
    CTask*    CreateNextSubTask(CPed* ped) override;
    CTask*    CreateFirstSubTask(CPed* ped) override;
    CTask*    ControlSubTask(CPed* ped) override { return m_pSubTask; }

private: // Wrappers for hooks
    // 0x6536B0
    CTaskComplexEvasiveDiveAndGetUp* Constructor(CVehicle* e, int32 nTimeOnGround, CVector* pvDirection, bool b) {
        this->CTaskComplexEvasiveDiveAndGetUp::CTaskComplexEvasiveDiveAndGetUp(e, nTimeOnGround, *pvDirection, b);
        return this;
    }

    // 0x653740
    CTaskComplexEvasiveDiveAndGetUp* Destructor() {
        this->CTaskComplexEvasiveDiveAndGetUp::~CTaskComplexEvasiveDiveAndGetUp();
        return this;
    }

protected:
    CVehicle* m_TargetVeh{};
    int32     m_UnconsciousTime{};
    CVector   m_DiveDir{};
    bool      m_bAchieveHeadingFirst{};
};
