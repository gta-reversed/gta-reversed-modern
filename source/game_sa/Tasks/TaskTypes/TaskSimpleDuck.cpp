#include "StdInc.h"

#include "TaskSimpleDuck.h"

void CTaskSimpleDuck::InjectHooks() {
    RH_ScopedClass(CTaskSimpleDuck);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x691FC0);
    RH_ScopedInstall(Destructor, 0x692030);
    RH_ScopedInstall(CanPedDuck, 0x692610, { .reversed = false });
    //RH_ScopedInstall(ControlDuckMove, 0x6923F0, { .reversed = false }); // todo
    RH_ScopedInstall(IsTaskInUseByOtherTasks, 0x61C3D0, { .reversed = false });
    RH_ScopedVirtualInstall(MakeAbortable, 0x692100, { .reversed = false });
    RH_ScopedVirtualInstall(ProcessPed, 0x694390, { .reversed = false });
}

// 0x691FC0
CTaskSimpleDuck::CTaskSimpleDuck(eDuckControlTypes DuckControlType, uint16 nLengthOfDuck, int16 nUseShotsWhizzingEvents) : CTaskSimple() {
    m_bNeedToSetDuckFlag   = true;
    m_bIsInControl         = true;
    m_bIsFinished          = false;
    m_bIsAborting          = false;
    m_vecMoveCommand       = CVector2D();
    m_nDuckControlType     = DuckControlType;
    m_nCountDownFrames     = -1;
    m_nStartTime           = CTimer::GetTimeInMS();
    m_pDuckAnim            = nullptr;
    m_pMoveAnim            = nullptr;
    m_nLengthOfDuck        = nLengthOfDuck;
    m_nShotWhizzingCounter = nUseShotsWhizzingEvents;
}

// 0x692030
CTaskSimpleDuck::~CTaskSimpleDuck() {
    if (m_pDuckAnim) {
        m_pDuckAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        if (m_pDuckAnim->m_BlendAmount > 0.0f && m_pDuckAnim->m_BlendDelta >= 0.0f && (m_pDuckAnim->m_Flags & ANIMATION_PARTIAL) != 0)
            m_pDuckAnim->m_BlendDelta = -8.0f;
    }

    if (m_pMoveAnim) {
        m_pMoveAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        if (m_pMoveAnim->m_BlendAmount > 0.0f && m_pMoveAnim->m_BlendDelta >= 0.0f)
            m_pMoveAnim->m_BlendDelta = -8.0f;
    }
}

// 0x692610
bool CTaskSimpleDuck::CanPedDuck(CPed* ped) {
    return plugin::CallAndReturn<bool, 0x692610, CPed*>(ped);
}

// 0x6923F0
bool CTaskSimpleDuck::ControlDuckMove(float moveSpeedX, float moveSpeedY) {
    return plugin::CallMethodAndReturn<bool, 0x6923F0, CTaskSimpleDuck*, float, float>(this, moveSpeedX, moveSpeedY);
}

// 0x61C3D0
bool CTaskSimpleDuck::IsTaskInUseByOtherTasks() {
    return plugin::CallMethodAndReturn<bool, 0x61C3D0, CTaskSimpleDuck*>(this);
}

// 0x692100
bool CTaskSimpleDuck::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x692100, CTaskSimpleDuck*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

// 0x694390
bool CTaskSimpleDuck::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x694390, CTaskSimpleDuck*, CPed*>(this, ped);
}

CTaskSimpleDuck* CTaskSimpleDuck::Constructor(eDuckControlTypes DuckControlType, uint16 nLengthOfDuck, int16 nUseShotsWhizzingEvents) {
    this->CTaskSimpleDuck::CTaskSimpleDuck(DuckControlType, nLengthOfDuck, nUseShotsWhizzingEvents);
    return this;
}

CTaskSimpleDuck* CTaskSimpleDuck::Destructor() {
    this->CTaskSimpleDuck::~CTaskSimpleDuck();
    return this;
}

bool CTaskSimpleDuck::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return CTaskSimpleDuck::MakeAbortable(ped, priority, event);
}

bool CTaskSimpleDuck::ProcessPed_Reversed(CPed* ped) {
    return CTaskSimpleDuck::ProcessPed(ped);
}

// 0x6924B0
void CTaskSimpleDuck::ForceStopMove() {
    m_bIsInControl = true;
    m_vecMoveCommand.y = 0.f;
}

void CTaskSimpleDuck::SetDuckTimer(uint16 lengthOfDuck) {
    if (m_nDuckControlType != DUCK_SCRIPT_CONTROLLED) {
        m_nStartTime = CTimer::GetTimeInMS();
        m_nLengthOfDuck = lengthOfDuck;
    }
}
