/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "MissionCleanup.h"

CMissionCleanup::CMissionCleanup()
{
    Init();
}

// Initializes data
// 0x4637A0
void CMissionCleanup::Init()
{
    ((void(__thiscall*)(CMissionCleanup*))0x4637A0)(this);
}

// Performs a clean-up
// 0x468560
void CMissionCleanup::Process()
{
    ((void(__thiscall*)(CMissionCleanup*))0x468560)(this);
}

// Finds a free entity, returns NULL if no free entity can be found.
// 0x4637C0
tMissionCleanupEntity* CMissionCleanup::FindFree()
{
    return ((tMissionCleanupEntity * (__thiscall*)(CMissionCleanup*))0x4637C0)(this);
}

// Adds entity to list
// 0x4637E0
void CMissionCleanup::AddEntityToList(int32 handle, MissionCleanUpEntityType type)
{
    ((void(__thiscall*)(CMissionCleanup*, int32, MissionCleanUpEntityType))0x4637E0)(this, handle, type);
}

// Remotes entity from list
// 0x4654B0
void CMissionCleanup::RemoveEntityFromList(int32 handle, MissionCleanUpEntityType type)
{
    ((void(__thiscall*)(CMissionCleanup*, int32, MissionCleanUpEntityType))0x4654B0)(this, handle, type);
}

// Checks if collision has loaded for mission objects
// 0x4652D0
void CMissionCleanup::CheckIfCollisionHasLoadedForMissionObjects()
{
    ((void(__thiscall*)(CMissionCleanup*))0x4652D0)(this);
}
