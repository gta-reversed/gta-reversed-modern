#pragma once

#include "ColModel.h"

class CTempColModels {
public:
    static CColModel& ms_colModelDoor1;
    static CColModel& ms_colModelBumper1;
    static CColModel& ms_colModelPanel1;
    static CColModel& ms_colModelBonnet1;
    static CColModel& ms_colModelBoot1;
    static CColModel& ms_colModelWheel1;
    static CColModel& ms_colModelBodyPart1;
    static CColModel& ms_colModelBodyPart2;
    static CColModel& ms_colModelWeapon;
    static CColModel& ms_colModelBBox;
    static inline CColModel& ms_colModelPeds = *(CColModel*)0x968DF0;

public:
    static void InjectHooks();

public:
    static void Initialise();
    static void Shutdown();
};

// TODO: For convenience, should be replaced by `CTempColModels::ms_colModelPeds`
static inline auto& colModelPeds = CTempColModels::ms_colModelPeds;
