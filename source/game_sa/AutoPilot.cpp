#include "StdInc.h"

#include "AutoPilot.h"

void CAutoPilot::InjectHooks() {
    RH_ScopedClass(CAutoPilot);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(RemoveOnePathNode, 0x41B950);
    RH_ScopedInstall(ModifySpeed, 0x41B980, {.reversed = false});
}

// 0x6D5E20
CAutoPilot::CAutoPilot() : m_aPathFindNodesInfo() {
    _smthNext = 1;
    _smthCurr = 1;

    m_nCarCtrlFlags = 0;

    m_timeToLeaveLink = 0;
    m_timeToNextLink = 1000;
    m_nNextLane = 0;
    m_nCurrentLane = 0;
    m_nCarDrivingStyle = DRIVING_STYLE_STOP_FOR_CARS;
    m_nCarMission = eCarMission::MISSION_NONE;
    m_nTempAction = 0;
    m_nCruiseSpeed = 10;
    m_speed = 10.0F;
    m_nPathFindNodesCount = 0;
    m_pTargetCar = nullptr;

    m_nTimeToStartMission = CTimer::GetTimeInMS();
    m_nTimeSwitchedToRealPhysics = CTimer::GetTimeInMS();
    _someStartTime = 0;

    m_nStraightLineDistance = 20;
    m_ucTempActionMode = 0;
    m_ucCarMissionModeCounter = 0;
    field_41 = 0;
    field_44 = 1.0f;
    m_ucHeliSpeedMult = 0;
    movementFlags.bIsStopped = false;
    movementFlags.bIsParked = false;
    field_4A = 0;
    m_ucCarFollowDist = 10;
    m_ucHeliTargetDist2 = 10;
    field_50 = CGeneral::GetRandomNumber() % 8 + 2;
    m_vehicleRecordingId = -1;
    m_bPlaneDogfightSomething = false;
    m_pCarWeMakingSlowDownFor = nullptr;
    m_fMaxTrafficSpeed = 0.0F;
}

// 0x41B980
void CAutoPilot::ModifySpeed(float targetSpeed) {
    /*
    * Code fine so far, missing CCurves stub
    // Check if both nodes are loaded
    if (!ThePaths.IsNodeAreaLoaded({ m_currentAddress, m_nNextPathNodeInfo })) {
        return;
    }

    // Make sure target speed is never 0 (to avoid division by 0 presumeably)
    targetSpeed = std::max(targetSpeed, 0.01f);
    */
}

// 0x41B950
void CAutoPilot::RemoveOnePathNode() {
    assert(m_nPathFindNodesCount >= 1); // Otherwise `- 1` would underflow it, and bug out
    
    // Shift to the left, this way the first node is "popped off" 
    std::shift_left(m_aPathFindNodesInfo.begin(), std::next(m_aPathFindNodesInfo.begin(), (size_t)m_nPathFindNodesCount), 1u);
    m_nPathFindNodesCount--;
}


/*!
* @notsa
* @brief Adds a temporary action
* @param action The action to add
* @param timeMs The action's duration in milliseconds
*/
void CAutoPilot::SetTempAction(uint32 action, uint32 durationMs) noexcept {
    m_nTempAction = action;
    m_nTempActionTime = CTimer::GetTimeInMS() + durationMs;
}

/*!
* @notsa
* @brief Clears the temporary action
*/
void CAutoPilot::ClearTempAction() noexcept {
    // Seems like they really had a function like this, and it seemingly used `SetTempAction(0, 0)`
    m_nTempAction = 0;
    m_nTempActionTime = 0;
}
