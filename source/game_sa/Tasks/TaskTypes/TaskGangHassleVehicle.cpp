#include "StdInc.h"
#include "TaskGangHassleVehicle.h"

void CTaskGangHassleVehicle::InjectHooks() {
    RH_ScopedClass(CTaskGangHassleVehicle);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x65FAC0);
    RH_ScopedInstall(Destructor, 0x65FB60);


    //RH_ScopedInstall(GetTargetHeading, 0x65FDD0);
    //RH_ScopedInstall(CalcTargetOffset, 0x6641A0);

    //RH_ScopedInstall(Clone, 0x65FC00);
    RH_ScopedInstall(GetTaskType, 0x65FB50);
    //RH_ScopedInstall(CreateNextSubTask, 0x65FC80);
    //RH_ScopedInstall(CreateFirstSubTask, 0x664BA0);
    //RH_ScopedInstall(ControlSubTask, 0x6637C0);
}

// 0x65FAC0
CTaskGangHassleVehicle::CTaskGangHassleVehicle(CVehicle* vehicle, int32 a3, uint8 a4, float a5, float a6) {}

// 0x65FB60
CTaskGangHassleVehicle::~CTaskGangHassleVehicle() {}

// 0x65FDD0
double CTaskGangHassleVehicle::GetTargetHeading(CPed* ped) {
    return plugin::CallMethodAndReturn<double, 0x65FDD0, CTaskGangHassleVehicle*, CPed*>(this, ped);
}

// 0x6641A0
void CTaskGangHassleVehicle::CalcTargetOffset() {
    plugin::CallMethod<0x6641A0, CTaskGangHassleVehicle*>(this);
}


// 0x65FC00
CTask* CTaskGangHassleVehicle::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x65FC00, CTaskGangHassleVehicle*>(this);
}

// 0x65FC80
CTask* CTaskGangHassleVehicle::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x65FC80, CTaskGangHassleVehicle*, CPed*>(this, ped);
}

// 0x664BA0
CTask* CTaskGangHassleVehicle::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x664BA0, CTaskGangHassleVehicle*, CPed*>(this, ped);
}

// 0x6637C0
CTask* CTaskGangHassleVehicle::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6637C0, CTaskGangHassleVehicle*, CPed*>(this, ped);
}

