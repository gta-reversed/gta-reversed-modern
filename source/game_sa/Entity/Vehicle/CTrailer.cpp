#include "StdInc.h"

void CTrailer::InjectHooks() {

}

CTrailer::CTrailer(int modelIndex, eVehicleCreatedBy createdBy) : CAutomobile(plugin::dummy)
{
    plugin::CallMethod<0x6D03A0, CTrailer*, int, eVehicleCreatedBy>(this, modelIndex, createdBy);
}

// 0x6CFDF0
bool CTrailer::SetTowLink(CVehicle* targetVehicle, bool arg1) {
    return SetTowLink_Reversed(targetVehicle, arg1);
}

bool CTrailer::SetTowLink_Reversed(CVehicle* targetVehicle, bool arg1) {
    return plugin::CallMethodAndReturn<bool, 0x6CFDF0, CTrailer*, CVehicle*, bool>(this, targetVehicle, arg1);
}
