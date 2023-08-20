/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "PathFind.h"
#include "TaskUtilityLineUpPedWithCar.h"
#include "eTargetDoor.h"

// Note: This class is abstract, that is, it can't be directly constructed,
// rather, use one of the derived classes.
class NOTSA_EXPORT_VTABLE CTaskComplexEnterCar : public CTaskComplex {
public:
    CVehicle*                     m_car{};                            /// Vehicle to get into/onto
    bool                          m_bAsDriver : 1{};                  /// Enter as driver
    bool                          m_bQuitAfterOpeningDoor : 1{};      /// Stop after opening the door
    bool                          m_bQuitAfterDraggingPedOut : 1{};   /// Stop after dragging the ped out from the target seat
    bool                          m_bCarryOnAfterFallingOff : 1{};    /// [For bikes, etc] Get back up and continue driving
    int32                         m_targetDoor{};                     /// Door to enter on
    int32                         m_targetDoorOppositeToFlag{};       /// Not sure
    int32                         m_targetSeat{};                     /// Seat we want to be at
    int32                         m_draggedPedDownTime{};             /// Not sure
    eMoveState                    m_moveState{ PEDMOVE_RUN };         /// How to approach the vehicle
    uint8                         m_numGettingInSet{};                /// Not sure
    uint8                         m_camMovementChoice{};              /// Not sure
    CVector                       m_targetDoorPos{};                  /// Target door's position (Persumeably calculated using `CCarEnterExit::GetPositionToOpenCarDoor`)
    CTaskUtilityLineUpPedWithCar* m_lineUpUtil{};                     /// Line up utility
    bool                          m_aborting{};                       /// Whenever `MakeAbortable` was called (?)
    CPed*                         m_draggedPed{};                     /// The ped we're dragging out rn (that was at targetSeat)
    uint8                         m_doorFlagsSet{};                   /// used for CVehicle::SetGettingInFlags
    float                         m_cruiseSpeed{-1.f};                /// How fast to go after we've entered. Only used when `m_bAsDriver` is set
    int32                         m_enterCarStartTime{};              /// When we started entering the vehicle (`CTimer::GetTimeMs()`)

public:
    static void InjectHooks();

    // Shouldn't be used directly, use `CTaskComplexEnterCarAsDriver` or `CTaskComplexEnterCarAsPassenger` instead
    CTaskComplexEnterCar(CVehicle* targetVehicle, bool bAsDriver, bool bQuitAfterOpeningDoor, bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff = false);
    ~CTaskComplexEnterCar() override;

    bool           MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    CTask*         CreateNextSubTask(CPed* ped) override;
    CTask*         CreateFirstSubTask(CPed* ped) override;
    CTask*         ControlSubTask(CPed* ped) override;
    CTask*         CreateSubTask(eTaskType type, CPed* ped);
    virtual CTask* CreateNextSubTask_AfterSimpleCarAlign(CPed* ped);
    CVector        GetTargetPos();
    CVehicle*      GetCameraAvoidVehicle();

    auto GetTarget() const { return m_car; }
private:
    // 0x63A220
    CTaskComplexEnterCar* Constructor(CVehicle* vehicle, bool bAsDriver, bool bQuitAfterOpeningDoor, bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff) {
        this->CTaskComplexEnterCar::CTaskComplexEnterCar(vehicle, bAsDriver, bQuitAfterOpeningDoor, bQuitAfterDraggingPedOut, bCarryOnAfterFallingOff);
        return this;
    }

    // 0x63DFA0
    CTaskComplexEnterCar* Destructor() {
        this->CTaskComplexEnterCar::~CTaskComplexEnterCar();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexEnterCar, 0x50);
