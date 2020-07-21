#include "StdInc.h"

float CPedGroup::FindDistanceToFurthestMember() {
    return plugin::CallMethodAndReturnDynGlobal<float, CPedGroup*>(0x5FB010, this);
}

float CPedGroup::FindDistanceToNearestMember(CPed** ppOutNearestMember) {
    return plugin::CallMethodAndReturnDynGlobal<float, CPedGroup*, CPed**>(0x5FB0A0, this, ppOutNearestMember);
}

void CPedGroup::Flush() {
    plugin::CallMethodDynGlobal<CPedGroup*>(0x5FB790, this);
}

CPed* CPedGroup::GetClosestGroupPed(CPed* ped, float* pOutDistance) {
    return plugin::CallMethodAndReturnDynGlobal<CPed*, CPedGroup*, CPed*, float*>(0x5FACD0, this, ped, pOutDistance);
}

bool CPedGroup::IsAnyoneUsingCar(CVehicle const* vehicle) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CPedGroup*, CVehicle const*>(0x5F7DB0, this, vehicle);
}

void CPedGroup::PlayerGaveCommand_Attack(CPed* playerPed, CPed* ped) {
    plugin::CallMethodDynGlobal<CPedGroup*, CPed*, CPed*>(0x5F7CC0, this, playerPed, ped);
}

void CPedGroup::PlayerGaveCommand_Gather(CPed* ped) {
    plugin::CallMethodDynGlobal<CPedGroup*, CPed*>(0x5FAB60, this, ped);
}

void CPedGroup::Process() {
    plugin::CallMethodDynGlobal<CPedGroup*>(0x5FC7E0, this);
}

void CPedGroup::RemoveAllFollowers() {
    plugin::CallMethodDynGlobal<CPedGroup*>(0x5FB7D0, this);
}

void CPedGroup::Teleport(CVector const* Pos) {
    plugin::CallMethodDynGlobal<CPedGroup*, CVector const*>(0x5F7AD0, this, Pos);
}
