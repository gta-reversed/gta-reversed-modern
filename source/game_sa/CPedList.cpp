#include "StdInc.h"
#include "CPedList.h"

void CPedList::InjectHooks() {
    ReversibleHooks::Install("CPedList", "Empty", 0x699DB0, &CPedList::Empty);
    ReversibleHooks::Install("CPedList", "BuildListFromGroup_NoLeader", 0x699DD0, &CPedList::BuildListFromGroup_NoLeader);
    ReversibleHooks::Install("CPedList", "ExtractPedsWithGuns", 0x69A4C0, &CPedList::ExtractPedsWithGuns);
}

// 0x699DB0
void CPedList::Empty() {
    m_count = 0;
    memset(m_peds, 0, sizeof(m_peds));
}

void CPedList::ClearUnused() {
    if (m_count < GetCapacity()) {
        memset(m_peds[m_count], 0, sizeof(m_peds[0]) * (GetCapacity() - m_count));
    }
}

uint32_t CPedList::GetCapacity() const {
    return ARRAYSIZE(m_peds);
}

void CPedList::AddMember(CPed* ped) {
    if (m_count < GetCapacity())
        m_peds[m_count++] = ped;
    else {
        assert(0); // NOTSA
    }
}

void CPedList::RemoveMemberNoFill(int i) {
    m_peds[i] = nullptr;
    m_count--;
    // Must call FillUpHoles afterwards!
}

CPed* CPedList::Get(int i) {
    return m_peds[i];
}

// 0x699DD0
void CPedList::BuildListFromGroup_NoLeader(CPedGroupMembership& groupMembership) {
    m_count = 0;
    for (int i = 0; i < 7; i++) { // TODO: Why 7?
        if (CPed* ped = groupMembership.GetMember(i)) {
            AddMember(ped);
        }
    }
    ClearUnused();
}

void CPedList::FillUpHoles() {
    CPed** copyTo = begin();
    for (CPed** it = begin(); it != end(); it++) {
        if (copyTo != it && *it) { // NOTSA: `copyTo != it` is important to avoid UB
            *copyTo++ = *it;
        }
    }
    ClearUnused(); // Note: Original code differs a little, but does the same thing.
}

// 0x69A4C0
void CPedList::ExtractPedsWithGuns(CPedList& from) {
    for (int i = 0; i < from.m_count; i++) {
        if (!from.Get(i)->GetActiveWeapon().IsTypeMelee()) {
            AddMember(from.Get(i));
            from.RemoveMemberNoFill(i);
        }
    }
    from.FillUpHoles();
}
