/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVehicle.h"
#include "CDoor.h"
#include "CBouncingPanel.h"
#include "CDamageManager.h"
#include "CColPoint.h"
#include "eSurfaceType.h"

class CObject;

enum eCarNodes {
    CAR_NODE_NONE = 0,
    CAR_CHASSIS = 1,
    CAR_WHEEL_RF = 2,
    CAR_WHEEL_RM = 3,
    CAR_WHEEL_RB = 4,
    CAR_WHEEL_LF = 5,
    CAR_WHEEL_LM = 6,
    CAR_WHEEL_LB = 7,
    CAR_DOOR_RF = 8,
    CAR_DOOR_RR = 9,
    CAR_DOOR_LF = 10,
    CAR_DOOR_LR = 11,
    CAR_BUMP_FRONT = 12,
    CAR_BUMP_REAR = 13,
    CAR_WING_RF = 14,
    CAR_WING_LF = 15,
    CAR_BONNET = 16,
    CAR_BOOT = 17,
    CAR_WINDSCREEN = 18,
    CAR_EXHAUST = 19,
    CAR_MISC_A = 20,
    CAR_MISC_B = 21,
    CAR_MISC_C = 22,
    CAR_MISC_D = 23,
    CAR_MISC_E = 24,
    CAR_NUM_NODES
};

enum eCarWheel {
    CARWHEEL_FRONT_LEFT = 0,
    CARWHEEL_REAR_LEFT = 1,
    CARWHEEL_FRONT_RIGHT = 2,
    CARWHEEL_REAR_RIGHT = 3
};

enum eExtraHandlingFlags : uint32_t
{
    EXTRA_HANDLING_PERFECT = 0x1,
    EXTRA_HANDLING_NITROS = 0x2,
    EXTRA_HANDLING_WHEELS_TOUCHING_SAND = 0x8,
    EXTRA_HANDLING_TAXI_BOOST = 0x10
};

class FxSystem_c;

class CAutomobile : public CVehicle {
protected:
    CAutomobile(plugin::dummy_func_t) : CVehicle(plugin::dummy) {}
public:
    CDamageManager m_damageManager;
    CDoor m_doors[6];
    RwFrame *m_aCarNodes[CAR_NUM_NODES];
    CBouncingPanel m_panels[3];
    CDoor m_swingingChassis;
    CColPoint m_wheelColPoint[4];
    float m_fWheelsSuspensionCompression[4]; // [0-1] with 0 being suspension fully compressed, and 1 being completely relaxed
    float m_fWheelsSuspensionCompressionPrev[4];
    float m_aWheelTimer[4];
    float field_804;
    float m_intertiaValue1;
    float m_intertiaValue2;
    int m_wheelSkidmarkType[4];
    bool m_wheelSkidmarkBloodState[4];
    bool m_wheelSkidmarkMuddy[4];
    float m_wheelRotation[4];
    float m_wheelPosition[4];
    union {
        float m_wheelSpeed[4];
        struct {
            float m_fHeliWheelSpeed1;
            float m_fHeliRotorSpeed;
            float m_fHeliWheelSpeed3;
            float m_fHeliWheelSpeed4;
        };
    };
    float m_wheelRotationUnused[4]; // Passed to CVehicle::ProcessWheel as last 3rd parameter, but it's not used
    union {
        struct {
            unsigned char bTaxiLightOn : 1;
            unsigned char ucNPCFlagPad2 : 1;
            unsigned char bIgnoreWater : 1;
            unsigned char bDontDamageOnRoof : 1;
            unsigned char bTakePanelDamage : 1;
            unsigned char ucTaxiUnkn6 : 1;
            unsigned char bLostTraction : 1;
            unsigned char bSoftSuspension : 1;
        } npcFlags;
        unsigned char ucNPCVehicleFlags;
    };
    char field_869;
    short m_doingBurnout;
    uint16_t m_wMiscComponentAngle;
    uint16_t m_wMiscComponentAnglePrev;
    uint32_t m_dwBusDoorTimerEnd;
    int m_dwBusDoorTimerStart;
    float m_aSuspensionSpringLength[4];
    float m_aSuspensionLineLength[4];
    float m_fFrontHeightAboveRoad;
    float m_fRearHeightAboveRoad;
    float m_fCarTraction;
    float m_fTireTemperature;
    float m_aircraftGoToHeading;
    float m_fRotationBalance; // used in CHeli::TestSniperCollision
    float m_fMoveDirection;
    int field_8B4[6];
    int field_8C8[6];
    int m_dwBurnTimer;
    CPhysical *m_pWheelCollisionEntity[4];
    CVector m_vWheelCollisionPos[4];
    char field_924;
    char field_925;
    char field_926;
    char field_927;
    char field_928;
    char field_929;
    char field_92A;
    char field_92B;
    char field_92C;
    char field_92D;
    char field_92E;
    char field_92F;
    char field_930;
    char field_931;
    char field_932;
    char field_933;
    char field_934;
    char field_935;
    char field_936;
    char field_937;
    char field_938;
    char field_939;
    char field_93A;
    char field_93B;
    char field_93C;
    char field_93D;
    char field_93E;
    char field_93F;
    int field_940;
    int field_944;
    float m_fDoomVerticalRotation;
    float m_fDoomHorizontalRotation;
    float m_fForcedOrientation;
    float m_fUpDownLightAngle[2];
    uint8_t m_nNumContactWheels;
    uint8_t m_nWheelsOnGround;
    uint8_t m_wheelsOnGrounPrev;
    char field_963;
    float field_964;
    tWheelState m_aWheelState[4];
    FxSystem_c* m_exhaustNitroFxSystem[2];
    uint8_t m_harvesterParticleCounter;
    char field_981;
    short field_982;
    float field_984;

