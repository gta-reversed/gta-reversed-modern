#include "StdInc.h"

void CTaskComplexAvoidOtherPedWhileWandering::InjectHooks()
{
    HookInstall(0x66A100, &CTaskComplexAvoidOtherPedWhileWandering::Constructor);
}

CTaskComplexAvoidOtherPedWhileWandering::CTaskComplexAvoidOtherPedWhileWandering(CPed* ped, CVector* targetPoint, std::int32_t moveState)
{
    m_ped = ped;
    field_1C = *targetPoint;
    field_28 = *targetPoint;
    m_moveState = moveState;
    m_ped = m_ped;
    m_flag1 = false;
    m_flag2 = false;
    m_flag3 = false;
    m_flag4 = false;
    if (m_ped)
        m_ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CTaskComplexAvoidOtherPedWhileWandering::~CTaskComplexAvoidOtherPedWhileWandering()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
}

CTaskComplexAvoidOtherPedWhileWandering* CTaskComplexAvoidOtherPedWhileWandering::Constructor(CPed* ped, CVector* targetPoint, std::int32_t moveState)
{
    this->CTaskComplexAvoidOtherPedWhileWandering::CTaskComplexAvoidOtherPedWhileWandering(ped, targetPoint, moveState);
    return this;
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x66D050, CTaskComplexAvoidOtherPedWhileWandering*>(this);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::ControlSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x6721B0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

bool CTaskComplexAvoidOtherPedWhileWandering::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return plugin::CallMethodAndReturn<bool, 0x66A260, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::CreateNextSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x66A2C0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x674610, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

void CTaskComplexAvoidOtherPedWhileWandering::QuitIK(CPed* ped)
{
    return plugin::CallMethod<0x66A230, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

std::uint8_t CTaskComplexAvoidOtherPedWhileWandering::NearbyPedsInSphere(CColSphere* colsphere, CPed* ped)
{
    return plugin::CallMethodAndReturn<std::uint8_t, 0x66A320, CTaskComplexAvoidOtherPedWhileWandering*, CColSphere*, CPed*>(this, colsphere, ped);
}

void CTaskComplexAvoidOtherPedWhileWandering::SetUpIK(CPed* ped)
{
    return plugin::CallMethod<0x66A850, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeSphere(CPed* ped, CColSphere* colsphere, CPed** pedsToCheck, CPed** pedsInSphere)
{
    return plugin::CallMethodAndReturn<bool, 0x671FE0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*, CPed**, CPed**>(this, ped, colsphere, pedsToCheck, pedsInSphere);
}

void CTaskComplexAvoidOtherPedWhileWandering::ComputeAvoidSphere(CPed* ped, CColSphere* colsphere)
{
    return plugin::CallMethod<0x672080, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*>(this, ped, colsphere);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeDetourTarget(CPed* ped, CColSphere* colsphere)
{
    return plugin::CallMethodAndReturn<bool, 0x66A7B0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*>(this, ped, colsphere);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeDetourTarget(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x672180, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

