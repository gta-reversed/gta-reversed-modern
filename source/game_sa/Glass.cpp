#include "StdInc.h"
#include "Glass.h"
#include "FallingGlassPane.h"

CVector2D (&PanePolyPositions)[4][3] = *(CVector2D(*)[4][3])0x8D5CD8;
int32& CGlass::ReflectionPolyVertexBaseIdx = *(int32*)0xC71B18;
int32& CGlass::ReflectionPolyIndexBaseIdx = *(int32*)0xC71B1C;
int32& CGlass::ShatteredVerticesBaseIdx = *(int32*)0xC71B20;
int32& CGlass::ShatteredIndicesBaseIdx = *(int32*)0xC71B24;
uint32& CGlass::NumHiLightPolyVertices = *(uint32*)0xC71B28;
int32& CGlass::NumHiLightPolyIndices = *(int32*)0xC71B2C;
CVector2D (&PanePolyCenterPositions)[5] = *(CVector2D(*)[5])0xC71B30;
int32 (&CGlass::apEntitiesToBeRendered)[1] = *(int32(*)[1])0xC71B58;
int32& CGlass::NumGlassEntities = *(int32*)0xC71BD8;
CFallingGlassPane (&aGlassPanes)[44] = *(CFallingGlassPane(*)[44])0xC71BF8;
int32& CGlass::LastColCheckMS = *(int32*)0xC72FA8;

void CGlass::InjectHooks() {
    // ReversibleHooks::Install("CGlass", "Init", 0x71A8D0, &CGlass::Init);
    // ReversibleHooks::Install("CGlass", "HasGlassBeenShatteredAtCoors", 0x71CB70, &CGlass::HasGlassBeenShatteredAtCoors);
    // ReversibleHooks::Install("CGlass", "CarWindscreenShatters", 0x71C2B0, &CGlass::CarWindscreenShatters);
    // ReversibleHooks::Install("CGlass", "WasGlassHitByBullet", 0x71C0D0, &CGlass::WasGlassHitByBullet);
    // ReversibleHooks::Install("CGlass", "WindowRespondsToCollision", 0x71BC40, &CGlass::WindowRespondsToCollision);
    // ReversibleHooks::Install("CGlass", "GeneratePanesForWindow", 0x71B620, &CGlass::GeneratePanesForWindow);
    // ReversibleHooks::Install("CGlass", "Update", 0x71B0D0, &CGlass::Update);
    // ReversibleHooks::Install("CGlass", "Render", 0x71CE20, &CGlass::Render);
    // ReversibleHooks::Install("CGlass", "FindWindowSectorList", 0x71AFC0, &CGlass::FindWindowSectorList);
    // ReversibleHooks::Install("CGlass", "RenderReflectionPolys", 0x71AED0, &CGlass::RenderReflectionPolys);
    // ReversibleHooks::Install("CGlass", "RenderShatteredPolys", 0x71AE30, &CGlass::RenderShatteredPolys);
    // ReversibleHooks::Install("CGlass", "RenderHiLightPolys", 0x71ADA0, &CGlass::RenderHiLightPolys);
    // ReversibleHooks::Install("CGlass", "CalcAlphaWithNormal", 0x71ACF0, &CGlass::CalcAlphaWithNormal);
    // ReversibleHooks::Install("CGlass", "AskForObjectToBeRenderedInGlass", 0x71ACD0, &CGlass::AskForObjectToBeRenderedInGlass);
    // ReversibleHooks::Install("CGlass", "FindFreePane", 0x71ACA0, &CGlass::FindFreePane);
    // ReversibleHooks::Install("CGlass", "WindowRespondsToSoftCollision", 0x71AF70, &CGlass::WindowRespondsToSoftCollision);
    // ReversibleHooks::Install("CGlass", "BreakGlassPhysically", 0x71CF50, &CGlass::BreakGlassPhysically);
}

// Static functions
// 0x71A8D0
void CGlass::Init() {
    plugin::Call<0x71A8D0>();
}

// 0x71CB70
bool CGlass::HasGlassBeenShatteredAtCoors(CVector pos) {
    return plugin::CallAndReturn<bool, 0x71CB70, CVector>(pos);
}

// 0x71C2B0
void CGlass::CarWindscreenShatters(CVehicle* pVeh) {
    plugin::Call<0x71C2B0, CVehicle*>(pVeh);
}

// 0x71C0D0
void CGlass::WasGlassHitByBullet(CEntity* pObj, CVector hitPos) {
    plugin::Call<0x71C0D0, CEntity*, CVector>(pObj, hitPos);
}

// 0x71BC40
void CGlass::WindowRespondsToCollision(CEntity* pEntity, float fDamageIntensity, CVector vecMoveSpeed, CVector vecPoint, bool a5) {
    return plugin::Call<0x71BC40, CEntity*, float, CVector, CVector, bool>(pEntity, fDamageIntensity, vecMoveSpeed, vecPoint, a5);
}

// 0x71B620
void CGlass::GeneratePanesForWindow(uint32 type, CVector bl_pos, CVector fwd_unnorm, CVector right_unnorm, CVector move_speed, CVector center, float velocityo_center_drag_coeff,
                                    bool bShatter, bool size_max_1, int32 num_sections, bool a11) {
    plugin::Call<0x71B620, uint32, CVector, CVector, CVector, CVector, CVector, float, bool, bool, int32, bool>(
        type, bl_pos, fwd_unnorm, right_unnorm, move_speed, center, velocityo_center_drag_coeff, bShatter, size_max_1, num_sections, a11);
}

// 0x71B0D0
void CGlass::Update() {
    plugin::Call<0x71B0D0>();
}

// 0x71CE20
void CGlass::Render() {
    plugin::Call<0x71CE20>();
}

// 0x71AFC0
void CGlass::FindWindowSectorList(CPtrList& objList, float& outDist, CEntity*& outEntity, CVector point) {
    plugin::Call<0x71AFC0, CPtrList&, float&, CEntity*&, CVector>(objList, outDist, outEntity, point);
}

// 0x71AED0
void CGlass::RenderReflectionPolys() {
    plugin::Call<0x71AED0>();
}

// 0x71AE30
void CGlass::RenderShatteredPolys() {
    plugin::Call<0x71AE30>();
}

// 0x71ADA0
void CGlass::RenderHiLightPolys() {
    plugin::Call<0x71ADA0>();
}

// 0x71ACF0
uint8 CGlass::CalcAlphaWithNormal(CVector* normal) {
    return plugin::CallAndReturn<uint8, 0x71ACF0, CVector*>(normal);
}

// 0x71ACD0
void CGlass::AskForObjectToBeRenderedInGlass(CEntity* a1) {
    plugin::Call<0x71ACD0, CEntity*>(a1);
}

// 0x71ACA0
CFallingGlassPane* CGlass::FindFreePane() {
    return plugin::CallAndReturn<CFallingGlassPane*, 0x71ACA0>();
}

// 0x71AF70
void CGlass::WindowRespondsToSoftCollision(CEntity* pEntity, float fDamageIntensity) {
    plugin::Call<0x71AF70, CEntity*, float>(pEntity, fDamageIntensity);
}

// 0x71CF50
void CGlass::BreakGlassPhysically(CVector pos, float radius) {
    plugin::Call<0x71CF50, CVector, float>(pos, radius);
}
