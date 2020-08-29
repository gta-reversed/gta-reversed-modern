/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CBaseModelInfo.h"
#include "CAtomicModelInfo.h"
#include "CVehicleModelInfo.h"
#include "CWeaponModelInfo.h"
#include "CTimeModelInfo.h"

enum eModelInfoType : unsigned char
{
    MODEL_INFO_TYPE_ATOMIC = 1,
    MODEL_INFO_TYPE_TIME = 3,
    MODEL_INFO_TYPE_WEAPON = 4,
    MODEL_INFO_TYPE_CLUMP = 5,
    MODEL_INFO_TYPE_VEHICLE = 6,
    MODEL_INFO_TYPE_PED = 7,
    MODEL_INFO_TYPE_LOD_ATOMIC = 8,
};

extern std::uint16_t& MI_GRASSHOUSE;
extern std::uint16_t& MI_FIRE_HYDRANT;
extern std::uint16_t& MI_PARKINGMETER;
extern std::uint16_t& MI_PARKINGMETER2;
extern std::uint16_t& MI_POOL_CUE_BALL;
extern std::uint16_t& MI_HARVESTERBODYPART1;
extern std::uint16_t& MI_HARVESTERBODYPART2;
extern std::uint16_t& MI_HARVESTERBODYPART3;
extern std::uint16_t& MI_HARVESTERBODYPART4;

class CModelInfo
{
public:
	// variables
	//static CBaseModelInfo *ms_modelInfoPtrs[20000]; Use GetModelInfo(int index) to get model info by id
	static CBaseModelInfo **ms_modelInfoPtrs;

	// functions
	static void ReInit2dEffects();
	static void ShutDown();
	static CAtomicModelInfo* AddAtomicModel(int index);
	static class CDamageAtomicModelInfo* AddDamageAtomicModel(int index);
	static class CLodAtomicModelInfo* AddLodAtomicModel(int index);
	static CTimeModelInfo* AddTimeModel(int index);
	static class CLodTimeModelInfo* AddLodTimeModel(int index);
	static CWeaponModelInfo* AddWeaponModel(int index);
	static CClumpModelInfo* AddClumpModel(int index);
	static CVehicleModelInfo* AddVehicleModel(int index);
	static class CPedModelInfo* AddPedModel(int index);
	static void Initialise();
	static CBaseModelInfo* GetModelInfo(char* name, int* index);
	static CBaseModelInfo* GetModelInfoFromHashKey(unsigned int arg0, int* index);
	static CBaseModelInfo* GetModelInfouint16_t(char* name, unsigned short* int16index);
	// get model in range (search for model only in range (min;max))
	static CBaseModelInfo* GetModelInfo(char* name, int minIndex, int maxInedx);
	static void* Get2dEffectStore();
	static bool IsBoatModel(int index);
	static bool IsCarModel(int index);
	static bool IsTrainModel(int index);
	static bool IsHeliModel(int index);
	static bool IsPlaneModel(int index);
	static bool IsBikeModel(int index);
	static bool IsFakePlaneModel(int index);
	static bool IsMonsterTruckModel(int index);
	static bool IsQuadBikeModel(int index);
	static bool IsBmxModel(int index);
	static bool IsTrailerModel(int index);
	// return -1 if model is not a vehicle model otherwise returns vehicle model type
	static int IsVehicleModelType(int index);

    static CBaseModelInfo *GetModelInfo(int index) { return ms_modelInfoPtrs[index]; }

};
