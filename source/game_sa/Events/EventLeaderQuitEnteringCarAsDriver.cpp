#include "StdInc.h"
#include "EventLeaderQuitEnteringCarAsDriver.h"


void CEventLeaderQuitEnteringCarAsDriver::InjectHooks()
{
    RH_ScopedClass(CEventLeaderQuitEnteringCarAsDriver);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x63A110);
    RH_ScopedVirtualInstall(AffectsPedGroup, 0x4B1010);
}

// 0x63A110
CEventLeaderQuitEnteringCarAsDriver* CEventLeaderQuitEnteringCarAsDriver::Constructor()
{
    this->CEventLeaderQuitEnteringCarAsDriver::CEventLeaderQuitEnteringCarAsDriver();
    return this;
}

// 0x4B1010
bool CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup(CPedGroup* pedGroup)
{
    return CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup_Reversed(pedGroup);
}

bool CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup_Reversed(CPedGroup* pedGroup) {
    const auto oe = pedGroup->GetIntelligence().GetOldEvent();
    return oe && oe->GetEvent().GetEventType() == EVENT_LEADER_ENTERED_CAR_AS_DRIVER;
}

