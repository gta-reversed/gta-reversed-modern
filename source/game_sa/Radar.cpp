/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Radar.h"
#include "EntryExitManager.h"
#include <extensions/enumerate.hpp>

static inline float& cachedCos = *(float*)0xBA8308;
static inline float& cachedSin = *(float*)0xBA830C;

constexpr std::array<airstrip_info, NUM_AIRSTRIPS> airstrip_table = { // 0x8D06E0
    airstrip_info{ { +1750.0f,  -2494.0f }, 180.0f, 1000.0f }, // AIRSTRIP_LS_AIRPORT
    airstrip_info{ { -1373.0f,  +120.00f }, 315.0f, 1500.0f }, // AIRSTRIP_SF_AIRPORT
    airstrip_info{ { +1478.0f,  +1461.0f }, 90.0f,  1200.0f }, // AIRSTRIP_LV_AIRPORT
    airstrip_info{ { +175.00f,  +2502.0f }, 180.0f, 1000.0f }  // AIRSTRIP_VERDANT_MEADOWS
};

// Array of TXD slot indices for each radar section's texture
static std::array<std::array<int32, MAX_RADAR_WIDTH_TILES>, MAX_RADAR_HEIGHT_TILES>& gRadarTextures = *(std::array<std::array<int32, MAX_RADAR_WIDTH_TILES>, MAX_RADAR_HEIGHT_TILES>*)0xBA8478;

// 0x8D0720
SpriteFileName CRadar::RadarBlipFileNames[] = {
    // name,                 maskName
    { nullptr,               nullptr },
    { nullptr,               nullptr },
    { "radar_centre",        nullptr },
    { "arrow",               nullptr },
    { "radar_north",         nullptr },
    { "radar_airYard",       nullptr },
    { "radar_ammugun",       nullptr },
    { "radar_barbers",       nullptr },
    { "radar_BIGSMOKE",      nullptr },
    { "radar_boatyard",      nullptr },
    { "radar_burgerShot",    nullptr },
    { "radar_bulldozer",     nullptr },
    { "radar_CATALINAPINK",  nullptr },
    { "radar_CESARVIAPANDO", nullptr },
    { "radar_chicken",       nullptr },
    { "radar_CJ",            nullptr },
    { "radar_CRASH1",        nullptr },
    { "radar_diner",         nullptr },
    { "radar_emmetGun",      nullptr },
    { "radar_enemyAttack",   nullptr },
    { "radar_fire",          nullptr },
    { "radar_girlfriend",    nullptr },
    { "radar_hostpitaL",     nullptr },
    { "radar_LocoSyndicate", nullptr },
    { "radar_MADDOG",        nullptr },
    { "radar_mafiaCasino",   nullptr },
    { "radar_MCSTRAP",       nullptr },
    { "radar_modGarage",     nullptr },
    { "radar_OGLOC",         nullptr },
    { "radar_pizza",         nullptr },
    { "radar_police",        nullptr },
    { "radar_propertyG",     nullptr },
    { "radar_propertyR",     nullptr },
    { "radar_race",          nullptr },
    { "radar_RYDER",         nullptr },
    { "radar_saveGame",      nullptr },
    { "radar_school",        nullptr },
    { "radar_qmark",         nullptr },
    { "radar_SWEET",         nullptr },
    { "radar_tattoo",        nullptr },
    { "radar_THETRUTH",      nullptr },
    { "radar_waypoint",      nullptr },
    { "radar_TorenoRanch",   nullptr },
    { "radar_triads",        nullptr },
    { "radar_triadsCasino",  nullptr },
    { "radar_tshirt",        nullptr },
    { "radar_WOOZIE",        nullptr },
    { "radar_ZERO",          nullptr },
    { "radar_dateDisco",     nullptr },
    { "radar_dateDrink",     nullptr },
    { "radar_dateFood",      nullptr },
    { "radar_truck",         nullptr },
    { "radar_cash",          nullptr },
    { "radar_flag",          nullptr },
    { "radar_gym",           nullptr },
    { "radar_impound",       nullptr },
    { "radar_light",         nullptr },
    { "radar_runway",        nullptr },
    { "radar_gangB",         nullptr },
    { "radar_gangP",         nullptr },
    { "radar_gangY",         nullptr },
    { "radar_gangN",         nullptr },
    { "radar_gangG",         nullptr },
    { "radar_spray",         nullptr }
};

constexpr float RADAR_MIN_RANGE = 180.0f;
constexpr float RADAR_MAX_RANGE = 350.0f;
constexpr float RADAR_MIN_SPEED = 0.3f;
constexpr float RADAR_MAX_SPEED = 0.9f;

void CRadar::InjectHooks() {
    RH_ScopedClass(CRadar);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Initialise, 0x587FB0);
    RH_ScopedInstall(LoadTextures, 0x5827D0);
    // RH_ScopedInstall(DrawLegend, 0x5828A0);
    RH_ScopedInstall(LimitRadarPoint, 0x5832F0);
    RH_ScopedInstall(Shutdown, 0x585940);
    RH_ScopedInstall(SetMapCentreToPlayerCoords, 0x585B20);
    RH_ScopedInstall(InitFrontEndMap, 0x585960);
    RH_ScopedInstall(CalculateBlipAlpha, 0x583420);
    // RH_ScopedInstall(TransformRadarPointToScreenSpace, 0x583480, true);
    RH_ScopedInstall(TransformRealWorldPointToRadarSpace, 0x583530);
    RH_ScopedInstall(CalculateCachedSinCos, 0x583670);
    RH_ScopedInstall(SetBlipSprite, 0x583D70);
    RH_ScopedInstall(SetBlipAlwaysDisplayInZoom, 0x583DB0);
    RH_ScopedInstall(DrawYouAreHereSprite, 0x584960);
    RH_ScopedInstall(ChangeBlipColour, 0x583AB0);
    RH_ScopedOverloadedInstall(ClearActualBlip, "OG", 0x587C10, void(*)(int32));
    RH_ScopedInstall(ClearBlip, 0x587CE0);
    RH_ScopedInstall(ClearBlipForEntity, 0x587C60);
    RH_ScopedInstall(RequestMapSection, 0x584B50);
    RH_ScopedInstall(RemoveMapSection, 0x584BB0);
    RH_ScopedInstall(RemoveRadarSections, 0x584BF0);
    RH_ScopedInstall(DrawRadarSprite, 0x585FF0);
    RH_ScopedInstall(DrawMap, 0x586B00);
    RH_ScopedInstall(DrawRadarMap, 0x586880);
    RH_ScopedOverloadedInstall(StreamRadarSections, "", 0x5858D0, void(*)(const CVector&));
    RH_ScopedInstall(SetupRadarRect, 0x584A80);
    RH_ScopedInstall(GetActualBlipArrayIndex, 0x582870);
    RH_ScopedInstall(LimitToMap, 0x583350);
    RH_ScopedInstall(DrawRotatingRadarSprite, 0x584850);
    RH_ScopedInstall(SetBlipFriendly, 0x583EB0);
    RH_ScopedInstall(ChangeBlipDisplay, 0x583D20);
    RH_ScopedInstall(SetBlipEntryExit, 0x583F00);
    RH_ScopedInstall(SetShortRangeCoordBlip, 0x583920);
    RH_ScopedInstall(ChangeBlipScale, 0x583CC0);
    RH_ScopedInstall(GetRadarTraceColour, 0x584770);
    RH_ScopedInstall(ShowRadarMarker, 0x584480);
    RH_ScopedInstall(DrawRadarMask, 0x585700);
    RH_ScopedInstall(Load, 0x5D53C0);
    RH_ScopedGlobalInstall(Save, 0x5D5860, { .reversed = false });
    RH_ScopedInstall(SetBlipFade, 0x583E00); // unused
    RH_ScopedInstall(SetCoordBlipAppearance, 0x583E50);
    RH_ScopedInstall(SetCoordBlip, 0x583820);
    RH_ScopedInstall(SetEntityBlip, 0x5839A0);
    RH_ScopedInstall(DisplayThisBlip, 0x583B40);
    RH_ScopedInstall(ChangeBlipBrightness, 0x583C70);
    RH_ScopedInstall(ShowRadarTrace, 0x583F40);
    RH_ScopedInstall(ShowRadarTraceWithHeight, 0x584070);
    RH_ScopedInstall(DrawCoordBlip, 0x586D60);

    // RH_ScopedInstall(SetupAirstripBlips, 0x587D20);
    // RH_ScopedInstall(DrawBlips, 0x588050);
    // RH_ScopedInstall(ClipRadarPoly, 0x585040);
    // RH_ScopedInstall(DrawAreaOnRadar, 0x5853D0);
    // RH_ScopedInstall(StreamRadarSections, 0x584C50);
    // RH_ScopedInstall(AddBlipToLegendList, 0x5859F0);
    // RH_ScopedInstall(Draw3dMarkers, 0x585BF0);
    // RH_ScopedInstall(DrawRadarSection, 0x586110);
    // RH_ScopedInstall(DrawRadarSectionMap, 0x586520);
    // RH_ScopedInstall(DrawRadarGangOverlay, 0x586650);
    // RH_ScopedInstall(DrawEntityBlip, 0x587000);
    // RH_ScopedGlobalInstall(LineRadarBoxCollision, 0x584E00);

    // unused
    RH_ScopedInstall(GetNewUniqueBlipIndex, 0x582820);
    RH_ScopedInstall(TransformRadarPointToRealWorldSpace, 0x5835A0);
    RH_ScopedGlobalInstall(IsPointInsideRadar, 0x584D40);
    RH_ScopedGlobalInstall(GetTextureCorners, 0x584D90);
    RH_ScopedGlobalInstall(ClipRadarTileCoords, 0x584B00);    
}

