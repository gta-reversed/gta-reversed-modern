#include "StdInc.h"

void(*(&CCheat::m_aCheatFunctions)[92])() = *reinterpret_cast<void(*(*)[92])()>(0x8A5B58);

int(&CCheat::m_aCheatHashKeys)[92] = *reinterpret_cast<int(*)[92]>(0x8A5CC8);
char(&CCheat::m_CheatString)[30] = *reinterpret_cast<char(*)[30]>(0x969110);
bool(&CCheat::m_aCheatsActive)[92] = *reinterpret_cast<bool(*)[92]>(0x969130);
bool& CCheat::m_bHasPlayerCheated = *reinterpret_cast<bool*>(0x96918C);