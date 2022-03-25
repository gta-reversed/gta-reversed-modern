#include "StdInc.h"
#include "BoneNodeManager_c.h"

void BoneNodeManager_c::InjectHooks() {
    RH_ScopedClass(BoneNodeManager_c);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(Init, 0x6173F0);
    // RH_ScopedInstall(Exit, 0x617420);
    // RH_ScopedInstall(Reset, 0x617430);
    // RH_ScopedInstall(GetBoneNode, 0x617460);
    // RH_ScopedInstall(ReturnBoneNode, 0x617470);
    // RH_ScopedInstall(GetNumBoneNodesLeft, 0x617480);
}

// 0x6173F0
bool BoneNodeManager_c::Init() {
    return plugin::CallMethodAndReturn<int8_t, 0x6173F0, BoneNodeManager_c*>(this);
}

// 0x617420
void BoneNodeManager_c::Exit() {
    return plugin::CallMethodAndReturn<void, 0x617420, BoneNodeManager_c*>(this);
}

// 0x617430
void BoneNodeManager_c::Reset() {
    return plugin::CallMethodAndReturn<void, 0x617430, BoneNodeManager_c*>(this);
}

// 0x617460
BoneNode_c* BoneNodeManager_c::GetBoneNode() {
    return plugin::CallMethodAndReturn<BoneNode_c*, 0x617460, BoneNodeManager_c*>(this);
}

// 0x617470
void BoneNodeManager_c::ReturnBoneNode(BoneNode_c* a2) {
    return plugin::CallMethodAndReturn<void, 0x617470, BoneNodeManager_c*, BoneNode_c*>(this, a2);
}

// 0x617480
int32 BoneNodeManager_c::GetNumBoneNodesLeft() {
    return plugin::CallMethodAndReturn<int32, 0x617480, BoneNodeManager_c*>(this);
}
