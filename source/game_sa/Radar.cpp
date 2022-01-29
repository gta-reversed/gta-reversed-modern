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
static inline float& cachedSin = *(float*)0xBA830c;

static inline uint8& airstrip_location = *(uint8*)0xBA8300; // current airstrip index in airstrip_table
static inline int32& airstrip_blip = *(int32*)0xBA8304;     // blip handle

constexpr std::array<airstrip_info, 4> airstrip_table = { // 0x8D06E0
    airstrip_info{ 1750.0f,  -2494.0f, 180.0f, 1000.0f },
    airstrip_info{ -1373.0f,  120.0f,  315.0f, 1500.0f },
    airstrip_info{ 1478.0f,  1461.0f,  90.0f,  1200.0f },
    airstrip_info{ 175.0f,   2502.0f,  180.0f, 1000.0f }
};

static std::array<int32, MAX_RADAR_WIDTH_TILES * MAX_RADAR_HEIGHT_TILES>& gRadarTextures = *(std::array<int32, 12 * 12>*)0xBA8478;

// name, maskName
// 0x8d0720
const char* CRadar::RadarBlipFileNames[][2] = {
    nullptr,               nullptr,
    nullptr,               nullptr,
    "radar_centre",        nullptr,
    "arrow",               nullptr,
    "radar_north",         nullptr,
    "radar_airYard",       nullptr,
    "radar_ammugun",       nullptr,
    "radar_barbers",       nullptr,
    "radar_BIGSMOKE",      nullptr,
    "radar_boatyard",      nullptr,
    "radar_burgerShot",    nullptr,
    "radar_bulldozer",     nullptr,
    "radar_CATALINAPINK",  nullptr,
    "radar_CESARVIAPANDO", nullptr,
    "radar_chicken",       nullptr,
    "radar_CJ",            nullptr,
    "radar_CRASH1",        nullptr,
    "radar_diner",         nullptr,
    "radar_emmetGun",      nullptr,
    "radar_enemyAttack",   nullptr,
    "radar_fire",          nullptr,
    "radar_girlfriend",    nullptr,
    "radar_hostpitaL",     nullptr,
    "radar_LocoSyndicate", nullptr,
    "radar_MADDOG",        nullptr,
    "radar_mafiaCasino",   nullptr,
    "radar_MCSTRAP",       nullptr,
    "radar_modGarage",     nullptr,
    "radar_OGLOC",         nullptr,
    "radar_pizza",         nullptr,
    "radar_police",        nullptr,
    "radar_propertyG",     nullptr,
    "radar_propertyR",     nullptr,
    "radar_race",          nullptr,
    "radar_RYDER",         nullptr,
    "radar_saveGame",      nullptr,
    "radar_school",        nullptr,
    "radar_qmark",         nullptr,
    "radar_SWEET",         nullptr,
    "radar_tattoo",        nullptr,
    "radar_THETRUTH",      nullptr,
    "radar_waypoint",      nullptr,
    "radar_TorenoRanch",   nullptr,
    "radar_triads",        nullptr,
    "radar_triadsCasino",  nullptr,
    "radar_tshirt",        nullptr,
    "radar_WOOZIE",        nullptr,
    "radar_ZERO",          nullptr,
    "radar_dateDisco",     nullptr,
    "radar_dateDrink",     nullptr,
    "radar_dateFood",      nullptr,
    "radar_truck",         nullptr,
    "radar_cash",          nullptr,
    "radar_flag",          nullptr,
    "radar_gym",           nullptr,
    "radar_impound",       nullptr,
    "radar_light",         nullptr,
    "radar_runway",        nullptr,
    "radar_gangB",         nullptr,
    "radar_gangP",         nullptr,
    "radar_gangY",         nullptr,
    "radar_gangN",         nullptr,
    "radar_gangG",         nullptr,
    "radar_spray",         nullptr,
};

eRadarTraceHeight& CRadar::legendTraceHeight = *(eRadarTraceHeight*)0xBAA350;
uint32& CRadar::legendTraceTimer = *(uint32*)0xBAA354;

uint32& CRadar::mapYouAreHereTimer = *(uint32*)0xBAA358;
bool& CRadar::mapYouAreHereDisplay = *(bool*)0x8D0930;

#define RADAR_MIN_RANGE (180.0f)
#define RADAR_MAX_RANGE (350.0f)
#define RADAR_MIN_SPEED (0.3f)
#define RADAR_MAX_SPEED (0.9f)

void CRadar::InjectHooks()
{
    RH_ScopedClass(CRadar);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Initialise, 0x587FB0);
    RH_ScopedInstall(LoadTextures, 0x5827D0);
    RH_ScopedInstall(DrawLegend, 0x5828A0);
    RH_ScopedInstall(LimitRadarPoint, 0x5832F0);
    RH_ScopedInstall(Shutdown, 0x585940);
    RH_ScopedInstall(SetMapCentreToPlayerCoords, 0x585B20);
    RH_ScopedInstall(InitFrontEndMap, 0x585960);
    RH_ScopedInstall(CalculateBlipAlpha, 0x583420);
    //RH_ScopedInstall(TransformRadarPointToScreenSpace, 0x583480, true, { .reversed = false }); // register problem?
    RH_ScopedInstall(TransformRealWorldPointToRadarSpace, 0x583530);
    RH_ScopedInstall(CalculateCachedSinCos, 0x583670);
    RH_ScopedInstall(SetBlipSprite, 0x583D70);
    RH_ScopedInstall(SetBlipAlwaysDisplayInZoom, 0x583DB0);
    RH_ScopedInstall(DrawYouAreHereSprite, 0x584960);
    RH_ScopedInstall(ChangeBlipColour, 0x583AB0);
    RH_ScopedInstall(ClearActualBlip, 0x587C10);
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
    RH_ScopedGlobalInstall(GetTextureCorners, 0x584D90);
    RH_ScopedInstall(ShowRadarMarker, 0x584480);
    RH_ScopedInstall(DrawRadarMask, 0x585700);
    RH_ScopedInstall(Load, 0x5D53C0);
    RH_ScopedGlobalInstall(Save, 0x5D5860, { .reversed = false });
    RH_ScopedInstall(SetBlipFade, 0x583E00); // unused
    RH_ScopedInstall(SetCoordBlipAppearance, 0x583E50);
    RH_ScopedInstall(SetCoordBlip, 0x583820);
    RH_ScopedInstall(SetEntityBlip, 0x5839A0);
    RH_ScopedInstall(DisplayThisBlip, 0x583B40);
    
    RH_ScopedInstall(GetNewUniqueBlipIndex, 0x582820);
    RH_ScopedInstall(TransformRadarPointToRealWorldSpace, 0x5835A0);
    RH_ScopedGlobalInstall(IsPointInsideRadar, 0x584D40);
}

