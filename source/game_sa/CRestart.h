/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVector.h"

class  CRestart
{
public:
	static bool &bOverrideRespawnBasePointForMission;
	static CVector *OverrideRespawnBasePointForMission;
	static float &OverrideHeading;
	static bool &bOverrideRestart;
	static CVector *OverridePosition;

	static short &NumberOfPoliceRestarts;
	static int &PoliceRestartWhenToUse;	// [10]
	static float &PoliceRestartHeadings;	// [10]
	static CVector *PoliceRestartPoints;	// [10]

	static short &NumberOfHospitalRestarts;
	static int &HospitalRestartWhenToUse;	// [10]
	static float &HospitalRestartHeadings;	// [10]
	static CVector *HospitalRestartPoints;	// [10]

	static void AddHospitalRestartPoint(CVector const &point, float angle, int townId);
	static void AddPoliceRestartPoint(CVector const &point, float angle, int townId);
	static void CancelOverrideRestart();
	static void ClearRespawnPointForDurationOfMission();
	static void FindClosestHospitalRestartPoint(CVector point, CVector *storedPoint, float *storedAngle);
	static void FindClosestPoliceRestartPoint(CVector point, CVector *storedPoint, float *storedAngle);
	static void Initialise();
	static void Load();
	static void OverrideNextRestart(CVector const& point, float angle);
	//static void Save();
	//static void SetRespawnPointForDurationOfMission(CVector point);
};