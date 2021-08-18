/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPed.h"
#include "CPedGroupMembership.h"

class CPedList {
public:
    uint32_t m_count = {};
    CPed* m_peds[30] = {};

public:
    static void InjectHooks();

    void Empty();
    void BuildListFromGroup_NoLeader(CPedGroupMembership& groupMembership);
    void ExtractPedsWithGuns(CPedList& pFrom);
    void ClearUnused();
    void AddMember(CPed* ped);
    void RemoveMemberNoFill(int i);
    CPed* Get(int i);
    uint32_t GetCapacity() const;

    // Inlined functions below (Present in Android version)
    void FillUpHoles();
    void BuildListFromGroup_NotInCar_NoLeader(CPedGroupMembership* pedGroupMembership);
    void BuildListOfPedsOfPedType(int pedtype);
    void RemovePedsAttackingPedType(int pedtype);
    void RemovePedsThatDontListenToPlayer();

    CPed** begin() { return m_peds; }
    CPed** end() { return m_peds + GetCapacity(); }
};
VALIDATE_SIZE(CPedList, 0x7C);
