#pragma once

#include "AEDoorAudioEntity.h"
#include "eGarage.h"

class CStoredCar;

class CGarage {
public:
    CVector Base;
    CVector2D m_Delta1;
    CVector2D m_Delta2;
    float CeilingZ;
    float Delta1Length;
    float Delta2Length;
    float MinX; // Left Coord
    float MaxX; // Right Coord
    float MinY; // Front Coord
    float MaxY; // Back Coord

    float Openness;
    uint32 TimeOfNextEvent; // Time To Open
    CAutomobile* CarToCollect;
    char Name[8];
    eGarageType Type;
    eGarageDoorState DoorState;
    union {
        uint8 m_nFlags;
        struct {
            uint8 bClosingEmpty : 1;
            uint8 bDeActivated : 1;
            uint8 bResprayHappened : 1;
            uint8 bRotateDoor : 1;
            uint8 bInvertRotation : 1;
            uint8 bLeaveCameraAlone : 1;
            uint8 bShouldDoorsHaveCollision : 1;
            uint8 bFreeResprays : 1;
        };
    };
    eGarageType        m_nOriginalType;
    CAEDoorAudioEntity m_GarageAE;

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
    [[nodiscard]] bool IsOpen()   const { return DoorState == GARAGE_DOOR_OPEN || DoorState == GARAGE_DOOR_WAITING_PLAYER_TO_EXIT; }
    [[nodiscard]] bool IsClosed() const { return DoorState == GARAGE_DOOR_CLOSED; }
    void SetOpened() { DoorState = GARAGE_DOOR_OPEN; }
    void SetClosed() { DoorState = GARAGE_DOOR_CLOSED; }
    void ResetDoorPosition() { Openness = 0.0f; } // todo: not good name
};
VALIDATE_SIZE(CGarage, 0xD8);
