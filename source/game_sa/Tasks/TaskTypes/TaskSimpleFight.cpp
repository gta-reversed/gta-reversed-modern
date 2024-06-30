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
    RH_ScopedGlobalInstall(LoadMeleeData, 0x5BEDC0);
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
    for (auto& cs : m_aComboData) {
        cs.AnimGroup       = ANIM_GROUP_MELEE_1;
        cs.GroupRange      = 1.5f;
        cs.GroundLoopStart = 0.f;
        cs.BlockLoopStart  = 100.f;
        cs.BlockLoopEnd    = 100.f;
        cs.Flags           = 0;
        rng::fill(cs.FireTime, 100.f);
        rng::fill(cs.ComboTime, 100.f);
        rng::fill(cs.Radius, 1.f);
        rng::fill(cs.HitLevel, eMeleeHitLevel::NUM);
        rng::fill(cs.Damage, 0);
        rng::fill(cs.HitSound, AE_UNDEFINED); // Originally 0
        rng::fill(cs.AltHitSound, AE_UNDEFINED); // Originally 0
    }

    rng::fill(m_aHitOffset, CVector{0.f, 0.75f, 0.f});

    // Sections
    enum {
        SNONE,
        SCOMBO,
        SLEVELS,
    } section = SNONE;

    // Combo section fields
    enum {
        FNONE      = 0x0,
        FANIMGROUP = 0x1,
        FRANGES    = 0x2,
        FATTACK1   = 0x3,
        FATTACK2   = 0x4,
        FATTACK3   = 0x5,
        FAGROUND   = 0x6,
        FAMOVING   = 0x7,
        FABLOCK    = 0x8,
        FFLAGS     = 0x9,
    };
    int32 field = FNONE;

    char fname[32];
    const auto CheckFieldIs = [&fname](const char* expected) {
        if (strcmp(fname, expected) != 0) {
            NOTSA_LOG_ERR("Expected field {} got {}", expected, fname);
        }
    };

    size_t comboN = 0;
    size_t levelN = 0;

    const auto file = CFileMgr::OpenFile("DATA\\melee.dat", "rb");
    for (;;) {
        const auto line = CFileLoader::LoadLine(file);
        if (!line) {
            break;
        }
        if (!line[0] || line[0] == '#') {
            continue;
        }
        const auto LineStartsWith = [line]<size_t N>(const char (&with)[N]) {
            return strncmp(line, with, N - 1) == 0;
        };
        if (LineStartsWith("END_MELEE_DATA")) { // End of file
            break;
        }
        if (section == SNONE) {
            if (LineStartsWith("START_COMBO")) {
                section = SCOMBO;
            } else if (LineStartsWith("START_LEVELS")) {
                section = SLEVELS;
            }
            continue;
        }
        if (LineStartsWith("END_COMBO")) { // Yes, `END_COMBO` is used for `START_LEVELS` too!
            if (section == SCOMBO) {
                comboN++;
                field = 0;
            }
            section = SNONE;
            continue;
        }
        if (section == SLEVELS) {
            NOTSA_LOG_TRACE("Reading offsets for level {}", levelN);

            auto* const o = &m_aHitOffset[levelN++];

            VERIFY(sscanf_s(
                line,
                "%s %f %f %f",
                SCANF_S_STR(fname), &o->x, &o->y, &o->z
            ) == 4);

        } else if (section == SCOMBO) { // Not that it could be something else at this point
            auto* const c = &m_aComboData[comboN];

            switch (++field) {
            case FANIMGROUP: {
                char animGroupName[32]{};

                VERIFY(sscanf_s(
                    line,
                    "%s %s",
                    SCANF_S_STR(fname), SCANF_S_STR(animGroupName)
                ) == 2);
                CheckFieldIs("ANIMGROUP");

                c->AnimGroup = CAnimManager::GetAnimationGroupIdByName(animGroupName);
                assert(c->AnimGroup != AssocGroupId::ANIM_GROUP_DEFAULT);

                break;
            }
            case FRANGES: {
                VERIFY(sscanf_s(
                    line,
                    "%s %f",
                    SCANF_S_STR(fname), &c->GroupRange
                ) == 2);
                CheckFieldIs("RANGES");

                break;
            }
            case FATTACK1:
            case FATTACK2:
            case FATTACK3:
            case FAGROUND:
            case FAMOVING: {
                // In the same order as they appear in the file:
                float hit;
                float chain;
                float radius;
                char  hitLevelName[32]{};
                int32 damage;
                int32 hitSound;
                int32 hitAltSound;
                float groundLoop = 0.f; // Optional

                VERIFY(sscanf_s(
                    line,
                    "%s %f %f %f %s %d %d %d %f",
                    SCANF_S_STR(fname), &hit, &chain, &radius, SCANF_S_STR(hitLevelName), &damage, &hitSound, &hitAltSound, &groundLoop
                ) >= 8);

                int32 lvl;
                switch (field) {
                case FATTACK1: CheckFieldIs("ATTACK1"); lvl = 0; break;
                case FATTACK2: CheckFieldIs("ATTACK2"); lvl = 1; break;
                case FATTACK3: CheckFieldIs("ATTACK3"); lvl = 2; break;
                case FAGROUND: CheckFieldIs("AGROUND"); lvl = 3; break;
                case FAMOVING: CheckFieldIs("AMOVING"); lvl = 4; break;
                default:       NOTSA_UNREACHABLE();
                }

                c->FireTime[lvl]    = hit / 30.f;
                c->Radius[lvl]      = radius;
                c->ComboTime[lvl]   = chain / 30.f;
                c->HitLevel[lvl]    = GetHitLevel(hitLevelName);
                c->Damage[lvl]      = (uint8)damage;
                c->HitSound[lvl]    = GetHitSound(hitSound);
                c->AltHitSound[lvl] = GetHitSound(hitAltSound);
                if (groundLoop > 0.f) {
                    c->GroundLoopStart = groundLoop / 30.f;
                }

                break;
            }
            case FABLOCK: {
                float loopStart;
                float loopEnd;

                VERIFY(sscanf_s(
                    line,
                    "%s %f %f",
                    SCANF_S_STR(fname), &loopStart, &loopEnd
                ) == 3);
                CheckFieldIs("ABLOCK");

                c->BlockLoopStart = loopStart / 30.f;
                c->BlockLoopEnd   = loopEnd / 30.f;

                break;
            }
            case FFLAGS: {
                uint32 flags;

                VERIFY(sscanf_s(
                    line,
                    "%s %x",
                    SCANF_S_STR(fname), &flags
                ) == 2);
                CheckFieldIs("FLAGS");

                c->Flags = flags;

                break;
            }
            default:
                NOTSA_UNREACHABLE("Invalid field {}", field);
            }
        } else {
            NOTSA_UNREACHABLE("Invalid section {}", (int32)section);
        }
    }
    CFileMgr::CloseFile(file);
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