// 0x587FB0
void CRadar::Initialise() {
    airstrip_blip = 0;
    airstrip_location = AIRSTRIP_LS_AIRPORT;

    for (auto& trace : ms_RadarTrace) {
        ClearActualBlip(trace);
    }

    m_radarRange = 350.0f;

    for (auto y = 0u; y < MAX_RADAR_HEIGHT_TILES; y++) {
        for (auto x = 0u; x < MAX_RADAR_WIDTH_TILES; x++) {
            gRadarTextures[y][x] = CTxdStore::FindTxdSlot(std::format("radar{:02d}", y * MAX_RADAR_WIDTH_TILES + x).c_str());
        }
    }
}

// 0x585940
void CRadar::Shutdown() {
    rng::for_each(RadarBlipSprites, &CSprite2d::Delete);
    RemoveRadarSections();
}

// 0x5827D0
void CRadar::LoadTextures() {
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(CTxdStore::FindTxdSlot("hud"));

    for (auto i = 0; i < MAX_RADAR_SPRITES; i++) {
        const auto [texture, mask] = RadarBlipFileNames[i];
        RadarBlipSprites[i].SetTexture(texture); // mask unused
    }

    CTxdStore::PopCurrentTxd();
}

// 0x582820 - Seemingly unused but actually just inlined
int32 CRadar::GetNewUniqueBlipIndex(int32 index) {
    auto& trace = ms_RadarTrace[index];
    if (trace.m_nCounter >= std::numeric_limits<uint16>::max() - 1)
        trace.m_nCounter = 1; // Wrap back to 1
    else
        trace.m_nCounter++; // Increment
    return index | (trace.m_nCounter << 16);
}

// 0x582870
int32 CRadar::GetActualBlipArrayIndex(int32 blipIndex) {
    if (blipIndex == -1)
        return -1;

    const auto  traceIndex = static_cast<uint16>(blipIndex);
    const auto& trace      = ms_RadarTrace[traceIndex];
    const auto  counter    = static_cast<uint16>(blipIndex >> 16);
    if (counter != trace.m_nCounter || !trace.m_bTrackingBlip)
        return -1;

    return traceIndex;
}

// 0x5828A0
void CRadar::DrawLegend(int32 x, int32 y, int32 blipType) {
    if (blipType == RADAR_SPRITE_NONE) { // None => Player position
        blipType = RADAR_SPRITE_MAP_HERE;
    }

    CFont::PrintString(
        (float)x + SCREEN_STRETCH_X(20.0f),
        (float)y + SCREEN_STRETCH_Y(3.0f),
        GetBlipName(static_cast<eRadarSprite>(blipType))
    );

    if (blipType > -1) { // The blip is a sprite, so just draw it.
        RadarBlipSprites[blipType].Draw(
            {
                (float)x,                           (float)y,
                (float)x + SCREEN_STRETCH_X(16.0f), (float)y + SCREEN_STRETCH_Y(16.0f)
            },
            { 255, 255, 255, 255 }
        );
        return;
    }

    if (CTimer::GetTimeInMSPauseMode() - legendTraceTimer > 600) {
        legendTraceTimer = CTimer::GetTimeInMSPauseMode();

        switch (legendTraceHeight) {
        case RADAR_TRACE_LOW:
            legendTraceHeight = RADAR_TRACE_HIGH;
            break;
        case RADAR_TRACE_HIGH:
            legendTraceHeight = RADAR_TRACE_NORMAL;
            break;
        case RADAR_TRACE_NORMAL:
            legendTraceHeight = RADAR_TRACE_LOW;
            break;
        }
    }

    const auto posX = std::round(SCREEN_STRETCH_X(8.0f) + (float)x);
    const auto posY = std::round(SCREEN_STRETCH_Y(8.0f) + (float)y);

    const auto x4px = SCREEN_STRETCH_X(4.0f);
    const auto x5px = SCREEN_STRETCH_X(5.0f), y5px = SCREEN_STRETCH_Y(5.0f);
    const auto x7px = SCREEN_STRETCH_X(7.0f), y7px = SCREEN_STRETCH_Y(7.0f);

    const auto& arrowColor   = ArrowBlipColour[-blipType];
    const auto  outlineColor = CRGBA{0, 0, 0, 255};

    switch (legendTraceHeight) {
    case RADAR_TRACE_LOW: {
        CSprite2d::Draw2DPolygon(
            posX - x7px, posY + y7px,
            posX + x7px, posY + y7px,
            posX,        posY - x7px,
            posX,        posY - x7px,
            outlineColor
        );

        CSprite2d::Draw2DPolygon(
            posX + x5px, posY + y5px,
            posX - x5px, posY + y5px,
            posX,        posY - x5px,
            posX,        posY - x5px,
            arrowColor
        );
        break;
    }
    case RADAR_TRACE_HIGH: {
        CSprite2d::Draw2DPolygon(
            posX + x7px, posY - y7px,
            posX - x7px, posY - y7px,
            posX,        posY + y7px,
            posX,        posY + y7px,
            outlineColor
        );

        CSprite2d::Draw2DPolygon(
            posX + x5px, posY - y5px,
            posX - x5px, posY - y5px,
            posX,        posY + y5px,
            posX,        posY + y5px,
            arrowColor
        );
        break;
    }
    case RADAR_TRACE_NORMAL: {
        CSprite2d::DrawRect(
            {
                posX - x5px,
                posY - x5px,
                posX + x5px,
                posY + x5px
            },
            outlineColor
        );

        CSprite2d::DrawRect(
            {
                posX - x4px,
                posY - x4px,
                posX + x4px,
                posY + x4px
            },
            arrowColor
        );
        break;
    }
    }
}

// 0x5832F0
float CRadar::LimitRadarPoint(CVector2D& point) {
    const auto mag = point.Magnitude();

    if (FrontEndMenuManager.m_bDrawingMap)
        return mag;

    if (mag > 1.0f) {
        // not in unit circle
        point.Normalise();
    }

    return mag;
}

// 0x583350
void CRadar::LimitToMap(float& x, float& y) {
    const auto zoom = FrontEndMenuManager.m_bMapLoaded ? FrontEndMenuManager.m_fMapZoom : 140.0f;

    {
        const auto min = SCREEN_STRETCH_X(FrontEndMenuManager.m_vMapOrigin.x - zoom);
        const auto max = SCREEN_STRETCH_X(FrontEndMenuManager.m_vMapOrigin.x + zoom);
        x = std::clamp(x, min, max);
    }

    {
        const auto min = SCREEN_STRETCH_Y(FrontEndMenuManager.m_vMapOrigin.y - zoom);
        const auto max = SCREEN_STRETCH_Y(FrontEndMenuManager.m_vMapOrigin.y + zoom);
        y = std::clamp(y, min, max);
    }
}

// 0x583420
uint8 CRadar::CalculateBlipAlpha(float distance) {
    if (FrontEndMenuManager.m_bDrawingMap) {
        return 255;
    }

    const auto alpha = 255 - (uint32)(distance / 6.0f * 255.0f);
    return (uint8)std::max((float)alpha, 70.0f);
}

