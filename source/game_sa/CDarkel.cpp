#include "StdInc.h"

char*& CDarkel::pStartMessage = *reinterpret_cast<char**>(0x96A6D0);
unsigned int& CDarkel::AmmoInterruptedWeapon = *reinterpret_cast<unsigned int*>(0x96A6D4);
eWeaponType& CDarkel::InterruptedWeaponType = *reinterpret_cast<eWeaponType*>(0x96A6D8);
eWeaponType& CDarkel::InterruptedWeaponTypeSelected = *reinterpret_cast<eWeaponType*>(0x96A6DC);
eDarkelStatus& CDarkel::Status = *(eDarkelStatus*)0x96A704;
unsigned int& CDarkel::TimeOfFrenzyStart = *reinterpret_cast<unsigned int*>(0x96A6E0);
eWeaponType& CDarkel::WeaponType = *reinterpret_cast<eWeaponType*>(0x96A700);

void CDarkel::InjectHooks() {
    ReversibleHooks::Install("CDarkel", "FrenzyOnGoing", 0x43D1F0, &CDarkel::FrenzyOnGoing);
    ReversibleHooks::Install("CDarkel", "Init", 0x43CEB0, &CDarkel::Init);
//    ReversibleHooks::Install("CDarkel", "DrawMessages", 0x43CEC0, &CDarkel::DrawMessages);
    ReversibleHooks::Install("CDarkel", "ReadStatus", 0x43D1E0, &CDarkel::ReadStatus);
//    ReversibleHooks::Install("CDarkel", "RegisterKillNotByPlayer", 0x43D210, &CDarkel::RegisterKillNotByPlayer);
//    ReversibleHooks::Install("CDarkel", "ThisPedShouldBeKilledForFrenzy", 0x43D2F0, &CDarkel::ThisPedShouldBeKilledForFrenzy);
//    ReversibleHooks::Install("CDarkel", "ThisVehicleShouldBeKilledForFrenzy", 0x0, &CDarkel::ThisVehicleShouldBeKilledForFrenzy);
//    ReversibleHooks::Install("CDarkel", "StartFrenzy", 0x43D3B0, &CDarkel::StartFrenzy);
//    ReversibleHooks::Install("CDarkel", "ResetModelsKilledByPlayer", 0x43D6A0, &CDarkel::ResetModelsKilledByPlayer);
//    ReversibleHooks::Install("CDarkel", "QueryModelsKilledByPlayer", 0x0, &CDarkel::QueryModelsKilledByPlayer);
//    ReversibleHooks::Install("CDarkel", "FindTotalPedsKilledByPlayer", 0x0, &CDarkel::FindTotalPedsKilledByPlayer);
//    ReversibleHooks::Install("CDarkel", "DealWithWeaponChangeAtEndOfFrenzy", 0x43D7A0, &CDarkel::DealWithWeaponChangeAtEndOfFrenzy);
    ReversibleHooks::Install("CDarkel", "CheckDamagedWeaponType", 0x43D9E0, &CDarkel::CheckDamagedWeaponType);
//    ReversibleHooks::Install("CDarkel", "Update", 0x43DAC0, &CDarkel::Update);
    ReversibleHooks::Install("CDarkel", "ResetOnPlayerDeath", 0x43DC10, &CDarkel::ResetOnPlayerDeath);
    ReversibleHooks::Install("CDarkel", "FailKillFrenzy", 0x43DC60, &CDarkel::FailKillFrenzy);
//    ReversibleHooks::Install("CDarkel", "RegisterKillByPlayer", 0x43DCD0, &CDarkel::RegisterKillByPlayer);
//    ReversibleHooks::Install("CDarkel", "RegisterCarBlownUpByPlayer", 0x43DF20, &CDarkel::RegisterCarBlownUpByPlayer);
}

