/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CLoadedCarGroup {
public:
    int16 m_members[22]; // model ids
    int16 field_2C;

    void  SortBasedOnUsage();
    int32 RemoveMember(int32 modelindex);
    int32 PickRandomCar(bool arg1, bool arg2);
    int32 PickLeastUsedModel(int32 minRefs);
    int32 GetMember(int32 count) const;
    int32 CountMembers() const;
    void  Clear();
    void  AddMember(int32 member);
};

VALIDATE_SIZE(CLoadedCarGroup, 0x2E);
