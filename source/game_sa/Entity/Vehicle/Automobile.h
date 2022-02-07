/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vehicle.h"
#include "Door.h"
#include "BouncingPanel.h"
#include "DamageManager.h"
#include "ColPoint.h"

#include "eSurfaceType.h"
#include "eCarWheel.h"
#include "eCarNodes.h"

class CVehicleModelInfo;

using eWheels = eCarWheel; // todo: maybe wrong, "eWheels" is original enum.

class CObject;

enum eExtraHandlingFlags : uint32 {
    EXTRA_HANDLING_PERFECT              = 0x1,
    EXTRA_HANDLING_NITROS               = 0x2,
    EXTRA_HANDLING_WHEELS_TOUCHING_SAND = 0x8,
    EXTRA_HANDLING_TAXI_BOOST           = 0x10
};

class FxSystem_c;

class CAutomobile : public CVehicle {
public:
    CDamageManager m_damageManager;
    CDoor          m_doors[6];
    RwFrame*       m_aCarNodes[CAR_NUM_NODES];
    CBouncingPanel m_panels[3];
    CDoor          m_swingingChassis;
    CColPoint      m_wheelColPoint[4];
    float          m_fWheelsSuspensionCompression[4];     // 0x7D4 - [0-1] with 0 being suspension fully compressed, and 1 being completely relaxed
    float          m_fWheelsSuspensionCompressionPrev[4]; // 0x7E4
    float          m_aWheelTimer[4];
    float          field_804;
    float          m_intertiaValue1;
    float          m_intertiaValue2;
    int32          m_wheelSkidmarkType[4];      // 0x810
    bool           m_wheelSkidmarkBloodState[4];// 0x820
    bool           m_wheelSkidmarkMuddy[4];     // 0x824
    float          m_wheelRotation[4];          // 0x828
    float          m_wheelPosition[4];          // 0x838
    union {                                     // 0x848
        float m_wheelSpeed[4];                  
        struct {
            float m_fHeliWheelSpeed1;
            float m_fHeliRotorSpeed;
            float m_fHeliWheelSpeed3;
            float m_fHeliWheelSpeed4;
        };
    };
    float m_wheelRotationUnused[4];             // 0x858 - Passed to CVehicle::ProcessWheel as last 3rd parameter, but it's not used
    union {
        struct {
            uint8 bTaxiLightOn : 1;
            uint8 ucNPCFlagPad2 : 1;
            uint8 bIgnoreWater : 1;
            uint8 bDontDamageOnRoof : 1;
            uint8 bTakePanelDamage : 1;
            uint8 ucTaxiUnkn6 : 1;
            uint8 bLostTraction : 1;
            uint8 bSoftSuspension : 1;
        } npcFlags;
        uint8 ucNPCVehicleFlags;
    };
    char        field_869;                      // 0x869
    int16       m_doingBurnout;                 // 0x86A
    uint16      m_wMiscComponentAngle;          // 0x86C
    uint16      m_wMiscComponentAnglePrev;      // 0x86E
    uint32      m_dwBusDoorTimerEnd;            // 0x870
    int32       m_dwBusDoorTimerStart;          // 0x874
    float       m_aSuspensionSpringLength[4];   // 0x878
    float       m_aSuspensionLineLength[4];     // 0x888
    float       m_fFrontHeightAboveRoad;
    float       m_fRearHeightAboveRoad;
    float       m_fCarTraction;
    float       m_fTireTemperature;
    float       m_aircraftGoToHeading;
    float       m_fRotationBalance; // used in CHeli::TestSniperCollision
    float       m_fMoveDirection;
    int32       field_8B4[6];
    int32       field_8C8[6];
    int32       m_dwBurnTimer;
    CPhysical*  m_pWheelCollisionEntity[4];
    CVector     m_vWheelCollisionPos[4];
    char        field_924;
    char        field_925;
    char        field_926;
    char        field_927;
    char        field_928;
    char        field_929;
    char        field_92A;
    char        field_92B;
    char        field_92C;
    char        field_92D;
    char        field_92E;
    char        field_92F;
    char        field_930;
    char        field_931;
    char        field_932;
    char        field_933;
    char        field_934;
    char        field_935;
    char        field_936;
    char        field_937;
    char        field_938;
    char        field_939;
    char        field_93A;
    char        field_93B;
    char        field_93C;
    char        field_93D;
    char        field_93E;
    char        field_93F;
    int32       field_940;
    int32       field_944;
    float       m_fDoomVerticalRotation;
    float       m_fDoomHorizontalRotation;
    float       m_fForcedOrientation;
    float       m_fUpDownLightAngle[2];
    uint8       m_nNumContactWheels;
    uint8       m_nWheelsOnGround;
    uint8       m_wheelsOnGrounPrev;
    char        field_963;
    float       field_964;
    tWheelState m_aWheelState[4];
    FxSystem_c* m_exhaustNitroFxSystem[2];
    uint8       m_harvesterParticleCounter;
    char        field_981;
    int16       field_982;
    float       field_984;

