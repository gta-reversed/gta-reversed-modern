#pragma once

#include "Base.h"
#include <rwplcore.h>
#include "TaskSimple.h"

class CEntity;
class CPed;
class CTaskSimpleIKChain;
class IKChain_c;

class NOTSA_EXPORT_VTABLE CTaskSimpleIKChain : public CTaskSimple {
public:
    int32     m_nTime;
    int32     m_nBlendTime;
    IKChain_c * m_pIKChain;
    int16     m_nAlotId;
    ePedBones m_nPivotBoneTag;
    ePedBones m_nEffectorBoneTag;
    CVector   m_vecEffectorVec;
    CEntity*  m_pEntity;
    ePedBones m_nOffsetBoneTag;
    int16     pad; // Must be kept, because originally `m_OffsetBoneTag` was likely an int32 - This inits the high word to 0
    CVector   m_vecOffsetPos;
    float     m_fSpeed;
    bool      m_bEntityExist;
    float     m_fBlend;
    int32     m_nEndTime;
    float     m_fTargetBlend;
    int32     m_nTargetTime;
    int32     m_bIsBlendingOut;

public:
    static constexpr auto Type = TASK_SIMPLE_IK_CHAIN;

    CTaskSimpleIKChain(const char* name, ePedBones effectorBoneTag, CVector effectorPos, ePedBones pivotBoneTag, CEntity* entity, ePedBones offsetBoneTag, CVector offsetPos,
                       float speed, int32 time, int32 blendTime);
    ~CTaskSimpleIKChain() override;

    eTaskType GetTaskType() const override { return Type; } // 0x62EC30
    CTask* Clone() const override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;

    virtual bool CreateIKChain(CPed* ped);

    void BlendOut(int32 blendOutTime = 250);
    IKChain_c* GetIKChain();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleIKChain* Constructor(char* name, ePedBones effectorBoneTag, RwV3d effectorVec, ePedBones pivotBoneTag, CEntity* a6, ePedBones offsetBoneTag, RwV3d offsetPos, float speed, int32 time, int32 blendTime) { this->CTaskSimpleIKChain::CTaskSimpleIKChain(name, effectorBoneTag, effectorVec, pivotBoneTag, a6, offsetBoneTag, offsetPos, speed, time, blendTime); return this; }
    CTaskSimpleIKChain* Destructor() { this->CTaskSimpleIKChain::~CTaskSimpleIKChain(); return this; }
    CTask* Clone_Reversed() { return CTaskSimpleIKChain::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleIKChain::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleIKChain::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed* ped) { return CTaskSimpleIKChain::ProcessPed(ped); }
    bool CreateIKChain_Reversed(CPed* ped) { return CTaskSimpleIKChain::CreateIKChain(ped); }
};
VALIDATE_SIZE(CTaskSimpleIKChain, 0x58);
