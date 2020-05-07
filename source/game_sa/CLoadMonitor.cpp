#include "StdInc.h"

CLoadMonitor& g_LoadMonitor = *reinterpret_cast<CLoadMonitor*> (0xB72978);
 
void CLoadMonitor::StartTimer(unsigned int timerIndex)
{
    plugin::CallMethod<0x53D050, CLoadMonitor*, unsigned int> (this, timerIndex);
}

void CLoadMonitor::EndTimer(unsigned int timerIndex)
{
    plugin::CallMethod<0x53D070, CLoadMonitor*, unsigned int>(this, timerIndex);
}
