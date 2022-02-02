/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vehicle.h"
#include "Vector.h"

#define STUCK_CAR_CHECK_SIZE 16

struct StuckCar {
    int32   m_nCarHandle;
    CVector m_vCarPos;
    int32   m_nStartTime;
    float   m_fDistance;
    int32   m_nStuckTime;
    bool    m_bCarStuck;
    char    field_1D;
    bool    m_bStuck;
    bool    m_bFlipped;
    bool    m_bbWarp;
    char    m_pathID;
    char    __pad[2];
};

class CStuckCarCheck {
public:
    StuckCar m_aStuckCars[STUCK_CAR_CHECK_SIZE];

    static void InjectHooks();

    void Init();
    void AddCarToCheck(int32 carHandle, float distance, uint32 time, uint8 a5, bool bStuck, bool bFlipped, bool bWarp, int8 pathId);
    bool AttemptToWarpVehicle(CVehicle* vehicle, CVector* origin, float orientation);
    void ClearStuckFlagForCar(int32 carHandle);
    bool HasCarBeenStuckForAWhile(int32 carHandle);
    bool IsCarInStuckCarArray(int32 carHandle);
    void Process();
    void RemoveCarFromCheck(int32 carHandle);
    void ResetArrayElement(StuckCar& car);
};

VALIDATE_SIZE(CStuckCarCheck, 0x240);
