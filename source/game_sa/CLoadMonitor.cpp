#include "StdInc.h"

CLoadMonitor& g_LoadMonitor = *reinterpret_cast<CLoadMonitor*> (0xB72978);

//0x53D030
void CLoadMonitor::BeginFrame()
{
    ((CLoadMonitor*(__thiscall*)(CLoadMonitor*))0x53D030)(this);
}

void CLoadMonitor::StartTimer(unsigned int timerIndex)
{
    plugin::CallMethod<0x53D050, CLoadMonitor*, unsigned int> (this, timerIndex);
}

void CLoadMonitor::EndTimer(unsigned int timerIndex)
{
    plugin::CallMethod<0x53D070, CLoadMonitor*, unsigned int>(this, timerIndex);
}
