#include "StdInc.h"
#include "BoneNode_c.h"

void BoneNode_c::InjectHooks() {
    RH_ScopedClass(BoneNode_c);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Constructor, 0x616B30);
    RH_ScopedInstall(Destructor, 0x616B80);

    //RH_ScopedGlobalInstall(EulerToQuat, 0x6171F0);
    //RH_ScopedGlobalInstall(QuatToEuler, 0x617080);
    //RH_ScopedGlobalInstall(GetIdFromBoneTag, 0x617050);
    //RH_ScopedInstall(ClampLimitsCurrent, 0x6175D0);
    //RH_ScopedInstall(ClampLimitsDefault, 0x617530);
    //RH_ScopedInstall(InitLimits, 0x617490);
    //RH_ScopedInstall(Limit, 0x617650);
    //RH_ScopedInstall(BlendKeyframe, 0x616E30);
    //RH_ScopedInstall(SetSpeed, 0x616CC0);
    //RH_ScopedInstall(GetSpeed, 0x616CB0);
    //RH_ScopedInstall(SetLimits, 0x616C50);
    //RH_ScopedInstall(GetLimits, 0x616BF0);
    //RH_ScopedInstall(AddChild, 0x616BD0);
    //RH_ScopedInstall(CalcWldMat, 0x616CD0);
    //RH_ScopedInstall(Init, 0x6177B0);
}

// 0x616B30
BoneNode_c::BoneNode_c() {
    // Done by the compiler
}

// 0x616B80
BoneNode_c::~BoneNode_c() {
    // Done by the compiler
}

// 0x6171F0
RtQuat BoneNode_c::EulerToQuat(RwV3d* angles) {
    plugin::CallAndReturn<RtQuat, 0x6171F0, RwV3d*>(angles);
}

// 0x617080
RwV3d BoneNode_c::QuatToEuler(RtQuat* quat) {
    plugin::CallAndReturn<RwV3d, 0x617080, RtQuat*>(quat);
}

// 0x617050
int32 BoneNode_c::GetIdFromBoneTag(ePedBones bone) {
    return plugin::CallAndReturn<int32, 0x617050, ePedBones>(bone);
}

// 0x6175D0
void BoneNode_c::ClampLimitsCurrent(uint8 a2, uint8 a3, uint8 a4) {
    plugin::CallMethod<0x6175D0, BoneNode_c*, uint8, uint8, uint8>(this, a2, a3, a4);
}

// 0x617530
void BoneNode_c::ClampLimitsDefault(uint8, uint8, uint8) {
    plugin::CallMethod<0x617530, BoneNode_c*, uint8, uint8, uint8>(this, , , );
}

// 0x617490
void BoneNode_c::InitLimits() {
    plugin::CallMethod<0x617490, BoneNode_c*>(this);
}

// 0x617650
void BoneNode_c::Limit(float float_1) {
    plugin::CallMethod<0x617650, BoneNode_c*, float>(this, float_1);
}

// 0x616E30
void BoneNode_c::BlendKeyframe(float blend) {
    plugin::CallMethod<0x616E30, BoneNode_c*, float>(this, blend);
}

// 0x616CC0
void BoneNode_c::SetSpeed(float) {
    plugin::CallMethod<0x616CC0, BoneNode_c*, float>(this, );
}

// 0x616CB0
double BoneNode_c::GetSpeed() {
    return plugin::CallMethodAndReturn<double, 0x616CB0, BoneNode_c*>(this);
}

// 0x616C50
void BoneNode_c::SetLimits(int32 type, float min, float max) {
    plugin::CallMethod<0x616C50, BoneNode_c*, int32, float, float>(this, type, min, max);
}

// 0x616BF0
void BoneNode_c::GetLimits(int32 type, float* pMin, float* pMax) {
    plugin::CallMethod<0x616BF0, BoneNode_c*, int32, float*, float*>(this, type, pMin, pMax);
}

// 0x616BD0
void BoneNode_c::AddChild(BoneNode_c* children) {
    plugin::CallMethod<0x616BD0, BoneNode_c*, BoneNode_c*>(this, children);
}

// 0x616CD0
RwMatrixTag* BoneNode_c::CalcWldMat(RwMatrixTag* boneMatrix) {
    return plugin::CallMethodAndReturn<RwMatrixTag*, 0x616CD0, BoneNode_c*, RwMatrixTag*>(this, boneMatrix);
}

// 0x6177B0
int8_t BoneNode_c::Init(int32 a2, RpHAnimBlendInterpFrame* a3) {
    return plugin::CallMethodAndReturn<int8_t, 0x6177B0, BoneNode_c*, int32, RpHAnimBlendInterpFrame*>(this, a2, a3);
}
