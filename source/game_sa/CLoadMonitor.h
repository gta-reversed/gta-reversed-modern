#pragma once

/*
TODO: size of CLoadMonitor is unknown, and it's uncomplete. 
*/
class CLoadMonitor
{
public:
    char field_0[68];
    std::int32_t m_numModelsRequest;
    char field_48[88];

    void StartTimer(unsigned int timerIndex);
    void EndTimer(unsigned int timerIndex);
};

extern CLoadMonitor& g_LoadMonitor;
