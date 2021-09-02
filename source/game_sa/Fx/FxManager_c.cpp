/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "FxManager_c.h"

FxManager_c& g_fxMan = *(FxManager_c*)0xA9AE80;

void FxManager_c::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("FxSystem_c", "FxSystem_c", 0x4A9470, &FxManager_c::Constructor);
    // Install("FxSystem_c", "~FxSystem_c", 0x4A90A0, &FxManager_c::Destructor);
    // Install("FxSystem_c", "Init", 0x4A98E0, &FxManager_c::Init);
    // Install("FxSystem_c", "Exit", 0x4A9A10, &FxManager_c::Exit);
    // Install("FxSystem_c", "DestroyFxSystem", 0x4A9810, &FxManager_c::DestroyFxSystem);
    // Install("FxSystem_c", "DestroyAllFxSystems", 0x4A98B0, &FxManager_c::DestroyAllFxSystems);
    // Install("FxSystem_c", "Update", 0x4A9A80, &FxManager_c::Update);
    // Install("FxSystem_c", "LoadFxProject", 0x5C2420, &FxManager_c::LoadFxProject);
    // Install("FxSystem_c", "UnloadFxProject", 0x4A9AE0, &FxManager_c::UnloadFxProject);
    // Install("FxSystem_c", "LoadFxSystemBP", 0x5C1F50, &FxManager_c::LoadFxSystemBP);
    // Install("FxSystem_c", "FindFxSystemBP", 0x4A9360, &FxManager_c::FindFxSystemBP);
    Install("FxSystem_c", "GetFrustumInfo", 0x4A9130, &FxManager_c::GetFrustumInfo);
    // Install("FxSystem_c", "CalcFrustumInfo", 0x4A9140, &FxManager_c::CalcFrustumInfo);
    // Install("FxSystem_c", "Render", 0x4A92A0, &FxManager_c::Render);
    // Install("FxSystem_c", "ReturnParticle", 0x4A93B0, &FxManager_c::ReturnParticle);
    // Install("FxSystem_c", "GetParticle", 0x4A93C0, &FxManager_c::GetParticle);
    // Install("FxSystem_c", "FreeUpParticle", 0x4A9400, &FxManager_c::FreeUpParticle);
    Install("FxSystem_c", "SetWindData", 0x4A93E0, &FxManager_c::SetWindData);
    // Install("FxSystem_c", "FxRwMatrixCreate", 0x4A9440, &FxManager_c::FxRwMatrixCreate);
    Install("FxSystem_c", "FxRwMatrixDestroy", 0x4A9460, &FxManager_c::FxRwMatrixDestroy);
    // Install("FxSystem_c", "ShouldCreate", 0x4A9500, &FxManager_c::ShouldCreate);
    // Install("FxSystem_c", "CreateFxSystem", 0x4A95C0, static_cast<FxSystem_c* (FxManager_c::*)(FxSystemBP_c*, RwMatrix*, RwMatrix*, bool)>(&FxManager_c::CreateFxSystem));
    // Install("FxSystem_c", "CreateFxSystem", 0x4A9BB0, static_cast<FxSystem_c* (FxManager_c::*)(const char*, RwMatrix*, RwMatrix*, bool)>(&FxManager_c::CreateFxSystem));
    // Install("FxSystem_c", "CreateFxSystem", 0x4A96B0, static_cast<FxSystem_c* (FxManager_c::*)(FxSystemBP_c*, RwV3d*, RwMatrix*, bool)>(&FxManager_c::CreateFxSystem));
    // Install("FxSystem_c", "CreateFxSystem", 0x4A9BE0, static_cast<FxSystem_c* (FxManager_c::*)(const char*, RwV3d*, RwMatrix*, bool)>(&FxManager_c::CreateFxSystem));
}

// 0x4A9470
FxManager_c::FxManager_c() {
    ((void(__thiscall*)(FxManager_c*))0x4A9470)(this);
}

FxManager_c* FxManager_c::Constructor() {
    this->FxManager_c::FxManager_c();
    return this;
}

// 0x4A90A0
FxManager_c::~FxManager_c() {
    ((void(__thiscall*)(FxManager_c*))0x4A90A0)(this);
}

FxManager_c* FxManager_c::Destructor() {
    this->FxManager_c::~FxManager_c();
    return this;
}

// 0x4A98E0
bool FxManager_c::Init() {
    return ((bool(__thiscall*)(FxManager_c*))0x4A98E0)(this);
}

// 0x4A9A10
void FxManager_c::Exit() {
    ((void(__thiscall*)(FxManager_c*))0x4A9A10)(this);
}

// 0x4A9810
void FxManager_c::DestroyFxSystem(FxSystem_c* system) {
    ((void(__thiscall*)(FxManager_c*, FxSystem_c*))0x4A9810)(this, system);
}

// 0x4A98B0
void FxManager_c::DestroyAllFxSystems() {
    ((void(__thiscall*)(FxManager_c*))0x4A98B0)(this);
}

// 0x4A9A80
void FxManager_c::Update(RwCamera* arg0, float timeDelta) {
    ((void(__thiscall*)(FxManager_c*, RwCamera*, float))0x4A9A80)(this, arg0, timeDelta);
}

// 0x5C2420
bool FxManager_c::LoadFxProject(const char* filename) {
    return ((bool(__thiscall*)(FxManager_c*, const char*))0x5C2420)(this, filename);
}

// 0x4A9AE0
void FxManager_c::UnloadFxProject() {
    ((void(__thiscall*)(FxManager_c*))0x4A9AE0)(this);
}

