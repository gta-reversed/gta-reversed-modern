#pragma once
#include "CAEDoorAudioEntity.h"

struct CStoredCar
{
    CVector m_vPosn;
    uint32_t m_dwHandlingFlags;
    uint8_t m_nStoredCarFlags;
    uint8_t _pad0;
    uint16_t m_wModelIndex;
    int16_t m_awCarMods[15];
    uint8_t m_nPrimaryColor;
    uint8_t m_nSecondaryColor;
    uint8_t m_nTertiaryColor;
    uint8_t m_nQuaternaryColor;
    uint8_t m_nRadiostation;
    uint8_t m_anCompsToUse[2];
    uint8_t m_nBombType;
    uint8_t m_nPaintjob;
    uint8_t m_nNitroBoosts;
    uint8_t m_nPackedForwardX;
    uint8_t m_nPackedForwardY;
    uint8_t m_nPackedForwardZ;
    uint8_t _pad1;

public:
    static void InjectHooks();

    CVehicle* RestoreCar();
    void StoreCar(CVehicle* pVehicle);
};
VALIDATE_SIZE(CStoredCar, 0x40);

class CGarage
{
public:
    CGarage() = default;
    ~CGarage() = default;
public:
    CVector m_vPosn;
    CVector2D m_vDirectionA;
    CVector2D m_vDirectionB;
    float m_fTopZ;
    float m_fWidth;
    float m_fHeight;
    float m_fLeftCoord;
    float m_fRightCoord;
    float m_fFrontCoord;
    float m_fBackCoord;
    float m_fDoorPosition;
    uint32_t m_dwTimeToOpen;
    CVehicle* m_pTargetCar;
    char m_anName[8];
    uint8_t m_nType; // see eGarageType
    uint8_t m_nDoorState; // see eGarageDoorState
    union
    {
        uint8_t m_nFlags;
        struct
        {
            uint8_t m_b0x1 : 1;
            uint8_t m_bInactive : 1;
            uint8_t m_bUsedRespray : 1;
            uint8_t m_bDoorOpensUp : 1;
            uint8_t m_bDoorGoesIn : 1;
            uint8_t m_bCameraFollowsPlayer : 1;
            uint8_t m_bDoorClosed : 1;
            uint8_t m_bRespraysAlwaysFree : 1;
        };
    };
    uint8_t m_nOriginalType;
    CAEDoorAudioEntity m_GarageAudio;

public:
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
    int FindMaxNumStoredCarsForGarage();
    bool IsEntityEntirelyInside3D(CEntity* pEntity, float fRadius);
    bool IsEntityEntirelyOutside(CEntity* pEntity, float fRadius);
    bool IsPlayerOutsideGarage(float fRadius);
    bool IsPlayerEntirelyInsideGarage();
    bool IsEntityTouching3D(CEntity* pEntity);
    bool EntityHasASpehereWayOutsideGarage(CEntity* pEntity, float fRadius);
    bool IsAnyOtherCarTouchingGarage(CVehicle* pIgnoredVehicle);
    void ThrowCarsNearDoorOutOfGarage(CVehicle* pIgnoredVehicle);
    bool IsAnyOtherPedTouchingGarage(CPed* pIgnoredPed);
    bool IsAnyCarBlockingDoor();
    int CountCarsWithCenterPointWithinGarage(CVehicle* pIgnoredVeh);
    void RemoveCarsBlockingDoorNotInside();
    void StoreAndRemoveCarsForThisHideOut(CStoredCar* pStoredCar, int iMaxSlot);
    void StoreAndRemoveCarsForThisImpoundingGarage(CStoredCar* pStoredCar, int iMaxSlot);
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
