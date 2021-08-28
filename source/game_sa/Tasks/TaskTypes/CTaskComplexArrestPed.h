#include "CTaskComplex.h"

class CVehicle;
class CTaskComplexArrestPed : public CTaskComplex {
public:
    bool m_subTaskNeedsToBeCreated;
    CPed* m_pedToArrest;
    std::int32_t field_14;
    std::int32_t field_18;
    std::int32_t field_1C;
    CVehicle* m_vehicle;

    static void InjectHooks();

    CTaskComplexArrestPed(CPed* ped);
    ~CTaskComplexArrestPed();
private:
    CTaskComplexArrestPed* Constructor(CPed* ped);
public:
    CTask* Clone() override { return new CTaskComplexArrestPed(m_pedToArrest); }
    eTaskType GetId() override { return TASK_COMPLEX_ARREST_PED; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(std::int32_t taskId, CPed* ped);

};

VALIDATE_SIZE(CTaskComplexArrestPed, 0x24);
