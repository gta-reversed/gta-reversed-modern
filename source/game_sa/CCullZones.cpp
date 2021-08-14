#include "StdInc.h"

CCullZoneReflection (&CCullZones::aMirrorAttributeZones)[72] = *(CCullZoneReflection(*)[72])0xC815C0;
CCullZone (&CCullZones::aTunnelAttributeZones)[40] = *(CCullZone(*)[40])0xC81C80;
CCullZone (&CCullZones::aAttributeZones)[1300] = *(CCullZone(*)[1300])0xC81F50;
int& CCullZones::CurrentFlags_Player = *(int*)0xC87AB8;
int& CCullZones::CurrentFlags_Camera = *(int*)0xC87ABC;
int& CCullZones::NumTunnelAttributeZones = *(int*)0xC87AC0;
int& CCullZones::NumMirrorAttributeZones = *(int*)0xC87AC4;
int& CCullZones::NumAttributeZones = *(int*)0xC87AC8;
bool& CCullZones::bMilitaryZonesDisabled = *(bool*)0xC87ACD;

void CCullZones::InjectHooks() {
    ReversibleHooks::Install("CCullZones", "Init", 0x72D6B0, &CCullZones::Init);
    ReversibleHooks::Install("CCullZones", "AddCullZone", 0x72DF70, &CCullZones::AddCullZone);
    ReversibleHooks::Install("CCullZones", "AddTunnelAttributeZone", 0x72DB50, &CCullZones::AddTunnelAttributeZone);
    ReversibleHooks::Install("CCullZones", "AddMirrorAttributeZone", 0x72DC10, &CCullZones::AddMirrorAttributeZone);
    ReversibleHooks::Install("CCullZones", "InRoomForAudio", 0x72DD70, &CCullZones::InRoomForAudio);
    ReversibleHooks::Install("CCullZones", "CamNoRain", 0x72DDB0, &CCullZones::CamNoRain);
    ReversibleHooks::Install("CCullZones", "PlayerNoRain", 0x72DDC0, &CCullZones::PlayerNoRain);
    ReversibleHooks::Install("CCullZones", "FewerPeds", 0x72DD90, &CCullZones::FewerPeds);
    ReversibleHooks::Install("CCullZones", "NoPolice", 0x72DD50, &CCullZones::NoPolice);
    ReversibleHooks::Install("CCullZones", "DoExtraAirResistanceForPlayer", 0x72DDD0, &CCullZones::DoExtraAirResistanceForPlayer);
    ReversibleHooks::Install("CCullZones", "FindTunnelAttributesForCoors", 0x72D9F0, &CCullZones::FindTunnelAttributesForCoors);
    ReversibleHooks::Install("CCullZones", "FindMirrorAttributesForCoors", 0x72DA70, &CCullZones::FindMirrorAttributesForCoors);
    ReversibleHooks::Install("CCullZones", "FindZoneWithStairsAttributeForPlayer", 0x72DAD0, &CCullZones::FindZoneWithStairsAttributeForPlayer);
    ReversibleHooks::Install("CCullZones", "FindAttributesForCoors", 0x72D970, &CCullZones::FindAttributesForCoors);
    ReversibleHooks::Install("CCullZones", "Update", 0x72DEC0, &CCullZones::Update);
}

// 0x72D6B0
void CCullZones::Init() {
    NumAttributeZones = 0;
    CurrentFlags_Player = 0;
    CurrentFlags_Camera = 0;
}

// flags: see eZoneAttributes
// 0x72DF70
void CCullZones::AddCullZone(const CVector& center, float zero1, float fWidthY, float fBottomZ, float fWidthX, float zero2, float fTopZ, uint16_t flags) {
    int i = NumAttributeZones;

    if ((flags & (eZoneAttributes::UNKNOWN_1 | eZoneAttributes::UNKNOWN_2))) {
        AddTunnelAttributeZone(center, zero1, fWidthY, fBottomZ, fWidthX, zero2, fTopZ, flags);
        flags &= ~(eZoneAttributes::UNKNOWN_2 | eZoneAttributes::UNKNOWN_1);
    }

    // Will be computed if flags less than 0x880 (UNKNOWN_1 + UNKNOWN_2)
    if (flags) {
        aAttributeZones[i].zoneDef.x = (short)(center.x - zero1 - fWidthX);
        aAttributeZones[i].zoneDef.y = (short)(center.y - fWidthY - zero2);
        aAttributeZones[i].zoneDef.field_4 = (short)(zero1 + zero1);
        aAttributeZones[i].zoneDef.widthY = (short)(2 * fWidthY);
        aAttributeZones[i].zoneDef.bottomZ = (short)(fBottomZ);
        aAttributeZones[i].zoneDef.widthX = (short)(2 * fWidthX);
        aAttributeZones[i].zoneDef.field_A = (short)(2 * zero2);
        aAttributeZones[i].zoneDef.topZ = (short)(fTopZ);
        aAttributeZones[i].flags = static_cast<eZoneAttributes>(flags);

        NumAttributeZones += 1;
    }
}

// flags: see eZoneAttributes
// 0x72DB50
void CCullZones::AddTunnelAttributeZone(const CVector& center, float unk1, float fWidthY, float fBottomZ, float fWidthX, float unk2, float fTopZ, uint16_t flags) {
    int i = NumTunnelAttributeZones;
    auto& attribute = aTunnelAttributeZones[i];

    attribute.zoneDef.x = (short)(center.x - unk1 - fWidthX);
    attribute.zoneDef.y = (short)(center.y - fWidthY - unk2);
    attribute.zoneDef.field_4 = (short)(2 * unk1);
    attribute.zoneDef.widthY = (short)(2 * fWidthY);
    attribute.zoneDef.bottomZ = (short)(fBottomZ);
    attribute.zoneDef.widthX = (short)(2 * fWidthX);
    attribute.zoneDef.field_A = (short)(2 * unk2);
    attribute.zoneDef.topZ = (short)(fTopZ);
    attribute.flags = static_cast<eZoneAttributes>(flags);

    NumTunnelAttributeZones += 1;
}

