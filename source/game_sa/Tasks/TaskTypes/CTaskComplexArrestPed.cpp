#include "StdInc.h"

void CTaskComplexArrestPed::InjectHooks()
{
    HookInstall(0x68B990, &CTaskComplexArrestPed::Constructor);
}

CTaskComplexArrestPed::CTaskComplexArrestPed(CPed* ped)
{
    m_pedToArrest = ped;
    m_vehicle = nullptr;
    if (ped)
        ped->RegisterReference(reinterpret_cast<CEntity**>(&m_pedToArrest));
}

CTaskComplexArrestPed::~CTaskComplexArrestPed()
{
    if (m_pedToArrest)
        m_pedToArrest->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pedToArrest));
}

CTaskComplexArrestPed* CTaskComplexArrestPed::Constructor(CPed* ped)
{
    this->CTaskComplexArrestPed::CTaskComplexArrestPed(ped);
    return this;
}

bool CTaskComplexArrestPed::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* event)
{
    return plugin::CallMethodAndReturn<bool, 0x68BA60, CTaskComplexArrestPed*, CPed*, eAbortPriority, CEvent*>(this, ped, priority, event);
}

CTask* CTaskComplexArrestPed::CreateNextSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x690220, CTaskComplexArrestPed*, CPed*>(this, ped);
}

CTask* CTaskComplexArrestPed::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x6907A0, CTaskComplexArrestPed*, CPed*>(this, ped);
}

CTask* CTaskComplexArrestPed::ControlSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x68D350, CTaskComplexArrestPed*, CPed*>(this, ped);
}

CTask* CTaskComplexArrestPed::CreateSubTask(std::int32_t taskId, CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x68CF80, CTaskComplexArrestPed*, std::int32_t, CPed*>(this, taskId, ped);
}

