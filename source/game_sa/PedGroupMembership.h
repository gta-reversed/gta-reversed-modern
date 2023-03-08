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
    static constexpr int32 LEADER_MEM_ID = 7; ///< Leader member ID
public:
    CPedGroup* m_pPedGroup;
    std::array<CPed*, TOTAL_PED_GROUP_MEMBERS> m_apMembers; // m_apMembers[LEADER_MEM_ID] is the leader
    float m_fSeparationRange;

    static const float& ms_fMaxSeparation;
    static const float& ms_fPlayerGroupMaxSeparation;

public:
    static void InjectHooks();

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
    CPed* GetLeader() const;
    CPed* GetMember(int32 memberId);
    int32 GetMemberId(const CPed* ped) const;
    //! Is ped a follower (A member, but not the leader)
    bool  IsFollower(const CPed* ped) const;

    //! Is ped the leader
    bool  IsLeader(const CPed* ped) const;

    //! Is ped a member (follower or leader)
    bool  IsMember(const CPed* ped) const;

    void  Process();

    void  RemoveAllFollowers(bool bCreatedByGameOnly);
    void  RemoveMember(int32 memberID);
    void  RemoveMember(CPed* ped);
    char  RemoveNFollowers(int32 count);

    void  SetLeader(CPed* ped);

    /// Get a random ped from the group. Might return null.
    CPed* GetRandom();

    /// Whenever `AddFollower` can be called to add a new follower
    bool CanAddFollower();

    /// Get all the members (including the leader)
    auto GetMembers(bool bExcludeLeader = false) {
        assert(LEADER_MEM_ID == m_apMembers.size() - 1); // the drop below requires this
        return
            m_apMembers
            | rng::views::drop(bExcludeLeader ? 1 : 0) // Last member is the leader
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
                closest       = &mem;
            }
        }

        return { closest, closestDistSq };
    }

    /// Wrapper around `GetMemberClosestToIf`, using an always-true predicate
    auto GetMemberClosestTo(CPed* ped) { return GetMemberClosestToIf(ped, [](CPed&) { return true; }); }

    static int32 GetObjectForPedToHold();

private: // Wrappers for hooks
    // 0x5F6930
    CPedGroupMembership* Constructor() {
        this->CPedGroupMembership::CPedGroupMembership();
        return this;
    }
    //// 0x5FB140 
    //CPedGroupMembership* Constructor(CPedGroupMembership const& ojb) { // copy ctor
    //    this->CPedGroupMembership::CPedGroupMembership(ojb);
    //    return this;
    //}
};

VALIDATE_SIZE(CPedGroupMembership, 0x28);
