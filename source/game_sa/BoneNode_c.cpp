#include "StdInc.h"
#include "BoneNode_c.h"

void BoneNode_c::InjectHooks() {
    RH_ScopedClass(BoneNode_c);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category! Animation?

    RH_ScopedInstall(Constructor, 0x616B30);
    RH_ScopedInstall(Destructor, 0x616B80);

    RH_ScopedInstall(Init, 0x6177B0);
    //RH_ScopedGlobalInstall(EulerToQuat, 0x6171F0);
    //RH_ScopedGlobalInstall(QuatToEuler, 0x617080);
    //RH_ScopedGlobalInstall(GetIdFromBoneTag, 0x617050);
    //RH_ScopedInstall(ClampLimitsCurrent, 0x6175D0);
    //RH_ScopedInstall(ClampLimitsDefault, 0x617530);
    //RH_ScopedInstall(InitLimits, 0x617490);
    //RH_ScopedInstall(Limit, 0x617650);
    //RH_ScopedInstall(BlendKeyframe, 0x616E30);
    RH_ScopedInstall(GetSpeed, 0x616CB0);
    RH_ScopedInstall(SetSpeed, 0x616CC0);
    RH_ScopedInstall(SetLimits, 0x616C50);
    RH_ScopedInstall(GetLimits, 0x616BF0);
    RH_ScopedInstall(AddChild, 0x616BD0);
    //RH_ScopedInstall(CalcWldMat, 0x616CD0);
}

// 0x6177B0
bool BoneNode_c::Init(int32 boneTag, RpHAnimBlendInterpFrame* interpFrame) {
    m_BoneTag     = boneTag;
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
    plugin::CallMethod<0x617490, BoneNode_c*>(this);
}

// 0x6171F0
RtQuat BoneNode_c::EulerToQuat(RwV3d* angles) {
    return plugin::CallAndReturn<RtQuat, 0x6171F0, RwV3d*>(angles);
}

// 0x617080
RwV3d BoneNode_c::QuatToEuler(RtQuat* quat) {
    return plugin::CallAndReturn<RwV3d, 0x617080, RtQuat*>(quat);
}

// 0x617050
int32 BoneNode_c::GetIdFromBoneTag(ePedBones bone) {
    return plugin::CallAndReturn<int32, 0x617050, ePedBones>(bone);
}

// 0x6175D0
void BoneNode_c::ClampLimitsCurrent(bool LimitX, bool LimitY, bool LimitZ) {
    plugin::CallMethod<0x6175D0, BoneNode_c*, bool, bool, bool>(this, LimitX, LimitY, LimitZ);
}

// 0x617530
void BoneNode_c::ClampLimitsDefault(bool LimitX, bool LimitY, bool LimitZ) {
    plugin::CallMethod<0x617530, BoneNode_c*, bool, bool, bool>(this, LimitX, LimitY, LimitZ);
}

// 0x617650
void BoneNode_c::Limit(float lim) {
    plugin::CallMethod<0x617650, BoneNode_c*, float>(this, lim);
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
RwMatrix* BoneNode_c::CalcWldMat(const RwMatrix* boneMatrix) {
    return plugin::CallMethodAndReturn<RwMatrix*, 0x616CD0, BoneNode_c*, const RwMatrix*>(this, boneMatrix);
}
