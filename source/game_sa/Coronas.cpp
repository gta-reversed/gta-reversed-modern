#include "StdInc.h"

#include "Coronas.h"



float& CCoronas::SunScreenX = *(float*)0xC3E028;
float& CCoronas::SunScreenY = *(float*)0xC3E02C;
//bool& CCoronas::SunBlockedByClouds = *(bool*)0x0;
bool& CCoronas::bChangeBrightnessImmediately = *(bool*)0xC3E034;
uint32& CCoronas::NumCoronas = *(uint32*)0xC3E038;
float& CCoronas::LightsMult = *(float*)0x8D4B5C; // 1.0f
uint32& CCoronas::MoonSize = *(uint32*)0x8D4B60; // 3
RwTexture* (&gpCoronaTexture)[CORONA_TEXTURES_COUNT] = *(RwTexture*(*)[CORONA_TEXTURES_COUNT])0xC3E000;
CRegisteredCorona(&CCoronas::aCoronas)[MAX_NUM_CORONAS] = *(CRegisteredCorona(*)[MAX_NUM_CORONAS])0xC3E058;

uint16(&CCoronas::ms_aEntityLightsOffsets)[8] = *(uint16(*)[8])0x8D5028;

auto& aCoronastar = StaticRef<std::array<char[26], 10>, 0x8D4950>();
auto& coronaTexturesAlphaMasks = StaticRef<std::array<char[26], 10>, 0x8D4A58>();

struct CFlareDefinition
{
    float Position;
    float Size;
    FixedVector<int16, 65535.f> ColorMult;
    FixedFloat<int16, 256.f> IntensityMult;
    int16 Sprite;
};
auto& HeadLightsFlareDef = StaticRef<std::array<CFlareDefinition, 27>, 0x8D4D88>();
auto& SunFlareDef = StaticRef<std::array<CFlareDefinition, 27>, 0x8D4B68>();


void CCoronas::InjectHooks() {
    RH_ScopedClass(CCoronas);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x6FAA70);
    RH_ScopedInstall(Shutdown, 0x6FAB00);
    RH_ScopedInstall(Update, 0x6FADF0, { .reversed = false });
    RH_ScopedInstall(Render, 0x6FAEC0);
    RH_ScopedInstall(RenderReflections, 0x6FB630);
    RH_ScopedInstall(RenderSunReflection, 0x6FBAA0, { .reversed = false });
    RH_ScopedOverloadedInstall(RegisterCorona, "type", 0x6FC180, void(*)(uint32, CEntity*, uint8, uint8, uint8, uint8, const CVector&, float, float, RwTexture*, eCoronaFlareType, bool, bool, int32, float, bool, float, uint8, float, bool, bool reflectionDelay), { .reversed = false });
    RH_ScopedOverloadedInstall(RegisterCorona, "texture", 0x6FC580, void(*)(uint32, CEntity*, uint8, uint8, uint8, uint8, const CVector&, float, float, eCoronaType, eCoronaFlareType, bool, bool, int32, float, bool, float, uint8, float, bool, bool reflectionDelay), { .reversed = false });
     
    RH_ScopedInstall(UpdateCoronaCoors, 0x6FC4D0, { .reversed = false });
    RH_ScopedInstall(DoSunAndMoon, 0x6FC5A0, { .reversed = false });
}

// Initialises coronas
// 0x6FAA70
void CCoronas::Init() {
    {
        CTxdStore::ScopedTXDSlot txd{"particle"};
        //for (auto&& [tex, name, maskName] : rng::zip_view{ gpCoronaTexture, aCoronastar, coronaTexturesAlphaMasks }) { // TODO: C++23
        //    if (!tex) { 
        //        tex = RwTextureRead(name, maskName);
        //    }
        //}
        for (auto i = 0; i < CORONA_TEXTURES_COUNT; i++) {
            auto& tex = gpCoronaTexture[i];
            if (!tex) {
                tex = RwTextureRead(aCoronastar[i], coronaTexturesAlphaMasks[i]);
            }
        }
    }
    rng::fill(aCoronas, CRegisteredCorona{});
}

// Terminates coronas
// 0x6FAB00
void CCoronas::Shutdown() {
    rng::for_each(gpCoronaTexture, RwTextureDestroy);
}

