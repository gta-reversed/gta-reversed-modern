/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PedGroupMembership.h"
#include "PedGroupIntelligence.h"

class CVector;
class CPed;
class CVehicle;

class CPedGroup {
public:
    CPed*                 m_pPed;
    bool                  m_bMembersEnterLeadersVehicle;
    CPedGroupMembership   m_groupMembership;
    CPedGroupIntelligence m_groupIntelligence;
    bool                  m_bIsMissionGroup;
    
public:
    static void InjectHooks();

    CPedGroup();
    ~CPedGroup();

    float FindDistanceToFurthestMember();

    //! Find follower closest to the leader
    float FindDistanceToNearestMember(CPed** ppOutNearestMember);
    void  Flush();
    CPed* GetClosestGroupPed(CPed* ped, float* pOutDistance);
    bool  IsAnyoneUsingCar(const CVehicle* vehicle);
    void  PlayerGaveCommand_Attack(CPed* playerPed, CPed* ped);
    void  PlayerGaveCommand_Gather(CPed* ped);
    void  Process();
    void  RemoveAllFollowers();
    void  Teleport(const CVector* pos);

    // NOTSA
    inline CPedGroupIntelligence& GetIntelligence() { return m_groupIntelligence; }

    int32 GetId() const;

    inline auto& GetMembership() const { return m_groupMembership; }
    inline auto& GetMembership() { return m_groupMembership; }

private: // Wrappers for hooks
    // 0x5FC150
    CPedGroup* Constructor() {
        this->CPedGroup::CPedGroup();
        return this;
    }

    // 0x5FC190
    CPedGroup* Destructor() {
        this->CPedGroup::~CPedGroup();
        return this;
    }
};
VALIDATE_SIZE(CPedGroup, 0x2D4);