// 0x587FB0
void CRadar::Initialise()
{
    airstrip_blip = 0;
    airstrip_location = 0;

    for (auto i = 0u; i < ms_RadarTrace.size(); i++) {
        ClearActualBlip(i);
    }

    /*
    for (auto& trace : ms_RadarTrace) {
        trace.m_fSphereRadius = 1.0f;
        trace.m_nBlipSize     = 0;
        trace.m_pEntryExit    = nullptr;
        trace.m_nCounter      = 1;

        trace.m_bBright              = true;
        trace.m_bTrackingBlip        = false;
        trace.m_bShortRange          = false;
        trace.m_bFriendly            = false;
        trace.m_bBlipRemain          = false;
        trace.m_bBlipFade            = false;
        trace.m_nCoordBlipAppearance = BLIP_FLAG_FRIEND;
        trace.m_nBlipDisplayFlag     = BLIP_DISPLAY_NEITHER;
        trace.m_nBlipType            = BLIP_NONE;
    }
    */

    m_radarRange = 350.0f;

    for (auto i = 0u; i < gRadarTextures.size(); i++) {
        char txdName[16] = { 0 };
        sprintf(txdName, "radar%02d", i);
        gRadarTextures[i] = CTxdStore::FindTxdSlot(txdName);
    }
}

// 0x585940
void CRadar::Shutdown()
{
    for (auto& sprite : RadarBlipSprites) {
        sprite.Delete();
    }
    RemoveRadarSections();
}

// 0x5827D0
void CRadar::LoadTextures()
{
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(CTxdStore::FindTxdSlot("hud"));

    for (auto i = 0; i < MAX_RADAR_SPRITES; i++)
        RadarBlipSprites[i].SetTexture(RadarBlipFileNames[i][0]);

    CTxdStore::PopCurrentTxd();
}

// 0x582820 - Seemingly unused but actually just inlined
int32 CRadar::GetNewUniqueBlipIndex(int32 idx)
{
    auto& t = ms_RadarTrace[idx];
    if (t.m_nCounter >= USHRT_MAX - 1)
        t.m_nCounter = 1; // Wrap back to 1
    else
        t.m_nCounter++; // Increment
    return idx | (t.m_nCounter << 16);
}

// 0x582870
int32 CRadar::GetActualBlipArrayIndex(int32 blipIndex)
{
    if (blipIndex == -1)
        return -1;

    uint16 traceIndex = (uint16)blipIndex;
    uint16 counter = blipIndex >> 16;
    tRadarTrace& trace = ms_RadarTrace[traceIndex];
    if (counter != trace.m_nCounter || !trace.m_bTrackingBlip)
        return -1;

    return traceIndex;
}

