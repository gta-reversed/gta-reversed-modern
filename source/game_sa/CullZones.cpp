#include "StdInc.h"

#include "CullZones.h"

CCullZoneReflection (&CCullZones::aMirrorAttributeZones)[72] = *(CCullZoneReflection(*)[72])0xC815C0;
CCullZone (&CCullZones::aTunnelAttributeZones)[40] = *(CCullZone(*)[40])0xC81C80;
CCullZone (&CCullZones::aAttributeZones)[1300] = *(CCullZone(*)[1300])0xC81F50;
int32& CCullZones::CurrentFlags_Player = *(int32*)0xC87AB8;
int32& CCullZones::CurrentFlags_Camera = *(int32*)0xC87ABC;
int32& CCullZones::NumTunnelAttributeZones = *(int32*)0xC87AC0;
int32& CCullZones::NumMirrorAttributeZones = *(int32*)0xC87AC4;
int32& CCullZones::NumAttributeZones = *(int32*)0xC87AC8;
bool& CCullZones::bMilitaryZonesDisabled = *(bool*)0xC87ACD;

void CCullZones::InjectHooks() {
    RH_ScopedClass(CCullZones);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x72D6B0);
    RH_ScopedInstall(AddCullZone, 0x72DF70);
    RH_ScopedInstall(AddTunnelAttributeZone, 0x72DB50);
    RH_ScopedInstall(AddMirrorAttributeZone, 0x72DC10);
    RH_ScopedInstall(InRoomForAudio, 0x72DD70);
    RH_ScopedInstall(CamNoRain, 0x72DDB0);
    RH_ScopedInstall(PlayerNoRain, 0x72DDC0);
    RH_ScopedInstall(FewerPeds, 0x72DD90);
    RH_ScopedInstall(NoPolice, 0x72DD50);
    RH_ScopedInstall(DoExtraAirResistanceForPlayer, 0x72DDD0);
    RH_ScopedInstall(FindTunnelAttributesForCoors, 0x72D9F0);
    RH_ScopedInstall(FindMirrorAttributesForCoors, 0x72DA70);
    RH_ScopedInstall(FindZoneWithStairsAttributeForPlayer, 0x72DAD0);
    RH_ScopedInstall(FindAttributesForCoors, 0x72D970);
    RH_ScopedInstall(Update, 0x72DEC0);
}

// 0x72D6B0
void CCullZones::Init() {
    NumAttributeZones = 0;
    CurrentFlags_Player = 0;
    CurrentFlags_Camera = 0;
}

// flags: see eZoneAttributes
// 0x72DF70
void CCullZones::AddCullZone(const CVector& center, float zero1, float fWidthY, float fBottomZ, float fWidthX, float zero2, float fTopZ, uint16 flags) {
    int32 i = NumAttributeZones;

    if ((flags & (eZoneAttributes::UNKNOWN_1 | eZoneAttributes::UNKNOWN_2))) {
        AddTunnelAttributeZone(center, zero1, fWidthY, fBottomZ, fWidthX, zero2, fTopZ, flags);
        flags &= ~(eZoneAttributes::UNKNOWN_2 | eZoneAttributes::UNKNOWN_1);
    }

    // Will be computed if flags less than 0x880 (UNKNOWN_1 + UNKNOWN_2)
    if (flags) {
        aAttributeZones[i].zoneDef.x = (int16)(center.x - zero1 - fWidthX);
        aAttributeZones[i].zoneDef.y = (int16)(center.y - fWidthY - zero2);
        aAttributeZones[i].zoneDef.field_4 = (int16)(zero1 + zero1);
        aAttributeZones[i].zoneDef.widthY = (int16)(2 * fWidthY);
        aAttributeZones[i].zoneDef.bottomZ = (int16)(fBottomZ);
        aAttributeZones[i].zoneDef.widthX = (int16)(2 * fWidthX);
        aAttributeZones[i].zoneDef.field_A = (int16)(2 * zero2);
        aAttributeZones[i].zoneDef.topZ = (int16)(fTopZ);
        aAttributeZones[i].flags = static_cast<eZoneAttributes>(flags);

        NumAttributeZones += 1;
    }
}

