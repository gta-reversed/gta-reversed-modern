/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CAutomobile.h"

enum eTrailerNodes {
    TRAILER_NODE_NONE = 0,
    TRAILER_CHASSIS = 1,
    TRAILER_WHEEL_RF = 2,
    TRAILER_WHEEL_RM = 3,
    TRAILER_WHEEL_RB = 4,
    TRAILER_WHEEL_LF = 5,
    TRAILER_WHEEL_LM = 6,
    TRAILER_WHEEL_LB = 7,
    TRAILER_DOOR_RF = 8,
    TRAILER_DOOR_RR = 9,
    TRAILER_DOOR_LF = 10,
    TRAILER_DOOR_LR = 11,
    TRAILER_BUMP_FRONT = 12,
    TRAILER_BUMP_REAR = 13,
    TRAILER_WING_RF = 14,
    TRAILER_WING_LF = 15,
    TRAILER_BONNET = 16,
    TRAILER_BOOT = 17,
    TRAILER_WINDSCREEN = 18,
    TRAILER_EXHAUST = 19,
    TRAILER_MISC_A = 20,
    TRAILER_MISC_B = 21,
    TRAILER_MISC_C = 22,
    TRAILER_NUM_NODES
};

class CTrailer : public CAutomobile {
protected:
    CTrailer(plugin::dummy_func_t) : CAutomobile(plugin::dummy) {}
public:
    CColPoint field_988[2];
    float field_9E0;
    float field_9E4;
    char field_9E8[4];
    float field_9EC;
    float field_9F0;

    static float& m_fTrailerSuspensionForce; // 1.5
    static float& m_fTrailerDampingForce; // 0.1

    CTrailer(int modelIndex, unsigned char createdBy);

    void ScanForTowLink();
};

VALIDATE_SIZE(CTrailer, 0x9F4);

extern float& TRAILER_TOWED_MINRATIO; // 0.9
extern float& RELINK_TRAILER_DIFF_LIMIT_XY; // 0.4
extern float& RELINK_TRAILER_DIFF_LIMIT_Z; // 1.0