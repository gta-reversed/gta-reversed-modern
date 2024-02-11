#include "StdInc.h"

#include "TaskSimpleTogglePedThreatScanner.h"

// 0x492D10
CTaskSimpleTogglePedThreatScanner::CTaskSimpleTogglePedThreatScanner(bool bActivatedEverywhere, bool bActivatedInVehicle, bool bActivatedDuringScriptCommands) :
    m_bActivatedEverywhere{bActivatedEverywhere},
    m_bActivatedInVehicle{bActivatedInVehicle},
    m_bActivatedDuringScriptCommands{bActivatedDuringScriptCommands}
{
}

// 0x6337A0
bool CTaskSimpleTogglePedThreatScanner::ProcessPed(CPed* ped) {
    ped->GetIntelligence()->GetEventScanner().GetAcquaintanceScanner().SetThreatScannerActivationState(
        m_bActivatedEverywhere,
        m_bActivatedInVehicle,
        m_bActivatedDuringScriptCommands
    );
    return true;
}
