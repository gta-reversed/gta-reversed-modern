#include "TaskSimple.h"

class NOTSA_EXPORT_VTABLE CTaskSimpleTogglePedThreatScanner final : public CTaskSimple {
public:
    static constexpr auto Type = TASK_SIMPLE_TOGGLE_PED_THREAT_SCANNER;

    CTaskSimpleTogglePedThreatScanner(bool bActivatedEverywhere, bool bActivatedInVehicle, bool bActivatedDuringScriptCommands);
    ~CTaskSimpleTogglePedThreatScanner() override = default;

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override { return new CTaskSimpleTogglePedThreatScanner(m_bActivatedEverywhere, m_bActivatedInVehicle, m_bActivatedDuringScriptCommands); } // 0x492D50
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override { return false; }
    bool ProcessPed(CPed* ped) override;

private:
    bool m_bActivatedEverywhere{};
    bool m_bActivatedInVehicle{};
    bool m_bActivatedDuringScriptCommands{};
};
VALIDATE_SIZE(CTaskSimpleTogglePedThreatScanner, 0xC);
