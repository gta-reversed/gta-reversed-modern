/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

// 0x4AA260
FxSystem_c::~FxSystem_c() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA260)(this);
}

// 0x4AA2F0
void FxSystem_c::Play() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA2F0)(this);
}

// 0x4AA370
void FxSystem_c::Pause() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA370)(this);
}

// 0x4AA390
void FxSystem_c::Stop() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA390)(this);
}

// 0x4AA3D0
void FxSystem_c::PlayAndKill() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA3D0)(this);
}

// 0x4AA3F0
void FxSystem_c::Kill() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA3F0)(this);
}

// 0x4AA400
void FxSystem_c::AttachToBone(CEntity* entity, int32 boneId) {
    ((void(__thiscall *)(FxSystem_c*, CEntity*, int32))0x4AA400)(this, entity, boneId);
}

//  0x4AA440
void FxSystem_c::AddParticle(RwV3d* position, RwV3d* velocity, float arg2, FxPrtMult_c* prtMult, float arg4, float brightness, float arg6, uint8 arg8) {
    ((void(__thiscall *)(FxSystem_c*, RwV3d*, RwV3d*, float, FxPrtMult_c*, float, float, float, uint8))0x4AA440)(this, position, velocity, arg2, prtMult, arg4, brightness, arg6, arg8);
}

// 0x4AA540
void FxSystem_c::AddParticle(RwMatrix* transform, RwV3d* position, float arg2, FxPrtMult_c* prtMult, float arg4, float arg5, float arg6, uint8 arg7) {
    ((void(__thiscall *)(FxSystem_c*, RwMatrix*, RwV3d*, float, FxPrtMult_c*, float, float, float, uint8))0x4AA540)(this, transform, position, arg2, prtMult, arg4, arg5, arg6, arg7);
}

// 0x4AA610
void FxSystem_c::EnablePrim(int32 primIndex, uint8 enable) {
    ((void(__thiscall *)(FxSystem_c*, int32, uint8))0x4AA610)(this, primIndex, enable);
}

// 0x4AA630
void FxSystem_c::SetMatrix(RwMatrix* matrix) {
    ((void(__thiscall *)(FxSystem_c*, RwMatrix*))0x4AA630)(this, matrix);
}

// (RwV3d*)
// 0x4AA660
void FxSystem_c::SetOffsetPos(const CVector& pos) {
    ((void(__thiscall *)(FxSystem_c*, const CVector&))0x4AA660)(this, pos);
}

// 0x4AA690
void FxSystem_c::AddOffsetPos(RwV3d* pos) {
    ((void(__thiscall *)(FxSystem_c*, RwV3d*))0x4AA690)(this, pos);
}

// 0x4AA6C0
void FxSystem_c::SetConstTime(uint8 arg0, float amount) {
    ((void(__thiscall *)(FxSystem_c*, uint8, float))0x4AA6C0)(this, arg0, amount);
}

// 0x4AA6F0
void FxSystem_c::SetRateMult(float mult) {
    ((void(__thiscall *)(FxSystem_c*, float))0x4AA6F0)(this, mult);
}

// 0x4AA710
void FxSystem_c::SetTimeMult(float mult) {
    ((void(__thiscall *)(FxSystem_c*, float))0x4AA710)(this, mult);
}

// 0x4AA730
void FxSystem_c::SetVelAdd(RwV3d* velAdd) {
    ((void(__thiscall *)(FxSystem_c*, RwV3d*))0x4AA730)(this, velAdd);
}

// 0x4AA750
bool FxSystem_c::Init(FxSystemBP_c* arg0, RwMatrix* local, RwMatrix* parent) {
    return ((bool(__thiscall *)(FxSystem_c*, FxSystemBP_c*, RwMatrix*, RwMatrix*))0x4AA750)(this, arg0, local, parent);
}

// 0x4AA840
void FxSystem_c::Exit() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA840)(this);
}

// 0x4AA890
void FxSystem_c::CopyParentMatrix() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA890)(this);
}

// 0x4AA8C0
void FxSystem_c::GetCompositeMatrix(RwMatrix* out) {
    ((void(__thiscall *)(FxSystem_c*, RwMatrix*))0x4AA8C0)(this, out);
}

// 0x4AA900
eFxSystemPlayStatus FxSystem_c::GetPlayStatus() {
    return ((eFxSystemPlayStatus(__thiscall *)(FxSystem_c*))0x4AA900)(this);
}

// 0x4AA910
void FxSystem_c::SetLocalParticles(uint8 enable) {
    ((void(__thiscall *)(FxSystem_c*, uint8))0x4AA910)(this, enable);
}

// 0x4AA930
uint32 FxSystem_c::ForAllParticles(void(*callback)(Particle_c *, int32, void **), void* data) {
    return ((uint32(__thiscall *)(FxSystem_c*, void(*)(Particle_c *, int32, void **), void*))0x4AA930)(this, callback, data);
}

// 0x4AA9A0
void FxSystem_c::UpdateBoundingBoxCB(Particle_c* particle, int32 arg1, void** data) {
    ((void(__cdecl *)(Particle_c*, int32, void**))0x4AA9A0)(particle, arg1, data);
}

// 0x4AAA40
void FxSystem_c::GetBoundingBox(FxBox_c* out) {
    ((void(__thiscall *)(FxSystem_c*, FxBox_c*))0x4AAA40)(this, out);
}

// 0x4AAAD0
bool FxSystem_c::GetBoundingSphereWld(FxSphere_c* out) {
    return ((bool(__thiscall *)(FxSystem_c*, FxSphere_c*))0x4AAAD0)(this, out);
}

// 0x4AAB50
bool FxSystem_c::GetBoundingSphereLcl(FxSphere_c* out) {
    return ((bool(__thiscall *)(FxSystem_c*, FxSphere_c*))0x4AAB50)(this, out);
}

// 0x4AAB80
void FxSystem_c::SetBoundingSphere(FxSphere_c* bound) {
    ((void(__thiscall *)(FxSystem_c*, FxSphere_c*))0x4AAB80)(this, bound);
}

// 0x4AABF0
void FxSystem_c::ResetBoundingSphere() {
    ((void(__thiscall *)(FxSystem_c*))0x4AABF0)(this);
}

// 0x4AAC50
void FxSystem_c::SetZTestEnable(uint8 enable) {
    ((void(__thiscall *)(FxSystem_c*, uint8))0x4AAC50)(this, enable);
}

// 0x4AAC70
void FxSystem_c::SetMustCreatePrts(uint8 enable) {
    ((void(__thiscall *)(FxSystem_c*, uint8))0x4AAC70)(this, enable);
}

// 0x4AAC90
void FxSystem_c::DoFxAudio(CVector posn) {
    ((void(__thiscall *)(FxSystem_c*, CVector))0x4AAC90)(this, posn);
}

// 0x4AAF00
FxSystem_c::FxSystem_c() {
    ((void(__thiscall *)(FxSystem_c*))0x4AAF00)(this);
}

// 0x4AAF30
bool FxSystem_c::IsVisible() {
    return ((bool(__thiscall *)(FxSystem_c*))0x4AAF30)(this);
}

// 0x4AAF70
bool FxSystem_c::Update(RwCamera* camera, float timeDelta) {
    return ((bool(__thiscall *)(FxSystem_c*, RwCamera*, float))0x4AAF70)(this, camera, timeDelta);
}
