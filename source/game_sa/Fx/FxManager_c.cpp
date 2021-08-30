/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

FxManager_c& g_fxMan = *(FxManager_c*)0xA9AE80;

// 0x4A90A0
FxManager_c::~FxManager_c() {
    ((void(__thiscall*)(FxManager_c*))0x4A90A0)(this);
}

// 0x4A9130
FxFrustumInfo_c* FxManager_c::GetFrustumInfo() {
    return ((FxFrustumInfo_c * (__thiscall*)(FxManager_c*))0x4A9130)(this);
}

// 0x4A9140
void FxManager_c::CalcFrustumInfo(RwCamera* camera) {
    ((void(__thiscall*)(FxManager_c*, RwCamera*))0x4A9140)(this, camera);
}

// 0x4A92A0
void FxManager_c::Render(RwCamera* camera, unsigned char arg1) {
    ((void(__thiscall*)(FxManager_c*, RwCamera*, unsigned char))0x4A92A0)(this, camera, arg1);
}

// 0x4A9360
FxSystemBP_c* FxManager_c::FindFxSystemBP(char* name) {
    return ((FxSystemBP_c * (__thiscall*)(FxManager_c*, char*))0x4A9360)(this, name);
}

// 0x4A93B0
void FxManager_c::ReturnParticle(FxEmitterPrt_c* emitter) {
    ((void(__thiscall*)(FxManager_c*, FxEmitterPrt_c*))0x4A93B0)(this, emitter);
}

// 0x4A93C0
FxEmitterPrt_c* FxManager_c::GetParticle(signed char arg0) {
    return ((FxEmitterPrt_c * (__thiscall*)(FxManager_c*, signed char))0x4A93C0)(this, arg0);
}

// 0x4A93E0
void FxManager_c::SetWindData(RwV3d* dir, float* speed) {
    ((void(__thiscall*)(FxManager_c*, RwV3d*, float*))0x4A93E0)(this, dir, speed);
}

// 0x4A9400
void FxManager_c::FreeUpParticle() {
    ((void(__thiscall*)(FxManager_c*))0x4A9400)(this);
}

// 0x4A9440
RwMatrix* FxManager_c::FxRwMatrixCreate() {
    return ((RwMatrix * (__thiscall*)(FxManager_c*))0x4A9440)(this);
}

// 0x4A9460
void FxManager_c::FxRwMatrixDestroy(RwMatrix* matrix) {
    ((void(__thiscall*)(FxManager_c*, RwMatrix*))0x4A9460)(this, matrix);
}

// 0x4A9470
FxManager_c::FxManager_c() {
    ((void(__thiscall*)(FxManager_c*))0x4A9470)(this);
}

// 0x4A9500
bool FxManager_c::ShouldCreate(FxSystemBP_c* bpSystem, RwMatrix* transform, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks) {
    return ((bool(__thiscall*)(FxManager_c*, FxSystemBP_c*, RwMatrix*, RwMatrix*, unsigned char))0x4A9500)(this, bpSystem, transform, objectMatrix, ignoreBoundingChecks);
}

// 0x4A95C0
FxSystem_c* FxManager_c::CreateFxSystem(FxSystemBP_c* bpSystem, RwMatrix* transform, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks) {
    return ((FxSystem_c * (__thiscall*)(FxManager_c*, FxSystemBP_c*, RwMatrix*, RwMatrix*, unsigned char))0x4A95C0)(this, bpSystem, transform, objectMatrix, ignoreBoundingChecks);
}

// 0x4A96B0
FxSystem_c* FxManager_c::CreateFxSystem(FxSystemBP_c* bpSystem, RwV3d* position, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks) {
    return ((FxSystem_c * (__thiscall*)(FxManager_c*, FxSystemBP_c*, RwV3d*, RwMatrix*, unsigned char))0x4A96B0)(this, bpSystem, position, objectMatrix, ignoreBoundingChecks);
}

// 0x4A9810
void FxManager_c::DestroyFxSystem(FxSystem_c* system) {
    ((void(__thiscall*)(FxManager_c*, FxSystem_c*))0x4A9810)(this, system);
}

// 0x4A98B0
void FxManager_c::DestroyAllFxSystems() {
    ((void(__thiscall*)(FxManager_c*))0x4A98B0)(this);
}

// 0x4A98E0
bool FxManager_c::Init() {
    return ((bool(__thiscall*)(FxManager_c*))0x4A98E0)(this);
}

// 0x4A9A10
void FxManager_c::Exit() {
    ((void(__thiscall*)(FxManager_c*))0x4A9A10)(this);
}

// 0x4A9A80
void FxManager_c::Update(RwCamera* arg0, float timeDelta) {
    ((void(__thiscall*)(FxManager_c*, RwCamera*, float))0x4A9A80)(this, arg0, timeDelta);
}

// 0x4A9AE0
void FxManager_c::UnloadFxProject() {
    ((void(__thiscall*)(FxManager_c*))0x4A9AE0)(this);
}

// 0x4A9BB0
FxSystem_c* FxManager_c::CreateFxSystem(char* name, RwMatrix* transform, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks) {
    return ((FxSystem_c * (__thiscall*)(FxManager_c*, char*, RwMatrix*, RwMatrix*, unsigned char))0x4A9BB0)(this, name, transform, objectMatrix, ignoreBoundingChecks);
}

// 0x4A9BE0
FxSystem_c* FxManager_c::CreateFxSystem(char* name, RwV3d* position, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks) {
    return ((FxSystem_c * (__thiscall*)(FxManager_c*, char*, RwV3d*, RwMatrix*, unsigned char))0x4A9BE0)(this, name, position, objectMatrix, ignoreBoundingChecks);
}

// 0x5C1F50
FxSystemBP_c* FxManager_c::LoadFxSystemBP(char* filename, int file) {
    return ((FxSystemBP_c * (__thiscall*)(FxManager_c*, char*, int))0x5C1F50)(this, filename, file);
}

// 0x5C2420
bool FxManager_c::LoadFxProject(char* filename) {
    return ((bool(__thiscall*)(FxManager_c*, char*))0x5C2420)(this, filename);
}