#pragma once
#include "TaskComplex.h"

class CVector;
class CVehicle;

class CTaskComplexGoToCarDoorAndStandStill : public CTaskComplex {
public:
    CVehicle* m_pVehicle = {};               // 0xC
    int32 f4 = {};                           // 0x10
    bool f14 = {};                           // 0x14
    float f18 = {};                          // 0x18
    float f1C = {};                          // 0x1C
    float f20 = {};                          // 0x20
    int32 f24 = {};                          // 0x24
    float f28 = {};                          // 0x28
    float f2C = {};                          // 0x2C
    int16 f30 = {};                          // 0x30
    int32 m_nDoorId = {};                    // 0x34
    CVector m_vecPositionToOpenCarDoor = {}; // 0x38
    int32 f44 = {};                          // 0x44
    bool f48 = {};                           // 0x48
    bool f49 = {};                           // 0x49
    int32 f4C = {};                          // 0x4C
    int32 dword44 = {};                      // 0x50

public:
    static void InjectHooks();

    CTaskComplexGoToCarDoorAndStandStill(CVehicle* vehicle, int32 a3, bool a4, int32 a5, float a6, float a7, float a8, int32 a9);
    ~CTaskComplexGoToCarDoorAndStandStill();

    BOOL IsVehicleInRange(int32 a2);
    CVector* ComputeRouteToDoor(CPed const& ped);
    void* CreateSubTask(eTaskType taskType, const CPed* a3);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x645780
    CTaskComplexGoToCarDoorAndStandStill* Constructor(CVehicle* vehicle, int32 a3, bool a4, int32 a5, float a6, float a7, float a8, int32 a9) {
        this->CTaskComplexGoToCarDoorAndStandStill::CTaskComplexGoToCarDoorAndStandStill(vehicle, a3, a4, a5, a6, a7, a8, a9);
        return this;
    }

    // 0x64A580
    CTaskComplexGoToCarDoorAndStandStill* Destructor() {
        this->CTaskComplexGoToCarDoorAndStandStill::~CTaskComplexGoToCarDoorAndStandStill();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexGoToCarDoorAndStandStill, 0x54);
