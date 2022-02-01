/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimple.h"
#include "Vehicle.h"

class CTaskSimpleCarSetPedOut : public CTaskSimple {
public:
    CVehicle* m_pTargetVehicle;
    int32 m_nTargetDoor;
    bool m_bSwitchOffEngine; 
    bool m_bWarpingOutOfCar;
    bool m_bFallingOutOfCar;	// jumping or falling off car or bike
    bool m_bKnockedOffBike;
    uint8 m_nDoorFlagsToClear;
    uint8 m_nNumGettingInToClear;
private:
    char pad[2];
public:

	CTaskSimpleCarSetPedOut(CVehicle *pTargetVehicle, int32 nTargetDoor, bool bSwitchOffEngine);
    ~CTaskSimpleCarSetPedOut();

    CTask* Clone() override;
    eTaskType GetTaskType() override { return TASK_SIMPLE_CAR_SET_PED_OUT; };
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return false; }
    bool ProcessPed(CPed* ped) override;

};

VALIDATE_SIZE(CTaskSimpleCarSetPedOut, 0x18);

