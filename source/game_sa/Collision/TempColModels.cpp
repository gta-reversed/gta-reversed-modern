#include "StdInc.h"

#include "TempColModels.h"

CColModel& CTempColModels::ms_colModelDoor1 = *(CColModel*)0x968E50;
CColModel& CTempColModels::ms_colModelBumper1 = *(CColModel*)0x968E80;
CColModel& CTempColModels::ms_colModelPanel1 = *(CColModel*)0x968EB0;
CColModel& CTempColModels::ms_colModelBonnet1 = *(CColModel*)0x968EE0;
CColModel& CTempColModels::ms_colModelBoot1 = *(CColModel*)0x968F10;
CColModel& CTempColModels::ms_colModelWheel1 = *(CColModel*)0x968F40;
CColModel& CTempColModels::ms_colModelBodyPart1 = *(CColModel*)0x968F70;
CColModel& CTempColModels::ms_colModelBodyPart2 = *(CColModel*)0x968FA0;
CColModel& CTempColModels::ms_colModelWeapon = *(CColModel*)0x968FD0;
CColModel& CTempColModels::ms_colModelBBox = *(CColModel*)0x968A00;

void CTempColModels::InjectHooks()
{
    RH_ScopedClass(CTempColModels);
    RH_ScopedCategory("Collision");

}

void CTempColModels::Initialise()
{
    plugin::Call<0x5BA8C0>();
}

void CTempColModels::Shutdown()
{
    plugin::Call<0x41B360>();
}
