#include "StdInc.h"

#include "IKChainManager_c.h"
#include "IKChain_c.h"
#include "BoneNodeManager_c.h"
#include "TaskSimpleIKManager.h"
#include "TaskSimpleIKLookAt.h"
#include "TaskSimpleIKPointArm.h"

IKChainManager_c& g_ikChainMan = *(IKChainManager_c*)0xC15448;

void IKChainManager_c::InjectHooks() {
    RH_ScopedClass(IKChainManager_c);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x6180A0);
    RH_ScopedInstall(Exit, 0x6180D0);
    RH_ScopedInstall(Reset, 0x618140);
    RH_ScopedInstall(Update, 0x6186D0);
    RH_ScopedInstall(AddIKChain, 0x618750);
    RH_ScopedInstall(RemoveIKChain, 0x618170);
    RH_ScopedInstall(CanAccept, 0x618800);
    RH_ScopedInstall(IsLooking, 0x6181A0);
    RH_ScopedInstall(GetLookAtEntity, 0x6181D0);
    RH_ScopedInstall(GetLookAtOffset, 0x618210);
    RH_ScopedInstall(AbortLookAt, 0x618280);
    RH_ScopedInstall(CanAcceptLookAt, 0x6188B0);
    RH_ScopedInstall(LookAt, 0x618970);
    RH_ScopedInstall(IsArmPointing, 0x6182B0);
    RH_ScopedInstall(AbortPointArm, 0x6182F0);
    RH_ScopedInstall(IsFacingTarget, 0x618330);
    RH_ScopedInstall(PointArm, 0x618B60);
}

// 0x6180A0
bool IKChainManager_c::Init() {
    for (auto& chain : m_Chains) {
        m_FreeList.AddItem(&chain);
    }
    return true;
}

// 0x6180D0
void IKChainManager_c::Exit() {
    for (auto it = m_ActiveList.GetTail(); it; it = m_ActiveList.GetPrev(it)) {
        static_cast<IKChain_c*>(it)->Exit();
    }
    m_ActiveList.RemoveAll();
    m_FreeList.RemoveAll();
}

// 0x618140
void IKChainManager_c::Reset() {
    Exit();
    Init();
}

// 0x6186D0
void IKChainManager_c::Update(float timeStep) {
    for (auto i = 0u; i < 4u; i++) {
        CWorld::IncrementCurrentScanCode();

        for (auto it = m_ActiveList.GetHead(); it; it = it = m_ActiveList.GetNext(it)) {
            auto& chain = *(IKChain_c*)it;
            if (chain.m_IndexInList == i) {
                // Update RpHAnim of ped (if any) - TODO: Maybe move this code into `IKChain_c::Update` as well..
                if (chain.m_Ped) {
                    if (!chain.m_Ped->IsScanCodeCurrent()) {
                        chain.m_Ped->UpdateRpHAnim();
                        chain.m_Ped->SetCurrentScanCode();
                    }
                }

                // Now update the IKChain itself
                chain.Update(timeStep);
            }
        }
    }
}

/*!
 * @addr 0x618750
 * @brief Tries initing a new chain from the free list.
 * @returns A new `IKChain_c` object, unless there are no more free chains or it's init failed.
 */
IKChain_c* IKChainManager_c::AddIKChain(const char* name,
                                        int32 IndexInList,
                                        CPed* ped,
                                        ePedBones bone1,
                                        RwV3d bonePosn,
                                        ePedBones bone2,
                                        CEntity* entity,
                                        int32 offsetBoneTag,
                                        RwV3d posn,
                                        float speed,
                                        int32 priority
) {
    if (auto chain = m_FreeList.RemoveHead()) {
        if (chain->Init(name, IndexInList, ped, bone1, bonePosn, bone2, entity, offsetBoneTag, posn, speed, priority)) {
            m_ActiveList.AddItem(chain);
            return chain;
        }
        m_FreeList.AddItem(chain); // Failed, add back to free list
    }
    return nullptr; // No more free chains
}

// 0x618170
void IKChainManager_c::RemoveIKChain(IKChain_c* chain) {
    chain->Exit();
    m_ActiveList.RemoveItem(chain);
    m_FreeList.AddItem(chain);
}

// 0x618800
bool IKChainManager_c::CanAccept(CPed* ped, float dist) const {
    if (!ped->GetModellingMatrix() || !ped->IsAlive() || !ped->GetIsOnScreen()) {
        return false;
    }

    return TheCamera.m_PlayerWeaponMode.m_nMode == MODE_SNIPER || dist >= 999.f || dist * dist >= (TheCamera.GetPosition() - ped->GetPosition()).SquaredMagnitude();
}

// NOTSA
CTaskSimpleIKManager* GetPedIKManagerTask(CPed* ped, bool create = false) {
    if (const auto mgr = static_cast<CTaskSimpleIKManager*>(ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_IK))) {
        return mgr;
    } else if (create) { // Doesn't exist, create it
        auto taskIKMgr = new CTaskSimpleIKManager{};
        ped->GetTaskManager().SetTaskSecondary(taskIKMgr, TASK_SECONDARY_IK);
        return taskIKMgr;
    }
    return nullptr;
}

// NOTSA
CTaskSimpleIKLookAt* GetPedIKLookAtTask(CPed* ped) {
    if (const auto mgr = GetPedIKManagerTask(ped)) {
        return static_cast<CTaskSimpleIKLookAt*>(mgr->GetTaskAtSlot(0));
    }
    return nullptr;
}

