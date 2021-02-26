#include "StdInc.h"

float &CCamera::m_f3rdPersonCHairMultY = *reinterpret_cast<float *>(0xB6EC10);
float &CCamera::m_f3rdPersonCHairMultX = *reinterpret_cast<float *>(0xB6EC14);
float &CCamera::m_fMouseAccelVertical = *reinterpret_cast<float *>(0xB6EC18);
float &CCamera::m_fMouseAccelHorzntl = *reinterpret_cast<float *>(0xB6EC1C);
bool &CCamera::m_bUseMouse3rdPerson = *reinterpret_cast<bool *>(0xB6EC2E);
CCamera &TheCamera = *reinterpret_cast<CCamera *>(0xB6F028);
bool& gbModelViewer = *reinterpret_cast<bool*>(0xBA6728);

CCam& CCamera::GetActiveCamera()
{
    return TheCamera.m_aCams[TheCamera.m_nActiveCam];
}

bool CCamera::Using1stPersonWeaponMode() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera*>(0x50BFF0, this);
}

void CCamera::ClearPlayerWeaponMode() {
    plugin::CallMethodDynGlobal<CCamera*>(0x50AB10, this);
}

void CCamera::SetNewPlayerWeaponMode(short mode, short maxZoom, short minZoom) {
    plugin::CallMethodDynGlobal<CCamera*, short, short, short>(0x50BFB0, this, mode, maxZoom, minZoom);
}

void CCamera::UpdateAimingCoors(CVector const* AimingTargetCoors) {
    plugin::CallMethodDynGlobal<CCamera*, CVector const*>(0x50CB10, this, AimingTargetCoors);
}

signed int CCamera::GetLookDirection() {
    return plugin::CallMethodAndReturnDynGlobal<signed int, CCamera*>(0x50AE90, this);
}

bool CCamera::Get_Just_Switched_Status()
{
    return plugin::CallMethodAndReturn<bool, 0x50AE10, CCamera*>(this);
}

float CCamera::CalculateGroundHeight(eGroundHeightType type) {
    return plugin::CallMethodAndReturnDynGlobal<float, CCamera*, eGroundHeightType>(0x514B80, this, type);
}

void CCamera::CamControl() {
    plugin::CallMethodDynGlobal<CCamera*>(0x527FA0, this);
}

void CCamera::CamShake(float arg2, float x, float y, float z) {
    plugin::CallMethodDynGlobal<CCamera*, float, float, float, float>(0x50A9F0, this, arg2, x, y, z);
}

void CCamera::DrawBordersForWideScreen()
{
    ((void(__thiscall*)(CCamera*))0x514860)(this);
}

bool CCamera::IsSphereVisible(CVector const& origin, float radius, RwMatrixTag* transformMatrix)
{
	return plugin::CallMethodAndReturn<bool, 0x420C40, CCamera*, CVector const&, float, RwMatrixTag*>(this, origin, radius, transformMatrix);
}

bool CCamera::IsSphereVisible(CVector const& origin, float radius)
{
    return plugin::CallMethodAndReturn<bool, 0x420D40, CCamera*, CVector const&, float>(this, origin, radius);
}
