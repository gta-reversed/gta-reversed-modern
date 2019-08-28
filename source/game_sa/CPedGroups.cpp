#include "StdInc.h"

bool CPedGroups::AreInSameGroup(CPed* ped1, CPed* ped2) {
    return plugin::CallAndReturnDynGlobal<bool, CPed*, CPed*>(0x5F7F40, ped1, ped2);
}

CPedGroup* CPedGroups::GetPedsGroup(CPed* ped) {
    return plugin::CallAndReturnDynGlobal<CPedGroup*, CPed*>(0x5F7E80, ped);
}