#pragma once

#include "CMatrix.h"

class CEntity;
class CPhysical;
class CVehicle;

enum class eBuoyancyPointState : int32 {
    COMPLETELY_ABOVE_WATER = 0x0,
    COLLIDING_WITH_WATER   = 0x1,
    COMPLETELY_UNDER_WATER = 0x2,
};

#pragma pack(push, 8)
struct CBuoyancyCalcStruct {
    float           fCurrentAverageContribution;
    float           fNewPointContribution;
    CVector         vecCurOffsetTurnPoint;
    float           fAddedDistToWaterSurface;
    bool            bBuoyancyDataSummed;
    unsigned __int8 pad[3];
};
#pragma pack(pop)
VALIDATE_SIZE(CBuoyancyCalcStruct, 0x1C);

class cBuoyancy {
public:
    CVector m_vecPos;            // Position of the entity which buoyancy is being calculated
    CMatrix m_EntityMatrix;      // Matrix of the entity which buoyancy is being calculated
    uint32  pad;
    CVector m_vecInitialZPos;    // Holds some info about current entity, only ever used to retrieve its Z coordinate, which is already stored in m_vecPos field
    float   m_fWaterLevel;       // Z coordinate of water at entity position
    float   m_fUnkn2;            // 104
    float   m_fBuoyancy;         // 108
    CVector m_vecBoundingMax;    // Max bounding of the entity, doesn't neccesarily match its collision as it's modified a bit
    CVector m_vecBoundingMin;    // Min bounding of the entity, doesn't neccesarily match its collision as it's modified a bit
    float   m_fNumCheckedPoints; // How many points have been checked to calculate the buoyancy force, 9 points are checked at most for entity, used to keep track of incremental
                                 // average calculation
    uint32  field_8C;
    uint32  field_90;
    uint32  field_94;
    bool    m_bInWater;          // Is entity in water?
    uint8   field_99;
    uint8   field_9A;
    uint8   field_9B;
    CVector m_vecCenterOffset;           // Offset from min bounding to the center
    CVector m_vecNormalizedCenterOffset; // Same as m_vecCenterOffset, but scaled by longest component so it's 1.0F in the longest direction
    uint32  field_B4;
    bool    m_bFlipUnknVector;           // Should the currently calculated move force be inverted? (multiplied by -1.0F in the calculations)
    uint8   field_B9;
    bool    m_bProcessingBoat;           // Are we currently checking buoyancy of a boat?
    uint8   field_BB;                    // 187
    float   m_fEntityWaterImmersion;     // How much of the entity is immersed in water, [0:1] where 0 means entity is out of water, and 1 means that entity is completely submerged in
                                         // water
    CVector m_vecTurnPoint;              // Calculated buoyancy move force
    uint32  field_CC;                    // 204

    static float& fPointVolMultiplier;
    static CBuoyancyCalcStruct& calcStruct;
    static float(*afBoatVolumeDistributionSpeed)[3];     // 3x3 array of buoyancy modifiers for speedboats
    static float(*afBoatVolumeDistributionDinghy)[3];    // 3x3 array of buoyancy modifiers for small boats
    static float(*afBoatVolumeDistributionSail)[3];      // 3x3 array of buoyancy modifiers for sailboats
    static float(*afBoatVolumeDistribution)[3];          // 3x3 array of buoyancy modifiers for other boats
    static float(*afBoatVolumeDistributionCat)[3];       // Catamaran volume distribution, unused in game, as there is no matching vehicle

    static void InjectHooks();
    bool ProcessBuoyancy(CPhysical* pEntity, float fBuoyancy, CVector* pVecTurnSpeed, CVector* pBuoyancy);
    bool ProcessBuoyancyBoat(CVehicle* pVehicle, float fBuoyancy, CVector* vecBuoyancyTurnPoint, CVector* vecBuoyancyForce, bool bUnderwater);
    bool CalcBuoyancyForce(CPhysical* pEntity, CVector* pVecTurnSpeed, CVector* pBuoyancy);
    void PreCalcSetup(CPhysical* pEntity, float fBuoyancy);
    void AddSplashParticles(CPhysical* pEntity, CVector vecFrom, CVector vecTo, CVector vecSplashDir, uint8 bReduceParticleSize);
    void SimpleCalcBuoyancy(CPhysical* pEntity);
    float SimpleSumBuoyancyData(CVector* vecPointRelativeToSurface, eBuoyancyPointState ePointState);
    void FindWaterLevel(CVector const& vecInitialZPos, CVector* outVecOffset, eBuoyancyPointState* outInWaterState);
    void FindWaterLevelNorm(CVector const& vecInitialZPos, CVector* outVecOffset, eBuoyancyPointState* outInWaterState, CVector* outVecNormal);
};

VALIDATE_SIZE(cBuoyancy, 0xD0);

extern cBuoyancy& mod_Buoyancy;
