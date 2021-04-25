/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CVehicle.h"
#include "CVector.h"

#define STUCK_CAR_CHECK_SIZE 16

struct StuckCar {
    int m_nCarHandle;
    CVector m_vCarPos;
    int m_nStartTime;
    float m_fDistance;
    int m_nStuckTime;
    bool m_bCarStuck;
    char field_1D;
    bool m_bStuck;
    bool m_bFlipped;
    bool m_bbWarp;
    char m_pathID;
    char __pad[2];
};

class CStuckCarCheck {
public:
    StuckCar m_aStuckCars[STUCK_CAR_CHECK_SIZE];

    static void InjectHooks();

    void Init();
    void AddCarToCheck(int carHandle, float distance, unsigned int time, unsigned char a5, bool bStuck, bool bFlipped, bool bWarp, signed char pathId);
    bool AttemptToWarpVehicle(CVehicle* vehicle, CVector* origin, float orientation);
    void ClearStuckFlagForCar(int carHandle);
    bool HasCarBeenStuckForAWhile(int carHandle);
    bool IsCarInStuckCarArray(int carHandle);
    void Process();
    void RemoveCarFromCheck(int carHandle);
    void ResetArrayElement(StuckCar& car);
};

VALIDATE_SIZE(CStuckCarCheck, 0x240);

//#include "meta/meta.CStuckCarCheck.h"
