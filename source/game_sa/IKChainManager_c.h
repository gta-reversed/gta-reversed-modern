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

    IKChain_c* AddIKChain(Const char* name, int32 a2, CPed* ped, int32 a4, CVector a5, int32 a6, CEntity* entity, int32 a8, CVector a9, float a10, int32 a11);
    void RemoveIKChain(IKChain_c* chain);

    bool CanAccept(CPed* ped, float);
    bool IsLooking(CPed* ped);
    CEntity* GetLookAtEntity(CPed* ped);
    void GetLookAtOffset(CPed* ped, CVector* outPos);
    void AbortLookAt(CPed* ped, int32);
    bool CanAcceptLookAt(CPed* ped);
    void LookAt(Const char* name, CPed* ped, CEntity* targetEntity, int32 time, ePedBones pedBoneId, CVector* posn, bool bArg7, float fSpeed, int32 blendTime, int32 a10, bool bForceLooking);

    void PointArm(Const char* taskName, int32 a2, CPed* ped, CEntity* target, ePedBones pedBoneId, CVector* posn, float fSpeedMB, int32 blendTimeMB, float a9);
    bool IsArmPointing(int32, CPed* ped);
    void AbortPointArm(int32 a1, CPed* ped, int32 a3);
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
