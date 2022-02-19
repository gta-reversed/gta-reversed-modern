#include "StdInc.h"
#include "InteriorManager_c.h"

void InteriorManager_c::InjectHooks() {
    RH_ScopedClass(InteriorManager_c);
    RH_ScopedCategory("Interior");

    // Constructors (1x)
    // RH_ScopedInstall(Constructor, 0x5984C0);

    // Destructors (1x)
    // RH_ScopedInstall(Destructor, 0x598580);

    // Static functions (3x)
    // RH_ScopedGlobalInstall(AddSameGroupEffectInfos, 0x598430);
    // RH_ScopedGlobalInstall(AreAnimsLoaded, 0x5980F0);

    // Methods (19x)
    // RH_ScopedInstall(PruneVisibleEffects, 0x598A60);
    // RH_ScopedInstall(Exit, 0x598010);
    // RH_ScopedInstall(GetVisibleEffects, 0x598D80);
    // RH_ScopedInstall(IsInteriorEffectVisible, 0x598690);
    // RH_ScopedInstall(GetPedsInterior, 0x598620);
    // RH_ScopedInstall(ReturnInteriorToPool, 0x5984B0);
    // RH_ScopedInstall(GetInteriorFromPool, 0x5984A0);
    // RH_ScopedInstall(GetVectorsInterior, 0x5983D0);
    // RH_ScopedInstall(SetStealableObjectStolen, 0x598390);
    // RH_ScopedOverloadedInstall(FindStealableObjectId, "", 0x598360,  int32(InteriorManager_c::*)(CEntity *));
    // RH_ScopedOverloadedInstall(FindStealableObjectId, "", 0x5982F0,  int32(InteriorManager_c::*)(int32, int32, CVector));
    // RH_ScopedInstall(HasInteriorHadStealDataSetup, 0x5982B0);
    // RH_ScopedInstall(IsGroupActive, 0x598280);
    // RH_ScopedInstall(GetPedsInteriorGroup, 0x598240);
    // RH_ScopedInstall(SetEntryExitPtr, 0x598180);
    // RH_ScopedInstall(GetBoundingBox, 0x598090);
    // RH_ScopedInstall(ActivatePeds, 0x598080);
    // RH_ScopedInstall(inlined_prune_visible_effects, 0x598070);
    // RH_ScopedInstall(Update, 0x598F50);
    // RH_ScopedInstall(Init, 0x5C0500);
}

// 0x5984C0
InteriorManager_c::InteriorManager_c() {}

// 0x5984C0
InteriorManager_c* InteriorManager_c::Constructor() {
    this->InteriorManager_c::InteriorManager_c();
    return this;
}

// 0x598580
InteriorManager_c::~InteriorManager_c() {}

// 0x598580
InteriorManager_c* InteriorManager_c::Destructor() {
    this->InteriorManager_c::~InteriorManager_c();
    return this;
}

// Static functions
// 0x598A60
void InteriorManager_c::PruneVisibleEffects(InteriorEffectInfo_t* a1, int32 a2, int32 a3, float a4) {
    plugin::CallMethod<0x598A60, InteriorManager_c*, InteriorEffectInfo_t*, int32, int32, float>(this, a1, a2, a3, a4);
}

// 0x598430
int8_t InteriorManager_c::AddSameGroupEffectInfos(InteriorEffectInfo_t* a1, int32 a2) {
    return plugin::CallAndReturn<int8_t, 0x598430, InteriorEffectInfo_t*, int32>(a1, a2);
}

// 0x5980F0
bool InteriorManager_c::AreAnimsLoaded(int32 animBlock) {
    return plugin::CallAndReturn<bool, 0x5980F0, int32>(animBlock);
}

// Methods
// 0x598010
void InteriorManager_c::Exit() {
    plugin::CallMethod<0x598010, InteriorManager_c*>(this);
}

// 0x598D80
int32 InteriorManager_c::GetVisibleEffects(InteriorEffectInfo_t* interiorEffect, int32 totalEffects) {
    return plugin::CallMethodAndReturn<int32, 0x598D80, InteriorManager_c*, InteriorEffectInfo_t*, int32>(this, interiorEffect, totalEffects);
}

