/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPedGroupMembership.h"
#include "CPedGroupIntelligence.h"
#include "CVector.h"
#include "CPed.h"
#include "CVehicle.h"

class  CPedGroup {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CPedGroup)

public:
    int field_0;
    bool m_bMembersEnterLeadersVehicle;
private:
    char _pad5[3];
public:
    CPedGroupMembership m_groupMembership;
    float m_fSeparationRange;
    CPedGroupIntelligence m_groupIntelligence;

     float FindDistanceToFurthestMember();
     float FindDistanceToNearestMember(CPed **ppOutNearestMember);
     void Flush();
     CPed *GetClosestGroupPed(CPed *ped, float *pOutDistance);
     bool IsAnyoneUsingCar(CVehicle const *vehicle);
     void PlayerGaveCommand_Attack(CPed *playerPed, CPed *ped);
     void PlayerGaveCommand_Gather(CPed *ped);
     void Process();
     void RemoveAllFollowers();
     void Teleport(CVector const *Pos);
};

VALIDATE_SIZE(CPedGroup, 0x2D4);

//#include "meta/meta.CPedGroup.h"