// 0x583480
// NOTE: Unhooked by default for now. Causes `DrawRadarSection` to crash.
void CRadar::TransformRadarPointToScreenSpace(CVector2D& out, const CVector2D& in) {
    if (FrontEndMenuManager.m_bDrawingMap) {
        out = {
            FrontEndMenuManager.m_vMapOrigin.x + FrontEndMenuManager.m_fMapZoom * in.x,
            FrontEndMenuManager.m_vMapOrigin.y - FrontEndMenuManager.m_fMapZoom * in.y
        };
    } else {
        out = {
            SCREEN_STRETCH_X(94.0f) / 2.0f + SCREEN_STRETCH_X(40.0f) + SCREEN_STRETCH_X(94.0f * in.x) / 2.0f,
            SCREEN_STRETCH_FROM_BOTTOM(104.0f) + SCREEN_STRETCH_Y(76.0f) / 2.0f - SCREEN_STRETCH_Y(76.0f * in.y) / 2.0f
        };
    }
}

// 0x583530
void CRadar::TransformRealWorldPointToRadarSpace(CVector2D& out, const CVector2D& in) {
    const auto xOffset = (in.x - vec2DRadarOrigin.x) / m_radarRange;
    const auto yOffset = (in.y - vec2DRadarOrigin.y) / m_radarRange;

    out = {
        cachedSin * yOffset + cachedCos * xOffset,
        cachedCos * yOffset - cachedSin * xOffset
    };
}

// unused
// 0x5835A0
void CRadar::TransformRadarPointToRealWorldSpace(CVector2D& out, const CVector2D& in) {
    out = CVector2D{
        cachedCos * in.x - cachedSin * in.y,
        cachedCos * in.y + cachedSin * in.x
    } * m_radarRange + vec2DRadarOrigin;
}

// unused, see CRadar::DrawRadarSection
// 0x583600
void CRadar::TransformRealWorldToTexCoordSpace(CVector2D& out, const CVector2D& in, int32 x, int32 y) {
    out = CVector2D{
        +(in.x - (float(500 * x) - 3000.0f)),
        -(in.y - ((500 * float(12 - y)) - 3000.0f))
    } / 500.0f;
}

// 0x583670
void CRadar::CalculateCachedSinCos() {
    if (FrontEndMenuManager.m_bDrawingMap) {
        cachedSin = std::sin(0.0f);
        cachedCos = std::cos(0.0f);

        return;
    }

    const auto SaveAngle = [](float angle) {
        m_fRadarOrientation = angle;
        cachedSin = std::sin(angle);
        cachedCos = std::cos(angle);
    };

    if (TheCamera.GetLookDirection() == LOOKING_DIRECTION_FORWARD) {
        SaveAngle(TheCamera.GetHeading());

        return;
    }

    const auto& activeCam = CCamera::GetActiveCamera();
    const auto targetEntity = activeCam.m_pCamTargetEntity;

    const auto directionToTarget = [&] {
        if (activeCam.m_nMode == MODE_1STPERSON || TheCamera.GetLookDirection() == LOOKING_DIRECTION_UNKNOWN_1) {
            return targetEntity->GetMatrix().GetForward().Normalized();
        } else {
            return targetEntity->GetPosition() - activeCam.m_vecSourceBeforeLookBehind;
        }
    }();

    SaveAngle(directionToTarget.Heading());
}

// param *scriptName* from Android
// 0x583820
int32 CRadar::SetCoordBlip(eBlipType type, CVector posn, eBlipColour color, eBlipDisplay blipDisplay, const char* scriptName) {
    auto index = FindTraceNotTrackingBlipIndex();
    if (index == -1)
        return -1;

    auto& t = ms_RadarTrace[index];

    t.m_vPosition        = posn;
    t.m_nBlipDisplayFlag = blipDisplay;
    t.m_nBlipType        = type;
    t.m_nColour          = color;
    t.m_fSphereRadius    = 1.f;
    t.m_nEntityHandle    = 0;
    t.m_nBlipSize        = 1;
    t.m_nBlipSprite      = eRadarSprite::RADAR_SPRITE_NONE;
    t.m_bBright          = true;
    t.m_bTrackingBlip    = true;
    t.m_pEntryExit       = nullptr;

    return GetNewUniqueBlipIndex(index);
}

// param *scriptName* from Android
// 0x583920
int32 CRadar::SetShortRangeCoordBlip(eBlipType type, CVector posn, eBlipColour color, eBlipDisplay blipDisplay, const char* scriptName) {
    int32 index = SetCoordBlip(type, posn, color, blipDisplay, scriptName);
    if (index == -1)
        return -1;

    auto actualIndex = GetActualBlipArrayIndex(index);
    ms_RadarTrace[actualIndex].m_bShortRange = true;
    return index;
}

// 0x5839A0
int32 CRadar::SetEntityBlip(eBlipType type, int32 entityHandle, uint32 arg2, eBlipDisplay blipDisplay) {
    auto index = FindTraceNotTrackingBlipIndex();
    if (index == -1)
        return -1;

    auto& t = ms_RadarTrace[index];

    t.m_nBlipDisplayFlag = blipDisplay;
    t.m_nColour          = (type == BLIP_CHAR || type == BLIP_CAR) ? BLIP_COLOUR_THREAT : BLIP_COLOUR_GREEN;
    t.m_nEntityHandle    = entityHandle;
    t.m_fSphereRadius    = 1.f;
    t.m_nBlipSize        = 1;
    t.m_nBlipDisplayFlag = blipDisplay;
    t.m_nBlipType        = type;
    t.m_nBlipSprite      = eRadarSprite::RADAR_SPRITE_NONE;
    t.m_bBright          = true;
    t.m_bTrackingBlip    = true;
    t.m_pEntryExit       = nullptr;

    return GetNewUniqueBlipIndex(index);
}

// 0x583AB0
void CRadar::ChangeBlipColour(int32 blipIndex, uint32 color) {
    const auto index = GetActualBlipArrayIndex(blipIndex);
    if (index != -1) {
        ms_RadarTrace[index].m_nColour = static_cast<eBlipColour>(color);
    }
}

// 0x583AF0
bool CRadar::HasThisBlipBeenRevealed(int32 blipIndex) {
    const auto& blipPos = ms_RadarTrace[blipIndex].m_vPosition;

    if (!FrontEndMenuManager.m_bDrawingMap
        || !ms_RadarTrace[blipIndex].m_bShortRange
        || CTheZones::ZonesRevealed > 80
        || CTheZones::GetCurrentZoneLockedOrUnlocked(blipPos.x, blipPos.y)
    ) {
        return true;
    }

    return false;
}

// 0x583B40
bool CRadar::DisplayThisBlip(eRadarSprite spriteId, char priority) {
    if (CGame::CanSeeOutSideFromCurrArea() && FindPlayerPed()->m_nAreaCode == AREA_CODE_NORMAL_WORLD) {
        switch (spriteId) {
        case RADAR_SPRITE_NONE:
        case RADAR_SPRITE_WHITE:
        case RADAR_SPRITE_CENTRE:
        case RADAR_SPRITE_MAP_HERE:
        case RADAR_SPRITE_NORTH:
            return true;

        case RADAR_SPRITE_AIRYARD:
        case RADAR_SPRITE_AMMUGUN:
        case RADAR_SPRITE_BARBERS:
        case RADAR_SPRITE_BOATYARD:
        case RADAR_SPRITE_BURGERSHOT:
        case RADAR_SPRITE_BULLDOZER:
        case RADAR_SPRITE_CHICKEN:
        case RADAR_SPRITE_DINER:
        case RADAR_SPRITE_HOSTPITAL:
        case RADAR_SPRITE_MODGARAGE:
        case RADAR_SPRITE_PIZZA:
        case RADAR_SPRITE_POLICE:
        case RADAR_SPRITE_RACE:
        case RADAR_SPRITE_SAVEGAME:
        case RADAR_SPRITE_SCHOOL:
        case RADAR_SPRITE_TATTOO:
        case RADAR_SPRITE_TSHIRT:
        case RADAR_SPRITE_DATEDISCO:
        case RADAR_SPRITE_DATEDRINK:
        case RADAR_SPRITE_DATEFOOD:
        case RADAR_SPRITE_TRUCK:
        case RADAR_SPRITE_CASH:
        case RADAR_SPRITE_FLAG:
        case RADAR_SPRITE_GYM:
        case RADAR_SPRITE_IMPOUND:
        case RADAR_SPRITE_SPRAY:
            return (FrontEndMenuManager.m_ShowLocationsBlips && priority < 0) || priority == 1;

        case RADAR_SPRITE_BIGSMOKE:
        case RADAR_SPRITE_CATALINAPINK:
        case RADAR_SPRITE_CESARVIAPANDO:
        case RADAR_SPRITE_CJ:
        case RADAR_SPRITE_CRASH1:
        case RADAR_SPRITE_EMMETGUN:
        case RADAR_SPRITE_GIRLFRIEND:
        case RADAR_SPRITE_LOGOSYNDICATE:
        case RADAR_SPRITE_MADDOG:
        case RADAR_SPRITE_MAFIACASINO:
        case RADAR_SPRITE_MCSTRAP:
        case RADAR_SPRITE_OGLOC:
        case RADAR_SPRITE_RYDER:
        case RADAR_SPRITE_QMARK:
        case RADAR_SPRITE_SWEET:
        case RADAR_SPRITE_THETRUTH:
        case RADAR_SPRITE_TORENORANCH:
        case RADAR_SPRITE_TRIADS:
        case RADAR_SPRITE_TRIADSCASINO:
        case RADAR_SPRITE_WOOZIE:
        case RADAR_SPRITE_ZERO:
        case RADAR_SPRITE_GANGB:
        case RADAR_SPRITE_GANGP:
        case RADAR_SPRITE_GANGY:
        case RADAR_SPRITE_GANGN:
        case RADAR_SPRITE_GANGG:
            return (FrontEndMenuManager.m_ShowContactsBlips && priority < 0) || priority == 3;

        default:
            return (FrontEndMenuManager.m_ShowOtherBlips && priority < 0) || priority == 2;
        }
    }

    switch (spriteId) {
    case RADAR_SPRITE_NONE:
    case RADAR_SPRITE_WHITE:
    case RADAR_SPRITE_CENTRE:
    case RADAR_SPRITE_MAP_HERE:
    case RADAR_SPRITE_NORTH:
    case RADAR_SPRITE_MAFIACASINO:
    case RADAR_SPRITE_SCHOOL:
    case RADAR_SPRITE_WAYPOINT:
    case RADAR_SPRITE_TRIADSCASINO:
    case RADAR_SPRITE_CASH:
        return true;

    default:
        return false;
    }
}