// 0x5828A0
void CRadar::DrawLegend(int32 x, int32 y, eRadarSprite blipType)
{
    const char* blipName{};

    switch (blipType) {
    case (eRadarSprite)-5:
        blipName = TheText.Get("LG_56"); // Player interest
        break;
    case (eRadarSprite)-4:
        blipName = TheText.Get("LG_55"); // Threat
        break;
    case (eRadarSprite)-3:
        blipName = TheText.Get("LG_54"); // Friend
        break;
    case (eRadarSprite)-2:
        blipName = TheText.Get("LG_50"); // Object
        break;
    case (eRadarSprite)-1:
        blipName = TheText.Get("LG_49"); // Destination
        break;
    // NOTSA
    case RADAR_SPRITE_NONE:
        // blipType = 0 for player position
        blipType = RADAR_SPRITE_MAP_HERE;
        /* fallthrough */
    case RADAR_SPRITE_MAP_HERE:
        blipName = TheText.Get("LG_01");
        break;
    case RADAR_SPRITE_AIRYARD:
        blipName = TheText.Get("LG_02");
        break;
    case RADAR_SPRITE_AMMUGUN:
        blipName = TheText.Get("LG_03");
        break;
    case RADAR_SPRITE_BARBERS:
        blipName = TheText.Get("LG_04");
        break;
    case RADAR_SPRITE_BIGSMOKE:
        blipName = TheText.Get("LG_05");
        break;
    case RADAR_SPRITE_BOATYARD:
        blipName = TheText.Get("LG_06");
        break;
    case RADAR_SPRITE_BURGERSHOT:
        blipName = TheText.Get("LG_07");
        break;
    case RADAR_SPRITE_BULLDOZER:
        blipName = TheText.Get("LG_66");
        break;
    case RADAR_SPRITE_CATALINAPINK:
        blipName = TheText.Get("LG_09");
        break;
    case RADAR_SPRITE_CESARVIAPANDO:
        blipName = TheText.Get("LG_10");
        break;
    case RADAR_SPRITE_CHICKEN:
        blipName = TheText.Get("LG_11");
        break;
    case RADAR_SPRITE_CJ:
        blipName = TheText.Get("LG_12");
        break;
    case RADAR_SPRITE_CRASH1:
        blipName = TheText.Get("LG_13");
        break;
    case RADAR_SPRITE_DINER:
        blipName = TheText.Get("LG_67");
        break;
    case RADAR_SPRITE_EMMETGUN:
        blipName = TheText.Get("LG_15");
        break;
    case RADAR_SPRITE_ENEMYATTACK:
        blipName = TheText.Get("LG_16");
        break;
    case RADAR_SPRITE_FIRE:
        blipName = TheText.Get("LG_17");
        break;
    case RADAR_SPRITE_GIRLFRIEND:
        blipName = TheText.Get("LG_18");
        break;
    case RADAR_SPRITE_HOSTPITAL:
        blipName = TheText.Get("LG_19");
        break;
    case RADAR_SPRITE_LOGOSYNDICATE:
        blipName = TheText.Get("LG_20");
        break;
    case RADAR_SPRITE_MADDOG:
        blipName = TheText.Get("LG_21");
        break;
    case RADAR_SPRITE_MAFIACASINO:
        blipName = TheText.Get("LG_22");
        break;
    case RADAR_SPRITE_MCSTRAP:
        blipName = TheText.Get("LG_23");
        break;
    case RADAR_SPRITE_MODGARAGE:
        blipName = TheText.Get("LG_24");
        break;
    case RADAR_SPRITE_OGLOC:
        blipName = TheText.Get("LG_25");
        break;
    case RADAR_SPRITE_PIZZA:
        blipName = TheText.Get("LG_26");
        break;
    case RADAR_SPRITE_POLICE:
        blipName = TheText.Get("LG_27");
        break;
    case RADAR_SPRITE_PROPERTYG:
        blipName = TheText.Get("LG_28");
        break;
    case RADAR_SPRITE_PROPERTYR:
        blipName = TheText.Get("LG_29");
        break;
    case RADAR_SPRITE_RACE:
        blipName = TheText.Get("LG_30");
        break;
    case RADAR_SPRITE_RYDER:
        blipName = TheText.Get("LG_31");
        break;
    case RADAR_SPRITE_SAVEGAME:
        blipName = TheText.Get("LG_32");
        break;
    case RADAR_SPRITE_SCHOOL:
        blipName = TheText.Get("LG_33");
        break;
    case RADAR_SPRITE_QMARK:
        blipName = TheText.Get("LG_63");
        break;
    case RADAR_SPRITE_SWEET:
        blipName = TheText.Get("LG_35");
        break;
    case RADAR_SPRITE_TATTOO:
        blipName = TheText.Get("LG_36");
        break;
    case RADAR_SPRITE_THETRUTH:
        blipName = TheText.Get("LG_37");
        break;
    case RADAR_SPRITE_WAYPOINT:
        blipName = TheText.Get("LG_64");
        break;
    case RADAR_SPRITE_TORENORANCH:
        blipName = TheText.Get("LG_39");
        break;
    case RADAR_SPRITE_TRIADS:
        blipName = TheText.Get("LG_40");
        break;
    case RADAR_SPRITE_TRIADSCASINO:
        blipName = TheText.Get("LG_41");
        break;
    case RADAR_SPRITE_TSHIRT:
        blipName = TheText.Get("LG_42");
        break;
    case RADAR_SPRITE_WOOZIE:
        blipName = TheText.Get("LG_43");
        break;
    case RADAR_SPRITE_ZERO:
        blipName = TheText.Get("LG_44");
        break;
    case RADAR_SPRITE_DATEDISCO:
        blipName = TheText.Get("LG_45");
        break;
    case RADAR_SPRITE_DATEDRINK:
        blipName = TheText.Get("LG_46");
        break;
    case RADAR_SPRITE_DATEFOOD:
        blipName = TheText.Get("LG_47");
        break;
    case RADAR_SPRITE_TRUCK:
        blipName = TheText.Get("LG_48");
        break;
    case RADAR_SPRITE_CASH:
        blipName = TheText.Get("LG_51");
        break;
    case RADAR_SPRITE_FLAG:
        blipName = TheText.Get("LG_52");
        break;
    case RADAR_SPRITE_GYM:
        blipName = TheText.Get("LG_53");
        break;
    case RADAR_SPRITE_IMPOUND:
        blipName = TheText.Get("LG_57");
        break;
    case RADAR_SPRITE_RUNWAY:
        blipName = TheText.Get("LG_65");
        break;
    case RADAR_SPRITE_GANGB:
        blipName = TheText.Get("LG_58");
        break;
    case RADAR_SPRITE_GANGP:
        blipName = TheText.Get("LG_59");
        break;
    case RADAR_SPRITE_GANGY:
        blipName = TheText.Get("LG_60");
        break;
    case RADAR_SPRITE_GANGN:
        blipName = TheText.Get("LG_61");
        break;
    case RADAR_SPRITE_GANGG:
        blipName = TheText.Get("LG_62");
        break;
    case RADAR_SPRITE_SPRAY:
        blipName = TheText.Get("LG_34");
        break;
    }

    CRect rt;
    rt.left = (float)x;
    rt.bottom = (float)y;

    CFont::PrintString(SCREEN_WIDTH_UNIT * 20.0f + rt.left, SCREEN_HEIGHT_UNIT * 3.0f + rt.bottom, blipName);

    auto blipId = (int32)blipType;

    if (blipId > -1) {
        // the blip is a sprite
        CRGBA color(255, 255, 255, 255);

        rt.right = rt.left + SCREEN_WIDTH_UNIT * 16.0f;
        rt.top = rt.bottom + SCREEN_WIDTH_UNIT * 16.0f;

        RadarBlipSprites[blipId].Draw(rt, color);

        return;
    }

    // arrow blips have negative type ids
    CRGBA arrowColor = ArrowBlipColour[-blipId];

    if (CTimer::GetTimeInMSPauseMode() - legendTraceTimer > 600) {
        legendTraceTimer = CTimer::GetTimeInMSPauseMode();

        legendTraceHeight = static_cast<eRadarTraceHeight>((legendTraceHeight + 1) % 3);
    }

    CRGBA black(0, 0, 0, 255);

    float posX = std::round(SCREEN_WIDTH_UNIT * 8.0f + (float)x);
    float posY = std::round(SCREEN_HEIGHT_UNIT * 8.0f + (float)y);

    switch (legendTraceHeight) {
    case RADAR_TRACE_LOW: {
        float x0 = posX + SCREEN_HEIGHT_UNIT * 7.0f;
        float y0 = posY + SCREEN_HEIGHT_UNIT * 7.0f;
        float x1 = posX - SCREEN_HEIGHT_UNIT * 7.0f;
        float y1 = posY + SCREEN_HEIGHT_UNIT * 7.0f;
        float x2 = posX;
        float y2 = posY - SCREEN_WIDTH_UNIT * 7.0f;

        CSprite2d::Draw2DPolygon(x0, y0, x1, y1, x2, y2, x2, y2, black);

        x0 = posX + SCREEN_HEIGHT_UNIT * 5.0f;
        y0 = posY + SCREEN_HEIGHT_UNIT * 5.0f;
        x1 = posX - SCREEN_HEIGHT_UNIT * 5.0f;
        y1 = posY + SCREEN_HEIGHT_UNIT * 5.0f;
        x2 = posX;
        y2 = posY - SCREEN_WIDTH_UNIT * 5.0f;

        CSprite2d::Draw2DPolygon(x0, y0, x1, y1, x2, y2, x2, y2, arrowColor);
        break;
    }
    case RADAR_TRACE_HIGH: {
        float x0 = posX + SCREEN_HEIGHT_UNIT * 7.0f;
        float y0 = posY - SCREEN_WIDTH_UNIT * 7.0f;
        float x1 = posX - SCREEN_HEIGHT_UNIT * 7.0f;
        float y1 = posY - SCREEN_WIDTH_UNIT * 7.0f;
        float x2 = posX;
        float y2 = SCREEN_HEIGHT_UNIT * 7.0f + posY;

        CSprite2d::Draw2DPolygon(x0, y0, x1, y1, x2, y2, x2, y2, black);

        x0 = posX + SCREEN_HEIGHT_UNIT * 5.0f;
        y0 = posY - SCREEN_WIDTH_UNIT * 5.0f;
        x1 = posX - SCREEN_HEIGHT_UNIT * 5.0f;
        y1 = posY - SCREEN_WIDTH_UNIT * 5.0f;
        x2 = posX;
        y2 = SCREEN_HEIGHT_UNIT * 5.0f + posY;

        CSprite2d::Draw2DPolygon(x0, y0, x1, y1, x2, y2, x2, y2, arrowColor);
        break;
    }
    case RADAR_TRACE_NORMAL: {
        rt.bottom    = posY - SCREEN_HEIGHT_UNIT * 5.0f;
        rt.top = posY + SCREEN_HEIGHT_UNIT * 5.0f;
        rt.left   = posX - SCREEN_WIDTH_UNIT * 5.0f;
        rt.right  = posX + SCREEN_WIDTH_UNIT * 5.0f;

        CSprite2d::DrawRect(rt, black);

        rt.bottom    = posY - SCREEN_HEIGHT_UNIT * 4.0f;
        rt.top = posY + SCREEN_HEIGHT_UNIT * 4.0f;
        rt.left   = posX - SCREEN_WIDTH_UNIT * 4.0f;
        rt.right  = posX + SCREEN_WIDTH_UNIT * 4.0f;

        CSprite2d::DrawRect(rt, arrowColor);
        break;
    }
    }
}

