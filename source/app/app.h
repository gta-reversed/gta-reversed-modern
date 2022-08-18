#pragma once

#include "Game.h"

static inline bool ForegroundApp = *(bool*)0x8D621C;

static inline RwRGBA& gColourTop    = *(RwRGBA*)0xB72CA0;
static inline RwRGBA& gColourBottom = *(RwRGBA*)0xB72CA4;
static inline float&  gHorZ = *(float*)0xB72C6C;

void AppInjectHooks();

extern RsEventStatus AppEventHandler(RsEvent nEvent, void* param);
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
extern void RenderEffects();
extern void Render2dStuff();
extern void RenderScene();
extern void RenderMenus();
extern void TheGame();
extern bool IsForegroundApp();
extern void CheckAniso();

/**
 * Camera
 */

extern RwCamera* CameraCreate(RwInt32 width, RwInt32 height, RwBool zBuffer);
extern void CameraDestroy(RwCamera* camera);
extern void CameraSize(RwCamera* camera, RwRect* rect, RwReal viewWindow, RwReal aspectRatio);

/**
* Input
*/
RsEventStatus HandleKeyDown(void* param);
RsEventStatus HandleKeyUp(void* param);
RsEventStatus KeyboardHandler(RsEvent event, void* param);
RsEventStatus HandlePadButtonDown(void* param);
RsEventStatus HandlePadButtonUp(void* param);
RsEventStatus PadHandler(RsEvent event, void* param);
bool AttachInputDevices();
