/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Restart.h"

int16& CRestart::NumberOfHospitalRestarts = *(int16*)0xA4326C;
CVector (&CRestart::HospitalRestartPoints)[10] = *(CVector(*)[10])0xA43318;
float (&CRestart::HospitalRestartHeadings)[10] = *(float(*)[10])0xA432E8;
int32 (&CRestart::HospitalRestartWhenToUse)[10] = *(int32(*)[10])0xA432C0;

uint16& CRestart::NumberOfPoliceRestarts = *(uint16*)0xA43268;
CVector (&CRestart::PoliceRestartPoints)[10] = *(CVector(*)[10])0xA43390;
float (&CRestart::PoliceRestartHeadings)[10] = *(float(*)[10])0xA43298;
int32 (&CRestart::PoliceRestartWhenToUse)[10] = *(int32(*)[10])0xA43270;

bool& CRestart::bOverrideRestart = *(bool*)0xA43264;
CVector& CRestart::OverridePosition = *(CVector*)0xA43408;
float& CRestart::OverrideHeading = *(float*)0xA43260;
bool& CRestart::bOverrideRespawnBasePointForMission = *(bool*)0xA43248;
CVector& CRestart::OverrideRespawnBasePointForMission = *(CVector*)0xA4342C;

bool& CRestart::bFadeInAfterNextDeath = *(bool*)0xA4325D;
bool& CRestart::bFadeInAfterNextArrest = *(bool*)0xA4325C;

CVector& CRestart::ExtraHospitalRestartCoors = *(CVector*)0xA43414;
float& CRestart::ExtraHospitalRestartRadius = *(float*)0xA43258;
float& CRestart::ExtraHospitalRestartHeading = *(float*)0x43254;

CVector& CRestart::ExtraPoliceStationRestartCoors = *(CVector*)0xA43420;
float& CRestart::ExtraPoliceStationRestartRadius = *(float*)0xA43250;
float& CRestart::ExtraPoliceStationRestartHeading = *(float*)0xA4324C;

void CRestart::InjectHooks() {
    RH_ScopedClass(CRestart);
    RH_ScopedCategoryRoot();

    RH_ScopedInstall(Initialise, 0x460630);
    RH_ScopedInstall(AddHospitalRestartPoint, 0x460730);
    RH_ScopedInstall(AddPoliceRestartPoint, 0x460780);
    RH_ScopedInstall(CancelOverrideRestart, 0x460800);
    RH_ScopedInstall(SetRespawnPointForDurationOfMission, 0x460810);
    RH_ScopedInstall(ClearRespawnPointForDurationOfMission, 0x460840);
    // RH_ScopedInstall(FindClosestHospitalRestartPoint, 0x460A50);
    // RH_ScopedInstall(FindClosestPoliceRestartPoint, 0x460850);
    RH_ScopedInstall(OverrideNextRestart, 0x4607D0);
    // RH_ScopedInstall(Load, 0x5D3770);
    // RH_ScopedInstall(Save, 0x5D3620);
}

// 0x460630
void CRestart::Initialise() {
    std::ranges::fill(HospitalRestartHeadings, 0.0f);
    std::ranges::fill(HospitalRestartPoints, CVector());

    std::ranges::fill(PoliceRestartHeadings, 0.0f);
    std::ranges::fill(PoliceRestartPoints, CVector());

    OverridePosition = CVector();
    NumberOfHospitalRestarts = 0;
    NumberOfPoliceRestarts = 0;
    bOverrideRestart = false;
    OverrideHeading = 0.0f;
    bFadeInAfterNextDeath = true;
    bFadeInAfterNextArrest = true;
    ExtraHospitalRestartRadius = 0.0f;
    ExtraPoliceStationRestartRadius = 0.0f;
    bOverrideRespawnBasePointForMission = false;
}

// 0x460730
void CRestart::AddHospitalRestartPoint(const CVector& point, float angle, int32 townId) {
    HospitalRestartPoints[NumberOfHospitalRestarts]    = point;
    HospitalRestartHeadings[NumberOfHospitalRestarts]  = angle;
    HospitalRestartWhenToUse[NumberOfHospitalRestarts] = townId;
    NumberOfHospitalRestarts += 1;
}

// 0x460780
void CRestart::AddPoliceRestartPoint(const CVector& point, float angle, int32 townId) {
    PoliceRestartPoints[NumberOfPoliceRestarts]    = point;
    PoliceRestartHeadings[NumberOfPoliceRestarts]  = angle;
    PoliceRestartWhenToUse[NumberOfPoliceRestarts] = townId;
    NumberOfPoliceRestarts += 1;
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

// 0x460A50
void CRestart::FindClosestHospitalRestartPoint(CVector point, CVector* storedPoint, float* storedAngle) {
    plugin::Call<0x460A50, CVector, CVector*, float*>(point, storedPoint, storedAngle);
}

// 0x460850
void CRestart::FindClosestPoliceRestartPoint(CVector point, CVector* storedPoint, float* storedAngle) {
    plugin::Call<0x460850, CVector, CVector*, float*>(point, storedPoint, storedAngle);
}

// 0x4607D0
void CRestart::OverrideNextRestart(const CVector& point, float angle) {
    OverridePosition = point;
    OverrideHeading  = angle;
    bOverrideRestart = true;
}

// 0x5D3770
bool CRestart::Load() {
    return plugin::CallAndReturn<bool, 0x5D3770>();
}

// 0x5D3620
bool CRestart::Save() {
    return plugin::CallAndReturn<bool, 0x5D3620>();
}
