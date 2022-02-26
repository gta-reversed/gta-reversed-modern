#pragma once

#include "Base.h"
#include <rwplcore.h>
#include "TaskSimple.h"

class CEntity;
class CPed;
class CTaskSimpleIKChain;
class IKChain_c;

class CTaskSimpleIKChain : public CTaskSimple {
public:
    int32      m_nTime{};
    int32      m_nBlendTime{};
    IKChain_c* m_pIKChain{};
    int16      m_nAlotId{};
    ePedBones  m_nPivotBoneTag{};
    ePedBones  m_nEffectorBoneTag{};
    RwV3d      m_vecEffectorVec{};
    CEntity*   m_pEntity{};
    ePedBones  m_nOffsetBoneTag{};
    int16      pad{}; // Must be kept, because originally `m_nffsetBoneTag` was likely an int32 - This inits the high word to 0
    RwV3d      m_vecOffsetPos{};
    float      m_fSpeed{};
    bool       m_bEntityExist{};
    float      m_fBlend{};
    int32      m_nEndTime{};
    float      m_fTargetBlend{};
    int32      m_nTargetTime{};
    int32      m_bIsBlendingOut{};

public:
    static void InjectHooks();

    CTaskSimpleIKChain(const CTaskSimpleIKChain&) = default;
    CTaskSimpleIKChain(const char* name, ePedBones effectorBoneTag, RwV3d effectorVec, ePedBones pivotBoneTag, CEntity* entity, ePedBones offsetBoneTag, RwV3d offsetPos, float speed, int32 time, int32 blendTime);
    ~CTaskSimpleIKChain() override;


    void BlendOut(int32 blendOutTime = 250);
    IKChain_c*      GetIKChain();

    CTaskSimpleIKChain* Clone() override { return new CTaskSimpleIKChain{*this}; }
    eTaskType           GetTaskType() override { return TASK_SIMPLE_IK_CHAIN; }
    bool                MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    bool                ProcessPed(CPed* ped) override;

    virtual bool CreateIKChain(CPed* ped);
private:
    CTaskSimpleIKChain* Constructor(char* name, ePedBones effectorBoneTag, RwV3d effectorVec, ePedBones pivotBoneTag, CEntity* a6, ePedBones offsetBoneTag, RwV3d offsetPos, float speed, int32 time, int32 blendTime);
    CTaskSimpleIKChain* Destructor();

    CTask* Clone_Reversed() { return CTaskSimpleIKChain::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleIKChain::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleIKChain::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed* ped) { return CTaskSimpleIKChain::ProcessPed(ped); }
    bool CreateIKChain_Reversed(CPed* ped) { return CTaskSimpleIKChain::CreateIKChain(ped); }
};
VALIDATE_SIZE(CTaskSimpleIKChain, 0x58);
