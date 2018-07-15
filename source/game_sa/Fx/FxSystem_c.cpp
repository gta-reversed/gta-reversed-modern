/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

// Converted from thiscall void FxSystem_c::~FxSystem_c() 0x4AA260
FxSystem_c::~FxSystem_c() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA260)(this);
}

// Converted from thiscall void FxSystem_c::Play(void) 0x4AA2F0
void FxSystem_c::Play() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA2F0)(this);
}

// Converted from thiscall void FxSystem_c::Pause(void) 0x4AA370
void FxSystem_c::Pause() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA370)(this);
}

// Converted from thiscall void FxSystem_c::Stop(void) 0x4AA390
void FxSystem_c::Stop() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA390)(this);
}

// Converted from thiscall void FxSystem_c::PlayAndKill(void) 0x4AA3D0
void FxSystem_c::PlayAndKill() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA3D0)(this);
}

// Converted from thiscall void FxSystem_c::Kill(void) 0x4AA3F0
void FxSystem_c::Kill() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA3F0)(this);
}

// Converted from thiscall void FxSystem_c::AttachToBone(CEntity *entity,int boneId) 0x4AA400
void FxSystem_c::AttachToBone(CEntity* entity, int boneId) {
    ((void(__thiscall *)(FxSystem_c*, CEntity*, int))0x4AA400)(this, entity, boneId);
}

// Converted from thiscall void FxSystem_c::AddParticle(RwV3d *position,RwV3d *velocity,float,FxPrtMult_c *prtMult,float,float brightness,float,uchar) 0x4AA440
void FxSystem_c::AddParticle(RwV3d* position, RwV3d* velocity, float arg2, FxPrtMult_c* prtMult, float arg4, float brightness, float arg6, unsigned char arg7) {
    ((void(__thiscall *)(FxSystem_c*, RwV3d*, RwV3d*, float, FxPrtMult_c*, float, float, float, unsigned char))0x4AA440)(this, position, velocity, arg2, prtMult, arg4, brightness, arg6, arg7);
}

// Converted from thiscall void FxSystem_c::AddParticle(RwMatrixTag *transform,RwV3d *position,float,FxPrtMult_c *prtMult,float,float,float,uchar) 0x4AA540
void FxSystem_c::AddParticle(RwMatrixTag* transform, RwV3d* position, float arg2, FxPrtMult_c* prtMult, float arg4, float arg5, float arg6, unsigned char arg7) {
    ((void(__thiscall *)(FxSystem_c*, RwMatrixTag*, RwV3d*, float, FxPrtMult_c*, float, float, float, unsigned char))0x4AA540)(this, transform, position, arg2, prtMult, arg4, arg5, arg6, arg7);
}

// Converted from thiscall void FxSystem_c::EnablePrim(int primIndex,uchar enable) 0x4AA610
void FxSystem_c::EnablePrim(int primIndex, unsigned char enable) {
    ((void(__thiscall *)(FxSystem_c*, int, unsigned char))0x4AA610)(this, primIndex, enable);
}

// Converted from thiscall void FxSystem_c::SetMatrix(RwMatrixTag *matrix) 0x4AA630
void FxSystem_c::SetMatrix(RwMatrixTag* matrix) {
    ((void(__thiscall *)(FxSystem_c*, RwMatrixTag*))0x4AA630)(this, matrix);
}

// Converted from thiscall void FxSystem_c::SetOffsetPos(RwV3d *pos) 0x4AA660
void FxSystem_c::SetOffsetPos(RwV3d* pos) {
    ((void(__thiscall *)(FxSystem_c*, RwV3d*))0x4AA660)(this, pos);
}

// Converted from thiscall void FxSystem_c::AddOffsetPos(RwV3d *pos) 0x4AA690
void FxSystem_c::AddOffsetPos(RwV3d* pos) {
    ((void(__thiscall *)(FxSystem_c*, RwV3d*))0x4AA690)(this, pos);
}

// Converted from thiscall void FxSystem_c::SetConstTime(uchar,float amount) 0x4AA6C0
void FxSystem_c::SetConstTime(unsigned char arg0, float amount) {
    ((void(__thiscall *)(FxSystem_c*, unsigned char, float))0x4AA6C0)(this, arg0, amount);
}

// Converted from thiscall void FxSystem_c::SetRateMult(float mult) 0x4AA6F0
void FxSystem_c::SetRateMult(float mult) {
    ((void(__thiscall *)(FxSystem_c*, float))0x4AA6F0)(this, mult);
}

// Converted from thiscall void FxSystem_c::SetTimeMult(float mult) 0x4AA710
void FxSystem_c::SetTimeMult(float mult) {
    ((void(__thiscall *)(FxSystem_c*, float))0x4AA710)(this, mult);
}

// Converted from thiscall void FxSystem_c::SetVelAdd(RwV3d *velAdd) 0x4AA730
void FxSystem_c::SetVelAdd(RwV3d* velAdd) {
    ((void(__thiscall *)(FxSystem_c*, RwV3d*))0x4AA730)(this, velAdd);
}

// Converted from thiscall bool FxSystem_c::Init(FxSystemBP_c *,RwMatrixTag *local,RwMatrixTag *parent) 0x4AA750
bool FxSystem_c::Init(FxSystemBP_c* arg0, RwMatrixTag* local, RwMatrixTag* parent) {
    return ((bool(__thiscall *)(FxSystem_c*, FxSystemBP_c*, RwMatrixTag*, RwMatrixTag*))0x4AA750)(this, arg0, local, parent);
}

