#include "StdInc.h"

#include "CPlaceName.h"

#include "CEntryExitManager.h"
#include "CHud.h"

void CPlaceName::InjectHooks() {
    ReversibleHooks::Install("CPlaceName", "GetForMap", 0x571D90, &CPlaceName::GetForMap);
    ReversibleHooks::Install("CPlaceName", "Process", 0x571F20, &CPlaceName::Process);
}

CPlaceName::CPlaceName() {
    Init();
}

// 0x571F10
void CPlaceName::Init() {
    m_pZone = nullptr;
    m_nAdditionalTimer = 0;
}

// 0x571E40
void CPlaceName::ProcessAfterFrontEndShutDown() {
    CHud::m_ZoneState = NAME_DONT_SHOW;
    CHud::m_pLastZoneName = nullptr;
    m_nAdditionalTimer = 250;
}

// 0x571D90
const char* CPlaceName::GetForMap(float x, float y) {
    CVector posn = CalcPosition();
    CZone* zone = CTheZones::FindSmallestZoneForPosition({ x, y, posn.z }, false);
    return zone->GetTranslatedName();
}

// 0x571F20
void CPlaceName::Process() {
    CVector posn = CalcPosition();
    CZone* smallestZone = CTheZones::FindSmallestZoneForPosition(posn, false);
    if (!smallestZone) {
        Init();
    }

    if ((smallestZone == m_pZone || CGame::currArea == AREA_CODE_1) &&
            m_pZone ||
            smallestZone &&
            m_pZone &&
            strcmp(smallestZone->m_szTextKey, m_pZone->m_szTextKey) == 0 // :thinking
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
