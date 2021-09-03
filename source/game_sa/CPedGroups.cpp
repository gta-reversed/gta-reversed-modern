#include "StdInc.h"

int16(&CPedGroups::ScriptReferenceIndex)[8] = *reinterpret_cast<int16(*)[8]>(0xC098D0);
char(&CPedGroups::ms_activeGroups)[8] = *reinterpret_cast<char(*)[8]>(0xC098E0);
bool& CPedGroups::ms_bIsPlayerOnAMission = *reinterpret_cast<bool*>(0xC098E8);
uint32& CPedGroups::ms_iNoOfPlayerKills = *reinterpret_cast<uint32*>(0xC098EC);
CPedGroup(&CPedGroups::ms_groups)[8] = *reinterpret_cast<CPedGroup(*)[8]>(0xC09920);

void CPedGroups::InjectHooks() {

}

// 0x5FB8C0
void CPedGroups::Init() {
    plugin::Call<0x5FB8C0>();
}

// 0x5F7F40
bool CPedGroups::AreInSameGroup(CPed* ped1, CPed* ped2) {
    return plugin::CallAndReturn<bool, 0x5F7F40, CPed*, CPed*>(ped1, ped2);
}

// 0x5F7E80
CPedGroup* CPedGroups::GetPedsGroup(CPed* ped) {
    return plugin::CallAndReturn<CPedGroup*, 0x5F7E80, CPed*>(ped);
}

bool CPedGroups::IsInPlayersGroup(CPed* ped)
{
    return plugin::CallAndReturn<bool, 0x5F7F10, CPed*>(ped);
}
