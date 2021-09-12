/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPed.h"
#include "CPedGroup.h"

class CPedGroups {
public:
    static int16 (&ScriptReferenceIndex)[8]; // static int16 ScriptReferenceIndex[8]
    static char (&ms_activeGroups)[8];       // static char ms_activeGroups[8]
    static bool& ms_bIsPlayerOnAMission;
    static uint32& ms_iNoOfPlayerKills;
    static CPedGroup (&ms_groups)[8]; // static CPedGroup ms_groups[8]

public:
    static void InjectHooks();

    static void Init();
    static CPedGroup& GetGroup(int32 groupId) { return ms_groups[groupId]; }
    //! return the index of the added group , return -1 if failed.
    static signed int AddGroup();
    static bool AreInSameGroup(CPed* ped1, CPed* ped2);
    static void CleanUpForShutDown();
    static signed int GetGroupId(CPedGroup* pedgrp);
    static CPedGroup* GetPedsGroup(CPed* ped);
    static bool IsGroupLeader(CPed* ped);
    static bool IsInPlayersGroup(CPed* ped);
    static void Process();
    static void RegisterKillByPlayer();
    static void RemoveAllFollowersFromGroup(int32 groupID);
    static void RemoveGroup(int32 groupID);
};
