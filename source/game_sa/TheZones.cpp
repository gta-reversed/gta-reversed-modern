/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "TheZones.h"

// Variables
eLevelName& CTheZones::m_CurrLevel = *(eLevelName*)0xBA6718;

char* CTheZones::ZonesVisited = (char*)0xBA3730;
int32& CTheZones::ZonesRevealed = *(int32*)0xBA372C;
int16& CTheZones::TotalNumberOfMapZones = *(int16*)0xBA1900;
CZone (&CTheZones::NavigationZoneArray)[380] = *(CZone(*)[380])0xBA3798;

int16& CTheZones::TotalNumberOfNavigationZones = *(int16*)0xBA3794;
CZone (&CTheZones::MapZoneArray)[39] = *(CZone(*)[39])0xBA1908;

int16& CTheZones::TotalNumberOfZoneInfos = *(int16*)0xBA1DE8;

void CTheZones::InjectHooks() {
    RH_ScopedClass(CTheZones);
    RH_ScopedCategoryGlobal();
    RH_ScopedInstall(ResetZonesRevealed, 0x572110);
    RH_ScopedInstall(GetCurrentZoneLockedOrUnlocked, 0x572130);
    RH_ScopedInstall(PointLiesWithinZone, 0x572270);
    RH_ScopedInstall(GetNavigationZone, 0x572590);
    RH_ScopedInstall(GetMapZone, 0x5725A0);
    RH_ScopedInstall(Save, 0x5D2E60);
    RH_ScopedInstall(Load, 0x5D2F40);
    RH_ScopedInstall(PostZoneCreation, 0x572B70);
}

// 0x5720D0
void CTheZones::InitZonesPopulationSettings() {
    ((void(__cdecl*)())0x5720D0)();
}

// 0x572110
void CTheZones::ResetZonesRevealed() {
    memset(ZonesVisited, 0, 100); // TODO: sizeof(CTheZones::ExploredTerritoriesArray)
    ZonesRevealed = 0;
}

// 0x572130
bool CTheZones::GetCurrentZoneLockedOrUnlocked(float posx, float posy) {
    return CTheZones::ZonesVisited[10 * (uint8)((posx + 3000.0) * 0.0016666667) - (uint8)((posy + 3000.0) * 0.0016666667) + 9] != 0; // todo: ugly
}

// 0x572180
void CTheZones::AssignZoneInfoForThisZone(int16 index) {
    ((void(__cdecl*)(int16))0x572180)(index);
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

    ((void(__cdecl*)())0x572670)();
}

// Unlock the current zone
// 0x572800
void CTheZones::SetCurrentZoneAsUnlocked() {
    ((void(__cdecl*)())0x572800)();
}

// Creates a zone
// 0x5728A0
void CTheZones::CreateZone(const char* name, eZoneType type, float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, eLevelName island, const char* GXT_key) {
    ((void(__cdecl*)(const char*, eZoneType, float, float, float, float, float, float, eLevelName island, const char*))0x5728A0)(name, type, posX1, posY1, posZ1, posX2, posY2, posZ2, island, GXT_key);
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
    return ((int16(__cdecl*)(const char*, eZoneType))0x572C40)(name, type);
}

// 0x572cc0
void CTheZones::SetZoneRadarColours(int16 index, char flag, uint8 red, uint8 green, uint8 blue) {
    ((void(__cdecl*)(int16, char, uint8, uint8, uint8))0x572cc0)(index, flag, red, green, blue);
}

// Updates CTheZones info
// 0x572D10
void CTheZones::Update() {
    ZoneScoped;

    ((void(__cdecl*)())0x572D10)();
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

    CGenericGameStorage::SaveDataToWorkBuffer(ZonesVisited, 100);
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
    CGenericGameStorage::LoadDataFromWorkBuffer(ZonesVisited, 100);
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
