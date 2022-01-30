#pragma once

#include "Vector.h"

class CRestart {
public:
    static int16&   NumberOfHospitalRestarts;
    static CVector  (&HospitalRestartPoints)[10];
    static float    (&HospitalRestartHeadings)[10];
    static int32    (&HospitalRestartWhenToUse)[10];

    static uint16&  NumberOfPoliceRestarts;
    static CVector  (&PoliceRestartPoints)[10];
    static float    (&PoliceRestartHeadings)[10];
    static int32    (&PoliceRestartWhenToUse)[10];

    static bool&    bOverrideRestart;
    static CVector& OverridePosition;
    static float&   OverrideHeading;
    static bool&    bOverrideRespawnBasePointForMission;
    static CVector& OverrideRespawnBasePointForMission;

    static bool&    bFadeInAfterNextDeath;
    static bool&    bFadeInAfterNextArrest;

    static CVector& ExtraHospitalRestartCoors;
    static float&   ExtraHospitalRestartRadius;
    static float&   ExtraHospitalRestartHeading;

    static CVector& ExtraPoliceStationRestartCoors;
    static float&   ExtraPoliceStationRestartRadius;
    static float&   ExtraPoliceStationRestartHeading;

public:
    static void InjectHooks();

    static void Initialise();
    static void AddHospitalRestartPoint(const CVector& point, float angle, int32 townId);
    static void AddPoliceRestartPoint(const CVector& point, float angle, int32 townId);
    static void CancelOverrideRestart();
    static void SetRespawnPointForDurationOfMission(CVector point);
    static void ClearRespawnPointForDurationOfMission();
    static void FindClosestHospitalRestartPoint(CVector point, CVector& outPos, float& outAngle);
    static void FindClosestPoliceRestartPoint(CVector point, CVector& storedPoint, float& outAngle);
    static void Initialise();
    static void Load();
    static void Save();
    static void OverrideNextRestart(CVector const& point, float angle);
};
