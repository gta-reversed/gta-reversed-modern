#pragma once

#include "Game.h"

#define GAME_LIMIT_FPS 30
#define GAME_LEVEL_FILE "DATA//GTA.DAT"

static inline bool ForegroundApp = *(bool*)0x8D621C;

static inline RwRGBA& gColourTop    = *(RwRGBA*)0xB72CA0;
static inline RwRGBA& gColourBottom = *(RwRGBA*)0xB72CA4;
static inline float&  gHorZ = *(float*)0xB72C6C;

/**
 * Game scene information
 */
/*
struct CScene {
    RpWorld*  m_pRpWorld;
    RwCamera* m_pRwCamera;
};
static inline CScene& Scene = *(CScene*)0xC17038;
*/

extern RsEventStatus AppEventHandler(RsEvent nEvent, void* param);
extern bool AttachInputDevices();
extern bool PluginAttach();
extern bool Initialise3D(void* param);
extern void Terminate3D();

extern void DefinedState();
extern void DefinedState2d();
extern void DoFade();
extern void DoGameState();
extern bool DoGameRestart();
extern bool DoRWStuffStartOfFrame(int16 TopRed, int16 TopGreen, int16 TopBlue, int16 BottomRed, int16 BottomGreen, int16 BottomBlue, int16 Alpha);
extern bool DoRWStuffStartOfFrame_Horizon(int16 TopRed, int16 TopGreen, int16 TopBlue, int16 BottomRed, int16 BottomGreen, int16 BottomBlue, int16 Alpha);
extern void DoRWStuffEndOfFrame();
extern void FrontendIdle();
extern void GameInit();
extern void Idle(void* param);
extern void InitialiseGame();
extern uint32 MainGameFunc(void* param);
extern void RenderScene();
extern void RenderMenus();
extern void TheGame();
extern void GameInit();
extern bool WasForegroundAppLastFrame();
extern bool IsForegroundApp();
extern void CheckAniso();

/**
 * Camera
 */

extern RwCamera* CameraCreate(RwInt32 width, RwInt32 height, RwBool zBuffer);
extern void CameraDestroy(RwCamera* camera);
extern void CameraSize(RwCamera* camera, RwRect* rect, RwReal viewWindow, RwReal aspectRatio);

/**
 * Lights
 */

extern void LightsCreate(RpWorld* world);
extern void LightsDestroy(RpWorld* world);
extern void SetLightsWithTimeOfDayColour(RpWorld* world);
extern void ActivateDirectional();
extern void DeActivateDirectional();
extern void SetAmbientColours();
extern void SetAmbientColours(RwRGBAReal* ambientLightColor);
extern void SetAmbientAndDirectionalColours(float mult);
extern void SetLightColoursForPedsCarsAndObjects(float mult);
extern void SetFlashyColours(float mult);
extern void SetFlashyColours_Mild(float mult);

extern void LightsEnable(int32 arg0);
extern void LightsCreate(RpWorld* world);
extern void LightsDestroy(RpWorld* world);

extern void SetLightsWithTimeOfDayColour(RpWorld* world);

extern void WorldReplaceNormalLightsWithScorched(RpWorld* world, float lighting);
extern void WorldReplaceScorchedLightsWithNormal(RpWorld* world);

extern void AddAnExtraDirectionalLight(RpWorld* world, float x, float y, float z, float red, float green, float blue);
extern void RemoveExtraDirectionalLights(RpWorld* world);

extern void SetFlashyColours(float fMult);
extern void SetFlashyColours_Mild(float fMult);

extern void SetBrightMarkerColours(float lighting);

extern void SetAmbientAndDirectionalColours(float fMult);
extern void ReSetAmbientAndDirectionalColours();

extern void ActivateDirectional();
extern void DeActivateDirectional();

extern void SetAmbientColoursToIndicateRoadGroup(int32 idx);
extern void SetFullAmbient();
extern void SetAmbientColours();
extern void SetAmbientColours(RwRGBAReal* color);

extern void SetDirectionalColours(RwRGBAReal* color);
extern void SetLightColoursForPedsCarsAndObjects(float fMult);

extern void SetLightsForInfraredVisionHeatObjects();
extern void StoreAndSetLightsForInfraredVisionHeatObjects();
extern void RestoreLightsForInfraredVisionHeatObjects();
extern void SetLightsForInfraredVisionDefaultObjects();
extern void SetLightsForNightVision();

float GetDayNightBalance();

// 0x746870
void MessageLoop();
