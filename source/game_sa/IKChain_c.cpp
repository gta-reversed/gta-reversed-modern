#include "StdInc.h"
#include "IKChain_c.h"
#include "BoneNodeManager_c.h"

void IKChain_c::InjectHooks() {
    RH_ScopedClass(IKChain_c);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category! Animation?

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
    m_ped = ped;

    const auto frames = m_ped->GetAnimBlendData().m_Frames;

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

// 0x617F30
bool IKChain_c::IsAtTarget(float maxDist, float& outDist) {
    // They used RwV3d stuff, but that's ugly.
    const auto dist = (m_offset - m_bones[0]->GetPosition()).Magnitude();
    if (outDist) {
        outDist = dist;
    }
    return dist <= maxDist && m_blend > 0.98f;
}

// 0x617E60
bool IKChain_c::IsFacingTarget() {
    // Geniune cancer :D

    RwV3d targetPos;
    RwV3dTransformVector(&targetPos, &m_bonePosn, &m_bones[0]->m_WorldMat);
    RwV3dNormalize(&targetPos, &targetPos);

    RwV3d dir;
    RwV3dSub(&dir, &m_offset, &targetPos);
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
    m_entity = entity;
    if (entity) {
        m_entity->RegisterReference(m_entity);
    }
}

// 0x617C60
BoneNode_c* IKChain_c::GetBoneNodeFromTag(int32 tag) {
    const auto it = rng::find_if(GetBones(), [tag](auto&& b) { return b->m_BoneTag == tag; });
    return it != GetBones().end() ? *it : nullptr;
}

// 0x617C50
int8 IKChain_c::GetPriority() {
    return m_priority;
}

// 0x617C30
void IKChain_c::SetOffsetPos(RwV3d value) {
    m_offsetPos = value;
}

// 0x617C20
void IKChain_c::SetOffsetBoneTag(int32 value) {
    m_offsetBoneTag = value;
}

// 0x617C10
void IKChain_c::SetBlend(float value) {
    m_blend = value;
}

// 0x6178B0
void IKChain_c::MoveBonesToTarget() {
    if (m_targetMB) {
        if (m_entity) {
            const auto mat = m_entity->GetModellingMatrix();
            if (m_offsetBoneTag == ePedBones::BONE_UNKNOWN) {
                if (mat) {
                    RwV3dTransformPoint(&m_offset, &m_offsetPos, mat);
                }
            } else {
                m_entity->AsPed()->GetBonePosition(m_offset, (ePedBones)m_offsetBoneTag);
                if (mat) {
                    RwV3d transformed;
                    RwV3dTransformVector(&transformed, &m_offsetPos, mat);
                    RwV3dAdd(&m_offset, &transformed, &m_offset);
                }
            }
        } else {
            m_offset = m_offsetPos;
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
        RwV3dTransformVector(&transformedBonePos, &m_bonePosn, &root->GetMatrix()); // Not sure why it's transformed every iteration..

        RwV3d dirBoneToRoot; // = transformedBonePos + root->pos - bone->pos
        RwV3dAdd(&dirBoneToRoot, &transformedBonePos, &root->GetPosition());
        RwV3dSub(&dirBoneToRoot, &dirBoneToRoot, &bone->GetPosition());
        if (RwV3dLength(&dirBoneToRoot) <= DIST_TOLERANCE) {
            continue;
        }
        RwV3dNormalize(&dirBoneToRoot, &dirBoneToRoot);

        RwV3d dirBoneToOffset; // = m_offset - bone->pos
        RwV3dSub(&dirBoneToOffset, &m_offset, &bone->GetPosition());
        if (RwV3dLength(&dirBoneToOffset) <= DIST_TOLERANCE) {
            continue;
        }
        RwV3dNormalize(&dirBoneToOffset, &dirBoneToOffset);

        const auto dot = RwV3dDotProduct(&dirBoneToOffset, &dirBoneToRoot);
        if (dot >= 0.997f) { // Make sure they don't point in the same direction
            continue;
        }

        const auto matrix = bone->m_Parent ? &bone->m_Parent->GetMatrix() : m_matrix;

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
        
        RwV3d cross;
        RwV3dCrossProduct(&cross, &dirBoneToRoot, &dirBoneToOffset);

        RwV3d axis;
        RtQuatTransformVectors(&axis, &cross, 1, &quat);

        RtQuatRotate(&bone->m_Orientation, &axis, RWRAD2DEG(bone->GetSpeed() * std::acos(dot) * m_speed), rwCOMBINEPOSTCONCAT);
        bone->Limit(m_blend); // Originally this was in an `if`, but the variable that was checked was always `true`
        bone->CalcWldMat(matrix);
    }
}

// 0x617CA0
void IKChain_c::SetupBones(ePedBones boneTag, RwV3d posn, ePedBones bone, AnimBlendFrameData* frames) {
    auto& hier = m_ped->GetAnimHierarchy();
    m_matrix = &RpHAnimHierarchyGetMatrixArray(&hier)[RpHAnimIDGetIndex(&hier, (RwInt32)bone)];
    m_bone = bone;

    BoneNode_c* bones[32]; // TODO: Magic number, BoneNodeManager_c::ms_boneInfos.size()
    m_count = 0;
    for (auto boneIt = boneTag; boneIt != bone; boneIt = BoneNodeManager_c::ms_boneInfos[BoneNode_c::GetIdFromBoneTag(boneIt)].m_prev) {
        auto node = g_boneNodeMan.GetBoneNode();
        node->Init(boneIt, frames[RpHAnimIDGetIndex(&hier, (RwInt32)boneIt)].m_pIFrame);
        bones[m_count++] = node;
    }

    assert(m_count); // Doesn't really make a whole lot of sense if theres not a single bone
    m_bones = new BoneNode_c*[m_count];
    rng::copy(bones, m_bones);

    // Link bones together
    for (auto&& bonex : GetBones()) {
        auto prevBone = BoneNodeManager_c::ms_boneInfos[BoneNode_c::GetIdFromBoneTag((ePedBones)bonex->m_BoneTag)].m_prev;
        if (prevBone > -1) {
            if (const auto next = GetBoneNodeFromTag(prevBone)) {
                //printf("next: %i\n", nextIdx);
                next->AddChild(bonex);
            }
        }
    }
}

// 0x618590
void IKChain_c::GetLimits(int32 boneTag, eRotationAxis axis, float& outMin, float& outMax) {
    GetBoneNodeFromTag(boneTag)->GetLimits(axis, outMin, outMax);
}
