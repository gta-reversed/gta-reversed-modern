#include "StdInc.h"

#include "TimecycEditor.h"

#include <imgui.h>
#include "Lines.h"
#include "PedPlacement.h"
#include "DebugModules/CTeleportDebugModule.h"

struct Color3 {
    float r, g, b;
};

struct Color4 : Color3 {
    float a;
};

uint8 ColorU8(float color) {
    return (uint8)(color * 255.0f);
}

float ColorF32(uint8 color) {
    return float(color) / 255.0f;
}

float ColorF32(float color) {
    return color / 255.0f;
}

namespace TimeCycleDebugModule {

constexpr const char* WEATHER_NAMES[] = {
    "EXTRASUNNY_LA",     "SUNNY_LA",           "EXTRASUNNY_SMOG_LA", "SUNNY_SMOG_LA",     "CLOUDY_LA",        "SUNNY_SF",         "EXTRASUNNY_SF",
    "CLOUDY_SF",         "RAINY_SF",           "FOGGY_SF",           "SUNNY_VEGAS",       "EXTRASUNNY_VEGAS", "CLOUDY_VEGAS",     "EXTRASUNNY_COUNTRYSIDE",
    "SUNNY_COUNTRYSIDE", "CLOUDY_COUNTRYSIDE", "RAINY_COUNTRYSIDE",  "EXTRASUNNY_DESERT", "SUNNY_DESERT",     "SANDSTORM_DESERT", "UNDERWATER",
    "EXTRACOLOURS_1",    "EXTRACOLOURS_2"
};

static int    OldWeatherTypeId;
static int    NewWeatherType;
static int    Hours;
static int    Minutes;
static Color3 CurrentRGB1;
static Color3 CurrentRGB2;
static Color3 AmbRGB;
static Color3 AmbObjRGB;
static Color3 SkyTopRGB;
static Color3 SkyBottomRGB;
static Color3 SunCoreRGB;
static Color3 SunCoronaRGB;
static int32  SunSize;
static Color4 BelowHorizonGrey;
static int32  SpriteSize;
static int32  SpriteBrightness;
static int32  ShadowStrength;
static int32  PoleShadowStrength;
static int32  LightShadowStrength;
static int32  FarClip;
static int32  FogStart;
static int32  LightsOnGroundBrightness;
static Color3 LowCloudsRGB;
static Color3 FluffyCloudsBottom;
static Color4 WaterRGBA;
static Color4 PostFx1RGBA;
static Color4 PostFx2RGBA;
static int32  CloudAlpha;
static int32  HighLightMinIntensity;
static int32  WaterFogAlpha;
static int32  DirectionalMult;
static Color3 BrightnessAddedToAmbient;

static int32 timeId = 0;
static int32 weatherId = 0;

static bool ShowBoxes = false;

void Sync() {
    weatherId                  = CWeather::OldWeatherType;

    OldWeatherTypeId           = CWeather::OldWeatherType;
    NewWeatherType             = CWeather::NewWeatherType;
    Hours                      = CClock::ms_nGameClockHours;
    Minutes                    = CClock::ms_nGameClockMinutes;
    CurrentRGB1.r              = ColorF32(CTimeCycle::m_fCurrentRGB1Red);
    CurrentRGB1.g              = ColorF32(CTimeCycle::m_fCurrentRGB1Green);
    CurrentRGB1.b              = ColorF32(CTimeCycle::m_fCurrentRGB1Blue);
    CurrentRGB2.r              = ColorF32(CTimeCycle::m_fCurrentRGB2Red);
    CurrentRGB2.g              = ColorF32(CTimeCycle::m_fCurrentRGB2Green);
    CurrentRGB2.b              = ColorF32(CTimeCycle::m_fCurrentRGB2Blue);
    AmbRGB.r                   = ColorF32(CTimeCycle::m_nAmbientRed[timeId][weatherId]);
    AmbRGB.g                   = ColorF32(CTimeCycle::m_nAmbientGreen[timeId][weatherId]);
    AmbRGB.b                   = ColorF32(CTimeCycle::m_nAmbientBlue[timeId][weatherId]);
    AmbObjRGB.r                = ColorF32(CTimeCycle::m_nAmbientRed_Obj[timeId][weatherId]);
    AmbObjRGB.g                = ColorF32(CTimeCycle::m_nAmbientGreen_Obj[timeId][weatherId]);
    AmbObjRGB.b                = ColorF32(CTimeCycle::m_nAmbientBlue_Obj[timeId][weatherId]);
    SkyTopRGB.r                = ColorF32(CTimeCycle::m_nSkyTopRed[timeId][weatherId]);
    SkyTopRGB.g                = ColorF32(CTimeCycle::m_nSkyTopGreen[timeId][weatherId]);
    SkyTopRGB.b                = ColorF32(CTimeCycle::m_nSkyTopBlue[timeId][weatherId]);
    SkyBottomRGB.r             = ColorF32(CTimeCycle::m_nSkyBottomRed[timeId][weatherId]);
    SkyBottomRGB.g             = ColorF32(CTimeCycle::m_nSkyBottomGreen[timeId][weatherId]);
    SkyBottomRGB.b             = ColorF32(CTimeCycle::m_nSkyBottomBlue[timeId][weatherId]);
    SunCoreRGB.r               = ColorF32(CTimeCycle::m_nSunCoreRed[timeId][weatherId]);
    SunCoreRGB.g               = ColorF32(CTimeCycle::m_nSunCoreGreen[timeId][weatherId]);
    SunCoreRGB.b               = ColorF32(CTimeCycle::m_nSunCoreBlue[timeId][weatherId]);
    SunCoronaRGB.r             = ColorF32(CTimeCycle::m_nSunCoronaRed[timeId][weatherId]);
    SunCoronaRGB.g             = ColorF32(CTimeCycle::m_nSunCoronaGreen[timeId][weatherId]);
    SunCoronaRGB.b             = ColorF32(CTimeCycle::m_nSunCoronaBlue[timeId][weatherId]);
    SunSize                    = CTimeCycle::m_fSunSize[timeId][weatherId];
    BelowHorizonGrey.r         = ColorF32(CTimeCycle::m_BelowHorizonGrey.red);
    BelowHorizonGrey.g         = ColorF32(CTimeCycle::m_BelowHorizonGrey.green);
    BelowHorizonGrey.b         = ColorF32(CTimeCycle::m_BelowHorizonGrey.blue);
    BelowHorizonGrey.a         = ColorF32(CTimeCycle::m_BelowHorizonGrey.alpha);
    SpriteSize                 = CTimeCycle::m_fSpriteSize[timeId][weatherId];
    SpriteBrightness           = CTimeCycle::m_fSpriteBrightness[timeId][weatherId];
    ShadowStrength             = CTimeCycle::m_nShadowStrength[timeId][weatherId];
    LightShadowStrength        = CTimeCycle::m_nLightShadowStrength[timeId][weatherId];
    PoleShadowStrength         = CTimeCycle::m_nPoleShadowStrength[timeId][weatherId];
    FarClip                    = CTimeCycle::m_fFarClip[timeId][weatherId];
    FogStart                   = CTimeCycle::m_fFogStart[timeId][weatherId];
    LightsOnGroundBrightness   = CTimeCycle::m_fLightsOnGroundBrightness[timeId][weatherId];
    LowCloudsRGB.r             = ColorF32(CTimeCycle::m_nLowCloudsRed[timeId][weatherId]);
    LowCloudsRGB.g             = ColorF32(CTimeCycle::m_nLowCloudsGreen[timeId][weatherId]);
    LowCloudsRGB.b             = ColorF32(CTimeCycle::m_nLowCloudsBlue[timeId][weatherId]);
    FluffyCloudsBottom.r       = ColorF32(CTimeCycle::m_nFluffyCloudsBottomRed[timeId][weatherId]);
    FluffyCloudsBottom.g       = ColorF32(CTimeCycle::m_nFluffyCloudsBottomGreen[timeId][weatherId]);
    FluffyCloudsBottom.b       = ColorF32(CTimeCycle::m_nFluffyCloudsBottomBlue[timeId][weatherId]);
    WaterRGBA.r                = ColorF32(CTimeCycle::m_fWaterRed[timeId][weatherId]);
    WaterRGBA.g                = ColorF32(CTimeCycle::m_fWaterGreen[timeId][weatherId]);
    WaterRGBA.b                = ColorF32(CTimeCycle::m_fWaterBlue[timeId][weatherId]);
    WaterRGBA.a                = ColorF32(CTimeCycle::m_fWaterAlpha[timeId][weatherId]);
    PostFx1RGBA.r              = ColorF32(CTimeCycle::m_fPostFx1Red[timeId][weatherId]);
    PostFx1RGBA.g              = ColorF32(CTimeCycle::m_fPostFx1Green[timeId][weatherId]);
    PostFx1RGBA.b              = ColorF32(CTimeCycle::m_fPostFx1Blue[timeId][weatherId]);
    PostFx1RGBA.a              = ColorF32(CTimeCycle::m_fPostFx1Alpha[timeId][weatherId]);
    PostFx2RGBA.r              = ColorF32(CTimeCycle::m_fPostFx2Red[timeId][weatherId]);
    PostFx2RGBA.g              = ColorF32(CTimeCycle::m_fPostFx2Green[timeId][weatherId]);
    PostFx2RGBA.b              = ColorF32(CTimeCycle::m_fPostFx2Blue[timeId][weatherId]);
    PostFx2RGBA.a              = ColorF32(CTimeCycle::m_fPostFx2Alpha[timeId][weatherId]);
    BrightnessAddedToAmbient.r = CTimeCycle::m_BrightnessAddedToAmbientRed;
    BrightnessAddedToAmbient.g = CTimeCycle::m_BrightnessAddedToAmbientGreen;
    BrightnessAddedToAmbient.b = CTimeCycle::m_BrightnessAddedToAmbientBlue;
    CloudAlpha                 = CTimeCycle::m_fCloudAlpha[timeId][weatherId];
    HighLightMinIntensity      = CTimeCycle::m_nHighLightMinIntensity[timeId][weatherId];
    WaterFogAlpha              = CTimeCycle::m_nWaterFogAlpha[timeId][weatherId];
    DirectionalMult            = CTimeCycle::m_nDirectionalMult[timeId][weatherId];
}

void DrawBoxesGui() {
    if (ImGui::BeginTable("Boxes", 7)) {
        ImGui::TableSetupColumn("Posistion");
        ImGui::TableSetupColumn("Far Clip");
        ImGui::TableSetupColumn("Lod Dis tMult");
        ImGui::TableSetupColumn("Extra Color");
        ImGui::TableSetupColumn("Strength");
        ImGui::TableSetupColumn("Fall Off");
        ImGui::TableSetupColumn("Teleport");
        ImGui::TableHeadersRow();

        const auto& playerPos = FindPlayerCoors();
        for (auto& box : CTimeCycle::GetBoxes()) {
            ImGui::PushID(&box);

            const auto& boxCenter = box.m_Box.GetCenter();

            ImGui::TableNextColumn();
            CZone* zone = CTheZones::FindSmallestZoneForPosition(boxCenter, false);
            ImGui::Text("%s", zone->GetTranslatedName());

            ImGui::TableNextColumn();
            ImGui::Text("%d", box.m_FarClip);

            ImGui::TableNextColumn();
            ImGui::Text("%d", box.m_LodDistMult);

            ImGui::TableNextColumn();
            ImGui::Text("%d", box.m_ExtraColor);

            ImGui::TableNextColumn();
            ImGui::Text("%f", box.m_Strength);

            ImGui::TableNextColumn();
            ImGui::Text("%f", box.m_Falloff);

            ImGui::TableNextColumn();
            bool selected = false;
            if (ImGui::Selectable("Teleport", &selected, ImGuiSelectableFlags_SpanAllColumns)) {
                TeleportDebugModule::TeleportTo(boxCenter);
                auto& pos = FindPlayerPed()->GetPosition();
                CPedPlacement::FindZCoorForPed(pos);
            }

            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}

void ProcessImGui() {
    Sync();

    ImGui::Checkbox("Stop Time", &CClock::gbFreezeTime);
    ImGui::SameLine();
    if (ImGui::Button("Save")) {
        CMessages::AddBigMessage("Saved", 3000, STYLE_MIDDLE);
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        CTimeCycle::Initialise();
    }
    ImGui::Checkbox("Extra Colour On", reinterpret_cast<bool*>(&CTimeCycle::m_bExtraColourOn));
    ImGui::Checkbox("Show boxes", &ShowBoxes);
    if (ShowBoxes) {
        DrawBoxesGui();
        ImGui::NewLine();
    }

    //if (ImGui::SliderInt("Selected Hour", &timeId, 0, CTimeCycle::NUM_HOURS)) {
    //    Hours = timeId * (24 / CTimeCycle::NUM_HOURS);
    //} else {
    //  timeId = Hours / (24 / CTimeCycle::NUM_HOURS);
    //}

    if (ImGui::Combo("Current Weather", &OldWeatherTypeId, WEATHER_NAMES, std::size(WEATHER_NAMES))) {
        CWeather::OldWeatherType = static_cast<eWeatherType>(OldWeatherTypeId);
    }
    if (ImGui::Combo("Next Weather", &NewWeatherType, WEATHER_NAMES, std::size(WEATHER_NAMES))) {
        CWeather::NewWeatherType = static_cast<eWeatherType>(NewWeatherType);
    }

    if (ImGui::SliderInt("Hours", &Hours, 0, 23, "%.0f")) {
        CClock::ms_nGameClockHours = static_cast<uint8>(Hours);
    }
    if (ImGui::SliderInt("Minutes", &Minutes, 0, 59, "%.0f")) {
        CClock::ms_nGameClockMinutes = static_cast<uint8>(Minutes);
    }

    timeId = Hours / (24 / CTimeCycle::NUM_HOURS);

    ImGui::NewLine();
    if (ImGui::ColorEdit3("Current RGB 1", (float*)&CurrentRGB1)) {
        CTimeCycle::m_fCurrentRGB1Red   = CurrentRGB1.r * 255.0f;
        CTimeCycle::m_fCurrentRGB1Green = CurrentRGB1.g * 255.0f;
        CTimeCycle::m_fCurrentRGB1Blue  = CurrentRGB1.b * 255.0f;
    }

    if (ImGui::ColorEdit3("Current RGB 2", (float*)&CurrentRGB2)) {
        CTimeCycle::m_fCurrentRGB2Red   = CurrentRGB2.r * 255.0f;
        CTimeCycle::m_fCurrentRGB2Green = CurrentRGB2.r * 255.0f;
        CTimeCycle::m_fCurrentRGB2Blue  = CurrentRGB2.r * 255.0f;
    }

    ImGui::NewLine();
    if (ImGui::ColorEdit3("Ambient", (float*)&AmbRGB)) {
        CTimeCycle::m_nAmbientRed[timeId][weatherId]   = ColorU8(AmbRGB.r);
        CTimeCycle::m_nAmbientGreen[timeId][weatherId] = ColorU8(AmbRGB.g);
        CTimeCycle::m_nAmbientBlue[timeId][weatherId]  = ColorU8(AmbRGB.b);
    }

    if (ImGui::ColorEdit3("Ambient Obj", (float*)&AmbObjRGB)) {
        CTimeCycle::m_nAmbientRed_Obj[timeId][weatherId]   = ColorU8(AmbObjRGB.r);
        CTimeCycle::m_nAmbientGreen_Obj[timeId][weatherId] = ColorU8(AmbObjRGB.g);
        CTimeCycle::m_nAmbientBlue_Obj[timeId][weatherId]  = ColorU8(AmbObjRGB.b);
    }

    ImGui::NewLine();
    if (ImGui::ColorEdit3("Sky Top", (float*)&SkyTopRGB)) {
        CTimeCycle::m_nSkyTopRed[timeId][weatherId]   = ColorU8(SkyTopRGB.r);
        CTimeCycle::m_nSkyTopGreen[timeId][weatherId] = ColorU8(SkyTopRGB.g);
        CTimeCycle::m_nSkyTopBlue[timeId][weatherId]  = ColorU8(SkyTopRGB.b);
    }

    if (ImGui::ColorEdit3("Sky Bottom", (float*)&SkyBottomRGB)) {
        CTimeCycle::m_nSkyBottomRed[timeId][weatherId]   = ColorU8(SkyBottomRGB.r);
        CTimeCycle::m_nSkyBottomGreen[timeId][weatherId] = ColorU8(SkyBottomRGB.g);
        CTimeCycle::m_nSkyBottomBlue[timeId][weatherId]  = ColorU8(SkyBottomRGB.b);
    }

    ImGui::NewLine();

    auto& vec = CTimeCycle::m_VectorToSun[0];
    ImGui::Text("Vector To Sun XYZ: %.3f %.3f %.3f", vec.x, vec.y, vec.z);

    if (ImGui::ColorEdit3("Sun Core", (float*)&SunCoreRGB)) {
        CTimeCycle::m_nSunCoreRed[timeId][weatherId]   = ColorU8(SunCoreRGB.r);
        CTimeCycle::m_nSunCoreGreen[timeId][weatherId] = ColorU8(SunCoreRGB.g);
        CTimeCycle::m_nSunCoreBlue[timeId][weatherId]  = ColorU8(SunCoreRGB.b);
    }

    if (ImGui::ColorEdit3("Sun Corona", (float*)&SunCoronaRGB)) {
        CTimeCycle::m_nSunCoronaRed[timeId][weatherId]   = ColorU8(SunCoronaRGB.r);
        CTimeCycle::m_nSunCoronaGreen[timeId][weatherId] = ColorU8(SunCoronaRGB.g);
        CTimeCycle::m_nSunCoronaBlue[timeId][weatherId]  = ColorU8(SunCoronaRGB.b);
    }

    if (ImGui::SliderInt("Sun Size", &SunSize, 0, 255)) {
        CTimeCycle::m_fSunSize[timeId][weatherId] = SunSize;
    }

    ImGui::SliderFloat("Light Direction To Sun X", &CTimeCycle::m_vecDirnLightToSun.x, 0, 255);
    ImGui::SliderFloat("Light Direction To Sun Y", &CTimeCycle::m_vecDirnLightToSun.z, 0, 255);
    ImGui::SliderFloat("Light Direction To Sun Z", &CTimeCycle::m_vecDirnLightToSun.y, 0, 255);

    if (ImGui::ColorEdit4("Below Horizon Grey", (float*)&BelowHorizonGrey)) {
        CTimeCycle::m_BelowHorizonGrey.red   = ColorU8(BelowHorizonGrey.r);
        CTimeCycle::m_BelowHorizonGrey.green = ColorU8(BelowHorizonGrey.g);
        CTimeCycle::m_BelowHorizonGrey.blue  = ColorU8(BelowHorizonGrey.b);
        CTimeCycle::m_BelowHorizonGrey.alpha = ColorU8(BelowHorizonGrey.a);
    }

    ImGui::NewLine();
    if (ImGui::SliderInt("Sprite Size", &SpriteSize, 0, 255)) {
        CTimeCycle::m_fSpriteSize[timeId][weatherId] = SpriteSize;
    }

    if (ImGui::SliderInt("Sprite Brightness", &SpriteBrightness, 1, 10)) {
        CTimeCycle::m_fSpriteBrightness[timeId][weatherId] = SpriteBrightness;
    }

    if (ImGui::SliderInt("Shadows Strength", &ShadowStrength, 0, 255)) {
        CTimeCycle::m_nShadowStrength[timeId][weatherId] = ShadowStrength;
    }

    if (ImGui::SliderInt("Light Shadows Strength", &LightShadowStrength, 0, 255)) {
        CTimeCycle::m_nLightShadowStrength[timeId][weatherId] = LightShadowStrength;
    }

    if (ImGui::SliderInt("Pole Shadows Strength", &PoleShadowStrength, 0, 255)) {
        CTimeCycle::m_nPoleShadowStrength[timeId][weatherId] = PoleShadowStrength;
    }

    if (ImGui::SliderInt("Light On Ground Brightness", &LightsOnGroundBrightness, 0, 255)) {
        CTimeCycle::m_fLightsOnGroundBrightness[timeId][weatherId] = LightsOnGroundBrightness;
    }

    if (ImGui::SliderInt("Far Clip", &FarClip, INT16_MIN, INT16_MAX)) {
        CTimeCycle::m_fFarClip[timeId][weatherId] = static_cast<uint16>(FarClip);
    }

    if (ImGui::SliderInt("Fog Start", &FogStart, INT16_MIN, INT16_MAX)) {
        CTimeCycle::m_fFogStart[timeId][weatherId] = static_cast<uint16>(FogStart);
    }

    ImGui::NewLine();
    if (ImGui::ColorEdit3("Low Clouds", (float*)&LowCloudsRGB)) {
        CTimeCycle::m_nLowCloudsRed[timeId][weatherId]   = ColorU8(LowCloudsRGB.r);
        CTimeCycle::m_nLowCloudsGreen[timeId][weatherId] = ColorU8(LowCloudsRGB.g);
        CTimeCycle::m_nLowCloudsBlue[timeId][weatherId]  = ColorU8(LowCloudsRGB.b);
    }

    if (ImGui::ColorEdit3("Fluffy Clouds", (float*)&FluffyCloudsBottom)) {
        CTimeCycle::m_nFluffyCloudsBottomRed[timeId][weatherId]   = ColorU8(FluffyCloudsBottom.r);
        CTimeCycle::m_nFluffyCloudsBottomGreen[timeId][weatherId] = ColorU8(FluffyCloudsBottom.g);
        CTimeCycle::m_nFluffyCloudsBottomBlue[timeId][weatherId]  = ColorU8(FluffyCloudsBottom.b);
    }

    if (ImGui::ColorEdit4("Water", (float*)&WaterRGBA)) {
        CTimeCycle::m_fWaterRed[timeId][weatherId]   = ColorU8(WaterRGBA.r);
        CTimeCycle::m_fWaterGreen[timeId][weatherId] = ColorU8(WaterRGBA.g);
        CTimeCycle::m_fWaterBlue[timeId][weatherId]  = ColorU8(WaterRGBA.b);
        CTimeCycle::m_fWaterAlpha[timeId][weatherId] = ColorU8(WaterRGBA.a);
    }

    if (ImGui::ColorEdit4("Post Fx 1", (float*)&PostFx1RGBA)) {
        CTimeCycle::m_fPostFx1Red[timeId][weatherId]   = ColorU8(PostFx1RGBA.r);
        CTimeCycle::m_fPostFx1Green[timeId][weatherId] = ColorU8(PostFx1RGBA.g);
        CTimeCycle::m_fPostFx1Blue[timeId][weatherId]  = ColorU8(PostFx1RGBA.b);
        CTimeCycle::m_fPostFx1Alpha[timeId][weatherId] = ColorU8(PostFx1RGBA.a);
    }

    if (ImGui::ColorEdit4("Post Fx 2", (float*)&PostFx2RGBA)) {
        CTimeCycle::m_fPostFx2Red[timeId][weatherId]   = ColorU8(PostFx2RGBA.r);
        CTimeCycle::m_fPostFx2Green[timeId][weatherId] = ColorU8(PostFx2RGBA.g);
        CTimeCycle::m_fPostFx2Blue[timeId][weatherId]  = ColorU8(PostFx2RGBA.b);
        CTimeCycle::m_fPostFx2Alpha[timeId][weatherId] = ColorU8(PostFx2RGBA.a);
    }

    if (ImGui::ColorEdit3("Brightness Added To Ambient", (float*)&BrightnessAddedToAmbient)) {
        CTimeCycle::m_BrightnessAddedToAmbientRed   = BrightnessAddedToAmbient.r;
        CTimeCycle::m_BrightnessAddedToAmbientGreen = BrightnessAddedToAmbient.g;
        CTimeCycle::m_BrightnessAddedToAmbientBlue  = BrightnessAddedToAmbient.b;
    }

    if (ImGui::SliderInt("Cloud Alpha", &CloudAlpha, 0, 255)) {
        CTimeCycle::m_fCloudAlpha[timeId][weatherId] = CloudAlpha;
    }

    if (ImGui::SliderInt("High Light Min Intensity", &HighLightMinIntensity, 0, 255)) {
        CTimeCycle::m_nHighLightMinIntensity[timeId][weatherId] = HighLightMinIntensity;
    }

    if (ImGui::SliderInt("Water Fog Alpha", &WaterFogAlpha, 0, 255)) {
        CTimeCycle::m_nWaterFogAlpha[timeId][weatherId] = WaterFogAlpha;
    }

    if (ImGui::SliderInt("Directional Mult", &DirectionalMult, 0, 255)) {
        CTimeCycle::m_nDirectionalMult[timeId][weatherId] = DirectionalMult;
    }

    ImGui::NewLine();
    ImGui::SliderInt("Current Stored Value", &CTimeCycle::m_CurrentStoredValue, 0, 16);
    ImGui::SliderFloat("Shadow Front X", &CTimeCycle::m_fShadowFrontX[0], 0.0f, 1.0f);
    ImGui::SliderFloat("Shadow Front Y", &CTimeCycle::m_fShadowFrontY[0], 0.0f, 1.0f);
    ImGui::SliderFloat("Shadow Side X", &CTimeCycle::m_fShadowSideX[0], 0.0f, 1.0f);
    ImGui::SliderFloat("Shadow Side Y", &CTimeCycle::m_fShadowSideY[0], 0.0f, 1.0f);
    ImGui::SliderFloat("Shadow Displacement X", &CTimeCycle::m_fShadowDisplacementX[0], 0.0f, 1.0f);
    ImGui::SliderFloat("Shadow Displacement Y", &CTimeCycle::m_fShadowDisplacementY[0], 0.0f, 1.0f);

    ImGui::NewLine();
    ImGui::SliderInt("Fog Reduction", &CTimeCycle::m_FogReduction, 0, 64);
    ImGui::SliderInt("Extra Colour", &CTimeCycle::m_ExtraColour, 0, 255);
    ImGui::SliderInt("Extra Colour Weather Type", &CTimeCycle::m_ExtraColourWeatherType, 0, 255);
    ImGui::SliderFloat("Extra Colour Inter", &CTimeCycle::m_ExtraColourInter, 0.0f, 1.0f);
}

void DrawBox(const CBox& box) {
    auto workVec = box.m_vecMin;
    CVector v11 = workVec;

    workVec.z = box.m_vecMax.z;
    CVector v23 = workVec;

    workVec = box.m_vecMin;
    workVec.x = box.m_vecMax.x;
    CVector v31 = workVec;

    workVec = box.m_vecMin;
    workVec.y = box.m_vecMax.y;
    CVector v42 = workVec;

    workVec = box.m_vecMin;
    workVec.y = box.m_vecMax.y;
    workVec.z = box.m_vecMax.z;
    CVector v51 = workVec;

    workVec = box.m_vecMin;
    workVec.x = box.m_vecMax.x;
    workVec.z = box.m_vecMax.z;
    CVector v62 = workVec;

    workVec = box.m_vecMin;
    workVec.x = box.m_vecMax.x;
    workVec.y = box.m_vecMax.y;
    CVector v71 = workVec;

    workVec = box.m_vecMax;
    CVector v81 = workVec;

    const auto boxColor = 0xFF0000FF;
    CLines::RenderLineWithClipping(v11, v23, boxColor, boxColor);
    CLines::RenderLineWithClipping(v11, v31, boxColor, boxColor);
    CLines::RenderLineWithClipping(v11, v42, boxColor, boxColor);
    CLines::RenderLineWithClipping(v51, v23, boxColor, boxColor);
    CLines::RenderLineWithClipping(v51, v81, boxColor, boxColor);
    CLines::RenderLineWithClipping(v51, v42, boxColor, boxColor);
    CLines::RenderLineWithClipping(v62, v23, boxColor, boxColor);
    CLines::RenderLineWithClipping(v62, v81, boxColor, boxColor);
    CLines::RenderLineWithClipping(v62, v31, boxColor, boxColor);
    CLines::RenderLineWithClipping(v71, v81, boxColor, boxColor);
    CLines::RenderLineWithClipping(v71, v31, boxColor, boxColor);
    CLines::RenderLineWithClipping(v71, v42, boxColor, boxColor);
}

void ProcessRender() {
    if (!ShowBoxes) {
        return;
    }

    for (auto& box : CTimeCycle::GetBoxes()) {
        DrawBox(box.m_Box);
    }
}

}
