#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CPedGroup;
class CPed;

class CTaskComplexFollowLeaderInFormation : public CTaskComplex {
    CPedGroup* m_Group;
    CPed*      m_Leader;
    CVector    m_Pos;
    uint32     m_Int;
    float      m_Dist; // Max distance between m_pos and some point, not sure. See `ControlSubTask`. Ignored if < 0

public:
    static constexpr auto Type = TASK_COMPLEX_FOLLOW_LEADER_IN_FORMATION;

    struct Offsets {
        std::array<CVector2D, 8> offsets;
        std::array<CVector2D, 8> movingOffsets;
        float                    scale;
    };
    static inline auto& ms_offsets = StaticRef<Offsets, 0xC196E8>();

    CTaskComplexFollowLeaderInFormation(CPedGroup* pedGroup, CPed* ped, const CVector& posn, float dist = -1.f);
    ~CTaskComplexFollowLeaderInFormation() override;

    eTaskType GetTaskType() const override { return Type; }
    CTask*    Clone() override { return plugin::CallMethodAndReturn<CTask*, 0x695740, CTaskComplexFollowLeaderInFormation*>(this); } // 0x695740
    CTask*    CreateNextSubTask(CPed* ped) override;
    CTask*    CreateFirstSubTask(CPed* ped) override;
    CTask*    ControlSubTask(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexFollowLeaderInFormation* Constructor(CPedGroup* pedGroup, CPed* ped, CVector const& posn, float a5) { return this; }
    CTaskComplexFollowLeaderInFormation* Destructor() { this->CTaskComplexFollowLeaderInFormation::~CTaskComplexFollowLeaderInFormation(); return this; }

    CTask*    Clone_Reversed() { return CTaskComplexFollowLeaderInFormation::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskComplexFollowLeaderInFormation::GetTaskType(); }
    CTask*    CreateNextSubTask_Reversed(CPed* ped) { return CTaskComplexFollowLeaderInFormation::CreateNextSubTask(ped); }
    CTask*    CreateFirstSubTask_Reversed(CPed* ped) { return CTaskComplexFollowLeaderInFormation::CreateFirstSubTask(ped); }
    CTask*    ControlSubTask_Reversed(CPed* ped) { return CTaskComplexFollowLeaderInFormation::ControlSubTask(ped); }
};
VALIDATE_SIZE(CTaskComplexFollowLeaderInFormation, 0x28);
