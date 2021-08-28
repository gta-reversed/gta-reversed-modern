/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CRadar.h"

float& CRadar::m_fRadarOrientation = *(float*)0xBA8310;
float& CRadar::m_radarRange = *(float*)0xBA8314;
unsigned short* CRadar::MapLegendList = (unsigned short*)0xBA8318;
unsigned short& CRadar::MapLegendCounter = *(unsigned short*)0xBA86B8;
CRGBA* CRadar::ArrowBlipColour = (CRGBA*)0xBA86D4;
tRadarTrace* CRadar::ms_RadarTrace = (tRadarTrace*)0xBA86F0;
CVector2D& CRadar::vec2DRadarOrigin = *(CVector2D*)0xBAA248;
CSprite2d* CRadar::RadarBlipSprites = (CSprite2d*)0xBAA250;
CRect& CRadar::m_radarRect = *(CRect*)0x8D0920; // {1000000.0f, -1000000.0f, -1000000.0f, 1000000.0f}
unsigned char& CRadar::airstrip_location = *(unsigned char*)0xBA8300;
int& CRadar::airstrip_blip = *(int*)0xBA8304;
float& CRadar::cachedCos = *(float*)0xBA8308;
float& CRadar::cachedSin = *(float*)0xBA830c;

/*
airstrip_info airstrip_table[4] = {
    {1750.0f, -2494.0f, 180.0f, 1000.0f},
    {-1373.0f, 120.0f, 315.0f, 1500.0f},
    {1478.0f, 1461.0f, 90.0f, 1200.0f},
    {175.0f, 2502.0f, 180.0f, 1000.0f}
};
*/
static airstrip_info* airstrip_table = (airstrip_info*)0x8D06E0;


// int gRadarTextures[MAX_RADAR_WIDTH_TILES][MAX_RADAR_HEIGHT_TILES];
static int* gRadarTextures = (int*)0xBA8478;

