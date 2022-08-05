/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Restart.h"

void CRestart::InjectHooks() {
    RH_ScopedClass(CRestart);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Initialise, 0x460630);
    RH_ScopedInstall(AddHospitalRestartPoint, 0x460730);
    RH_ScopedInstall(AddPoliceRestartPoint, 0x460780);
    RH_ScopedInstall(OverrideNextRestart, 0x4607D0);
    RH_ScopedInstall(CancelOverrideRestart, 0x460800);
    RH_ScopedInstall(ClearRespawnPointForDurationOfMission, 0x460840);
    RH_ScopedInstall(SetRespawnPointForDurationOfMission, 0x460810);
    RH_ScopedInstall(FindClosestHospitalRestartPoint, 0x460850);
    RH_ScopedInstall(FindClosestPoliceRestartPoint, 0x460A50);
    RH_ScopedInstall(Load, 0x5D3770);
    RH_ScopedInstall(Save, 0x5D3620);
}

// 0x460630
void CRestart::Initialise() {
    for (auto i = 0u; i < MAX_RESTART_POINTS; i++) {
        HospitalRestartHeadings[i] = 0.0f;
        HospitalRestartPoints[i] = CVector{};
    }
    NumberOfHospitalRestarts = 0;

    for (auto i = 0u; i < MAX_RESTART_POINTS; i++) {
        PoliceRestartHeadings[i] = 0.0f;
        PoliceRestartPoints[i] = CVector{};
    }
    NumberOfPoliceRestarts = 0;

    OverridePosition = CVector{};
    OverrideHeading = 0.0f;
    bOverrideRestart = false;
    bFadeInAfterNextDeath = false;
    bFadeInAfterNextArrest = true; // todo: always true
    ScriptExtraHospitalRestartPoint_Radius = 0.0f;
    ScriptExtraPoliceRestartPoint_Radius = 0.0f;
    bOverrideRespawnBasePointForMission = false;
}

// 0x460730
void CRestart::AddHospitalRestartPoint(CVector const& point, float angle, int32 townId) {
    HospitalRestartPoints[NumberOfHospitalRestarts]    = point;
    HospitalRestartHeadings[NumberOfHospitalRestarts]  = angle;
    HospitalRestartWhenToUse[NumberOfHospitalRestarts] = townId;
    NumberOfHospitalRestarts++;
}

// 0x460780
void CRestart::AddPoliceRestartPoint(CVector const& point, float angle, int32 townId) {
    PoliceRestartPoints[NumberOfPoliceRestarts]    = point;
    PoliceRestartHeadings[NumberOfPoliceRestarts]  = angle;
    PoliceRestartWhenToUse[NumberOfPoliceRestarts] = townId;
    NumberOfPoliceRestarts++;
}

// 0x4607D0
void CRestart::OverrideNextRestart(CVector const& point, float angle) {
    OverridePosition = point;
    OverrideHeading  = angle;
    bOverrideRestart = true;
}

// 0x460800
void CRestart::CancelOverrideRestart() {
    bOverrideRestart = false;
}

// 0x460810
void CRestart::SetRespawnPointForDurationOfMission(CVector point) {
    bOverrideRespawnBasePointForMission = true;
    OverrideRespawnBasePointForMission  = point;
}

// 0x460840
void CRestart::ClearRespawnPointForDurationOfMission() {
    bOverrideRespawnBasePointForMission = false;
}

// 0x460850
void CRestart::FindClosestHospitalRestartPoint(CVector point, CVector& outPos, float& outAngle) {
    if (bOverrideRestart) {
        outPos = OverridePosition;
        outAngle = OverrideHeading;
        bOverrideRestart = false;
        return;
    }

    if (bOverrideRespawnBasePointForMission) {
        point = OverrideRespawnBasePointForMission;
        bOverrideRespawnBasePointForMission = false;
    }

    if (ScriptExtraHospitalRestartPoint_Radius <= 0.0f || DistanceBetweenPoints(ScriptExtraHospitalRestartPoint_Pos, point) >= ScriptExtraHospitalRestartPoint_Radius) {
        const auto pointLevel = CTheZones::GetLevelFromPosition(point);
        float closestDist = FLT_MAX; // OG: 10'000'000.0f
        int32 closestIdx = -1;
        for (auto i = 0u; i < NumberOfHospitalRestarts; i++) {
            if ((int32)CStats::GetStatValue(STAT_CITY_UNLOCKED) >= HospitalRestartWhenToUse[i]) {
                const auto& restartPos = HospitalRestartPoints[i];
                auto dist = DistanceBetweenPoints(restartPos, point);
                if (pointLevel != eLevelName::LEVEL_NAME_COUNTRY_SIDE && pointLevel != CTheZones::GetLevelFromPosition(restartPos)) {
                    dist *= 6.0f;
                }
                if (dist < closestDist) {
                    closestDist = dist;
                    closestIdx = (int32)i;
                }
            }
        }

        if (closestIdx >= 0u) {
            outPos = HospitalRestartPoints[closestIdx];
            outAngle = HospitalRestartHeadings[closestIdx];
        }
    } else {
        outPos = ScriptExtraHospitalRestartPoint_Pos;
        outAngle = ScriptExtraHospitalRestartPoint_Angle;
    }
}

