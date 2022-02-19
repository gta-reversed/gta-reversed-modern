#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CPedGroup;
class CPed;

class CTaskComplexFollowLeaderInFormation : public CTaskComplex {
    CPedGroup* m_group;     // 0xC
    CPed*      m_leader;    // 0x10        
    CVector    m_pos;       // 0x14
    uint32     m_int;       // 0x20
    float      m_dist;      // 0x24 - Max distance between m_pos and some point, not sure. See `ControlSubTask`. Ignored if < 0
public:
    static void InjectHooks();

    ~CTaskComplexFollowLeaderInFormation();
    CTaskComplexFollowLeaderInFormation(CPedGroup * pedGroup, CPed * ped, CVector const& posn, float dist); 

    CTask*    Clone() override;
    eTaskType GetTaskType() override { return eTaskType::TASK_COMPLEX_FOLLOW_LEADER_IN_FORMATION; }
    CTask*    CreateNextSubTask(CPed * ped) override;
    CTask*    CreateFirstSubTask(CPed * ped) override;
    CTask*    ControlSubTask(CPed * ped) override;
private:
    CTaskComplexFollowLeaderInFormation* Constructor(CPedGroup * pedGroup, CPed * ped, CVector const& posn, float a5);
    CTaskComplexFollowLeaderInFormation* Destructor();

    CTask*    Clone_Reversed() { return CTaskComplexFollowLeaderInFormation::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskComplexFollowLeaderInFormation::GetTaskType(); }
    CTask*    CreateNextSubTask_Reversed(CPed * ped) { return CTaskComplexFollowLeaderInFormation::CreateNextSubTask(ped); }
    CTask*    CreateFirstSubTask_Reversed(CPed * ped) { return CTaskComplexFollowLeaderInFormation::CreateFirstSubTask(ped); }
    CTask*    ControlSubTask_Reversed(CPed * ped) { return CTaskComplexFollowLeaderInFormation::ControlSubTask(ped); }
};
VALIDATE_SIZE(CTaskComplexFollowLeaderInFormation, 0x28);
