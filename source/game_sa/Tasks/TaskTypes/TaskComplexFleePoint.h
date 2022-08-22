#pragma once

#include "TaskComplex.h"
#include "TaskTimer.h"
#include "Vector.h"

class CTaskSimpleGoToPoint;
class CEvent;
class CPed;

/*!
* Task to make a ped run away from a position ASAP.
*
* Sequence goes like:
* - If in vehicle, TASK_COMPLEX_LEAVE_ANY_CAR
* - TASK_SIMPLE_GO_TO_POINT => Repeat until not in danger or `m_timer` expires
* - TASK_COMPLEX_SEQUENCE
* - TASK_FINISHED
*/
class NOTSA_EXPORT_VTABLE CTaskComplexFleePoint : public CTaskComplex {
public:
    CVector m_vFleePos;     // Position to flee from
    CVector m_vTargetPoint; // The position the ped should go(flee) to
    int32 m_nFleeTime;      // The duration in ms
    CTaskTimer m_Timer;     // Task timer: Started in `ControlSubTask`, if out of time skips to `TASK_COMPLEX_SEQUENCE`
    float m_fSafeDistance;  // The safe distance, once the ped is further away than this, the task is considered done
    bool m_bScream;         // If peds should scream while sprinting away
    bool m_bNewFleePoint;   // New `m_fleeFromPos` was set using `SetFleePosition`

public:
    constexpr static auto Type = TASK_COMPLEX_FLEE_POINT;

    CTaskComplexFleePoint(const CVector& fleePos, bool bScream, float fSafeDistance, int32 fleeTime); // 0x65B390
    ~CTaskComplexFleePoint() override = default; // 0x65B410

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexFleePoint(m_vFleePos, m_bScream, m_fSafeDistance, m_nFleeTime); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    auto CreateSubTask(eTaskType taskType) -> CTask*;
    void SetFleePosition(CVector const& fleePos, float safeDistance, bool scream);
    void ComputeTargetPoint(const CPed* ped);

    static void InjectHooks();
    CTaskComplexFleePoint* Constructor(CVector const& point, bool a3, float radius, int32 timeLimit) { this->CTaskComplexFleePoint::CTaskComplexFleePoint(point, a3, radius, timeLimit); return this; }
    CTaskComplexFleePoint* Destructor() { this->CTaskComplexFleePoint::~CTaskComplexFleePoint(); return this; }
};
VALIDATE_SIZE(CTaskComplexFleePoint, 0x3C);
