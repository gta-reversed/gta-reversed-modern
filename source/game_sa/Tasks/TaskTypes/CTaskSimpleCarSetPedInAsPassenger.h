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
#include "CTaskUtilityLineUpPedWithCar.h"

class  CTaskSimpleCarSetPedInAsPassenger : public CTaskSimple {
public:
    bool m_bIsFinished;
private:
    char gap9[3];
public:
    CAnimBlendAssociation* m_pAnim;
    CVehicle* m_pTargetVehicle;
    int m_iTargetDoor;
    CTaskUtilityLineUpPedWithCar* m_pUtility;
    bool m_bWarpingInToCar;
    unsigned char m_nDoorFlagsToClear;
    unsigned char m_nNumGettingInToClear;
private:
    char _pad2[1];
public:

    CTaskSimpleCarSetPedInAsPassenger(CVehicle *pTargetVehicle, int nTargetDoor, CTaskUtilityLineUpPedWithCar *pUtility);

};

VALIDATE_SIZE(CTaskSimpleCarSetPedInAsPassenger, 0x20);

