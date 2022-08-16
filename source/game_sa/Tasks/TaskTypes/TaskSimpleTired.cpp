#include "StdInc.h"
#include "TaskSimpleTired.h"

void CTaskSimpleTired::InjectHooks() {
    RH_ScopedClass(CTaskSimpleTired);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x630F20);
    RH_ScopedInstall(Destructor, 0x630F60);

    RH_ScopedInstall(StartAnim, 0x630F70);

    RH_ScopedVirtualInstall2(Clone, 0x636180);
    RH_ScopedVirtualInstall2(GetTaskType, 0x630F50);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x630FF0);
    RH_ScopedVirtualInstall2(ProcessPed, 0x637970);
}

// 0x630F20
CTaskSimpleTired::CTaskSimpleTired(uint32 tiredDurationMs) :
    m_tiredDurationMs{ tiredDurationMs }
{
}

CTaskSimpleTired::CTaskSimpleTired(const CTaskSimpleTired& o) :
    CTaskSimpleTired{o.m_tiredDurationMs}
{
}

// 0x630F70
void CTaskSimpleTired::StartAnim(CPed* ped) {
    ped->SetMoveState(PEDMOVE_STILL);
    ped->SetMoveAnim();
    m_animStartMs = CTimer::GetTimeInMS();
    m_tiredDurationCpy = m_tiredDurationMs;
    m_animHasStarted = true;
    m_tiredAnim = CAnimManager::BlendAnimation(
        ped->m_pRwClump,
        FindPlayerPed() == ped && CClothes::GetDefaultPlayerMotionGroup() == ANIM_GROUP_FAT ? ANIM_GROUP_FAT_TIRED : ANIM_GROUP_DEFAULT,
        ANIM_ID_IDLE_TIRED,
        4.f
    );
}

// 0x630FF0
bool CTaskSimpleTired::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    if (m_tiredAnim && m_tiredAnim == RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_IDLE_TIRED)) {
        m_tiredAnim->m_fBlendDelta = -4.f;
    }
    return true;
}

// 0x637970
bool CTaskSimpleTired::ProcessPed(CPed* ped) {
    if (!m_tiredAnim) {
        StartAnim(ped);
    }

    if (!m_animHasStarted) {
        return false;
    }

    if (m_needsToStartAnim) {
        m_animStartMs = CTimer::GetTimeInMS();
        m_needsToStartAnim = true;
    }

    if (CTimer::GetTimeInMS() < m_animStartMs + m_tiredDurationCpy) {
        return false;
    }

    MakeAbortable(ped, ABORT_PRIORITY_LEISURE, nullptr);

    return true;
}
