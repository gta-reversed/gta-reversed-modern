/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "Garages.h"
#include "common.h"
#include "GxtChar.h"
#include "CDebugMenu.h"
#include "CarCtrl.h"
#include "UserDisplay.h"
#include "PostEffects.h"
#include "SpecialFX.h"

#include "Hud.h"
#include "app.h"

void InjectCommonHooks() {
    RH_ScopedNamespaceName("Common");
    RH_ScopedCategory("Common");

    RH_ScopedGlobalInstall(MakeUpperCase, 0x7186E0);
    RH_ScopedGlobalInstall(AsciiToGxtChar, 0x718600);
    RH_ScopedGlobalInstall(WriteRaster, 0x005A4150);
    RH_ScopedGlobalOverloadedInstall(CalcScreenCoors, "VVff", 0x71DA00, bool(*)(const CVector&, CVector*, float*, float*), { .reversed = false });
    RH_ScopedGlobalOverloadedInstall(CalcScreenCoors, "VV", 0x71DAB0, bool(*)(const CVector&, CVector*), { .reversed = false });
    RH_ScopedGlobalInstall(LittleTest, 0x541330);
}

// WINDOWS
void MessageLoop() {
    tagMSG msg;
    while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE | PM_NOYIELD)) {
        if (msg.message == WM_QUIT) {
            RsGlobal.quit = true;
        } else {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }
}

// 0x54ECE0
void TransformPoint(RwV3d& point, const CSimpleTransform& placement, const RwV3d& vecPos) {
    plugin::Call<0x54ECE0, RwV3d&, const CSimpleTransform&, const RwV3d&>(point, placement, vecPos);
}

// 0x54EEA0
void TransformVectors(RwV3d* vecsOut, int32 numVectors, const CMatrix& matrix, const RwV3d* vecsin) {
    plugin::Call<0x54EEA0, RwV3d*, int32, const CMatrix&, const RwV3d*>(vecsOut, numVectors, matrix, vecsin);
}

// 0x54EE30
void TransformVectors(RwV3d* vecsOut, int32 numVectors, const CSimpleTransform& transform, const RwV3d* vecsin) {
    plugin::Call<0x54EE30, RwV3d*, int32, const CSimpleTransform&, const RwV3d*>(vecsOut, numVectors, transform, vecsin);
}

// 0x54EEF0
void TransformPoints(RwV3d* pointOut, int count, const RwMatrix& transformMatrix, RwV3d* pointIn) {
    plugin::Call<0x54EEF0, RwV3d*, int, const RwMatrix&, RwV3d*>(pointOut, count, transformMatrix, pointIn);
}

// 0x7186E0
char* MakeUpperCase(char* dest, const char* src) {
    for (; *src; src++, dest++)
        *dest = std::toupper(*src);
    *dest = 0;
    return dest;
}

// NOTSA
bool EndsWith(const char* str, const char* with, bool caseSensitive) {
    const auto strsz = strlen(str), withsz = strlen(with);
    assert(strsz >= withsz);
    return (caseSensitive ? strncmp : _strnicmp)(str + strsz - withsz, with, withsz) == 0;
}

// 0x734650
void DefinedState() {
    CRGBA rgbaFog(
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomRed,
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomBlue
    );

    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE,   RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            RWRSTATE(rwSHADEMODEGOURAUD));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEBORDERCOLOR,          RWRSTATE((RWRGBALONG(0, 0, 0, 255))));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEFOGCOLOR,             RWRSTATE(rgbaFog.ToIntARGB()));
    RwRenderStateSet(rwRENDERSTATEFOGTYPE,              RWRSTATE(rwFOGTYPELINEAR));
    RwRenderStateSet(rwRENDERSTATECULLMODE,             RWRSTATE(rwCULLMODECULLNONE));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(2)); // TODO: ?
}

// 0x734750
void DefinedState2d() {
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE,   RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            RWRSTATE(rwSHADEMODEGOURAUD));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEBORDERCOLOR,          RWRSTATE((RWRGBALONG(0, 0, 0, 255))));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATECULLMODE,             RWRSTATE(rwCULLMODECULLNONE));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(2)); // TODO: ?
}

