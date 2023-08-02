/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "TheZones.h"

#include <Extensions/ci_string.hpp>

// Variables
eLevelName& CTheZones::m_CurrLevel = *(eLevelName*)0xBA6718;

int32& CTheZones::ZonesRevealed = *(int32*)0xBA372C;
int16& CTheZones::TotalNumberOfMapZones = *(int16*)0xBA1900;
CZone (&CTheZones::NavigationZoneArray)[380] = *(CZone(*)[380])0xBA3798;

int16& CTheZones::TotalNumberOfNavigationZones = *(int16*)0xBA3794;
CZone (&CTheZones::MapZoneArray)[39] = *(CZone(*)[39])0xBA1908;

int16& CTheZones::TotalNumberOfZoneInfos = *(int16*)0xBA1DE8;

void CTheZones::InjectHooks() {
    RH_ScopedClass(CTheZones);
    RH_ScopedCategoryGlobal();

    RH_ScopedGlobalInstall(ResetZonesRevealed, 0x572110);
    RH_ScopedGlobalInstall(GetCurrentZoneLockedOrUnlocked, 0x572130);
    RH_ScopedGlobalInstall(PointLiesWithinZone, 0x572270);
    RH_ScopedGlobalInstall(GetNavigationZone, 0x572590);
    RH_ScopedGlobalInstall(GetMapZone, 0x5725A0);
    RH_ScopedGlobalInstall(Save, 0x5D2E60);
    RH_ScopedGlobalInstall(Load, 0x5D2F40);
    RH_ScopedGlobalInstall(PostZoneCreation, 0x572B70);
    RH_ScopedGlobalInstall(InitZonesPopulationSettings, 0x5720D0);
    RH_ScopedGlobalInstall(Update, 0x572D10);
    RH_ScopedGlobalInstall(SetZoneRadarColours, 0x572CC0);
    RH_ScopedGlobalInstall(FindZoneByLabel, 0x572C40);
    RH_ScopedGlobalInstall(CreateZone, 0x5728A0);
    RH_ScopedGlobalInstall(Init, 0x572670);
    RH_ScopedGlobalInstall(AssignZoneInfoForThisZone, 0x572180);
    //RH_ScopedGlobalInstall(FindZone, 0x572B80, { .reversed = false });
    //RH_ScopedGlobalInstall(CheckZonesForOverlap, 0x572B60, { .reversed = false });
    RH_ScopedGlobalInstall(Calc2DDistanceBetween2Zones, 0x5725B0, { .reversed = false });
    RH_ScopedGlobalInstall(FillZonesWithGangColours, 0x572440, { .reversed = false });
    //RH_ScopedGlobalInstall(GetZoneInfo, 0x572400, { .reversed = false });
    RH_ScopedGlobalInstall(FindSmallestZoneForPosition, 0x572360, { .reversed = false });
    RH_ScopedGlobalInstall(GetLevelFromPosition, 0x572300, { .reversed = false });
    RH_ScopedGlobalInstall(ZoneIsEntirelyContainedWithinOtherZone, 0x572220, { .reversed = false });

}

// 0x5720D0
void CTheZones::InitZonesPopulationSettings() {
    rng::fill(ZoneInfoArray, CZoneInfo{});
}

// 0x572110
void CTheZones::ResetZonesRevealed() {
    rng::fill(ZonesVisited, false);
    ZonesRevealed = 0;
}

// 0x572130
bool CTheZones::GetCurrentZoneLockedOrUnlocked(CVector2D pos) {
    return CTheZones::ZonesVisited[10 * (size_t)((pos.x + 3000.f) / 600.f) - (size_t)((pos.y + 3000.f) / 600.f) + 9] != 0;
}