// name, maskName
// 0x8d0720
char* CRadar::RadarBlipFileNames[][2] = {
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
unsigned int& CRadar::legendTraceTimer = *(unsigned int*)0xBAA354;

unsigned int& CRadar::mapYouAreHereTimer = *(unsigned int*)0xBAA358;
bool& CRadar::mapYouAreHereDisplay = *(bool*)0x8D0930;

#define RADAR_MIN_RANGE (180.0f)
#define RADAR_MAX_RANGE (350.0f)
#define RADAR_MIN_SPEED (0.3f)
#define RADAR_MAX_SPEED (0.9f)

void CRadar::InjectHooks()
{
    ReversibleHooks::Install("CRadar", "LoadTextures", 0x5827D0, &CRadar::LoadTextures);
    ReversibleHooks::Install("CRadar", "DrawLegend", 0x5828A0, &CRadar::DrawLegend);
    ReversibleHooks::Install("CRadar", "LimitRadarPoint", 0x5832F0, &CRadar::LimitRadarPoint);
    ReversibleHooks::Install("CRadar", "Shutdown", 0x585940, &CRadar::Shutdown);
    ReversibleHooks::Install("CRadar", "SetMapCentreToPlayerCoords", 0x585B20, &CRadar::SetMapCentreToPlayerCoords);
    ReversibleHooks::Install("CRadar", "InitFrontEndMap", 0x585960, &CRadar::InitFrontEndMap);
    ReversibleHooks::Install("CRadar", "CalculateBlipAlpha", 0x583420, &CRadar::CalculateBlipAlpha);
    //ReversibleHooks::Install("CRadar", "TransformRadarPointToScreenSpace", 0x583480, &CRadar::TransformRadarPointToScreenSpace);
    ReversibleHooks::Install("CRadar", "TransformRealWorldPointToRadarSpace", 0x583530, &CRadar::TransformRealWorldPointToRadarSpace);
    ReversibleHooks::Install("CRadar", "CalculateCachedSinCos", 0x583670, &CRadar::CalculateCachedSinCos);
    ReversibleHooks::Install("CRadar", "SetBlipSprite", 0x583D70, &CRadar::SetBlipSprite); // OK
    ReversibleHooks::Install("CRadar", "SetBlipAlwaysDisplayInZoom", 0x583DB0, &CRadar::SetBlipAlwaysDisplayInZoom);
    ReversibleHooks::Install("CRadar", "DrawYouAreHereSprite", 0x584960, &CRadar::DrawYouAreHereSprite);
    ReversibleHooks::Install("CRadar", "ChangeBlipColour", 0x583AB0, &CRadar::ChangeBlipColour);
    ReversibleHooks::Install("CRadar", "ClearActualBlip", 0x587C10, &CRadar::ClearActualBlip);
    ReversibleHooks::Install("CRadar", "ClearBlip", 0x587CE0, &CRadar::ClearBlip);
    ReversibleHooks::Install("CRadar", "ClearBlipForEntity", 0x587C60, &CRadar::ClearBlipForEntity);
    ReversibleHooks::Install("CRadar", "RequestMapSection", 0x584B50, &CRadar::RequestMapSection);
    ReversibleHooks::Install("CRadar", "RemoveMapSection", 0x584BB0, &CRadar::RemoveMapSection);
    ReversibleHooks::Install("CRadar", "RemoveRadarSections", 0x584BF0, &CRadar::RemoveRadarSections);
    ReversibleHooks::Install("CRadar", "DrawRadarSprite", 0x585FF0, &CRadar::DrawRadarSprite); // OK
    ReversibleHooks::Install("CRadar", "DrawMap", 0x586B00, &CRadar::DrawMap);
    ReversibleHooks::Install("CRadar", "DrawRadarMap", 0x586880, &CRadar::DrawRadarMap);
    ReversibleHooks::Install("CRadar", "StreamRadarSections", 0x5858D0, static_cast<void(*)(CVector const&)>(&CRadar::StreamRadarSections));
    ReversibleHooks::Install("CRadar", "SetupRadarRect", 0x584A80, &CRadar::SetupRadarRect);
    ReversibleHooks::Install("CRadar", "GetActualBlipArrayIndex", 0x582870, &CRadar::GetActualBlipArrayIndex);
    ReversibleHooks::Install("CRadar", "LimitToMap", 0x583350, &CRadar::LimitToMap);
    ReversibleHooks::Install("CRadar", "DrawRotatingRadarSprite", 0x5835A0, &CRadar::DrawRotatingRadarSprite);
    ReversibleHooks::Install("CRadar", "SetBlipFriendly", 0x583EB0, &CRadar::SetBlipFriendly);
    ReversibleHooks::Install("CRadar", "ChangeBlipDisplay", 0x583D20, &CRadar::ChangeBlipDisplay);
    ReversibleHooks::Install("CRadar", "SetBlipEntryExit", 0x583F00, &CRadar::SetBlipEntryExit); // OK
    ReversibleHooks::Install("CRadar", "SetShortRangeCoordBlip", 0x583920, &CRadar::SetShortRangeCoordBlip);
    ReversibleHooks::Install("CRadar", "ChangeBlipScale", 0x583CC0, &CRadar::ChangeBlipScale);
    ReversibleHooks::Install("CRadar", "GetRadarTraceColour", 0x584770, &CRadar::GetRadarTraceColour);

    // unused
    ReversibleHooks::Install("CRadar", "GetNewUniqueBlipIndex", 0x582820, &CRadar::GetNewUniqueBlipIndex);
    ReversibleHooks::Install("CRadar", "TransformRadarPointToRealWorldSpace", 0x5835A0, &CRadar::TransformRadarPointToRealWorldSpace);

    ReversibleHooks::Install("", "IsPointInsideRadar", 0x584D40, &IsPointInsideRadar);
    ReversibleHooks::Install("", "GetTextureCorners", 0x584D90, &GetTextureCorners);
}

// 0x587FB0
void CRadar::Initialise()
{
    ((void(__cdecl*)())0x587FB0)();
    /*
    airstrip_blip = 0;
    airstrip_location = 0;

    for (int i = 0; i < 250; i++) {
        auto trace& = ms_RadarTrace[i];

        trace.m_fSphereRadius = 1.0f;
        trace.m_nBlipSize = 0;
        trace.m_pEntryExit = nullptr;
        trace.m_nCounter = 1;

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

    m_radarRange = 350.0f;

    char txdName[10];

    for (int i = 0; i < 144; i++) {
        sprintf(txdName, "radar%02d", i);
        gRadarTextures[i] = CTxdStore::FindTxdSlot(txdName);
    }
    */
}

// 0x585940
void CRadar::Shutdown()
{
    for (unsigned int i = 0; i < MAX_RADAR_SPRITES; i++) {
        RadarBlipSprites[i].Delete();
    }
    RemoveRadarSections();
}

// 0x5827D0
void CRadar::LoadTextures()
{
    CTxdStore::PushCurrentTxd();
    int slot = CTxdStore::FindTxdSlot("hud");
    CTxdStore::SetCurrentTxd(slot);

    for (auto i = 0; i < MAX_RADAR_SPRITES; i++)
        RadarBlipSprites[i].SetTexture(RadarBlipFileNames[i][0]);

    CTxdStore::PopCurrentTxd();
}

// unused
// 0x582820
int CRadar::GetNewUniqueBlipIndex(int blipIndex)
{
    return ((int(__cdecl*)(int))0x582820)(blipIndex);
}

// 0x582870
int CRadar::GetActualBlipArrayIndex(int blipIndex)
{
    if (blipIndex == -1)
        return -1;

    uint16_t traceIndex = (uint16_t)blipIndex;
    uint16_t counter = blipIndex >> 16;
    tRadarTrace& trace = ms_RadarTrace[traceIndex];
    if (counter != trace.m_nCounter || !trace.m_bTrackingBlip)
        return -1;

    return traceIndex;
}

// 0x5828A0
void CRadar::DrawLegend(int x, int y, eRadarSprite blipType)
{
    char* blipName;

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
    rt.top = (float)y;

    CFont::PrintString(SCREEN_WIDTH_UNIT * 20.0f + rt.left, SCREEN_HEIGHT_UNIT * 3.0f + rt.top, blipName);

    auto blipId = (int)blipType;

    if (blipId > -1) {
        // the blip is a sprite
        CRGBA color(255, 255, 255, 255);

        rt.right = rt.left + SCREEN_WIDTH_UNIT * 16.0f;
        rt.bottom = rt.top + SCREEN_WIDTH_UNIT * 16.0f;

        RadarBlipSprites[blipId].Draw(rt, color);

        return;
    }

    // arrow blips have negative type ids
    CRGBA arrowColor = ArrowBlipColour[-blipId];

    if (CTimer::m_snTimeInMillisecondsPauseMode - legendTraceTimer > 600) {
        legendTraceTimer = CTimer::m_snTimeInMillisecondsPauseMode;

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
        rt.top    = posY - SCREEN_HEIGHT_UNIT * 5.0f;
        rt.bottom = posY + SCREEN_HEIGHT_UNIT * 5.0f;
        rt.left   = posX - SCREEN_WIDTH_UNIT * 5.0f;
        rt.right  = posX + SCREEN_WIDTH_UNIT * 5.0f;

        CSprite2d::DrawRect(rt, black);

        rt.top    = posY - SCREEN_HEIGHT_UNIT * 4.0f;
        rt.bottom = posY + SCREEN_HEIGHT_UNIT * 4.0f;
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

    if (FrontEndMenuManager.drawRadarOrMap)
        return mag;

    if (mag > 1.0f)
        point.Normalise();

    return mag;
}

// 0x583350
void CRadar::LimitToMap(float* pX, float* pY)
{
    float zoom = (FrontEndMenuManager.field_78) ? FrontEndMenuManager.m_fMapZoom : 140.0f;

    float xMin = (FrontEndMenuManager.m_fMapBaseX - zoom) * SCREEN_WIDTH_UNIT;
    float xMax = (FrontEndMenuManager.m_fMapBaseX + zoom) * SCREEN_WIDTH_UNIT;
    *pX = clamp(*pX, xMin, xMax);

    float yMin = (FrontEndMenuManager.m_fMapBaseY - zoom) * SCREEN_HEIGHT_UNIT;
    float yMax = (FrontEndMenuManager.m_fMapBaseY + zoom) * SCREEN_HEIGHT_UNIT;
    *pY = clamp(*pY, yMin, yMax);
}

// 0x583420
unsigned char CRadar::CalculateBlipAlpha(float distance)
{
    if (FrontEndMenuManager.drawRadarOrMap)
        return 255;

    auto distAlpha = 255 - (int)(distance * 1.0f / 60.0f * 255.0f);

    return std::max(distAlpha, 70);
}

// 0x583480
void CRadar::TransformRadarPointToScreenSpace(CVector2D& out, const CVector2D& in)
{
    ((void(__cdecl*)(CVector2D&, CVector2D const&))0x583480)(out, in);
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
void CRadar::TransformRealWorldToTexCoordSpace(CVector2D& out, CVector2D const& in, int arg2, int arg3)
{
    out.x = in.x - ((500 * arg2) - 3000.0f);
    out.y = -(in.y - ((500 * (12 - arg3)) - 3000.0f));

    out.x *= 0.002f;
    out.y *= 0.002f;
}

// 0x583670
void CRadar::CalculateCachedSinCos()
{
    if (FrontEndMenuManager.drawRadarOrMap) {
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
        auto entityPosn = targetEntity->GetPosition();
        in = entityPosn - activeCam.m_vecSourceBeforeLookBehind;
    }

    float angle = atan2(-in.x, in.y);
    cachedSin = sin(angle);
    cachedCos = cos(angle);
    m_fRadarOrientation = angle;
}

// 0x583820
int CRadar::SetCoordBlip(eBlipType type, CVector posn, _IGNORED_ unsigned int color, eBlipDisplay blipDisplay, _IGNORED_ char* scriptName)
{
    return ((int(__cdecl*)(eBlipType, CVector, unsigned int, eBlipDisplay, char*))0x583820)(type, posn, color, blipDisplay, scriptName);
}

// 0x583920
int CRadar::SetShortRangeCoordBlip(eBlipType type, CVector posn, unsigned int color, eBlipDisplay blipDisplay, char* scriptName)
{
    int index = SetCoordBlip(type, posn, color, blipDisplay, scriptName);
    if (index == -1)
        return -1;

    auto actualIndex = GetActualBlipArrayIndex(index);
    ms_RadarTrace[actualIndex].m_bShortRange = true;
    return index;
}

// 0x5839A0
int CRadar::SetEntityBlip(eBlipType type, int entityHandle, unsigned int arg2, eBlipDisplay blipDisplay)
{
    return ((int(__cdecl*)(eBlipType, int, unsigned int, eBlipDisplay))0x5839A0)(type, entityHandle, arg2, blipDisplay);
}

// 0x583AB0
void CRadar::ChangeBlipColour(int blipIndex, unsigned int color)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_nColour = static_cast<eBlipColour>(color);
}

// 0x583AF0
bool CRadar::HasThisBlipBeenRevealed(int blipIndex)
{
    CVector blipPos = ms_RadarTrace[blipIndex].m_vPosition;

    if (!FrontEndMenuManager.drawRadarOrMap || !ms_RadarTrace[blipIndex].m_bShortRange
    || CTheZones::ZonesRevealed > 80 || CTheZones::GetCurrentZoneLockedOrUnlocked(blipPos.x, blipPos.y))
        return true;

    return false;
}

// 0x583B40
bool CRadar::DisplayThisBlip(int spriteId, char priority)
{
    return ((bool(__cdecl*)(int, signed))0x583B40)(spriteId, priority);
}

// unused
// 0x583C70
void CRadar::ChangeBlipBrightness(int blipIndex, int brightness)
{
    ((void(__cdecl*)(int, int))0x583C70)(blipIndex, brightness);
}

// 0x583CC0
void CRadar::ChangeBlipScale(int blipIndex, int size)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (FrontEndMenuManager.drawRadarOrMap)
        size = 1;

    ms_RadarTrace[index].m_nBlipSize = size;
}

// 0x583D20
void CRadar::ChangeBlipDisplay(int blipIndex, eBlipDisplay blipDisplay)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_nBlipDisplayFlag = blipDisplay;
}

