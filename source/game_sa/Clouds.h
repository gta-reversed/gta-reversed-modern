/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"
#include <rwplcore.h>

constexpr auto MAX_MOVING_FOG = 350;
constexpr auto MAX_VOLUMETRIC_CLOUDS = 180;

constexpr auto SKYP_WIDTH_MULT = 1.4f;
constexpr auto SKYP_CAM_DIST = 30.f;

constexpr auto SKYP_ABOVE_HORIZON_Z = 0.5f;
constexpr auto SKYP_HORIZON_Z = 0.0f;
constexpr auto SKYP_SEA_HORIZON_Z = -0.1f;
constexpr auto SKYP_BELOW_HORIZON_Z = -0.3f;

struct tMovingFog {
    bool    m_bFogSlots[MAX_MOVING_FOG];
    CVector m_vecPosn[MAX_MOVING_FOG];
    float   m_fSize[MAX_MOVING_FOG];
    float   m_fIntensity[MAX_MOVING_FOG];
    float   m_fMaxIntensity[MAX_MOVING_FOG];
    CVector m_vecWind;
    float   m_fSpeed[MAX_MOVING_FOG];
    int     field_27B4[12];
    std::array<uint32, 6> m_nPrimIndices;
};

struct tVolumetricClouds {
    bool       m_bSlots[MAX_VOLUMETRIC_CLOUDS];
    bool       m_bInsideVisibilityRange[MAX_VOLUMETRIC_CLOUDS];
    CVector    field_168[MAX_VOLUMETRIC_CLOUDS];
    CVector    field_9D8[MAX_VOLUMETRIC_CLOUDS];
    int32      m_nHeight[MAX_VOLUMETRIC_CLOUDS];
    RwTexture* m_pTex;
    CVector    m_vecCloudsSpace[3];
    float      m_fCloudXCoords[18];
    float      m_fCloudYCoords[18];
    float      m_fCloudZCoords[18];
    float      m_fCloudUCoords[18];
    float      m_fCloudVCoords[18];
};

class CClouds {
public:
    static float& m_fVolumetricCloudDensity;        // default 1.0f
    static bool& m_bVolumetricCloudHeightSwitch;    // default true
    static float& m_fVolumetricCloudWindMoveFactor; // default 0.1f
    static float& m_fVolumetricCloudMaxDistance;
    static uint32& m_VolumetricCloudsUsedNum;
    static float& ms_cameraRoll;
    static int32& IndividualRotation;
    static float& CloudRotation;
    static tVolumetricClouds& ms_vc;
    static tMovingFog& ms_mf;
    static CVector& PlayerCoords;
    static CVector& CameraCoors;

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void Shutdown();

    static void SetUpOneSkyPoly(CVector vert1pos, CVector vert2pos, CVector vert3pos, CVector vert4pos, uint8 topRed, uint8 topGreen, uint8 topBlue, uint8 bottomRed, uint8 bottomGreen, uint8 bottomBlue);

    static void MovingFogInit();
    static void MovingFog_Create(CVector* posn);
    static void MovingFog_Delete(int32 fogSlotIndex);
    static void MovingFog_Update();
    static void MovingFogRender();
    static void Render_MaybeRenderMoon(float colorBalance);
    static void Render_MaybeRenderStars(float colorBalance);
    static float MovingFog_GetFXIntensity();
    static CVector MovingFog_GetWind();
    static int32 MovingFog_GetFirstFreeSlot();

    static void VolumetricCloudsInit();
    static void VolumetricClouds_Create(CVector* posn);
    static void VolumetricClouds_Delete(int32 vcSlotIndex);
    static float VolumetricCloudsGetMaxDistance();
    static int32 VolumetricClouds_GetFirstFreeSlot();
    static void VolumetricCloudsRender();

    static void Render();
    static void RenderSkyPolys();
    static void RenderBottomFromHeight();
};

extern uint8* RAINBOW_LINES_COLOR_RED;   // RAINBOW_LINES_COLOR_RED[6] =   { 30, 30, 30, 10,  0, 15 }
extern uint8* RAINBOW_LINES_COLOR_GREEN; // RAINBOW_LINES_COLOR_GREEN[6] = {  0, 15, 30, 30,  0,  0 }
extern uint8* RAINBOW_LINES_COLOR_BLUE;  // RAINBOW_LINES_COLOR_BLUE[6]  = {  0,  0,  0, 10, 30, 30 }
extern float* LOW_CLOUDS_X_COORDS;               // LOW_CLOUDS_X_COORDS[12] = { 1.0f, 0.7f, 0.0f, -0.7f, -1.0f, -0.7f, 0.0f, 0.7f, 0.8f, -0.8f, 0.4f, 0.4f }
extern float* LOW_CLOUDS_Y_COORDS;               // LOW_CLOUDS_Y_COORDS[12] = { 0.0f, -0.7f, -1.0f, -0.7f, 0.0f, 0.7f, 1.0f, 0.7f, 0.4f, 0.4f, -0.8f. -0.8f }
extern float* LOW_CLOUDS_Z_COORDS;               // LOW_CLOUDS_Z_COORDS[12] = { 0.0f, 1.0f, 0.5f, 0.0f, 1.0f, 0.3f, 0.9f, 0.4f, 1.3f, 1.4f, 1.2f, 1.7f }
extern float* STARS_Y_POSITIONS;                 // STARS_Y_POSITIONS[9] = { 0.0f, 0.05f, 0.13f, 0.4f, 0.7f, 0.6f, 0.27f, 0.55f, 0.75f }
extern float* STARS_Z_POSITIONS;                 // STARS_Z_POSITIONS[9] = { 0.0f, 0.45f, 0.9f, 1.0f, 0.85f, 0.52f, 0.48f, 0.35f, 0.2f }
extern float* STARS_SIZES;                       // STARS_SIZES[9] = { 1.0f, 1.4f, 0.9f, 1.0f, 0.6f, 1.5f, 1.3f, 1.0f, 0.8f }
extern float& CurrentFogIntensity;               // default 1.0f
extern RwTexture*& gpMoonMask;
extern RwTexture*& gpCloudTex;
extern RwTexture*& gpCloudMaskTex;
extern float& flt_C6E954;
extern float& flt_C6E970;

extern int32& dword_C6E974;
