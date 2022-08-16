#pragma once

#include "TaskSimple.h"
#include "Base.h"

class CAnimBlendAssociation;

class CTaskSimpleTired : public CTaskSimple {
public:
    uint32 m_tiredDurationMs = {};
    uint32 m_animStartMs = {};
    uint32 m_tiredDurationCpy = {};
    bool  m_animHasStarted = {};
    bool  m_needsToStartAnim = {};
    CAnimBlendAssociation* m_tiredAnim = {};

public:
    static void InjectHooks();

    constexpr static auto Type = eTaskType::TASK_SIMPLE_TIRED;

    CTaskSimpleTired(uint32 tiredDurationMs);
    CTaskSimpleTired(const CTaskSimpleTired&);
    ~CTaskSimpleTired() override = default;

    void StartAnim(CPed* ped);

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleTired{ *this }; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    bool ProcessPed(CPed* ped) override;

private: // Wrappers for hooks
    // 0x630F20
    CTaskSimpleTired* Constructor(int32 tiredDurationMs) {
        this->CTaskSimpleTired::CTaskSimpleTired(tiredDurationMs);
        return this;
    }

    // 0x630F60
    CTaskSimpleTired* Destructor() {
        this->CTaskSimpleTired::~CTaskSimpleTired();
        return this;
    }
};
//VALIDATE_SIZE(CTaskSimpleTired, 0x1C);
