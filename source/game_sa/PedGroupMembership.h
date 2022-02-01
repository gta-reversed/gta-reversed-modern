/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CPed;
class CPedGroup;

const int32 TOTAL_PED_GROUP_MEMBERS = 8;
// -1 because every ped group has a leader, and the leader cannot be a follower
const int32 TOTAL_PED_GROUP_FOLLOWERS = TOTAL_PED_GROUP_MEMBERS - 1;

class CPedGroupMembership {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CPedGroupMembership)

public:
    CPedGroup* m_pPedGroup;
    CPed*      m_apMembers[TOTAL_PED_GROUP_MEMBERS]; //!< m_apMembers[7] is a leader

    static float const& ms_fMaxSeparation;
    static float const& ms_fPlayerGroupMaxSeparation;

public:
    void  AddFollower(CPed* ped);
    void  AddMember(CPed* member, int32 memberID);
    void  AppointNewLeader();
    int32 CountMembers();
    int32 CountMembersExcludingLeader();
    void  Flush();
    //! copy constructor subfunction
    void  From(CPedGroupMembership const* obj);
    CPed* GetLeader();
    CPed* GetMember(int32 memberId);
    bool  IsFollower(CPed const* ped) const;
    bool  IsLeader(CPed const* ped);
    bool  IsMember(CPed const* ped);
    void  Process();
    void  RemoveAllFollowers(bool bCreatedByGameOnly);
    void  RemoveMember(int32 memberID);
    char  RemoveNFollowers(int32 count);
    void  SetLeader(CPed* ped);

    static signed int GetObjectForPedToHold();
};

VALIDATE_SIZE(CPedGroupMembership, 0x24);
