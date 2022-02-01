/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"
#include "Vector2D.h"

#include "Pool.h"

class QuadTreeNode;
class CEntryExit;
class CEntity;

class CEntryExitManager {
public:
    static CEntryExit* (&ms_entryExitStack)[4]; // static CEntryExit *ms_entryExitStack[4]
    static bool& ms_bBurglaryHousesEnabled;
    static int32& ms_oldAreaCode;
    static CEntity* (&ms_visibleEntityList)[32]; // static CEntity *ms_visibleEntityList[32]
    static int32& ms_entryExitStackPosn;
    static bool& ms_bDisabled;
    static int32& ms_exitEnterState;
    static CQuadTreeNode*& mp_QuadTree;
    static CEntryExit*& mp_Active;
    static CPool<CEntryExit>*& mp_poolEntryExits;
    static uint32& ms_numVisibleEntities;

public:
    static void InjectHooks();

    static void Init();
    static void Load();
    static void Save();
    static void Update();
    static void Shutdown();
    static void ShutdownForRestart();

    static void AddEntryExitToStack(CEntryExit* entryExit);
    static int32 AddOne(float entranceX, float entranceY, float entranceZ, float entranceAngle, float entranceRangeX, float entranceRangeY, float fUnused, float exitX, float exitY, float exitZ, float exitAngle, int32 area, int32 flags, int32 skyColor, int32 timeOn, int32 timeOff, int32 numberOfPeds, const char* name);
    static void DeleteOne(int32 index);
    static void EnableBurglaryHouses(bool enable);
    static CEntity* FindNearestDoor(CEntryExit const& entryExit, float range);
    static int32 FindNearestEntryExit(CVector2D const& position, float range, int32 ignoreArea);
    static CEntryExit* GetEntryExit(int32 index);
    static int32 GetEntryExitIndex(const char* name, uint16 enabledFlags, uint16 disabledFlags);
    static void GetPositionRelativeToOutsideWorld(CVector& positionInOut);
    static void GotoEntryExit(CEntryExit* entryExit);
    static void GotoEntryExitVC(const char* name);
    static void GotoNextEntryExit();
    static void GotoPreviousEntryExit();
    static void LinkEntryExit(CEntryExit* entryExit);
    static void PostEntryExitsCreation();
    static void ResetAreaCodeForVisibleObjects();
    static void SetAreaCodeForVisibleObjects();
    static void SetEnabled(int32 index, bool enable);
    static void SetEnabledByName(const char* name, bool enable);
    static void SetEntryExitFlag(const char* name, uint32 flag, bool enable);
    static void SetEntryExitFlagWithIndex(int32 index, uint32 flag, bool enable);
    static bool WeAreInInteriorTransition();
};
