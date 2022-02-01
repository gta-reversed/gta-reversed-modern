/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "LoadedCarGroup.h"

// 0x611E10
void CLoadedCarGroup::SortBasedOnUsage() {
    plugin::CallMethod<0x611E10, CLoadedCarGroup *>(this);
}

// 0x611BD0
int32 CLoadedCarGroup::RemoveMember(int32 modelindex) {
    return plugin::CallMethodAndReturn<int32, 0x611BD0, CLoadedCarGroup *, int32>(this, modelindex);
}

// 0x611C50
int32 CLoadedCarGroup::PickRandomCar(bool arg1, bool arg2) {
    return plugin::CallMethodAndReturn<int32, 0x611C50, CLoadedCarGroup *, bool, bool>(this, arg1, arg2);
}

// 0x611E90
int32 CLoadedCarGroup::PickLeastUsedModel(int32 minRefs) {
    return plugin::CallMethodAndReturn<int32, 0x611E90, CLoadedCarGroup *, int32>(this, minRefs);
}

// 0x611C20
int32 CLoadedCarGroup::GetMember(int32 count) const {
    return plugin::CallMethodAndReturn<int32, 0x611C20, const CLoadedCarGroup *, int32>(this, count);
}

// 0x611C30
int32 CLoadedCarGroup::CountMembers() const {
    return plugin::CallMethodAndReturn<int32, 0x611C30, const CLoadedCarGroup *>(this);
}

// 0x611B90
void CLoadedCarGroup::Clear() {
    plugin::CallMethod<0x611B90, CLoadedCarGroup *>(this);
}

// 0x611BB0
void CLoadedCarGroup::AddMember(int32 member) {
    plugin::CallMethod<0x611BB0, CLoadedCarGroup *, int32>(this, member);
}
