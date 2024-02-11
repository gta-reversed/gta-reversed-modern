#include "StdInc.h"
#include "AttractorScanner.h"

void CAttractorScanner::InjectHooks() {
    RH_ScopedClass(CAttractorScanner);
    RH_ScopedCategory("Events/Scanners");

    //RH_ScopedGlobalInstall(GetClosestAttractorOfType, 0x6002F0, { .reversed = false });

    RH_ScopedInstall(Clear, 0x5FFF90);
    RH_ScopedInstall(AddEffect, 0x5FFFD0, { .reversed = false });
    RH_ScopedInstall(ScanForAttractorsInPtrList, 0x6034B0, { .reversed = false });
    RH_ScopedInstall(ScanForAttractorsInRange, 0x6060A0, { .reversed = false });
}

// 0x6002F0
//int8 CAttractorScanner::GetClosestAttractorOfType(const CVector& point, float radius, int32, int32, char const* String1, bool, C2dEffect const*, C2dEffect*&, CEntity*&) {
//    return plugin::CallAndReturn<int8, 0x6002F0, CVector const&, float, int32, int32, char const*, bool, C2dEffect const*, C2dEffect*&, CEntity*&>(point, radius, , , String1, , , , );
//}

// 0x5FFF90
void CAttractorScanner::Clear() {
    rng::fill(m_Entities, nullptr);
    rng::fill(m_Effects, nullptr);

    rng::fill(m_MinDistSq, sq(5.f));
    m_MinDistSq[PED_ATTRACTOR_SCRIPTED] = sq(15.f);
    m_MinDistSq[PED_ATTRACTOR_SHELTER]  = sq(15.f);
}

// 0x5FFFD0
void CAttractorScanner::AddEffect(C2dEffectPedAttractor* fx, CEntity* e, const CPed& ped) {
    return plugin::CallMethodAndReturn<void, 0x5FFFD0, CAttractorScanner*, C2dEffectPedAttractor*, CEntity*, const CPed&>(this, fx, e, ped);
}

// 0x6034B0
CPtrNode* CAttractorScanner::ScanForAttractorsInPtrList(CPtrList& list, CPed const& ped) {
    return plugin::CallMethodAndReturn<CPtrNode*, 0x6034B0, CAttractorScanner*, CPtrList&, CPed const&>(this, list, ped);
}

// 0x6060A0
void CAttractorScanner::ScanForAttractorsInRange(const CPed& a2) {
    return plugin::CallMethodAndReturn<void, 0x6060A0, CAttractorScanner*, const CPed&>(this, a2);
}