// flags: see eZoneAttributes
// 0x72DB50
void CCullZones::AddTunnelAttributeZone(const CVector& center, float unk1, float fWidthY, float fBottomZ, float fWidthX, float unk2, float fTopZ, uint16 flags) {
    auto& attribute = aTunnelAttributeZones[NumTunnelAttributeZones];

    attribute.zoneDef.x       = (int16)(center.x - unk1 - fWidthX);
    attribute.zoneDef.y       = (int16)(center.y - fWidthY - unk2);
    attribute.zoneDef.field_4 = (int16)(2 * unk1);
    attribute.zoneDef.widthY  = (int16)(2 * fWidthY);
    attribute.zoneDef.bottomZ = (int16)(fBottomZ);
    attribute.zoneDef.widthX  = (int16)(2 * fWidthX);
    attribute.zoneDef.field_A = (int16)(2 * unk2);
    attribute.zoneDef.topZ    = (int16)(fTopZ);
    attribute.flags           = static_cast<eZoneAttributes>(flags);

    NumTunnelAttributeZones += 1;
}

// 0x72DC10
void CCullZones::AddMirrorAttributeZone(const CVector& center, float unk1, float fWidthY, float fBottomZ, float fWidthX, float unk2, float fTopZ, eZoneAttributes flags, float cm, float vX, float vY, float vZ) {
    auto& attribute = aMirrorAttributeZones[NumMirrorAttributeZones];

    attribute.zoneDef.x       = (int16)(center.x - unk1 - fWidthX);
    attribute.zoneDef.y       = (int16)(center.y - fWidthY - unk2);
    attribute.zoneDef.field_4 = (int16)(2 * unk1);
    attribute.zoneDef.widthY  = (int16)(2 * fWidthY);
    attribute.zoneDef.bottomZ = (int16)(fBottomZ);
    attribute.zoneDef.widthX  = (int16)(2 * fWidthX);
    attribute.zoneDef.field_A = (int16)(2 * unk2);
    attribute.zoneDef.topZ    = (int16)(fTopZ);
    attribute.flags           = (uint16)(static_cast<eZoneAttributes>(flags));
    attribute.cm              = cm;

    attribute.vx = (int8)(vX * 100.0f);
    attribute.vy = (int8)(vY * 100.0f);
    attribute.vz = (int8)(vZ * 100.0f);

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

    int32 out = eZoneAttributes::NONE;
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
eZoneAttributes CCullZones::FindAttributesForCoors(CVector pos) {
    if (NumAttributeZones <= 0)
        return eZoneAttributes::NONE;

    int32 out = eZoneAttributes::NONE;
    for (auto& attributeZone : aAttributeZones) {
        if (attributeZone.IsPointWithin(pos)) {
            out |= attributeZone.flags;
        }
    }

    return static_cast<eZoneAttributes>(out);
}

// 0x72DEC0
void CCullZones::Update() {
    if ((CTimer::GetFrameCounter() & 7) == 2) {
        auto cameraPosition = TheCamera.GetGameCamPosition();
        CurrentFlags_Camera = FindAttributesForCoors(cameraPosition);
    }
    else if ((CTimer::GetFrameCounter() & 7) == 6) {
        CVector posn = FindPlayerCoors();
        CurrentFlags_Player = FindAttributesForCoors(posn);
        if (!bMilitaryZonesDisabled && (CurrentFlags_Player & eZoneAttributes::MILITARY_ZONE) != 0) {
            auto player = FindPlayerPed();
            if (player->IsAlive()) {
                player->SetWantedLevelNoDrop(5);
            }
        }
    }
}
