#include "StdInc.h"

#include "TaskSimpleSlideToCoord.h"
#include "TaskSimpleStandStill.h"

void CTaskSimpleSlideToCoord::InjectHooks() {
    RH_ScopedClass(CTaskSimpleSlideToCoord);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedOverloadedInstall(Constructor, "NoAnim", 0x66C3E0, CTaskSimpleSlideToCoord*(CTaskSimpleSlideToCoord::*)(CVector const&, float, float));
    RH_ScopedOverloadedInstall(Constructor, "Anim", 0x66C450, CTaskSimpleSlideToCoord*(CTaskSimpleSlideToCoord::*)(CVector const&, float, float, char const*, char const*, int32, float, bool, int32));
    RH_ScopedInstall(Destructor, 0x66C4C0);
    RH_ScopedInstall(Clone_Reversed, 0x66D300);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x66C4D0);
    RH_ScopedInstall(ProcessPed_Reversed, 0x66C4E0);
}

// 0x66C3E0
CTaskSimpleSlideToCoord::CTaskSimpleSlideToCoord(CVector const& pos, float aimingRotation, float radius) :
    m_SlideToPos{ pos },
    m_fAimingRotation{ aimingRotation },
    m_fRadius{ radius },
    m_bHasAnim{ false }
{
    assert(0 && "where call to parent CTaskSimpleRunNamedAnim?");
}

// 0x66C450
CTaskSimpleSlideToCoord::CTaskSimpleSlideToCoord(CVector const& slideToPos, float aimingRotation, float radius, char const* animBlockName, char const* animGroupName, uint32 animFlags, float animBlendDelta, bool isActiveSequence, uint32 endTime) :
    CTaskSimpleRunNamedAnim{ animBlockName, animGroupName, animFlags, animBlendDelta, endTime, false, isActiveSequence, false, false },
    m_SlideToPos{ slideToPos },
    m_fAimingRotation{ aimingRotation },
    m_fRadius{ radius },
    m_bHasAnim{ false }
{
}

// 0x66D300
CTask* CTaskSimpleSlideToCoord::Clone() {
    return m_bHasAnim ?
        new CTaskSimpleSlideToCoord{m_SlideToPos, m_fAimingRotation, m_fRadius, m_animName, m_animGroupName, m_animFlags, m_blendDelta, !!m_bRunInSequence, m_endTime } :
        new CTaskSimpleSlideToCoord{m_SlideToPos, m_fAimingRotation, m_fRadius};
}

// 0x66C4D0
bool CTaskSimpleSlideToCoord::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return !m_bHasAnim || CTaskSimpleAnim::MakeAbortable(ped, priority, event);
}

// 0x66C4E0
bool CTaskSimpleSlideToCoord::ProcessPed(CPed* ped) {
    const bool hasSuccessfullyProcessedRunAnim = m_bHasAnim ? CTaskSimpleRunNamedAnim::ProcessPed(ped) : true; // Yeah could be simplified, but this is easier to understand.

    if (m_endTime == (uint32)-1) {
        if (m_bHasAnim) {
            if (hasSuccessfullyProcessedRunAnim) {
                m_endTime = CTimer::GetTimeInMS() + 500;
            }
        } else {
            m_endTime = CTimer::GetTimeInMS() + 2000;
        }
    }

    // The same standstill stuff has been used in `CTaskSimpleWaitUntilPedIsOutCar` as well.. weird.
    if (m_bShouldProcessStandStill) {
        m_bShouldProcessStandStill = false;

        CTaskSimpleStandStill standStillTask{ STAND_STILL_TIME };
        standStillTask.ProcessPed(ped);
        if (ped->IsPlayer()) {
            ped->GetTaskManager().GetTaskPrimary(TASK_PRIMARY_DEFAULT)->MakeAbortable(ped, ABORT_PRIORITY_IMMEDIATE, nullptr);
        }
        ped->m_fAimingRotation = m_fAimingRotation;
    }

    const auto pedToSlidePosDir = (m_SlideToPos - ped->GetPosition()) * m_fRadius; // Originally they calculated this twice, but thats a waste of performance, so.. :D
    const auto pedToSlidePosDistSq2D = pedToSlidePosDir.SquaredMagnitude2D();
    if (pedToSlidePosDir.SquaredMagnitude2D() < sq(0.05f)) {
        ped->m_vecAnimMovingShiftLocal = CVector2D{};
    } else {
        const auto& pedMat = ped->GetMatrix();
        ped->m_vecAnimMovingShiftLocal = {
            DotProduct(pedToSlidePosDir, pedMat.GetForward()), // Originally Y was calculated first, but I swapped it!
            DotProduct(pedToSlidePosDir, pedMat.GetRight())
        };
    }

    if (m_endTime < CTimer::GetTimeInMS()) {
        return true;
    }

    if (hasSuccessfullyProcessedRunAnim && pedToSlidePosDistSq2D < sq(0.05f)) {
        if (std::abs(ped->m_fCurrentRotation - ped->m_fAimingRotation) < 0.1f) {
            return true;
        }
    }

    return false;
}