// 0x72DC10
void CCullZones::AddMirrorAttributeZone(const CVector& center, float unk1, float fWidthY, float fBottomZ, float fWidthX, float unk2, float fTopZ, eZoneAttributes flags, float cm, float vX, float vY, float vZ) {
    int i = NumMirrorAttributeZones;
    auto& attribute = aMirrorAttributeZones[i];

    attribute.zoneDef.x = (short)(center.x - unk1 - fWidthX);
    attribute.zoneDef.y = (short)(center.y - fWidthY - unk2);
    attribute.zoneDef.field_4 = (short)(2 * unk1);
    attribute.zoneDef.widthY = (short)(2 * fWidthY);
    attribute.zoneDef.bottomZ = (short)(fBottomZ);
    attribute.zoneDef.widthX = (short)(2 * fWidthX);
    attribute.zoneDef.field_A = (short)(2 * unk2);
    attribute.zoneDef.topZ = (short)(fTopZ);
    attribute.flags = (short)(static_cast<eZoneAttributes>(flags));
    attribute.cm = (short)(cm);

    attribute.vx = (char)(vX * 100.0f);
    attribute.vy = (char)(vY * 100.0f);
    attribute.vz = (char)(vZ * 100.0f);

    NumMirrorAttributeZones += 1;
}

// 0x72DD70
bool CCullZones::InRoomForAudio() {
    return (CurrentFlags_Camera & eZoneAttributes::IN_ROOMS_FOR_AUDIO) != 0;
}

// 0x72DDB0
bool CCullZones::CamNoRain() {
    return (CurrentFlags_Camera & eZoneAttributes::CAM_NO_RAIN) != 0;
}

// 0x72DDC0
bool CCullZones::PlayerNoRain() {
    return (CurrentFlags_Player & eZoneAttributes::CAM_NO_RAIN) != 0;
}

// 0x72DD90
bool CCullZones::FewerPeds() {
    return (CurrentFlags_Player & eZoneAttributes::IN_ROOMS_FEWER_PEDS) != 0;
}

// 0x72DD50
bool CCullZones::NoPolice() {
    return (CurrentFlags_Player & eZoneAttributes::NO_POLICE) != 0;
}

// 0x72DDD0
bool CCullZones::DoExtraAirResistanceForPlayer() {
    return (CurrentFlags_Player & eZoneAttributes::EXTRA_AIR_RESISTANCE) != 0;
}

// 0x72D9F0
eZoneAttributes CCullZones::FindTunnelAttributesForCoors(CVector point) {
    if (NumTunnelAttributeZones <= 0)
        return eZoneAttributes::NONE;

    int out = eZoneAttributes::NONE;
    for (auto& tunnelAttributeZone : aTunnelAttributeZones) {
        if (tunnelAttributeZone.IsPointWithin(point)) {
            out |= tunnelAttributeZone.flags;
        }
    }

    return static_cast<eZoneAttributes>(out);
}

// NOTSA
CCullZoneReflection* CCullZones::FindMirrorAttributesForCoors_(CVector cameraPosition) {
    if (NumMirrorAttributeZones <= 0)
        return nullptr;

    for (auto& pCullZoneReflection: aMirrorAttributeZones) {
        if (pCullZoneReflection.IsPointWithin(cameraPosition))
            return &pCullZoneReflection;
    }

    return nullptr;
}

// 0x72DA70
CCullZoneReflection* CCullZones::FindMirrorAttributesForCoors(float x, float y, float z) {
    CVector cameraPosition{x, y, z};
    return FindMirrorAttributesForCoors_(cameraPosition);
}

// 0x72DAD0
CCullZone* CCullZones::FindZoneWithStairsAttributeForPlayer() {
    if (NumAttributeZones <= 0)
        return nullptr;

    for (auto& pCullZone : aAttributeZones) {
        if ((pCullZone.flags & eZoneAttributes::CAM_STAIRS_FOR_PLAYER) != 0 && pCullZone.IsPointWithin(FindPlayerCoors()))
            return &pCullZone;
    }

    return nullptr;
}

// 0x72D970
eZoneAttributes CCullZones::FindAttributesForCoors(float x, float y) {
    if (NumAttributeZones <= 0)
        return eZoneAttributes::NONE;

    int out = eZoneAttributes::NONE;
    for (auto& attributeZone : aAttributeZones) {
        if (attributeZone.IsPointWithin({x, y, 0})) {
            out |= attributeZone.flags;
        }
    }

    return static_cast<eZoneAttributes>(out);
}

// 0x72DEC0
void CCullZones::Update() {
    if ((CTimer::m_FrameCounter & 7) == 2) {
        auto cameraPosition = TheCamera.GetGameCamPosition();
        CurrentFlags_Camera = FindAttributesForCoors(cameraPosition->x, cameraPosition->y);
    }
    else if ((CTimer::m_FrameCounter & 7) == 6) {
        CVector posn = FindPlayerCoors();
        CurrentFlags_Player = FindAttributesForCoors(posn.x, posn.y);
        if (!bMilitaryZonesDisabled && (CurrentFlags_Player & eZoneAttributes::MILITARY_ZONE) != 0) {
            auto player = FindPlayerPed();
            if (player->IsAlive()) {
                player->SetWantedLevelNoDrop(5);
            }
        }
    }
}
