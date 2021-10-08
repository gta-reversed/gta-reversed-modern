#include "StdInc.h"

#include "IKChainManager_c.h"
// #include "IKChain_c.h"

IKChainManager_c& g_ikChainMan = *(IKChainManager_c*)0xC15448;

void IKChainManager_c::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("IKChainManager_c", "IsArmPointing", 0x6182B0, &IKChainManager_c::IsArmPointing);
    // Install("IKChainManager_c", "AbortPointArm", 0x6182F0, &IKChainManager_c::AbortPointArm);
    // Install("IKChainManager_c", "CanAccept", 0x618800, &IKChainManager_c::CanAccept);
    // Install("IKChainManager_c", "Init", 0x6180A0, &IKChainManager_c::Init);
    // Install("IKChainManager_c", "Exit", 0x6180D0, &IKChainManager_c::Exit);
    // Install("IKChainManager_c", "Reset", 0x618140, &IKChainManager_c::Reset);
    // Install("IKChainManager_c", "RemoveIKChain", 0x618170, &IKChainManager_c::RemoveIKChain);
    // Install("IKChainManager_c", "IsLooking", 0x6181A0, &IKChainManager_c::IsLooking);
    // Install("IKChainManager_c", "GetLookAtEntity", 0x6181D0, &IKChainManager_c::GetLookAtEntity);
    // Install("IKChainManager_c", "AbortLookAt", 0x618280, &IKChainManager_c::AbortLookAt);
    // Install("IKChainManager_c", "Update", 0x6186D0, &IKChainManager_c::Update);
    // Install("IKChainManager_c", "AddIKChain", 0x618750, &IKChainManager_c::AddIKChain);
    // Install("IKChainManager_c", "CanAcceptLookAt", 0x6188B0, &IKChainManager_c::CanAcceptLookAt);
    // Install("IKChainManager_c", "LookAt", 0x618970, &IKChainManager_c::LookAt);
}

// 0x6180A0
bool IKChainManager_c::Init() {
    return plugin::CallMethodAndReturn<bool, 0x6180A0, IKChainManager_c*>(this);
}

// 0x6180D0
void IKChainManager_c::Exit() {
    return plugin::CallMethod<0x6180D0, IKChainManager_c*>(this);
}

// 0x618140
void IKChainManager_c::Reset() {
    return plugin::CallMethod<0x618140, IKChainManager_c*>(this);
}

// 0x6186D0
void IKChainManager_c::Update(float a1) {
    return plugin::CallMethod<0x6186D0, float>(a1);
}

// 0x618750
IKChain_c* IKChainManager_c::AddIKChain(Const char* name, int32 a2, CPed* ped, int32 a4, CVector a5, int32 a6, CEntity* entity, int32 a8, CVector a9, float a10, int32 a11) {
    return plugin::CallMethodAndReturn<IKChain_c*, 0x618750, IKChainManager_c*, const char*, int32, CPed*, int32, CVector, int32, CEntity*, int32, CVector, float, int32>(this, name, a2, ped, a4, a5, a6, entity, a8, a9, a10, a11);
}

// 0x618170
void IKChainManager_c::RemoveIKChain(IKChain_c* chain) {
    plugin::CallMethod<0x618170, IKChainManager_c*, IKChain_c*>(this, chain);
}

// 0x618800
bool IKChainManager_c::CanAccept(CPed* ped, float a2) {
    return plugin::CallMethodAndReturn<bool, 0x618800, IKChainManager_c*, CPed*, float>(this, ped, a2);
}

// 0x6181A0
bool IKChainManager_c::IsLooking(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x6181A0, IKChainManager_c*, CPed*>(this, ped);
}

// 0x6181D0
CEntity* IKChainManager_c::GetLookAtEntity(CPed* ped) {
    return plugin::CallMethodAndReturn<CEntity*, 0x6181D0, IKChainManager_c*, CPed*>(this, ped);
}

// 0x618210
void IKChainManager_c::GetLookAtOffset(CPed* ped, CVector* outPosn) {
    plugin::CallMethod<0x618210, IKChainManager_c*, CPed*, CVector*>(this, ped, outPosn);
}

// 0x618280
void IKChainManager_c::AbortLookAt(CPed* ped, int32 blendOutTime) {
    return plugin::CallMethod<0x618280, IKChainManager_c*, CPed*, int32>(this, ped, blendOutTime);
}

// 0x6188B0
bool IKChainManager_c::CanAcceptLookAt(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x6188B0, CPed*>(ped);
}

// 0x618970
void IKChainManager_c::LookAt(Const char* name, CPed* ped, CEntity* targetEntity, int32 time, ePedBones pedBoneId, CVector* posn, bool bArg7, float fSpeed, int32 blendTime, int32 a10, bool bForceLooking) {
    plugin::CallMethod<0x618970, IKChainManager_c*, Const char*, CPed*, CEntity*, int32, int32, CVector*, bool, float, int32, int32, bool>(this, name, ped, targetEntity, time, pedBoneId, posn, bArg7, fSpeed, blendTime, a10, bForceLooking);
}

bool IKChainManager_c::IsArmPointing(int32 nSlot, CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x6182B0, IKChainManager_c*, int32, CPed*>(this, nSlot, ped);
}

// 0x6182F0
void IKChainManager_c::AbortPointArm(int32 a1, CPed* ped, int32 a3) {
    return plugin::CallMethod<0x6182F0, IKChainManager_c*, int32, CPed*, int32>(this, a1, ped, a3);
}

// 0x618330
bool IKChainManager_c::IsFacingTarget(CPed* ped, int32 a2) {
    return plugin::CallMethodAndReturn<bool, 0x0, IKChainManager_c*, CPed*, int32>(this, ped, a2);
}

// 0x618B60
void IKChainManager_c::PointArm(Const char* taskName, int32 a2, CPed* ped, CEntity* target, ePedBones pedBoneId, CVector* posn, float fSpeedMB, int32 blendTimeMB, float a9) {
    plugin::CallMethod<0x618B60, IKChainManager_c*, const char*, int32, CPed*, CEntity*, ePedBones, CVector*, float, int32, float>(this, taskName, a2, ped, target, pedBoneId, posn, fSpeedMB, blendTimeMB, a9);
}
