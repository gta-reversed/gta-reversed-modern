/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CEntryExit.h"
#include "CVector.h"
#include "CVector2D.h"
#include "CEntity.h"
#include "CQuadTreeNode.h"

class CEntryExitManager {
public:
    static CEntryExit* (&ms_entryExitStack)[4]; // static CEntryExit *ms_entryExitStack[4]
    static bool& ms_bBurglaryHousesEnabled;
    static int& ms_oldAreaCode;
    static CEntity* (&ms_visibleEntityList)[32]; // static CEntity *ms_visibleEntityList[32]
    static int& ms_entryExitStackPosn;
    static bool& ms_bDisabled;
    static int& ms_exitEnterState;
    static CQuadTreeNode*& mp_QuadTree;
    static CEntryExit*& mp_Active;
    static CPool<CEntryExit>*& mp_poolEntryExits;
    static unsigned int& ms_numVisibleEntities;

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void Shutdown();
    static void ShutdownForRestart();

    static void AddEntryExitToStack(CEntryExit* a1);
    static int AddOne(float entranceX, float entranceY, float entranceZ, float entranceAngle, float entranceRangeX, float entranceRangeY, float fUnused, float exitX, float exitY, float exitZ, float exitAngle, int area, int flags, int skyColor, int timeOn, int timeOff, int numberOfPeds, char const* name);
    static void DeleteOne(int index);
    static void EnableBurglaryHouses(bool enable);
    static CEntity* FindNearestDoor(CEntryExit const& entryExit, float range);
    static int FindNearestEntryExit(CVector2D const& position, float range, int ignoreArea);
    static CEntryExit* GetEntryExit(int index);
    static int GetEntryExitIndex(char const* name, unsigned short enabledFlags, unsigned short disabledFlags);
    static void GetPositionRelativeToOutsideWorld(CVector& positionInOut);
    static void GotoEntryExit(CEntryExit* entryExit);
    static void GotoEntryExitVC(char const* name);
    static void GotoNextEntryExit();
    static void GotoPreviousEntryExit();
    static void LinkEntryExit(CEntryExit* entryExit);
    static bool Load();
    static bool Save();
    static void PostEntryExitsCreation();
    static void ResetAreaCodeForVisibleObjects();
    static void SetAreaCodeForVisibleObjects();
    static void SetEnabled(int index, bool enable);
    static void SetEnabledByName(char const* name, bool enable);
    static void SetEntryExitFlag(char const* name, unsigned int flag, bool enable);
    static void SetEntryExitFlagWithIndex(int index, unsigned int flag, bool enable);
    static bool WeAreInInteriorTransition();
};

//#include "meta/meta.CEntryExitManager.h"