// unused
// 0x583C70
void CRadar::ChangeBlipBrightness(int32 blipIndex, int32 brightness) {
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_bBright = brightness == 1 ? true : false;
}

// 0x583CC0
void CRadar::ChangeBlipScale(int32 blipIndex, int32 size) {
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (FrontEndMenuManager.m_bDrawingMap)
        size = 1;

    ms_RadarTrace[index].m_nBlipSize = size;
}

// 0x583D20
void CRadar::ChangeBlipDisplay(int32 blipIndex, eBlipDisplay blipDisplay) {
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_nBlipDisplayFlag = blipDisplay;
}

// 0x583D70
void CRadar::SetBlipSprite(int32 blipIndex, eRadarSprite spriteId) {
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (ms_RadarTrace[index].m_bTrackingBlip)
        ms_RadarTrace[index].m_nBlipSprite = static_cast<eRadarSprite>(spriteId);
}

// 0x583DB0
void CRadar::SetBlipAlwaysDisplayInZoom(int32 blipIndex, bool display) {
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (ms_RadarTrace[index].m_bTrackingBlip)
        ms_RadarTrace[index].m_bBlipRemain = display;
}

// unused?
// 0x583E00
void CRadar::SetBlipFade(int32 blipIndex, bool fade) {
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_bBlipFade = fade;
}

// 0x583E50
void CRadar::SetCoordBlipAppearance(int32 blipIndex, eBlipAppearance appearance) {
    const auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1) {
        return;
    }

    auto& trace = ms_RadarTrace[index];
    if (trace.m_nBlipType != eBlipType::BLIP_CAR) {
        return;
    }

    switch (appearance) { // Seems like there's a 3rd appearance type?
    case BLIP_FLAG_FRIEND:
    case BLIP_FLAG_THREAT:
    case BLIP_FLAG_UNK:
        trace.m_nAppearance = appearance;
        break;
    }
}

// 0x583EB0
void CRadar::SetBlipFriendly(int32 blipIndex, bool friendly) {
    const auto index = GetActualBlipArrayIndex(blipIndex);
    if (index != -1) {
        ms_RadarTrace[index].m_bFriendly = friendly;
    }
}

// 0x583F00
void CRadar::SetBlipEntryExit(int32 blipIndex, CEntryExit* enex) {
    const auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    auto& trace = ms_RadarTrace[index];
    if (trace.m_bTrackingBlip) {
        trace.m_pEntryExit = enex;
    }
}

// This code piece seems fairly common.. Perhaps its inlined?
void Limit(float& x, float& y) {
    if (FrontEndMenuManager.m_bDrawingMap) {
        x = SCREEN_STRETCH_X(x);
        y = SCREEN_STRETCH_Y(y);

        CRadar::LimitToMap(x, y);
    }
}

    // 0x583F40
void CRadar::ShowRadarTrace(float x, float y, uint32 size, uint8 red, uint8 green, uint8 blue, uint8 alpha) {
    Limit(x, y);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(NULL));

    // Draw background rect - Since it's 1px bigger on each side when we draw the next rect on top of it will act as a border
    CSprite2d::DrawRect({
        x - float(size - 1),
        y - float(size - 1),
        x + float(size + 1),
        y + float(size + 1)
    }, { 0, 0, 0, alpha });

    // Now draw actual rect on top of it
    CSprite2d::DrawRect({
        x - float(size),
        y - float(size),
        x + float(size),
        y + float(size)
    }, { red, blue, green, alpha });
}

// 0x584070
void CRadar::ShowRadarTraceWithHeight(float x, float y, uint32 size, CRGBA color, eRadarTraceHeight height) {
    Limit(x, y);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(NULL));

    const auto size0 = float(size + 0), size1 = float(size + 1);
    const auto size2 = float(size + 2), size3 = float(size + 3);

    switch (height) {
    case RADAR_TRACE_HIGH:
        CSprite2d::Draw2DPolygon( // draw black border
            x,                           y + SCREEN_STRETCH_Y(size3),
            x,                           y + SCREEN_STRETCH_Y(size3),
            x + SCREEN_STRETCH_X(size3), y - SCREEN_STRETCH_Y(size2),
            x - SCREEN_STRETCH_X(size3), y - SCREEN_STRETCH_Y(size2),
            { 0, 0, 0, color.a }
        );
        CSprite2d::Draw2DPolygon( // draw triangle
            x,                           y + SCREEN_STRETCH_Y(size1),
            x,                           y + SCREEN_STRETCH_Y(size1),
            x + SCREEN_STRETCH_X(size1), y - SCREEN_STRETCH_Y(size1),
            x - SCREEN_STRETCH_X(size1), y - SCREEN_STRETCH_Y(size1),
            color
        );
        break;
    case RADAR_TRACE_NORMAL:
        CSprite2d::DrawRect( // draw black border
            CRect(
                x - SCREEN_STRETCH_X(size1), y - SCREEN_STRETCH_Y(size1),
                x + SCREEN_STRETCH_X(size1), y + SCREEN_STRETCH_Y(size1)
            ),
            { 0, 0, 0, color.a }
        );

        CSprite2d::DrawRect( // draw box
            {
                x - SCREEN_STRETCH_X(size0), y - SCREEN_STRETCH_Y(size0),
                x + SCREEN_STRETCH_X(size0), y + SCREEN_STRETCH_Y(size0)
            },
            color
        );
        break;
    case RADAR_TRACE_LOW:
        CSprite2d::Draw2DPolygon( // draw black border
            x + SCREEN_STRETCH_X(size3), y + SCREEN_STRETCH_Y(size2),
            x - SCREEN_STRETCH_X(size3), y + SCREEN_STRETCH_Y(size2),
            x,                           y - SCREEN_STRETCH_Y(size3),
            x,                           y - SCREEN_STRETCH_Y(size3),
            { 0, 0, 0, color.a }
        );

        CSprite2d::Draw2DPolygon( // draw triangle
            x + SCREEN_STRETCH_X(size1), y + SCREEN_STRETCH_Y(size1),
            x - SCREEN_STRETCH_X(size1), y + SCREEN_STRETCH_Y(size1),
            x,                           y - SCREEN_STRETCH_Y(size1),
            x,                           y - SCREEN_STRETCH_Y(size1),
            color
        );
        break;
    }
}

// show debug line at this position
// 0x584480
void CRadar::ShowRadarMarker(CVector p, uint32 color, float radius) {
    auto& mat   = TheCamera.m_mCameraMatrix;
    auto& up    = mat.GetUp();
    auto& right = mat.GetRight();

    auto r0 = radius * 0.5f;
    auto r1 = radius * 1.4f;

    CTheScripts::ScriptDebugLine3D(p + r1 * up,    p + r0 * up,    color, color);
    CTheScripts::ScriptDebugLine3D(p - r1 * up,    p - r0 * up,    color, color);
    CTheScripts::ScriptDebugLine3D(p + r1 * right, p + r0 * right, color, color);
    CTheScripts::ScriptDebugLine3D(p - r1 * right, p - r0 * right, color, color);
}

