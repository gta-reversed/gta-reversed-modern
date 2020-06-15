#include "StdInc.h"

void CPedGroupMembership::AddFollower(CPed* ped) {
    plugin::CallMethodDynGlobal<CPedGroupMembership*, CPed*>(0x5F8020, this, ped);
}

void CPedGroupMembership::AddMember(CPed* member, int memberID) {
    plugin::CallMethodDynGlobal<CPedGroupMembership*, CPed*, int>(0x5F6AE0, this, member, memberID);
}

void CPedGroupMembership::AppointNewLeader() {
    plugin::CallMethodDynGlobal<CPedGroupMembership*>(0x5FB240, this);
}

int CPedGroupMembership::CountMembers() {
    return plugin::CallMethodAndReturnDynGlobal<int, CPedGroupMembership*>(0x5F6A50, this);
}

int CPedGroupMembership::CountMembersExcludingLeader() {
    return plugin::CallMethodAndReturnDynGlobal<int, CPedGroupMembership*>(0x5F6AA0, this);
}

void CPedGroupMembership::Flush() {
    plugin::CallMethodDynGlobal<CPedGroupMembership*>(0x5FB160, this);
}

void CPedGroupMembership::From(CPedGroupMembership const* obj) {
    plugin::CallMethodDynGlobal<CPedGroupMembership*, CPedGroupMembership const*>(0x5F7FE0, this, obj);
}

CPed* CPedGroupMembership::GetLeader() {
    return plugin::CallMethodAndReturnDynGlobal<CPed*, CPedGroupMembership*>(0x5F69A0, this);
}

CPed* CPedGroupMembership::GetMember(int memberId) {
    return plugin::CallMethodAndReturnDynGlobal<CPed*, CPedGroupMembership*, int>(0x5F69B0, this, memberId);
}

bool CPedGroupMembership::IsFollower(CPed const* ped) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CPedGroupMembership*, CPed const*>(0x5F69E0, this, ped);
}

bool CPedGroupMembership::IsLeader(CPed const* ped) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CPedGroupMembership*, CPed const*>(0x5F69C0, this, ped);
}

bool CPedGroupMembership::IsMember(CPed const* ped) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CPedGroupMembership*, CPed const*>(0x5F6A10, this, ped);
}

void CPedGroupMembership::Process() {
    plugin::CallMethodDynGlobal<CPedGroupMembership*>(0x5FBA60, this);
}

void CPedGroupMembership::RemoveAllFollowers(bool bCreatedByGameOnly) {
    plugin::CallMethodDynGlobal<CPedGroupMembership*, bool>(0x5FB190, this, bCreatedByGameOnly);
}

void CPedGroupMembership::RemoveMember(int memberID) {
    plugin::CallMethodDynGlobal<CPedGroupMembership*, int>(0x5F80D0, this, memberID);
}

char CPedGroupMembership::RemoveNFollowers(int count) {
    return plugin::CallMethodAndReturnDynGlobal<char, CPedGroupMembership*, int>(0x5FB1D0, this, count);
}

void CPedGroupMembership::SetLeader(CPed* ped) {
    plugin::CallMethodDynGlobal<CPedGroupMembership*, CPed*>(0x5FB9C0, this, ped);
}

signed int CPedGroupMembership::GetObjectForPedToHold() {
    return plugin::CallAndReturnDynGlobal<signed int>(0x5F6950);
}
