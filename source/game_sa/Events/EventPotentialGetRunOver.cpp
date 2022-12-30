#include "StdInc.h"

#include "EventPotentialGetRunOver.h"

// 0x4AE1A0
CEventPotentialGetRunOver::CEventPotentialGetRunOver(CVehicle* vehicle) {
    m_Vehicle = vehicle;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x4AE270
CEventPotentialGetRunOver::~CEventPotentialGetRunOver() {
    CEntity::SafeCleanUpRef(m_Vehicle);
}

// 0x4AE2D0
bool CEventPotentialGetRunOver::AffectsPed(CPed* ped) {
    return ped->IsAlive()
       && !ped->m_pAttachedTo
       && !ped->bInVehicle
       && m_Vehicle
       && !m_Vehicle->IsBoat();
}
