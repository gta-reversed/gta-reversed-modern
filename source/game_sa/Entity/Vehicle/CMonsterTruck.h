/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CAutomobile.h"

enum eMonsterTruckNodes {
    MONSTER_NODE_NONE = 0,
    MONSTER_CHASSIS = 1,
    MONSTER_WHEEL_RF = 2,
    MONSTER_WHEEL_RM = 3,
    MONSTER_WHEEL_RB = 4,
    MONSTER_WHEEL_LF = 5,
    MONSTER_WHEEL_LM = 6,
    MONSTER_WHEEL_LB = 7,
    MONSTER_DOOR_RF = 8,
    MONSTER_DOOR_RR = 9,
    MONSTER_DOOR_LF = 10,
    MONSTER_DOOR_LR = 11,
    MONSTER_BUMP_FRONT = 12,
    MONSTER_BUMP_REAR = 13,
    MONSTER_WING_RF = 14,
    MONSTER_WING_LF = 15,
    MONSTER_BONNET = 16,
    MONSTER_BOOT = 17,
    MONSTER_WINDSCREEN = 18,
    MONSTER_TRANSMISSION_F = 19,
    MONSTER_TRANSMISSION_R = 20,
    MONSTER_LOADBAY = 21,
    MONSTER_MISC_A = 22,
    MONSTER_NUM_NODES
};

class CMonsterTruck : public CAutomobile {
protected:
    CMonsterTruck(plugin::dummy_func_t) : CAutomobile(plugin::dummy) {}
public:
    float field_988;
    float field_98C;
    float field_990;
    float field_994;
    float field_998;

    static float& DUMPER_COL_ANGLEMULT; // 0.0002

    CMonsterTruck(int modelIndex, unsigned char createdBy);

    void ExtendSuspension();
};

VALIDATE_SIZE(CMonsterTruck, 0x99C);

extern float& fWheelExtensionRate; // 0.1