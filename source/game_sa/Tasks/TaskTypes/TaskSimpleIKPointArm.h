#pragma once

#include "Base.h"
#include <rwplcore.h>
#include "TaskSimpleIKChain.h"

class CEntity;
class CPed;

class CTaskSimpleIKPointArm : public CTaskSimpleIKChain {
public:
    int32 m_Hand;

public:
    CTaskSimpleIKPointArm(const char* purpose, int32 hand, CEntity* targetEntity, ePedBones bone, CVector offsetPos, float speed, int32 blendTime);
    ~CTaskSimpleIKPointArm() override = default; // 0x634240

    void UpdatePointArmInfo(const char* purpose, CEntity* entity, ePedBones bone, CVector posn, float speed, int32 timeOffset);

    CTaskSimpleIKPointArm* Clone() override;
    eTaskType GetTaskType() override { return TASK_SIMPLE_IK_POINT_R_ARM; } // Weird.. L_ARM never used?

    bool CreateIKChain(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleIKPointArm* Constructor(const char* purpose, int32 hand, CEntity* targetEntity, ePedBones bone, RwV3d offsetPosn, float speed, int32 blendTime) { this->CTaskSimpleIKPointArm::CTaskSimpleIKPointArm(purpose, hand, targetEntity, bone, offsetPosn, speed, blendTime); return this; }
    CTaskSimpleIKPointArm* Destructor() { this->CTaskSimpleIKPointArm::~CTaskSimpleIKPointArm(); return this; }
    CTaskSimpleIKPointArm* Clone_Reversed() { return CTaskSimpleIKPointArm::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleIKPointArm::GetTaskType(); }
    bool CreateIKChain_Reversed(CPed* ped) { return CTaskSimpleIKPointArm::CreateIKChain(ped); }
};
VALIDATE_SIZE(CTaskSimpleIKPointArm, 0x5C);
