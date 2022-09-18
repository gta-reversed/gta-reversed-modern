#include "StdInc.h"
#include "BoneNode_c.h"
#include "BoneNodeManager_c.h"

void BoneNode_c::InjectHooks() {
    RH_ScopedClass(BoneNode_c);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category! Animation?

    RH_ScopedInstall(Constructor, 0x616B30);
    RH_ScopedInstall(Destructor, 0x616B80);

    RH_ScopedInstall(Init, 0x6177B0);
    RH_ScopedInstall(InitLimits, 0x617490);
    RH_ScopedGlobalInstall(EulerToQuat, 0x6171F0);
    RH_ScopedGlobalInstall(QuatToEuler, 0x617080);
    RH_ScopedGlobalInstall(GetIdFromBoneTag, 0x617050);
    RH_ScopedInstall(ClampLimitsCurrent, 0x6175D0);
    RH_ScopedInstall(ClampLimitsDefault, 0x617530);
    RH_ScopedInstall(Limit, 0x617650);
    RH_ScopedInstall(BlendKeyframe, 0x616E30, { .reversed = false });
    RH_ScopedInstall(GetSpeed, 0x616CB0);
    RH_ScopedInstall(SetSpeed, 0x616CC0);
    RH_ScopedInstall(SetLimits, 0x616C50);
    RH_ScopedInstall(GetLimits, 0x616BF0);
    RH_ScopedInstall(AddChild, 0x616BD0);
    RH_ScopedInstall(CalcWldMat, 0x616CD0); // Not tested!!
}

// 0x6177B0
bool BoneNode_c::Init(int32 boneTag, RpHAnimBlendInterpFrame* interpFrame) {
    m_BoneTag     = static_cast<ePedBones>(boneTag);
    m_InterpFrame = interpFrame;
    m_Orientation = interpFrame->orientation;
    m_Pos         = interpFrame->translation;
    m_Parent      = nullptr;

    m_Childs.RemoveAll();
    InitLimits();

    m_Speed = 1.0f;

    return true;
}

// 0x617490
void BoneNode_c::InitLimits() {
    const auto id = GetIdFromBoneTag(m_BoneTag);
    assert(id != -1);
    const auto& boneInfo = BoneNodeManager_c::ms_boneInfos[id]; // Possible out of bounds when `id` = -1 (they don't check for -1) | unnecessary copying

    m_LimitMin.x = boneInfo.m_Max.x - boneInfo.m_Min.x;
    m_LimitMin.y = boneInfo.m_Max.y - boneInfo.m_Min.z;
    m_LimitMin.z = boneInfo.m_Max.z - boneInfo.m_ABC.y;

    m_LimitMax.x = boneInfo.m_Min.y + boneInfo.m_Max.x;
    m_LimitMax.y = boneInfo.m_ABC.x + boneInfo.m_Max.y;
    m_LimitMax.z = boneInfo.m_ABC.z + boneInfo.m_Max.z;
}

// 0x6171F0
void BoneNode_c::EulerToQuat(CVector* angles, CQuaternion* quat) {
    CVector radAngles = {
        DegreesToRadians(angles->x),
        DegreesToRadians(angles->y),
        DegreesToRadians(angles->z)
    };

    float cr = cos(radAngles.x * 0.5f);
    float sr = sin(radAngles.x * 0.5f);
    float cp = cos(radAngles.y * 0.5f);
    float sp = sin(radAngles.y * 0.5f);
    float cy = cos(radAngles.z * 0.5f);
    float sy = sin(radAngles.z * 0.5f);

    quat->w = cr * cp * cy + sr * sp * sy;
    quat->x = sr * cp * cy - cr * sp * sy;
    quat->y = cr * sp * cy + sr * cp * sy;
    quat->z = cr * cp * sy - sr * sp * cy;
}

// 0x617080
void BoneNode_c::QuatToEuler(CQuaternion* quat, CVector* angles) {
    angles->x = atan2f(2.0f * (quat->w * quat->x + quat->y * quat->z), 1.0f - 2.0f * (quat->x * quat->x + quat->y * quat->y));

    float sinp = 2.0f * (quat->w * quat->y - quat->z * quat->x);

    if (abs(sinp) >= 1.0f) {
        angles->y = copysignf(FRAC_TAU_2, sinp);
    } else {
        angles->y = asinf(sinp);
    }

    angles->z = atan2f(2.0f * (quat->w * quat->z + quat->x * quat->y), 1.0f - 2.0f * (quat->y * quat->y + quat->z * quat->z));
}

// 0x617050
int32 BoneNode_c::GetIdFromBoneTag(ePedBones bone) {
    for (auto i = 0u; i < BoneNodeManager_c::ms_boneInfos.size(); i++) {
        if (BoneNodeManager_c::ms_boneInfos[i].m_current == bone) {
            return i;
        }
    }
    return -1;
}

// Empty in Android
// 0x6175D0
void BoneNode_c::ClampLimitsCurrent(bool LimitX, bool LimitY, bool LimitZ) {
    if (*(bool*)0x8D2BD1) // always true
        return;

    CVector angles;
    QuatToEuler(&m_Orientation, &angles);
    if (LimitX) {
        m_LimitMax.x = angles.x;
        m_LimitMin.x = angles.x;
    }
    if (LimitY) {
        m_LimitMax.y = angles.y;
        m_LimitMin.y = angles.y;
    }
    if (LimitZ) {
        m_LimitMax.z = angles.z;
        m_LimitMin.z = angles.z;
    }
}

