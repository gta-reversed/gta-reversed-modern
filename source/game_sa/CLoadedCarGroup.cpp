/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

// Converted from thiscall void CLoadedCarGroup::SortBasedOnUsage(void)	0x611E10
void CLoadedCarGroup::SortBasedOnUsage() {
    plugin::CallMethod<0x611E10, CLoadedCarGroup *>(this);
}

// Converted from thiscall int CLoadedCarGroup::RemoveMember(int modelindex)	0x611BD0
int CLoadedCarGroup::RemoveMember(int modelindex) {
    return plugin::CallMethodAndReturn<int, 0x611BD0, CLoadedCarGroup *, int>(this, modelindex);
}

// Converted from thiscall int CLoadedCarGroup::PickRandomCar(bool arg1,bool arg2)	0x611C50
int CLoadedCarGroup::PickRandomCar(bool arg1, bool arg2) {
    return plugin::CallMethodAndReturn<int, 0x611C50, CLoadedCarGroup *, bool, bool>(this, arg1, arg2);
}

// Converted from thiscall int CLoadedCarGroup::PickLeastUsedModel(int minRefs)	0x611E90
int CLoadedCarGroup::PickLeastUsedModel(int minRefs) {
    return plugin::CallMethodAndReturn<int, 0x611E90, CLoadedCarGroup *, int>(this, minRefs);
}

// Converted from thiscall int CLoadedCarGroup::GetMember(int count)	0x611C20
int CLoadedCarGroup::GetMember(int count) {
    return plugin::CallMethodAndReturn<int, 0x611C20, CLoadedCarGroup *, int>(this, count);
}

// Converted from thiscall int CLoadedCarGroup::CountMembers(void)	0x611C30
int CLoadedCarGroup::CountMembers() {
    return plugin::CallMethodAndReturn<int, 0x611C30, CLoadedCarGroup *>(this);
}

// Converted from thiscall void CLoadedCarGroup::Clear(void)	0x611B90
void CLoadedCarGroup::Clear() {
    plugin::CallMethod<0x611B90, CLoadedCarGroup *>(this);
}

// Converted from thiscall void CLoadedCarGroup::AddMember(int member)	0x611BB0
void CLoadedCarGroup::AddMember(int member) {
    plugin::CallMethod<0x611BB0, CLoadedCarGroup *, int>(this, member);
}
