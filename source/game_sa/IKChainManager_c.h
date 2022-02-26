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

    IKChain_c* AddIKChain(const char* name, int32 IndexInList, CPed* ped, int32 animId, RwV3d bonePosn, int32 animId_1, CEntity* entity, int32 offsetBoneTag, RwV3d posn, float a11,
        int32 priority);
    void RemoveIKChain(IKChain_c* chain);

    bool CanAccept(CPed* ped, float);
    bool IsLooking(CPed* ped);
    CEntity* GetLookAtEntity(CPed* ped);
    CVector GetLookAtOffset(CPed* ped);
    void AbortLookAt(CPed* ped, uint32 blendOutTime = 250u);
    bool CanAcceptLookAt(CPed* ped);
    void LookAt(Const char* name, CPed* ped, CEntity* targetEntity, int32 time, ePedBones pedBoneId, CVector* posn, bool bArg7, float fSpeed, int32 blendTime, uint8 taskPriority, bool bForceLooking);

    void PointArm(Const char* taskName, int32 a2, CPed* ped, CEntity* target, ePedBones pedBoneId, CVector* posn, float fSpeedMB, int32 blendTimeMB);
    static bool IsArmPointing(int32, CPed* ped);
    static void AbortPointArm(int32 a1, CPed* ped, int32 a3);
    bool IsFacingTarget(CPed* ped, int32);

public:
    IKChain_c                 m_chains[32]{};
    TList_c<IKChain_c>        m_activeList{};
    TList_c<IKChain_c>        m_freeList{};
    char                      pad1[754];
    //CTaskSimpleAchieveHeading m_list2[32]; // pad1 was this originally, but I really don't think it's really this.
};
VALIDATE_SIZE(IKChainManager_c, 0xE0C);

extern IKChainManager_c& g_ikChainMan;
