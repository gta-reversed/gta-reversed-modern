#include "StdInc.h"

float& CMonsterTruck::DUMPER_COL_ANGLEMULT = *(float*)0x8D33A8;
float& fWheelExtensionRate = *(float*)0x8D33AC;

CMonsterTruck::CMonsterTruck(int32 modelIndex, eVehicleCreatedBy createdBy) : CAutomobile(plugin::dummy) {
    plugin::CallMethod<0x6C8D60, CMonsterTruck*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
}

void CMonsterTruck::ExtendSuspension() {
    ((void(__thiscall*)(CMonsterTruck*))0x6C7D80)(this);
}
