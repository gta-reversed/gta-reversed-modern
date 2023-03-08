#include "StdInc.h"

#include <functional>
#include "PedGroupMembership.h"

// 0x5F6930
CPedGroupMembership::CPedGroupMembership() {
    std::ranges::fill(m_apMembers, nullptr);
    m_fSeparationRange = 60.0f;
}

// 0x5FB140
CPedGroupMembership::CPedGroupMembership(const CPedGroupMembership& obj) {
    From(obj);
}

CPedGroupMembership::~CPedGroupMembership() {
    Flush();
}

// 0x5F7FE0
void CPedGroupMembership::From(const CPedGroupMembership& obj) {
    for (auto i = 0; i < TOTAL_PED_GROUP_MEMBERS; i++) {
        AddMember(obj.m_apMembers[i], i);
    }
    m_pPedGroup        = obj.m_pPedGroup;
    m_fSeparationRange = obj.m_fSeparationRange;
}

void CPedGroupMembership::AddFollower(CPed* ped) {
    plugin::CallMethod<0x5F8020, CPedGroupMembership*, CPed*>(this, ped);
}

// 0x5F6AE0
void CPedGroupMembership::AddMember(CPed* member, int32 memberID) {
    plugin::CallMethod<0x5F6AE0, CPedGroupMembership*, CPed*, int32>(this, member, memberID);
}

void CPedGroupMembership::AppointNewLeader() {
    plugin::CallMethod<0x5FB240, CPedGroupMembership*>(this);
}

// 0x5F6A50
size_t CPedGroupMembership::CountMembers() {
    return rng::count_if(m_apMembers, notsa::NotIsNull{});
}

// 0x5F6AA0
int32 CPedGroupMembership::CountMembersExcludingLeader() {
    // Last member is the leader
    return rng::count_if(m_apMembers | rng::views::drop(1), notsa::NotIsNull{});
}

// 0x5FB160
void CPedGroupMembership::Flush() {
    for (auto i = 0u; i < m_apMembers.size(); i++) {
        RemoveMember(i);
    }
}

CPed* CPedGroupMembership::GetLeader() const {
    return m_apMembers[7];
}

// 0x5F69B0
CPed* CPedGroupMembership::GetMember(int32 memberId) {
    return m_apMembers[memberId];
}

// 0x5F69E0
bool CPedGroupMembership::IsFollower(const CPed* ped) const {
    return !IsLeader(ped) && IsMember(ped);
}

// 0x5F69C0
bool CPedGroupMembership::IsLeader(const CPed* ped) const {
    return ped && GetLeader() == ped;
}

// 0x5F6A10
bool CPedGroupMembership::IsMember(const CPed* ped) const {
    return ped && notsa::contains(m_apMembers, ped);
}

// 0x5FBA60
void CPedGroupMembership::Process() {
    plugin::CallMethod<0x5FBA60, CPedGroupMembership*>(this);
}

// 0x5FB190
void CPedGroupMembership::RemoveAllFollowers(bool bCreatedByGameOnly) {
    plugin::CallMethod<0x5FB190, CPedGroupMembership*, bool>(this, bCreatedByGameOnly);
}

// 0x5F80D0
void CPedGroupMembership::RemoveMember(int32 memberID) {
    plugin::CallMethod<0x5F80D0, CPedGroupMembership*, int32>(this, memberID);
}

// 0x5FB1D0
char CPedGroupMembership::RemoveNFollowers(int32 count) {
    return plugin::CallMethodAndReturn<char, 0x5FB1D0, CPedGroupMembership*, int32>(this, count);
}

// 0x5FB9C0
void CPedGroupMembership::SetLeader(CPed* ped) {
    plugin::CallMethod<0x5FB9C0, CPedGroupMembership*, CPed*>(this, ped);
}

// 0x5F6950
int32 CPedGroupMembership::GetObjectForPedToHold() {
    return plugin::CallAndReturn<int32, 0x5F6950>();
}

bool CPedGroupMembership::CanAddFollower() {
    return std::size(m_apMembers) > CountMembers();
}

CPed* CPedGroupMembership::GetRandom() {
    return CGeneral::RandomChoice(m_apMembers | rng::views::take(CountMembers()));
}

void CPedGroupMembership::InjectHooks() {
    RH_ScopedClass(CPedGroupMembership);
    RH_ScopedCategory(); // TODO: Change this to the appropriate category!

    RH_ScopedOverloadedInstall(Constructor, "", 0x5F6930, CPedGroupMembership * (CPedGroupMembership::*)());
    //RH_ScopedOverloadedInstall(Constructor, "", 0x5FB140, CPedGroupMembership * (CPedGroupMembership::*)(CPedGroupMembership const&)); // copy ctor

    RH_ScopedGlobalInstall(GetObjectForPedToHold, 0x5F6950, {.reversed = false});

    RH_ScopedInstall(AppointNewLeader, 0x5FB240, {.reversed = false});
    //RH_ScopedOverloadedInstall(RemoveMember, "ByPed", 0x5FB210, void(CPedGroupMembership::*)(CPed*), {.reversed = false});
    RH_ScopedInstall(RemoveNFollowers, 0x5FB1D0, {.reversed = false});
    RH_ScopedInstall(RemoveAllFollowers, 0x5FB190, {.reversed = false});
    RH_ScopedOverloadedInstall(RemoveMember, "ByMemIdx", 0x5F80D0, void(CPedGroupMembership::*)(int32), {.reversed = false});
    RH_ScopedInstall(AddFollower, 0x5F8020, {.reversed = false});
    RH_ScopedInstall(From, 0x5F7FE0, {.reversed = false});
    RH_ScopedInstall(AddMember, 0x5F6AE0, {.reversed = false});
    RH_ScopedInstall(CountMembersExcludingLeader, 0x5F6AA0, {.reversed = false});
    RH_ScopedInstall(CountMembers, 0x5F6A50, {.reversed = false});

    RH_ScopedInstall(IsMember, 0x5F6A10);
    RH_ScopedInstall(IsFollower, 0x5F69E0);
    RH_ScopedInstall(IsLeader, 0x5F69C0);

    RH_ScopedInstall(GetMember, 0x5F69B0, {.reversed = false});

    RH_ScopedInstall(GetLeader, 0x5F69A0, {.reversed = false});
    RH_ScopedInstall(SetLeader, 0x5FB9C0, {.reversed = false});

    RH_ScopedInstall(Process, 0x5FBA60, {.reversed = false});
}
