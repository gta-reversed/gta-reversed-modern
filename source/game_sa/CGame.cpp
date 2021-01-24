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
    ReversibleHooks::Install("CGame", "ShutdownRenderWare", 0x53BB80, CGame::ShutdownRenderWare);
    ReversibleHooks::Install("CGame", "Init1", 0x5BF840, CGame::Init1);
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

bool CGame::Init1(char const* datFile)
{
    CMaths::InitMathsTables();
    strcpy(CGame::aDatFile, datFile);
    CPools::Initialise();
    CPlaceable::InitMatrixArray();
    CIniFile::LoadIniFile();
    D3DResourceSystem::SetUseD3DResourceBuffering(false);
    CGame::currLevel = LEVEL_NAME_COUNTRY_SIDE;
    CGame::currArea = AREA_CODE_NORMAL_WORLD;
    gameTxdSlot = CTxdStore::AddTxdSlot("generic");
    CTxdStore::Create(gameTxdSlot);
    CTxdStore::AddRef(gameTxdSlot);
    int32_t slot = CTxdStore::AddTxdSlot("particle");
    CTxdStore::LoadTxd(slot, "MODELS\\PARTICLE.TXD");
    CTxdStore::AddRef(slot);
    CTxdStore::SetCurrentTxd(gameTxdSlot);
    CGameLogic::InitAtStartOfGame();
    CGangWars::InitAtStartOfGame();
    CConversations::Clear();
    CPedToPlayerConversations::Clear();
    CQuadTreeNode::InitPool();
    if (!CPlantMgr::Initialise() || !CCustomRoadsignMgr::Initialise())
        return false;
    CReferences::Init();
    CDebug::DebugInitTextBuffer();
    CTagManager::Init();
    CWeather::Init();
    CCover::Init();
    CCullZones::Init();
    COcclusion::Init();
    CCollision::Init();
    CBirds::Init();
    CEntryExitManager::Init();
    CStuntJumpManager::Init();
    CSetPieces::Init();
    CTheZones::Init();
    CUserDisplay::Init();
    CMessages::Init();
    CMessages::ClearAllMessagesDisplayedByGame(0);
    CVehicleRecording::Init();
    CRestart::Initialise();
    CWorld::Initialise();
    CAnimManager::Initialise();
    CCutsceneMgr::Initialise();
    CCarCtrl::Init();
    InitModelIndices();
    CModelInfo::Initialise();
    CPickups::Init();
    CTheCarGenerators::Init();
    CGarages::Init();
    CAudioZones::Init();
    CStreaming::InitImageList();
    CStreaming::ReadIniFile();
    ThePaths.Init();
    CPathFind::AllocatePathFindInfoMem();
    CTaskSimpleFight::LoadMeleeData();
    CPad::ResetCheats();
    g_fx.Init();
    return true;
}

void CGame::ShutdownRenderWare() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal(0x53BB80);
#else
    CDebugMenu::Shutdown();
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
    Scene.m_pRpWorld = nullptr;
    Scene.m_pRwCamera = nullptr;
    D3DResourceSystem::CancelBuffering();
    CPostEffects::Close();
#endif
}

void CGame::TidyUpMemory(bool a1, bool clearD3Dmem) {
    plugin::CallDynGlobal<bool, bool>(0x53C500, a1, clearD3Dmem);
}
