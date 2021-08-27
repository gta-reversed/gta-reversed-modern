#include "CTaskComplex.h"
#include "CTaskTimer.h"
#include "CVector.h"

class CColSphere;

class CTaskComplexAvoidOtherPedWhileWandering : public CTaskComplex {
public:
    CPed* m_ped;
    CVector field_10;
    CVector field_1C;
    CVector field_28;
    std::int32_t field_34;
    std::int32_t field_38;
    std::int32_t field_3C;
    CTaskTimer field_40;
    CTaskTimer field_4C;
    std::int32_t m_moveState; // see eMoveState
    std::int8_t m_flag1 : 1;
    std::int8_t m_flag2 : 1;
    std::int8_t m_flag3 : 1;
    std::int8_t m_flag4 : 1;
    char field_5D[3];

    static void InjectHooks();

    CTaskComplexAvoidOtherPedWhileWandering(CPed* ped, CVector* targetPoint, std::int32_t moveState);
    ~CTaskComplexAvoidOtherPedWhileWandering();
private:
    CTaskComplexAvoidOtherPedWhileWandering* Constructor(CPed* ped, CVector* targetPoint, std::int32_t moveState);
public:
    CTask* Clone() override;
    CTask* ControlSubTask(CPed* ped) override;
    eTaskType GetId() override { return TASK_COMPLEX_AVOID_OTHER_PED_WHILE_WANDERING; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;

    void QuitIK(CPed* ped);
    std::uint8_t NearbyPedsInSphere(CColSphere* colsphere, CPed* ped);
    void SetUpIK(CPed* ped);
    bool ComputeSphere(CPed* ped, CColSphere* colsphere, CPed** pedsToCheck, CPed** pedsInSphere);
    void ComputeAvoidSphere(CPed* ped, CColSphere* colsphere);
    bool ComputeDetourTarget(CPed* ped, CColSphere* colsphere);
    bool ComputeDetourTarget(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexAvoidOtherPedWhileWandering, 0x60);
