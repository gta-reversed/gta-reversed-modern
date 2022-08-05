#include "StdInc.h"

#include "EventFireNearby.h"

// 0x4B1F10
CEventFireNearby::CEventFireNearby(const CVector& position) : CEventEditableResponse() {
    m_position = position;
}

// 0x4B1F90
bool CEventFireNearby::AffectsPed(CPed* ped) {
    return !ped->GetTaskManager().Has<TASK_COMPLEX_EXTINGUISH_FIRES>() && ped->IsAlive();
}
