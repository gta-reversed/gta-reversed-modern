#include "StdInc.h"

float& CMonsterTruck::DUMPER_COL_ANGLEMULT = *(float*)0x8D33A8;
float& fWheelExtensionRate = *(float*)0x8D33AC;

CMonsterTruck::CMonsterTruck(int modelIndex, unsigned char createdBy) : CAutomobile(plugin::dummy) {
    plugin::CallMethod<0x6C8D60, CMonsterTruck*, int, unsigned char>(this, modelIndex, createdBy);
}

void CMonsterTruck::ExtendSuspension() {
    ((void(__thiscall*)(CMonsterTruck*))0x6C7D80)(this);
}
