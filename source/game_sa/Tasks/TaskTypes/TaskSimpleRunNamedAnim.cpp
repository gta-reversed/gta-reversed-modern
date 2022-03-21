#include "StdInc.h"
#include "TaskSimpleRunNamedAnim.h"


void CTaskSimpleRunNamedAnim::InjectHooks() {
    RH_ScopedClass(CTaskSimpleRunNamedAnim);
    RH_ScopedCategory(); // TODO: Change this to the appropriate category!

    RH_ScopedOverloadedInstall(Constructor, "Default", 0x6674B0, CTaskSimpleRunNamedAnim*(CTaskSimpleRunNamedAnim::*)());
    RH_ScopedOverloadedInstall(Constructor, "Anim", 0x61A990, CTaskSimpleRunNamedAnim*(CTaskSimpleRunNamedAnim::*)(char const*, char const*, int32, float, int32, bool, bool, bool, bool));
    RH_ScopedInstall(Destructor, 0x61BF10);

    // RH_ScopedGlobalInstall(FinishRunAnimMovePedCB, 0x61AAA0);

    // RH_ScopedInstall(StartAnim, 0x61BB10);
    // RH_ScopedInstall(Clone_Reversed, 0x61B770);
    RH_ScopedInstall(GetTaskType_Reversed, 0x61AA90);
    // RH_ScopedInstall(ProcessPed_Reversed, 0x61BF20);
}

// 0x6674B0
CTaskSimpleRunNamedAnim::CTaskSimpleRunNamedAnim() :
    CTaskSimpleAnim{ false }
{
    // Rest done in header
}

// 0x61A990
CTaskSimpleRunNamedAnim::CTaskSimpleRunNamedAnim(
    const char* animName,
    const char* animGroupName,
    uint32 animFlags,
    float blendDelta,
    uint32 endTime,
    bool bDontInterrupt,
    bool bRunInSequence,
    bool bOffsetPed,
    bool bHoldLastFrame
) :
    CTaskSimpleAnim{bHoldLastFrame, bDontInterrupt, bRunInSequence, bOffsetPed},

    m_blendDelta{blendDelta},
    m_endTime{endTime},
    m_animFlags{animFlags}
{
    strcpy_s(m_animName, animName);
    strcpy_s(m_animGroupName, animGroupName);
    if (const auto block = CAnimManager::GetAnimationBlock(m_animGroupName)) {
        m_pAnimHierarchy = CAnimManager::GetAnimation(m_animName, block);
    }
}

bool CTaskSimpleRunNamedAnim::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x61BF20>(this, ped);
}