// 0x584770
uint32 CRadar::GetRadarTraceColour(eBlipColour color, bool bright, bool friendly) {
    switch (color) {
    case BLIP_COLOUR_RED:
    case BLIP_COLOUR_REDCOPY:
        return HudColour.GetIntColour((bright) ? HUD_COLOUR_RED : HUD_COLOUR_DARK_RED);
    case BLIP_COLOUR_GREEN:
        return HudColour.GetIntColour((bright) ? HUD_COLOUR_GREEN : HUD_COLOUR_DARK_GREEN);
    case BLIP_COLOUR_BLUE:
    case BLIP_COLOUR_BLUECOPY:
        return HudColour.GetIntColour((bright) ? HUD_COLOUR_LIGHT_BLUE : HUD_COLOUR_BLUE);
    case BLIP_COLOUR_WHITE:
        return HudColour.GetIntColour((bright) ? HUD_COLOUR_LIGHT_GRAY : HUD_COLOUR_DARK_GRAY);
    case BLIP_COLOUR_YELLOW:
        return HudColour.GetIntColour((bright) ? HUD_COLOUR_CREAM : HUD_COLOUR_GOLD);
    case BLIP_COLOUR_THREAT:
        return HudColour.GetIntColour((friendly) ? HUD_COLOUR_BLUE : HUD_COLOUR_RED);
    case BLIP_COLOUR_DESTINATION:
        return HudColour.GetIntColour(HUD_COLOUR_CREAM);
    default:
        return color;
    }
}

// 0x584850
void CRadar::DrawRotatingRadarSprite(CSprite2d* sprite, float x, float y, float angle, uint32 width, uint32 height, CRGBA color) {
    Limit(x, y);
    CVector2D verts[4];
    for (auto i = 0u; i < std::size(verts); i++) {
        float theta = (float)i * HALF_PI + (angle - FRAC_PI_4);

        verts[i].x = std::sin(theta) * (float)width + x;
        verts[i].y = std::cos(theta) * (float)height + y;
    }

    sprite->Draw(verts[3].x, verts[3].y, verts[2].x, verts[2].y, verts[0].x, verts[0].y, verts[1].x, verts[1].y, color);
}

// 0x584960
void CRadar::DrawYouAreHereSprite(float x, float y) {
    static uint32& mapYouAreHereTimer = *(uint32*)0xBAA358; // TODO | STATICREF
    static bool& mapYouAreHereDisplay = *(bool*)0x8D0930;

    if ((CTimer::GetTimeInMSPauseMode() - mapYouAreHereTimer) > 700) {
        mapYouAreHereTimer = CTimer::GetTimeInMSPauseMode();
        mapYouAreHereDisplay = !mapYouAreHereDisplay;
    }

    if (mapYouAreHereDisplay) {
        float angle = FindPlayerHeading(0) + PI;
        float circleAngle = angle + HALF_PI;

        CRGBA white(255, 255, 255, 255);
        float drawX = x + 17.0f * std::cos(circleAngle);
        float drawY = y - 17.0f * std::sin(circleAngle);

        DrawRotatingRadarSprite(
            &RadarBlipSprites[RADAR_SPRITE_MAP_HERE],
            drawX,
            drawY,
            angle,
            (uint32)(SCREEN_STRETCH_X(25.0f)),
            (uint32)(SCREEN_STRETCH_Y(25.0f)),
            white
        );
    }

    MapLegendList[MapLegendCounter++] = RADAR_SPRITE_MAP_HERE;
}

// 0x584A80
void CRadar::SetupRadarRect(int32 x, int32 y) {
    m_radarRect.left   = 500.0f * float(x - 6) - 500.0f;
    m_radarRect.top    = 500.0f * float(5 - y) - 500.0f;
    m_radarRect.right  = 500.0f * float(x - 4);
    m_radarRect.bottom = 500.0f * float(7 - y);
}

// unused
// 0x584B00
// Returns true if either coords had to be clipped
bool ClipRadarTileCoords(int32& x, int32& y) {
    // Not quite the way they've done it, but nicer.

    const auto ox = x, oy = y;

    x = std::clamp(x, 0, (int32)MAX_RADAR_WIDTH_TILES - 1);
    y = std::clamp(y, 0, (int32)MAX_RADAR_HEIGHT_TILES - 1);

    return ox != x || oy != y;
}

// 0x584B50
void CRadar::RequestMapSection(int32 x, int32 y) {
    if (x < 0 || x > MAX_RADAR_WIDTH_TILES - 1 || y < 0 || y > MAX_RADAR_HEIGHT_TILES - 1)
        return;

    int32 tex = gRadarTextures[y][x];
    if (tex == -1)
        return;

    CStreaming::RequestTxdModel(tex, (STREAMING_GAME_REQUIRED | STREAMING_KEEP_IN_MEMORY));
}

// 0x584BB0
void CRadar::RemoveMapSection(int32 x, int32 y) {
    if (x < 0 || x > MAX_RADAR_WIDTH_TILES || y < 0 || y > MAX_RADAR_HEIGHT_TILES)
        return;

    int32 tex = gRadarTextures[y][x];
    if (tex == -1)
        return;

    CStreaming::RemoveTxdModel(tex);
}

// 0x584BF0
void CRadar::RemoveRadarSections() {
    for (auto y = 0u; y < MAX_RADAR_HEIGHT_TILES; y++) {
        for (auto x = 0u; x < MAX_RADAR_WIDTH_TILES; x++) {
            CStreaming::RemoveTxdModel(gRadarTextures[y][x]);
        }
    }
}

// 0x584D40
bool IsPointInsideRadar(const CVector2D& point) {
    return std::abs(point.x) < 1.0f
        && std::abs(point.y) < 1.0f;
}

// 0x584D90
void GetTextureCorners(int32 x, int32 y, CVector2D* corners) {
    // Magic numbers probably come from `MAX_RADAR_WIDTH_TILES` and `MAX_RADAR_HEIGHT_TILES`

    corners[0] = {500.0f * float(x - 6), 500.0f * float(5 - y)};
    corners[1] = {500.0f * float(x - 5), 500.0f * float(5 - y)};
    corners[2] = {500.0f * float(x - 5), 500.0f * float(6 - y)};
    corners[3] = {500.0f * float(x - 6), 500.0f * float(6 - y)};
}

// Returns number of intersections
// 0x584E00
int32 LineRadarBoxCollision(CVector2D& result, const CVector2D& lineStart, const CVector2D& lineEnd) {
    return plugin::CallAndReturn<int32, 0x584E00, CVector2D&, const CVector2D&, const CVector2D&>(result, lineStart, lineEnd);
}

// 0x585040
int32 CRadar::ClipRadarPoly(CVector2D* out, const CVector2D* in) {
    return plugin::CallAndReturn<int32, 0x585040, CVector2D*, const CVector2D*>(out, in);
}

// 0x5853D0
void CRadar::DrawAreaOnRadar(const CRect& rect, const CRGBA&  color, bool inMenu) {
    return plugin::Call<0x5853D0, const CRect&, const CRGBA&, bool>(rect, color, inMenu);

    if (!m_radarRect.IsRectInside(rect)) {
        return;
    }

    //// Corner positions - Not transformed
    //const CVector2D rectCorners[]{
    //    {rect.right, rect.top},     // Top right
    //    {rect.right, rect.bottom},  // Bottom right

    //    {rect.left,  rect.bottom},  // Bottom left
    //    {rect.left,  rect.top}      // Top left
    //};

    //// Corner positions - Transformed, not yet clipped
    //CVector2D polyUnclippedVertices[4];
    //rng::transform(rectCorners, polyUnclippedVertices, [](auto&& v) {
    //    CVector2D transformed;
    //    TransformRealWorldPointToRadarSpace(transformed, v);
    //    return transformed;
    //});

    //// Now clip all corners to be within the radar area
    //CVector2D polyVertices[4];
    //const auto nVerticesInsideRadar = ClipRadarPoly(polyVertices, polyUnclippedVertices);

    //RwTexCoords texCoords[4];
    //if (nVerticesInsideRadar) {
    //    for (auto i = 0; i < nVerticesInsideRadar; i++) {
    //}
}