// 0x5832F0
float CRadar::LimitRadarPoint(CVector2D& point)
{
    float mag = point.Magnitude();

    if (FrontEndMenuManager.m_bDrawRadarOrMap)
        return mag;

    if (mag > 1.0f)
        point.Normalise();

    return mag;
}

// 0x583350
void CRadar::LimitToMap(float* pX, float* pY)
{
    float zoom = (FrontEndMenuManager.m_bMapLoaded) ? FrontEndMenuManager.m_fMapZoom : 140.0f;

    float xMin = (FrontEndMenuManager.m_vMapOrigin.x - zoom) * SCREEN_WIDTH_UNIT;
    float xMax = (FrontEndMenuManager.m_vMapOrigin.x + zoom) * SCREEN_WIDTH_UNIT;
    *pX = std::clamp(*pX, xMin, xMax);

    float yMin = (FrontEndMenuManager.m_vMapOrigin.y - zoom) * SCREEN_HEIGHT_UNIT;
    float yMax = (FrontEndMenuManager.m_vMapOrigin.y + zoom) * SCREEN_HEIGHT_UNIT;
    *pY = std::clamp(*pY, yMin, yMax);
}

// 0x583420
uint8 CRadar::CalculateBlipAlpha(float distance)
{
    if (FrontEndMenuManager.m_bDrawRadarOrMap)
        return 255;

    auto distAlpha = 255 - (int32)(distance * 1.0f / 60.0f * 255.0f);

    return std::max(distAlpha, 70);
}

// 0x583480
// NOTE: Unhooked by default for now. Causes `DrawRadarSection` to crash.
void CRadar::TransformRadarPointToScreenSpace(CVector2D& out, const CVector2D& in)
{
    if (FrontEndMenuManager.m_bDrawRadarOrMap) {
        out.x = FrontEndMenuManager.m_vMapOrigin.x + FrontEndMenuManager.m_fMapZoom * in.x;
        out.y = FrontEndMenuManager.m_vMapOrigin.y - FrontEndMenuManager.m_fMapZoom * in.y;
    } else {
        out.x = SCREEN_STRETCH_X(94.0f) / 2.0f + SCREEN_STRETCH_X(40.0f) + SCREEN_STRETCH_X(94.0f * in.x) / 2.0f;
        out.y = SCREEN_HEIGHT - SCREEN_STRETCH_Y(104.0f) + SCREEN_STRETCH_Y(76.0f) / 2.0f - SCREEN_STRETCH_Y(76.0f * in.y) / 2.0f;
    }
}

// 0x583530
void CRadar::TransformRealWorldPointToRadarSpace(CVector2D& out, const CVector2D& in)
{
    float rangeRecip = 1.0f / m_radarRange;

    float xOffset = rangeRecip * (in.x - vec2DRadarOrigin.x);
    float yOffset = rangeRecip * (in.y - vec2DRadarOrigin.y);

    out.x = cachedSin * yOffset + cachedCos * xOffset;
    out.y = cachedCos * yOffset - cachedSin * xOffset;
}

