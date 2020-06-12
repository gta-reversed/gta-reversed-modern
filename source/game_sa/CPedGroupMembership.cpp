#include "StdInc.h"

void CPedGroupMembership::Flush() {
    plugin::CallMethodDynGlobal<CPedGroupMembership*>(0x5FB160, this);
}

void CPedGroupMembership::From(CPedGroupMembership const* obj) {
    plugin::CallMethodDynGlobal<CPedGroupMembership*, CPedGroupMembership const*>(0x5F7FE0, this, obj);
}

CPed* CPedGroupMembership::GetLeader() {
    return plugin::CallMethodAndReturnDynGlobal<CPed*, CPedGroupMembership*>(0x5F69A0, this);
}

CPed* CPedGroupMembership::GetMember(int memberId) {
    return plugin::CallMethodAndReturnDynGlobal<CPed*, CPedGroupMembership*, int>(0x5F69B0, this, memberId);
}

bool CPedGroupMembership::IsMember(CPed const* ped) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CPedGroupMembership*, CPed const*>(0x5F6A10, this, ped);
}
