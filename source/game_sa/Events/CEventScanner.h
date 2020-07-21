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

class CPedAcquaintanceScanner {
public:
    static float& ms_fThresholdDotProduct;

    CTaskTimer m_timer;
    bool m_bScanAllowedScriptPed;
    bool m_bScanAllowedInVehicle;
    bool m_bScanAllowedScriptedTask;
};

class CVehiclePotentialCollisionScanner
{
public:
    CTaskTimer m_timer;
};

class CObjectPotentialCollisionScanner
{
public:
    CTaskTimer m_timer;
};

class CSexyPedScanner
{
public:
    CTaskTimer m_timer;
};

class CNearbyFireScanner
{
public:
    CTaskTimer m_timer;
};

VALIDATE_SIZE(CPedAcquaintanceScanner, 0x10);
VALIDATE_SIZE(CVehiclePotentialCollisionScanner, 0xC);
VALIDATE_SIZE(CObjectPotentialCollisionScanner, 0xC);
VALIDATE_SIZE(CSexyPedScanner, 0xC);
VALIDATE_SIZE(CNearbyFireScanner, 0xC);

class CEventScanner {
public:
    std::uint32_t m_nNextScanTime;
    CVehiclePotentialCollisionScanner m_vehiclePotentialCollisionScanner;
    CObjectPotentialCollisionScanner m_objectPotentialCollisionScanner;
    CAttractorScanner m_attractorScanner;
    CPedAcquaintanceScanner m_pedAcquaintanceScanner;
    CSexyPedScanner m_sexyPedScanner;
    CNearbyFireScanner m_nearbyFireScanner;

    void ScanForEvents(CPed* pPed);
    void ScanForEventsNow(CPed* ped, bool bDontScan);
};

VALIDATE_SIZE(CEventScanner, 0xD4);