// unused
// 0x5835A0
void CRadar::TransformRadarPointToRealWorldSpace(CVector2D& out, const CVector2D& in)
{
    out.x = cachedCos * in.x - cachedSin * in.y;
    out.y = cachedCos * in.y + cachedSin * in.x;

    out *= m_radarRange;
    out += vec2DRadarOrigin;
}

// unused, see CRadar::DrawRadarSection
// 0x583600
void CRadar::TransformRealWorldToTexCoordSpace(CVector2D& out, const CVector2D& in, int32 x, int32 y)
{
    out.x = in.x - ((500 * x) - 3000.0f);
    out.y = -(in.y - ((500 * (12 - y)) - 3000.0f));

    out.x *= 0.002f;
    out.y *= 0.002f;
}

// 0x583670
void CRadar::CalculateCachedSinCos()
{
    if (FrontEndMenuManager.m_bDrawRadarOrMap) {
        cachedSin = 0.0f;
        cachedCos = 1.0f;

        return;
    }

    if (TheCamera.GetLookDirection() == LOOKING_DIRECTION_FORWARD) {
        float angle;

        if (TheCamera.m_matrix) {
            CVector forward = TheCamera.m_matrix->GetForward();
            angle = atan2(-forward.x, forward.y);
        }
        else
            angle = TheCamera.m_placement.m_fHeading;

        m_fRadarOrientation = angle;
        cachedSin = sin(angle);
        cachedCos = cos(angle);

        return;
    }

    auto activeCam = CCamera::GetActiveCamera();
    CEntity* targetEntity = activeCam.m_pCamTargetEntity;

    CVector in;

    if (activeCam.m_nMode == MODE_1STPERSON || TheCamera.GetLookDirection() == LOOKING_DIRECTION_UNKNOWN_1) {
        if (!targetEntity->m_matrix) {
            targetEntity->AllocateMatrix();
            targetEntity->m_placement.UpdateMatrix(targetEntity->m_matrix);
        }

        in = targetEntity->m_matrix->GetForward();
        in.Normalise();
    }
    else {
        in = targetEntity->GetPosition() - activeCam.m_vecSourceBeforeLookBehind;
    }

    float angle = atan2(-in.x, in.y);
    cachedSin = sin(angle);
    cachedCos = cos(angle);
    m_fRadarOrientation = angle;
}

// 0x583820
int32 CRadar::SetCoordBlip(eBlipType type, CVector posn, _IGNORED_ eBlipColour color, eBlipDisplay blipDisplay, _IGNORED_ char* scriptName)
{
    if (auto idx = FindTraceNotTrackingBlipIndex(); idx != -1) {
        auto& t = ms_RadarTrace[idx];

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

        return GetNewUniqueBlipIndex(idx);
    }
    return -1;
}

// 0x583920
int32 CRadar::SetShortRangeCoordBlip(eBlipType type, CVector posn, eBlipColour color, eBlipDisplay blipDisplay, char* scriptName)
{
    int32 index = SetCoordBlip(type, posn, color, blipDisplay, scriptName);
    if (index == -1)
        return -1;

    auto actualIndex = GetActualBlipArrayIndex(index);
    ms_RadarTrace[actualIndex].m_bShortRange = true;
    return index;
}

// 0x5839A0
int32 CRadar::SetEntityBlip(eBlipType type, int32 entityHandle, uint32 arg2, eBlipDisplay blipDisplay)
{
    if (auto idx = FindTraceNotTrackingBlipIndex(); idx != -1) {
        auto& t = ms_RadarTrace[idx];

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

        return GetNewUniqueBlipIndex(idx);
    }
    return -1;
}

// 0x583AB0
void CRadar::ChangeBlipColour(int32 blipIndex, uint32 color)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_nColour = static_cast<eBlipColour>(color);
}

// 0x583AF0
bool CRadar::HasThisBlipBeenRevealed(int32 blipIndex)
{
    CVector blipPos = ms_RadarTrace[blipIndex].m_vPosition;

    if (!FrontEndMenuManager.m_bDrawRadarOrMap || !ms_RadarTrace[blipIndex].m_bShortRange
    || CTheZones::ZonesRevealed > 80 || CTheZones::GetCurrentZoneLockedOrUnlocked(blipPos.x, blipPos.y))
        return true;

    return false;
}

// 0x583B40
bool CRadar::DisplayThisBlip(eRadarSprite spriteId, char priority)
{
    if (CGame::CanSeeOutSideFromCurrArea() || FindPlayerPed()->m_nAreaCode == AREA_CODE_NORMAL_WORLD) {
        switch (spriteId)
        {
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
    } else {
        switch (spriteId)
        {
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
            return (FrontEndMenuManager.field_45[0] && priority < 0) || priority == 1;

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
            return (FrontEndMenuManager.field_45[1] && priority < 0) || priority == 3;

        default:
            return (FrontEndMenuManager.field_45[3] && priority < 0) || priority == 2;
        }
    }
}

// unused
// 0x583C70
void CRadar::ChangeBlipBrightness(int32 blipIndex, int32 brightness)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_bBright = brightness == 1 ? true : false;
}

// 0x583CC0
void CRadar::ChangeBlipScale(int32 blipIndex, int32 size)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (FrontEndMenuManager.m_bDrawRadarOrMap)
        size = 1;

    ms_RadarTrace[index].m_nBlipSize = size;
}

// 0x583D20
void CRadar::ChangeBlipDisplay(int32 blipIndex, eBlipDisplay blipDisplay)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_nBlipDisplayFlag = blipDisplay;
}

// 0x583D70
void CRadar::SetBlipSprite(int32 blipIndex, int32 spriteId)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (ms_RadarTrace[index].m_bTrackingBlip)
        ms_RadarTrace[index].m_nBlipSprite = static_cast<eRadarSprite>(spriteId);
}

// 0x583DB0
void CRadar::SetBlipAlwaysDisplayInZoom(int32 blipIndex, uint8 display)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (ms_RadarTrace[index].m_bTrackingBlip)
        ms_RadarTrace[index].m_bBlipRemain = display;
}

