/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPedGroupMembership.h"
#include "CPedGroupIntelligence.h"
#include "CVector.h"
#include "CPed.h"
#include "CVehicle.h"

class CPedGroup {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CPedGroup)

public:
    CPed*                 field_0;
    bool                  m_bMembersEnterLeadersVehicle;
    char                  _pad5[3];
    CPedGroupMembership   m_groupMembership;
    float                 m_fSeparationRange;
    CPedGroupIntelligence m_groupIntelligence;
    bool                  m_bIsMissionGroup;
    char                  field_2D1[3];

public:
    float FindDistanceToFurthestMember();
    float FindDistanceToNearestMember(CPed** ppOutNearestMember);
    void  Flush();
    CPed* GetClosestGroupPed(CPed* ped, float* pOutDistance);
    bool  IsAnyoneUsingCar(CVehicle const* vehicle);
    void  PlayerGaveCommand_Attack(CPed* playerPed, CPed* ped);
    void  PlayerGaveCommand_Gather(CPed* ped);
    void  Process();
    void  RemoveAllFollowers();
    void  Teleport(CVector const* Pos);

    inline CPedGroupIntelligence& GetIntelligence() { return m_groupIntelligence; }
    inline CPedGroupMembership& GetMembership() { return m_groupMembership; }
};

VALIDATE_SIZE(CPedGroup, 0x2D4);
