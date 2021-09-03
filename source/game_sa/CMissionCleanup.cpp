/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"


// Default constructor
CMissionCleanup::CMissionCleanup()
{
    this->Init();
}

// Initializes data
void CMissionCleanup::Init()
{
    ((void(__thiscall*)(CMissionCleanup*)) FUNC_CMissionCleanup__Init)(this);
}

// Performs a clean-up
void CMissionCleanup::Process()
{
    ((void(__thiscall*)(CMissionCleanup*)) FUNC_CMissionCleanup__Process)(this);
}

// Finds a free entity, returns NULL if no free entity can be found.
tMissionCleanupEntity* CMissionCleanup::FindFree()
{
    return ((tMissionCleanupEntity * (__thiscall*)(CMissionCleanup*)) FUNC_CMissionCleanup__FindFree)(this);
}

// Adds entity to list
void CMissionCleanup::AddEntityToList(int32 handle, MissionCleanUpEntityType type)
{
    ((void(__thiscall*)(CMissionCleanup*, int32, MissionCleanUpEntityType)) FUNC_CMissionCleanup__AddEntityToList)(this, handle, type);
}

// Remotes entity from list
void CMissionCleanup::RemoveEntityFromList(int32 handle, MissionCleanUpEntityType type)
{
    ((void(__thiscall*)(CMissionCleanup*, int32, MissionCleanUpEntityType)) FUNC_CMissionCleanup__RemoveEntityFromList)(this, handle, type);
}

// Checks if collision has loaded for mission objects
void CMissionCleanup::CheckIfCollisionHasLoadedForMissionObjects()
{
    ((void(__thiscall*)(CMissionCleanup*)) FUNC_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects)(this);
}