// unused?
// 0x583E00
void CRadar::SetBlipFade(int32 blipIndex, bool fade)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_bBlipFade = fade;
}

// 0x583E50
void CRadar::SetCoordBlipAppearance(int32 blipIndex, eBlipAppearance appearance)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (ms_RadarTrace[index].m_nBlipDisplayFlag == (BLIP_DISPLAY_BLIPONLY | BLIP_DISPLAY_BOTH) && appearance <= 2)
        ms_RadarTrace[index].m_nCoordBlipAppearance = appearance;
}

// 0x583EB0
void CRadar::SetBlipFriendly(int32 blipIndex, bool friendly)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_bFriendly = friendly;
}

// 0x583F00
void CRadar::SetBlipEntryExit(int32 blipIndex, CEntryExit* enex)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (ms_RadarTrace[index].m_bTrackingBlip)
        ms_RadarTrace[index].m_pEntryExit = enex;
}

// 0x583F40
void CRadar::ShowRadarTrace(float x, float y, uint32 size, uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
    // unused
    ((void(__cdecl*)(float, float, uint32, uint8, uint8, uint8, uint8))0x583F40)(x, y, size, red, green, blue, alpha);
}

// 0x584070
void CRadar::ShowRadarTraceWithHeight(float x, float y, uint32 size, uint8 red, uint8 green, uint8 blue, uint8 alpha, eRadarTraceHeight height)
{
    ((void(__cdecl*)(float, float, uint32, uint8, uint8, uint8, uint8, eRadarTraceHeight))0x584070)(x, y, size, red, green, blue, alpha, height);
}

// show debug line at this position
// 0x584480
void CRadar::ShowRadarMarker(CVector p, uint32 color, float radius)
{
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
uint32 CRadar::GetRadarTraceColour(eBlipColour color, bool bright, bool friendly)
{
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
void CRadar::DrawRotatingRadarSprite(CSprite2d* sprite, float x, float y, float angle, uint32 width, uint32 height, CRGBA color)
{
    CVector2D verts[4];

    if (FrontEndMenuManager.m_bDrawRadarOrMap) {
        x *= SCREEN_WIDTH_UNIT;
        y *= SCREEN_HEIGHT_UNIT;

        LimitToMap(&x, &y);
    }

    for (auto i = 0u; i < std::size(verts); i++) {
        float theta = (float)i * HALF_PI + (angle - PI / 4.0f);

        verts[i].x = std::sin(theta) * (float)width + x;
        verts[i].y = std::cos(theta) * (float)height + y;
    }

    sprite->Draw(verts[3].x, verts[3].y, verts[2].x, verts[2].y, verts[0].x, verts[0].y, verts[1].x, verts[1].y, color);
}

// 0x584960
void CRadar::DrawYouAreHereSprite(float x, float y)
{
    if ((CTimer::GetTimeInMSPauseMode() - mapYouAreHereTimer) > 700) {
        mapYouAreHereTimer = CTimer::GetTimeInMSPauseMode();
        mapYouAreHereDisplay = !mapYouAreHereDisplay;
    }

    if (mapYouAreHereDisplay) {
        float angle = FindPlayerHeading(0) + PI;
        float circleAngle = angle + HALF_PI;

        CRGBA white(255, 255, 255, 255);
        float drawX = x + 17.0f * cos(circleAngle);
        float drawY = y - 17.0f * sin(circleAngle);

        DrawRotatingRadarSprite(
            &RadarBlipSprites[RADAR_SPRITE_MAP_HERE],
            drawX,
            drawY,
            angle,
            (uint32)(25.0f * SCREEN_WIDTH_UNIT),
            (uint32)(25.0f * SCREEN_HEIGHT_UNIT),
            white
        );
    }

    MapLegendCounter++;
    MapLegendList[MapLegendCounter] = RADAR_SPRITE_MAP_HERE;
}

// 0x584A80
void CRadar::SetupRadarRect(int32 x, int32 y)
{
    m_radarRect.left   = 500.0f * (x - 6) - 500.0f;
    m_radarRect.bottom = 500.0f * (5 - y) - 500.0f;
    m_radarRect.right  = 500.0f * (x - 4);
    m_radarRect.top    = 500.0f * (7 - y);
}

// unused
// 0x584B00
bool ClipRadarTileCoords(int32& x, int32& y)
{
    return ((bool(__cdecl*)(int32&, int32&))0x584B00)(x, y);
}

// 0x584B50
void CRadar::RequestMapSection(int32 x, int32 y)
{
    if (x < 0 || x > 11 || y < 0 || y > 11)
        return;

    int32 tex = GetRadarTexture(x, y);
    if (tex == -1)
        return;

    CStreaming::RequestTxdModel(tex, (STREAMING_GAME_REQUIRED | STREAMING_KEEP_IN_MEMORY));
}

// 0x584BB0
void CRadar::RemoveMapSection(int32 x, int32 y)
{
    if (x < 0 || x > MAX_RADAR_WIDTH_TILES || y < 0 || y > MAX_RADAR_HEIGHT_TILES)
        return;

    int32 tex = GetRadarTexture(x, y);
    if (tex == -1)
        return;

    CStreaming::RemoveTxdModel(tex);
}

// 0x584BF0
void CRadar::RemoveRadarSections()
{
    rng::for_each(gRadarTextures, CStreaming::RemoveTxdModel);
}

// 0x584D40
bool IsPointInsideRadar(const CVector2D& point)
{
    return std::abs(point.x) < 1.0f
        && std::abs(point.y) < 1.0f;
}

// 0x584D90
void GetTextureCorners(int32 x, int32 y, CVector2D* corners)
{
    corners[0].x = 500.0f * (x - 6);
    corners[0].y = 500.0f * (5 - y);

    corners[1].x = 500.0f * (x - 5);
    corners[1].y = 500.0f * (5 - y);

    corners[2].x = 500.0f * (x - 5);
    corners[2].y = 500.0f * (6 - y);

    corners[3].x = 500.0f * (x - 6);
    corners[3].y = 500.0f * (6 - y);
}

// Returns number of intersections
// 0x584E00
int32 LineRadarBoxCollision(CVector2D& result, const CVector2D& lineStart, const CVector2D& lineEnd)
{
    return ((int32(__cdecl*)(CVector2D&, const CVector2D&, const CVector2D&))0x584E00)(result, lineStart, lineEnd);
}

// 0x585040
int32 CRadar::ClipRadarPoly(CVector2D* out, const CVector2D* in)
{
    return ((int32(__cdecl*)(CVector2D*, const CVector2D*))0x585040)(out, in);
}

// 0x5853D0
void CRadar::DrawAreaOnRadar(const CRect& rect, const CRGBA&  color, bool inMenu)
{
    ((void(__cdecl*)(const CRect&, const CRGBA&, bool))0x5853D0)(rect, color, inMenu);
}

// 0x585700
void CRadar::DrawRadarMask()
{
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
            in.x = corner.x * std::cos(j * (PI / 2.0f / 6.0f));
            in.y = corner.y * std::sin(j * (PI / 2.0f / 6.0f));
            TransformRadarPointToScreenSpace(out[j + 1], in);
        };

        CSprite2d::SetMaskVertices(std::size(out), (float*)out, CSprite2d::GetNearScreenZ());
        RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::GetVertices(), std::size(out));
    }

    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, RWRSTATE(rwALPHATESTFUNCTIONGREATER));
}

