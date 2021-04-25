#include "StdInc.h"
#include "CDebugMenu.h"

char(&CGame::aDatFile)[32] = *reinterpret_cast<char (*)[32]>(0xB728EC);
int &CGame::currLevel = *reinterpret_cast<int *>(0xB7290C);
unsigned char &CGame::bMissionPackGame = *reinterpret_cast<unsigned char *>(0xB72910);
int &CGame::currArea = *reinterpret_cast<int *>(0xB72914);
RwMatrix *&CGame::m_pWorkingMatrix1 = *reinterpret_cast<RwMatrix **>(0xB72920);
RwMatrix *&CGame::m_pWorkingMatrix2 = *reinterpret_cast<RwMatrix **>(0xB72924);
int &gameTxdSlot = *reinterpret_cast<int *>(0xB728E8);

void CGame::InjectHooks() {
    ReversibleHooks::Install("CGame", "ShutdownRenderWare", 0x53BB80, CGame::ShutdownRenderWare);
    ReversibleHooks::Install("CGame", "Init1", 0x5BF840, &CGame::Init1);
//    ReversibleHooks::Install("CGame", "Init2", 0x5BA1A0, &CGame::Init2);
//    ReversibleHooks::Install("CGame", "Init3", 0x5BA400, &CGame::Init3);
//    ReversibleHooks::Install("CGame", "InitAfterLostFocus", 0x0, &CGame::InitAfterLostFocus);
}

// 0x72FD90
static void CameraDestroy(RwCamera *pRwCamera) {
    plugin::Call<0x72FD90, RwCamera *>(pRwCamera);
}

// 0x53BB80
void CGame::ShutdownRenderWare() {
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
}

// 0x53C4A0
bool CGame::CanSeeOutSideFromCurrArea() {
    return false;
}

// 0x53C4B0
bool CGame::CanSeeWaterFromCurrArea() {
    return false;
}

// 0x53C500
void CGame::TidyUpMemory(bool a1, bool clearD3Dmem) {
    plugin::CallDynGlobal<bool, bool>(0x53C500, a1, clearD3Dmem);
}

// 0x53C810
void CGame::DrasticTidyUpMemory(bool a1) {

}

// 0x53C900
bool CGame::Shutdown() {
    return plugin::CallAndReturnDynGlobal<bool>(0x53C900);
}

// 0x53C550
void CGame::ShutDownForRestart() {
    plugin::CallDynGlobal(0x53C550);
}

// 0x53BC30
void CGame::FinalShutdown() {

}

// dummy function
// 0x
void CGame::GenerateTempPedAtStartOfNetworkGame() {

}

// 0x5BF840
bool CGame::Init1(char const *datFile) {
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
    if (!CPlantMgr::Initialise() || !CCustomRoadsignMgr::Initialise()) {
        return false;
    }

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

// 0x5BA1A0
void CGame::Init2(char const *datFile) {
    plugin::CallDynGlobal(0x5BA1A0);
}

// 0x5BA400
void CGame::Init3(char const *datFile) {
    plugin::CallDynGlobal(0x5BA400);
}

// 0x
void CGame::InitAfterLostFocus() {

}

// 0x53BC80
void CGame::Initialise(char const *datFile) {
    CGame::Init1(datFile);
    CColAccel::StartCache();
    CFileLoader::LoadLevel("DATA\\DEFAULT.DAT");
    CFileLoader::LoadLevel(datFile);
    CColAccel::EndCache();
    CGame::Init2(datFile);
    CStencilShadows::Init();
    LoadingScreen((char *) "Loading the Game", (char *) "Start script");
    CTheScripts::StartTestScript();
    CTheScripts::Process();
    TheCamera.Process();
    CGame::Init3(datFile);
}

// 0x5BFA90
void CGame::InitialiseCoreDataAfterRW() {

}

// 0x5BA160
bool CGame::InitialiseEssentialsAfterRW() {
    return true;
}

// 0x53BB50
void CGame::InitialiseOnceBeforeRW() {

}

// 0x5BD600
bool CGame::InitialiseRenderWare() {
    return true;
}

// 0x53C680
void CGame::InitialiseWhenRestarting() {

}

// 0x53BEE0
void CGame::Process() {

}

// 0x53BCF0
void CGame::ReInitGameObjectVariables() {

}

// 0x53BED0
void CGame::ReloadIPLs() {
    plugin::CallDynGlobal(0x53BED0);
}
