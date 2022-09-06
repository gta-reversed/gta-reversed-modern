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

CPed* CPedGroupMembership::GetLeader() {
    return m_apMembers[7];
}

// 0x5F69B0
CPed* CPedGroupMembership::GetMember(int32 memberId) {
    return m_apMembers[memberId];
}

// 0x5F69E0
bool CPedGroupMembership::IsFollower(const CPed* ped) const {
    return plugin::CallMethodAndReturn<bool, 0x5F69E0, const CPedGroupMembership*, const CPed*>(this, ped);
}

// 0x5F69C0
bool CPedGroupMembership::IsLeader(const CPed* ped) {
    return ped && GetLeader() == ped;
}

// 0x5F6A10
bool CPedGroupMembership::IsMember(const CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x5F6A10, CPedGroupMembership*, const CPed*>(this, ped);
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

auto CPedGroupMembership::GetMemberClosestTo(CPed* ped) -> std::tuple<CPed*, float> {
    const auto& pedPos = ped->GetPosition();

    float closestDistSq{std::numeric_limits<float>::max()};
    CPed* closest{};
    for (auto& mem : GetMembers()) {
        if (&mem == ped) {
            continue;
        }

        if (const auto distSq = (pedPos - mem.GetPosition()).SquaredMagnitude(); closestDistSq > distSq) {
            closestDistSq = distSq;
            closest = &mem;
        }
    }

    return { closest, closestDistSq };
}
