#include "StdInc.h"
#include "TaskComplexSmartFleeEntity.h"

void CTaskComplexSmartFleeEntity::InjectHooks() {
    RH_ScopedClass(CTaskComplexSmartFleeEntity);
    RH_ScopedCategory(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Constructor, 0x65C430);
    RH_ScopedInstall(Destructor, 0x65C4D0);

    // RH_ScopedInstall(Clone, 0x65CF40);
    RH_ScopedInstall(GetTaskType, 0x65C4C0);
    // RH_ScopedInstall(CreateNextSubTask, 0x65C680);
    // RH_ScopedInstall(CreateFirstSubTask, 0x65C6F0);
    // RH_ScopedInstall(ControlSubTask, 0x65C780);
}

// 0x65C430
CTaskComplexSmartFleeEntity::CTaskComplexSmartFleeEntity(CEntity* entity_1, bool a3, float a4, int32 a5, int32 a6, float a7) {}

// 0x65C4D0
CTaskComplexSmartFleeEntity::~CTaskComplexSmartFleeEntity() {}

// 0x65CF40
CTask* CTaskComplexSmartFleeEntity::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x65CF40, CTaskComplexSmartFleeEntity*>(this);
}

// 0x65C680
CTask* CTaskComplexSmartFleeEntity::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x65C680, CTaskComplexSmartFleeEntity*, CPed*>(this, ped);
}

// 0x65C6F0
CTask* CTaskComplexSmartFleeEntity::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x65C6F0, CTaskComplexSmartFleeEntity*, CPed*>(this, ped);
}

// 0x65C780
CTask* CTaskComplexSmartFleeEntity::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x65C780, CTaskComplexSmartFleeEntity*, CPed*>(this, ped);
}
