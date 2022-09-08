/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <ranges>
#include <concepts>

class CPed;
class CPedGroup;

const int32 TOTAL_PED_GROUP_MEMBERS = 8;
// -1 because every ped group has a leader, and the leader cannot be a follower
const int32 TOTAL_PED_GROUP_FOLLOWERS = TOTAL_PED_GROUP_MEMBERS - 1;

class CPedGroupMembership {
public:
    CPedGroup* m_pPedGroup;
    std::array<CPed*, TOTAL_PED_GROUP_MEMBERS> m_apMembers; // m_apMembers[7] is the leader
    float m_fSeparationRange;

    static const float& ms_fMaxSeparation;
    static const float& ms_fPlayerGroupMaxSeparation;

public:
    CPedGroupMembership();
    CPedGroupMembership(const CPedGroupMembership& from);
    ~CPedGroupMembership();

    void  AddFollower(CPed* ped);
    void  AddMember(CPed* member, int32 memberID);
    void  AppointNewLeader();
    size_t CountMembers();
    int32 CountMembersExcludingLeader();
    void  Flush();
    void  From(const CPedGroupMembership& obj);
    CPed* GetLeader();
    CPed* GetMember(int32 memberId);
    bool  IsFollower(const CPed* ped) const;
    bool  IsLeader(const CPed* ped);
    bool  IsMember(const CPed* ped);
    void  Process();
    void  RemoveAllFollowers(bool bCreatedByGameOnly);
    void  RemoveMember(int32 memberID);
    char  RemoveNFollowers(int32 count);
    void  SetLeader(CPed* ped);

    /// Get a random ped from the group. Might return null.
    CPed* GetRandom();

    /// Whenever `AddFollower` can be called to add a new follower
    bool CanAddFollower();

    /// Get all the members (including the leader)
    auto GetMembers() {
        return
            m_apMembers
            | rng::views::filter(notsa::NotIsNull{})
            | rng::views::transform([](CPed* mem) -> CPed& { return *mem; }); // Dereference
    }

    /*!
    * @notsa
    * @brief Find the member of this group closest to the ped.
    * 
    * @param ped  The ped to which the cloest member should be searched for
    * @param pred Custom predicate to filter members
    * 
    * @return The closest member (may be null, in which case the distance should be considered invalid), and it's sq. dist from `ped`
    */
    template<std::predicate<CPed&> Pred>
    auto GetMemberClosestToIf(CPed* ped, Pred&& pred) -> std::tuple<CPed*, float> {
        const auto& pedPos = ped->GetPosition();

        float closestDistSq{ std::numeric_limits<float>::max() };
        CPed* closest{};
        for (auto& mem : GetMembers()) {
            if (&mem == ped) {
                continue;
            }

            if (!std::invoke(pred, mem)) {
                continue;
            }

            if (const auto distSq = (pedPos - mem.GetPosition()).SquaredMagnitude(); closestDistSq > distSq) {
                closestDistSq = distSq;
                closest = &mem;
            }
        }

        return { closest, closestDistSq };
    }

    /// Wrapper around `GetMemberClosestToIf`, using an always-true predicate
    auto GetMemberClosestTo(CPed* ped) { return GetMemberClosestToIf(ped, [](CPed&) { return true; }); }

    static int32 GetObjectForPedToHold();
};

VALIDATE_SIZE(CPedGroupMembership, 0x28);
