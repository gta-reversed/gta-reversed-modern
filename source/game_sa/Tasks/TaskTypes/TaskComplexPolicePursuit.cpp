#include "StdInc.h"
#include "TaskComplexPolicePursuit.h"

void CTaskComplexPolicePursuit::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexPolicePursuit, 0x8709d4, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x68BA70);
    RH_ScopedInstall(Destructor, 0x68D880);

    RH_ScopedInstall(SetWeapon, 0x68BAD0);
    RH_ScopedInstall(ClearPursuit, 0x68BD90);
    RH_ScopedInstall(SetPursuit, 0x68BBD0);
    RH_ScopedInstall(PersistPursuit, 0x68BDC0, { .reversed = false });
    RH_ScopedInstall(CreateSubTask, 0x68D910, { .reversed = false });
    RH_ScopedVMTInstall(Clone, 0x68CDD0, { .reversed = false });
    RH_ScopedVMTInstall(GetTaskType, 0x68BAA0, { .reversed = false });
    RH_ScopedVMTInstall(MakeAbortable, 0x68BAB0, { .reversed = false });
    RH_ScopedVMTInstall(CreateNextSubTask, 0x68BAC0, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x6908E0, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x690920, { .reversed = false });
}

// 0x68CDD0
CTaskComplexPolicePursuit::CTaskComplexPolicePursuit(const CTaskComplexPolicePursuit& o) :
    CTaskComplexPolicePursuit{}
{
}

// 0x68D880
CTaskComplexPolicePursuit::~CTaskComplexPolicePursuit() {
    if (m_Pursuer) {
        ClearPursuit(m_Pursuer);
        if (notsa::IsFixBugs()) {
            CEntity::SafeCleanUpRef(m_Pursuer);
        }
    }
    CEntity::SafeCleanUpRef(m_Persecuted);
}

//! @addr 0x68BAD0
//! Make sure cop has a weapon on them
void CTaskComplexPolicePursuit::SetWeapon(CPed* ped) { // `ped` is the pursuer
    const auto wantedLevel = FindPlayerWanted()->GetWantedLevel();

    // At level 0 we dont do anything (I don't think this is possible anyways)
    if (wantedLevel == 0) {
        return;
    }

    if (wantedLevel > 1) {
        if (ped->GetActiveWeapon().GetType() != WEAPON_UNARMED) { // Already has a weapon
            return;
        }
    } else /*wantedLevel == 1*/ {
        const auto player = FindPlayerPed();
        if (player->m_standingOnEntity || ped->m_nPedState == PEDSTATE_ARREST_PLAYER) {
            return;
        }
        if (ped->DoWeHaveWeaponAvailable(WEAPON_NIGHTSTICK)) {
            switch (player->GetActiveWeapon().GetWeaponInfo(player).m_nWeaponFire) {
            case WEAPON_FIRE_INSTANT_HIT:
            case WEAPON_FIRE_PROJECTILE:
                break;
            default:
                ped->SetCurrentWeapon(WEAPON_NIGHTSTICK);
                return;
            }
        }
    }

    ped->SetCurrentWeapon(ped->DoWeHaveWeaponAvailable(WEAPON_SHOTGUN) ? WEAPON_SHOTGUN : WEAPON_PISTOL);
}

// 0x68BD90
void __stdcall CTaskComplexPolicePursuit::ClearPursuit(CCopPed* pursuer) {
    if (FindPlayerPed()) {
        FindPlayerWanted()->RemovePursuitCop(pursuer);
    }
}

// 0x68BBD0
int8 CTaskComplexPolicePursuit::SetPursuit(CPed* ped) {
    // Find closest player
    float minDistSq = FLT_MAX;
    CPlayerPed* closestPlayer{};
    for (const auto& v : CWorld::Players) {
        const auto plyr = v.m_pPed;
        const auto distSq = (plyr->GetPosition() - ped->GetPosition()).SquaredMagnitude();
        if (distSq >= minDistSq) {
            continue;
        }
        if (plyr->bInVehicle) {
            if (distSq * plyr->m_pVehicle->GetMoveSpeed().SquaredMagnitude() >= sq(4.f)) { // TODO/BUG: Why `*`?
                continue;
            }
        }
        closestPlayer = plyr;
        minDistSq     = distSq;
    }
    CEntity::ChangeEntityReference(m_Persecuted, closestPlayer);
    return closestPlayer && FindPlayerWanted()->SetPursuitCop(ped->AsCop());
}

// 0x68BDC0
int8 CTaskComplexPolicePursuit::PersistPursuit(CPed* ped) {
    return plugin::CallMethodAndReturn<int8, 0x68BDC0, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

// 0x68D910
void CTaskComplexPolicePursuit::CreateSubTask(int32 taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<void, 0x68D910, CTaskComplexPolicePursuit*, int32, CPed*>(this, taskType, ped);
}

// 0x68BAC0
CTask* CTaskComplexPolicePursuit::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x68BAC0, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

// 0x6908E0
CTask* CTaskComplexPolicePursuit::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6908E0, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

// 0x690920
CTask* CTaskComplexPolicePursuit::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690920, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}
