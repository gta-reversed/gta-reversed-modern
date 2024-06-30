#include "StdInc.h"
#include "TaskSimpleFight.h"

void CTaskSimpleFight::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleFight, 0x86d684, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x61C470);
    RH_ScopedInstall(Destructor, 0x61C530);

    RH_ScopedGlobalInstall(GetComboType, 0x61DB30);
    RH_ScopedGlobalInstall(FinishMeleeAnimCB, 0x61DAE0);
    RH_ScopedGlobalInstall(FightSetUpCol, 0x61D5F0);
    RH_ScopedGlobalInstall(LoadMeleeData, 0x5BEDC0, { .reversed = false });
    RH_ScopedGlobalInstall(GetHitSound, 0x5BD3B0);
    RH_ScopedGlobalInstall(GetHitLevel, 0x5BD360);
    RH_ScopedInstall(GetComboAnimGroupID, 0x4ABDA0);
    RH_ScopedInstall(FindTargetOnGround, 0x61D6F0, { .reversed = false });
    RH_ScopedInstall(FightHitObj, 0x61D400, { .reversed = false });
    RH_ScopedInstall(FightHitCar, 0x61D0B0, { .reversed = false });
    RH_ScopedInstall(FightHitPed, 0x61CBA0, { .reversed = false });
    RH_ScopedInstall(SetPlayerMoveAnim, 0x61C9B0, { .reversed = false });
    RH_ScopedInstall(FightStrike, 0x6240B0, { .reversed = false });
    RH_ScopedInstall(GetAvailableComboSet, 0x61C7F0, { .reversed = false });
    RH_ScopedInstall(ControlFight, 0x61C5E0);
    RH_ScopedInstall(IsHitComboSet, 0x4ABDF0);
    RH_ScopedInstall(IsComboSet, 0x4ABDC0);
    RH_ScopedInstall(GetStrikeDamage, 0x61C740);
    RH_ScopedInstall(GetRange, 0x61C1C0);
    RH_ScopedVMTInstall(Clone, 0x622E40);
    RH_ScopedVMTInstall(GetTaskType, 0x61C520);
    RH_ScopedVMTInstall(MakeAbortable, 0x6239F0, { .reversed = false });
    RH_ScopedVMTInstall(ProcessPed, 0x629920, { .reversed = false });
}

// 0x61C470
CTaskSimpleFight::CTaskSimpleFight(CEntity* target, eMeleeCommandS32 firstCmd, uint32 idlePeriod) :
    m_IdlePeriod{(uint16)std::min(60'000u, idlePeriod)},
    m_Target{target},
    m_NextCmd{firstCmd}
{
}

// 0x622E40
CTaskSimpleFight::CTaskSimpleFight(const CTaskSimpleFight& o) :
    CTaskSimpleFight{o.m_Target, o.m_NextCmd, o.m_IdlePeriod}
{
}

// 0x61C530
CTaskSimpleFight::~CTaskSimpleFight() {
    if (m_Anim) {
        m_Anim->SetDefaultDeleteCallback();
    }
    if (m_IdleAnim) {
        m_IdleAnim->SetDefaultDeleteCallback();
    }
    if (m_AreAnimsReferenced) {
        if (m_RequiredAnimGroup != ANIM_GROUP_MELEE_1) {
            CAnimManager::RemoveAnimBlockRef(CAnimManager::GetAnimationBlockIndex(m_RequiredAnimGroup));
        }
    }
}

// 0x6239F0
bool CTaskSimpleFight::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x6239F0>(this, ped, priority, event);
}

// 0x629920
bool CTaskSimpleFight::ProcessPed(CPed * ped) {
    return plugin::CallMethodAndReturn<bool, 0x629920, CTaskSimpleFight*, CPed *>(this, ped);
}

// 0x61DB30
eMeleeCombo CTaskSimpleFight::GetComboType(const char* comboName) {
    return notsa::find_value_or(
        notsa::make_mapping<std::string_view, eMeleeCombo>({
            {"UNARMED",     eMeleeCombo::UNARMED_1},
            {"BBALLBAT",    eMeleeCombo::BBALLBAT },
            {"KNIFE",       eMeleeCombo::KNIFE    },
            {"GOLFCLUB",    eMeleeCombo::GOLFCLUB },
            {"SWORD",       eMeleeCombo::SWORD    },
            {"CHAINSAW",    eMeleeCombo::CHAINSAW },
            {"DILDO",       eMeleeCombo::DILDO    },
            {"FLOWERS",     eMeleeCombo::FLOWERS  },
        }),
        comboName,
        eMeleeCombo::UNARMED_1
    );
}

// 0x61DAE0
void CTaskSimpleFight::FinishMeleeAnimCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = CTask::Cast<CTaskSimpleFight>(static_cast<CTask*>(data));

    assert(anim && self);

    if (self->m_Anim == anim) {
        self->m_Anim = nullptr;
    } else if (self->m_IdleAnim == anim) {
        self->m_IdleAnim = nullptr;
    } else {
        NOTSA_UNREACHABLE();
    }

    if (anim->GetAnimId() == ANIM_ID_FIGHT2IDLE) {
        self->m_IsFinished = true;
    } else if (!self->m_IdleAnim) {
        using enum eMeleeCommand;
        switch (self->m_LastCmd) {
        case END_RUNAWAY:
        case END_SPRINTAWAY:
        case END_QUICK:
        case END_SLOW:
            self->m_IsFinished = true;
        }
    }
}   