// 0x585700
void CRadar::DrawRadarMask() {
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,     RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,         RWRSTATE(rwSHADEMODEFLAT));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, RWRSTATE(rwALPHATESTFUNCTIONALWAYS));

    CVector2D out[8];
    CVector2D in;
        CVector2D corners[4] = {
        { 1.0f,  -1.0f },
        { 1.0f,  1.0f  },
        { -1.0f, 1.0f  },
        { -1.0,  -1.0f }
    };

    // Draw the shape we want to mask out from the radar in four segments
    for (auto& corner : corners) {
        // First point is always the corner itself
        in.x = corner.x;
        in.y = corner.y;
        TransformRadarPointToScreenSpace(out[0], in);

        // Then generate a quarter of the circle
        for (auto j = 0; j < 7; j++) {
            in.x = corner.x * std::cos(float(j) * (FRAC_PI_2 / 6.0f));
            in.y = corner.y * std::sin(float(j) * (FRAC_PI_2 / 6.0f));
            TransformRadarPointToScreenSpace(out[j + 1], in);
        };

        CSprite2d::SetMaskVertices(std::size(out), (float*)out, CSprite2d::GetNearScreenZ());
        RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::GetVertices(), std::size(out));
    }

    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, RWRSTATE(rwALPHATESTFUNCTIONGREATER));
}

// 0x5858D0
void CRadar::StreamRadarSections(const CVector& worldPosn) {
    if (!CStreaming::ms_disableStreaming) {
        StreamRadarSections(
            (int32)std::floor((worldPosn.x + 3000.0f) / 500.0f),
            (int32)std::ceil(11.0f - (worldPosn.y + 3000.0f) / 500.0f)
        );
    }
}

// 0x584C50
void CRadar::StreamRadarSections(int32 x, int32 y) {
    plugin::Call<0x584C50, int32, int32>(x, y);
}

// 0x585960
void CRadar::InitFrontEndMap() {
    CalculateCachedSinCos();
    std::ranges::fill(MapLegendList, 0);

    vec2DRadarOrigin.Set(0.0f, 0.0f);
    m_radarRange = 2990.0f; // todo: world const - 1.0f
    MapLegendCounter = 0;

    std::ranges::fill(ArrowBlipColour, CRGBA(0, 0, 0, 0));
}

// 0x5859F0
void CRadar::AddBlipToLegendList(uint8 arg0, int32 blipIndex) {
    plugin::Call<0x5859F0, uint8, int32>(arg0, blipIndex);
}

// 0x585B20
void CRadar::SetMapCentreToPlayerCoords() {
    if (FindPlayerPed() == nullptr)
        return;

    FrontEndMenuManager.m_bDrawingMap = true;

    InitFrontEndMap();

    CVector2D posReal = FindPlayerCentreOfWorld_NoInteriorShift(0);

    if (CTheScripts::HideAllFrontEndMapBlips || CTheScripts::bPlayerIsOffTheMap)
        posReal.Set(0.0f, 0.0f);

    CVector2D posRadar;
    TransformRealWorldPointToRadarSpace(posRadar, posReal);
    LimitRadarPoint(posRadar);

    FrontEndMenuManager.m_vMousePos = posReal;
    FrontEndMenuManager.m_vMapOrigin.x = DEFAULT_SCREEN_WIDTH  / 2.0f - FrontEndMenuManager.m_fMapZoom * posRadar.x;
    FrontEndMenuManager.m_vMapOrigin.y = DEFAULT_SCREEN_HEIGHT / 2.0f + FrontEndMenuManager.m_fMapZoom * posRadar.y;
    FrontEndMenuManager.m_bDrawingMap = false;
}

// 0x585BF0
void CRadar::Draw3dMarkers() {
    plugin::Call<0x585BF0>();
}

// unused
// 0x585FE0
void CRadar::SetRadarMarkerState(int32 counter, bool flag) {
    // NOP

    /* III/VC leftover
    const auto GetEntity = [=]() -> CEntity* {
        const auto handle = ms_RadarTrace[counter].m_nEntityHandle;
        switch (ms_RadarTrace[counter].m_nBlipType) {
        case BLIP_CAR:
            return GetVehiclePool()->GetAt(handle);
        case BLIP_CHAR:
            return GetPedPool()->GetAt(handle);
        case BLIP_OBJECT:
            return GetObjectPool()->GetAt(handle);
        default:
            return nullptr;
        }
    };

    if (auto* entity = GetEntity()) {
        entity->bHasBlip = flag;
    }
    */
}

// 0x585FF0
void CRadar::DrawRadarSprite(eRadarSprite spriteId, float x, float y, uint8 alpha) {
    Limit(x, y);

    const auto width  = std::floor(SCREEN_STRETCH_X(8.0f));
    const auto height = std::floor(SCREEN_STRETCH_Y(8.0f));

    if (DisplayThisBlip(spriteId, -99)) {
        RadarBlipSprites[(size_t)spriteId].Draw(
            { x - width, y - height, x + width, y + height },
            { 255, 255, 255, alpha }
        );
        AddBlipToLegendList(0, spriteId);
    }
}

// 0x586110
void CRadar::DrawRadarSection(int32 x, int32 y) {
    plugin::Call<0x586110, int32, int32>(x, y);
}

// 0x586520
void CRadar::DrawRadarSectionMap(int32 x, int32 y, CRect rect) {
    plugin::Call<0x586520, int32, int32, CRect>(x, y, rect);
}

// 0x586650
void CRadar::DrawRadarGangOverlay(bool inMenu) {
    plugin::Call<0x586650, bool>(inMenu);
}

// 0x586880
void CRadar::DrawRadarMap() {
    DrawRadarMask();

    auto x = (int32)std::floor((vec2DRadarOrigin.x + 3000.0f) / 500.0f);  // todo: inlined
    auto y = (int32)std::ceil(11.0f - (vec2DRadarOrigin.y + 3000.0f) / 500.0f);

    SetupRadarRect(x, y);
    StreamRadarSections(x, y);

    RwRenderStateSet(rwRENDERSTATEFOGENABLE,          RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,           RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,          RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,      RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,          RWRSTATE(D3DSHADE_FLAT));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,        RWRSTATE(rwRENDERSTATETEXTURERASTER));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,  RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,     RWRSTATE(D3DTADDRESS_CLAMP));
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE, RWRSTATE(FALSE));

    DrawRadarSection(x - 1,     y - 1);
    DrawRadarSection(x,         y - 1);
    DrawRadarSection(x + 1,     y - 1);
    DrawRadarSection(x - 1,     y    );
    DrawRadarSection(x,         y    );
    DrawRadarSection(x + 1,     y    );
    DrawRadarSection(x - 1,     y + 1);
    DrawRadarSection(x,         y + 1);
    DrawRadarSection(x + 1,     y + 1);

    DrawRadarGangOverlay(false);

    const auto vehicle = FindPlayerVehicle();

    // Draw green rectangle when in plane
    if (vehicle && vehicle->IsSubPlane() && vehicle->m_nModelIndex != MODEL_VORTEX) {
        CVector playerPos = FindPlayerCentreOfWorld_NoInteriorShift(0);

        const auto cSin = cachedSin;
        const auto cCos = cachedCos;
        cachedSin = std::sin(PI);
        cachedCos = std::cos(PI);

        // Pitch and roll combined
        const float angle = std::atan2(-vehicle->m_matrix->GetForward().z, vehicle->m_matrix->GetUp().z);

        DrawAreaOnRadar(
            {
                playerPos.x - 1000.0f,
                playerPos.y - (2.0f * RadiansToDegrees(angle)),
                playerPos.x + 1000.0f,
                playerPos.y + 2000.0f
            },
            { 20, 175, 20, 200 },
            false
        );

        cachedSin = cSin;
        cachedCos = cCos;
    }

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(FALSE));
}

