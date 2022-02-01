#include "StdInc.h"

#include "PedGroupMembership.h"

void CPedGroupMembership::AddFollower(CPed* ped) {
    plugin::CallMethod<0x5F8020, CPedGroupMembership*, CPed*>(this, ped);
}

void CPedGroupMembership::AddMember(CPed* member, int32 memberID) {
    plugin::CallMethod<0x5F6AE0, CPedGroupMembership*, CPed*, int32>(this, member, memberID);
}

void CPedGroupMembership::AppointNewLeader() {
    plugin::CallMethod<0x5FB240, CPedGroupMembership*>(this);
}

int32 CPedGroupMembership::CountMembers() {
    return plugin::CallMethodAndReturn<int32, 0x5F6A50, CPedGroupMembership*>(this);
}

int32 CPedGroupMembership::CountMembersExcludingLeader() {
    return plugin::CallMethodAndReturn<int32, 0x5F6AA0, CPedGroupMembership*>(this);
}

void CPedGroupMembership::Flush() {
    plugin::CallMethod<0x5FB160, CPedGroupMembership*>(this);
}

void CPedGroupMembership::From(CPedGroupMembership const* obj) {
    plugin::CallMethod<0x5F7FE0, CPedGroupMembership*, CPedGroupMembership const*>(this, obj);
}

CPed* CPedGroupMembership::GetLeader() {
    return plugin::CallMethodAndReturn<CPed*, 0x5F69A0, CPedGroupMembership*>(this);
}

CPed* CPedGroupMembership::GetMember(int32 memberId) {
    return plugin::CallMethodAndReturn<CPed*, 0x5F69B0, CPedGroupMembership*, int32>(this, memberId);
}

bool CPedGroupMembership::IsFollower(CPed const* ped) const {
    return plugin::CallMethodAndReturn<bool, 0x5F69E0, CPedGroupMembership const*, CPed const*>(this, ped);
}

bool CPedGroupMembership::IsLeader(CPed const* ped) {
    return plugin::CallMethodAndReturn<bool, 0x5F69C0, CPedGroupMembership*, CPed const*>(this, ped);
}

bool CPedGroupMembership::IsMember(CPed const* ped) {
    return plugin::CallMethodAndReturn<bool, 0x5F6A10, CPedGroupMembership*, CPed const*>(this, ped);
}

void CPedGroupMembership::Process() {
    plugin::CallMethod<0x5FBA60, CPedGroupMembership*>(this);
}

void CPedGroupMembership::RemoveAllFollowers(bool bCreatedByGameOnly) {
    plugin::CallMethod<0x5FB190, CPedGroupMembership*, bool>(this, bCreatedByGameOnly);
}

void CPedGroupMembership::RemoveMember(int32 memberID) {
    plugin::CallMethod<0x5F80D0, CPedGroupMembership*, int32>(this, memberID);
}

char CPedGroupMembership::RemoveNFollowers(int32 count) {
    return plugin::CallMethodAndReturn<char, 0x5FB1D0, CPedGroupMembership*, int32>(this, count);
}

void CPedGroupMembership::SetLeader(CPed* ped) {
    plugin::CallMethod<0x5FB9C0, CPedGroupMembership*, CPed*>(this, ped);
}

signed int CPedGroupMembership::GetObjectForPedToHold() {
    return plugin::CallAndReturn<signed int, 0x5F6950>();
}
