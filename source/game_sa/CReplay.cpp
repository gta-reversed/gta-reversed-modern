#include "StdInc.h"

int &CReplay::Mode = *reinterpret_cast<int *>(0xA43088);

void CReplay::Display()
{
    ((void(__cdecl*)())0x45C210)();
}