// 0x5C1F50
FxSystemBP_c* FxManager_c::LoadFxSystemBP(char* filename, int file) {
    return ((FxSystemBP_c * (__thiscall*)(FxManager_c*, char*, int))0x5C1F50)(this, filename, file);
}

// 0x4A9360
FxSystemBP_c* FxManager_c::FindFxSystemBP(const char* name) {
    return ((FxSystemBP_c * (__thiscall*)(FxManager_c*, const char*))0x4A9360)(this, name);
}
// 0x4A9130
FxFrustumInfo_c* FxManager_c::GetFrustumInfo() {
    return &m_frustum;
}

// 0x4A9140
void FxManager_c::CalcFrustumInfo(RwCamera* camera) {
    ((void(__thiscall*)(FxManager_c*, RwCamera*))0x4A9140)(this, camera);
}

// 0x4A92A0
void FxManager_c::Render(RwCamera* camera, uint8 arg1) {
    ((void(__thiscall*)(FxManager_c*, RwCamera*, uint8))0x4A92A0)(this, camera, arg1);
}

// 0x4A93B0
void FxManager_c::ReturnParticle(FxEmitterPrt_c* emitter) {
    ((void(__thiscall*)(FxManager_c*, FxEmitterPrt_c*))0x4A93B0)(this, emitter);
    // m_fxEmitterParticlesList.AddItem(&emitter->m_link);
}

// 0x4A93C0
FxEmitterPrt_c* FxManager_c::GetParticle(signed char arg0) {
    return ((FxEmitterPrt_c * (__thiscall*)(FxManager_c*, signed char))0x4A93C0)(this, arg0);
}

// 0x4A9400
void FxManager_c::FreeUpParticle() {
    ((void(__thiscall*)(FxManager_c*))0x4A9400)(this);
}

// 0x4A93E0
void FxManager_c::SetWindData(RwV3d* dir, float* speed) {
    m_pWindDir = dir;
    m_pfWindSpeed = speed;
}

// 0x4A9440
RwMatrix* FxManager_c::FxRwMatrixCreate() {
    return ((RwMatrix * (__thiscall*)(FxManager_c*))0x4A9440)(this);
}

// 0x4A9460
void FxManager_c::FxRwMatrixDestroy(RwMatrix* matrix) {
    m_nCurrentMatrix--;
}

// 0x4A9500
bool FxManager_c::ShouldCreate(FxSystemBP_c* bpSystem, RwMatrix* transform, RwMatrix* objectMatrix, bool ignoreBoundingChecks) {
    return ((bool(__thiscall*)(FxManager_c*, FxSystemBP_c*, RwMatrix*, RwMatrix*, bool))0x4A9500)(this, bpSystem, transform, objectMatrix, ignoreBoundingChecks);
}

// 0x4A95C0
FxSystem_c* FxManager_c::CreateFxSystem(FxSystemBP_c* bpSystem, RwMatrix* transform, RwMatrix* objectMatrix, bool ignoreBoundingChecks) {
    return plugin::CallMethodAndReturn<FxSystem_c*, 0x4A95C0, FxManager_c*, FxSystemBP_c*, RwMatrix*, RwMatrix*, bool>(this, bpSystem, transform, objectMatrix, ignoreBoundingChecks);

    /*
    if (!bpSystem || !FxManager_c::ShouldCreate(bpSystem, transform, objectMatrix, ignoreBoundingChecks))
        return nullptr;

    auto fx = new FxSystem_c();
    fx->Init(bpSystem, transform, objectMatrix);
    m_fxSystems.AddItem(&fx->m_link);

    const auto quality = g_fx.GetFxQuality();
    switch (quality) {
    case FXQUALITY_LOW:
        fx->SetRateMult(0.5f);
        break;
    case FXQUALITY_MEDIUM:
        fx->SetRateMult(0.75f);
        break;
    case FXQUALITY_HIGH:
    case FXQUALITY_VERY_HIGH:
        fx->SetRateMult(1.0f);
        break;
    };

    return fx;
    */
}

// char* name -> const char*
// 0x4A9BB0
FxSystem_c* FxManager_c::CreateFxSystem(const char* name, RwMatrix* transform, RwMatrix* objectMatrix, bool ignoreBoundingChecks) {
    return plugin::CallMethodAndReturn<FxSystem_c*, 0x4A9BB0, FxManager_c*, const char*, RwMatrix*, RwMatrix*, bool>(this, name, transform, objectMatrix, ignoreBoundingChecks);

    /*
    FxSystemBP_c* bpSystem = FindFxSystemBP(name);
    return CreateFxSystem(bpSystem, transform, objectMatrix, ignoreBoundingChecks);
    */
}

// 0x4A96B0
FxSystem_c* FxManager_c::CreateFxSystem(FxSystemBP_c* bpSystem, RwV3d* position, RwMatrix* objectMatrix, bool ignoreBoundingChecks) {
    return ((FxSystem_c * (__thiscall*)(FxManager_c*, FxSystemBP_c*, RwV3d*, RwMatrix*, bool))0x4A96B0)(this, bpSystem, position, objectMatrix, ignoreBoundingChecks);
}

// char* name -> const char*
// 0x4A9BE0
FxSystem_c* FxManager_c::CreateFxSystem(const char* name, RwV3d* position, RwMatrix* objectMatrix, bool ignoreBoundingChecks) {
    return plugin::CallMethodAndReturn<FxSystem_c*, 0x4A9BE0, FxManager_c*, const char*, RwV3d*, RwMatrix*, bool>(this, name, position, objectMatrix, ignoreBoundingChecks);

    /*
    FxSystemBP_c * bpSystem = FindFxSystemBP(name);
    return CreateFxSystem(bpSystem, position, objectMatrix, ignoreBoundingChecks);
    */
}