// 0x598690
int32 InteriorManager_c::IsInteriorEffectVisible(C2dEffect* effect, CEntity* entity) {
    return plugin::CallMethodAndReturn<int32, 0x598690, InteriorManager_c*, C2dEffect*, CEntity*>(this, effect, entity);
}

// 0x598620
int32 InteriorManager_c::GetPedsInterior(CPed* a2) {
    return plugin::CallMethodAndReturn<int32, 0x598620, InteriorManager_c*, CPed*>(this, a2);
}

// 0x5984B0
int32 InteriorManager_c::ReturnInteriorToPool(Interior_c* a2) {
    return plugin::CallMethodAndReturn<int32, 0x5984B0, InteriorManager_c*, Interior_c*>(this, a2);
}

// 0x5984A0
ListItem_c* InteriorManager_c::GetInteriorFromPool() {
    return plugin::CallMethodAndReturn<ListItem_c*, 0x5984A0, InteriorManager_c*>(this);
}

// 0x5983D0
int32 InteriorManager_c::GetVectorsInterior(CVector* a2) {
    return plugin::CallMethodAndReturn<int32, 0x5983D0, InteriorManager_c*, CVector*>(this, a2);
}

// 0x598390
int32 InteriorManager_c::SetStealableObjectStolen(CEntity* a2, uint8 a3) {
    return plugin::CallMethodAndReturn<int32, 0x598390, InteriorManager_c*, CEntity*, uint8>(this, a2, a3);
}

// 0x598360
int32 InteriorManager_c::FindStealableObjectId(CEntity* a2) {
    return plugin::CallMethodAndReturn<int32, 0x598360, InteriorManager_c*, CEntity*>(this, a2);
}

// 0x5982F0
int32 InteriorManager_c::FindStealableObjectId(int32 interiorId, int32 modelId, CVector point) {
    return plugin::CallMethodAndReturn<int32, 0x5982F0, InteriorManager_c*, int32, int32, CVector>(this, interiorId, modelId, point);
}

// 0x5982B0
int8_t InteriorManager_c::HasInteriorHadStealDataSetup(Interior_c* a2) {
    return plugin::CallMethodAndReturn<int8_t, 0x5982B0, InteriorManager_c*, Interior_c*>(this, a2);
}

// 0x598280
int8_t InteriorManager_c::IsGroupActive(int32 group) {
    return plugin::CallMethodAndReturn<int8_t, 0x598280, InteriorManager_c*, int32>(this, group);
}

// 0x598240
ListItem_c* InteriorManager_c::GetPedsInteriorGroup(CPed* ped) {
    return plugin::CallMethodAndReturn<ListItem_c*, 0x598240, InteriorManager_c*, CPed*>(this, ped);
}

// 0x598180
int32 InteriorManager_c::SetEntryExitPtr(CEntryExit* a2) {
    return plugin::CallMethodAndReturn<int32, 0x598180, InteriorManager_c*, CEntryExit*>(this, a2);
}

// 0x598090
int8_t InteriorManager_c::GetBoundingBox(CEntity* a2, CVector* a3) {
    return plugin::CallMethodAndReturn<int8_t, 0x598090, InteriorManager_c*, CEntity*, CVector*>(this, a2, a3);
}

// 0x598080
int8_t InteriorManager_c::ActivatePeds(uint8 enable) {
    return plugin::CallMethodAndReturn<int8_t, 0x598080, InteriorManager_c*, uint8>(this, enable);
}

// 0x598070
int8_t InteriorManager_c::inlined_prune_visible_effects(int8_t prune) {
    return plugin::CallMethodAndReturn<int8_t, 0x598070, InteriorManager_c*, int8_t>(this, prune);
}

// 0x598F50
int8_t InteriorManager_c::Update() {
    return plugin::CallMethodAndReturn<int8_t, 0x598F50, InteriorManager_c*>(this);
}

// 0x5C0500
void InteriorManager_c::Init() {
    plugin::CallMethod<0x5C0500, InteriorManager_c*>(this);
}
