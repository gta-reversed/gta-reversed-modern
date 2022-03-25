#include "StdInc.h"
#include "CivilianPed.h"

// 0x5DDB70
CCivilianPed::CCivilianPed(ePedType pedType, uint32 modelIndex) : CPed(pedType) {
    SetModelIndex(modelIndex);
    m_pedSpeech.Initialise(this);
}

// 0x5DDBF0
void CCivilianPed::ProcessControl() {
    if (m_nCreatedBy != (PED_MISSION | PED_GAME)) {
        CPed::ProcessControl();
        if (!m_bWasPostponed && m_nPedState != PEDSTATE_DEAD)
            GetActiveWeapon().Update(this);
    }
}
