#pragma once

#include "Vector.h"
#include "TaskSimple.h"

class CTaskSimpleGunControl;
class CPed;
class CEntity;
class CVector;
class CEvent;

enum class eGunCommand : uint8 {
    NONE,
    AIM,
    FIRE,
    FIREBURST,
    RELOAD,
    PISTOLWHIP,
    END_LEISURE,
    END_NOW,
};

class NOTSA_EXPORT_VTABLE CTaskSimpleGunControl : public CTaskSimple {
public:
    static inline uint32& DEFAULT_GUN_ATTACK_PERIOD = *(uint32*)9252472;

public:
    bool        m_isFinished{};
    CEntity*    m_targetEntity{};
    CVector     m_targetPos{};
    CVector     m_moveTarget{};
    int32       m_leisureDurMs{};
    int16       m_burstAmmoCnt{};
    eGunCommand m_firingTask{};
    float       m_attackIntervalMult{};
    uint32      m_nextAtkTimeMs{};
    bool        m_isFirstTime{};
    bool        m_isLOSBlocked{true};
    bool        m_aimImmidiately{};

public:
    static void InjectHooks();

    static constexpr auto Type = eTaskType::TASK_SIMPLE_GUN_CTRL;

    CTaskSimpleGunControl(CEntity* targetEntity, CVector const& targetPos, CVector const& moveTarget, eGunCommand firingTask, int16 burstAmmoCnt, int32 leisureDurMs);
    CTaskSimpleGunControl(const CTaskSimpleGunControl&);
    ~CTaskSimpleGunControl();

    CTask*    Clone() const override { return new CTaskSimpleGunControl{*this}; }
    eTaskType GetTaskType() const override { return Type; }
    bool      MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool      ProcessPed(CPed* ped) override;

private:
    void ForceStopDuckingMove(CPed* const ped);

    /// Target's position relative to the ped. False if target's position is invalid.
    bool GetPedToTarget(const CPed* ped, CVector& out);

private: // Wrappers for hooks
    // 0x61F3F0
    CTaskSimpleGunControl* Constructor(CEntity* targetEntity, CVector const* target, CVector const* moveTarget, eGunCommand firingTask, int16 burstLength, int32 durationMs) {
        this->CTaskSimpleGunControl::CTaskSimpleGunControl(targetEntity, target ? *target : CVector{}, moveTarget ? *moveTarget : CVector{}, firingTask, burstLength, durationMs);
        return this;
    }
    // 0x61F4D0
    CTaskSimpleGunControl* Destructor() {
        this->CTaskSimpleGunControl::~CTaskSimpleGunControl();
        return this;
    }
};