// 0x5BEDC0
void CTaskSimpleFight::LoadMeleeData() {
    return plugin::CallAndReturn<void, 0x5BEDC0>();
}

// 0x5BD3B0
eAudioEvents CTaskSimpleFight::GetHitSound(int32 hitSound) {
    switch (hitSound) {
    case 1: return AE_PED_HIT_HIGH;
    case 2: return AE_PED_HIT_LOW;
    case 3: return AE_PED_HIT_GROUND;
    case 4: return AE_PED_HIT_GROUND_KICK;
    case 5: return AE_PED_HIT_HIGH_UNARMED;
    case 6: return AE_PED_HIT_LOW_UNARMED;
    case 7: return AE_PED_HIT_MARTIAL_PUNCH;
    case 8: return AE_PED_HIT_MARTIAL_KICK;
    default:       NOTSA_UNREACHABLE();
    }
}

// 0x5BD360
eMeleeHitLevel CTaskSimpleFight::GetHitLevel(char const* hitLevelID) {
    using enum eMeleeHitLevel;

    /*if constexpr (notsa::IsFixBugs()) {
        switch (MAKEFOURCC(hitLevelID[0], hitLevelID[0] ? hitLevelID[1] : 0, 0, 0)) {
        case MAKEFOURCC('H', 0,   0, 0): return HIGH;
        case MAKEFOURCC('L', 0,   0, 0): return LOW;
        case MAKEFOURCC('G', 0,   0, 0): return GROUND;
        case MAKEFOURCC('B', 0,   0, 0): return BEHIND;
        case MAKEFOURCC('H', 'L', 0, 0): return HIGH_LONG;
        case MAKEFOURCC('L', 'L', 0, 0): return LOW_LONG;
        case MAKEFOURCC('G', 'L', 0, 0): return GROUND_LONG;
        default:                         return NUM; //NOTSA_UNREACHABLE();
        }
    } else */{
        switch (hitLevelID[0]) {
        case 'H': return HIGH;
        case 'L': return LOW;
        case 'G': return GROUND;
        case 'B': return BEHIND;
        }

        // Note how above they didn't check the second character
        // because of that the values below won't ever be returned

        if (!strcmp(hitLevelID, "HL")) {
            return HIGH_LONG;
        }
        if (!strcmp(hitLevelID, "LL")) {
            return LOW_LONG;
        }
        if (!strcmp(hitLevelID, "GL")) {
            return GROUND_LONG;
        }
        return NUM;
    }
}

// 0x4ABDA0
AssocGroupId CTaskSimpleFight::GetComboAnimGroupID() const {
    return GetCurrentComboData().AnimGroup;
}

// 0x61D6F0
bool CTaskSimpleFight::FindTargetOnGround(CPed * ped) {
    return plugin::CallMethodAndReturn<bool, 0x61D6F0, CTaskSimpleFight*, CPed *>(this, ped);
}

// 0x61C9B0
void CTaskSimpleFight::SetPlayerMoveAnim(CPlayerPed * player) {
    return plugin::CallMethodAndReturn<void, 0x61C9B0, CTaskSimpleFight*, CPlayerPed *>(this, player);
}

// 0x61C5E0
bool CTaskSimpleFight::ControlFight(CEntity * newTarget,  eMeleeCommandS8 command) {
    m_IsInControl = true;
    m_Target      = newTarget;
    m_NextCmd     = std::max(m_NextCmd, command);
    return true;
}

