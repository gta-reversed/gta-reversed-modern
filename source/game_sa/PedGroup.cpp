#include "StdInc.h"

float CPedGroup::FindDistanceToFurthestMember() {
    return plugin::CallMethodAndReturn<float, 0x5FB010, CPedGroup*>(this);
}

float CPedGroup::FindDistanceToNearestMember(CPed** ppOutNearestMember) {
    return plugin::CallMethodAndReturn<float, 0x5FB0A0, CPedGroup*, CPed**>(this, ppOutNearestMember);
}

void CPedGroup::Flush() {
    plugin::CallMethod<0x5FB790, CPedGroup*>(this);
}

CPed* CPedGroup::GetClosestGroupPed(CPed* ped, float* pOutDistance) {
    return plugin::CallMethodAndReturn<CPed*, 0x5FACD0, CPedGroup*, CPed*, float*>(this, ped, pOutDistance);
}

bool CPedGroup::IsAnyoneUsingCar(CVehicle const* vehicle) {
    return plugin::CallMethodAndReturn<bool, 0x5F7DB0, CPedGroup*, CVehicle const*>(this, vehicle);
}

void CPedGroup::PlayerGaveCommand_Attack(CPed* playerPed, CPed* ped) {
    plugin::CallMethod<0x5F7CC0, CPedGroup*, CPed*, CPed*>(this, playerPed, ped);
}

void CPedGroup::PlayerGaveCommand_Gather(CPed* ped) {
    plugin::CallMethod<0x5FAB60, CPedGroup*, CPed*>(this, ped);
}

void CPedGroup::Process() {
    plugin::CallMethod<0x5FC7E0, CPedGroup*>(this);
}

void CPedGroup::RemoveAllFollowers() {
    plugin::CallMethod<0x5FB7D0, CPedGroup*>(this);
}

void CPedGroup::Teleport(CVector const* Pos) {
    plugin::CallMethod<0x5F7AD0, CPedGroup*, CVector const*>(this, Pos);
}
