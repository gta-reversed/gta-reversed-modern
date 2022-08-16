#pragma once

#include "TaskComplexDestroyCar.h"
#include "Vector.h"

class CVehicle;

class CTaskComplexDestroyCarMelee : public CTaskComplexDestroyCar {
public:
    int32 m_field20 = {};  
    int32 m_field24 = {};  
    int32 m_field28 = {};  
    int32 m_field2C = {};  
    int32 m_field30 = {-1};
    int32 m_field34 = {};  

public:
    static void InjectHooks();

    static constexpr eTaskType Type = eTaskType::TASK_COMPLEX_DESTROY_CAR_MELEE;

    CTaskComplexDestroyCarMelee(CVehicle* vehToDestroy);
    ~CTaskComplexDestroyCarMelee();

    void CalculateSearchPositionAndRanges(CPed* ped);
    CTask* CreateSubTask(eTaskType taskType, CPed* ped);

    virtual eTaskType GetTaskType() { return Type; }
    virtual CTask* Clone();
    virtual bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x621D10
    CTaskComplexDestroyCarMelee* Constructor(CVehicle* vehToDestroy) { this->CTaskComplexDestroyCarMelee::CTaskComplexDestroyCarMelee(vehToDestroy); return this; }

    // 0x621DA0
    CTaskComplexDestroyCarMelee* Destructor() { this->CTaskComplexDestroyCarMelee::~CTaskComplexDestroyCarMelee(); return this; }
};
VALIDATE_SIZE(CTaskComplexDestroyCarMelee, 0x38);
