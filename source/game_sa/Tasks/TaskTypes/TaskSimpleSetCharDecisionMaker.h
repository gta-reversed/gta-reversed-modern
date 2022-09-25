#pragma once

#include "TaskSimple.h"

class CEvent;
class CPed;
class CTaskSimpleSetCharDecisionMaker;

class NOTSA_EXPORT_VTABLE CTaskSimpleSetCharDecisionMaker : public CTaskSimple {

public:
    uint32 m_decisionMaker{};

public:
    static void InjectHooks();

    static constexpr auto Type = eTaskType::TASK_SIMPLE_SET_CHAR_DECISION_MAKER;

    CTaskSimpleSetCharDecisionMaker(uint32 decisionMaker);
    CTaskSimpleSetCharDecisionMaker(const CTaskSimpleSetCharDecisionMaker&); // NOTSA
    ~CTaskSimpleSetCharDecisionMaker() = default;

    CTask*    Clone() override { return new CTaskSimpleSetCharDecisionMaker{*this}; }
    eTaskType GetTaskType() override { return Type; }
    bool      MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override { return false; }
    bool      ProcessPed(CPed* ped) override;

private: // Wrappers for hooks
    // 0x46A470
    CTaskSimpleSetCharDecisionMaker* Constructor(uint32 dm) {
        this->CTaskSimpleSetCharDecisionMaker::CTaskSimpleSetCharDecisionMaker(dm);
        return this;
    }
    // 0x46AF10
    CTaskSimpleSetCharDecisionMaker* Destructor() {
        this->CTaskSimpleSetCharDecisionMaker::~CTaskSimpleSetCharDecisionMaker();
        return this;
    }
};
