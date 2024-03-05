#include "StdInc.h"

#include "PedGroups.h"

void CPedGroups::InjectHooks() {
    RH_ScopedClass(CPedGroups);
    RH_ScopedCategory("Ped Groups");

    RH_ScopedInstall(AddGroup, 0x5FB800);
    RH_ScopedInstall(RemoveGroup, 0x5FB870);
    RH_ScopedInstall(RemoveAllFollowersFromGroup, 0x5FB8A0);
    RH_ScopedInstall(Init, 0x5FB8C0);
    RH_ScopedInstall(RegisterKillByPlayer, 0x5F7E30);
    RH_ScopedInstall(CleanUpForShutDown, 0x5FB930, {.reversed=false});
    RH_ScopedInstall(IsGroupLeader, 0x5F7E40, {.reversed=false});
    RH_ScopedInstall(GetPedsGroup, 0x5F7E80, {.reversed=false});
    RH_ScopedInstall(GetGroupId, 0x5F7EE0, {.reversed=false});
    RH_ScopedInstall(Process, 0x5FC800, {.reversed=false});
    RH_ScopedInstall(AreInSameGroup, 0x5F7F40, {.reversed=false});
    RH_ScopedInstall(IsInPlayersGroup, 0x5F7F10, {.reversed=false});
    // RH_ScopedInstall(GetGroup, 0x0, {.reversed=false});
}

#ifdef ANDROID
void CPedGroups::Save() {
    
}

void CPedGroups::Load() {
    
}
#endif

// return the index of the added group , return -1 if failed.
// 0x5FB800
int32 CPedGroups::AddGroup() {
    const auto slot = FindFreeGroupSlot();
    if (slot == -1) {
        return -1;
    }

    ms_activeGroups[slot] = true;
    ms_groups[slot].Flush();
    return slot;
}

// 0x5FB870
void CPedGroups::RemoveGroup(int32 groupId) {
    if (ms_activeGroups[groupId]) {
        ms_activeGroups[groupId] = false;
        ms_groups[groupId].Flush();
    }
}

// 0x5FB8A0
void CPedGroups::RemoveAllFollowersFromGroup(int32 groupId) {
    if (ms_activeGroups[groupId]) {
        ms_groups[groupId].RemoveAllFollowers();
    }
}

// 0x5FB8C0
void CPedGroups::Init() {
    for (auto i = 0; i < NUM_PEDGROUPS; i++) {
        ScriptReferenceIndex[i] = 1;

        if (ms_activeGroups[i]) {
            ms_activeGroups[i] = false;
            for (auto& member : ms_groups[i].GetMembership().GetMembers()) {
                ms_groups[i].GetMembership().RemoveMember(&member);
            }
        }
    }
}

// 0x5F7E30
void CPedGroups::RegisterKillByPlayer() {
    if (ms_bIsPlayerOnAMission)
        ms_iNoOfPlayerKills++;
}

// 0x5FB930
void CPedGroups::CleanUpForShutDown() {
    plugin::Call<0x5FB930>();
}

// 0x5F7E40
bool CPedGroups::IsGroupLeader(CPed* ped) {
    return plugin::CallAndReturn<bool, 0x5F7E40, CPed*>(ped);
}

// 0x5F7E80
CPedGroup* CPedGroups::GetPedsGroup(const CPed* ped) {
    return plugin::CallAndReturn<CPedGroup*, 0x5F7E80>(ped);
}

// 0x5F7EE0
int32 CPedGroups::GetGroupId(const CPedGroup* pedGroup) {
    return plugin::CallAndReturn<int32, 0x5F7EE0, const CPedGroup*>(pedGroup);
}

// 0x5FC800
void CPedGroups::Process() {
    plugin::Call<0x5FC800>();
}

// 0x5F7F10
bool CPedGroups::IsInPlayersGroup(CPed* ped) {
    return plugin::CallAndReturn<bool, 0x5F7F10, CPed*>(ped);
}

CPedGroup& CPedGroups::GetGroup(int32 groupId) {
    return ms_groups[groupId];
}

// 0x5F7F40
bool CPedGroups::AreInSameGroup(const CPed* ped1, const CPed* ped2) {
    return plugin::CallAndReturn<bool, 0x5F7F40, const CPed*, const CPed*>(ped1, ped2);
}