bool CTheZones::SetCurrentZoneVisited(CVector2D pos, bool visited) {
    bool& wasVisited = CTheZones::ZonesVisited[10 * (size_t)((pos.x + 3000.f) / 600.f) - (size_t)((pos.y + 3000.f) / 600.f) + 9];
    if (wasVisited == visited) {
        return false;
    }
    wasVisited = visited;
    return true;
}

// 0x572180
void CTheZones::AssignZoneInfoForThisZone(int16 newZoneIndex) {
    auto& zone = NavigationZoneArray[newZoneIndex];
    zone.m_nZoneExtraIndexInfo = [&]{
        for (const auto& [i, zoneInfo] : notsa::enumerate(GetNavigationZones())) {
            if (i != newZoneIndex && zoneInfo.GetInfoLabel() == zone.GetInfoLabel()) {
                return zoneInfo.m_nZoneExtraIndexInfo;
            }
        }
        return TotalNumberOfZoneInfos++;
    }();
}

// 0x572220
bool CTheZones::ZoneIsEntirelyContainedWithinOtherZone(CZone* zone1, CZone* zone2) {
    return ((bool(__cdecl*)(CZone*, CZone*))0x572220)(zone1, zone2);
}

// Returns true if point lies within zone
// 0x572270
bool CTheZones::PointLiesWithinZone(const CVector* point, CZone* zone) {
    return (
        (float)zone->m_fX1 <= point->x &&
        (float)zone->m_fX2 >= point->x &&
        (float)zone->m_fY1 <= point->y &&
        (float)zone->m_fY2 >= point->y &&
        (float)zone->m_fZ1 <= point->z &&
        (float)zone->m_fZ2 >= point->z
    );
}

// Returns eLevelName from position
eLevelName CTheZones::GetLevelFromPosition(const CVector& point) {
    return ((eLevelName(__cdecl*)(const CVector&))0x572300)(point);
}

// Returns pointer to zone by a point
// 0x572360
CZone* CTheZones::FindSmallestZoneForPosition(const CVector& point, bool FindOnlyZonesType0) {
    return ((CZone * (__cdecl*)(const CVector&, bool))0x572360)(point, FindOnlyZonesType0);
}

// 0x572400
CZoneInfo* CTheZones::GetZoneInfo(const CVector& point, CZone** outZone) {
    return ((CZoneInfo * (__cdecl*)(const CVector&, CZone**))0x572400)(point, outZone);
}

// 0x572440
void CTheZones::FillZonesWithGangColours(bool disableRadarGangColors) {
    ((void(__cdecl*)(bool))0x572440)(disableRadarGangColors);
}

// Returns pointer to zone by index
// 0x572590
CZone* CTheZones::GetNavigationZone(uint16 index) {
    return &CTheZones::NavigationZoneArray[index];
}

// Returns pointer to zone by index
// 0x5725A0
CZone* CTheZones::GetMapZone(uint16 index) {
    return &CTheZones::MapZoneArray[index];
}

// 0x5725b0
long double CTheZones::Calc2DDistanceBetween2Zones(CZone* zone1, CZone* zone2) {
    return ((long double(__cdecl*)(CZone*, CZone*))0x5725b0)(zone1, zone2);
}

// Initializes CTheZones
// 0x572670
void CTheZones::Init() {
    ZoneScoped;
    
    rng::fill(NavigationZoneArray, CZone{});
    rng::fill(MapZoneArray, CZone{});
    InitZonesPopulationSettings();
    rng::fill(ZonesVisited, false);

    TotalNumberOfZoneInfos       = 0;
    TotalNumberOfNavigationZones = 0;
    ZonesRevealed                = 0;
    TotalNumberOfMapZones        = 0;
    m_CurrLevel                  = LEVEL_NAME_COUNTRY_SIDE;

    CreateZone("SAN_AND", ZONE_TYPE_NAVI, { -3000.f, -3000.f, -2000.f }, { 3000.f, 3000.f, 2000.f }, LEVEL_NAME_COUNTRY_SIDE, "SAN_AND");
    CreateZone("THEMAP", ZONE_TYPE_MAP, { -3000.f, -3000.f, -2000.f }, { 3000.f, 3000.f, 2000.f }, LEVEL_NAME_COUNTRY_SIDE, "THEMAP");
}