    // variables
    static constexpr float PACKER_COL_ANGLE_MULT = -0.0001f;
    static constexpr float FORKLIFT_COL_ANGLE_MULT = 0.0006f;
    static constexpr float DOZER_COL_ANGLE_MULT = 0.0002f;
    static constexpr float ROLL_ONTO_WHEELS_FORCE = 0.0025f;
    static bool &m_sAllTaxiLights;
    static CVector &vecHunterGunPos; // { 0.0f, 4.8f, -1.3f }
    static CMatrix *matW2B;

    //vtable
    void ProcessControl() override;
    CVector AddMovingCollisionSpeed(CVector& point) override;

    virtual bool ProcessAI(unsigned int& extraHandlingFlags);
    virtual void ResetSuspension();
    virtual void ProcessFlyingCarStuff();
    virtual void DoHoverSuspensionRatios();
    virtual void ProcessSuspension();

private:
    void ProcessControl_Reversed();
    CVector AddMovingCollisionSpeed_Reversed(CVector& point);
    bool ProcessAI_Reversed(unsigned int& extraHandlingFlags);
    void ResetSuspension_Reversed();
    void ProcessFlyingCarStuff_Reversed();
    void DoHoverSuspensionRatios_Reversed();
    void ProcessSuspension_Reversed();
public:

    static void InjectHooks();
    //funcs
    CAutomobile(int modelIndex, unsigned char createdBy, bool setupSuspensionLines);

    void SetEngineState(bool state)
    {
        if (vehicleFlags.bEngineBroken)
            vehicleFlags.bEngineOn = false;
        else
            vehicleFlags.bEngineOn = state;
    }

    inline bool IsAnyWheelMakingContactWithGround() {
        return m_fWheelsSuspensionCompression[0] != 1.0F
            || m_fWheelsSuspensionCompression[1] != 1.0F
            || m_fWheelsSuspensionCompression[2] != 1.0F
            || m_fWheelsSuspensionCompression[3] != 1.0F;
    };

