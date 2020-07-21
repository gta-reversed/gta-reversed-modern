/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplex.h"
#include "CPathFind.h"
#include "CTaskUtilityLineUpPedWithCar.h"

/*enum eTargetDoor
{
    DOOR_FRONT_LEFT = 0,
    DOOR_FRONT_RIGHT = 8,
    DOOR_REAR_RIGHT = 9,
    DOOR_REAR_LEFT = 11
};*/

class CTaskComplexEnterCar : public CTaskComplex {
public:
    CVehicle* m_pTargetVehicle;
    union
    {
        unsigned char m_nFlags;
        struct
        {
            unsigned char m_bAsDriver : 1;
            unsigned char m_bQuitAfterOpeningDoor : 1;
            unsigned char m_bQuitAfterDraggingPedOut : 1;
            unsigned char m_bCarryOnAfterFallingOff : 1;
        };
    };
private:
    char _pad[3];
public:
    int m_nTargetDoor;
    int m_nTargetDoorOppositeToFlag;
    int m_nTargetSeat;
    int m_nDraggedPedDownTime;
    int m_nMoveState; // see eMoveState

    unsigned char m_nNumGettingInSet;
    unsigned char m_nCamMovementChoice;
private:
    char _pad2[2];
public:
    CVector m_vTargetDoorPos;
    CTaskUtilityLineUpPedWithCar* m_pTaskUtilityLineUpPedWithCar;
    bool m_bIsAborting;
private:
    char _pad3[3];
public:
    CPed* m_pDraggedPed;
    unsigned char m_nDoorFlagsSet; // used for CVehicle::SetGettingInFlags
private:
    char _pad4[3];
public:
    float m_fCruiseSpeed;
    int m_nEnterCarStartTime;

    // Shouldn't be used directly, use CTaskComplexEnterCarAsDriver or CTaskComplexEnterCarAsPassenger instead
    CTaskComplexEnterCar(CVehicle* pTargetVehicle, bool bAsDriver, bool bQuitAfterOpeningDoor,
        bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff = false);
    ~CTaskComplexEnterCar();

    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    virtual CTask* CreateNextSubTask_AfterSimpleCarAlign(CPed* ped);

};

VALIDATE_SIZE(CTaskComplexEnterCar, 0x50);
