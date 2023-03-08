#include "StdInc.h"

#include <functional>
#include "PedGroupMembership.h"

// 0x5F6930
CPedGroupMembership::CPedGroupMembership() {
    std::ranges::fill(m_apMembers, nullptr);
    m_fSeparationRange = 60.0f;
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

// 0x5F8020
void CPedGroupMembership::AddFollower(CPed* ped) {
    ped->bHasGroupDriveTask = false;

    // Peds in the player's group can't drown
    if (const auto leader = GetLeader()) {
        if (leader->IsPlayer()) { // same effect as m_pPlayerData, no?
            assert(leader->m_pPlayerData); // Test above theory
            ped->bDrownsInWater = false;
        }
    }

    if (IsFollower(ped) || GetLeader() == ped) { // TODO/BUG/NOTE: Stuff that was set above is now not reverted... I'm not sure if that's intended
        return;
    }

    const auto memId = FindIdForNewMember();
    if (memId == -1) {
        return;
    }

    AddMember(ped, memId);
    GivePedRandomObjectToHold(ped);
}

// 0x5F6AE0
void CPedGroupMembership::AddMember(CPed* member, int32 memberID) {
    /* dead code before checking if the member is in the player's group */
    if (!member->IsPlayer()) {
        member->GetIntelligence()->SetPedDecisionMakerType(0);
    }
}

void CPedGroupMembership::AppointNewLeader() {
    if (HasLeader()) {
        return;
    }

    const auto memId = FindNewLeaderToAppoint();
    if (memId == -1) {
        return;
    }

    RemoveMember(memId); // Must call as it does some cleanup
    AddMember(m_apMembers[memId], LEADER_MEM_ID);
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
    return m_apMembers[LEADER_MEM_ID];
}

// 0x5F69B0
CPed* CPedGroupMembership::GetMember(int32 memberId) {
    return m_apMembers[memberId];
}

int32 CPedGroupMembership::GetMemberId(const CPed* ped) const {
    for (auto&& [id, mem] : notsa::enumerate(m_apMembers)) {
        if (mem == ped) {
            return id;
        }
    }
    return -1;
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
    // Remove dead members (except player ped)
    for (auto&& [i, mem] : notsa::enumerate(m_apMembers)) {
        if (mem->IsAlive()) {
            continue;
        }
        if (IsLeader(mem) && mem->IsPlayer()) { // Player always stays in it's group
            continue;
        }
        RemoveMember(i);
    }

    // If no leader, try appointing a new one
    if (!HasLeader()) {
        AppointNewLeader();
        if (!HasLeader()) { // Couldn't appoint a new leader
            return;
        }
    }

    // Now that we have a leader, check for separation distance and remove members further than it
    const auto leaderPos = GetLeader()->GetPosition();
    for (auto&& [i, mem] : notsa::enumerate(m_apMembers)) {
        if (mem->bNeverLeavesGroup) {
            continue;
        }
        if (IsLeader(mem)) { // Leader's distance to itself always 0, thus ignore
            continue;
        }
        if (sq(m_fSeparationRange) >= (leaderPos - mem->GetPosition()).SquaredMagnitude()) {
            continue;
        }
        RemoveMember(i); // Ped is too far
    }
}

// 0x5FB190
void CPedGroupMembership::RemoveAllFollowers(bool bCreatedByMissionOnly) {
    for (auto&& [i, mem] : notsa::enumerate(m_apMembers)) {
        if (IsLeader(mem)) { // Leader isn't a follower
            continue;
        }
        if (bCreatedByMissionOnly && mem->IsCreatedBy(PED_MISSION)) {
            continue;
        }
        RemoveMember(i);
    }
}

// 0x5FB1D0
void CPedGroupMembership::RemoveNFollowers(size_t count) {
    if (count == 0) { // Nothing to do
        return;
    }
    for (auto&& [i, mem] : notsa::enumerate(m_apMembers)) {
        if (IsLeader(mem)) { // Leader isn't a follower
            continue;
        }
        if (mem->IsCreatedBy(PED_MISSION)) {
            continue;
        }
        RemoveMember(i);
        if (!--count) {
            break;
        }
    }
}

// 0x5F80D0
void CPedGroupMembership::RemoveMember(int32 memIdx) {
    const auto mem = m_apMembers[memIdx];
    assert(mem);

    CEntity::ClearReference(m_apMembers[memIdx]); // Does `m_apMembers[memIdx] = nullptr`

    if (mem->IsPlayer()) {
        return;
    }

    if (mem->bClearRadarBlipOnDeath) {
        CRadar::ClearBlipForEntity(mem);
        mem->bClearRadarBlipOnDeath = false;
    }

    mem->GetIntelligence()->RestorePedDecisionMakerType();

    if (const auto leader = GetLeader()) {
        if (const auto plyrdat = leader->m_pPlayerData) {
            mem->bDrownsInWater = true;
        }
    }
}

// 0x5FB210
void CPedGroupMembership::RemoveMember(CPed* ped) {
    if (const auto id = GetMemberId(ped); id != -1) {
        RemoveMember(id);
    }
}

// 0x5FB9C0
void CPedGroupMembership::SetLeader(CPed* ped) {
    assert(ped);

    // Remove member (Just in case he's in the group already)
    RemoveMember(ped);

    // Remov the current leader (If any)
    if (GetLeader()) {
        RemoveMember(GetLeader());
    }

    // Now add member as the leader
    AddMember(ped, LEADER_MEM_ID);
    GivePedRandomObjectToHold(ped);
}

auto CPedGroupMembership::FindClosestFollowerToLeader() -> FindMemberResult {
    if (const auto leader = GetLeader()) {
        return GetMemberClosestTo(leader);
    }
    return { nullptr, 0.f }; // We return 0.f here, `GetMemberClosestTo` returns FLT_MAX, but it should be ignored anyways, because the CPed* is nullptr
}

// 0x5F6950
eModelID CPedGroupMembership::GetObjectForPedToHold() {
    using namespace ModelIndices;
    return CGeneral::RandomChoiceFromList({ (eModelID)MI_GANG_SMOKE, MODEL_INVALID, (eModelID)MI_GANG_DRINK }); // Each has 33% chance
}

int32 CPedGroupMembership::FindNewLeaderToAppoint() const {
    for (auto&& [i, mem] : notsa::enumerate(m_apMembers)) {
        if (mem) {
            return i;
        }
    }
    return -1;
}

int32 CPedGroupMembership::FindIdForNewMember() const {
    for (auto&& [i, mem] : notsa::enumerate(m_apMembers)) {
        if (!mem) {
            return i;
        }
    }
    return -1;
}

void CPedGroupMembership::GivePedRandomObjectToHold(CPed* mem, bool onlyIfUnarmed) const {
    if (m_pPedGroup->m_bIsMissionGroup) {
        return;
    }
    if (onlyIfUnarmed && !mem->IsCurrentlyUnarmed()) {
        return;
    }
    if (const auto modelId = GetObjectForPedToHold(); modelId != MODEL_INVALID) {
        mem->GiveObjectToPedToHold(modelId, true);
    }
}

bool CPedGroupMembership::CanAddFollower() {
    return std::size(m_apMembers) - 1 >= CountMembers(); // - 1 to compensate for leader
}

CPed* CPedGroupMembership::GetRandom() {
    return CGeneral::RandomChoice(m_apMembers | rng::views::take(CountMembers()));
}

void CPedGroupMembership::InjectHooks() {
    RH_ScopedClass(CPedGroupMembership);
    RH_ScopedCategory(); // TODO: Change this to the appropriate category!

    RH_ScopedOverloadedInstall(Constructor, "", 0x5F6930, CPedGroupMembership * (CPedGroupMembership::*)());
    //RH_ScopedOverloadedInstall(Constructor, "", 0x5FB140, CPedGroupMembership * (CPedGroupMembership::*)(CPedGroupMembership const&)); // copy ctor

    RH_ScopedGlobalInstall(GetObjectForPedToHold, 0x5F6950);

    RH_ScopedInstall(From, 0x5F7FE0, {.reversed = false});

    RH_ScopedInstall(CountMembersExcludingLeader, 0x5F6AA0, {.reversed = false});
    RH_ScopedInstall(CountMembers, 0x5F6A50, {.reversed = false});

    RH_ScopedInstall(IsMember, 0x5F6A10);
    RH_ScopedInstall(IsFollower, 0x5F69E0);
    RH_ScopedInstall(IsLeader, 0x5F69C0);

    RH_ScopedInstall(GetMember, 0x5F69B0);
    RH_ScopedInstall(AddMember, 0x5F6AE0, {.reversed = false});

    RH_ScopedInstall(AddFollower, 0x5F8020, {.reversed = false});

    RH_ScopedInstall(GetLeader, 0x5F69A0);
    RH_ScopedInstall(SetLeader, 0x5FB9C0);
    RH_ScopedInstall(AppointNewLeader, 0x5FB240, {.reversed = false});

    RH_ScopedInstall(RemoveNFollowers, 0x5FB1D0);
    RH_ScopedInstall(RemoveAllFollowers, 0x5FB190);
    RH_ScopedOverloadedInstall(RemoveMember, "ByPed", 0x5FB210, void(CPedGroupMembership::*)(CPed*));
    RH_ScopedOverloadedInstall(RemoveMember, "ByMemIdx", 0x5F80D0, void(CPedGroupMembership::*)(int32));

    RH_ScopedInstall(Process, 0x5FBA60);
}
