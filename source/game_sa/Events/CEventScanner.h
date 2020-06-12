/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskTimer.h"
#include "CAttractorScanner.h"

class CPed;

class CEventScanner {
public:
    int field_0;
    CTaskTimer field_4;
    CTaskTimer field_10;
    CAttractorScanner m_attractorScanner;
    CTaskTimer field_AC;
    char field_B8;
    char field_B9;
    char field_BA;
    char field_BB;
    CTaskTimer field_BC;
    CTaskTimer field_C8;

    void ScanForEvents(CPed* pPed);
    void ScanForEventsNow(CPed* ped, bool bDontScan);
};

VALIDATE_SIZE(CEventScanner, 0xD4);