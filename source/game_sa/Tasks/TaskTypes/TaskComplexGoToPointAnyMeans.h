#pragma once
#include "TaskComplex.h"
#include "Vector.h"
#include "Ped.h" // for eMoveState

class CVehicle;

class CTaskComplexGoToPointAnyMeans : public CTaskComplex {
public:
    CVector m_posn = {};           // 0xC
    eMoveState m_moveState = {};   // 0x18
    float m_fRadius = {};          // 0x1C
    CVehicle* m_vehicle = {};      // 0x20
    int32 dword2C = {};            // 0x24
    uint32 m_nStartTimeInMs = {};  // 0x28
    uint32 m_nTimeOffsetInMs = {}; // 0x2C
    bool byte32 = {};              // 0x30
    bool m_bResetStartTime = {};   // 0x31

public:
    static void InjectHooks();

    ~CTaskComplexGoToPointAnyMeans();
    CTaskComplexGoToPointAnyMeans(int32 a2, CVector const& posn, float a4, int32 a5);
    CTaskComplexGoToPointAnyMeans(int32 moveState, CVector const& posn, CVehicle* vehicle, float radius, int32 a6);

    CTask* CreateSubTask(int32 taskType, CPed* ped);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GO_TO_POINT_ANY_MEANS;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x66B720
    CTaskComplexGoToPointAnyMeans* Constructor(int32 a2, CVector const& posn, float a4, int32 a5) {
        this->CTaskComplexGoToPointAnyMeans::CTaskComplexGoToPointAnyMeans(a2, posn, a4, a5);
        return this;
    }
    // 0x66B790
    CTaskComplexGoToPointAnyMeans* Constructor(int32 moveState, CVector const& posn, CVehicle* vehicle, float radius, int32 a6) {
        this->CTaskComplexGoToPointAnyMeans::CTaskComplexGoToPointAnyMeans(moveState, posn, vehicle, radius, a6);
        return this;
    }

    // 0x66B830
    CTaskComplexGoToPointAnyMeans* Destructor() {
        this->CTaskComplexGoToPointAnyMeans::~CTaskComplexGoToPointAnyMeans();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexGoToPointAnyMeans, 0x34);
