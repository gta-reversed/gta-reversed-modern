/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class CVehicle;

enum eDoorState : unsigned char
{
    DOOR_NOTHING,
    DOOR_HIT_MAX_END,
    DOOR_HIT_MIN_END,
    DOOR_POP_OPEN,
    DOOR_SLAM_SHUT
};

class  CDoor {
public:
    float         m_fOpenAngle;
    float         m_fClosedAngle;
    short         m_nDirn;
    unsigned char m_nAxis;
    eDoorState m_nDoorState;
    float         m_fAngle;
    float         m_fPrevAngle;
    union 
    {
        struct 
        {
            unsigned char m_nDoorFlags;
        };
        float         m_fAngVel;
    };

    static float &DOOR_SPEED_MAX_CAPPED; // 0.5

    bool Process(CVehicle* vehicle, CVector& arg1, CVector& arg2, CVector& arg3);
    bool ProcessImpact(CVehicle* vehicle, CVector& arg1, CVector& arg2, CVector& arg3);
    void Open(float openRatio);
    float GetAngleOpenRatio();
    bool IsClosed();
    bool IsFullyOpen();
};

VALIDATE_SIZE(CDoor, 0x18);