// 0x583D70
void CRadar::SetBlipSprite(int blipIndex, int spriteId)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (ms_RadarTrace[index].m_bTrackingBlip)
        ms_RadarTrace[index].m_nBlipSprite = static_cast<eRadarSprite>(spriteId);
}

// 0x583DB0
void CRadar::SetBlipAlwaysDisplayInZoom(int blipIndex, unsigned char display)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (ms_RadarTrace[index].m_bTrackingBlip)
        ms_RadarTrace[index].m_bBlipRemain = display;
}

// 0x583E00
void CRadar::SetBlipFade(int blipIndex, unsigned char fade)
{
    // unused
    ((void(__cdecl*)(int, unsigned char))0x583E00)(blipIndex, fade);
}

// 0x583E50
void CRadar::SetCoordBlipAppearance(int blipIndex, unsigned char appearance)
{
    ((void(__cdecl*)(int, unsigned char))0x583E50)(blipIndex, appearance);
}

// 0x583EB0
void CRadar::SetBlipFriendly(int blipIndex, bool friendly)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    ms_RadarTrace[index].m_bFriendly = friendly;
}

// 0x583F00
void CRadar::SetBlipEntryExit(int blipIndex, CEntryExit* enex)
{
    auto index = GetActualBlipArrayIndex(blipIndex);
    if (index == -1)
        return;

    if (!ms_RadarTrace[index].m_bTrackingBlip)
        ms_RadarTrace[index].m_pEntryExit = enex;
}

