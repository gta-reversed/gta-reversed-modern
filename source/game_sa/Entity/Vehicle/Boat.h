/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vehicle.h"
#include "Door.h"
#include "tBoatHandlingData.h"

enum eBoatNodes {
    BOAT_NODE_NONE = 0,
    BOAT_MOVING = 1,
    BOAT_WINDSCREEN = 2,
    BOAT_RUDDER = 3,
    BOAT_FLAP_LEFT = 4,
    BOAT_FLAP_RIGHT = 5,
    BOAT_REARFLAP_LEFT = 6,
    BOAT_REARFLAP_RIGHT = 7,
    BOAT_STATIC_PROP = 8,
    BOAT_MOVING_PROP = 9,
    BOAT_STATIC_PROP_2 = 10,
    BOAT_MOVING_PROP_2 = 11,
    BOAT_NUM_NODES
};

class CBoat : public CVehicle {
public:
    CBoat(int32 modelIndex, eVehicleCreatedBy createdBy);
    ~CBoat() override;
public:
    float m_fMovingHiRotation; // works as counter also
    float m_fPropSpeed;        // propeller speed
    float m_fPropRotation;     // propeller rotation (radians)
    struct {
        uint8 bOnWater : 1; // is placed on water
        uint8 bMovingOnWater : 1;
        uint8 bAnchored : 1; // is anchored
    } m_nBoatFlags;
    char               _pad5AD[3];
    RwFrame*           m_aBoatNodes[BOAT_NUM_NODES];
    CDoor              m_boatFlap; // for marquis model
    tBoatHandlingData* m_pBoatHandling;
    float              m_fAnchoredAngle; // radians, initialised with -9999.99
    uint32             m_nAttackPlayerTime;
    int32              field_604;       // initialised with 0, not used
    float              m_fBurningTimer; // starts when vehicle health is lower than 250.0, boat blows up when it hits 5000.0
    CEntity*           m_pWhoDestroyedMe;
    CVector            m_vecBoatMoveForce; // m_vecBoatMoveForce = m_vecMoveForce + m_vecFrictionMoveForce
    CVector            m_vecBoatTurnForce; // m_vecBoatTurnForce = m_vecTurnForce + m_vecFrictionTurnForce
    FxSystem_c*        m_apPropSplashFx[2];
    CVector            m_vecWaterDamping; // { 0.0f, 0.0f, DampingPower }
    char               field_63C;         // initialised with 0, maybe boat handling type (@CBoat::DebugCode), possibly a leftover
    uint8              m_nPadNumber;      // 0 - 3
    char               _pad63E[2];
    float              m_fLastWaterImmersionDepth; // initialised with 7.0f, 0.0f - not in water
    int16              m_nNumWaterTrailPoints;
    char               _pad646[2];
    CVector2D          m_avecWakePoints[32];
    float              m_afWakePointLifeTime[32];
    uint8              m_anWakePointIntensity[32]; // m_anWakePointIntensity[i] = boat->m_vecMoveForce.Magnitude() * 100.0f;

    static constexpr int32 NUM_WAKE_GEN_BOATS = 4;
    static CBoat*(&apFrameWakeGeneratingBoats)[NUM_WAKE_GEN_BOATS]; // static CBoat *apFrameWakeGeneratingBoats[4]
    static float& MAX_WAKE_LENGTH; // 50.0
    static float& MIN_WAKE_INTERVAL; // 2.0
    static float& WAKE_LIFETIME; // 150.0
    static float& fShapeLength; // 0.4
    static float& fShapeTime; // 0.05
    static float& fRangeMult; // 0.6

    static int16* waUnknArr;  // static CBoat::waUnknArr[4]
    static int16* waUnknArr2; // static CBoat::waUnknArr2[4]

    static const constexpr uint32 uiNumVertices = 4;
    static RxObjSpace3DVertex* aRenderVertices;

    static const constexpr uint32 uiNumIndices = 6;
    static RxVertexIndex* auRenderIndices;

public:
    static void InjectHooks();

    // Virtual methods
    void SetModelIndex(uint32 index) override;
    void ProcessControl() override;
    void Teleport(CVector destination, bool resetRotation) override;
    void PreRender() override;
    void Render() override;
    void ProcessControlInputs(uint8 playerNum) override;
    void GetComponentWorldPosition(int32 componentId, CVector& outPos) override;
    void ProcessOpenDoor(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 arg3, float arg4) override;
    void BlowUpCar(CEntity* damager, uint8 bHideExplosion) override;

    inline void SetupModelNodes(); // fill m_aBoatNodes array
    void DebugCode();
    void PrintThrustAndRudderInfo(); // uses debug printing
    void ModifyHandlingValue(const bool& bIncrement);
    void PruneWakeTrail();
    void AddWakePoint(CVector posn);

    static bool IsSectorAffectedByWake(CVector2D vecPos, float fOffset, CBoat** ppBoats);
    static float IsVertexAffectedByWake(CVector vecPos, CBoat* pBoat, int16 wIndex, bool bUnkn);
    static void CheckForSkippingCalculations();
    static void FillBoatList();

private:
    void SetModelIndex_Reversed(uint32 index);
    void ProcessControl_Reversed();
    void Teleport_Reversed(CVector destination, bool resetRotation);
    void PreRender_Reversed();
    void inline ProcessBoatNodeRendering(eBoatNodes eNode, float fRotation, RwUInt8 ucAlpha);
    void Render_Reversed();
    void ProcessControlInputs_Reversed(uint8 ucPadNum);
    void GetComponentWorldPosition_Reversed(int32 componentId, CVector& outPos);
    void ProcessOpenDoor_Reversed(CPed* ped, uint32 doorComponentId, uint32 arg2, uint32 arg3, float arg4);
    void BlowUpCar_Reversed(CEntity* damager, uint8 bHideExplosion);
};

VALIDATE_SIZE(CBoat, 0x7E8);

RwObject* GetBoatAtomicObjectCB(RwObject* object, void* data);