// Updates coronas
// 0x6FADF0
void CCoronas::Update() {
    plugin::Call<0x6FADF0>();

    /**
    * NOTE: Unfinished and untested
    ***
    
    LightsMult = std::min(CTimer::GetTimeStep() * 0.03f * LightsMult, 1.f);

    struct CamLook {
        bool unused : 4{}, left : 1{}, right : 1{}, behind : 1{}, forward : 1{}; // Have to initialize the msb 4 bits too, otherwise it wont compare equal to the original code's value
    } &LastCamLook = StaticRef<CamLook, 0xC3EF58>(); // NOTE/TODO: I'm not sure if foward is really forward

    const auto c = TheCamera.GetActiveCam();
    const CamLook currLook{
        .left = c.m_bLookingLeft,
        .right = c.m_bLookingRight,
        .behind = c.m_bLookingBehind,
        .forward = TheCamera.GetLookDirection() != 0,
    };

    if (currLook == LastCamLook) {

    }
    */
}

// Renders coronas
// 0x6FAEC0
void CCoronas::Render() {
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDONE));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDONE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(TRUE));

    const auto raster     = RwCameraGetRaster(Scene.m_pRwCamera);
    const auto rasterSize = CVector2D{ (float)RwRasterGetWidth(raster), (float)RwRasterGetHeight(raster) };
    const auto rasterRect = CRect{
        0.f,          0.f,
        rasterSize.x, rasterSize.y
    };

    bool zTestEnable = true;
    for (auto& c : aCoronas) {
        if (!c.m_dwId) {
            continue;
        }

        if (!c.m_FadedIntensity && !c.m_Color.a) {
            continue;
        }

        const auto covidPos = c.GetPosition();

        //< 0x6FB009 - Get on-screen position, and check if it's on it
        CVector   onScrPos;
        CVector2D onScrSize;
        if (c.m_bOffScreen = !CSprite::CalcScreenCoors(covidPos, &onScrPos, &onScrSize.x, &onScrSize.y, true, true)) {
            continue;
        }

        c.m_bOffScreen = !rasterRect.IsPointInside(CVector2D{ onScrPos }); // Seems like a useless check

        // Already faded out
        if (c.m_FadedIntensity == 0) {
            continue;
        }

        // If outside farclip range, just ignore
        if (onScrPos.z >= c.m_fFarClip) {
            continue;
        }

        const auto rz = 1.f / onScrPos.z;

        //< 0x6FB0A7 - Start fading out at half the far clip distance
        const auto intensity = (int16)((float)c.m_FadedIntensity * c.CalculateIntensity(onScrPos.z, c.m_fFarClip));

        //< 0x6FB0D9 - Enable/disable Z test if necessary
        if (c.m_bCheckObstacles == zTestEnable) {
            zTestEnable = !zTestEnable;
            RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(zTestEnable));
        }

        const auto LerpColorC = [](uint8 cc, float t) {
            return (uint8)((float)cc * t);
        };

        //< 0x6FB131 - Render with texture
        if (c.m_pTexture) {
            RwRenderStateSet(rwRENDERSTATEZTESTENABLE,   RWRSTATE(TRUE));
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(RwTextureGetRaster(c.m_pTexture)));

            //< 0x6FB122
            const auto scale = std::min(40.f, onScrPos.z) * CWeather::Foggyness / 40.f + 1.f;

            // NOP - The coordinates are later overwritten
            //if (c.m_dwId == 1) {
            //    scrPos.z = RwCameraGetFarClipPlane(Scene.m_pRwCamera) * 0.95f;
            //}

            //< 0x6FB24E
            if (CSprite::CalcScreenCoors(
                covidPos - (covidPos - TheCamera.GetPosition()).Normalized() * c.m_fNearClip,
                &onScrPos, // NOTE/BUG: Yeah, overwrites the previously calculated value. Not sure if it's intentional.
                &onScrSize.x, &onScrSize.y,
                true,
                true
            )) {
                CSprite::RenderOneXLUSprite_Rotate_Aspect(
                    onScrPos,
                    onScrSize * c.m_fSize * CVector2D{1.f, scale},
                    LerpColorC(c.m_Color.r, 1.f / scale),
                    LerpColorC(c.m_Color.g, 1.f / scale),
                    LerpColorC(c.m_Color.b, 1.f / scale),
                    intensity,
                    rz * 20.f,
                    0.f,
                    255
                );
            }
        }

        //< 0x6FB2F3 - Render flare
        if (c.m_nFlareType != FLARETYPE_NONE) {
            RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(FALSE));
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(RwTextureGetRaster(gpCoronaTexture[0])));

            const auto pFlareDefArray = [&] {
                switch (c.m_nFlareType) {
                case FLARETYPE_SUN:        return &SunFlareDef[0];
                case FLARETYPE_HEADLIGHTS: return &HeadLightsFlareDef[0];
                default:                   NOTSA_UNREACHABLE();
                }
            }();

            //< 0x6FB35B
            const auto colorVariationMult = CGeneral::GetRandomNumberInRange(0.7f, 1.f) * (float)c.m_FadedIntensity; 

            //< 0x6FB46C
            for (auto it = pFlareDefArray; it->Sprite; it++) {
                CEntity* hitEntity;
                CColPoint hitCP;
                if (!CWorld::ProcessLineOfSight(
                    covidPos,
                    TheCamera.GetPosition(),
                    hitCP,
                    hitEntity,
                    false,
                    true,
                    true,
                    false,
                    false,
                    false,
                    false,
                    true
                )) { //< 0x6FB409
                    auto color = c.m_Color * colorVariationMult;
                    color.a = 255;
                    CSprite::RenderBufferedOneXLUSprite2D(
                        lerp(rasterSize / 2.f, CVector2D{ onScrPos }, it->Position),
                        CVector2D{ it->Size, it->Size } * 4.f,
                        color,
                        255,
                        255
                    );
                }
            }

            RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(TRUE));

            //< 0x6FB483
            if (c.m_nFlareType == FLARETYPE_HEADLIGHTS && CWeather::HeadLightsSpectrum != 0.f && CGame::CanSeeOutSideFromCurrArea()) {
                for (auto it = HeadLightsFlareDef.begin(); it->Sprite; it++) {
                    const auto RenderFlareSprite = [
                        &,
                        spriteIntensity = (int16)((float)intensity * it->IntensityMult)
                    ](RwRGBA clr, float posOffset) {
                        CSprite::RenderBufferedOneXLUSprite2D(
                            lerp(rasterSize / 2.f, CVector2D{ onScrPos }, it->Position + posOffset),
                            CVector2D{ it->Size, it->Size },
                            clr,
                            spriteIntensity,
                            255
                        );
                    };
                    RenderFlareSprite({ LerpColorC(c.m_Color.r, it->ColorMult.x * CWeather::HeadLightsSpectrum), 0, 0, 255 }, +0.05f); // 0x6FB561
                    RenderFlareSprite({ 0, 0, LerpColorC(c.m_Color.b, it->ColorMult.z * CWeather::HeadLightsSpectrum), 255 }, -0.05f); // 0x6FB5EA
                }
            }
        }
    }
    CSprite::FlushSpriteBuffer();

    /* NOTE/BUG: Renderstates not restored? */
}