// 0x5858D0
void CRadar::StreamRadarSections(const CVector& worldPosn)
{
    auto x = (int32)std::floor((worldPosn.x + 3000.0f) / 500.0f); // todo: World constant
    auto y = (int32)std::ceil(11.0f - (worldPosn.y + 3000.0f) / 500.0f);

    if (CStreaming::ms_disableStreaming)
        return;

    StreamRadarSections(x, y);
}

// 0x584C50
void CRadar::StreamRadarSections(int32 x, int32 y)
{
    ((void(__cdecl*)(int32, int32))0x584C50)(x, y);
}

// 0x585960
void CRadar::InitFrontEndMap()
{
    CalculateCachedSinCos();
    std::ranges::fill(MapLegendList, 0);

    vec2DRadarOrigin.Set(0.0f, 0.0f);
    m_radarRange = 2990.0f;
    MapLegendCounter = 0;

    std::ranges::fill(ArrowBlipColour, CRGBA(0, 0, 0, 0));
}

// 0x5859F0
void CRadar::AddBlipToLegendList(uint8 arg0, int32 blipIndex)
{
    ((void(__cdecl*)(uint8, int32))0x5859F0)(arg0, blipIndex);
}

// 0x585B20
void CRadar::SetMapCentreToPlayerCoords()
{
    if (FindPlayerPed() == nullptr)
        return;

    FrontEndMenuManager.m_bDrawRadarOrMap = true;

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
    FrontEndMenuManager.m_bDrawRadarOrMap = false;
}

// 0x585BF0
void CRadar::Draw3dMarkers()
{
    ((void(__cdecl*)())0x585BF0)();
}

// unused
// 0x585FE0
void CRadar::SetRadarMarkerState(int32 counter, bool flag)
{
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

    if (auto* entity = GetEntity())
        entity->bHasBlip = flag;
    */
}

// 0x585FF0
void CRadar::DrawRadarSprite(uint16 spriteId, float x, float y, uint8 alpha)
{
    if (FrontEndMenuManager.m_bDrawRadarOrMap) {
        x *= SCREEN_WIDTH_UNIT;
        y *= SCREEN_HEIGHT_UNIT;

        LimitToMap(&x, &y);
    }

    float width = std::floor(SCREEN_WIDTH_UNIT * 8.f);   // uint32 width  = 8 * SCREEN_WIDTH_UNIT;  original math with warnings, NOTSA
    float height = std::floor(SCREEN_HEIGHT_UNIT * 8.f); // uint32 height = 8 * SCREEN_HEIGHT_UNIT;

    auto sprite16 = (uint16)spriteId;
    if (!DisplayThisBlip(sprite16, -99))
        return;

    CRect rt{
        x - width,
        y - height,
        x + width,
        y + height,
    };
    CRGBA white(255, 255, 255, alpha);
    RadarBlipSprites[sprite16].Draw(rt, white);
    AddBlipToLegendList(0, sprite16);
}

// 0x586110
void CRadar::DrawRadarSection(int32 x, int32 y)
{
    ((void(__cdecl*)(int32, int32))0x586110)(x, y);
}

// 0x586520
void CRadar::DrawRadarSectionMap(int32 x, int32 y, CRect rect)
{
    ((void(__cdecl*)(int32, int32, CRect))0x586520)(x, y, rect);
}

// 0x586650
void CRadar::DrawRadarGangOverlay(bool inMenu)
{
    ((void(__cdecl*)(bool))0x586650)(inMenu);
}

// 0x586880
void CRadar::DrawRadarMap()
{
    DrawRadarMask();

    auto x = (int32)std::floor((vec2DRadarOrigin.x + 3000.0f) / 500.0f);
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
    DrawRadarSection(x - 1,     y);
    DrawRadarSection(x,         y);
    DrawRadarSection(x + 1,     y);
    DrawRadarSection(x - 1,     y + 1);
    DrawRadarSection(x,         y + 1);
    DrawRadarSection(x + 1,     y + 1);

    DrawRadarGangOverlay(false);

    CVehicle* vehicle = FindPlayerVehicle();

    if (vehicle && vehicle->IsSubPlane() && vehicle->m_nModelIndex != MODEL_VORTEX) {
        CVector playerPos = FindPlayerCentreOfWorld_NoInteriorShift(0);

        float cSin = cachedSin;
        float cCos = cachedCos;
        cachedSin = SIN_PI;
        cachedCos = COS_PI;

        float angle = std::atan2(-vehicle->m_matrix->GetForward().z, vehicle->m_matrix->GetUp().z);
        CRect rt;
        rt.left   = playerPos.x - 1000.0f;
        rt.bottom    = playerPos.y - (2 * RadiansToDegrees(angle));
        rt.right  = playerPos.x + 1000.0f;
        rt.top = playerPos.y + 2000.0f;

        CRGBA color(20, 175, 20, 200); // light green with some transparency
        DrawAreaOnRadar(rt, color, false);
        cachedSin = cSin;
        cachedCos = cCos;
    }

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(FALSE));
}

