#include "CTaskSimple.h"

class CTaskSimpleTogglePedThreatScanner : public CTaskSimple
{
public:
    bool m_bScanAllowedScriptPed;
    bool m_bScanAllowedInVehicle;
    bool m_bScanAllowedScriptedTask;

    CTaskSimpleTogglePedThreatScanner(bool bScanAllowedScriptPed, bool bScanAllowedInVehicle, bool bScanAllowedScriptedTask);
    ~CTaskSimpleTogglePedThreatScanner() {}

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_SIMPLE_TOGGLE_PED_THREAT_SCANNER; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override { return false; }
    bool ProcessPed(CPed* ped) override;
};

VALIDATE_SIZE(CTaskSimpleTogglePedThreatScanner, 0xC);
