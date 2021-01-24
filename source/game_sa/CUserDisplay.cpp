#include "StdInc.h"

COnscreenTimer& CUserDisplay::OnscnTimer = *(COnscreenTimer*)0xBA1788;

void CUserDisplay::Init()
{
    plugin::Call<0x571EE0>();
}
