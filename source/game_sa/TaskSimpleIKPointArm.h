#pragma once

#include "Base.h"
#include <rwplcore.h>
#include "TaskSimpleIKChain.h"

class CEntity;
class CPed;

class CTaskSimpleIKPointArm : public CTaskSimpleIKChain {
public:
    int32 m_hand = {}; // 0x58

public:
    static void InjectHooks();

    CTaskSimpleIKPointArm(const CTaskSimpleIKPointArm&) = default;
    CTaskSimpleIKPointArm(const char* purpose, int32 hand, CEntity* targetEntity, ePedBones bone, RwV3d offsetPosn, float speed, int32 blendTime);
    ~CTaskSimpleIKPointArm() override;

    void UpdatePointArmInfo(const char* purpose, CEntity* entity, ePedBones bone, RwV3d posn, float a8, int32 timeOffset);

    CTaskSimpleIKPointArm* Clone() override { return new CTaskSimpleIKPointArm{ *this }; }
    eTaskType GetTaskType() override { return TASK_SIMPLE_IK_POINT_R_ARM; } // Weird.. L_ARM never used?

    bool CreateIKChain(CPed* ped) override;

private:
    CTaskSimpleIKPointArm* Constructor(const char* purpose, int32 hand, CEntity* targetEntity, ePedBones bone, RwV3d offsetPosn, float speed, int32 blendTime);
    CTaskSimpleIKPointArm* Destructor();

    CTaskSimpleIKPointArm* Clone_Reversed() {
        return CTaskSimpleIKPointArm::Clone();
    }
    eTaskType GetTaskType_Reversed() {
        return CTaskSimpleIKPointArm::GetTaskType();
    }
    bool CreateIKChain_Reversed(CPed* ped) {
        return CTaskSimpleIKPointArm::CreateIKChain(ped);
    }
};
VALIDATE_SIZE(CTaskSimpleIKPointArm, 0x5C);
