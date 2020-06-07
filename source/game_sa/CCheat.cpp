#include "StdInc.h"

void(*(&CCheat::m_aCheatFunctions)[92])() = *reinterpret_cast<void(*(*)[92])()>(0x8A5B58);

int(&CCheat::m_aCheatHashKeys)[92] = *reinterpret_cast<int(*)[92]>(0x8A5CC8);
char(&CCheat::m_CheatString)[30] = *reinterpret_cast<char(*)[30]>(0x969110);
bool(&CCheat::m_aCheatsActive)[92] = *reinterpret_cast<bool(*)[92]>(0x969130);
bool& CCheat::m_bHasPlayerCheated = *reinterpret_cast<bool*>(0x96918C);

void CCheat::InjectHooks()
{
    HookInstall(0x438FF0, &CCheat::SuicideCheat);
}

void CCheat::SuicideCheat()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal(0x438FF0);
#else
    CPedDamageResponseCalculator damageCalculator(nullptr, 1000.0f, WEAPON_UNARMED, PED_PIECE_TORSO, 0);
    CEventDamage damageEvent(nullptr, CTimer::m_snTimeInMilliseconds, WEAPON_UNARMED, PED_PIECE_TORSO, 0, 0, 0);
    CPlayerPed* pPlayer = FindPlayerPed(-1);
    if (damageEvent.AffectsPed(pPlayer))
        damageCalculator.ComputeDamageResponse(pPlayer, &damageEvent.m_damageResponse, true);
    else
        damageEvent.m_damageResponse.m_bDamageCalculated = 1;
    pPlayer->GetEventGroup().Add(&damageEvent, 0);
#endif
}

bool CCheat::IsZoneStreamingAllowed()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x407410>();
#else
    return CCheat::m_aCheatsActive[CHEAT_ELVIS_IS_EVERYWHERE]
        || CCheat::m_aCheatsActive[CHEAT_PEDS_ATTACK_YOU_WITH_ROCKETS]
        || CCheat::m_aCheatsActive[CHEAT_BEACH_PARTY]
        || CCheat::m_aCheatsActive[CHEAT_GANGMEMBERS_EVERYWHERE]
        || CCheat::m_aCheatsActive[CHEAT_NINJA_THEME]
        || CCheat::m_aCheatsActive[CHEAT_SLUT_MAGNET]
        || CCheat::m_aCheatsActive[CHEAT_FUNHOUSE_THEME]
        || CCheat::m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC];
#endif
}
