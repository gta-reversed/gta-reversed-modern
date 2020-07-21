#include "StdInc.h"

short(&CPedGroups::ScriptReferenceIndex)[8] = *reinterpret_cast<short(*)[8]>(0xC098D0);
char(&CPedGroups::ms_activeGroups)[8] = *reinterpret_cast<char(*)[8]>(0xC098E0);
bool& CPedGroups::ms_bIsPlayerOnAMission = *reinterpret_cast<bool*>(0xC098E8);
unsigned int& CPedGroups::ms_iNoOfPlayerKills = *reinterpret_cast<unsigned int*>(0xC098EC);
CPedGroup(&CPedGroups::ms_groups)[8] = *reinterpret_cast<CPedGroup(*)[8]>(0xC09920);

bool CPedGroups::AreInSameGroup(CPed* ped1, CPed* ped2) {
    return plugin::CallAndReturnDynGlobal<bool, CPed*, CPed*>(0x5F7F40, ped1, ped2);
}

CPedGroup* CPedGroups::GetPedsGroup(CPed* ped) {
    return plugin::CallAndReturnDynGlobal<CPedGroup*, CPed*>(0x5F7E80, ped);
}
