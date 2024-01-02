#include "StdInc.h"

#include "PedShelterAttractor.h"

// SArray& CPedShelterAttractor::ms_displacements = *(SArray*)0xC0986C;

// 0x5EF420
CVector CPedShelterAttractor::GetDisplacement(int32 pedId) {
    return plugin::CallAndReturn<CVector, 0x5EF420, int32>(pedId);
}

// 0x5EFC40
void CPedShelterAttractor::ComputeAttractPos(int32 pedId, CVector& outPos) {
    if (m_pEffect) {
        CVector displacement = GetDisplacement(pedId);
        outPos = displacement + m_vecAttractorPosn;
    }
}

// 0x5E9690
void CPedShelterAttractor::ComputeAttractHeading(int32 bQueue, float& heading) {
    heading = CGeneral::GetRandomNumberInRange(0.0f, TWO_PI);
}

// 0x5EF570
void CPedShelterAttractor::BroadcastDeparture(CPed* ped) {
    plugin::CallMethod<0x5EF570, CPedShelterAttractor*, CPed*>(this, ped);
}

void CPedShelterAttractor::InjectHooks() {
    RH_ScopedClass(CPedShelterAttractor);
    RH_ScopedCategory("Attractors");

    RH_ScopedInstall(GetDisplacement, 0x5EF420, { .reversed = false });
    RH_ScopedVirtualInstall(ComputeAttractPos, 0x5EFC40);
    RH_ScopedVirtualInstall(ComputeAttractHeading, 0x5E9690);
    RH_ScopedVirtualInstall(BroadcastDeparture, 0x5EF570, { .reversed = false });
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
