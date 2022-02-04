#pragma once

#include "AEDoorAudioEntity.h"

class CStoredCar;
class CEntity;
class CPed;
class CObject;
class CVehicle;

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
    bool RightModTypeForThisGarage(CVehicle* vehicle);
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
    bool IsEntityEntirelyInside3D(CEntity* entity, float fRadius);
    bool IsEntityEntirelyOutside(CEntity* entity, float fRadius);
    bool IsPlayerOutsideGarage(float fRadius);
    bool IsPlayerEntirelyInsideGarage();
    bool IsEntityTouching3D(CEntity* entity);
    bool EntityHasASphereWayOutsideGarage(CEntity* entity, float fRadius);
    bool IsAnyOtherCarTouchingGarage(CVehicle* ignoredVeh);
    void ThrowCarsNearDoorOutOfGarage(CVehicle* ignoredVeh);
    bool IsAnyOtherPedTouchingGarage(CPed* pIgnoredPed);
    bool IsAnyCarBlockingDoor();
    int32 CountCarsWithCenterPointWithinGarage(CVehicle* ignoredVeh);
    void RemoveCarsBlockingDoorNotInside();
    void StoreAndRemoveCarsForThisHideOut(CStoredCar* pStoredCar, int32 iMaxSlot);
    void StoreAndRemoveCarsForThisImpoundingGarage(CStoredCar* pStoredCar, int32 iMaxSlot);
    void TidyUpGarage();
    void TidyUpGarageClose();
    void CenterCarInGarage(CVehicle* vehicle);
    void FindDoorsWithGarage(CObject** ppFirstDoor, CObject** ppSecondDoor);
    bool SlideDoorOpen();
    bool SlideDoorClosed();
    bool IsStaticPlayerCarEntirelyInside();
    bool IsGarageEmpty();

public:
    static void BuildRotatedDoorMatrix(CEntity* entity, float fDoorPosition);

};
VALIDATE_SIZE(CGarage, 0xD8);
