/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vehicle.h"

struct tBikeHandlingData;

enum eBikeNodes {
    BIKE_NODE_NONE   = 0,
    BIKE_CHASSIS     = 1,
    BIKE_FORKS_FRONT = 2,
    BIKE_FORKS_REAR  = 3,
    BIKE_WHEEL_FRONT = 4,
    BIKE_WHEEL_REAR  = 5,
    BIKE_MUDGUARD    = 6,
    BIKE_HANDLEBARS  = 7,
    BIKE_MISC_A      = 8,
    BIKE_MISC_B      = 9,

    BIKE_NUM_NODES
};

class CBike : public CVehicle {
public:
    RwFrame* m_aBikeNodes[BIKE_NUM_NODES];
    bool     m_bLeanMatrixCalculated;
    CMatrix  m_mLeanMatrix;
    union {
        struct {
            uint8 bDamageFlag1     : 1;
            uint8 bDamageFlag2     : 1;
            uint8 bIgnoreWater     : 1; // bWaterTight
            uint8 bIsBeingPickedUp : 1;
            uint8 bIsStanding      : 1;
            uint8 bExtraSpeed      : 1;
            uint8 bIsOnFire        : 1;
            uint8 bWheelieCam      : 1;
        } bikeFlags;
        uint8 nBikeFlags;
    };
    CVector            f618;
    CVector            m_vecAvgSurfaceNormal; // sued
    CVector            m_vecAvgSurfaceRight;  // sued
    tBikeHandlingData* m_pBikeHandlingData;
    CRideAnimData      m_rideAnimData;
    uint8              m_anWheelDamageState[2];

    CColPoint     m_aWheelColPoint[4];
    float         m_fWheelsSuspensionCompression[4];
    float         m_fWheelsSuspensionCompressionPrev[4];
    float         m_aWheelTimer[4];
    float         field_740; // sued unused
    int32         m_anWheelSurfaceType[2];
    bool          m_abBloodState[2];
    bool          m_aWheelSkidmarkUnk[2]; // sued
    float         m_afWheelRotationX[2];
    float         m_fWheelSpeed[2];

    float         m_aWheelFrontPosition;     // sued m_aWheelPosition[2]
    float         m_aWheelRearPosition;
    float         m_aWheelBaseFrontPosition; // sued m_aWheelBasePosition[2]
    float         m_aWheelBaseRearPosition;

    float         field_770[4]; // sued m_aSuspensionSpringLength[4]
    float         field_780[4]; // sued m_aSuspensionLineLength[4]
    float         m_fHeightAboveRoad;
    float         m_fTraction;

    float         m_fRearForkLength;
    float         m_fFrontForkY;
    float         m_fFrontForkZ;
    float         m_fFrontForkSlope;

    int16         m_bDoingBurnout;
    float         m_fTireTemperature;
    float         m_fBrakeDestabilization;
    bool          m_bPedLeftHandFixed;
    bool          m_bPedRightHandFixed;
    char          field_7B6[2];
    cTransmission* field_7B8; // sued float m_fVelocityChangeForAudio
    float         m_fFireBlowUpTimer;
    CEntity*      m_apWheelCollisionEntity[4];  // sued m_aGroundPhysical
    CVector       m_avTouchPointsLocalSpace[4]; // sued m_aGroundOffset
    CEntity*      m_pDamager;
    uint8         m_nNumContactWheels;
    uint8         m_nNumWheelsOnGround;
    uint8         m_nDriveWheelsOnGround;     // sued
    uint8         m_nDriveWheelsOnGroundPrev; // sued
    float         m_fGasPedalAudio;           // sued
    tWheelState   m_anWheelState[2];

public:
    CBike(plugin::dummy_func_t) : CVehicle(plugin::dummy), m_mLeanMatrix(plugin::dummy) { /* todo: remove NOTSA */ }
    CBike(int32 modelIndex, eVehicleCreatedBy createdBy); // 0x6BF430
    ~CBike() override;

