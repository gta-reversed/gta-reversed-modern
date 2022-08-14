#pragma once
#include "TaskComplex.h"
#include "Vector.h"
#include "Vehicle.h"
#include "Entity.h"

class CVehicle;
class CEntity;

class CTaskGangHassleVehicle : public CTaskComplex {
public:
    uint8     gapC[4] = {}; // 0xC
    CVehicle* m_pVehicle = {}; // 0x10
    int32     m_nHasslePosId = {}; // 0x14
    uint8     byte18 = {}; // 0x18
    uint8     gap19[3] = {}; // 0x19
    float     dword1C = {}; // 0x1C
    float     m_fOffsetX = {}; // 0x20
    CVector   m_vecPosn = {}; // 0x24
    bool      m_bRemoveAnim = {}; // 0x30
    bool      m_b31 = {}; // 0x31
    uint8     gap32[2] = {}; // 0x32
    CEntity*  m_pEntity = {}; // 0x34
    uint32    m_nTime = {}; // 0x38
    int32     dword3C = {}; // 0x3C
    bool      byte40 = {}; // 0x40
    uint8     byte41 = {}; // 0x41

public:
    static void InjectHooks();

    ~CTaskGangHassleVehicle();
    CTaskGangHassleVehicle(CVehicle* vehicle, int32 a3, uint8 a4, float a5, float a6);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GANG_HASSLE_VEHICLE;

    double GetTargetHeading(CPed* ped);
    void CalcTargetOffset();

    virtual CTask*    Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual CTask*    CreateNextSubTask(CPed* ped);
    virtual CTask*    CreateFirstSubTask(CPed* ped);
    virtual CTask*    ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x65FAC0
    CTaskGangHassleVehicle* Constructor(CVehicle* vehicle, int32 a3, uint8 a4, float a5, float a6) {
        this->CTaskGangHassleVehicle::CTaskGangHassleVehicle(vehicle, a3, a4, a5, a6);
        return this;
    }

    // 0x65FB60
    CTaskGangHassleVehicle* Destructor() {
        this->CTaskGangHassleVehicle::~CTaskGangHassleVehicle();
        return this;
    }

};
VALIDATE_SIZE(CTaskGangHassleVehicle, 0x44);
