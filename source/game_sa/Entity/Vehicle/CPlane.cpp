#include "StdInc.h"

int32& CPlane::GenPlane_ModelIndex = *(int32*)0xC1CAD8;
uint32& CPlane::GenPlane_Status = *(uint32*)0xC1CADC;
uint32& CPlane::GenPlane_LastTimeGenerated = *(uint32*)0xC1CAE0;

bool& CPlane::GenPlane_Active = *(bool*)0x8D33BC;               // true
float& CPlane::ANDROM_COL_ANGLE_MULT = *(float*)0x8D33C0;       // 0.00015
float& CPlane::HARRIER_NOZZLE_ROTATE_LIMIT = *(float*)0x8D33C4; // 5000.0
float& CPlane::HARRIER_NOZZLE_SWITCH_LIMIT = *(float*)0x8D33C8; // 3000.0
float& CPlane::PLANE_MIN_PROP_SPEED = *(float*)0x8D33CC;        // 0.05
float& CPlane::PLANE_STD_PROP_SPEED = *(float*)0x8D33D0;        // 0.18
float& CPlane::PLANE_MAX_PROP_SPEED = *(float*)0x8D33D4;        // 0.34
float& CPlane::PLANE_ROC_PROP_SPEED = *(float*)0x8D33D8;        // 0.01

extern float& HARRIER_NOZZLE_ROTATERATE = *(float*)0x8D33DC;       // 25.0
extern float& PLANE_DAMAGE_WAVE_COUNTER_VAR = *(float*)0x8D33E0;   // 0.75
extern float& PLANE_DAMAGE_THRESHHOLD = *(float*)0x8D33E4;         // 500.0
extern float& PLANE_DAMAGE_SCALE_MASS = *(float*)0x8D33E8;         // 10000.0
extern float& PLANE_DAMAGE_DESTROY_THRESHHOLD = *(float*)0x8D33EC; // 5000.0
extern CVector& vecRCBaronGunPos = *(CVector*)0x8D33F0;            // <0.0, 0.45, 0.0>

void CPlane::InjectHooks() {

}

CPlane::CPlane(int32 modelIndex, eVehicleCreatedBy createdBy) : CAutomobile(plugin::dummy)
{
    plugin::CallMethod<0x6C8E20, CPlane*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
}

// 0x6CCCF0
void CPlane::BlowUpCar(CEntity* damager, uint8 bHideExplosion) {
    return BlowUpCar_Reversed(damager, bHideExplosion);
}

void CPlane::BlowUpCar_Reversed(CEntity* damager, uint8 bHideExplosion) {
    plugin::CallMethod<0x6CCCF0, CPlane*, CEntity*, uint8>(this, damager, bHideExplosion);
}

// 0x6CABB0
void CPlane::Fix() {
    Fix_Reversed();
}

void CPlane::Fix_Reversed() {
    plugin::CallMethod<0x6CABB0, CPlane*>(this);
}
