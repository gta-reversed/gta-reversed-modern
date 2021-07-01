/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CBaseModelInfo.h"
#include "CAtomicModelInfo.h"
#include "CDamageAtomicModelInfo.h"
#include "CLodAtomicModelInfo.h"
#include "CVehicleModelInfo.h"
#include "CWeaponModelInfo.h"
#include "CTimeModelInfo.h"
#include "CLodTimeModelInfo.h"
#include "CPedModelInfo.h"

enum eModelInfoType : unsigned char {
    MODEL_INFO_TYPE_ATOMIC = 1,
    MODEL_INFO_TYPE_TIME = 3,
    MODEL_INFO_TYPE_WEAPON = 4,
    MODEL_INFO_TYPE_CLUMP = 5,
    MODEL_INFO_TYPE_VEHICLE = 6,
    MODEL_INFO_TYPE_PED = 7,
    MODEL_INFO_TYPE_LOD_ATOMIC = 8,
};

class CModelInfo {
public:
    // static CBaseModelInfo *ms_modelInfoPtrs[20000]; Use GetModelInfo(int index) to get model info by id
    static constexpr int NUM_MODEL_INFOS = 20000;
    static CBaseModelInfo* (&ms_modelInfoPtrs)[NUM_MODEL_INFOS];
    static int& ms_lastPositionSearched;

    static constexpr int NUM_ATOMIC_MODEL_INFOS = 14000;
    static CStore<CAtomicModelInfo, NUM_ATOMIC_MODEL_INFOS>& ms_atomicModelInfoStore;

    static constexpr int NUM_DAMAGE_ATOMIC_MODEL_INFOS = 70;
    static CStore<CDamageAtomicModelInfo, NUM_DAMAGE_ATOMIC_MODEL_INFOS>& ms_damageAtomicModelInfoStore;

    static constexpr int NUM_LOD_ATOMIC_MODEL_INFOS = 1;
    static CStore<CLodAtomicModelInfo, NUM_LOD_ATOMIC_MODEL_INFOS>& ms_lodAtomicModelInfoStore;

    static constexpr int NUM_TIME_MODEL_INFOS = 169;
    static CStore<CTimeModelInfo, NUM_TIME_MODEL_INFOS>& ms_timeModelInfoStore;

    static constexpr int NUM_LOD_TIME_MODEL_INFOS = 1;
    static CStore<CLodTimeModelInfo, NUM_LOD_TIME_MODEL_INFOS>& ms_lodTimeModelInfoStore;

    static constexpr int NUM_WEAPON_MODEL_INFOS = 51;
    static CStore<CWeaponModelInfo, NUM_WEAPON_MODEL_INFOS>& ms_weaponModelInfoStore;

    static constexpr int NUM_CLUMP_MODEL_INFOS = 92;
    static CStore<CClumpModelInfo, NUM_CLUMP_MODEL_INFOS>& ms_clumpModelInfoStore;

    static constexpr int NUM_VEHICLE_MODEL_INFOS = 212;
    static CStore<CVehicleModelInfo, NUM_VEHICLE_MODEL_INFOS>& ms_vehicleModelInfoStore;

    static constexpr int NUM_PED_MODEL_INFOS = 278;
    static CStore<CPedModelInfo, NUM_PED_MODEL_INFOS>& ms_pedModelInfoStore;

    static constexpr int NUM_2DFX_INFOS = 100;
    static CStore<C2dEffect, NUM_2DFX_INFOS>& ms_2dFXInfoStore;

public:
    static void InjectHooks();

    static void ReInit2dEffects();
    static void ShutDown();
    static CAtomicModelInfo* AddAtomicModel(int index);
    static CDamageAtomicModelInfo* AddDamageAtomicModel(int index);
    static CLodAtomicModelInfo* AddLodAtomicModel(int index);
    static CTimeModelInfo* AddTimeModel(int index);
    static CLodTimeModelInfo* AddLodTimeModel(int index);
    static CWeaponModelInfo* AddWeaponModel(int index);
    static CClumpModelInfo* AddClumpModel(int index);
    static CVehicleModelInfo* AddVehicleModel(int index);
    static class CPedModelInfo* AddPedModel(int index);
    static void Initialise();
    static CBaseModelInfo* GetModelInfo(const char* name, int* index);
    static CBaseModelInfo* GetModelInfoFromHashKey(unsigned int uiHash, int* index);
    static CBaseModelInfo* GetModelInfoUInt16(const char* name, unsigned short* pOutIndex);
    // get model in range (search for model only in range (min;max))
    static CBaseModelInfo* GetModelInfo(const char* name, int minIndex, int maxIndex);
    static CStore<C2dEffect, NUM_2DFX_INFOS>* Get2dEffectStore();
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

    static CBaseModelInfo* GetModelInfo(int index) { return ms_modelInfoPtrs[index]; }
    static void SetModelInfo(int index, CBaseModelInfo* pInfo) { ms_modelInfoPtrs[index] = pInfo; }
};
