/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"

class  CLoadedCarGroup {
public:
    short m_members[22]; // model ids
    short field_2C;

	void SortBasedOnUsage();
    int RemoveMember(int modelindex);
    int PickRandomCar(bool arg1, bool arg2);
    int PickLeastUsedModel(int minRefs);
    int GetMember(int count);
    int CountMembers();
    void Clear();
    void AddMember(int member);
};

VALIDATE_SIZE(CLoadedCarGroup, 0x2E);