// Renders coronas reflections on a wet ground
// 0x6FB630
void CCoronas::RenderReflections() {
    if (s_DebugSettings.DisableWetRoadReflections) {
        return;
    }

    if (!s_DebugSettings.AlwaysRenderWetRoadReflections) {
        // Check if the roads are wet enough
        if (CWeather::WetRoads <= 0.f) {
            for (auto& c : aCoronas) {
                c.m_bHasValidHeightAboveGround = false;
            }
            return;
        }
    }

    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDONE));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDONE));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(RwTextureGetRaster(gpCoronaTexture[3])));

    const auto camPos = TheCamera.GetPosition();
    for (auto&& [i, c] : notsa::enumerate(aCoronas)) {
        const auto covidPos = c.GetPosition();
        if (!c.m_bHasValidHeightAboveGround || ((i & 0xFF) + (CTimer::GetFrameCounter() & 0xFF) % 16) == 0) { //< Simplified code
            bool bGroundFound;
            const auto groundZ = CWorld::FindGroundZFor3DCoord(covidPos, &bGroundFound);
            if (bGroundFound) { // NOTE/BUG: Weird.. Why not set it according to `bGroundFound` directly?
                c.m_bHasValidHeightAboveGround = true;
                c.m_fHeightAboveGround         = covidPos.z - groundZ;
            }
        }
        if (!c.m_bHasValidHeightAboveGround) {
            continue;
        }
        if (c.m_bHasValidHeightAboveGround >= 20.f) {
            continue;
        }
        if (covidPos.z - c.m_fHeightAboveGround >= camPos.z) {
            continue;
        }
        CVector   onScrPos;
        CVector2D onScrSize;
        if (!CSprite::CalcScreenCoors(covidPos - CVector{0.f, 0.f, 2 * c.m_fHeightAboveGround }, & onScrPos, & onScrSize.x, & onScrSize.y, true, true)) {
            continue;
        }
        const auto clampedFarClip = std::min(55.f, c.m_fFarClip * 0.75f);
        if (onScrPos.z >= clampedFarClip) {
            continue;
        }
        const auto LerpColorC = [
            t =   (s_DebugSettings.AlwaysRenderWetRoadReflections ? 1.f : CWeather::WetRoads)
                * c.CalculateIntensity(onScrPos.z, clampedFarClip)
                * invLerp(20.f, 0.f, c.m_fHeightAboveGround)
                * 230.f
        ](uint8 cc) {
            return (uint8)((uint16)((float)cc * t) >> 8 & 0xFF); // divide by 256
        };
        CSprite::RenderBufferedOneXLUSprite(
            { onScrPos.x, onScrPos.y, notsa::IsFixBugs() ? RwIm2DGetFarScreenZMacro() : RwIm2DGetNearScreenZMacro() },
            onScrSize * CVector2D{0.75f, 2.f} * c.m_fSize,
            LerpColorC(c.m_Color.r),
            LerpColorC(c.m_Color.g),
            LerpColorC(c.m_Color.b),
            128,
            1.f / RwCameraGetNearClipPlane(Scene.m_pRwCamera),
            255
        );
    }
    CSprite::FlushSpriteBuffer();

    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(TRUE));
}