// todo: move
// 0x53D840
void DoRWStuffEndOfFrame() {
    plugin::Call<0x53D840>();
}

// todo: move
// 0x53EC10
RsEventStatus AppEventHandler(RsEvent nEvent, void* param) {
    return plugin::CallAndReturn<RsEventStatus, 0x53EC10, RsEvent, void*>(nEvent, param);
}

// 0x70F9B0
bool GraphicsLowQuality() {
    if (g_fx.GetFxQuality() < FX_QUALITY_MEDIUM)
        return false;
    if (RwRasterGetDepth(RwCameraGetRaster(Scene.m_pRwCamera)) < 32)
        return false;
    return true;
}

// 0x5A4150
void WriteRaster(RwRaster* raster, const char* filename) {
    assert(raster);
    assert(filename && filename[0]);

    RwImage* img = RwImageCreate(RwRasterGetWidth(raster), RwRasterGetHeight(raster), RwRasterGetDepth(raster));
    RwImageAllocatePixels(img);
    RwImageSetFromRaster(img, raster);
    RtPNGImageWrite(img, filename);
    RwImageDestroy(img);
}

// 0x71DA00
bool CalcScreenCoors(const CVector& in, CVector* out, float* screenX, float* screenY) {
    return plugin::CallAndReturn<bool, 0x71DA00, const CVector&, CVector*, float*, float*>(in, out, screenX, screenY);

    // TODO: Figure out how to get screen size..
    CVector screen =  TheCamera.m_mViewMatrix * in;
    if (screen.z <= 1.0f)
        return false;

    const float depth = 1.0f / screen.z;

    CVector2D screenSize{};

    *out = screen * depth * CVector(screenSize.x, screenSize.y, 1.0f);

    *screenX = screenSize.x * depth / CDraw::ms_fFOV * 70.0f;
    *screenY = screenSize.y * depth / CDraw::ms_fFOV * 70.0f;

    return true;
}

/*!
* @0x71DAB0
* @brief Calculate a 3D position on the screen
* @param in  in  The 3D to get the screen position of
* @param out out The 2D screen position (Also includes the depth in the `z` component)
* @returns False if the depth was <= 1 (in which case the `x, y` positions are not not calculated, but `z` is)
*/
bool CalcScreenCoors(const CVector& in, CVector* out) {
    return plugin::CallAndReturn<bool, 0x71DAB0, const CVector&, CVector*>(in, out);

    *out = TheCamera.GetViewMatrix() * in;
    if (out->z <= 1.0f)
        return false;

    const auto depthRecp = 1.0f / out->z;
    out->x = SCREEN_WIDTH * depthRecp * out->x;
    out->y = SCREEN_HEIGHT * depthRecp * out->y;

    return true;
}

// 0x541330
void LittleTest() {
    ++g_nNumIm3dDrawCalls;
}

// used only in COccluder::ProcessLineSegment
// 0x71DB80
bool DoesInfiniteLineTouchScreen(float baseX, float baseY, float deltaX, float deltaY) {
    return plugin::CallAndReturn<bool, 0x71DB80, float, float, float, float>(baseX, baseY, deltaX, deltaY);
}

// Used only in COcclusion, COccluder, CActiveOccluder
// 0x71E050
bool IsPointInsideLine(float fLineBaseX, float fLineBaseY, float fDeltaX, float fDeltaY, float fTestPointX, float fTestPointY, float fRadius) {
    return (fTestPointX - fLineBaseX) * fDeltaY - (fTestPointY - fLineBaseY) * fDeltaX >= fRadius;
}

// 0x53E160
void RenderDebugShit() {
    PUSH_RENDERGROUP("RenderDebugShit");
    CTheScripts::RenderTheScriptDebugLines();
#ifndef FINAL
    // if(gbShowCollisionLines) CRenderer::RenderCollisionLines();
    // ThePaths.DisplayPathData();
    // CDebug::DrawLines();
    DefinedState();
#endif
    POP_RENDERGROUP();
}

