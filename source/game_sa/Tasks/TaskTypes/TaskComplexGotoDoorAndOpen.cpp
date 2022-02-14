#include "StdInc.h"
#include "TaskComplexGotoDoorAndOpen.h"

void CTaskComplexGotoDoorAndOpen::InjectHooks() {
    //RH_ScopedClass(CTaskComplexGotoDoorAndOpen);
    //RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    // Constructors (2x)
    //RH_ScopedOverloadedInstall(Constructor, "", 0x66BB20, CTaskComplexGotoDoorAndOpen * (CTaskComplexGotoDoorAndOpen::*)(CObject*));
    //RH_ScopedOverloadedInstall(Constructor, "", 0x66BBA0, CTaskComplexGotoDoorAndOpen * (CTaskComplexGotoDoorAndOpen::*)(CVector const&, CVector const&));

    // Destructors (1x)
    //RH_ScopedOverloadedInstall(Destructor, "", 0x66BC00, CTaskComplexGotoDoorAndOpen * (CTaskComplexGotoDoorAndOpen::*)());

    // Virtual methods (6x)
    //RH_ScopedInstall(Clone_Reversed, 0x66BCA0);
    //RH_ScopedInstall(GetTaskType_Reversed, 0x66BB90);
    //RH_ScopedInstall(MakeAbortable_Reversed, 0x66BC80);
    //RH_ScopedInstall(CreateNextSubTask_Reversed, 0x66C0D0);
    //RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x66BD40);
    //RH_ScopedInstall(ControlSubTask_Reversed, 0x66C1F0);
}

// 0x66BB20
CTaskComplexGotoDoorAndOpen::CTaskComplexGotoDoorAndOpen(CObject* door)
{
    plugin::CallMethodAndReturn<CTaskComplexGotoDoorAndOpen*, 0x66BB20>(this, door);
}

// 0x66BB20
CTaskComplexGotoDoorAndOpen* CTaskComplexGotoDoorAndOpen::Constructor(CObject* door) {
    this->CTaskComplexGotoDoorAndOpen::CTaskComplexGotoDoorAndOpen(door);
    return this;
}
// 0x66BBA0
CTaskComplexGotoDoorAndOpen::CTaskComplexGotoDoorAndOpen(CVector const& start, CVector const& end) {
    plugin::CallMethodAndReturn<CTaskComplexGotoDoorAndOpen*, 0x66BBA0, CTaskComplexGotoDoorAndOpen*, CVector const&, CVector const&>(this, start, end);
}

// 0x66BBA0
CTaskComplexGotoDoorAndOpen* CTaskComplexGotoDoorAndOpen::Constructor(CVector const& start, CVector const& end) {
    this->CTaskComplexGotoDoorAndOpen::CTaskComplexGotoDoorAndOpen(start, end);
    return this;
}

// 0x66BC00
CTaskComplexGotoDoorAndOpen::~CTaskComplexGotoDoorAndOpen() {
    plugin::CallMethodAndReturn<CTaskComplexGotoDoorAndOpen*, 0x66BC00>(this);
}

// 0x66BC00
CTaskComplexGotoDoorAndOpen* CTaskComplexGotoDoorAndOpen::Destructor() {
    this->CTaskComplexGotoDoorAndOpen::~CTaskComplexGotoDoorAndOpen();
    return this;
}

// Virtual methods
// 0x66BCA0
CTask* CTaskComplexGotoDoorAndOpen::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x66BCA0, CTaskComplexGotoDoorAndOpen*>(this);
}

// 0x66BC80
bool CTaskComplexGotoDoorAndOpen::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x66BC80, CTaskComplexGotoDoorAndOpen*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x66C0D0
CTask* CTaskComplexGotoDoorAndOpen::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66C0D0, CTaskComplexGotoDoorAndOpen*, CPed*>(this, ped);
}

// 0x66BD40
CTask* CTaskComplexGotoDoorAndOpen::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66BD40, CTaskComplexGotoDoorAndOpen*, CPed*>(this, ped);
}

// 0x66C1F0
CTask* CTaskComplexGotoDoorAndOpen::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66C1F0, CTaskComplexGotoDoorAndOpen*, CPed*>(this, ped);
}