// Unlock the current zone
// 0x572800
void CTheZones::SetCurrentZoneAsUnlocked() {
    ((void(__cdecl*)())0x572800)();
}

// Creates a zone
// 0x5728A0
void CTheZones::CreateZone(
    const char* infoLabel,
    eZoneType   type,
    CVector     pos1,
    CVector     pos2,
    eLevelName  level,
    const char* textLabel
) {
    const auto z = [type]{
        switch (type) {
        case ZONE_TYPE_LOCAL_NAVI:
        case ZONE_TYPE_NAVI:       return &NavigationZoneArray[TotalNumberOfNavigationZones++];
        case ZONE_TYPE_MAP:        return &MapZoneArray[TotalNumberOfMapZones++];
        }
        NOTSA_UNREACHABLE();
    }();

    const auto StrCpyUpper = [](auto& dst, auto& src) {
        rng::fill(dst, 0);
        strcpy_s(dst, src);
        for (auto& ch : dst) {
            if (ch == 0) {
                break;
            }
            ch = toupper(ch);
        }
    };
    StrCpyUpper(z->m_TextLabel, textLabel);
    StrCpyUpper(z->m_InfoLabel, infoLabel);

    std::tie(z->m_fX1, z->m_fX2) = std::minmax((int16)pos1.x, (int16)pos2.x);
    std::tie(z->m_fY1, z->m_fY2) = std::minmax((int16)pos1.y, (int16)pos2.y);
    std::tie(z->m_fZ1, z->m_fZ2) = std::minmax((int16)pos1.z, (int16)pos2.z);

    z->m_nLevel = level;

    switch (type) {
    case ZONE_TYPE_LOCAL_NAVI:
    case ZONE_TYPE_NAVI:
        AssignZoneInfoForThisZone(TotalNumberOfNavigationZones - 1);
        break;
    }
}

// Returns 1 if point lies within the specified zonename otherwise return 0
// 0x572B80
bool CTheZones::FindZone(CVector* point, int32 zonename_part1, int32 zonename_part2, eZoneType type) {
    return ((bool(__cdecl*)(CVector*, int32, int32, eZoneType))0x572B80)(point, zonename_part1, zonename_part2, type);
}

//! Find zone by name `name` and of type `type` and check if `point` lies within it
bool CTheZones::FindZone(const CVector& point, std::string_view name, eZoneType type) {
    switch (type) {
    case ZONE_TYPE_INFO:
    case ZONE_TYPE_NAVI:
        break;
    default:
        return false;
    }

    for (auto& zone : GetNavigationZones()) {
        if ((type == ZONE_TYPE_INFO ? zone.GetInfoLabel() : zone.GetNaviLabel()) == name) {
            if (PointLiesWithinZone(&point, &zone)) {
                return true;
            }
        }
    }

    return false;
}

// Returns pointer to zone by index
// 0x572C40
int16 CTheZones::FindZoneByLabel(const char* name, eZoneType type) {
    assert(type == eZoneType::ZONE_TYPE_INFO); // Originally an `if` returning `-1`, but let's be safe

    for (auto&& [i, v] : notsa::enumerate(GetNavigationZones())) {
        if (name == v.GetInfoLabel()) {
            return (int16)i;
        }
    }
    return -1;
}

// 0x572cc0
void CTheZones::SetZoneRadarColours(int16 index, char radarMode, uint8 red, uint8 green, uint8 blue) {
    const auto zone = &ZoneInfoArray[NavigationZoneArray[index].m_nZoneExtraIndexInfo];
    zone->radarMode = radarMode;
    zone->ZoneColor = { red, green, blue, 255 };
}

