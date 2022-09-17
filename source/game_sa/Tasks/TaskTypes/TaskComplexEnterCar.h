/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "PathFind.h"
#include "TaskUtilityLineUpPedWithCar.h"
#include "eTargetDoor.h"

// Note: This class is abstract, that is, it can't be directly constructed,
// rather, use one of the derived classes.
class NOTSA_EXPORT_VTABLE CTaskComplexEnterCar : public CTaskComplex {
public:
    CVehicle* m_pTargetVehicle;
    union {
        uint8 m_nFlags;
        struct {
            uint8 m_bAsDriver : 1;
            uint8 m_bQuitAfterOpeningDoor : 1;
            uint8 m_bQuitAfterDraggingPedOut : 1;
            uint8 m_bCarryOnAfterFallingOff : 1;
        };
    };
    int32 m_nTargetDoor;
    int32 m_nTargetDoorOppositeToFlag;
    int32 m_nTargetSeat;
    int32 m_nDraggedPedDownTime;
    int32 m_nMoveState; // see eMoveState

    uint8                         m_nNumGettingInSet;
    uint8                         m_nCamMovementChoice;
    CVector                       m_vTargetDoorPos;
    CTaskUtilityLineUpPedWithCar* m_pTaskUtilityLineUpPedWithCar;
    bool                          m_bIsAborting;
    CPed*                         m_pDraggedPed;
    uint8                         m_nDoorFlagsSet; // used for CVehicle::SetGettingInFlags
    float                         m_fCruiseSpeed;
    int32                         m_nEnterCarStartTime;

public:
    static void InjectHooks();

    // Shouldn't be used directly, use `CTaskComplexEnterCarAsDriver` or `CTaskComplexEnterCarAsPassenger` instead
    CTaskComplexEnterCar(CVehicle* targetVehicle, bool bAsDriver, bool bQuitAfterOpeningDoor, bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff = false);
    ~CTaskComplexEnterCar() override;

    bool           MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask*         CreateNextSubTask(CPed* ped) override;
    CTask*         CreateFirstSubTask(CPed* ped) override;
    CTask*         ControlSubTask(CPed* ped) override;
    CTask*         CreateSubTask(eTaskType type, CPed* ped);
    virtual CTask* CreateNextSubTask_AfterSimpleCarAlign(CPed* ped);
    CVector        GetTargetPos();

    auto GetVehicle() const { return m_pTargetVehicle; }
private:
    // 0x63A220
    CTaskComplexEnterCar* Constructor(CVehicle* vehicle, bool bAsDriver, bool bQuitAfterOpeningDoor, bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff) {
        this->CTaskComplexEnterCar::CTaskComplexEnterCar(vehicle, bAsDriver, bQuitAfterOpeningDoor, bQuitAfterDraggingPedOut, bCarryOnAfterFallingOff);
        return this;
    }

    // 0x63DFA0
    CTaskComplexEnterCar* Destructor() {
        this->CTaskComplexEnterCar::~CTaskComplexEnterCar();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexEnterCar, 0x50);
