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
    int16      m_nPivotBoneTag{};
    int16      m_nEffectorBoneTag{};
    RwV3d      m_vecEffectorVec{};
    CEntity*   m_pEntity{};
    int32      m_nOffsetBoneTag{};
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

    ~CTaskSimpleIKChain();
    CTaskSimpleIKChain(const char* name, int16 effectorBoneTag, RwV3d effectorVec, int16 pivotBoneTag, CEntity* entity, int32 offsetBoneTag, RwV3d offsetPos, float speed, int32 time, int32 blendTime);


    void BlendOut(int32 blendOutTime);
    IKChain_c*      GetIKChain();

    CTaskSimpleIKChain* Clone() override;
    eTaskType           GetTaskType() override { return TASK_SIMPLE_IK_CHAIN; }
    bool                MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    bool                ProcessPed(CPed* ped) override;

    virtual bool CreateIKChain(CPed* ped);
private:
    CTaskSimpleIKChain* Constructor(char* name, int32 effectorBoneTag, RwV3d effectorVec, int32 pivotBoneTag, CEntity* a6, int32 offsetBoneTag, RwV3d offsetPos, float speed, int32 time, int32 blendTime);
    CTaskSimpleIKChain* Destructor();

    CTask* Clone_Reversed() { return CTaskSimpleIKChain::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleIKChain::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleIKChain::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed* ped) { return CTaskSimpleIKChain::ProcessPed(ped); }
    bool CreateIKChain_Reversed(CPed* ped) { return CTaskSimpleIKChain::CreateIKChain(ped); }
};
VALIDATE_SIZE(CTaskSimpleIKChain, 0x58);
