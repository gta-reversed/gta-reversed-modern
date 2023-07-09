#include "StdInc.h"
#include "InteriorManager_c.h"

void InteriorManager_c::InjectHooks() {
    RH_ScopedClass(InteriorManager_c);
    RH_ScopedCategory("Interior");

    RH_ScopedGlobalInstall(AddSameGroupEffectInfos, 0x598430, { .reversed = false });
    RH_ScopedGlobalInstall(AreAnimsLoaded, 0x5980F0, { .reversed = false });
    RH_ScopedInstall(PruneVisibleEffects, 0x598A60, { .reversed = false });
    RH_ScopedInstall(Exit, 0x598010, { .reversed = false });
    RH_ScopedInstall(GetVisibleEffects, 0x598D80, { .reversed = false });
    RH_ScopedInstall(IsInteriorEffectVisible, 0x598690, { .reversed = false });
    RH_ScopedInstall(GetPedsInterior, 0x598620, { .reversed = false });
    RH_ScopedInstall(ReturnInteriorToPool, 0x5984B0, { .reversed = false });
    RH_ScopedInstall(GetInteriorFromPool, 0x5984A0, { .reversed = false });
    RH_ScopedInstall(GetVectorsInterior, 0x5983D0, { .reversed = false });
    RH_ScopedInstall(SetStealableObjectStolen, 0x598390, { .reversed = false });
    // RH_ScopedOverloadedInstall(FindStealableObjectId, "", 0x598360,  int32(InteriorManager_c::*)(CEntity *));
    // RH_ScopedOverloadedInstall(FindStealableObjectId, "", 0x5982F0,  int32(InteriorManager_c::*)(int32, int32, CVector));
    RH_ScopedInstall(HasInteriorHadStealDataSetup, 0x5982B0, { .reversed = false });
    RH_ScopedInstall(IsGroupActive, 0x598280, { .reversed = false });
    RH_ScopedInstall(GetPedsInteriorGroup, 0x598240, { .reversed = false });
    RH_ScopedInstall(SetEntryExitPtr, 0x598180, { .reversed = false });
    RH_ScopedInstall(GetBoundingBox, 0x598090, { .reversed = false });
    RH_ScopedInstall(ActivatePeds, 0x598080, { .reversed = false });
    RH_ScopedInstall(inlined_prune_visible_effects, 0x598070, { .reversed = false });
    RH_ScopedInstall(Update, 0x598F50, { .reversed = false });
    RH_ScopedInstall(Init, 0x5C0500, { .reversed = false });
}

// 0x5C0500
void InteriorManager_c::Init() {
    plugin::CallMethod<0x5C0500, InteriorManager_c*>(this);
}

// 0x598F50
int8 InteriorManager_c::Update() {
    ZoneScoped;

    return plugin::CallMethodAndReturn<int8, 0x598F50, InteriorManager_c*>(this);
}

// 0x598A60
void InteriorManager_c::PruneVisibleEffects(InteriorEffectInfo_t* effectInfo, int32 a2, int32 a3, float a4) {
    plugin::CallMethod<0x598A60, InteriorManager_c*, InteriorEffectInfo_t*, int32, int32, float>(this, effectInfo, a2, a3, a4);
}

// 0x598430
int8 InteriorManager_c::AddSameGroupEffectInfos(InteriorEffectInfo_t* effectInfo, int32 a2) {
    return plugin::CallAndReturn<int8, 0x598430, InteriorEffectInfo_t*, int32>(effectInfo, a2);
}

// 0x5980F0
bool InteriorManager_c::AreAnimsLoaded(int32 animBlock) {
    return plugin::CallAndReturn<bool, 0x5980F0, int32>(animBlock);
}

// 0x598010
void InteriorManager_c::Exit() {
    plugin::CallMethod<0x598010, InteriorManager_c*>(this);
}

// 0x598D80
int32 InteriorManager_c::GetVisibleEffects(InteriorEffectInfo_t* effectInfo, int32 totalEffects) {
    return plugin::CallMethodAndReturn<int32, 0x598D80, InteriorManager_c*, InteriorEffectInfo_t*, int32>(this, effectInfo, totalEffects);
}

// 0x598690
int32 InteriorManager_c::IsInteriorEffectVisible(C2dEffect* effect, CEntity* entity) {
    return plugin::CallMethodAndReturn<int32, 0x598690, InteriorManager_c*, C2dEffect*, CEntity*>(this, effect, entity);
}

// 0x598620
int32 InteriorManager_c::GetPedsInterior(CPed* ped) {
    return plugin::CallMethodAndReturn<int32, 0x598620, InteriorManager_c*, CPed*>(this, ped);
}

// 0x5984B0
int32 InteriorManager_c::ReturnInteriorToPool(Interior_c* interior) {
    return plugin::CallMethodAndReturn<int32, 0x5984B0, InteriorManager_c*, Interior_c*>(this, interior);
}

// 0x5984A0
ListItem_c* InteriorManager_c::GetInteriorFromPool() {
    return plugin::CallMethodAndReturn<ListItem_c*, 0x5984A0, InteriorManager_c*>(this);
}

// 0x5983D0
int32 InteriorManager_c::GetVectorsInterior(CVector* pos) {
    return plugin::CallMethodAndReturn<int32, 0x5983D0, InteriorManager_c*, CVector*>(this, pos);
}

// 0x598390
int32 InteriorManager_c::SetStealableObjectStolen(CEntity* entity, uint8 a3) {
    return plugin::CallMethodAndReturn<int32, 0x598390, InteriorManager_c*, CEntity*, uint8>(this, entity, a3);
}

// 0x598360
int32 InteriorManager_c::FindStealableObjectId(CEntity* entity) {
    return plugin::CallMethodAndReturn<int32, 0x598360, InteriorManager_c*, CEntity*>(this, entity);
}

// 0x5982F0
int32 InteriorManager_c::FindStealableObjectId(int32 interiorId, int32 modelId, CVector point) {
    return plugin::CallMethodAndReturn<int32, 0x5982F0, InteriorManager_c*, int32, int32, CVector>(this, interiorId, modelId, point);
}

// 0x5982B0
bool InteriorManager_c::HasInteriorHadStealDataSetup(Interior_c* interior) {
    return plugin::CallMethodAndReturn<bool, 0x5982B0, InteriorManager_c*, Interior_c*>(this, interior);
}

// 0x598280
int8 InteriorManager_c::IsGroupActive(int32 group) {
    return plugin::CallMethodAndReturn<int8, 0x598280, InteriorManager_c*, int32>(this, group);
}

// 0x598240
ListItem_c* InteriorManager_c::GetPedsInteriorGroup(CPed* ped) {
    return plugin::CallMethodAndReturn<ListItem_c*, 0x598240, InteriorManager_c*, CPed*>(this, ped);
}

// 0x598180
int32 InteriorManager_c::SetEntryExitPtr(CEntryExit* exit) {
    return plugin::CallMethodAndReturn<int32, 0x598180, InteriorManager_c*, CEntryExit*>(this, exit);
}

// 0x598090
int8 InteriorManager_c::GetBoundingBox(CEntity* entity, CVector* pos) {
    return plugin::CallMethodAndReturn<int8, 0x598090, InteriorManager_c*, CEntity*, CVector*>(this, entity, pos);
}

// 0x598080
int8 InteriorManager_c::ActivatePeds(uint8 enable) {
    return plugin::CallMethodAndReturn<int8, 0x598080, InteriorManager_c*, uint8>(this, enable);
}
