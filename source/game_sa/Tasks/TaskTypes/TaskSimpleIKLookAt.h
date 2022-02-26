#pragma once

#include "Base.h"
#include <rwplcore.h>

#include "TaskSimpleIKChain.h"

class CEntity;
class CPed;

class CTaskSimpleIKLookAt : public CTaskSimpleIKChain {
public:
    bool  m_bUseTorso{};
    uint8 m_nPriority{};

public:
    static void InjectHooks();

    CTaskSimpleIKLookAt(const char* purpose, CEntity* lookAtEntity, int32 time, int32 pedBoneID, CVector lookAtOffset, bool useTorso, float speed, uint32 blendTime, uint8 priority);
    ~CTaskSimpleIKLookAt();

    void UpdateLookAtInfo(const char* strPurpose, CPed* ped, CEntity* targetPed, int32 time, int32 pedBoneID, RwV3d lookAtOffset, bool useTorso, float fSpeed, int32 blendTime,
                          int32 unused);
    CEntity* GetLookAtEntity();
    CVector GetLookAtOffset();

    CTaskSimpleIKLookAt* Clone() override;
    eTaskType GetTaskType() override { return TASK_SIMPLE_IK_LOOK_AT; }
    bool CreateIKChain(CPed* ped) override;

private:
    CTaskSimpleIKLookAt* Constructor(char* name, CEntity* lookAtEntity, int32 time, int32 pedBoneID, RwV3d lookAtOffset, uint8 a9, float fSpeed, int32 blendTime, int32 a12);
    CTaskSimpleIKLookAt* Destructor();

    CTask* Clone_Reversed() {
        return CTaskSimpleIKLookAt::Clone();
    }
    eTaskType GetTaskType_Reversed() {
        return CTaskSimpleIKLookAt::GetTaskType();
    }
    bool CreateIKChain_Reversed(CPed* ped) {
        return CTaskSimpleIKLookAt::CreateIKChain(ped);
    }
};
VALIDATE_SIZE(CTaskSimpleIKLookAt, 0x5C);