// 0x43D1F0
bool CDarkel::FrenzyOnGoing() {
    return CDarkel::Status == DARKEL_STATUS_1 || CDarkel::Status == DARKEL_STATUS_4;
}

// 0x43CEB0
void CDarkel::Init() {
    CDarkel::Status = DARKEL_STATUS_0;
}

// 0x43CEC0
void CDarkel::DrawMessages() {
    plugin::Call<0x43CEC0>();
}

// 0x43D1E0
eDarkelStatus CDarkel::ReadStatus() {
    return CDarkel::Status;
}

// 0x43D210
void CDarkel::RegisterKillNotByPlayer(const CPed* pKilledPed) {
    plugin::Call<0x43D210, const CPed*>(pKilledPed);
}

// 0x43D2F0
bool CDarkel::ThisPedShouldBeKilledForFrenzy(const CPed* pPed) {
    return plugin::CallAndReturn<bool, 0x43D2F0, const CPed*>(pPed);
}

// 0x
bool CDarkel::ThisVehicleShouldBeKilledForFrenzy(const CVehicle* pVehicle) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*>(pVehicle);
}

// 0x43D3B0
void CDarkel::StartFrenzy(eWeaponType weaponType, int timeLimit, unsigned short killsNeeded, int modelToKill, unsigned short* pStartMessage, int modelToKill2, int modelToKill3, int modelToKill4, bool bStandardSoundAndMessages, bool bNeedHeadShot) {
    plugin::Call<0x43D3B0, eWeaponType, int, unsigned short, int, unsigned short*, int, int, int, bool, bool>(weaponType, timeLimit, killsNeeded, modelToKill, pStartMessage, modelToKill2, modelToKill3, modelToKill4, bStandardSoundAndMessages, bNeedHeadShot);
}

// 0x43D6A0
void CDarkel::ResetModelsKilledByPlayer(int playerId) {
    plugin::Call<0x43D6A0, int>(playerId);
}

// 0x
int CDarkel::QueryModelsKilledByPlayer(int player, int modelId) {
    return plugin::CallAndReturn<int, 0x0, int, int>(player, modelId);
}

// 0x
int CDarkel::FindTotalPedsKilledByPlayer(int player) {
    return plugin::CallAndReturn<int, 0x0, int>(player);
}

// 0x43D7A0
void CDarkel::DealWithWeaponChangeAtEndOfFrenzy() {
    plugin::Call<0x43D7A0>();
}

