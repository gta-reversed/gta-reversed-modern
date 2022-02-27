#include "StdInc.h"
#include "IKChain_c.h"
#include "BoneNodeManager_c.h"

void IKChain_c::InjectHooks() {
    RH_ScopedClass(IKChain_c);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Exit, 0x617870);
    RH_ScopedInstall(Update, 0x6184B0);
    RH_ScopedInstall(IsAtTarget, 0x617F30);
    RH_ScopedInstall(Init, 0x618370);
    RH_ScopedInstall(IsFacingTarget, 0x617E60);
    RH_ScopedInstall(UpdateTarget, 0x617E50);
    RH_ScopedInstall(UpdateOffset, 0x617E20);
    RH_ScopedInstall(ClampLimits, 0x618520);
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
    m_matrix = &m_ped->GetBoneMatrix(m_bone);
    m_bones[m_count - 1]->CalcWldMat(m_matrix);
    MoveBonesToTarget();
    for (auto&& bone : GetBones()) {
        bone->BlendKeyframe(m_blend);
    }
}

// 0x618370
bool IKChain_c::Init(const char* name, int32 IndexInList, CPed* ped, ePedBones bone, RwV3d bonePosn, ePedBones bone2, CEntity* entity, int32 offsetBoneTag, RwV3d posn, float speed,
                     int8 priority) {
    m_ped = ped;

    const auto frames = m_ped->GetAnimBlendData().m_pFrames;

    if (frames[0].m_bCheckBlendNodeClumpKeyFrames || !frames[0].m_bUpdatingFrame) {
        return false;
    }

    if (!m_ped->bHasBeenRendered) {
        return false;
    }

    // Check if frame of this bone has non-zero translation 
    {
        const auto& boneFrame = frames[RpHAnimIDGetIndex(&m_ped->GetAnimHierarchy(), (RwInt32)bone)].m_pIFrame;
        if (CVector{ boneFrame->translation }.IsZero()) {
            return false;
        }
    }

    m_ped->RegisterReference(m_ped);

    m_bones = nullptr;
    SetupBones(bone, bonePosn, bone2, frames);
    m_bonePosn = bonePosn;
    m_blend = 0.f;
    m_bone1 = bone;

    UpdateEntity(entity);

    m_offsetBoneTag = offsetBoneTag;
    m_offsetPos = posn;
    m_speed = speed;
    m_targetMB = 1;
    m_indexInList = IndexInList;
    m_priority = priority;

    return true;
}

// 0x617F30
bool IKChain_c::IsAtTarget(float maxDist, float& outDist) {
    // They used RwV3d stuff, but that's ugly.
    const auto dist = (m_vec - m_bones[0]->GetPosition()).Magnitude();
    if (outDist) {
        outDist = dist;
    }
    return dist <= maxDist && m_blend > 0.98f;
}

// 0x617E60
bool IKChain_c::IsFacingTarget() {
    // Geniune cancer :D

    RwV3d targetPos;
    RwV3dTransformVector(&targetPos, &m_bonePosn, &m_bones[0]->m_worldMat);
    RwV3dNormalize(&targetPos, &targetPos);

    RwV3d dir;
    RwV3dSub(&dir, &m_vec, &targetPos);
    RwV3dNormalize(&dir, &dir);

    return RwV3dDotProduct(&dir, &targetPos) >= 0.95f && m_blend > 0.98f;
}

// 0x617E50
void IKChain_c::UpdateTarget(uint8 target) {
    m_targetMB = target;
}

// 0x617E20
void IKChain_c::UpdateOffset(int32 offsetBoneTag, RwV3d offsetPosn) {
    m_offsetBoneTag = offsetBoneTag;
    m_offsetPos = offsetPosn;
}

// 0x618520
void IKChain_c::ClampLimits(int32 boneTag, uint8 a2, uint8 a3, uint8 a4, bool useCurrentLimits) {
    auto& bone = *GetBoneNodeFromTag(boneTag);
    if (useCurrentLimits) {
        bone.ClampLimitsCurrent(a2, a3, a4);
    } else {
        bone.ClampLimitsDefault(a2, a3, a4);
    }
}

// 0x617E00
void IKChain_c::UpdateEntity(CEntity* entity) {
    // NOTE: No unregistering the ref?
    m_entity = entity;
    if (entity) {
        m_entity->RegisterReference(m_entity);
    }
}

// 0x617C60
BoneNode_c* IKChain_c::GetBoneNodeFromTag(int32 tag) {
    const auto it = rng::find_if(GetBones(), [tag](auto&& b) { return b->m_boneTag == tag; });
    return it != GetBones().end() ? *it : nullptr;
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
