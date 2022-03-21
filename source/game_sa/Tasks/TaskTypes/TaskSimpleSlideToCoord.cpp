#include "StdInc.h"
#include "TaskSimpleSlideToCoord.h"
#include <TaskSimpleStandStill.h>

void CTaskSimpleSlideToCoord::InjectHooks() {
    RH_ScopedClass(CTaskSimpleSlideToCoord);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedOverloadedInstall(Constructor, "NoAnim", 0x66C3E0, CTaskSimpleSlideToCoord*(CTaskSimpleSlideToCoord::*)(CVector const&, float, float));
    RH_ScopedOverloadedInstall(Constructor, "Anim", 0x66C450, CTaskSimpleSlideToCoord*(CTaskSimpleSlideToCoord::*)(CVector const&, float, float, char const*, char const*, int32, float, bool, int32));
    RH_ScopedInstall(Destructor, 0x66C4C0);

    RH_ScopedInstall(Clone_Reversed, 0x66D300);
    RH_ScopedInstall(GetTaskType_Reversed, 0x66C440);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x66C4D0);
    RH_ScopedInstall(ProcessPed_Reversed, 0x66C4E0);
}

// 0x66C3E0
CTaskSimpleSlideToCoord::CTaskSimpleSlideToCoord(CVector const& pos, float aimingRotation, float radius) :
    m_slideToPos{ pos },
    m_aimingRotation{ aimingRotation },
    m_radius{ radius },
    m_hasAnim{ false }
{
}

// 0x66C450
CTaskSimpleSlideToCoord::CTaskSimpleSlideToCoord(CVector const& slideToPos, float aimingRotation, float radius, char const* animBlockName, char const* animGroupName, uint32 animFlags, float animBlendDelta, bool isActiveSequence, uint32 endTime) :
    CTaskSimpleRunNamedAnim{ animBlockName, animGroupName, animFlags, animBlendDelta, endTime, false, isActiveSequence, false, false },
    m_slideToPos{ slideToPos },
    m_aimingRotation{ aimingRotation },
    m_radius{ radius },
    m_hasAnim{ false }
{
}

// 0x66D300
CTask* CTaskSimpleSlideToCoord::Clone() {
    return m_hasAnim ?
        new CTaskSimpleSlideToCoord{ m_slideToPos, m_aimingRotation, m_radius, m_animName, m_animGroupName, m_animFlags, m_blendDelta, !!m_bRunInSequence, m_endTime } :
        new CTaskSimpleSlideToCoord{ m_slideToPos, m_aimingRotation, m_radius };
}

// 0x66C4D0
bool CTaskSimpleSlideToCoord::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return !m_hasAnim || CTaskSimpleAnim::MakeAbortable(ped, priority, event);
}

// 0x66C4E0
bool CTaskSimpleSlideToCoord::ProcessPed(CPed* ped) {
    const bool hasSuccessfullyProcessedRunAnim = m_hasAnim ? CTaskSimpleRunNamedAnim::ProcessPed(ped) : true; // Yeah could be simplified, but this is easier to understand.

    if (m_endTime == (uint32)-1) {
        if (m_hasAnim) {
            if (hasSuccessfullyProcessedRunAnim) {
                m_endTime = CTimer::GetTimeInMS() + 500;
            }
        } else {
            m_endTime = CTimer::GetTimeInMS() + 2000;
        }
    }

    // The same standstill stuff has been used in `CTaskSimpleWaitUntilPedIsOutCar` as well.. weird.
    if (m_shouldProcessStandStill) {
        m_shouldProcessStandStill = false;

        CTaskSimpleStandStill standStillTask{ STAND_STILL_TIME };
        standStillTask.ProcessPed(ped);
        if (ped->IsPlayer()) {
            ped->GetTaskManager().GetTaskPrimary(TASK_PRIMARY_DEFAULT)->MakeAbortable(ped, ABORT_PRIORITY_IMMEDIATE, nullptr);
        }
        ped->m_fAimingRotation = m_aimingRotation;
    }

    const auto pedToSlidePosDir = (m_slideToPos - ped->GetPosition()) * m_radius; // Origianlly they calculated this twice, but thats a waste of performance, so.. :D
    const auto pedToSlidePosDistSq2D = pedToSlidePosDir.SquaredMagnitude2D();
    if (pedToSlidePosDir.SquaredMagnitude2D() < 0.05f * 0.05f) {
        ped->m_vecAnimMovingShiftLocal = CVector2D{};
    } else {
        auto& pedMat = ped->GetMatrix();
        ped->m_vecAnimMovingShiftLocal = {
            DotProduct(pedToSlidePosDir, pedMat.GetForward()), // Originally Y was calculated first, but I swapped it!
            DotProduct(pedToSlidePosDir, pedMat.GetRight())
        }; 
    }

    if (m_endTime < CTimer::GetTimeInMS()) {
        return true;
    }

    if (hasSuccessfullyProcessedRunAnim && pedToSlidePosDistSq2D < 0.05f * 0.05f) {
        if (std::abs(ped->m_fCurrentRotation - ped->m_fAimingRotation) < 0.1f) {
            return true;
        }
    }

    return false;
}