// Empty in Android
// 0x617530
void BoneNode_c::ClampLimitsDefault(bool LimitX, bool LimitY, bool LimitZ) {
    if (*(bool*)0x8D2BD0) // always true
        return;

    const auto id = GetIdFromBoneTag(m_BoneTag);
    const auto boneInfo = BoneNodeManager_c::ms_boneInfos[id];

    if (LimitX) {
        m_LimitMax.x = boneInfo.m_Min.x;
        m_LimitMin.x = boneInfo.m_Min.x;
    }
    if (LimitY) {
        m_LimitMax.y = boneInfo.m_Min.y;
        m_LimitMin.y = boneInfo.m_Min.y;
    }
    if (LimitZ) {
        m_LimitMax.z = boneInfo.m_Min.z;
        m_LimitMin.z = boneInfo.m_Min.z;
    }
}

// argumnet (float blend) - ignored
// 0x617650
void BoneNode_c::Limit(float blend) {
    CVector eulerOrientation{};

    BoneNode_c::QuatToEuler(&m_Orientation, &eulerOrientation);

    eulerOrientation.x = std::clamp(eulerOrientation.x, m_LimitMin.x, m_LimitMax.x);
    eulerOrientation.y = std::clamp(eulerOrientation.y, m_LimitMin.y, m_LimitMax.y);

    float clampZMin = m_LimitMin.z;
    float clampZMax = m_LimitMax.z;

    if (m_BoneTag == ePedBones::BONE_HEAD) {
        float maxHeadZ = BoneNodeManager_c::ms_boneInfos[GetIdFromBoneTag(ePedBones::BONE_HEAD)].m_Max.z;
        float multy = std::max(abs(eulerOrientation.x) / -45.0f + 1.0f, 0.0f);

        clampZMin = maxHeadZ + (m_LimitMin.z - maxHeadZ) * multy;
        clampZMax = maxHeadZ + (m_LimitMax.z - maxHeadZ) * multy;
    }

    eulerOrientation.z = std::clamp(eulerOrientation.z, clampZMin, clampZMax);

    BoneNode_c::EulerToQuat(&eulerOrientation, &m_Orientation);
}

// 0x616E30
void BoneNode_c::BlendKeyframe(float blend) {
    plugin::CallMethod<0x616E30, BoneNode_c*, float>(this, blend);
}

// 0x616CB0
float BoneNode_c::GetSpeed() const {
    return m_Speed;
}

// 0x616CC0
void BoneNode_c::SetSpeed(float speed) {
    m_Speed = speed;
}

// 0x616C50
void BoneNode_c::SetLimits(eRotationAxis axis, float min, float max) {
    switch (axis) {
    case AXIS_X:
        m_LimitMin.x = min;
        m_LimitMax.x = max;
        break;
    case AXIS_Y: {
        m_LimitMin.y = min;
        m_LimitMax.y = max;
        break;
    }
    case AXIS_Z: {
        m_LimitMin.z = min;
        m_LimitMax.z = max;
        break;
    }
    }
}

// 0x616BF0
void BoneNode_c::GetLimits(eRotationAxis axis, float& min, float& max) {
    switch (axis) {
    case AXIS_X:
        min = m_LimitMin.x;
        max = m_LimitMax.x;
        break;
    case AXIS_Y: {
        min = m_LimitMin.y;
        max = m_LimitMax.y;
        break;
    }
    case AXIS_Z: {
        min = m_LimitMin.z;
        max = m_LimitMax.z;
        break;
    }
    }
}

// 0x616BD0
void BoneNode_c::AddChild(BoneNode_c* children) {
    children->m_Parent = this;
    m_Childs.AddItem(children);
}

// 0x616CD0
void BoneNode_c::CalcWldMat(const RwMatrix* boneMatrix) {
    RwMatrix math;

    float dst = 2.0f / ((m_Orientation.x * m_Orientation.x) + (m_Orientation.y * m_Orientation.y) + (m_Orientation.z * m_Orientation.z) +
                        (m_Orientation.w * m_Orientation.w));

	math.right = {
                    1.0f - ((m_Orientation.y * (m_Orientation.y * dst)) + (m_Orientation.z + (m_Orientation.z * dst))),
                    (m_Orientation.x * (m_Orientation.y * dst)) + (m_Orientation.w * (m_Orientation.z * dst)),
                    (m_Orientation.z * (m_Orientation.x * dst)) - (m_Orientation.w * (m_Orientation.y * dst))
    };

    math.up = {
                (m_Orientation.x * (m_Orientation.y * dst)) - (m_Orientation.w * (m_Orientation.z * dst)),
                1.0f - ((m_Orientation.z + (m_Orientation.z * dst)) + (m_Orientation.x * (m_Orientation.x * dst))),
                (m_Orientation.y * (m_Orientation.z * dst)) + (m_Orientation.w * (m_Orientation.x * dst))
    };
    math.at = {
                (m_Orientation.z * (m_Orientation.x * dst)) + (m_Orientation.w * (m_Orientation.y * dst)),
                (m_Orientation.y * (m_Orientation.z * dst)) - (m_Orientation.w * (m_Orientation.x * dst)),
                1.0f - ((m_Orientation.x * (m_Orientation.x * dst)) + (m_Orientation.y * (m_Orientation.y * dst)))
    };

    math.flags = 3;
    math.pos = m_Pos;

    RwMatrixMultiply(&m_WorldMat, &math, boneMatrix);

    for (auto bone = m_Childs.GetHead(); bone; bone = m_Childs.GetNext(bone)) {
        bone->CalcWldMat(&m_WorldMat);
    }
}
