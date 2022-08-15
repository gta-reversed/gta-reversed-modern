#pragma once

#include "TaskComplexDestroyCar.h"
#include "Vector.h"
#include <Base.h>

class CVehicle;
class CPed;
class CEvent;

class CTaskComplexDestroyCarArmed : public CTaskComplexDestroyCar {
public:
    CVector m_vehPos = {};         // 0x20
    CVector m_vehToPedVector = {}; // 0x2C
    float m_rangeMax = {};         // 0x38
    int32 dword28 = {};            // 0x3C
    float m_rangeMin = {};         // 0x40
    int32 dword30 = {};            // 0x44
    float m_pedToVehDist = {};     // 0x48
    float dword38 = {};            // 0x4C
    bool dword3C = {};             // 0x50
    int32 dword40 = {-1};          // 0x54
    CVector m_posn = {};           // 0x58

public:
    static void InjectHooks();

    ~CTaskComplexDestroyCarArmed();
    CTaskComplexDestroyCarArmed(CVehicle* vehicleToDestroy, CVector posn);

    void CalculateSearchPositionAndRanges(CPed* ped);
    void CreateSubTask(int32 a2, CPed* ped);

    static constexpr eTaskType Type = eTaskType::TASK_COMPLEX_DESTROY_CAR_ARMED;

    CTask* Clone() override;
    eTaskType GetTaskType() override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private: // Wrappers for hooks
    // 0x621F50
    CTaskComplexDestroyCarArmed* Constructor(CVehicle* vehicleToDestroy, CVector posn) {
        this->CTaskComplexDestroyCarArmed::CTaskComplexDestroyCarArmed(vehicleToDestroy, posn);
        return this;
    }

    // 0x622010
    CTaskComplexDestroyCarArmed* Destructor() {
        this->CTaskComplexDestroyCarArmed::~CTaskComplexDestroyCarArmed();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexDestroyCarArmed, 0x64);
