#include "StdInc.h"
#include "TaskComplexFacial.h"

void CTaskComplexFacial::InjectHooks() {
    RH_ScopedClass(CTaskComplexFacial);
    RH_ScopedCategory("Task/TaskTypes"); // TODO: Change this to the appropriate category!

    // Constructors (1x)
    // RH_ScopedInstall(Constructor, 0x690D20);

    // Destructors (1x)
    // RH_ScopedOverloadedInstall(Destructor, "", 0x690D90, CTaskComplexFacial * (CTaskComplexFacial::*)());

    // Methods (1x)
    // RH_ScopedInstall(StopAll, 0x691250);

    // Virtual methods (6x)
    // RH_ScopedInstall(Clone_Reversed, 0x6928B0);
    // RH_ScopedInstall(GetTaskType_Reversed, 0x690D80);
    // RH_ScopedInstall(MakeAbortable_Reversed, 0x690DA0);
    // RH_ScopedInstall(CreateNextSubTask_Reversed, 0x690DC0);
    // RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x690F30);
    // RH_ScopedInstall(ControlSubTask_Reversed, 0x690FC0);
}

// 0x690D20
CTaskComplexFacial::CTaskComplexFacial() {}

// 0x690D20
CTaskComplexFacial* CTaskComplexFacial::Constructor() {
    this->CTaskComplexFacial::CTaskComplexFacial();
    return this;
}

// 0x690D90
CTaskComplexFacial::~CTaskComplexFacial() {}

// 0x690D90
CTaskComplexFacial* CTaskComplexFacial::Destructor() {
    this->CTaskComplexFacial::~CTaskComplexFacial();
    return this;
}

// Methods
// 0x691250
void CTaskComplexFacial::StopAll() {
    plugin::CallMethod<0x691250, CTaskComplexFacial*>(this);
}

// Virtual methods
// 0x6928B0
CTask* CTaskComplexFacial::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x6928B0, CTaskComplexFacial*>(this);
}

// 0x690DA0
bool CTaskComplexFacial::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x690DA0, CTaskComplexFacial*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x690DC0
CTask* CTaskComplexFacial::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690DC0, CTaskComplexFacial*, CPed*>(this, ped);
}

// 0x690F30
CTask* CTaskComplexFacial::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690F30, CTaskComplexFacial*, CPed*>(this, ped);
}

// 0x690FC0
CTask* CTaskComplexFacial::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690FC0, CTaskComplexFacial*, CPed*>(this, ped);
}