// 0x6181A0
bool IKChainManager_c::IsLooking(CPed* ped) const {
    return !!GetPedIKLookAtTask(ped);
}

// 0x6181D0
CEntity* IKChainManager_c::GetLookAtEntity(CPed* ped) {
    if (const auto task = GetPedIKLookAtTask(ped)) {
        return task->GetLookAtEntity();
    }
    return nullptr;
}

// 0x618210
CVector IKChainManager_c::GetLookAtOffset(CPed* ped) { // TODO: It's possible this is incorrect, originally it took the vector as an arg (although that's probably a compiler optimization)
    if (const auto task = GetPedIKLookAtTask(ped)) {
        return task->GetLookAtOffset();
    }
    return {};
}

// 0x618280
void IKChainManager_c::AbortLookAt(CPed* ped, uint32 blendOutTime) {
    if (const auto task = GetPedIKLookAtTask(ped)) {
        task->BlendOut(blendOutTime);
    }
}

// 0x6188B0
bool IKChainManager_c::CanAcceptLookAt(CPed* ped) {
    if (!CanAccept(ped, 20.f)) {
        return false;
    }

    // If ped doesn't accept look at IK's abort it (if any) and return false
    if (!ped->bDontAcceptIKLookAts) {
        if (IsLooking(ped)) {
            AbortLookAt(ped);
        }
        return false;
    }

    if (ped->m_pedIK.bUnk) {
        return false;
    }

    // Check if ped has any of the anims present - TODO: Make this into a CPed funtion perhaps?
    if (rng::any_of(
        std::array{
            ANIM_ID_DRNKBR_PRTL,
            ANIM_ID_SMKCIG_PRTL,
            ANIM_ID_DRNKBR_PRTL_F
        }, [ped](AnimationId anim) {
            return RpAnimBlendClumpGetAssociation(ped->m_pRwClump, anim);
        }
    )) {
        return false;
    }

    return !RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SMKCIG_PRTL_F);
}

// 0x618970
void IKChainManager_c::LookAt(Const char* purpose, CPed* ped, CEntity* targetEntity, int32 time, ePedBones pedBoneId, const CVector* posn, bool useTorso, float fSpeed, int32 blendTime,
                              int32 priority, bool bForceLooking) {
    if (!bForceLooking && !CanAcceptLookAt(ped)) { // byte_C1542C
        return;
    }

    auto& taskIKMgr = *GetPedIKManagerTask(ped, true);

    const auto lookAtOffset = posn ? *posn : CVector{};

    // Now, either update existing task or create one
    if (const auto lookAt = static_cast<CTaskSimpleIKLookAt*>(taskIKMgr.GetTaskAtSlot(0))) {
        if (priority < lookAt->m_nPriority) {
            return;
        }
        if (useTorso || !lookAt->m_bUseTorso) {
            lookAt->UpdateLookAtInfo(purpose, ped, targetEntity, time, pedBoneId, lookAtOffset, useTorso && lookAt->m_bUseTorso, fSpeed, blendTime, priority);
        } else {
            AbortLookAt(ped);
        }
    } else { // Doesn't have task yet, create it
        taskIKMgr.AddIKChainTask(new CTaskSimpleIKLookAt(purpose, targetEntity, time, pedBoneId, lookAtOffset, useTorso, fSpeed, blendTime, priority), 0);
    }
}

// 0x6182B0
bool __stdcall IKChainManager_c::IsArmPointing(int32 slot, CPed* ped) {
    const auto mgr = GetPedIKManagerTask(ped);
    return mgr && mgr->GetTaskAtSlot(slot + 1);
}

// 0x6182F0
void __stdcall IKChainManager_c::AbortPointArm(int32 slot, CPed* ped, int32 blendOutTime) {
    const auto mgr = GetPedIKManagerTask(ped);
    assert(mgr);
    if (const auto lookAt = static_cast<CTaskSimpleIKChain*>(mgr->GetTaskAtSlot(slot + 1))) {
        lookAt->BlendOut(blendOutTime);
    }
}

// 0x618330
bool IKChainManager_c::IsFacingTarget(CPed* ped, int32 slot) const {
    if (const auto mgr = GetPedIKManagerTask(ped)) {
        if (const auto task = mgr->GetTaskAtSlot(slot)) {
            return task->GetIKChain()->IsFacingTarget();
        }
    }
    return false;
}

// 0x618B60
void IKChainManager_c::PointArm(Const char* purpose, int32 arm, CPed* ped, CEntity* target, ePedBones pedBoneId, const CVector* posn, float speed, int32 blendTime, float dist) {
    assert(arm <= 1); // I have a theory: that is, that `arm` is a bool, like `bool isLeftArm`. Let's test it!

    if (!CanAccept(ped, dist)) {
        return;
    }

    auto& taskIKMgr = *GetPedIKManagerTask(ped, true);

    const auto slot = arm + 1;

    const auto offset = posn ? *posn : CVector{};

    // Now, either create or update existing
    if (const auto pointArm = static_cast<CTaskSimpleIKPointArm*>(taskIKMgr.GetTaskAtSlot(slot))) {
        pointArm->UpdatePointArmInfo(purpose, target, pedBoneId, offset, speed, blendTime);
    } else { // Create task
        taskIKMgr.AddIKChainTask(new CTaskSimpleIKPointArm{purpose, arm, target, pedBoneId, offset, speed, blendTime}, slot);
    }
}
