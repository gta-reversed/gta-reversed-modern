#include "StdInc.h"
#include "CivilianPed.h"

// 0x5DDB70
CCivilianPed::CCivilianPed(ePedType pedType, uint32 modelIndex) : CPed(pedType) {
    SetModelIndex(modelIndex); // V1053 Calling the 'SetModelIndex' virtual function in the constructor may lead to unexpected result at runtime
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