// 0x53E230
void Render2dStuff() {
    RenderDebugShit(); // NOTSA, temp

    const auto DrawOuterZoomBox = []() {
        CPed* player = FindPlayerPed();
        eWeaponType weaponType = WEAPON_UNARMED;
        if (player)
            weaponType = player->GetActiveWeapon().m_nType;
        eCamMode camMode = CCamera::GetActiveCamera().m_nMode;
        bool firstPersonWeapon = false;
        if (camMode == MODE_SNIPER
            || camMode == MODE_SNIPER_RUNABOUT
            || camMode == MODE_ROCKETLAUNCHER
            || camMode == MODE_ROCKETLAUNCHER_RUNABOUT
            || camMode == MODE_CAMERA
            || camMode == MODE_HELICANNON_1STPERSON)
        {
            firstPersonWeapon = true;
        }

        if ((weaponType == WEAPON_SNIPERRIFLE || weaponType == WEAPON_ROCKET) && firstPersonWeapon) {
            CRGBA black(0, 0, 0, 255);
            if (weaponType == WEAPON_ROCKET)
            {
                CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT / 2 - SCREEN_SCALE_Y(180.0f)), black);
                CSprite2d::DrawRect(CRect(0.0f, SCREEN_HEIGHT / 2 + SCREEN_SCALE_Y(170.0f), SCREEN_WIDTH, SCREEN_HEIGHT), black);
            }
            else
            {
                CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT / 2 - SCREEN_SCALE_Y(210.0f)), black);
                CSprite2d::DrawRect(CRect(0.0f, SCREEN_HEIGHT / 2 + SCREEN_SCALE_Y(210.0f), SCREEN_WIDTH, SCREEN_HEIGHT), black);
            }
            CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH / 2 - SCREEN_SCALE_X(210.0f), SCREEN_HEIGHT), black);
            CSprite2d::DrawRect(CRect(SCREEN_WIDTH / 2 + SCREEN_SCALE_X(210.0f), 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT), black);
        }
    };

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(rwRENDERSTATENARENDERSTATE));
    RwRenderStateSet(rwRENDERSTATECULLMODE,          RWRSTATE(rwCULLMODECULLNONE));

    CReplay::Display();
    CPickups::RenderPickUpText();
    if (TheCamera.m_bWideScreenOn && !FrontEndMenuManager.m_bWidescreenOn) TheCamera.DrawBordersForWideScreen();
    DrawOuterZoomBox();
    AudioEngine.DisplayRadioStationName();
    CHud::Draw();
    CSpecialFX::Render2DFXs();
    CUserDisplay::OnscnTimer.ProcessForDisplay();
    CMessages::Display(true);
    CDarkel::DrawMessages();
    CGarages::PrintMessages();
    CFont::DrawFonts();

    // NOTSA: ImGui menu draw loop
    CDebugMenu::ImGuiDrawLoop();
}

// Convert UTF-8 string to Windows Unicode. Free pointer using delete[]
// NOTSA
std::wstring UTF8ToUnicode(const std::string &str)
{
    std::wstring out;

    int32 size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.data(), str.length(), nullptr, 0);
    if (size)
    {
        std::vector<wchar_t> temp;
        temp.resize(size, 0);

        if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.data(), str.length(), temp.data(), size)) {
            out.resize(size);
            std::copy(temp.begin(), temp.end(), out.begin());
        }
    }

    return out;
}

// Convert Windows Unicode to UTF-8. Free pointer using delete[]
// NOTSA
std::string UnicodeToUTF8(const std::wstring& str) {
    std::string out;

    int32 size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str.data(), str.length(), nullptr, 0, nullptr, nullptr);
    if (size) {
        std::vector<char> temp;
        temp.resize(size, 0);

        if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str.data(), str.length(), temp.data(), size, nullptr, nullptr)) {
            out.resize(size);
            std::copy(temp.begin(), temp.end(), out.begin());
        }
    }

    return out;
}

/*!
* @notsa
* @return The anim first found from `ids`
*/
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, std::initializer_list<AnimationId> ids) {
    for (const auto id : ids) {
        if (const auto anim = RpAnimBlendClumpGetAssociation(clump, (int32)id)) {
            return anim;
        }
    }
    return nullptr;
}