// 0x460A50
void CRestart::FindClosestPoliceRestartPoint(CVector point, CVector& outPos, float& outAngle) {
    if (bOverrideRestart) {
        outPos = OverridePosition;
        outAngle = OverrideHeading;
        bOverrideRestart = false;
        return;
    }

    if (bOverrideRespawnBasePointForMission) {
        point = OverrideRespawnBasePointForMission;
        bOverrideRespawnBasePointForMission = false;
    }

    if (ScriptExtraPoliceRestartPoint_Radius <= 0.0f || DistanceBetweenPoints(ScriptExtraPoliceRestartPoint_Pos, point) >= ScriptExtraPoliceRestartPoint_Radius) {
        const auto pointLevel = CTheZones::GetLevelFromPosition(point);
        float closestDist = FLT_MAX; // OG: 10'000'000.0f
        int32 closestIdx = -1;
        for (auto i = 0u; i < NumberOfPoliceRestarts; i++) {
            if ((int32)CStats::GetStatValue(STAT_CITY_UNLOCKED) >= PoliceRestartWhenToUse[i]) {
                const auto& restartPos = PoliceRestartPoints[i];
                auto dist = DistanceBetweenPoints(restartPos, point);
                if (pointLevel != eLevelName::LEVEL_NAME_COUNTRY_SIDE && pointLevel != CTheZones::GetLevelFromPosition(restartPos)) {
                    dist *= 6.0f;
                }
                if (dist < closestDist) {
                    closestDist = dist;
                    closestIdx = (int32)i;
                }
            }
        }

        if (closestIdx >= 0u) {
            outPos = PoliceRestartPoints[closestIdx];
            outAngle = PoliceRestartHeadings[closestIdx];
        }
    } else {
        outPos = ScriptExtraPoliceRestartPoint_Pos;
        outAngle = ScriptExtraPoliceRestartPoint_Angle;
    }
}

// 0x5D3770
void CRestart::Load() {
    Initialise();

    CGenericGameStorage::SaveDataToWorkBuffer(&NumberOfHospitalRestarts, 2);
    for (auto i = 0; i < NumberOfHospitalRestarts; ++i) {
        CGenericGameStorage::SaveDataToWorkBuffer(&HospitalRestartPoints[i], 12);
        CGenericGameStorage::SaveDataToWorkBuffer(&HospitalRestartHeadings[i], 4);
        CGenericGameStorage::SaveDataToWorkBuffer(&HospitalRestartWhenToUse[i], 4);
    }

    CGenericGameStorage::SaveDataToWorkBuffer(&NumberOfPoliceRestarts, 2);
    for (auto j = 0; j < NumberOfPoliceRestarts; ++j) {
        CGenericGameStorage::SaveDataToWorkBuffer(&PoliceRestartPoints[j], 12);
        CGenericGameStorage::SaveDataToWorkBuffer(&PoliceRestartHeadings[j], 4);
        CGenericGameStorage::SaveDataToWorkBuffer(&PoliceRestartWhenToUse[j], 4);
    }

    CGenericGameStorage::SaveDataToWorkBuffer(&bOverrideRestart, 1);
    CGenericGameStorage::SaveDataToWorkBuffer(&OverridePosition, 12);
    CGenericGameStorage::SaveDataToWorkBuffer(&bFadeInAfterNextDeath, 1);
    CGenericGameStorage::SaveDataToWorkBuffer(&bFadeInAfterNextArrest, 1);

    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraHospitalRestartPoint_Pos, 12);
    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraHospitalRestartPoint_Radius, 4);
    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraHospitalRestartPoint_Angle, 4);

    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraPoliceRestartPoint_Pos, 12);
    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraPoliceRestartPoint_Radius, 4);
    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraPoliceRestartPoint_Angle, 4);
}

// 0x5D3620
void CRestart::Save() {
    CGenericGameStorage::SaveDataToWorkBuffer(&NumberOfHospitalRestarts, 2);
    for (auto i = 0; i < NumberOfHospitalRestarts; ++i) {
        CGenericGameStorage::SaveDataToWorkBuffer(&HospitalRestartPoints[i], 12);
        CGenericGameStorage::SaveDataToWorkBuffer(&HospitalRestartHeadings[i], 4);
        CGenericGameStorage::SaveDataToWorkBuffer(&HospitalRestartWhenToUse[i], 4);
    }

    CGenericGameStorage::SaveDataToWorkBuffer(&NumberOfPoliceRestarts, 2);
    for (auto j = 0; j < NumberOfPoliceRestarts; ++j) {
        CGenericGameStorage::SaveDataToWorkBuffer(&PoliceRestartPoints[j], 12);
        CGenericGameStorage::SaveDataToWorkBuffer(&PoliceRestartHeadings[j], 4);
        CGenericGameStorage::SaveDataToWorkBuffer(&PoliceRestartWhenToUse[j], 4);
    }

    CGenericGameStorage::SaveDataToWorkBuffer(&bOverrideRestart, 1);
    CGenericGameStorage::SaveDataToWorkBuffer(&OverridePosition, 12);
    CGenericGameStorage::SaveDataToWorkBuffer(&bFadeInAfterNextDeath, 1);
    CGenericGameStorage::SaveDataToWorkBuffer(&bFadeInAfterNextArrest, 1);

    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraHospitalRestartPoint_Pos, 12);
    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraHospitalRestartPoint_Radius, 4);
    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraHospitalRestartPoint_Angle, 4);

    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraPoliceRestartPoint_Pos, 12);
    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraPoliceRestartPoint_Radius, 4);
    CGenericGameStorage::SaveDataToWorkBuffer(&ScriptExtraPoliceRestartPoint_Angle, 4);
}
