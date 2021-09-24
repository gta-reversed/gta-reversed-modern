/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CVector.h"

class CRestart {
public:
    static bool&    bOverrideRespawnBasePointForMission;
    static CVector* OverrideRespawnBasePointForMission;
    static float&   OverrideHeading;
    static bool&    bOverrideRestart;
    static CVector* OverridePosition;

    static int16&   NumberOfPoliceRestarts;
    static int32&   PoliceRestartWhenToUse; // [10]
    static float&   PoliceRestartHeadings;  // [10]
    static CVector* PoliceRestartPoints;    // [10]

    static int16&   NumberOfHospitalRestarts;
    static int32&   HospitalRestartWhenToUse; // [10]
    static float&   HospitalRestartHeadings;  // [10]
    static CVector* HospitalRestartPoints;    // [10]

    static void AddHospitalRestartPoint(CVector const& point, float angle, int32 townId);
    static void AddPoliceRestartPoint(CVector const& point, float angle, int32 townId);
    static void CancelOverrideRestart();
    static void ClearRespawnPointForDurationOfMission();
    static void FindClosestHospitalRestartPoint(CVector point, CVector* storedPoint, float* storedAngle);
    static void FindClosestPoliceRestartPoint(CVector point, CVector* storedPoint, float* storedAngle);
    static void Initialise();
    static void Load();
    static void OverrideNextRestart(CVector const& point, float angle);
    // static void Save();
    // static void SetRespawnPointForDurationOfMission(CVector point);
};