// 0x61D400
void CTaskSimpleFight::FightHitObj(CPed* attacker, CObject* victim, CVector& hitPt, CVector& hitDelta, int16 hitPieceType, uint8 hitSurfaceType) {
    plugin::CallMethodAndReturn<void, 0x61D400, CTaskSimpleFight*, CPed *, CObject *, CVector &, CVector &, int16, uint8>(this, attacker, victim, hitPt, hitDelta, hitPieceType, hitSurfaceType);
}

// 0x61D0B0
void CTaskSimpleFight::FightHitCar(CPed * creator, CVehicle * victim, CVector & hitPt, CVector & hitDelta, int16 hitPieceType, uint8 hitSurfaceType) {
    return plugin::CallMethodAndReturn<void, 0x61D0B0, CTaskSimpleFight*, CPed *, CVehicle *, CVector &, CVector &, int16, uint8>(this, creator, victim, hitPt, hitDelta, hitPieceType, hitSurfaceType);
}

// 0x61CBA0
CPed* CTaskSimpleFight::FightHitPed(CPed * creator, CPed * victim, CVector & hitPt, CVector & hitDelta, int16 hitPieceType) {
    return plugin::CallMethodAndReturn<CPed *, 0x61CBA0, CTaskSimpleFight*, CPed *, CPed *, CVector &, CVector &, int16>(this, creator, victim, hitPt, hitDelta, hitPieceType);
}

// 0x6240B0
eMeleeCommand CTaskSimpleFight::FightStrike(CPed * ped, CVector & pos) {
    return plugin::CallMethodAndReturn<eMeleeCommand, 0x6240B0, CTaskSimpleFight*, CPed *, CVector &>(this, ped, pos);
}

// 0x61D5F0
void CTaskSimpleFight::FightSetUpCol(float radius) {
    auto* const cm = &m_sStrikeColModel;
    auto* const cd = &m_sStrikeColData;

    if (!cm->GetData()) {
        cm->m_pColData    = cd;
        cd->m_pSpheres    = m_sStrikeSpheres.data();
        cd->m_nNumSpheres = (uint16)m_sStrikeSpheres.size();
    }

    cd->GetSpheres()[0].Set(radius, {0.f, 0.f, 0.f});

    cm->GetBoundingBox().Set(
        {-radius, -radius, -radius},
        { radius,  radius,  radius}
    );
    cm->GetBoundingSphere().Set(
        radius,
        {0.f, 0.f, 0.f}
    );
}

// 0x61C7F0
eMeleeCombo CTaskSimpleFight::GetAvailableComboSet(CPed* ped, eMeleeCommandS8 nextCmd) {
    return plugin::CallMethodAndReturn<eMeleeCombo, 0x61C7F0, CTaskSimpleFight*, CPed *,  eMeleeCommandS8>(this, ped, nextCmd);
}

// 0x4ABDF0
bool CTaskSimpleFight::IsHitComboSet() const {
    const auto* const c = &GetCurrentComboData();

    using enum eMeleeMove;
    switch (m_CurrentMove) {
    case ATTACK1: return c->NoFall1;
    case ATTACK2: return c->NoFall2;
    case ATTACK3: return c->NoFall3;
    default:      return false;
    }
}

// 0x4ABDC0
bool CTaskSimpleFight::IsComboSet() const {
    const auto* const c = &GetCurrentComboData();

    using enum eMeleeMove;
    switch (m_CurrentMove) {
    case ATTACK1: return c->Fall1;
    case ATTACK2: return c->Fall2;
    case ATTACK3: return c->Fall3;
    case GROUND:  return c->FallGround;
    case MOVING:  return c->FallRun;
    default:      NOTSA_UNREACHABLE();
    }
}

// 0x61C1C0
float CTaskSimpleFight::GetRange() const {
    return m_aComboData[MeleeCombo2MeleeDataIdx(m_ComboSet)].GroupRange;
}

// 0x61C740
float CTaskSimpleFight::GetStrikeDamage(CPed * attacker) {
    const auto baseDmg = (float)m_aComboData[MeleeCombo2MeleeDataIdx(m_ComboSet)].Damage[+m_CurrentMove];
    if (attacker->IsPlayer()) {
        return attacker->m_pPlayerData->m_bAdrenaline
            ? 50.f
            : CStats::GetFatAndMuscleModifier(STAT_MOD_4) * baseDmg;
    }
    switch (attacker->GetActiveWeapon().GetType()) {
    case WEAPON_BRASSKNUCKLE:
        return baseDmg * 1.5f;
    case WEAPON_UNARMED:
        return baseDmg;
    default:
        return baseDmg * attacker->m_pStats->m_fAttackStrength;
    }
}