// 0x43D9E0
bool CDarkel::CheckDamagedWeaponType(eWeaponType damageWeaponId, eWeaponType expectedDamageWeaponId) {
    if (damageWeaponId == -1) {
        return false;
    }

    if (expectedDamageWeaponId == WEAPON_ANYMELEE) {
        switch (damageWeaponId) {
            case WEAPON_UNARMED:
            case WEAPON_BRASSKNUCKLE:
            case WEAPON_GOLFCLUB:
            case WEAPON_NIGHTSTICK:
            case WEAPON_KNIFE:
            case WEAPON_BASEBALLBAT:
            case WEAPON_SHOVEL:
            case WEAPON_POOL_CUE:
            case WEAPON_KATANA:
            case WEAPON_CHAINSAW:
            case WEAPON_DILDO1:
            case WEAPON_DILDO2:
            case WEAPON_VIBE1:
            case WEAPON_VIBE2:
            case WEAPON_FLOWERS:
            case WEAPON_CANE:
                return true;
            default:
                return false;
        }
    }
    if (expectedDamageWeaponId != WEAPON_ANYWEAPON) {
        return false;
    }

    switch (damageWeaponId) {
        case WEAPON_UNARMED:
        case WEAPON_BRASSKNUCKLE:
        case WEAPON_GOLFCLUB:
        case WEAPON_NIGHTSTICK:
        case WEAPON_KNIFE:
        case WEAPON_BASEBALLBAT:
        case WEAPON_SHOVEL:
        case WEAPON_POOL_CUE:
        case WEAPON_KATANA:
        case WEAPON_CHAINSAW:
        case WEAPON_DILDO1:
        case WEAPON_DILDO2:
        case WEAPON_VIBE1:
        case WEAPON_VIBE2:
        case WEAPON_FLOWERS:
        case WEAPON_CANE:
        case WEAPON_GRENADE:
        case WEAPON_TEARGAS:
        case WEAPON_MOLOTOV:
        case WEAPON_ROCKET:
        case WEAPON_ROCKET_HS:
        case WEAPON_FREEFALL_BOMB:
        case WEAPON_PISTOL:
        case WEAPON_PISTOL_SILENCED:
        case WEAPON_DESERT_EAGLE:
        case WEAPON_SHOTGUN:
        case WEAPON_SAWNOFF_SHOTGUN:
        case WEAPON_SPAS12_SHOTGUN:
        case WEAPON_MICRO_UZI:
        case WEAPON_MP5:
        case WEAPON_AK47:
        case WEAPON_M4:
        case WEAPON_TEC9:
        case WEAPON_COUNTRYRIFLE:
        case WEAPON_SNIPERRIFLE:
        case WEAPON_RLAUNCHER:
        case WEAPON_RLAUNCHER_HS:
        case WEAPON_FLAMETHROWER:
        case WEAPON_MINIGUN:
        case WEAPON_REMOTE_SATCHEL_CHARGE:
        case WEAPON_DETONATOR:
        case WEAPON_SPRAYCAN:
        case WEAPON_EXTINGUISHER:
        case WEAPON_CAMERA:
        case WEAPON_NIGHTVISION:
        case WEAPON_INFRARED:
        case WEAPON_EXPLOSION:
        case WEAPON_UZI_DRIVEBY:
            return true;
        default:
            return false;
    }
}

// 0x43DAC0
void CDarkel::Update() {
    plugin::Call<0x43DAC0>();
}

// 0x43DC10
void CDarkel::ResetOnPlayerDeath() {
    CHud::SetHelpMessage(nullptr, true, false, false);
    if (CDarkel::Status == DARKEL_STATUS_1 || CDarkel::Status == DARKEL_STATUS_4) {
        CDarkel::Status = DARKEL_STATUS_3;
        CPopulation::m_AllRandomPedsThisType = -1;
        CDarkel::TimeOfFrenzyStart = CTimer::m_snTimeInMilliseconds;
        CDarkel::DealWithWeaponChangeAtEndOfFrenzy();
    }
}

// 0x43DC60
void CDarkel::FailKillFrenzy() {
    if (CDarkel::Status == DARKEL_STATUS_4) {
        CGameLogic::GameState = GAME_STATE_TITLE;
        CGameLogic::TimeOfLastEvent = CTimer::m_snTimeInMilliseconds;
    }
    CHud::SetHelpMessage(nullptr, true, false, false);
    if (CDarkel::Status == DARKEL_STATUS_1 || CDarkel::Status == DARKEL_STATUS_4) {
        CDarkel::Status = DARKEL_STATUS_3;
        CPopulation::m_AllRandomPedsThisType = -1;
        CDarkel::TimeOfFrenzyStart = CTimer::m_snTimeInMilliseconds;
        CDarkel::DealWithWeaponChangeAtEndOfFrenzy();
    }
}

// 0x43DCD0
void CDarkel::RegisterKillByPlayer(CPed const* pKilledPed, eWeaponType damageWeaponID, bool bHeadShotted, int arg4) {
    plugin::Call<0x43DCD0, CPed const*, eWeaponType, bool, int>(pKilledPed, damageWeaponID, bHeadShotted, arg4);
}

// 0x43DF20
void CDarkel::RegisterCarBlownUpByPlayer(CVehicle* pVehicle, int arg2) {
    plugin::Call<0x43DF20, CVehicle*, int>(pVehicle, arg2);
}