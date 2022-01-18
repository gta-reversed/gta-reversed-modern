#include "StdInc.h"

#include "PedShelterAttractor.h"

// SArray& CPedShelterAttractor::ms_displacements = *(SArray*)0xC0986C;

// 0x5EF420
CVector CPedShelterAttractor::GetDisplacement(int32 pedId) {
    return plugin::CallAndReturn<CVector, 0x5EF420, int32>(pedId);
}

// 0x5EFC40
void CPedShelterAttractor::ComputeAttractPos(int32 pedId, CVector& outPosn) {
    if (m_pEffect) {
        CVector displacement = GetDisplacement(pedId);
        outPosn = displacement + m_vecAttractorPosn;
    }
}

// 0x5E9690
void CPedShelterAttractor::ComputeAttractHeading(int32 bQueue, float& heading) {
    heading = rand() * RAND_MAX_FLOAT_RECIPROCAL * TWO_PI;
}

// 0x5EF570
void CPedShelterAttractor::BroadcastDeparture(CPed* ped) {
    plugin::CallMethod<0x5EF570, CPedShelterAttractor*, CPed*>(this, ped);
}

void CPedShelterAttractor::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("CPedShelterAttractor", "GetDisplacement", 0x5EF420, &CPedShelterAttractor::GetDisplacement);
    Install("CPedShelterAttractor", "ComputeAttractPos", 0x5EFC40, &CPedShelterAttractor::ComputeAttractPos_Reversed);
    Install("CPedShelterAttractor", "ComputeAttractHeading", 0x5E9690, &CPedShelterAttractor::ComputeAttractHeading_Reversed);
    // Install("CPedShelterAttractor", "BroadcastDeparture", 0x5EF570, &CPedShelterAttractor::BroadcastDeparture_Reversed);
}

void CPedShelterAttractor::ComputeAttractPos_Reversed(int32 pedId, CVector& posn) {
    CPedShelterAttractor::ComputeAttractPos(pedId, posn);
}

void CPedShelterAttractor::ComputeAttractHeading_Reversed(int32 bQueue, float& heading) {
    CPedShelterAttractor::ComputeAttractHeading(bQueue, heading);
}

void CPedShelterAttractor::BroadcastDeparture_Reversed(CPed* ped) {
    CPedShelterAttractor::BroadcastDeparture(ped);
}
