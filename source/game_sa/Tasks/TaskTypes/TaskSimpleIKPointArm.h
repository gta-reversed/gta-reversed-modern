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
    static constexpr auto Type = TASK_SIMPLE_IK_POINT_R_ARM;

    CTaskSimpleIKPointArm(const char* purpose, int32 hand, CEntity* targetEntity, ePedBones bone, CVector offsetPos, float speed, int32 blendTime);
    ~CTaskSimpleIKPointArm() override = default; // 0x634240

    eTaskType GetTaskType() const override { return Type; } // Weird.. L_ARM never used?
    CTask* Clone() const override;

    bool CreateIKChain(CPed* ped) override;
    void UpdatePointArmInfo(const char* purpose, CEntity* entity, ePedBones bone, CVector posn, float speed, int32 timeOffset);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleIKPointArm* Constructor(const char* purpose, int32 hand, CEntity* targetEntity, ePedBones bone, RwV3d offsetPosn, float speed, int32 blendTime) { this->CTaskSimpleIKPointArm::CTaskSimpleIKPointArm(purpose, hand, targetEntity, bone, offsetPosn, speed, blendTime); return this; }
    CTaskSimpleIKPointArm* Destructor() { this->CTaskSimpleIKPointArm::~CTaskSimpleIKPointArm(); return this; }
    CTask* Clone_Reversed() { return CTaskSimpleIKPointArm::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleIKPointArm::GetTaskType(); }
    bool CreateIKChain_Reversed(CPed* ped) { return CTaskSimpleIKPointArm::CreateIKChain(ped); }
};
VALIDATE_SIZE(CTaskSimpleIKPointArm, 0x5C);
