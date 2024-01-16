#pragma once

#include "Vector.h"
#include "TaskComplex.h"

class CPed;
class CTaskComplexEvasiveDiveAndGetUp;
class CEntity;
class CEvent;

class NOTSA_EXPORT_VTABLE CTaskComplexEvasiveDiveAndGetUp : public CTaskComplex {
public:
    static constexpr auto Type = eTaskType::TASK_COMPLEX_EVASIVE_DIVE_AND_GET_UP;

    static void InjectHooks();

    CTaskComplexEvasiveDiveAndGetUp(CVehicle* target, int32 unconsciousTime, const CVector& diveDir, bool bAchieveHeadingFirst);
    ~CTaskComplexEvasiveDiveAndGetUp();

    CTask* CreateSubTask(eTaskType tt);

    CTask*    Clone() const override { return new CTaskComplexEvasiveDiveAndGetUp{ *this }; }
    eTaskType GetTaskType() const override { return Type; }
    bool      MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, CEvent const* event = nullptr) override;
    CTask*    CreateNextSubTask(CPed* ped) override;
    CTask*    CreateFirstSubTask(CPed* ped) override;
    CTask*    ControlSubTask(CPed* ped) override { return m_pSubTask; }

private: // Wrappers for hooks
    // 0x6536B0
    CTaskComplexEvasiveDiveAndGetUp* Constructor(CVehicle* a, int32 b, const CVector& c, bool d) {
        this->CTaskComplexEvasiveDiveAndGetUp::CTaskComplexEvasiveDiveAndGetUp(a, b, c, d);
        return this;
    }

    // 0x653740
    CTaskComplexEvasiveDiveAndGetUp* Destructor() {
        this->CTaskComplexEvasiveDiveAndGetUp::~CTaskComplexEvasiveDiveAndGetUp();
        return this;
    }

public:
    CVehicle* m_TargetVeh{};
    int32     m_UnconsciousTime{};
    CVector   m_DiveDir{};
    bool      m_bAchieveHeadingFirst{};
};
