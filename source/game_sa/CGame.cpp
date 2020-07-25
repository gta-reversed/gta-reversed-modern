#include "StdInc.h"
#include "CDebugMenu.h"

char(&CGame::aDatFile)[32] = *reinterpret_cast<char(*)[32]>(0xB728EC);
int &CGame::currLevel = *reinterpret_cast<int *>(0xB7290C);
unsigned char &CGame::bMissionPackGame = *reinterpret_cast<unsigned char *>(0xB72910);
int &CGame::currArea = *reinterpret_cast<int *>(0xB72914);
RwMatrix *&CGame::m_pWorkingMatrix1 = *reinterpret_cast<RwMatrix **>(0xB72920);
RwMatrix *&CGame::m_pWorkingMatrix2 = *reinterpret_cast<RwMatrix **>(0xB72924);
int &gameTxdSlot = *reinterpret_cast<int *>(0xB728E8);

void CGame::InjectHooks()
{
    HookInstall(0x53BB80, CGame::ShutdownRenderWare);
}

void CGame::ReloadIPLs() {
    plugin::CallDynGlobal(0x53BED0);
}

void CGame::ShutDownForRestart() {
    plugin::CallDynGlobal(0x53C550);
}

bool CGame::Shutdown() {
    return plugin::CallAndReturnDynGlobal<bool>(0x53C900);
}

static void CameraDestroy(RwCamera* pRwCamera)
{
    plugin::Call<0x72FD90, RwCamera*>(pRwCamera);
}

void CGame::ShutdownRenderWare() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal(0x53BB80);
#else
    CDebugMenu::ImguiDestroy();
    RwMatrixDestroy(CGame::m_pWorkingMatrix1);
    RwMatrixDestroy(CGame::m_pWorkingMatrix2);
    CLoadingScreen::Shutdown();
    CHud::Shutdown();
    CFont::Shutdown();
    for (std::int32_t i = 0; i < CWorld::TOTAL_PLAYERS; i++) {
        CWorld::Players[i].DeletePlayerSkin();
    }
    CPlayerSkin::Shutdown();
    DestroyDebugFont();
    LightsDestroy(Scene.m_pRpWorld);
    CVisibilityPlugins::Shutdown();
    RpWorldRemoveCamera(Scene.m_pRpWorld, Scene.m_pRwCamera);
    RpWorldDestroy(Scene.m_pRpWorld);
    CameraDestroy(Scene.m_pRwCamera);
    Scene.m_pRpWorld = 0;
    Scene.m_pRwCamera = 0;
    D3DResourceSystem::CancelBuffering();
    CPostEffects::Close();
#endif
}

void CGame::TidyUpMemory(bool a1, bool clearD3Dmem) {
    plugin::CallDynGlobal<bool, bool>(0x53C500, a1, clearD3Dmem);
}
