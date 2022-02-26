#include "StdInc.h"
#include "IKChain_c.h"
#include "BoneNodeManager_c.h"

void IKChain_c::InjectHooks() {
    RH_ScopedClass(IKChain_c);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Exit, 0x617870);
    // RH_ScopedInstall(Update, 0x6184B0);
    // RH_ScopedInstall(Init, 0x618370);
    // RH_ScopedInstall(IsAtTarget, 0x617F30);
    // RH_ScopedInstall(IsFacingTarget, 0x617E60);
    // RH_ScopedInstall(UpdateTarget, 0x617E50);
    // RH_ScopedInstall(UpdateOffset, 0x617E20);
    // RH_ScopedInstall(ClampLimits, 0x618520);
    // RH_ScopedInstall(UpdateEntity, 0x617E00);
    // RH_ScopedInstall(GetBoneNodeFromTag, 0x617C60);
    // RH_ScopedInstall(GetPriority, 0x617C50);
    // RH_ScopedInstall(SetOffsetPos, 0x617C30);
    // RH_ScopedInstall(SetOffsetBoneTag, 0x617C20);
    // RH_ScopedInstall(SetBlend, 0x617C10);
    // RH_ScopedInstall(MoveBonesToTarget, 0x6178B0);
    // RH_ScopedInstall(SetupBones, 0x617CA0);
    // RH_ScopedInstall(GetLimits, 0x618590);
}

// Methods
// 0x617870
void IKChain_c::Exit() {
    for (auto i = 0; i < m_count; i++) {
        g_boneNodeMan.ReturnBoneNode(m_bones[i]);
    }
    delete[] m_bones;
    m_bones = nullptr;
}

// 0x6184B0
void IKChain_c::Update(float timeStep) {
    plugin::CallMethod<0x6184B0, IKChain_c*, float>(this, timeStep);
}

// 0x618370
bool IKChain_c::Init(const char* name, int32 IndexInList, CPed* ped, int32 animId, RwV3d bonePosn, int32 animId_1, CEntity* entity, int32 offsetBoneTag, RwV3d posn, float a11,
                     int32 priority) {
    return plugin::CallMethodAndReturn<bool, 0x618370, IKChain_c*, const char*, int32, CPed*, int32, RwV3d, int32, CEntity*, int32, RwV3d, float, int32>(
        this, name, IndexInList, ped, animId, bonePosn, animId_1, entity, offsetBoneTag, posn, a11, priority);
}

// 0x617F30
bool IKChain_c::IsAtTarget(float a2, float* a3) {
    return plugin::CallMethodAndReturn<bool, 0x617F30, IKChain_c*, float, float*>(this, a2, a3);
}

// 0x617E60
bool IKChain_c::IsFacingTarget() {
    return plugin::CallMethodAndReturn<bool, 0x617E60, IKChain_c*>(this);
}

// 0x617E50
void IKChain_c::UpdateTarget(uint8 target) {
    plugin::CallMethod<0x617E50, IKChain_c*, uint8>(this, target);
}

// 0x617E20
void IKChain_c::UpdateOffset(int32 offsetBoneTag, RwV3d offsetPosn) {
    plugin::CallMethod<0x617E20, IKChain_c*, int32, RwV3d>(this, offsetBoneTag, offsetPosn);
}

// 0x618520
void IKChain_c::ClampLimits(int32 a1, uint8 a2, uint8 a3, uint8 a4, int32 a5) {
    plugin::CallMethod<0x618520, IKChain_c*, int32, uint8, uint8, uint8, int32>(this, a1, a2, a3, a4, a5);
}

// 0x617E00
void IKChain_c::UpdateEntity(CEntity* entity) {
    plugin::CallMethod<0x617E00, IKChain_c*, CEntity*>(this, entity);
}

// 0x617C60
BoneNode_c* IKChain_c::GetBoneNodeFromTag(int32 a2) {
    return plugin::CallMethodAndReturn<BoneNode_c*, 0x617C60, IKChain_c*, int32>(this, a2);
}

// 0x617C50
int8 IKChain_c::GetPriority() {
    return plugin::CallMethodAndReturn<int8, 0x617C50, IKChain_c*>(this);
}

// 0x617C30
void IKChain_c::SetOffsetPos(RwV3d value) {
    plugin::CallMethod<0x617C30, IKChain_c*, RwV3d>(this, value);
}

// 0x617C20
void IKChain_c::SetOffsetBoneTag(int32 value) {
    plugin::CallMethod<0x617C20, IKChain_c*, int32>(this, value);
}

// 0x617C10
void IKChain_c::SetBlend(float value) {
    plugin::CallMethod<0x617C10, IKChain_c*, float>(this, value);
}

// 0x6178B0
void IKChain_c::MoveBonesToTarget() {
    plugin::CallMethod<0x6178B0, IKChain_c*>(this);
}

// 0x617CA0
void IKChain_c::SetupBones(int32 a2, RwV3d posn, int32 animId, AnimBlendFrameData* a7) {
    plugin::CallMethod<0x617CA0, IKChain_c*, int32, RwV3d, int32, AnimBlendFrameData*>(this, a2, posn, animId, a7);
}

// 0x618590
void IKChain_c::GetLimits(int32 a2, int32 type, float* a3, float* a4) {
    plugin::CallMethod<0x618590>(this, a2, type, a3, a4);
}
