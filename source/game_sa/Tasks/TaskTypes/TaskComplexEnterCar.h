/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "PathFind.h"
#include "TaskUtilityLineUpPedWithCar.h"

enum eTargetDoor {
    TARGET_DOOR_FRONT_LEFT  = 0,
    TARGET_DOOR_FRONT_RIGHT = 8,
    TARGET_DOOR_REAR_RIGHT  = 9,
    TARGET_DOOR_DRIVER      = 10,
    TARGET_DOOR_REAR_LEFT   = 11
};

class CTaskComplexEnterCar : public CTaskComplex {
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
    char  _pad[3];
    int32 m_nTargetDoor;
    int32 m_nTargetDoorOppositeToFlag;
    int32 m_nTargetSeat;
    int32 m_nDraggedPedDownTime;
    int32 m_nMoveState; // see eMoveState

    uint8                         m_nNumGettingInSet;
    uint8                         m_nCamMovementChoice;
    char                          _pad2[2];
    CVector                       m_vTargetDoorPos;
    CTaskUtilityLineUpPedWithCar* m_pTaskUtilityLineUpPedWithCar;
    bool                          m_bIsAborting;
    char                          _pad3[3];
    CPed*                         m_pDraggedPed;
    uint8                         m_nDoorFlagsSet; // used for CVehicle::SetGettingInFlags
    char                          _pad4[3];
    float                         m_fCruiseSpeed;
    int32                         m_nEnterCarStartTime;

public:
    // Shouldn't be used directly, use CTaskComplexEnterCarAsDriver or CTaskComplexEnterCarAsPassenger instead
    CTaskComplexEnterCar(CVehicle* targetVehicle, bool bAsDriver, bool bQuitAfterOpeningDoor, bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff = false);
    ~CTaskComplexEnterCar();

    bool           MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask*         CreateNextSubTask(CPed* ped) override;
    CTask*         CreateFirstSubTask(CPed* ped) override;
    CTask*         ControlSubTask(CPed* ped) override;
    virtual CTask* CreateNextSubTask_AfterSimpleCarAlign(CPed* ped);
    CVector        GetTargetPos();
};

VALIDATE_SIZE(CTaskComplexEnterCar, 0x50);
