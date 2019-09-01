#pragma once

class CLoadMonitor
{
public:
    void StartTimer(unsigned int timerIndex);
    void EndTimer(unsigned int timerIndex);
};

extern CLoadMonitor* g_LoadMonitor;