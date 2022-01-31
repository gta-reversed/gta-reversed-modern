/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CPed;
class CPedGroup;

class CPedGroups {
public:
    static int16 (&ScriptReferenceIndex)[8]; // static int16 ScriptReferenceIndex[8]
    static char (&ms_activeGroups)[8];       // static char ms_activeGroups[8]
    static bool& ms_bIsPlayerOnAMission;
    static uint32& ms_iNoOfPlayerKills;
    static CPedGroup (&ms_groups)[8]; // static CPedGroup ms_groups[8]

public:
    static void InjectHooks();

    static int32 AddGroup();
    static void RemoveGroup(int32 groupID);
    static void RemoveAllFollowersFromGroup(int32 groupId);

    static void Init();

    static void RegisterKillByPlayer();

    static void CleanUpForShutDown();

    static bool IsGroupLeader(CPed* ped);

    static CPedGroup* GetPedsGroup(CPed* ped);
    static int32 GetGroupId(CPedGroup* pedGroup);

    static void Process();

    static bool AreInSameGroup(const CPed* ped1, const CPed* ped2);
    static bool IsInPlayersGroup(CPed* ped);

    // inlined
    static CPedGroup& GetGroup(int32 groupId);
};
