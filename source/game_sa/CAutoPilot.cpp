#include "StdInc.h"

CAutoPilot::CAutoPilot() : m_aPathFindNodesInfo()
{
    _smthNext = 1;
    _smthCurr = 1;

    m_nCarCtrlFlags = 0;

    field_C = 0;
    m_nSpeedScaleFactor = 1000;
    m_nNextLane = 0;
    m_nCurrentLane = 0;
    m_nCarDrivingStyle = eCarDrivingStyle::DRIVINGSTYLE_STOP_FOR_CARS;
    m_nCarMission = eCarMission::MISSION_NONE;
    m_nTempAction = 0;
    m_nCruiseSpeed = 10;
    m_fSomeSpeed = 10.0F;
    m_nPathFindNodesCount = 0;
    m_pTargetCar = nullptr;

    m_nTimeToStartMission = CTimer::m_snTimeInMilliseconds;
    m_nTimeSwitchedToRealPhysics = CTimer::m_snTimeInMilliseconds;
    _someStartTime = 0;

    m_nStraightLineDistance = 20;
    m_ucTempActionMode = 0;
    m_ucCarMissionModeCounter = 0;
    field_41 = 0;
    field_44 = 1.0;
    m_ucHeliSpeedMult = 0;   
    movementFlags.bIsStopped = false;
    movementFlags.bIsParked = false;
    field_4A = 0;
    m_ucCarFollowDist = 10;
    m_ucHeliTargetDist2 = 10;
    field_50 = (rand() & 7) + 2;
    field_94 = -1;
    m_bPlaneDogfightSomething = 0;
    m_pCarWeMakingSlowDownFor = nullptr;
    m_fMaxTrafficSpeed = 0.0F;
}
