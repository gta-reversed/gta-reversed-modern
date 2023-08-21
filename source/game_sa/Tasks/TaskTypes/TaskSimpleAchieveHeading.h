#pragma once

#include "TaskSimple.h"

class CTaskSimpleAchieveHeading : public CTaskSimple {
public:
    float m_fAngle;
    float m_fChangeRateMult;
    float m_fMaxHeading;
    union {
        struct {
            bool m_b1 : 1;
        };
        uint8 m_Flags;
    };

public:
    static constexpr auto Type = TASK_SIMPLE_ACHIEVE_HEADING;

    /*!
     * @param desiredHeading The heading to achieve
     * @param changeRate     How fast to change the heading
     * @param tolerance      The tolerance of the heading
    */
    CTaskSimpleAchieveHeading(float desiredHeading, float changeRate = 0.5f, float tolerance = 0.2f);

    /*!
     * @notsa
     * @brief Achieve heading towards an entity
     * 
     * @param looker      The ped that has to achieve the heading
     * @param lookTowards The entity the ped has to achieve the heading towards
     * @param changeRate  How fast to change the heading
     * @param tolerance   The tolerance of the heading
    */
    CTaskSimpleAchieveHeading(CPed* looker, CEntity* lookTowards, float changeRate = 0.5f, float tolerance = 0.2f); // NOTSA
    ~CTaskSimpleAchieveHeading() override = default; // 0x667E70

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override { return new CTaskSimpleAchieveHeading(m_fAngle, m_fChangeRateMult, m_fMaxHeading); } // 0x66CCF0
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(class CPed* ped) override;

    void QuitIK(CPed* ped) const;
    void SetUpIK(CPed* ped);

    static void InjectHooks() {};
};
VALIDATE_SIZE(CTaskSimpleAchieveHeading, 0x18);
