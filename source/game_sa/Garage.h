#pragma once

#include "AEDoorAudioEntity.h"

struct CStoredCar {
    CVector  m_vPosn;
    uint32 m_dwHandlingFlags;
    uint8  m_nStoredCarFlags;
    uint8  _pad0;
    uint16 m_wModelIndex;
    int16  m_awCarMods[15];
    uint8  m_nPrimaryColor;
    uint8  m_nSecondaryColor;
    uint8  m_nTertiaryColor;
    uint8  m_nQuaternaryColor;
    uint8  m_nRadiostation;
    uint8  m_anCompsToUse[2];
    uint8  m_nBombType;
    uint8  m_nPaintjob;
    uint8  m_nNitroBoosts;
    uint8  m_nPackedForwardX;
    uint8  m_nPackedForwardY;
    uint8  m_nPackedForwardZ;
    uint8  _pad1;

public:
    static void InjectHooks();

    CVehicle* RestoreCar();
    void      StoreCar(CVehicle* pVehicle);

    // NOTSA
    void Init() { m_wModelIndex = 0; }
    void Clear() { m_wModelIndex = 0; }
    bool HasCar() { return m_wModelIndex != 0; }
};
VALIDATE_SIZE(CStoredCar, 0x40);

class CGarage {
public:
    CGarage() = default;
    ~CGarage() = default;

public:
    CVector   m_vPosn;
    CVector2D m_vDirectionA;
    CVector2D m_vDirectionB;
    float     m_fTopZ;
    float     m_fWidth;
    float     m_fHeight;
    float     m_fLeftCoord;
    float     m_fRightCoord;
    float     m_fFrontCoord;
    float     m_fBackCoord;
    float     m_fDoorPosition;
    uint32    m_dwTimeToOpen;
    CVehicle* m_pTargetCar;
    char      m_anName[8];
    uint8     m_nType;      // see eGarageType
    uint8     m_nDoorState; // see eGarageDoorState
    union {
        uint8 m_nFlags;
        struct {
            uint8 m_b0x1 : 1;
            uint8 m_bInactive : 1;
            uint8 m_bUsedRespray : 1;
            uint8 m_bDoorOpensUp : 1;
            uint8 m_bDoorGoesIn : 1;
            uint8 m_bCameraFollowsPlayer : 1;
            uint8 m_bDoorClosed : 1;
            uint8 m_bRespraysAlwaysFree : 1;
        };
    };
    uint8              m_nOriginalType;
    CAEDoorAudioEntity m_GarageAudio;

public:
    static constexpr size_t NUM_GARAGE_STORED_CARS = 4;

    static void InjectHooks();

    void Update();
    void InitDoorsAtStart();
    bool RightModTypeForThisGarage(CVehicle* pVehicle);
    void OpenThisGarage();
    void CloseThisGarage();
    float CalcDistToGarageRectangleSquared(float, float);
    void NeatlyLineUpStoredCars(CStoredCar* pCar);
    bool RestoreCarsForThisHideOut(CStoredCar* pCar);
    bool RestoreCarsForThisImpoundingGarage(CStoredCar* pCar);
    void PlayerArrestedOrDied();
    bool IsPointInsideGarage(CVector vecPoint);
    bool IsPointInsideGarage(CVector vecPoint, float fRadius);
    int32 FindMaxNumStoredCarsForGarage();
    bool IsEntityEntirelyInside3D(CEntity* pEntity, float fRadius);
    bool IsEntityEntirelyOutside(CEntity* pEntity, float fRadius);
    bool IsPlayerOutsideGarage(float fRadius);
    bool IsPlayerEntirelyInsideGarage();
    bool IsEntityTouching3D(CEntity* pEntity);
    bool EntityHasASphereWayOutsideGarage(CEntity* pEntity, float fRadius);
    bool IsAnyOtherCarTouchingGarage(CVehicle* pIgnoredVehicle);
    void ThrowCarsNearDoorOutOfGarage(CVehicle* pIgnoredVehicle);
    bool IsAnyOtherPedTouchingGarage(CPed* pIgnoredPed);
    bool IsAnyCarBlockingDoor();
    int32 CountCarsWithCenterPointWithinGarage(CVehicle* pIgnoredVeh);
    void RemoveCarsBlockingDoorNotInside();
    void StoreAndRemoveCarsForThisHideOut(CStoredCar* pStoredCar, int32 iMaxSlot);
    void StoreAndRemoveCarsForThisImpoundingGarage(CStoredCar* pStoredCar, int32 iMaxSlot);
    void TidyUpGarage();
    void TidyUpGarageClose();
    void CenterCarInGarage(CVehicle* pVehicle);
    void FindDoorsWithGarage(CObject** ppFirstDoor, CObject** ppSecondDoor);
    bool SlideDoorOpen();
    bool SlideDoorClosed();
    bool IsStaticPlayerCarEntirelyInside();
    bool IsGarageEmpty();

public:
    static void BuildRotatedDoorMatrix(CEntity* pEntity, float fDoorPosition);

};
VALIDATE_SIZE(CGarage, 0xD8);
