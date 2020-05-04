#include "StdInc.h"

void(*(&CCheat::m_aCheatFunctions)[92])() = *reinterpret_cast<void(*(*)[92])()>(0x8A5B58);

int(&CCheat::m_aCheatHashKeys)[92] = *reinterpret_cast<int(*)[92]>(0x8A5CC8);
char(&CCheat::m_CheatString)[30] = *reinterpret_cast<char(*)[30]>(0x969110);
bool(&CCheat::m_aCheatsActive)[92] = *reinterpret_cast<bool(*)[92]>(0x969130);
bool& CCheat::m_bHasPlayerCheated = *reinterpret_cast<bool*>(0x96918C);

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
