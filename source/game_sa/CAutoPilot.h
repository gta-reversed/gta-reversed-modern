/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "CPathFind.h"
#include "eCarMission.h"

enum eCarDrivingStyle : int8_t
{
    DRIVINGSTYLE_STOP_FOR_CARS,
    DRIVINGSTYLE_SLOW_DOWN_FOR_CARS,
    DRIVINGSTYLE_AVOID_CARS,
    DRIVINGSTYLE_PLOUGH_THROUGH,
    DRIVINGSTYLE_STOP_FOR_CARS_IGNORE_LIGHTS
};

class  CAutoPilot {
public:
    CAutoPilot();

public:
    CNodeAddress         m_currentAddress;
    CNodeAddress         m_startingRouteNode;
    CNodeAddress         m_endingRouteNode;
    int field_C;
    unsigned int         m_nSpeedScaleFactor;
    CCarPathLinkAddress  m_nCurrentPathNodeInfo;
    CCarPathLinkAddress  m_nNextPathNodeInfo;
    CCarPathLinkAddress  m_nPreviousPathNodeInfo;
    char field_1A[2];
    unsigned int         m_nTimeToStartMission;
    unsigned int         m_nTimeSwitchedToRealPhysics;
    char _smthPrev;
    char _smthCurr;
    char _smthNext;
    char                 m_nCurrentLane;
    char                 m_nNextLane;
    eCarDrivingStyle     m_nCarDrivingStyle;
    eCarMission          m_nCarMission;
    char                 m_nTempAction;
    unsigned int         m_nTempActionTime;
    unsigned int        _someStartTime;
    unsigned char        m_ucTempActionMode;
    unsigned char        m_ucCarMissionModeCounter; 
    char field_36[2];
    float               m_speed;
    float               m_fMaxTrafficSpeed;
    unsigned char       m_nCruiseSpeed;
    char field_41;
    char field_42[2];
    float field_44;
    unsigned char m_ucHeliTargetDist;
    unsigned char m_ucHeliSpeedMult;
    char field_4A;
    union {
        unsigned char  m_nCarCtrlFlags;
        struct carCtrlFlags {
            unsigned char bHonkAtCar : 1;
            unsigned char bHonkAtPed : 1;
            unsigned char bAvoidLevelTransitions : 1;
            unsigned char bStayInFastLane : 1;
            unsigned char bStayInSlowLane : 1;
            unsigned char bDoTargetCatchupCheck : 1;
            unsigned char bCantGoAgainstTraffic : 1;
            unsigned char bHeliFollowTarget : 1;
        } carCtrlFlags;
    };
    union
    {
        unsigned char m_nMovementFlags;
        struct movementFlags
        {
            unsigned char bIsStopped : 1;
            unsigned char bIsParked : 1;
        } movementFlags;
    };
    char                 m_nStraightLineDistance;
    unsigned char m_ucCarFollowDist;
    unsigned char m_ucHeliTargetDist2;
    char field_50;
    char field_51;
    char field_52[10];
    CVector              m_vecDestinationCoors;
    CNodeAddress         m_aPathFindNodesInfo[8];
    unsigned short       m_nPathFindNodesCount;
    char field_8A[2];
    class CVehicle      *m_pTargetCar;
    class CEntity       *m_pCarWeMakingSlowDownFor;
    int8_t m_vehicleRecordingId;
    bool m_bPlaneDogfightSomething;
    short field_96;

    void SetCarMission(eCarMission carMission)
    {
        if (m_nCarMission != MISSION_CRASH_PLANE_AND_BURN && m_nCarMission != MISSION_CRASH_HELI_AND_BURN)
            m_nCarMission = carMission;
    }
};

VALIDATE_SIZE(CAutoPilot, 0x98);
