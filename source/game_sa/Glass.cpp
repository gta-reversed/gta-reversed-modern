#include "StdInc.h"

void CGlass::InjectHooks() {
    RH_ScopedClass(CGlass);
    RH_ScopedCategoryGlobal();

//    RH_ScopedInstall(Init, 0x71A8D0);
//    RH_ScopedInstall(Update, 0x71B0D0);
//    RH_ScopedInstall(AskForObjectToBeRenderedInGlass, 0x71ACD0);
//    RH_ScopedInstall(BreakGlassPhysically, 0x71CF50);
//    RH_ScopedInstall(CalcAlphaWithNormal, 0x71ACF0);
//    RH_ScopedInstall(CarWindscreenShatters, 0x71C2B0);
//    RH_ScopedInstall(FindFreePane, 0x71ACA0);
//    RH_ScopedInstall(FindWindowSectorList, 0x71AFC0);
//    RH_ScopedInstall(GeneratePanesForWindow, 0x71B620);
//    RH_ScopedInstall(HasGlassBeenShatteredAtCoors, 0x71CB70);
//    RH_ScopedInstall(Render, 0x71CE20);
//    RH_ScopedInstall(RenderHiLightPolys, 0x71ADA0);
//    RH_ScopedInstall(RenderReflectionPolys, 0x71AED0);
//    RH_ScopedInstall(RenderShatteredPolys, 0x71AE30);
//    RH_ScopedInstall(WasGlassHitByBullet, 0x71C0D0);
//    RH_ScopedInstall(WindowRespondsToCollision, 0x71BC40);
//    RH_ScopedInstall(WindowRespondsToExplosion, 0x71C1A0);
//    RH_ScopedInstall(WindowRespondsToSoftCollision, 0x71AF70);
}

// 0x71A8D0
void CGlass::Init() {
    plugin::Call<0x71A8D0>();
}

// 0x71B0D0
void CGlass::Update() {
    plugin::Call<0x71B0D0>();
}

// 0x71ACD0
void CGlass::AskForObjectToBeRenderedInGlass(CEntity* pEntity) {
    plugin::Call<0x71ACD0, CEntity*>(pEntity);
}

// 0x71CF50
void CGlass::BreakGlassPhysically(CVector a1, float a2) {
    plugin::Call<0x71CF50, CVector, float>(a1, a2);
}

// 0x71ACF0
void CGlass::CalcAlphaWithNormal(CVector* a1) {
    plugin::Call<0x71ACF0, CVector*>(a1);
}

// 0x71C2B0
void CGlass::CarWindscreenShatters(CVehicle* a1) {
    plugin::Call<0x71C2B0, CVehicle*>(a1);
}

// 0x71ACA0
void CGlass::FindFreePane() {
    plugin::Call<0x71ACA0>();
}

// 0x71AFC0
void CGlass::FindWindowSectorList(CPtrList& a1, float* a2, CEntity** a3, float a4, float a5, float a6) {
    plugin::Call<0x71AFC0, CPtrList&, float*, CEntity**, float, float, float>(a1, a2, a3, a4, a5, a6);
}

// 0x71B620
void CGlass::GeneratePanesForWindow(uint32 a1, CVector a2, CVector a3, CVector a4, CVector a5, CVector a6, float a7, bool a8, bool a9, int32 a10, bool a11) {
    plugin::Call<0x71B620, uint32, CVector, CVector, CVector, CVector, CVector, float, bool, bool, int32, bool>(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}

// 0x71CB70
void CGlass::HasGlassBeenShatteredAtCoors(CVector a1) {
    plugin::Call<0x71CB70, CVector>(a1);
}

// 0x71CE20
void CGlass::Render() {
    plugin::Call<0x71CE20>();
}

// 0x71ADA0
void CGlass::RenderHiLightPolys() {
    plugin::Call<0x71ADA0>();
}

// 0x71AED0
void CGlass::RenderReflectionPolys() {
    plugin::Call<0x71AED0>();
}

// 0x71AE30
void CGlass::RenderShatteredPolys() {
    plugin::Call<0x71AE30>();
}

// 0x71C0D0
void CGlass::WasGlassHitByBullet(CEntity* a1, CVector a2) {
    plugin::Call<0x71C0D0, CEntity*, CVector>(a1, a2);
}

// 0x71BC40
void CGlass::WindowRespondsToCollision(CEntity* pEntity, float fDamageIntensity, CVector vecMoveSpeed, CVector vecPoint, int32 bUnknown) {
    return plugin::Call<0x71BC40, CEntity*, float, CVector, CVector, int32>(pEntity, fDamageIntensity, vecMoveSpeed, vecPoint, bUnknown);
}

// 0x71C1A0
void CGlass::WindowRespondsToExplosion(CEntity* a1, const CVector& a2) {
    plugin::Call<0x71C1A0, CEntity*, CVector>(a1, a2);
}

// 0x71AF70
void CGlass::WindowRespondsToSoftCollision(CObject* pEntity, float fDamageIntensity) {
    return plugin::Call<0x71AF70, CObject*, float>(pEntity, fDamageIntensity);
}