    inline bool IsAnyWheelNotMakingContactWithGround() {
        return m_fWheelsSuspensionCompression[0] == 1.0F
            || m_fWheelsSuspensionCompression[1] == 1.0F
            || m_fWheelsSuspensionCompression[2] == 1.0F
            || m_fWheelsSuspensionCompression[3] == 1.0F;
    };

    inline bool IsAnyWheelTouchingSand() {
        for (int32_t i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] < 1.0f) {
                if (g_surfaceInfos->GetAdhesionGroup(m_wheelColPoint[i].m_nSurfaceTypeB) == ADHESION_GROUP_SAND)
                    return true;
            }
        }
        return false;
    }

    inline bool IsAnyWheelTouchingRailTrack() {
        for (int32_t i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] < 1.0f) {
                if (m_wheelColPoint[i].m_nSurfaceTypeB == SURFACE_RAILTRACK)
                    return true;
            }
        }
        return false;
    }

    inline bool IsAnyWheelTouchingShallowWaterGround() {
        for (int32_t i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] < 1.0f && m_wheelColPoint[i].m_nSurfaceTypeB == SURFACE_WATER_SHALLOW)
                return true;
        }
        return false;
    }

    inline bool IsAnyFrontAndRearWheelTouchingGround() {
        if (m_fWheelsSuspensionCompression[CARWHEEL_FRONT_LEFT] < 1.0f  || m_fWheelsSuspensionCompression[CARWHEEL_FRONT_RIGHT] < 1.0f) {
            if (m_fWheelsSuspensionCompression[CARWHEEL_REAR_LEFT] < 1.0f || m_fWheelsSuspensionCompression[CARWHEEL_REAR_RIGHT] < 1.0f)
                return true;
        }
        return false;
    }

    // check the previous compression state using m_fWheelsSuspensionCompressionPrev
    inline bool DidAnyWheelTouchShallowWaterGroundPrev() {
        for (int32_t i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompressionPrev[i] < 1.0f && m_wheelColPoint[i].m_nSurfaceTypeB == SURFACE_WATER_SHALLOW)
                return true;
        }
        return false;
    }
    inline bool DidAnyWheelTouchGroundPrev() {
        for (int32_t i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompressionPrev[i] < 1.0f)
                return true;
        }
        return false;
    }

    bool IsRealHeli(void) { return !!(m_pHandlingData->m_nModelFlags & VEHICLE_HANDLING_MODEL_IS_HELI); }

    // Find and save components ptrs (RwFrame) to m_modelNodes array
    void SetupModelNodes();
    // Process vehicle hydraulics
    void HydraulicControl();
    // Sets the angle of a vehicles extra. Called at 08A4 opcode (CONTROL_MOVABLE_VEHICLE_PART)
    bool UpdateMovingCollision(float angle);
    // Called at 098D opcode (GET_CAR_MOVING_COMPONENT_OFFSET)
    float GetMovingCollisionOffset();
    // Makes the helicopter fly to the specified location, keeping a specific Z height/altitude. This must be called for helis only.
    void TellHeliToGoToCoors(float x, float y, float z, float altitudeMin, float altitudeMax);
    // Force orientation for heli to specified angle (radians)
    void SetHeliOrientation(float angle);
    // Cancel orientation forcing (m_fForcedOrientation = -1.0f)
    void ClearHeliOrientation();
    // Makes the plane fly to the specified location, keeping a specific Z height/altitude.
    void TellPlaneToGoToCoors(float x, float y, float z, float altitudeMin, float altitudeMax);
    // Empty function
    void HideAllComps();
    // Empty function
    void ShowAllComps();
    // Set random damage to vehicle. Called when generating a vehicle @CCarCtrl::GenerateOneRandomCar
    void SetRandomDamage(bool arg0);
    // Make a vehicle fully damaged
    void SetTotalDamage(bool arg0);
    // if(m_nHornCounter) m_nHornCounter--;
    void ReduceHornCounter();
    // Apply custom car plate texture to vehicle
    void CustomCarPlate_BeforeRenderingStart(CVehicleModelInfo* model);
    // Reset car plate texture after rendering
    void CustomCarPlate_AfterRenderingStop(CVehicleModelInfo* model);
    // Check if vehicle is in air
    bool GetAllWheelsOffGround();
    // Some debug function
    void DebugCode();
    // Repair vehicle's tyre
    void FixTyre(eWheelStatus wheel);
    // Repair vehicle's door. "nodeIndex" is an index of component in m_modelNodes array
    void FixDoor(int nodeIndex, eDoors door);
    // Repair vehicle's panel. "nodeIndex" is an index of component in m_modelNodes array
    void FixPanel(int nodeIndex, ePanels panel);
    // Enable/disable taxi light for taxi
    void SetTaxiLight(bool enable);
    // Enable taxi light for all taxis (CAutomobile::m_sAllTaxiLights = true;)
    static void SetAllTaxiLights(bool arg0);
    // Play horn for NPC vehicle (called @CAutomobile::ProcessAI)
    void PlayHornIfNecessary();
    void SetBusDoorTimer(unsigned int time, unsigned char arg1);
    void ProcessAutoBusDoors();
    // Make player vehicle jumps when pressing horn
    void BoostJumpControl();
    // Creates/updates nitro particle
    void DoNitroEffect(float power);
    // Remove nitro particle
    void StopNitroEffect();
    void NitrousControl(signed char);
    void TowTruckControl();
    // Empty function
    CPed* KnockPedOutCar(eWeaponType arg0, unsigned short arg1, CPed* arg2);
    void PopBootUsingPhysics();
    // Close all doors
    void CloseAllDoors();
    void DoSoftGroundResistance(unsigned int& extraHandlingFlags);
    void ProcessCarWheelPair(int leftWheel, int rightWheel, float steerAngle, CVector* contactSpeeds, CVector* contactPoints, float traction, float acceleration, float brake, bool bFront);
    float GetCarRoll();
    float GetCarPitch();
    bool IsInAir();
    // Create colliding particles
    void dmgDrawCarCollidingParticles(CVector const&, float force, eWeaponType weapon);
    void ProcessCarOnFireAndExplode(bool bExplodeImmediately);
    CObject* SpawnFlyingComponent(int nodeIndex, unsigned int collisionType);
    void ProcessBuoyancy();
    void inline ProcessPedInVehicleBuoyancy(CPed* pPed, bool bIsDriver);
    // Process combine
    void ProcessHarvester();
    void ProcessSwingingDoor(int nodeIndex, eDoors door);
    // Returns spawned flying component?
    CObject* RemoveBonnetInPedCollision();
    void UpdateWheelMatrix(int nodeIndex, int flags);
    void PopDoor(int nodeIndex, eDoors door, bool showVisualEffect);
    void PopPanel(int nodeIndex, ePanels panel, bool showVisualEffect);
    void ScanForCrimes();
    void TankControl();
    // Makes a vehicles acts like a tank on a road - blows up collided vehicles. Must be called in a loop
    void BlowUpCarsInPath();
    void PlaceOnRoadProperly();
    void PopBoot();
    void CloseBoot();
    void DoHeliDustEffect(float arg0, float arg1);
    void SetBumperDamage(ePanels panel, bool withoutVisualEffect);
    void SetPanelDamage(ePanels panel, bool createWindowGlass);
    void SetDoorDamage(eDoors door, bool withoutVisualEffect);
    bool RcbanditCheck1CarWheels(CPtrList& ptrlist);
    bool RcbanditCheckHitWheels();
    void FireTruckControl(CFire* fire);
    bool HasCarStoppedBecauseOfLight();
};

VALIDATE_SIZE(CAutomobile, 0x988);

extern CColPoint *aAutomobileColPoints;

// Disable matfx (material effects) for material (callback), "data" parameter is unused
RpMaterial *DisableMatFx(RpMaterial* material, void* data);
// callback
RwObject* GetCurrentAtomicObjectCB(RwObject* object, void* data);
