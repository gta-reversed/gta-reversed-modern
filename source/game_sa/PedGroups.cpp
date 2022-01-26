#include "StdInc.h"

#include "PedGroups.h"

int16 (&CPedGroups::ScriptReferenceIndex)[8] = *reinterpret_cast<int16 (*)[8]>(0xC098D0);
char (&CPedGroups::ms_activeGroups)[8] = *reinterpret_cast<char (*)[8]>(0xC098E0);
bool& CPedGroups::ms_bIsPlayerOnAMission = *reinterpret_cast<bool*>(0xC098E8);
uint32& CPedGroups::ms_iNoOfPlayerKills = *reinterpret_cast<uint32*>(0xC098EC);
CPedGroup (&CPedGroups::ms_groups)[8] = *reinterpret_cast<CPedGroup (*)[8]>(0xC09920);

void CPedGroups::InjectHooks() {
    RH_ScopedClass(CPedGroups);
    RH_ScopedCategoryGlobal();


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
    return plugin::CallAndReturn<int32, 0x5FB800>();
}

// 0x5FB870
void CPedGroups::RemoveGroup(int32 groupId) {
    plugin::Call<0x5FB870, int32>(groupId);
}

// 0x5FB8A0
void CPedGroups::RemoveAllFollowersFromGroup(int32 groupId) {
    plugin::Call<0x5FB8A0, int32>(groupId);
}

// 0x5FB8C0
void CPedGroups::Init() {
    plugin::Call<0x5FB8C0>();
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
CPedGroup* CPedGroups::GetPedsGroup(CPed* ped) {
    return plugin::CallAndReturn<CPedGroup*, 0x5F7E80, CPed*>(ped);
}

// 0x5F7EE0
int32 CPedGroups::GetGroupId(CPedGroup* pedGroup) {
    return plugin::CallAndReturn<int32, 0x5F7EE0, CPedGroup*>(pedGroup);
}

// 0x5FC800
void CPedGroups::Process() {
    plugin::Call<0x5FC800>();
}

// 0x5F7F10
bool CPedGroups::IsInPlayersGroup(CPed* ped) {
    return plugin::CallAndReturn<bool, 0x5F7F10, CPed*>(ped);
}

// 0x5F7F40
bool CPedGroups::AreInSameGroup(const CPed* ped1, const CPed* ped2) {
    return plugin::CallAndReturn<bool, 0x5F7F40, const CPed*, const CPed*>(ped1, ped2);
}
