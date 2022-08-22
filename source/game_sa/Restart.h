#pragma once

#include "Vector.h"

class CRestart {
public:
    static constexpr uint32 MAX_RESTART_POINTS{ 10u };

    static inline bool& bOverrideRespawnBasePointForMission = *(bool*)0xA43248;
    static inline CVector& OverrideRespawnBasePointForMission = *(CVector*)0xA4342C;
    static inline float& OverrideHeading = *(float*)0xA43260;
    static inline bool& bOverrideRestart = *(bool*)0xA43264;
    static inline CVector& OverridePosition = *(CVector*)0xA43408;

    static inline bool& bFadeInAfterNextArrest = *(bool*)0xA4325C;
    static inline bool& bFadeInAfterNextDeath = *(bool*)0xA4325D;

    static inline uint16& NumberOfPoliceRestarts = *(uint16*)0xA43268;
    static inline int32 (&PoliceRestartWhenToUse)[MAX_RESTART_POINTS] = *(int32(*)[MAX_RESTART_POINTS])0xA43270;
    static inline float (&PoliceRestartHeadings)[MAX_RESTART_POINTS] = *(float (*)[MAX_RESTART_POINTS])0xA43298;
    static inline CVector (&PoliceRestartPoints)[MAX_RESTART_POINTS] = *(CVector(*)[MAX_RESTART_POINTS])0xA43390;

    static inline uint16& NumberOfHospitalRestarts = *(uint16*)0xA4326C;
    static inline int32 (&HospitalRestartWhenToUse)[MAX_RESTART_POINTS] = *(int32(*)[MAX_RESTART_POINTS])0xA432C0;
    static inline float (&HospitalRestartHeadings)[MAX_RESTART_POINTS] = *(float (*)[MAX_RESTART_POINTS])0xA432E8;
    static inline CVector (&HospitalRestartPoints)[MAX_RESTART_POINTS] = *(CVector(*)[MAX_RESTART_POINTS])0xA43318;

    // Script command 2271 (COMMAND_SET_EXTRA_HOSPITAL_RESTART_POINT) arguments
    static inline CVector& ExtraHospitalRestartCoors = *(CVector*)0xA43414;
    static inline float& ExtraHospitalRestartRadius = *(float*)0xA43258;
    static inline float& ExtraHospitalRestartHeading = *(float*)0xA43254;

    // Script command 2272 (COMMAND_SET_EXTRA_POLICE_RESTART_POINT) arguments
    static inline CVector& ExtraPoliceStationRestartCoors = *(CVector*)0xA43420;
    static inline float& ExtraPoliceStationRestartRadius = *(float*)0xA43250;
    static inline float& ExtraPoliceStationRestartHeading = *(float*)0xA4324C;

public:
    static void InjectHooks();

    static void Initialise();
    static void AddHospitalRestartPoint(const CVector& point, float angle, int32 townId);
    static void AddPoliceRestartPoint(const CVector& point, float angle, int32 townId);
    static void OverrideNextRestart(CVector const& point, float angle);
    static void CancelOverrideRestart();
    static void SetRespawnPointForDurationOfMission(CVector point);
    static void ClearRespawnPointForDurationOfMission();
    static void FindClosestHospitalRestartPoint(CVector point, CVector& outPos, float& outAngle);
    static void FindClosestPoliceRestartPoint(CVector point, CVector& storedPoint, float& outAngle);
    static bool Load();
    static bool Save();
};
