/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vehicle.h"

struct tBikeHandlingData;

enum eBikeNodes {
    BIKE_NODE_NONE = 0,
    BIKE_CHASSIS = 1,
    BIKE_FORKS_FRONT = 2,
    BIKE_FORKS_REAR = 3,
    BIKE_WHEEL_FRONT = 4,
    BIKE_WHEEL_REAR = 5,
    BIKE_MUDGUARD = 6,
    BIKE_HANDLEBARS = 7,
    BIKE_MISC_A = 8,
    BIKE_MISC_B = 9,
    BIKE_NUM_NODES
};

class CBike : public CVehicle {
protected:
    CBike(plugin::dummy_func_t) : CVehicle(plugin::dummy), m_mLeanMatrix(plugin::dummy) {}
public:
    RwFrame* m_aBikeNodes[BIKE_NUM_NODES];
    bool     m_bLeanMatrixCalculated;
    char     _pad0[3];
    CMatrix  m_mLeanMatrix;
    union {
        struct {
            uint8 bDamageFlag1 : 1;
            uint8 bDamageFlag2 : 1;
            uint8 bIgnoreWater : 1;
            uint8 bDamageFlag3 : 1;
            uint8 bDamageFlag4 : 1;
            uint8 bDamageFlag5 : 1;
            uint8 bDamageFlag7 : 1;
            uint8 bDamageFlag8 : 1;
        } damageFlags;
        uint8 ucDamageFlags;
    };
    char          field_615[27];
    CVector       field_630;
    void*         m_pBikeHandlingData;
    CRideAnimData m_rideAnimData;
    uint8         m_anWheelDamageState[2];
    char          field_65E;
    char          field_65F;
    CColPoint     m_anWheelColPoint[4];
    float         m_fWheelsSuspensionCompression[4];
    float         field_720[4];
    float         m_wheelCollisionState[4];
    float         field_740;
    int32         m_anWheelSurfaceType[2];
    char          field_74C[2];
    char          field_74E[2];
    float         m_afWheelRotationX[2];
    float         m_fWheelSpeed[2];
    float         field_760;
    float         field_764;
    float         field_768;
    float         field_76C;
    float         field_770[4];
    float         field_780[4];
    float         m_fHeightAboveRoad;
    float         m_fCarTraction;
    float         field_798;
    float         field_79C;
    float         field_7A0;
    float         field_7A4;
    int16         field_7A8;
    char          field_7AA[2];
    int32         field_7AC;
    int32         field_7B0;
    bool          m_bPedLeftHandFixed;
    bool          m_bPedRightHandFixed;
    char          field_7B6[2];
    int32         field_7B8;
    int32         field_7BC;
    CEntity*      m_apWheelCollisionEntity[4];
    CVector       m_avTouchPointsLocalSpace[4];
    CEntity*      m_pDamager;
    uint8         m_nNumContactWheels;
    uint8         m_nNumWheelsOnGround;
    char          field_806;
    char          field_807;
    float         m_fSomeGasPedalStuff;
    tWheelState   m_anWheelState[2]; // enum tWheelState

public:
    static void InjectHooks();

    // VTABLE
    void Fix() override;
    void BlowUpCar(CEntity* damager, uint8 bHideExplosion) override;

    bool IsDoorReady(eDoors door) override { return true; }      // 0x6B58E0
    bool IsDoorFullyOpen(eDoors door) override { return false; } // 0x6B58F0
    bool IsDoorClosed(eDoors door) override { return false; }    // 0x6B5900
    bool IsDoorMissing(eDoors door) override { return true; }    // 0x6B5910
    bool IsDoorReady(uint32 door) override { return true; }      // 0x6B5920
    bool IsDoorFullyOpen(uint32 door) override { return false; } // 0x6B5930
    bool IsDoorClosed(uint32 door) override { return false; }    // 0x6B5940
    bool IsDoorMissing(uint32 door) override { return true; }    // 0x6B5950

    void ProcessAI(uint32& arg0);

    // FUNCS
    CBike(int32 modelIndex, eVehicleCreatedBy createdBy);

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

    void SetupModelNodes();
    void dmgDrawCarCollidingParticles(CVector const& position, float power, eWeaponType weaponType);
    static bool DamageKnockOffRider(CVehicle* arg0, float arg1, uint16 arg2, CEntity* arg3, CVector& arg4, CVector& arg5);
    CPed* KnockOffRider(eWeaponType arg0, uint8 arg1, CPed* arg2, bool arg3);
    void SetRemoveAnimFlags(CPed* ped);
    void ReduceHornCounter();
    void ProcessBuoyancy();
    void inline ProcessPedInVehicleBuoyancy(CPed* pPed, bool bIsDriver);
    void ResetSuspension();
    bool GetAllWheelsOffGround();
    void DebugCode(); // dummy function
    void DoSoftGroundResistance(uint32& arg0);
    void PlayHornIfNecessary();
    void CalculateLeanMatrix();
    static void ProcessRiderAnims(CPed* rider, CVehicle* vehicle, CRideAnimData* rideData, tBikeHandlingData* handling);
    void FixHandsToBars(CPed* rider);
    void PlaceOnRoadProperly();
    void GetCorrectedWorldDoorPosition(CVector& out, CVector arg1, CVector arg2);

private:
    void BlowUpCar_Reversed(CEntity* damager, uint8 bHideExplosion);
    void Fix_Reversed();
};

VALIDATE_SIZE(CBike, 0x814);
