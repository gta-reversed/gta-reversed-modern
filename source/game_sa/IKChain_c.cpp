#include "StdInc.h"
#include "IKChain_c.h"
#include "BoneNodeManager_c.h"

// CHANGES:
// They used RwV3d stuff, but that's ugly.
// todo: Get rid off RwV3d, RtQuat

void IKChain_c::InjectHooks() {
    RH_ScopedClass(IKChain_c);
    RH_ScopedCategory("Animation");

    RH_ScopedInstall(Init, 0x618370);
    RH_ScopedInstall(Exit, 0x617870);
    RH_ScopedInstall(Update, 0x6184B0);
    RH_ScopedInstall(IsAtTarget, 0x617F30);
    RH_ScopedInstall(IsFacingTarget, 0x617E60);
    RH_ScopedInstall(UpdateTarget, 0x617E50);
    RH_ScopedInstall(UpdateOffset, 0x617E20);
    RH_ScopedInstall(ClampLimits, 0x618520);
    RH_ScopedInstall(UpdateEntity, 0x617E00);
    RH_ScopedInstall(GetBoneNodeFromTag, 0x617C60);
    RH_ScopedInstall(GetPriority, 0x617C50);
    RH_ScopedInstall(SetOffsetPos, 0x617C30);
    RH_ScopedInstall(SetOffsetBoneTag, 0x617C20);
    RH_ScopedInstall(SetBlend, 0x617C10);
    RH_ScopedInstall(MoveBonesToTarget, 0x6178B0);
    RH_ScopedInstall(SetupBones, 0x617CA0);
    RH_ScopedInstall(GetLimits, 0x618590);
}

// 0x618370
bool IKChain_c::Init(const char* name,
                     int32 IndexInList,
                     CPed* ped,
                     ePedBones bone,
                     RwV3d bonePosn,
                     ePedBones bone2,
                     CEntity* entity,
                     int32 offsetBoneTag,
                     RwV3d posn,
                     float speed,
                     int8 priority
) {
    m_Ped = ped;

    const auto frames = m_Ped->GetAnimBlendData().m_Frames;

    if (frames[0].m_bCheckBlendNodeClumpKeyFrames || !frames[0].m_bUpdatingFrame) {
        return false;
    }

    if (!m_Ped->bHasBeenRendered) {
        return false;
    }

    // Check if frame of this bone has non-zero translation
    {
        const auto index = RpHAnimIDGetIndex(&m_Ped->GetAnimHierarchy(), (RwInt32)bone);
        const auto& boneFrame = frames[index].m_pIFrame;
        if (boneFrame->translation.IsZero()) {
            return false;
        }
    }

    m_Ped->RegisterReference(m_Ped);

    m_Bones = nullptr;
    SetupBones(bone, bonePosn, bone2, frames);
    m_BonePosn = bonePosn;
    m_Blend = 0.f;
    m_Bone1 = bone;

    UpdateEntity(entity);

    m_OffsetBoneTag = offsetBoneTag;
    m_OffsetPos = posn;
    m_Speed = speed;
    m_TargetMB = true;
    m_IndexInList = IndexInList;
    m_Priority = priority;

    return true;
}

// 0x617870
void IKChain_c::Exit() {
    for (auto&& bone : GetBones()) {
        g_boneNodeMan.ReturnBoneNode(bone);
    }
    delete[] m_Bones;
    m_Bones = nullptr;
}

// 0x6184B0
void IKChain_c::Update(float timeStep) {
    UNUSED(timeStep);

    m_Matrix = &m_Ped->GetBoneMatrix(m_Bone);
    m_Bones[m_Count - 1]->CalcWldMat(m_Matrix);
    MoveBonesToTarget();
    for (auto&& bone : GetBones()) {
        bone->BlendKeyframe(m_Blend);
    }
}

// 0x617F30
bool IKChain_c::IsAtTarget(float maxDist, float* outDist) const {
    const auto dist = (m_Offset - m_Bones[0]->GetPosition()).Magnitude();
    if (outDist) {
        *outDist = dist;
    }
    return dist <= maxDist && m_Blend > 0.98f;
}

// 0x617E60
bool IKChain_c::IsFacingTarget() {
    // Genuine cancer :D

    RwV3d targetPos;
    RwV3dTransformVector(&targetPos, &m_BonePosn, &m_Bones[0]->m_WorldMat);
    RwV3dNormalize(&targetPos, &targetPos);

    RwV3d dir;
    RwV3dSub(&dir, &m_Offset, &targetPos);
    RwV3dNormalize(&dir, &dir);

    return RwV3dDotProduct(&dir, &targetPos) >= 0.95f && m_Blend > 0.98f;
}

// 0x617E50
void IKChain_c::UpdateTarget(bool target) {
    m_TargetMB = target;
}

// 0x617E20
void IKChain_c::UpdateOffset(int32 offsetBoneTag, CVector offsetPosn) {
    m_OffsetBoneTag = offsetBoneTag;
    m_OffsetPos = offsetPosn;
}

// 0x618520
void IKChain_c::ClampLimits(int32 boneTag, bool LimitX, bool LimitY, bool LimitZ, bool UseCurrentLimits) {
    auto& bone = *GetBoneNodeFromTag(boneTag);
    if (UseCurrentLimits) {
        bone.ClampLimitsCurrent(LimitX, LimitY, LimitZ);
    } else {
        bone.ClampLimitsDefault(LimitX, LimitY, LimitZ);
    }
}

// 0x617E00
void IKChain_c::UpdateEntity(CEntity* entity) {
    // NOTE: No unregistering the ref?
    m_Entity = entity;
    CEntity::SafeRegisterRef(m_Entity);
}

