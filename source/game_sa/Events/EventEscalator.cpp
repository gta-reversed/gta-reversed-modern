#include "StdInc.h"

#include "EventEscalator.h"

void CEventEscalator::InjectHooks() {
    RH_ScopedClass(CEventEscalator);
    RH_ScopedCategory("Events");

    RH_ScopedVirtualInstall(AffectsPed, 0x4B2580);
}
bool CEventEscalator::AffectsPed(CPed* ped) { return CEventEscalator::AffectsPed_Reversed(ped); }

// 0x4B2580
bool CEventEscalator::AffectsPed_Reversed(CPed* ped) {
    if (ped->IsAlive() && !ped->IsPlayer() && ped->m_pContactEntity) {
        auto modelId = ped->m_pContactEntity->m_nModelIndex;
        if (modelId == ModelIndices::MI_ESCALATORSTEP || modelId == ModelIndices::MI_ESCALATORSTEP8)
            return true;
    }
    return false;
}
