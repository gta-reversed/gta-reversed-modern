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
    RH_ScopedClass(CPedShelterAttractor);
    RH_ScopedCategory("Attractors");

    using namespace ReversibleHooks;
    // RH_ScopedInstall(GetDisplacement, 0x5EF420);
    RH_ScopedInstall(ComputeAttractPos_Reversed, 0x5EFC40);
    RH_ScopedInstall(ComputeAttractHeading_Reversed, 0x5E9690);
    // RH_ScopedInstall(BroadcastDeparture_Reversed, 0x5EF570);
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