    void Fix() override;
    void BlowUpCar(CEntity* damager, uint8 bHideExplosion) override;
    void ProcessDrivingAnims(CPed* driver, uint8 bBlend) override;
    bool BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) override;
    void ProcessControlInputs(uint8 playerNum) override;
    int32 ProcessEntityCollision(CEntity* entity, CColPoint* colPoint) override;
    void Render() override;
    void PreRender() override;
    void Teleport(CVector destination, bool resetRotation) override;
    void ProcessControl() override;
    void VehicleDamage(float damageIntensity, eVehicleCollisionComponent component, CEntity* damager, CVector* vecCollisionCoors, CVector* vecCollisionDirection, eWeaponType weapon) override;
    void SetupSuspensionLines() override;
    void SetModelIndex(uint32 index) override;
    void PlayCarHorn() override;
    void SetupDamageAfterLoad() override;
    void DoBurstAndSoftGroundRatios() override;
    bool SetUpWheelColModel(CColModel* wheelCol) override;
    void RemoveRefsToVehicle(CEntity* entityToRemove) override;
    void ProcessControlCollisionCheck(bool applySpeed) override;
    void GetComponentWorldPosition(int32 componentId, CVector& outPos) override;
    void ProcessOpenDoor(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 animId, float fTime) override;

    bool IsDoorReady(eDoors door) override { return true; }      // 0x6B58E0
    bool IsDoorFullyOpen(eDoors door) override { return false; } // 0x6B58F0
    bool IsDoorClosed(eDoors door) override { return false; }    // 0x6B5900
    bool IsDoorMissing(eDoors door) override { return true; }    // 0x6B5910
    bool IsDoorReady(uint32 door) override { return true; }      // 0x6B5920
    bool IsDoorFullyOpen(uint32 door) override { return false; } // 0x6B5930
    bool IsDoorClosed(uint32 door) override { return false; }    // 0x6B5940
    bool IsDoorMissing(uint32 door) override { return true; }    // 0x6B5950

    bool IsRoomForPedToLeaveCar(uint32 a1, CVector* a2) override { return true; }                        // 0x6B7270
    inline bool IsComponentPresent(int32 componentId) override { return m_aBikeNodes[componentId] != nullptr; } // 0x6B59E0
    CRideAnimData* GetRideAnimData() override { return &m_rideAnimData; }                                // 0x6B58C0
    float GetHeightAboveRoad() override { return m_fHeightAboveRoad; }                                   // 0x6B58B0
    int32 GetNumContactWheels() override { return m_nNumContactWheels; }                                 // 0x6B58A0
    float FindWheelWidth(bool bRear) override { return 0.15f; }                                          // 0x6B8940

    virtual bool ProcessAI(uint32& extraHandlingFlags);

    void SetupModelNodes();
    void dmgDrawCarCollidingParticles(const CVector& position, float power, eWeaponType weaponType);
    static bool DamageKnockOffRider(CVehicle* arg0, float arg1, uint16 arg2, CEntity* arg3, CVector& arg4, CVector& arg5);
    CPed* KnockOffRider(eWeaponType arg0, uint8 arg1, CPed* ped, bool arg3);
    void SetRemoveAnimFlags(CPed* ped);
    void ReduceHornCounter();
    void ProcessBuoyancy();
    void inline ProcessPedInVehicleBuoyancy(CPed* ped, bool bIsDriver);
    void ResetSuspension();
    [[nodiscard]] bool GetAllWheelsOffGround() const;
    void DebugCode();
    void DoSoftGroundResistance(uint32& arg0);
    void PlayHornIfNecessary();
    void CalculateLeanMatrix();
    static void ProcessRiderAnims(CPed* rider, CVehicle* vehicle, CRideAnimData* rideData, tBikeHandlingData* handling, int16 a5);
    void FixHandsToBars(CPed* rider);
    void PlaceOnRoadProperly();
    void GetCorrectedWorldDoorPosition(CVector& out, CVector arg1, CVector arg2);

public: // NOTSA
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

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CBike* Constructor(int32 modelIndex, eVehicleCreatedBy createdBy) { this->CBike::CBike(modelIndex, createdBy); return this; }
    CBike* Destructor() {this->CBike::~CBike(); return this; }

    void Fix_Reversed() { CBike::Fix(); }
    void BlowUpCar_Reversed(CEntity* damager, uint8 bHideExplosion) { CBike::BlowUpCar(damager, bHideExplosion); }
    void ProcessDrivingAnims_Reversed(CPed* driver, uint8 bBlend) { CBike::ProcessDrivingAnims(driver, bBlend); }
    bool BurstTyre_Reversed(uint8 tyreComponentId, bool bPhysicalEffect) { return CBike::BurstTyre(tyreComponentId, bPhysicalEffect); }
    void ProcessControlInputs_Reversed(uint8 playerNum) { CBike::ProcessControlInputs(playerNum); }
    int32 ProcessEntityCollision_Reversed(CEntity* entity, CColPoint* colPoint) { return CBike::ProcessEntityCollision(entity, colPoint); }
    void Render_Reversed() { CBike::Render(); }
    void PreRender_Reversed() { CBike::PreRender(); }
    void Teleport_Reversed(CVector destination, bool resetRotation) { CBike::Teleport(destination, resetRotation); }
    void ProcessControl_Reversed() { CBike::ProcessControl(); }
    void VehicleDamage_Reversed(float damageIntensity, eVehicleCollisionComponent component, CEntity* damager, CVector* vecCollisionCoors, CVector* vecCollisionDirection, eWeaponType weapon) { CBike::VehicleDamage(damageIntensity, component, damager, vecCollisionCoors, vecCollisionDirection, weapon); }
    void SetupSuspensionLines_Reversed() { CBike::SetupSuspensionLines(); }
    void SetModelIndex_Reversed(uint32 index) { CBike::SetModelIndex(index); }
    void PlayCarHorn_Reversed() { CBike::PlayCarHorn(); }
    void SetupDamageAfterLoad_Reversed() { CBike::SetupDamageAfterLoad(); }
    void DoBurstAndSoftGroundRatios_Reversed() { CBike::DoBurstAndSoftGroundRatios(); }
    bool SetUpWheelColModel_Reversed(CColModel* wheelCol) { return CBike::SetUpWheelColModel(wheelCol); }
    void RemoveRefsToVehicle_Reversed(CEntity* entityToRemove) { CBike::RemoveRefsToVehicle(entityToRemove); }
    void ProcessControlCollisionCheck_Reversed(bool applySpeed) { CBike::ProcessControlCollisionCheck(applySpeed); }
    void GetComponentWorldPosition_Reversed(int32 componentId, CVector& outPos) { CBike::GetComponentWorldPosition(componentId, outPos); }
    void ProcessOpenDoor_Reversed(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 animId, float fTime) { CBike::ProcessOpenDoor(ped, doorComponentId, animGroup, animId, fTime); }
};

VALIDATE_SIZE(CBike, 0x814);