    // variables
    static constexpr float PACKER_COL_ANGLE_MULT = -0.0001f;
    static constexpr float FORKLIFT_COL_ANGLE_MULT = 0.0006f;
    static constexpr float DOZER_COL_ANGLE_MULT = 0.0002f;
    static constexpr float ROLL_ONTO_WHEELS_FORCE = 0.0025f;
    static bool&           m_sAllTaxiLights;
    static CVector&        vecHunterGunPos; // { 0.0f, 4.8f, -1.3f }
    static CMatrix*        matW2B;

public:
    CAutomobile(plugin::dummy_func_t) : CVehicle(plugin::dummy) {}
    CAutomobile(int32 modelIndex, eVehicleCreatedBy createdBy, bool setupSuspensionLines);

    // CPhysical
    void ProcessControl() override;

    // CVehicle
    void ProcessControlCollisionCheck(bool applySpeed) override;
    void ProcessControlInputs(uint8 playerNum) override;
    void GetComponentWorldPosition(int32 componentId, CVector& outPos) override;
    bool IsComponentPresent(int32 componentId) override;
    void OpenDoor(CPed* ped, int32 componentId, eDoors door, float doorOpenRatio, bool playSound) override;
    float GetDooorAngleOpenRatio(eDoors door) override;
    float GetDooorAngleOpenRatio(uint32 door) override;
    bool IsDoorReady(eDoors door) override;
    bool IsDoorReady(uint32 door) override;
    bool IsDoorFullyOpen(eDoors door) override;
    bool IsDoorFullyOpen(uint32 door) override;
    bool IsDoorClosed(eDoors door) override;
    bool IsDoorClosed(uint32 door) override;
    bool IsDoorMissing(eDoors door) override;
    bool IsDoorMissing(uint32 door) override;
    bool IsOpenTopCar() override;
    void RemoveRefsToVehicle(CEntity* entity) override;
    void BlowUpCar(CEntity* damager, uint8 bHideExplosion) override;
    void BlowUpCarCutSceneNoExtras(bool bNoCamShake, bool bNoSpawnFlyingComps, bool bDetachWheels, bool bExplosionSound) override;
    bool SetUpWheelColModel(CColModel* wheelCol) override;
    bool BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) override;
    bool IsRoomForPedToLeaveCar(uint32 arg0, CVector* arg1) override;
    void SetupSuspensionLines() override;
    CVector AddMovingCollisionSpeed(CVector& point) override;
    void Fix() override;
    void SetupDamageAfterLoad() override;
    void DoBurstAndSoftGroundRatios() override;
    float GetHeightAboveRoad() override;
    void PlayCarHorn() override;
    int32 GetNumContactWheels() override;
    void VehicleDamage(float damageIntensity, eVehicleCollisionComponent collisionComponent, CEntity* damager, CVector* vecCollisionCoors, CVector* vecCollisionDirection, eWeaponType weapon) override;
    bool GetTowHitchPos(CVector& outPos, bool bCheckModelInfo, CVehicle* veh) override;
    bool GetTowBarPos(CVector& outPos, bool bCheckModelInfo, CVehicle* veh) override;
    bool SetTowLink(CVehicle* tractor, bool setMyPosToTowBar) override;
    bool BreakTowLink() override;
    float FindWheelWidth(bool bRear) override;
    bool Save() override;
    bool Load() override;

    virtual bool ProcessAI(uint32& extraHandlingFlags);
    virtual void ResetSuspension();
    virtual void ProcessFlyingCarStuff();
    virtual void DoHoverSuspensionRatios();
    virtual void ProcessSuspension();

    void PreRender() override { plugin::CallMethod<0x6AAB50, CAutomobile*>(this); }

    void SetEngineState(bool state)
    {
        if (vehicleFlags.bEngineBroken)
            vehicleFlags.bEngineOn = false;
        else
            vehicleFlags.bEngineOn = state;
    }

    bool IsAnyWheelMakingContactWithGround() {
        return m_fWheelsSuspensionCompression[0] != 1.0F
            || m_fWheelsSuspensionCompression[1] != 1.0F
            || m_fWheelsSuspensionCompression[2] != 1.0F
            || m_fWheelsSuspensionCompression[3] != 1.0F;
    };

    bool IsAnyWheelNotMakingContactWithGround() {
        return m_fWheelsSuspensionCompression[0] == 1.0F
            || m_fWheelsSuspensionCompression[1] == 1.0F
            || m_fWheelsSuspensionCompression[2] == 1.0F
            || m_fWheelsSuspensionCompression[3] == 1.0F;
    };

    bool IsAnyWheelTouchingSand() {
        for (int32 i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] < 1.0f) {
                if (g_surfaceInfos->GetAdhesionGroup(m_wheelColPoint[i].m_nSurfaceTypeB) == ADHESION_GROUP_SAND)
                    return true;
            }
        }
        return false;
    }

    bool IsAnyWheelTouchingRailTrack() {
        for (int32 i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] < 1.0f) {
                if (m_wheelColPoint[i].m_nSurfaceTypeB == SURFACE_RAILTRACK)
                    return true;
            }
        }
        return false;
    }

    bool IsAnyWheelTouchingShallowWaterGround() {
        for (int32 i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] < 1.0f && m_wheelColPoint[i].m_nSurfaceTypeB == SURFACE_WATER_SHALLOW)
                return true;
        }
        return false;
    }

    bool IsAnyFrontAndRearWheelTouchingGround() {
        if (m_fWheelsSuspensionCompression[CARWHEEL_FRONT_LEFT] < 1.0f  || m_fWheelsSuspensionCompression[CARWHEEL_FRONT_RIGHT] < 1.0f) {
            if (m_fWheelsSuspensionCompression[CARWHEEL_REAR_LEFT] < 1.0f || m_fWheelsSuspensionCompression[CARWHEEL_REAR_RIGHT] < 1.0f)
                return true;
        }
        return false;
    }

    [[nodiscard]] bool AreFrontWheelsNotTouchingGround() const { // NOTSA
        return m_fWheelsSuspensionCompression[eCarWheel::CARWHEEL_FRONT_LEFT] >= 1.0f && m_fWheelsSuspensionCompression[eCarWheel::CARWHEEL_FRONT_RIGHT];
    }

    [[nodiscard]] bool AreRearWheelsNotTouchingGround() const { // NOTSA
        return m_fWheelsSuspensionCompression[eCarWheel::CARWHEEL_REAR_LEFT] >= 1.0f && m_fWheelsSuspensionCompression[eCarWheel::CARWHEEL_REAR_RIGHT];
    }

    // check the previous compression state using m_fWheelsSuspensionCompressionPrev
    bool DidAnyWheelTouchShallowWaterGroundPrev() {
        for (int32 i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompressionPrev[i] < 1.0f && m_wheelColPoint[i].m_nSurfaceTypeB == SURFACE_WATER_SHALLOW)
                return true;
        }
        return false;
    }
    bool DidAnyWheelTouchGroundPrev() {
        for (int32 i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompressionPrev[i] < 1.0f)
                return true;
        }
        return false;
    }

    bool IsRealHeli() { return !!(m_pHandlingData->m_nModelFlags & VEHICLE_HANDLING_MODEL_IS_HELI); }

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
    void FixTyre(eWheels wheel);
    // Repair vehicle's door. "nodeIndex" is an index of component in m_modelNodes array
    void FixDoor(int32 nodeIndex, eDoors door);
    // Repair vehicle's panel. "nodeIndex" is an index of component in m_modelNodes array
    void FixPanel(int32 nodeIndex, ePanels panel);
    // Enable/disable taxi light for taxi
    void SetTaxiLight(bool enable);
    // Enable taxi light for all taxis (CAutomobile::m_sAllTaxiLights = true;)
    static void SetAllTaxiLights(bool enable);
    // Play horn for NPC vehicle (called @CAutomobile::ProcessAI)
    void PlayHornIfNecessary();
    void SetBusDoorTimer(uint32 time, uint8 arg1);
    void ProcessAutoBusDoors();
    // Make player vehicle jumps when pressing horn
    void BoostJumpControl();
    // Creates/updates nitro particle
    void DoNitroEffect(float power);
    // Remove nitro particle
    void StopNitroEffect();
    void NitrousControl(int8);
    void TowTruckControl();
    // Empty function
    CPed* KnockPedOutCar(eWeaponType arg0, uint16 arg1, CPed* arg2);
    void PopBootUsingPhysics();
    // Close all doors
    void CloseAllDoors();
    void DoSoftGroundResistance(uint32& extraHandlingFlags);
    void ProcessCarWheelPair(eCarWheel leftWheel, eCarWheel rightWheel, float steerAngle, CVector* contactSpeeds, CVector* contactPoints, float traction, float acceleration, float brake, bool bFront);
    float GetCarRoll();
    float GetCarPitch();
    bool IsInAir();
    // Create colliding particles
    void dmgDrawCarCollidingParticles(const CVector&, float force, eWeaponType weapon);
    void ProcessCarOnFireAndExplode(bool bExplodeImmediately);
    CObject* SpawnFlyingComponent(int32 nodeIndex, uint32 collisionType);
    void ProcessBuoyancy();
    void inline ProcessPedInVehicleBuoyancy(CPed* ped, bool bIsDriver);
    // Process combine
    void ProcessHarvester();
    void ProcessSwingingDoor(int32 nodeIndex, eDoors door);
    // Returns spawned flying component?
    CObject* RemoveBonnetInPedCollision();
    void UpdateWheelMatrix(int32 nodeIndex, int32 flags);
    void PopDoor(int32 nodeIndex, eDoors door, bool showVisualEffect);
    void PopPanel(int32 nodeIndex, ePanels panel, bool showVisualEffect);
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
    bool RcbanditCheck1CarWheels(CPtrList& ptrList);
    bool RcbanditCheckHitWheels();
    void FireTruckControl(CFire* fire);
    bool HasCarStoppedBecauseOfLight();
    CDoor& GetDoor(eDoors door) { return m_doors[(unsigned)door]; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    bool ProcessAI_Reversed(uint32& extraHandlingFlags) { return CAutomobile::ProcessAI(extraHandlingFlags); }
    void ResetSuspension_Reversed() { return CAutomobile::ResetSuspension(); }
    void ProcessFlyingCarStuff_Reversed() { return CAutomobile::ProcessFlyingCarStuff(); }
    void DoHoverSuspensionRatios_Reversed() { return CAutomobile::DoHoverSuspensionRatios(); }
    void ProcessSuspension_Reversed() { return CAutomobile::ProcessSuspension(); }

    // CPhysical
    void ProcessControl_Reversed() { CAutomobile::ProcessControl(); }

    // CVehicle
    void ProcessControlCollisionCheck_Reversed(bool applySpeed) { CAutomobile::ProcessControlCollisionCheck(applySpeed); }
    void ProcessControlInputs_Reversed(uint8 playerNum) { CAutomobile::ProcessControlInputs(playerNum); }
    void GetComponentWorldPosition_Reversed(int32 componentId, CVector& outPos) { CAutomobile::GetComponentWorldPosition(componentId, outPos); }
    bool IsComponentPresent_Reversed(int32 componentId) { return CAutomobile::IsComponentPresent(componentId); }
    void OpenDoor_Reversed(CPed* ped, int32 componentId, eDoors door, float doorOpenRatio, bool playSound) { CAutomobile::OpenDoor(ped, componentId, door, doorOpenRatio, playSound); }
    float GetDooorAngleOpenRatio_Reversed(eDoors door) { return CAutomobile::GetDooorAngleOpenRatio(door); }
    float GetDooorAngleOpenRatio_Reversed(uint32 door) { return CAutomobile::GetDooorAngleOpenRatio(door); }
    bool IsDoorReady_Reversed(eDoors door) { return CAutomobile::IsDoorReady(door); }
    bool IsDoorReady_Reversed(uint32 door) { return CAutomobile::IsDoorReady(door); }
    bool IsDoorFullyOpen_Reversed(eDoors door) { return CAutomobile::IsDoorFullyOpen(door); }
    bool IsDoorFullyOpen_Reversed(uint32 door) { return CAutomobile::IsDoorFullyOpen(door); }
    bool IsDoorClosed_Reversed(eDoors door) { return CAutomobile::IsDoorClosed(door); }
    bool IsDoorClosed_Reversed(uint32 door) { return CAutomobile::IsDoorClosed(door); }
    bool IsDoorMissing_Reversed(eDoors door) { return CAutomobile::IsDoorMissing(door); }
    bool IsDoorMissing_Reversed(uint32 door) { return CAutomobile::IsDoorMissing(door); }
    bool IsOpenTopCar_Reversed() { return CAutomobile::IsOpenTopCar(); }
    void RemoveRefsToVehicle_Reversed(CEntity* entity) { CAutomobile::RemoveRefsToVehicle(entity); }
    void BlowUpCar_Reversed(CEntity* damager, uint8 bHideExplosion) { CAutomobile::BlowUpCar(damager, bHideExplosion); }
    void BlowUpCarCutSceneNoExtras_Reversed(bool bNoCamShake, bool bNoSpawnFlyingComps, bool bDetachWheels, bool bExplosionSound) { CAutomobile::BlowUpCarCutSceneNoExtras(bNoCamShake, bNoSpawnFlyingComps, bDetachWheels, bExplosionSound); }
    bool SetUpWheelColModel_Reversed(CColModel* wheelCol) { return CAutomobile::SetUpWheelColModel(wheelCol); }
    bool BurstTyre_Reversed(uint8 tyreComponentId, bool bPhysicalEffect) { return CAutomobile::BurstTyre(tyreComponentId, bPhysicalEffect); }
    bool IsRoomForPedToLeaveCar_Reversed(uint32 arg0, CVector* arg1) { return CAutomobile::IsRoomForPedToLeaveCar(arg0, arg1); }
    void SetupSuspensionLines_Reversed() { CAutomobile::SetupSuspensionLines(); }
    CVector AddMovingCollisionSpeed_Reversed(CVector& point) { return CAutomobile::AddMovingCollisionSpeed(point); }
    void Fix_Reversed() { CAutomobile::Fix(); }
    void SetupDamageAfterLoad_Reversed() { CAutomobile::SetupDamageAfterLoad(); }
    void DoBurstAndSoftGroundRatios_Reversed() { CAutomobile::DoBurstAndSoftGroundRatios(); }
    float GetHeightAboveRoad_Reversed() { return CAutomobile::GetHeightAboveRoad(); }
    void PlayCarHorn_Reversed() { CAutomobile::PlayCarHorn(); }
    int32 GetNumContactWheels_Reversed() { return CAutomobile::GetNumContactWheels(); }
    void VehicleDamage_Reversed(float damageIntensity, eVehicleCollisionComponent collisionComponent, CEntity* damager, CVector* vecCollisionCoors, CVector* vecCollisionDirection, eWeaponType weapon) { CAutomobile::VehicleDamage(damageIntensity, collisionComponent, damager, vecCollisionCoors, vecCollisionDirection, weapon); }
    bool GetTowHitchPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* veh) { return CAutomobile::GetTowHitchPos(outPos, bCheckModelInfo, veh); }
    bool GetTowBarPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* veh) { return CAutomobile::GetTowBarPos(outPos, bCheckModelInfo, veh); }
    bool SetTowLink_Reversed(CVehicle* tractor, bool arg1) { return CAutomobile::SetTowLink(tractor, arg1); }
    bool BreakTowLink_Reversed() { return CAutomobile::BreakTowLink(); }
    float FindWheelWidth_Reversed(bool bRear) { return CAutomobile::FindWheelWidth(bRear); }
    bool Save_Reversed() { return CAutomobile::Save(); }
    bool Load_Reversed() { return CAutomobile::Load(); }
};

VALIDATE_SIZE(CAutomobile, 0x988);

extern CColPoint *aAutomobileColPoints;

// Disable matfx (material effects) for material (callback), "data" parameter is unused
RpMaterial *DisableMatFx(RpMaterial* material, void* data);
// callback
RwObject* GetCurrentAtomicObjectCB(RwObject* object, void* data);
