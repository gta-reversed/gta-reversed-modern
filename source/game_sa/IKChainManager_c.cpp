#include "StdInc.h"

#include "IKChainManager_c.h"
#include "IKChain_c.h"
#include "BoneNodeManager_c.h"

IKChainManager_c& g_ikChainMan = *(IKChainManager_c*)0xC15448;

void IKChainManager_c::InjectHooks() {
    RH_ScopedClass(IKChainManager_c);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(IsArmPointing, 0x6182B0);
    // RH_ScopedInstall(AbortPointArm, 0x6182F0);
    // RH_ScopedInstall(CanAccept, 0x618800);
    RH_ScopedInstall(Init, 0x6180A0);
    // RH_ScopedInstall(Exit, 0x6180D0);
    RH_ScopedInstall(Reset, 0x618140);
    // RH_ScopedInstall(RemoveIKChain, 0x618170);
    // RH_ScopedInstall(IsLooking, 0x6181A0);
    // RH_ScopedInstall(GetLookAtEntity, 0x6181D0);
    // RH_ScopedInstall(AbortLookAt, 0x618280);
    RH_ScopedInstall(Update, 0x6186D0);
    RH_ScopedInstall(AddIKChain, 0x618750);
    // RH_ScopedInstall(CanAcceptLookAt, 0x6188B0);
    // RH_ScopedInstall(LookAt, 0x618970);
}

// 0x6180A0
bool IKChainManager_c::Init() {
    for (auto&& v : m_chains) {
        m_freeList.AddItem(&v);
    }
}

// 0x6180D0
void IKChainManager_c::Exit() {
    for (auto it = m_activeList.GetTail(); it; it = m_activeList.GetPrev(it)) {
        ((IKChain_c*)it)->Exit();
    }
    m_activeList.RemoveAll();
    m_freeList.RemoveAll();
}

// 0x618140
void IKChainManager_c::Reset() {
    Exit();
    Init();
}

// 0x6186D0
void IKChainManager_c::Update(float timeStep) {
    UNUSED(timeStep);

    for (auto i = 0u; i < 4u; i++) {
        CWorld::IncrementCurrentScanCode();

        for (auto it = m_activeList.GetHead(); it; it = it = m_activeList.GetNext(it)) {
            auto& v = *(IKChain_c*)it;
            if (v.m_indexInList == i) {
                // Update RpHAnim of ped (if any) - TODO: Maybe move this code into `IKChain_c::Update` as well..
                if (v.m_ped) {
                    if (!v.m_ped->IsScanCodeCurrent()) {
                        v.m_ped->UpdateRpHAnim();
                        v.m_ped->SetCurrentScanCode();
                    }
                }

                // Now update the IKChain itself
                v.Update();
            }
        }
    }
}

/*!
* @addr 0x618750
* @brief Tries initing a new chain from the free list.
* @returns A new `IKChain_c` object, unless there are no more free chains or it's init failed.
*/
IKChain_c* IKChainManager_c::AddIKChain(const char* name, int32 IndexInList, CPed* ped, int32 animId, RwV3d bonePosn, int32 animId_1, CEntity* entity, int32 offsetBoneTag,
    RwV3d posn, float a11, int32 priority) {
    if (auto chain = m_freeList.RemoveHead()) {
        if (chain->Init(name, IndexInList, ped, animId, bonePosn, animId_1, entity, offsetBoneTag, posn, a11, priority)) {
            m_activeList.AddItem(chain);
            return chain;
        }
        m_freeList.AddItem(chain); // Failed, add back to free list
    }
    return nullptr; // No more free chains
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
void IKChainManager_c::GetLookAtOffset(CPed* ped, CVector* outPos) {
    plugin::CallMethod<0x618210, IKChainManager_c*, CPed*, CVector*>(this, ped, outPos);
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
    plugin::CallMethod<0x618970, IKChainManager_c*, const char*, CPed*, CEntity*, int32, ePedBones, CVector*, bool, float, int32, int32, bool>(this, name, ped, targetEntity, time, pedBoneId, posn, bArg7, fSpeed, blendTime, a10, bForceLooking);
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
    return plugin::CallMethodAndReturn<bool, 0x618330, IKChainManager_c*, CPed*, int32>(this, ped, a2);
}

// 0x618B60
void IKChainManager_c::PointArm(Const char* taskName, int32 a2, CPed* ped, CEntity* target, ePedBones pedBoneId, CVector* posn, float fSpeedMB, int32 blendTimeMB, float a9) {
    plugin::CallMethod<0x618B60, IKChainManager_c*, const char*, int32, CPed*, CEntity*, ePedBones, CVector*, float, int32, float>(this, taskName, a2, ped, target, pedBoneId, posn, fSpeedMB, blendTimeMB, a9);
}