// 0x617C60
BoneNode_c* IKChain_c::GetBoneNodeFromTag(int32 tag) {
    const auto it = rng::find_if(GetBones(), [tag](auto&& b) { return b->m_BoneTag == tag; });
    return it != GetBones().end() ? *it : nullptr;
}

// 0x617C50
int8 IKChain_c::GetPriority() const {
    return m_Priority;
}

// 0x617C30
void IKChain_c::SetOffsetPos(CVector value) {
    m_OffsetPos = value;
}

// 0x617C20
void IKChain_c::SetOffsetBoneTag(int32 value) {
    m_OffsetBoneTag = value;
}

// 0x617C10
void IKChain_c::SetBlend(float value) {
    m_Blend = value;
}

// 0x6178B0
void IKChain_c::MoveBonesToTarget() {
    if (m_TargetMB) {
        if (m_Entity) {
            const auto mat = m_Entity->GetModellingMatrix();
            if (m_OffsetBoneTag == ePedBones::BONE_UNKNOWN) {
                if (mat) {
                    RwV3dTransformPoint(&m_Offset, &m_OffsetPos, mat);
                }
            } else {
                m_Entity->AsPed()->GetBonePosition(m_Offset, (ePedBones)m_OffsetBoneTag);
                if (mat) {
                    RwV3d transformed;
                    RwV3dTransformVector(&transformed, &m_OffsetPos, mat);
                    m_Offset += transformed;
                }
            }
        } else {
            m_Offset = m_OffsetPos;
        }
    }

    auto bones = GetBones();
    if (bones.empty()) {
        return;
    }

    constexpr auto DIST_TOLERANCE = 0.00001f;

    const auto root = bones.front();
    for (auto&& bone : bones) {
        RwV3d transformedBonePos;
        RwV3dTransformVector(&transformedBonePos, &m_BonePosn, &root->GetMatrix()); // Not sure why it's transformed every iteration..

        CVector dirBoneToRoot = transformedBonePos + root->GetPosition() - bone->GetPosition();
        if (dirBoneToRoot.Magnitude() <= DIST_TOLERANCE) {
            continue;
        }
        RwV3dNormalize(&dirBoneToRoot, &dirBoneToRoot);

        CVector dirBoneToOffset = m_Offset - bone->GetPosition();
        if (dirBoneToOffset.Magnitude() <= DIST_TOLERANCE) {
            continue;
        }
        RwV3dNormalize(&dirBoneToOffset, &dirBoneToOffset);

        const auto dot = DotProduct(&dirBoneToOffset, &dirBoneToRoot);
        if (dot >= 0.997f) { // Make sure they don't point in the same direction
            continue;
        }

        const auto matrix = bone->m_Parent ? &bone->m_Parent->GetMatrix() : m_Matrix;

        RtQuat quat;
        RtQuatConvertFromMatrix(&quat, matrix);

        // NOTE: Normalize Quat.. I wonder why there isn't a macro or something for this?
        {
            const auto mag = RwV3dDotProduct(&quat.imag, &quat.imag) + quat.real * quat.real;
            if (mag > 0.f) {
                const auto recp = 1.f / mag;
                quat.real *= recp;
                RwV3dScale(&quat.imag, &quat.imag, -recp);
            }
        }

        CVector cross = CrossProduct(dirBoneToRoot, dirBoneToOffset);

        RwV3d axis;
        RtQuatTransformVectors(&axis, &cross, 1, &quat);

        RtQuatRotate(reinterpret_cast<RtQuat*>(&bone->m_Orientation), &axis, RadiansToDegrees(bone->GetSpeed() * std::acos(dot) * m_Speed), rwCOMBINEPOSTCONCAT);
        bone->Limit(m_Blend); // Originally this was in an `if`, but the variable that was checked was always `true`
        bone->CalcWldMat(matrix);
    }
}

// 0x617CA0
void IKChain_c::SetupBones(ePedBones boneTag, CVector posn, ePedBones bone, AnimBlendFrameData* frames) {
    auto& hier = m_Ped->GetAnimHierarchy();
    m_Matrix = &RpHAnimHierarchyGetMatrixArray(&hier)[RpHAnimIDGetIndex(&hier, (RwInt32)bone)];
    m_Bone = bone;

    BoneNode_c* bones[32]; // TODO: Magic number, BoneNodeManager_c::ms_boneInfos.size()
    m_Count = 0;
    for (auto boneIt = boneTag; boneIt != bone; boneIt = BoneNodeManager_c::ms_boneInfos[BoneNode_c::GetIdFromBoneTag(boneIt)].m_prev) {
        auto* node = g_boneNodeMan.GetBoneNode();
        const auto index = RpHAnimIDGetIndex(&hier, (RwInt32)boneIt);
        node->Init(boneIt, frames[index].m_pIFrame);
        bones[m_Count++] = node;
    }

    m_Bones = new BoneNode_c*[m_Count];
    for (auto i = 0; i < m_Count; i++) {
        m_Bones[i] = bones[i];
    }

    // Link bones together
    for (auto&& bonex : GetBones()) {
        auto prevBone = BoneNodeManager_c::ms_boneInfos[BoneNode_c::GetIdFromBoneTag((ePedBones)bonex->m_BoneTag)].m_prev;
        if (prevBone > -1) {
            if (const auto next = GetBoneNodeFromTag(prevBone)) {
                next->AddChild(bonex);
            }
        }
    }
}

// 0x618590
void IKChain_c::GetLimits(int32 boneTag, eRotationAxis axis, float& outMin, float& outMax) {
    GetBoneNodeFromTag(boneTag)->GetLimits(axis, outMin, outMax);
}