// Updates CTheZones info
// 0x572D10
void CTheZones::Update() {
    ZoneScoped;

    const auto DELAY = 5000;

    static auto CountSeconds = CTimer::GetTimeInMS() - DELAY;
    assert(CTimer::GetTimeInMS() >= DELAY); // Avoid underflow

    if (CGame::CanSeeOutSideFromCurrArea()) { // Inverted
        if (CTimer::GetTimeInMS() - CountSeconds > DELAY) {
            // Code from 0x572800
            const auto pos = FindPlayerCoors();
            m_CurrLevel = CTheZones::GetLevelFromPosition(pos);
            if (   !CTheScripts::bPlayerIsOffTheMap
                && CGame::CanSeeOutSideFromCurrArea()
                && SetCurrentZoneVisited(pos, true)
            ) {
                CTheZones::ZonesRevealed++;
            }
        }
    } else {
        CountSeconds = CTimer::GetTimeInMS();
    }
}

// Save CTheZones info
// 0x5D2E60
void CTheZones::Save() {
    CGenericGameStorage::SaveDataToWorkBuffer(&m_CurrLevel, 4);
    CGenericGameStorage::SaveDataToWorkBuffer(&TotalNumberOfNavigationZones, 2);
    CGenericGameStorage::SaveDataToWorkBuffer(&TotalNumberOfZoneInfos, 2);
    CGenericGameStorage::SaveDataToWorkBuffer(&TotalNumberOfMapZones, 2);

    for (int32 i = 0; i < TotalNumberOfNavigationZones; i++) {
        CGenericGameStorage::SaveDataToWorkBuffer(&NavigationZoneArray[i], 0x20);
    }

    for (int32 i = 0; i < TotalNumberOfZoneInfos; i++) {
        CGenericGameStorage::SaveDataToWorkBuffer(&ZoneInfoArray[i], 0x11);
    }

    for (int32 i = 0; i < TotalNumberOfMapZones; i++) {
        CGenericGameStorage::SaveDataToWorkBuffer(&MapZoneArray[i], 0x20);
    }

    SaveDataToWorkBuffer(ZonesVisited);
    CGenericGameStorage::SaveDataToWorkBuffer(&ZonesRevealed, 4);
}

// Load CTheZones info
// 0x5D2F40
void CTheZones::Load() {
    Init();

    CGenericGameStorage::LoadDataFromWorkBuffer(&m_CurrLevel, 4);
    CGenericGameStorage::LoadDataFromWorkBuffer(&TotalNumberOfNavigationZones, 2);
    CGenericGameStorage::LoadDataFromWorkBuffer(&TotalNumberOfZoneInfos, 2);
    CGenericGameStorage::LoadDataFromWorkBuffer(&TotalNumberOfMapZones, 2);

    for (int32 i = 0; i < TotalNumberOfNavigationZones; i++) {
        CGenericGameStorage::LoadDataFromWorkBuffer(&NavigationZoneArray[i], 0x20u);
    }

    for (int32 i = 0; i < TotalNumberOfZoneInfos; i++) {
        CGenericGameStorage::LoadDataFromWorkBuffer(&ZoneInfoArray[i], 0x11u);
    }

    for (int32 i = 0; i < TotalNumberOfMapZones; i++) {
        CGenericGameStorage::LoadDataFromWorkBuffer(&MapZoneArray[i], 0x20u);
    }
    LoadDataFromWorkBuffer(ZonesVisited);
    CGenericGameStorage::LoadDataFromWorkBuffer(&ZonesRevealed, 4u);
}

// dummy function
// 0x572B70
void CTheZones::PostZoneCreation() {
    // NOP
}

const char* CTheZones::GetZoneName(const CVector& point) {
    CZone* zone{};
    auto extraInfo = GetZoneInfo(point, &zone);
    if (zone)
        return zone->GetTranslatedName();
    return "Unknown zone";
}