// 0x586B00
void CRadar::DrawMap()
{
    CPlayerPed* player = FindPlayerPed();
    bool mapShouldDrawn = !CGame::currArea && player->m_nAreaCode == 0 && FrontEndMenuManager.m_nRadarMode != 1;

    CalculateCachedSinCos();

    CVehicle* vehicle = FindPlayerVehicle();
    CPlayerInfo* playerInfo = player->GetPlayerInfoForThisPlayerPed();
    if (!vehicle || playerInfo->IsPlayerInRemoteMode()) {
        if (CTheScripts::RadarZoomValue)
            m_radarRange = RADAR_MIN_RANGE - (float)CTheScripts::RadarZoomValue;
        else
            m_radarRange = RADAR_MIN_RANGE;

        goto DRAW_RADAR;
    }

    if (vehicle && vehicle->IsSubPlane() && !ModelIndices::IsVortex(vehicle->m_nModelIndex)) {
        float speedZ = vehicle->GetPosition().z / 200.0f;

        if (speedZ < RADAR_MIN_SPEED)
            m_radarRange = RADAR_MAX_RANGE - 10.0f;
        else if (speedZ < RADAR_MAX_SPEED)
            m_radarRange = (speedZ - RADAR_MIN_SPEED) / 60.0f + (RADAR_MAX_RANGE - 10.0f);
        else
            m_radarRange = RADAR_MAX_RANGE;
    }
    else {
        float speed = FindPlayerSpeed().Magnitude();

        if (speed < RADAR_MIN_SPEED)
            m_radarRange = RADAR_MIN_RANGE;
        else if (speed >= RADAR_MAX_SPEED)
            m_radarRange = RADAR_MAX_RANGE;
        else
            m_radarRange = (speed - RADAR_MIN_SPEED) * (850.0f / (RADAR_MIN_SPEED * 10.0f)) + RADAR_MIN_RANGE;
    }

DRAW_RADAR:
    if (!CGameLogic::IsCoopGameGoingOn()) {
        CVector playerPos = FindPlayerCentreOfWorld_NoInteriorShift(0);
        vec2DRadarOrigin.x = playerPos.x;
        vec2DRadarOrigin.y = playerPos.y;

        if (mapShouldDrawn)
            DrawRadarMap();

        return;
    }

    if (CGameLogic::n2PlayerPedInFocus == eFocusedPlayer::PLAYER2) {
        CVector playerPos = FindPlayerCentreOfWorld_NoInteriorShift(1);
        vec2DRadarOrigin.x = playerPos.x;
        vec2DRadarOrigin.y = playerPos.y;

        if (mapShouldDrawn)
            DrawRadarMap();

        return;
    }

    CVector pos0 = FindPlayerCentreOfWorld_NoInteriorShift(0);
    CVector pos1 = FindPlayerCentreOfWorld_NoInteriorShift(1);

    CVector2D posAvg = (pos0 + pos1) / 2.0f;

    vec2DRadarOrigin.x = posAvg.x;
    vec2DRadarOrigin.y = posAvg.y;

    if (mapShouldDrawn)
        DrawRadarMap();
}

// 0x586D60
void CRadar::DrawCoordBlip(int32 blipIndex, bool isSprite)
{
    ((void(__cdecl*)(int32, uint8))0x586D60)(blipIndex, isSprite);
}

// 0x587000
void CRadar::DrawEntityBlip(int32 blipIndex, uint8 arg1)
{
    ((void(__cdecl*)(int32, uint8))0x587000)(blipIndex, arg1);
}

// 0x587C10
void CRadar::ClearActualBlip(int32 blipIndex)
{
    if (blipIndex < 0 || blipIndex >= MAX_RADAR_TRACES)
        return;

    auto& trace = ms_RadarTrace[blipIndex];
    trace.m_nBlipSize = 1;
    trace.m_fSphereRadius = 1.0f;
    trace.m_pEntryExit = nullptr;
    trace.m_nBlipSprite = RADAR_SPRITE_NONE;

    trace.m_bBright = true;
    trace.m_bTrackingBlip = false;
    trace.m_bShortRange = false;
    trace.m_bFriendly = false;
    trace.m_bBlipRemain = false;
    trace.m_bBlipFade = false;

    trace.m_nCoordBlipAppearance = BLIP_FLAG_FRIEND;
    trace.m_nBlipDisplayFlag = BLIP_DISPLAY_NEITHER;
    trace.m_nBlipType = BLIP_NONE;
}

// 0x587C60
void CRadar::ClearBlipForEntity(eBlipType blipType, int32 entityHandle)
{
    for (auto i = 0u; i < ms_RadarTrace.size(); i++) {
        if (ms_RadarTrace[i].m_nBlipType != blipType || ms_RadarTrace[i].m_nEntityHandle != entityHandle)
            continue;

        ClearActualBlip(i);
    }
}

// 0x587CE0
void CRadar::ClearBlip(int32 blipIndex)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ClearActualBlip(index);
}

// 0x587D20
void CRadar::SetupAirstripBlips()
{
    ((void(__cdecl*)())0x587D20)();
}

// 0x588050
void CRadar::DrawBlips()
{
    ((void(__cdecl*)())0x588050)();
}

/*! Load radar blips from save file
 * @addr 0x5D53C0
 */
bool CRadar::Load()
{
    Initialise();

    for (auto i = 0u; i < ms_RadarTrace.size(); i++) {
        auto& trace = ms_RadarTrace[i];
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
bool CRadar::Save()
{
    return plugin::CallAndReturn<bool, 0x5D5860>();

    for (const auto& trace : ms_RadarTrace) {

    }

    return true;

}

int32 CRadar::FindTraceNotTrackingBlipIndex() {
    for (auto&& [i, v] : notsa::enumerate(ms_RadarTrace)) {
        if (!v.m_bTrackingBlip) {
            return (int32)i;
        }
    }
    return -1;
}