// Converted from thiscall void FxSystem_c::Exit(void) 0x4AA840
void FxSystem_c::Exit() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA840)(this);
}

// Converted from thiscall void FxSystem_c::CopyParentMatrix(void) 0x4AA890
void FxSystem_c::CopyParentMatrix() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA890)(this);
}

// Converted from thiscall void FxSystem_c::GetCompositeMatrix(RwMatrixTag *out) 0x4AA8C0
void FxSystem_c::GetCompositeMatrix(RwMatrixTag* out) {
    ((void(__thiscall *)(FxSystem_c*, RwMatrixTag*))0x4AA8C0)(this, out);
}

// Converted from thiscall void FxSystem_c::GetPlayStatus(void) 0x4AA900
void FxSystem_c::GetPlayStatus() {
    ((void(__thiscall *)(FxSystem_c*))0x4AA900)(this);
}

// Converted from thiscall void FxSystem_c::SetLocalParticles(uchar enable) 0x4AA910
void FxSystem_c::SetLocalParticles(unsigned char enable) {
    ((void(__thiscall *)(FxSystem_c*, unsigned char))0x4AA910)(this, enable);
}

// Converted from thiscall unsigned int FxSystem_c::ForAllParticles(void *callback,void *data) 0x4AA930
unsigned int FxSystem_c::ForAllParticles(void(*callback)(Particle_c *, int, void **), void* data) {
    return ((unsigned int(__thiscall *)(FxSystem_c*, void(*)(Particle_c *, int, void **), void*))0x4AA930)(this, callback, data);
}

// Converted from cdecl void FxSystem_c::UpdateBoundingBoxCB(Particle_c *particle,int,void **data) 0x4AA9A0
void FxSystem_c::UpdateBoundingBoxCB(Particle_c* particle, int arg1, void** data) {
    ((void(__cdecl *)(Particle_c*, int, void**))0x4AA9A0)(particle, arg1, data);
}

// Converted from thiscall void FxSystem_c::GetBoundingBox(FxBox_c *out) 0x4AAA40
void FxSystem_c::GetBoundingBox(FxBox_c* out) {
    ((void(__thiscall *)(FxSystem_c*, FxBox_c*))0x4AAA40)(this, out);
}

// Converted from thiscall bool FxSystem_c::GetBoundingSphereWld(FxSphere_c *out) 0x4AAAD0
bool FxSystem_c::GetBoundingSphereWld(FxSphere_c* out) {
    return ((bool(__thiscall *)(FxSystem_c*, FxSphere_c*))0x4AAAD0)(this, out);
}

// Converted from thiscall bool FxSystem_c::GetBoundingSphereLcl(FxSphere_c *out) 0x4AAB50
bool FxSystem_c::GetBoundingSphereLcl(FxSphere_c* out) {
    return ((bool(__thiscall *)(FxSystem_c*, FxSphere_c*))0x4AAB50)(this, out);
}

// Converted from thiscall void FxSystem_c::SetBoundingSphere(FxSphere_c *bound) 0x4AAB80
void FxSystem_c::SetBoundingSphere(FxSphere_c* bound) {
    ((void(__thiscall *)(FxSystem_c*, FxSphere_c*))0x4AAB80)(this, bound);
}

// Converted from thiscall void FxSystem_c::ResetBoundingSphere(void) 0x4AABF0
void FxSystem_c::ResetBoundingSphere() {
    ((void(__thiscall *)(FxSystem_c*))0x4AABF0)(this);
}

// Converted from thiscall void FxSystem_c::SetZTestEnable(uchar enable) 0x4AAC50
void FxSystem_c::SetZTestEnable(unsigned char enable) {
    ((void(__thiscall *)(FxSystem_c*, unsigned char))0x4AAC50)(this, enable);
}

// Converted from thiscall void FxSystem_c::SetMustCreatePrts(uchar enable) 0x4AAC70
void FxSystem_c::SetMustCreatePrts(unsigned char enable) {
    ((void(__thiscall *)(FxSystem_c*, unsigned char))0x4AAC70)(this, enable);
}

// Converted from thiscall void FxSystem_c::DoFxAudio(CVector posn) 0x4AAC90
void FxSystem_c::DoFxAudio(CVector posn) {
    ((void(__thiscall *)(FxSystem_c*, CVector))0x4AAC90)(this, posn);
}

// Converted from thiscall void FxSystem_c::FxSystem_c(void) 0x4AAF00
FxSystem_c::FxSystem_c() {
    ((void(__thiscall *)(FxSystem_c*))0x4AAF00)(this);
}

// Converted from thiscall bool FxSystem_c::IsVisible(void) 0x4AAF30
bool FxSystem_c::IsVisible() {
    return ((bool(__thiscall *)(FxSystem_c*))0x4AAF30)(this);
}

// Converted from thiscall bool FxSystem_c::Update(RwCamera *camera,float timeDelta) 0x4AAF70
bool FxSystem_c::Update(RwCamera* camera, float timeDelta) {
    return ((bool(__thiscall *)(FxSystem_c*, RwCamera*, float))0x4AAF70)(this, camera, timeDelta);
}
