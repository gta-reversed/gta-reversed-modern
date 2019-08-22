#include "StdInc.h"

float &CCamera::m_f3rdPersonCHairMultY = *reinterpret_cast<float *>(0xB6EC10);
float &CCamera::m_f3rdPersonCHairMultX = *reinterpret_cast<float *>(0xB6EC14);
float &CCamera::m_fMouseAccelVertical = *reinterpret_cast<float *>(0xB6EC18);
float &CCamera::m_fMouseAccelHorzntl = *reinterpret_cast<float *>(0xB6EC1C);
bool &CCamera::m_bUseMouse3rdPerson = *reinterpret_cast<bool *>(0xB6EC2E);
CCamera &TheCamera = *reinterpret_cast<CCamera *>(0xB6F028);

bool CCamera::Using1stPersonWeaponMode() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera*>(0x50BFF0, this);
}