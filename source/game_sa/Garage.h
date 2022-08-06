#pragma once

#include "AEDoorAudioEntity.h"
#include "eGarage.h"

class CStoredCar;

class CGarage {
public:
    CVector          m_vPosn;
    CVector2D        m_vDirectionA;
    CVector2D        m_vDirectionB;
    float            m_fTopZ;
    float            m_fWidth;
    float            m_fHeight;
    float            m_fLeftCoord;
    float            m_fRightCoord;
    float            m_fFrontCoord;
    float            m_fBackCoord;
    float            m_fDoorPosition;
    uint32           m_nTimeToOpen;
    CVehicle*        m_pTargetCar;
    char             m_anName[8];
    eGarageType      m_nType;
    eGarageDoorState m_nDoorState;
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
    eGarageType        m_nOriginalType;
    CAEDoorAudioEntity m_GarageAudio;

public:
    static constexpr auto NUM_GARAGE_STORED_CARS{ 4 };

    static void InjectHooks();

    CGarage() = default;  // 0x4470E0
    ~CGarage() = default; // 0x447110

    void InitDoorsAtStart();
    void Update(int32 garageId);

    void TidyUpGarageClose();
    void TidyUpGarage();

    void StoreAndRemoveCarsForThisHideOut(CStoredCar* car, int32 maxSlot);
    bool RestoreCarsForThisHideOut(CStoredCar* car);
    bool RestoreCarsForThisImpoundingGarage(CStoredCar* car);

    void RemoveCarsBlockingDoorNotInside();

    bool IsEntityTouching3D(CEntity* entity);
    bool IsEntityEntirelyOutside(CEntity* entity, float radius);
    bool IsStaticPlayerCarEntirelyInside();
    bool IsEntityEntirelyInside3D(CEntity* entity, float radius);
    bool IsPointInsideGarage(CVector point);
    bool IsPointInsideGarage(CVector point, float radius);
    bool IsPlayerOutsideGarage(float fRadius);
    bool IsPlayerEntirelyInsideGarage();
    bool IsAnyOtherCarTouchingGarage(CVehicle* vehicle);
    bool IsAnyOtherPedTouchingGarage(CPed* ped);
    bool IsAnyCarBlockingDoor();
    bool IsGarageEmpty();

    eGarageDoorState PlayerArrestedOrDied();

    void OpenThisGarage();
    void CloseThisGarage();

    bool SlideDoorOpen();
    bool SlideDoorClosed();

    bool RightModTypeForThisGarage(CVehicle* vehicle);
    float CalcDistToGarageRectangleSquared(float, float);
    void NeatlyLineUpStoredCars(CStoredCar* car);

    int32 FindMaxNumStoredCarsForGarage();
    bool EntityHasASphereWayOutsideGarage(CEntity* entity, float fRadius);

    void ThrowCarsNearDoorOutOfGarage(CVehicle* ignoredVehicle);
    int32 CountCarsWithCenterPointWithinGarage(CVehicle* ignoredVehicle);
    void StoreAndRemoveCarsForThisImpoundingGarage(CStoredCar* storedCars, int32 iMaxSlot);
    void CenterCarInGarage(CVehicle* vehicle);
    void FindDoorsWithGarage(CObject** ppFirstDoor, CObject** ppSecondDoor);

    static void BuildRotatedDoorMatrix(CEntity* entity, float fDoorPosition);

    // NOTSA section
    [[nodiscard]] bool IsHideOut() const;
    [[nodiscard]] bool IsOpen()   const { return m_nDoorState == GARAGE_DOOR_OPEN || m_nDoorState == GARAGE_DOOR_WAITING_PLAYER_TO_EXIT; }
    [[nodiscard]] bool IsClosed() const { return m_nDoorState == GARAGE_DOOR_CLOSED; }
    void SetOpened() { m_nDoorState = GARAGE_DOOR_OPEN; }
    void SetClosed() { m_nDoorState = GARAGE_DOOR_CLOSED; }
    void ResetDoorPosition() { m_fDoorPosition = 0.0f; } // todo: not good name
};
VALIDATE_SIZE(CGarage, 0xD8);
