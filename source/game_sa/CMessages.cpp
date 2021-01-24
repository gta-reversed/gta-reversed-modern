#include "StdInc.h"

void CMessages::Init()
{
    ((void(__cdecl*)())0x69EE00)();
}

void CMessages::Display(bool flag)
{
    ((void(__cdecl*)(bool))0x69EFC0)(flag);
}

void CMessages::ClearAllMessagesDisplayedByGame(uint8_t unk)
{
    ((void(__cdecl*)(uint8_t))0x69EDC0)(unk);
}
