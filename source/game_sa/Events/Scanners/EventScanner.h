/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskTimer.h"
#include "AttractorScanner.h"
#include "NearbyFireScanner.h"
#include "SexyPedScanner.h"
#include "PedAcquaintanceScanner.h"
#include "VehiclePotentialCollisionScanner.h"
#include "ObjectPotentialCollisionScanner.h"

class CPed;

class CEventScanner {
private:
    static inline uint32 m_sDeadPedWalkingTimer = *(uint32*)0xC0B038;

public:
    static void InjectHooks();

    CEventScanner();
    ~CEventScanner() = default;

    void Clear();
    void ScanForEvents(CPed& ped);
    void ScanForEventsNow(const CPed& ped, bool bDontScan);

private:
    // 0x605300
    CEventScanner* Constructor() {
        this->CEventScanner::CEventScanner();
        return this;
    }

private:
    uint32                            m_NextScanTime{};
    CVehiclePotentialCollisionScanner m_VehCollisionScanner{};
    CObjectPotentialCollisionScanner  m_ObjCollisionScanner{};
    CAttractorScanner                 m_AttractorScanner{};
    CPedAcquaintanceScanner           m_AcquaintanceScanner{};
    CSexyPedScanner                   m_SexyPedScanner{};
    CNearbyFireScanner                m_FireScanner{};
};
VALIDATE_SIZE(CEventScanner, 0xD4);
