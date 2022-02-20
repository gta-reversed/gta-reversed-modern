/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Base.h"

class CPedGroupMembership;
class CPed;

class CPedList {
public:
    uint32_t              m_count{};
    std::array<CPed*, 30> m_peds{};
public:
    static void InjectHooks();

    void Empty();
    void BuildListFromGroup_NoLeader(CPedGroupMembership& groupMembership);
    void ExtractPedsWithGuns(CPedList& pFrom);

    // Inlined functions below (Present in Android version)
    void FillUpHoles();
    void BuildListFromGroup_NotInCar_NoLeader(CPedGroupMembership* pedGroupMembership);
    void BuildListOfPedsOfPedType(int pedtype);
    void RemovePedsAttackingPedType(int pedtype);
    void RemovePedsThatDontListenToPlayer();

    // NOTSA
    void ClearUnused();
    void AddMember(CPed* ped);
    void RemoveMemberNoFill(int i);
    CPed* Get(int i);
};
VALIDATE_SIZE(CPedList, 0x7C);