// Renders sun reflection on water
// 0x6FBAA0
void CCoronas::RenderSunReflection() {
    plugin::Call<0x6FBAA0>();
}

// Creates corona by texture
// 0x6FC180
void CCoronas::RegisterCorona(uint32 id, CEntity* attachTo, uint8 red, uint8 green, uint8 blue, uint8 alpha, const CVector& posn, float radius, float farClip, RwTexture* texture, eCoronaFlareType flareType, bool enableReflection, bool checkObstacles, int32 _param_not_used, float angle, bool longDistance, float nearClip, uint8 fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay) {
    plugin::Call<0x6FC180, uint32, CEntity*, uint8, uint8, uint8, uint8, const CVector&, float, float, RwTexture*, eCoronaFlareType, bool, bool, int32, float, bool, float, uint8, float, bool, bool>(id, attachTo, red, green, blue, alpha, posn, radius, farClip, texture, flareType, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

// Creates corona by type
// 0x6FC580
void CCoronas::RegisterCorona(uint32 id, CEntity* attachTo, uint8 red, uint8 green, uint8 blue, uint8 alpha, const CVector& posn, float radius, float farClip, eCoronaType coronaType, eCoronaFlareType flareType, bool enableReflection, bool checkObstacles, int32 _param_not_used, float angle, bool longDistance, float nearClip, uint8 fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay) {
    plugin::Call<0x6FC580, uint32, CEntity*, uint8, uint8, uint8, uint8, const CVector&, float, float, eCoronaType, eCoronaFlareType, bool, bool, int32, float, bool, float, uint8, float, bool, bool>(id, attachTo, red, green, blue, alpha, posn, radius, farClip, coronaType, flareType, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

// 0x6FC4D0
void CCoronas::UpdateCoronaCoors(uint32 id, const CVector& posn, float farClip, float angle) {
    plugin::Call<0x6FC4D0, uint32, const CVector&, float, float>(id, posn, farClip, angle);
}

// Draw sun (Moon went to CClouds since SA)
// 0x6FC5A0
void CCoronas::DoSunAndMoon() {
    plugin::Call<0x6FC5A0>();
}