// 0x586B00
// TODO: Fix me - Zoom incorrect
void CRadar::DrawMap() {
    const auto player = FindPlayerPed();
    const auto mapShouldDrawn = !CGame::currArea && player->m_nAreaCode == 0 && FrontEndMenuManager.m_nRadarMode != 1;

    CalculateCachedSinCos();

    const auto vehicle = FindPlayerVehicle();
    const auto playerInfo = player->GetPlayerInfoForThisPlayerPed();

    if (!vehicle || playerInfo->IsPlayerInRemoteMode()) {
        if (CTheScripts::RadarZoomValue)
            m_radarRange = RADAR_MIN_RANGE - (float)CTheScripts::RadarZoomValue;
        else
            m_radarRange = RADAR_MIN_RANGE;
    } else {
        if (vehicle && vehicle->IsSubPlane() && ModelIndices::IsVortex(vehicle->m_nModelIndex)) {
            const auto speedZ = vehicle->GetPosition().z * 1.0f / 200.0f;

            if (speedZ < RADAR_MIN_SPEED)
                m_radarRange = RADAR_MAX_RANGE - 10.0f;
            else if (speedZ < RADAR_MAX_SPEED)
                m_radarRange = (speedZ - RADAR_MIN_SPEED) * (1.0f / 60.0f) + (RADAR_MAX_RANGE - 10.0f);
            else
                m_radarRange = RADAR_MAX_RANGE;
        } else {
            const auto speed = FindPlayerSpeed().Magnitude();

            if (speed < RADAR_MIN_SPEED)
                m_radarRange = RADAR_MIN_RANGE;
            else if (speed >= RADAR_MAX_SPEED)
                m_radarRange = RADAR_MAX_RANGE;
            else
                m_radarRange = (speed - RADAR_MIN_SPEED) * (850.0f / (RADAR_MIN_SPEED * 10.0f)) + RADAR_MIN_RANGE;
        }
    }

    vec2DRadarOrigin = []() -> CVector2D {
        if (!CGameLogic::IsCoopGameGoingOn()) [[likely]] {
            return FindPlayerCentreOfWorld_NoInteriorShift(0);
        } else if (CGameLogic::n2PlayerPedInFocus == eFocusedPlayer::PLAYER2) {
            return FindPlayerCentreOfWorld_NoInteriorShift(1);
        } else {
            return (FindPlayerCentreOfWorld_NoInteriorShift(0) + FindPlayerCentreOfWorld_NoInteriorShift(1)) / 2.0f; // Halfway between the two player's positions
        }
    }();

    if (mapShouldDrawn) {
        DrawRadarMap();
    }
}

// 0x586D60
void CRadar::DrawCoordBlip(int32 blipIndex, bool isSprite) {
    const auto& trace = ms_RadarTrace[blipIndex];
    if (trace.m_nBlipType == BLIP_CONTACT_POINT && CTheScripts::IsPlayerOnAMission())
        return;

    if (isSprite == !trace.HasSprite())
        return;

    if (trace.m_nBlipDisplayFlag != BLIP_DISPLAY_BOTH && trace.m_nBlipDisplayFlag != BLIP_DISPLAY_BLIPONLY)
        return;

    float realDist{};
    const auto [radarPos, screenPos] = trace.GetRadarAndScreenPos(&realDist);
    const auto zoomedDist = CTheScripts::RadarZoomValue != 0u ? 255.0f : realDist;

    if (isSprite) {
        // either the blip is close to the player or we're drawing the whole map.
        const auto canBeDrawn = !trace.m_bShortRange || zoomedDist <= 1.0f || FrontEndMenuManager.m_bDrawingMap;

        if (trace.HasSprite() && canBeDrawn && HasThisBlipBeenRevealed(blipIndex)) {
            DrawRadarSprite(trace.m_nBlipSprite, screenPos.x, screenPos.y, 255);
        }
        return;
    }

    if (trace.HasSprite())
        return;

    if (FrontEndMenuManager.m_bDrawingMap && !FrontEndMenuManager.m_ShowMissionBlips) {
        // drawing the whole map but mission blips are hidden by the player.
        return;
    }

    const auto GetHeight = [&] {
        const auto zDiff = trace.GetWorldPos().z - FindPlayerCentreOfWorld_NoInteriorShift().z;

        if (zDiff < 2.0f) {
            // trace is higher
            return RADAR_TRACE_LOW;
        } else if (zDiff < -4.0f) {
            // player is higher
            return RADAR_TRACE_HIGH;
        } else {
            // they are at the around the same elevation.
            return RADAR_TRACE_NORMAL;
        }
    };

    const auto color = trace.GetStaticColour();
    CRadar::ShowRadarTraceWithHeight(
        screenPos.x,
        screenPos.y,
        trace.m_nBlipSize,
        {
            color.r,
            color.g,
            color.b,
            trace.m_bBlipFade ? color.a : CalculateBlipAlpha(realDist)
        },
        GetHeight()
    );

    AddBlipToLegendList(1, blipIndex);
}

// 0x587000
void CRadar::DrawEntityBlip(int32 blipIndex, uint8 arg1) {
    plugin::Call<0x587000, int32, uint8>(blipIndex, arg1);
}

// 0x587C10
void CRadar::ClearActualBlip(int32 blipIndex) {
    if (blipIndex < 0 || blipIndex >= MAX_RADAR_TRACES)
        return;

    ClearActualBlip(ms_RadarTrace[blipIndex]);
}

// NOTSA
void CRadar::ClearActualBlip(tRadarTrace& trace) {
    trace.m_nBlipSize = 1;
    trace.m_fSphereRadius = 1.0f;
    trace.m_pEntryExit = nullptr;
    trace.m_nBlipSprite = RADAR_SPRITE_NONE;

    trace.m_bBright       = true;
    trace.m_bTrackingBlip = false;
    trace.m_bShortRange   = false;
    trace.m_bFriendly     = false;
    trace.m_bBlipRemain   = false;
    trace.m_bBlipFade     = false;

    trace.m_nCoordBlipAppearance = BLIP_FLAG_FRIEND;
    trace.m_nBlipDisplayFlag = BLIP_DISPLAY_NEITHER;
    trace.m_nBlipType = BLIP_NONE;
}

// 0x587C60
void CRadar::ClearBlipForEntity(eBlipType blipType, int32 entityHandle) {
    for (auto& trace : ms_RadarTrace) {
        if (trace.m_nBlipType == blipType && trace.m_nEntityHandle == entityHandle) {
            ClearActualBlip(trace);
        }
    }
}

// 0x587CE0
void CRadar::ClearBlip(int32 blipIndex) {
    const auto index = GetActualBlipArrayIndex(blipIndex);
    if (index != -1) {
        ClearActualBlip(index);
    }
}

CVector GetAirStripLocation(eAirstripLocation location) {
    return CVector(airstrip_table[location].position);
}

// 0x587D20
void CRadar::SetupAirstripBlips() {
    return plugin::Call<0x587D20>();

    // WIP
    auto* vehicle = FindPlayerVehicle();
    if (vehicle && vehicle->IsSubPlane() && vehicle->m_nModelIndex != MODEL_VORTEX) {
        if ((CTimer::GetFrameCounter() & 4) == 0) {
            if (airstrip_blip) {
                return;
            }

            CVector pos = GetAirStripLocation(airstrip_location);
            airstrip_blip = SetCoordBlip(BLIP_AIRSTRIP, pos, BLIP_COLOUR_RED, BLIP_DISPLAY_BLIPONLY);
            return;
        }

        for (auto& table : airstrip_table) {
            auto distance = DistanceBetweenPoints2D(table.position, vehicle->GetPosition());
            // todo add condition
        }

        auto location = AIRSTRIP_LS_AIRPORT;
        /*
        if (distanceTo1 >= (double)distanceTo2 ||
            distanceTo1 >= (double)distanceTo3 ||
            distanceTo1 >= (double)distanceTo4
        ) {
            location = AIRSTRIP_SF_AIRPORT;
        }
        if (distanceTo2 >= (double)distanceTo1 ||
            distanceTo2 >= (double)distanceTo3 ||
            distanceTo2 >= (double)distanceTo4
        ) {
            if (distanceTo3 >= (double)distanceTo1 ||
                distanceTo3 >= (double)distanceTo2 ||
                (location = AIRSTRIP_LV_AIRPORT, distanceTo3 >= (double)distanceTo4)
            ) {
                location = AIRSTRIP_VERDANT_MEADOWS;
            }
        }
        */

        if (airstrip_location == location) {
            if (airstrip_blip) {
                return;
            }
        } else if (airstrip_blip) {
            ClearBlip(airstrip_blip);
            airstrip_location = location;
        }

        CVector pos = GetAirStripLocation(airstrip_location);
        airstrip_blip = SetCoordBlip(BLIP_AIRSTRIP, pos, BLIP_COLOUR_RED, BLIP_DISPLAY_BLIPONLY);
        return;
    }

    if (airstrip_blip) {
        ClearBlip(airstrip_blip);
        airstrip_blip = 0;
    }
}

// 0x588050
void CRadar::DrawBlips() {
    plugin::Call<0x588050>();
}

/*! Load radar blips from save file
 * @addr 0x5D53C0
 */
bool CRadar::Load() {
    Initialise();

    for (auto&& [i, trace] : notsa::enumerate(ms_RadarTrace)) {
        CGenericGameStorage::LoadDataFromWorkBuffer(&trace, sizeof(trace));
        if (trace.m_pEntryExit) {
            trace.m_pEntryExit = CEntryExitManager::mp_poolEntryExits->GetAt(i);
        }
    }

    return true;
}

/*! Save radar blips to save file
 * @addr 0x5D5860
 */
