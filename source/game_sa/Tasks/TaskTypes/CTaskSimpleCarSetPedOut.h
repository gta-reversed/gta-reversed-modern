/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CVehicle.h"

class CTaskSimpleCarSetPedOut : public CTaskSimple {
public:
    CVehicle* m_pTargetVehicle;
    int m_nTargetDoor; 
    bool m_bSwitchOffEngine; 
    bool m_bWarpingOutOfCar;
    bool m_bFallingOutOfCar;	// jumping or falling off car or bike
    bool m_bKnockedOffBike;
    unsigned char m_nDoorFlagsToClear;
    unsigned char m_nNumGettingInToClear;
private:
    char pad[2];
public:

	CTaskSimpleCarSetPedOut(CVehicle *pTargetVehicle, int nTargetDoor, bool bSwitchOffEngine);
    ~CTaskSimpleCarSetPedOut();

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_SIMPLE_CAR_SET_PED_OUT; };
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override { return false; }
    bool ProcessPed(CPed* ped) override;

};

VALIDATE_SIZE(CTaskSimpleCarSetPedOut, 0x18);

