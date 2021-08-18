#include "StdInc.h"
#include "CPedList.h"

void CPedList::InjectHooks() {
    ReversibleHooks::Install("CPedList", "Empty", 0x699DB0, &CPedList::Empty);
    // ReversibleHooks::Install("CPedList", "BuildListFromGroup_NoLeader", 0x699DD0, &CPedList::BuildListFromGroup_NoLeader);
    // ReversibleHooks::Install("CPedList", "ExtractPedsWithGuns", 0x69A4C0, &CPedList::ExtractPedsWithGuns);
}

// 0x699DB0
void CPedList::Empty() {
    m_count = 0;
    memset(m_peds, 0, sizeof(m_peds));
}

// 0x699DD0
void CPedList::BuildListFromGroup_NoLeader(CPedGroupMembership& groupMembership) {
    plugin::CallMethod<0x699DD0, CPedList*, CPedGroupMembership&>(this, groupMembership);
}

// 0x69A4C0
void CPedList::ExtractPedsWithGuns(CPedList& from) {
    plugin::CallMethod<0x69A4C0, CPedList*, CPedList&>(this, from);
}