bool CRadar::Save() {
    return plugin::CallAndReturn<bool, 0x5D5860>();

    for (auto& trace : ms_RadarTrace) {
        CEntryExit* enex = nullptr;
        if (trace.m_pEntryExit) {
            // todo:
        }

        const auto& blipType = trace.m_nBlipType;
        auto bIsTracking = false;
        if (blipType != BLIP_COORD && blipType != BLIP_CONTACT_POINT) {
            if (trace.m_bTrackingBlip) {
                trace.m_bTrackingBlip = false;
                bIsTracking = true;
            }
        }

        CGenericGameStorage::SaveDataToWorkBuffer(&trace, sizeof(trace));
        if (enex) {
            trace.m_pEntryExit = enex;
        }
        if (bIsTracking) {
            trace.m_bTrackingBlip = true;
        }
    }

    return true;

}

// see CRadar::DrawLegend
// NOTSA
const char* CRadar::GetBlipName(eRadarSprite blipType) {
    switch (blipType) {
    case RADAR_SPRITE_PLAYER_INTEREST:  return TheText.Get("LG_56");
    case RADAR_SPRITE_THREAT:           return TheText.Get("LG_55");
    case RADAR_SPRITE_FRIEND:           return TheText.Get("LG_54");
    case RADAR_SPRITE_OBJECT:           return TheText.Get("LG_50");
    case RADAR_SPRITE_DESTINATION:      return TheText.Get("LG_49");
    case RADAR_SPRITE_NONE:             break;
    case RADAR_SPRITE_WHITE:            break;
    case RADAR_SPRITE_CENTRE:           break;
    case RADAR_SPRITE_MAP_HERE:         return TheText.Get("LG_01");
    case RADAR_SPRITE_NORTH:            break; // NOTSA
    case RADAR_SPRITE_AIRYARD:          return TheText.Get("LG_02");
    case RADAR_SPRITE_AMMUGUN:          return TheText.Get("LG_03");
    case RADAR_SPRITE_BARBERS:          return TheText.Get("LG_04");
    case RADAR_SPRITE_BIGSMOKE:         return TheText.Get("LG_05");
    case RADAR_SPRITE_BOATYARD:         return TheText.Get("LG_06");
    case RADAR_SPRITE_BURGERSHOT:       return TheText.Get("LG_07");
    case RADAR_SPRITE_BULLDOZER:        return TheText.Get("LG_66");
    case RADAR_SPRITE_CATALINAPINK:     return TheText.Get("LG_09");
    case RADAR_SPRITE_CESARVIAPANDO:    return TheText.Get("LG_10");
    case RADAR_SPRITE_CHICKEN:          return TheText.Get("LG_11");
    case RADAR_SPRITE_CJ:               return TheText.Get("LG_12");
    case RADAR_SPRITE_CRASH1:           return TheText.Get("LG_13");
    case RADAR_SPRITE_DINER:            return TheText.Get("LG_67");
    case RADAR_SPRITE_EMMETGUN:         return TheText.Get("LG_15");
    case RADAR_SPRITE_ENEMYATTACK:      return TheText.Get("LG_16");
    case RADAR_SPRITE_FIRE:             return TheText.Get("LG_17");
    case RADAR_SPRITE_GIRLFRIEND:       return TheText.Get("LG_18");
    case RADAR_SPRITE_HOSTPITAL:        return TheText.Get("LG_19");
    case RADAR_SPRITE_LOGOSYNDICATE:    return TheText.Get("LG_20");
    case RADAR_SPRITE_MADDOG:           return TheText.Get("LG_21");
    case RADAR_SPRITE_MAFIACASINO:      return TheText.Get("LG_22");
    case RADAR_SPRITE_MCSTRAP:          return TheText.Get("LG_23");
    case RADAR_SPRITE_MODGARAGE:        return TheText.Get("LG_24");
    case RADAR_SPRITE_OGLOC:            return TheText.Get("LG_25");
    case RADAR_SPRITE_PIZZA:            return TheText.Get("LG_26");
    case RADAR_SPRITE_POLICE:           return TheText.Get("LG_27");
    case RADAR_SPRITE_PROPERTYG:        return TheText.Get("LG_28");
    case RADAR_SPRITE_PROPERTYR:        return TheText.Get("LG_29");
    case RADAR_SPRITE_RACE:             return TheText.Get("LG_30");
    case RADAR_SPRITE_RYDER:            return TheText.Get("LG_31");
    case RADAR_SPRITE_SAVEGAME:         return TheText.Get("LG_32");
    case RADAR_SPRITE_SCHOOL:           return TheText.Get("LG_33");
    case RADAR_SPRITE_QMARK:            return TheText.Get("LG_63");
    case RADAR_SPRITE_SWEET:            return TheText.Get("LG_35");
    case RADAR_SPRITE_TATTOO:           return TheText.Get("LG_36");
    case RADAR_SPRITE_THETRUTH:         return TheText.Get("LG_37");
    case RADAR_SPRITE_WAYPOINT:         return TheText.Get("LG_64");
    case RADAR_SPRITE_TORENORANCH:      return TheText.Get("LG_39");
    case RADAR_SPRITE_TRIADS:           return TheText.Get("LG_40");
    case RADAR_SPRITE_TRIADSCASINO:     return TheText.Get("LG_41");
    case RADAR_SPRITE_TSHIRT:           return TheText.Get("LG_42");
    case RADAR_SPRITE_WOOZIE:           return TheText.Get("LG_43");
    case RADAR_SPRITE_ZERO:             return TheText.Get("LG_44");
    case RADAR_SPRITE_DATEDISCO:        return TheText.Get("LG_45");
    case RADAR_SPRITE_DATEDRINK:        return TheText.Get("LG_46");
    case RADAR_SPRITE_DATEFOOD:         return TheText.Get("LG_47");
    case RADAR_SPRITE_TRUCK:            return TheText.Get("LG_48");
    case RADAR_SPRITE_CASH:             return TheText.Get("LG_51");
    case RADAR_SPRITE_FLAG:             return TheText.Get("LG_52");
    case RADAR_SPRITE_GYM:              return TheText.Get("LG_53");
    case RADAR_SPRITE_IMPOUND:          return TheText.Get("LG_57");
    case RADAR_SPRITE_LIGHT:            break;
    case RADAR_SPRITE_RUNWAY:           return TheText.Get("LG_65");
    case RADAR_SPRITE_GANGB:            return TheText.Get("LG_58");
    case RADAR_SPRITE_GANGP:            return TheText.Get("LG_59");
    case RADAR_SPRITE_GANGY:            return TheText.Get("LG_60");
    case RADAR_SPRITE_GANGN:            return TheText.Get("LG_61");
    case RADAR_SPRITE_GANGG:            return TheText.Get("LG_62");
    case RADAR_SPRITE_SPRAY:            return TheText.Get("LG_34");
    case RADAR_SPRITE_TORENO:           break;
    default:
        break;
    }
    NOTSA_UNREACHABLE("Bug in GetBlipName");
    return nullptr;
}

int32 CRadar::FindTraceNotTrackingBlipIndex() {
    for (auto&& [i, v] : notsa::enumerate(ms_RadarTrace)) {
        if (!v.m_bTrackingBlip) {
            return (int32)i;
        }
    }
    return -1;
}

// Color with the alpha set to 0xFF
// NOTSA
CRGBA tRadarTrace::GetStaticColour() const {
    switch (m_nAppearance) {
    case eBlipAppearance::BLIP_FLAG_FRIEND:
        return CRadar::GetRadarTraceColour(m_nColour, m_bBright, false);

    case eBlipAppearance::BLIP_FLAG_THREAT:
        return HudColour.GetIntColour(HUD_COLOUR_BLUE);

    case eBlipAppearance::BLIP_FLAG_UNK:
        return HudColour.GetIntColour(HUD_COLOUR_RED);

    default:
        NOTSA_UNREACHABLE("Invalid blip appearance (={})", (uint8)m_nAppearance);
    }

    return 0;
}

CVector tRadarTrace::GetWorldPos() const {
    if (m_pEntryExit) {
        CVector pos{};
        m_pEntryExit->GetPositionRelativeToOutsideWorld(pos);
        return pos;
    } else {
        return m_vPosition;
    }
}

std::pair<CVector2D, CVector2D> tRadarTrace::GetRadarAndScreenPos(float* radarPointDist) const {
    const auto world = GetWorldPos();

    CVector2D radar;
    CRadar::TransformRealWorldPointToRadarSpace(radar, world);

    const auto dist = CRadar::LimitRadarPoint(radar); // Normalises vector `radar`
    if (radarPointDist) {
        *radarPointDist = dist;
    }

    CVector2D screen;
    CRadar::TransformRadarPointToScreenSpace(screen, radar);

    return std::make_pair(radar, screen);
}