// 0x583F40
void CRadar::ShowRadarTrace(float x, float y, unsigned int size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    // unused
    ((void(__cdecl*)(float, float, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char))0x583F40)(x, y, size, red, green, blue, alpha);
}

// 0x584070
void CRadar::ShowRadarTraceWithHeight(float x, float y, unsigned int size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, eRadarTraceHeight height)
{
    ((void(__cdecl*)(float, float, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char, eRadarTraceHeight))0x584070)(x, y, size, red, green, blue, alpha, height);
}

// show debug line at this position
// 0x584480
void CRadar::ShowRadarMarker(CVector posn, unsigned int color, float radius)
{
    ((void(__cdecl*)(CVector, unsigned int, float))0x584480)(posn, color, radius);
}

// 0x584770
unsigned int CRadar::GetRadarTraceColour(eBlipColour color, bool bright, bool friendly)
{
    switch (color)
    {
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
void CRadar::DrawRotatingRadarSprite(CSprite2d* sprite, float x, float y, float angle, unsigned int width, unsigned int height, const CRGBA& color)
{
    CVector2D verts[4];

    if (FrontEndMenuManager.drawRadarOrMap) {
        x *= SCREEN_WIDTH_UNIT;
        y *= SCREEN_HEIGHT_UNIT;

        LimitToMap(&x, &y);
    }

    for (int i = 0; i < 4; i++) {
        float theta = i * HALF_PI + (angle - PI / 4.0f);

        verts[i].x = std::sin(theta) * width + x;
        verts[i].y = std::cos(theta) * height + y;
    }

    sprite->Draw(verts[3].x, verts[3].y, verts[2].x, verts[2].y, verts[0].x, verts[0].y, verts[1].x, verts[1].y, color);
}

// 0x584960
void CRadar::DrawYouAreHereSprite(float x, float y)
{
    if ((CTimer::m_snTimeInMillisecondsPauseMode - mapYouAreHereTimer) > 700) {
        mapYouAreHereTimer = CTimer::m_snTimeInMillisecondsPauseMode;
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
            (unsigned int)(25.0f * SCREEN_WIDTH_UNIT),
            (unsigned int)(25.0f * SCREEN_HEIGHT_UNIT),
            white
            );
    }

    MapLegendCounter++;
    MapLegendList[MapLegendCounter] = RADAR_SPRITE_MAP_HERE;
}

// 0x584A80
void CRadar::SetupRadarRect(int x, int y)
{
    m_radarRect.left   = 500.0f * (x - 6) - 500.0f;
    m_radarRect.top    = 500.0f * (5 - y) - 500.0f;
    m_radarRect.right  = 500.0f * (x - 4);
    m_radarRect.bottom = 500.0f * (7 - y);
}

// unused
// 0x584B00
bool ClipRadarTileCoords(int& x, int& y)
{
    return ((bool(__cdecl*)(int&, int&))0x584B00)(x, y);
}

// 0x584B50
void CRadar::RequestMapSection(int x, int y)
{
    if (x < 0 || x > 11 || y < 0 || y > 11)
        return;

    int tex = gRadarTextures[x + 12 * y];
    if (tex == -1)
        return;

    CStreaming::RequestTxdModel(tex, (STREAMING_GAME_REQUIRED | STREAMING_KEEP_IN_MEMORY));
}

// 0x584BB0
void CRadar::RemoveMapSection(int x, int y)
{
    if (x < 0 || x > 11 || y < 0 || y > 11)
        return;

    int tex = gRadarTextures[x + 12 * y];
    if (tex == -1)
        return;

    CStreaming::RemoveTxdModel(tex);
}

// 0x584BF0
void CRadar::RemoveRadarSections()
{
    for (int i = 0; i < 12; i++) {
        CStreaming::RemoveTxdModel(gRadarTextures[i]);
    }
}

// 0x584D40
bool IsPointInsideRadar(const CVector2D& point)
{
    return std::abs(point.x) < 1.0f &&
    std::abs(point.y) < 1.0f;
}

// 0x584D90
void GetTextureCorners(int x, int y, CVector2D* corners)
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
int LineRadarBoxCollision(CVector2D& result, const CVector2D& lineStart, const CVector2D& lineEnd)
{
    return ((int(__cdecl*)(CVector2D&, CVector2D const&, CVector2D const&))0x584E00)(result, lineStart, lineEnd);
}

// 0x585040
int CRadar::ClipRadarPoly(CVector2D* out, const CVector2D* in)
{
    return ((int(__cdecl*)(CVector2D*, CVector2D const*))0x585040)(out, in);
}

// 0x5853D0
void CRadar::DrawAreaOnRadar(const CRect& rect, const CRGBA&  color, bool inMenu)
{
    ((void(__cdecl*)(CRect const&, CRGBA const&, bool))0x5853D0)(rect, color, inMenu);
}

// 0x585700
void CRadar::DrawRadarMask()
{
    ((void(__cdecl*)())0x585700)();
}

// 0x5858D0
void CRadar::StreamRadarSections(const CVector& worldPosn)
{
    auto x = (int)std::floor((worldPosn.x + 3000.0f) / 500.0f);
    auto y = (int)std::ceil(11.0f - (worldPosn.y + 3000.0f) / 500.0f);

    if (CStreaming::ms_disableStreaming)
        return;

    StreamRadarSections(x, y);
}

// 0x584C50
void CRadar::StreamRadarSections(int x, int y)
{
    ((void(__cdecl*)(int, int))0x584C50)(x, y);
}

// 0x585960
void CRadar::InitFrontEndMap()
{
    CalculateCachedSinCos();
    memset(MapLegendList, 0, 175 * 2);

    vec2DRadarOrigin.x = 0.0f;
    vec2DRadarOrigin.y = 0.0f;
    m_radarRange = 2990.0f;
    MapLegendCounter = 0;

    for (int i = 0; i < 6; i++) {
        ArrowBlipColour[i] = CRGBA(0, 0, 0, 0);
    }
}

// 0x5859F0
void CRadar::AddBlipToLegendList(unsigned char arg0, int blipIndex)
{
    ((void(__cdecl*)(unsigned char, int))0x5859F0)(arg0, blipIndex);
}

// 0x585B20
void CRadar::SetMapCentreToPlayerCoords()
{
    if (FindPlayerPed() == nullptr)
        return;

    FrontEndMenuManager.drawRadarOrMap = true;

    InitFrontEndMap();

    CVector2D posReal = FindPlayerCentreOfWorld_NoInteriorShift(0);

    if (CTheScripts::HideAllFrontEndMapBlips || CTheScripts::bPlayerIsOffTheMap)
        posReal.Set(0.0f, 0.0f);

    CVector2D posRadar;
    TransformRealWorldPointToRadarSpace(posRadar, posReal);
    LimitRadarPoint(posRadar);

    FrontEndMenuManager.m_vMousePos = posReal;
    FrontEndMenuManager.m_fMapBaseX = DEFAULT_SCREEN_WIDTH / 2.0f - FrontEndMenuManager.m_fMapZoom * posRadar.x;
    FrontEndMenuManager.drawRadarOrMap = 0;
    FrontEndMenuManager.m_fMapBaseY = DEFAULT_SCREEN_HEIGHT / 2.0f + FrontEndMenuManager.m_fMapZoom * posRadar.y;
}

// 0x585BF0
void CRadar::Draw3dMarkers()
{
    ((void(__cdecl*)())0x585BF0)();
}

// unused
// 0x585FE0
void CRadar::SetRadarMarkerState(int arg0, unsigned char arg1)
{
    // NOP
}

// 0x585FF0
void CRadar::DrawRadarSprite(unsigned short spriteId, float x, float y, unsigned char alpha)
{
    if (FrontEndMenuManager.drawRadarOrMap) {
        x *= SCREEN_WIDTH_UNIT;
        y *= SCREEN_HEIGHT_UNIT;

        LimitToMap(&x, &y);
    }

    float width = SCREEN_WIDTH_UNIT * 8.0f;
    float height = SCREEN_HEIGHT_UNIT * 8.0f;

    auto sprite16 = (unsigned short)spriteId;
    if (!DisplayThisBlip(sprite16, -99))
        return;

    CRect rt;
    rt.left = x - width;
    rt.top = y - height;
    rt.right = x + width;
    rt.bottom = y + height;

    CRGBA white(255, 255, 255, alpha);

    RadarBlipSprites[sprite16].Draw(rt, white);
    AddBlipToLegendList(0, sprite16);
}

// 0x586110
void CRadar::DrawRadarSection(int x, int y)
{
    ((void(__cdecl*)(int, int))0x586110)(x, y);
}

// 0x586520
void CRadar::DrawRadarSectionMap(int x, int y, CRect rect)
{
    ((void(__cdecl*)(int, int, CRect))0x586520)(x, y, rect);
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

    auto x = (int)std::floor((vec2DRadarOrigin.x + 3000.0f) / 500.0f);
    auto y = (int)std::ceil(11.0f - (vec2DRadarOrigin.y + 3000.0f) / 500.0f);

    SetupRadarRect(x, y);
    StreamRadarSections(x, y);

    RwRenderStateSet(rwRENDERSTATEFOGENABLE,          (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND,           (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,          (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,      (void*)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATESHADEMODE,          (void*)D3DSHADE_FLAT);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,        (void*)rwRENDERSTATETEXTURERASTER);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,       (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,  (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,     (void*)D3DTADDRESS_CLAMP);
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE, (void*)FALSE);

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

    CVehicle* vehicle = FindPlayerVehicle(-1, false);

    if (vehicle && vehicle->m_vehicleSubType == VEHICLE_PLANE && vehicle->m_nModelIndex != MODEL_VORTEX) {
        CVector playerPos = FindPlayerCentreOfWorld_NoInteriorShift(0);

        float cSin = cachedSin;
        float cCos = cachedCos;
        cachedSin = SIN_PI;
        cachedCos = COS_PI;

        float angle = std::atan2(-vehicle->m_matrix->GetForward().z, vehicle->m_matrix->GetUp().z);
        CRect rt;
        rt.left   = playerPos.x - 1000.0f;
        rt.top    = playerPos.y - (2 * RadiansToDegrees(angle));
        rt.right  = playerPos.x + 1000.0f;
        rt.bottom = playerPos.y + 2000.0f;

        CRGBA color(20, 175, 20, 200); // light green with some transparency
        DrawAreaOnRadar(rt, color, false);
        cachedSin = cSin;
        cachedCos = cCos;
    }

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
}

// 0x586B00
void CRadar::DrawMap()
{
    CPlayerPed* player = FindPlayerPed(-1);
    bool mapShouldDrawn = !CGame::currArea && player->m_nAreaCode == 0 && FrontEndMenuManager.m_nRadarMode != 1;

    CalculateCachedSinCos();

    CVehicle* vehicle = FindPlayerVehicle(-1, false);
    CPlayerInfo* playerInfo = player->GetPlayerInfoForThisPlayerPed();
    if (!vehicle || playerInfo->IsPlayerInRemoteMode()) {
        if (CTheScripts::RadarZoomValue)
            m_radarRange = RADAR_MIN_RANGE - (float)CTheScripts::RadarZoomValue;
        else
            m_radarRange = RADAR_MIN_RANGE;

        goto DRAW_RADAR;
    }

    if (vehicle && vehicle->IsPlane() && ModelIndices::IsVortex(vehicle->m_nModelIndex)) {
        float speedZ = vehicle->GetPosition().z * 1.0f / 200.0f;

        if (speedZ < RADAR_MIN_SPEED)
            m_radarRange = RADAR_MAX_RANGE - 10.0f;
        else if (speedZ < RADAR_MAX_SPEED)
            m_radarRange = (speedZ - RADAR_MIN_SPEED) * (1.0f / 60.0f) + (RADAR_MAX_RANGE - 10.0f);
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

    if (CGameLogic::n2PlayerPedInFocus == 1) {
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
void CRadar::DrawCoordBlip(int blipIndex, bool isSprite)
{
    ((void(__cdecl*)(int, unsigned char))0x586D60)(blipIndex, isSprite);
}

// 0x587000
void CRadar::DrawEntityBlip(int blipIndex, unsigned char arg1)
{
    ((void(__cdecl*)(int, unsigned char))0x587000)(blipIndex, arg1);
}

// 0x587C10
void CRadar::ClearActualBlip(int blipIndex)
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
void CRadar::ClearBlipForEntity(eBlipType blipType, int entityHandle)
{
    for (int i = 0; i < MAX_RADAR_TRACES; i++) {
        auto& trace = ms_RadarTrace[i];

        if (trace.m_nBlipType == blipType && trace.m_nEntityHandle == entityHandle) {
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
    }
}

// 0x587CE0
void CRadar::ClearBlip(int blipIndex)
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

// Load radar blips from save file
void CRadar::Load()
{
    ((void(__cdecl*)())0x5D53C0)();
}

// Save radar blips to save file
void CRadar::Save()
{
    ((void(__cdecl*)())0x5D5860)();
}
