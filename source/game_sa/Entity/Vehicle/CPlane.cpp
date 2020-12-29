#include "StdInc.h"

int& CPlane::GenPlane_ModelIndex = *(int*)0xC1CAD8;
unsigned int& CPlane::GenPlane_Status = *(unsigned int*)0xC1CADC;
unsigned int& CPlane::GenPlane_LastTimeGenerated = *(unsigned int*)0xC1CAE0;

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
