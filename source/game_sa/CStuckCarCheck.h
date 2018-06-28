/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVehicle.h"
#include "CVector.h"

class  CStuckCarCheck {
public:

    struct {
        int m_nCarHandle;
        CVector m_vCarPos;
        int m_nStartTime;
        float m_fDistance;
        int m_nTime;
        bool m_bCarStuck;
        char field_1D;
        char m_bStuck;
        char m_bFlipped;
        char m_bbWarp;
        char pathID;
        char __pad[2];
    } m_aStuckCars[16];

     void AddCarToCheck(int carHandle, float distance, unsigned int time, unsigned char a5, unsigned char bStuck, unsigned char bFlipped, unsigned char bWarp, signed char pathID);
     bool AttemptToWarpVehicle(CVehicle *vehicle, CVector *origin, float orientation);
     void ClearStuckFlagForCar(int carHandle);
     bool HasCarBeenStuckForAWhile(int carHandle);
     void Init();
     bool IsCarInStuckCarArray(int carHandle);
     void Process();
     void RemoveCarFromCheck(int carHandle);
     void ResetArrayElement(unsigned short index);
};

VALIDATE_SIZE(CStuckCarCheck, 0x240);

//#include "meta/meta.CStuckCarCheck.h"
