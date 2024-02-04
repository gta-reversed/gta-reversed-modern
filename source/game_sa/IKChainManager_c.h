#pragma once

#include "List_c.h"
#include "IKChain_c.h"

class CPed;
class CEntity;

class IKChainManager_c {
public:
    static void InjectHooks();

    IKChainManager_c() = default;  // 0x617FC0
    ~IKChainManager_c() = default; // 0x8568E0

    bool Init();
    void Exit();
    void Reset();
    void Update(float a1);

    /*!
    * @addr 0x618750
    * @brief Tries initing a new chain from the free list.
    * @returns A new `IKChain_c` object, unless there are no more free chains or it's init failed.
    */
    IKChain_c* AddIKChain(const char* name, int32 IndexInList, CPed* ped, ePedBones bone1, RwV3d bonePosn, ePedBones bone2, CEntity* entity, int32 offsetBoneTag, RwV3d posn, float a11, int32 priority);
    void RemoveIKChain(IKChain_c* chain);

    bool CanAccept(CPed* ped, float) const;
    bool IsLooking(CPed* ped) const;
    CEntity* GetLookAtEntity(CPed* ped);
    CVector GetLookAtOffset(CPed* ped);
    void AbortLookAt(CPed* ped, uint32 blendOutTime = 250u);
    bool CanAcceptLookAt(CPed* ped);
    void LookAt(Const char* purpose, CPed* ped, CEntity* targetEntity, int32 time, ePedBones pedBoneId, CVector* posn, bool useTorso, float fSpeed, int32 blendTime, int32 priority, bool bForceLooking);
    void PointArm(Const char* purpose, int32 arm, CPed* ped, CEntity* target, ePedBones pedBoneId, CVector* posn, float speed, int32 blendTime, float dist);
    static bool __stdcall IsArmPointing(int32 slot, CPed* ped);
    static void __stdcall AbortPointArm(int32 slot, CPed* ped, int32 a3);
    bool IsFacingTarget(CPed* ped, int32) const;

public:
    IKChain_c          m_Chains[32];
    TList_c<IKChain_c> m_ActiveList;
    TList_c<IKChain_c> m_FreeList;
    char               pad1[754];
    // CTaskSimpleAchieveHeading m_list2[32]; // pad1 was this originally, but I really don't think it's really this.
};
VALIDATE_SIZE(IKChainManager_c, 0xE0C);

extern IKChainManager_c& g_ikChainMan;
