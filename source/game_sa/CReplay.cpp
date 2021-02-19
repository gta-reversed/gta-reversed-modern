#include "StdInc.h"

eReplayMode &CReplay::Mode = *reinterpret_cast<eReplayMode*>(0xA43088);

void CReplay::Display()
{
    ((void(__cdecl*)())0x45C210)();
}
