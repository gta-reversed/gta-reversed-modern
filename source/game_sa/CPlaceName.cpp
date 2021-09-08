#include "StdInc.h"

#include "CPlaceName.h"

#include "CEntryExitManager.h"

void CPlaceName::InjectHooks() {
    ReversibleHooks::Install("CPlaceName", "Init", 0x571E40, &CPlaceName::Init);
    ReversibleHooks::Install("CPlaceName", "GetForMap", 0x571D90, &CPlaceName::GetForMap);
    ReversibleHooks::Install("CPlaceName", "Process", 0x571F20, &CPlaceName::Process);
}

// 0x571E40
void CPlaceName::Init() {
    CHud::m_ZoneState     = 0;
    CHud::m_pLastZoneName = nullptr;
    m_nAdditionalTimer    = 250;
}

// 0x571D80
void CPlaceName::Clear() {
    m_pZone = nullptr;
    m_nAdditionalTimer = 0;
}

// 0x571D90
const char* CPlaceName::GetForMap(float x, float y) {
    CVector posn;
    auto player = FindPlayerPed();
    if (player->bInVehicle) {
        posn = player->m_pVehicle->GetPosition();
    } else {
        posn = player->GetPosition();
        CEntryExitManager::GetPositionRelativeToOutsideWorld(posn);
    }

    CZone* zone = CTheZones::FindSmallestZoneForPosition({x, y, posn.z}, false);
    auto name = zone->GetTranslatedName();
    printf("%s\n", name);
    return name;
}

// 0x571F20
void CPlaceName::Process() {
    CVector posn;
    auto player = FindPlayerPed();
    if (player->bInVehicle) {
        posn = player->m_pVehicle->GetPosition();
    } else {
        posn = player->GetPosition();
        CEntryExitManager::GetPositionRelativeToOutsideWorld(posn);
    }

    CZone* smallestZone = CTheZones::FindSmallestZoneForPosition(posn, false);
    if (!smallestZone) {
        Clear();
    }

    if ((smallestZone == m_pZone || CGame::currArea) &&
            m_pZone ||
            smallestZone &&
            m_pZone &&
            *smallestZone->m_szTextKey == *m_pZone->m_szTextKey &&
            *&smallestZone->m_szTextKey[4] == *&m_pZone->m_szTextKey[4]
    ) {
        if (m_nAdditionalTimer) {
            m_nAdditionalTimer -= 1;
        }
    } else {
        m_pZone = smallestZone;
        m_nAdditionalTimer = 250;
    }

    Display();
}

// 0x571E60
void CPlaceName::Display() const {
    if (m_pZone) {
        const char* name = m_pZone->GetTranslatedName();
        CHud::SetZoneName(const_cast<char*>(name), false);
    } else {
        CHud::SetZoneName(nullptr, false);
    }
}
