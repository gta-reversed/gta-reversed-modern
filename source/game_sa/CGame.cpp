#include "StdInc.h"

#include "CDebugMenu.h"
#include "CWaterCannons.h"
#include "CTheCarGenerators.h"
#include "CRadar.h"

char (&CGame::aDatFile)[32] = *reinterpret_cast<char (*)[32]>(0xB728EC);
int& CGame::currLevel = *reinterpret_cast<int*>(0xB7290C);
unsigned char& CGame::bMissionPackGame = *reinterpret_cast<unsigned char*>(0xB72910);
int& CGame::currArea = *reinterpret_cast<int*>(0xB72914);
RwMatrix*& CGame::m_pWorkingMatrix1 = *reinterpret_cast<RwMatrix**>(0xB72920);
RwMatrix*& CGame::m_pWorkingMatrix2 = *reinterpret_cast<RwMatrix**>(0xB72924);
int& gameTxdSlot = *reinterpret_cast<int*>(0xB728E8);

bool& gbLARiots = *(bool*)0xB72958;
bool& gbLARiots_NoPoliceCars = *(bool*)0xB72959;

void CGame::InjectHooks() {
//    ReversibleHooks::Install("CGame", "CanSeeOutSideFromCurrArea", 0x53C4A0, &CGame::CanSeeOutSideFromCurrArea);
//    ReversibleHooks::Install("CGame", "CanSeeWaterFromCurrArea", 0x53C4B0, &CGame::CanSeeWaterFromCurrArea);
    ReversibleHooks::Install("CGame", "Init1", 0x5BF840, &CGame::Init1);
    ReversibleHooks::Install("CGame", "Init2", 0x5BA1A0, &CGame::Init2);
//    ReversibleHooks::Install("CGame", "Init3", 0x5BA400, &CGame::Init3);
    ReversibleHooks::Install("CGame", "Initialise", 0x53BC80, &CGame::Initialise);
//    ReversibleHooks::Install("CGame", "InitialiseCoreDataAfterRW", 0x5BFA90, &CGame::InitialiseCoreDataAfterRW);
//    ReversibleHooks::Install("CGame", "InitialiseEssentialsAfterRW", 0x5BA160, &CGame::InitialiseEssentialsAfterRW);
    ReversibleHooks::Install("CGame", "InitialiseOnceBeforeRW", 0x53BB50, &CGame::InitialiseOnceBeforeRW);
//    ReversibleHooks::Install("CGame", "InitialiseRenderWare", 0x5BD600, &CGame::InitialiseRenderWare);
//    ReversibleHooks::Install("CGame", "InitialiseWhenRestarting", 0x53C680, &CGame::InitialiseWhenRestarting);
//    ReversibleHooks::Install("CGame", "Process", 0x53BEE0, &CGame::Process);
//    ReversibleHooks::Install("CGame", "ReInitGameObjectVariables", 0x53BCF0, &CGame::ReInitGameObjectVariables);
//    ReversibleHooks::Install("CGame", "ReloadIPLs", 0x53BED0, &CGame::ReloadIPLs);
//    ReversibleHooks::Install("CGame", "ShutDownForRestart", 0x53C550, &CGame::ShutDownForRestart);
//    ReversibleHooks::Install("CGame", "Shutdown", 0x53C900, &CGame::Shutdown);
    ReversibleHooks::Install("CGame", "ShutdownRenderWare", 0x53BB80, &CGame::ShutdownRenderWare);
//    ReversibleHooks::Install("CGame", "DrasticTidyUpMemory", 0x53C810, &CGame::DrasticTidyUpMemory);
//    ReversibleHooks::Install("CGame", "FinalShutdown", 0x53BC30, &CGame::FinalShutdown);
//    ReversibleHooks::Install("CGame", "TidyUpMemory", 0x53C500, &CGame::TidyUpMemory);
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
    for (int i = 0; i < CWorld::TOTAL_PLAYERS; i++) {
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
    return plugin::CallAndReturn<bool, 0x53C4A0>();
}

// 0x53C4B0
bool CGame::CanSeeWaterFromCurrArea() {
    return plugin::CallAndReturn<bool, 0x53C4B0>();
}

// 0x53C500
void CGame::TidyUpMemory(bool a1, bool clearD3Dmem) {
    plugin::Call<0x53C500, bool, bool>(a1, clearD3Dmem);
}

// 0x53C810
void CGame::DrasticTidyUpMemory(bool a1) {
    plugin::Call<0x53C810, bool>(a1);
}

// 0x53C900
bool CGame::Shutdown() {
    return plugin::CallAndReturn<bool, 0x53C900>();
}

// 0x53C550
void CGame::ShutDownForRestart() {
    plugin::Call<0x53C550>();
}

// 0x53BC30
void CGame::FinalShutdown() {
    plugin::Call<0x53BC30>();
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
    CCheat::ResetCheats();
    g_fx.Init();
    return true;
}

// 0x53ED30
void TestModelIndices() {
    // NOP
}

// 0x5BA1A0
void CGame::Init2(char const* datFile) {
    LoadingScreen((char*)"Loading the Game", (char*)"Add Particles");
    CTheZones::PostZoneCreation();
    CEntryExitManager::PostEntryExitsCreation();

    LoadingScreen((char*)"Loading the Game", (char*)"Setup paths");
    CPathFind::PreparePathData();

    for (int i = 0; i < CWorld::TOTAL_PLAYERS; ++i) {
        CWorld::Players[i].Clear();
        CWorld::Players[i].LoadPlayerSkin();
    }

    TestModelIndices();
    LoadingScreen((char*)"Loading the Game", (char*)"Setup water");
    CClothes::Init();
    CWaterLevel::WaterLevelInitialise();
    CDraw::SetFOV(120.0f);
    CDraw::ms_fLODDistance = 0.0f;

    if (!CCustomCarPlateMgr::Initialise()) {
        return;
    }

    LoadingScreen((char*)"Loading the Game", (char*)"Setup streaming");
    CStreaming::LoadInitialVehicles();
    CStreaming::LoadInitialPeds();
    CStreaming::LoadAllRequestedModels(false);

    LoadingScreen((char*)"Loading the Game", (char*)"Load animations");
    CAnimManager::LoadAnimFiles();

    LoadingScreen((char*)"Loading the Game", (char*)"Setup streaming");
    CStreaming::LoadInitialWeapons();
    CStreaming::LoadAllRequestedModels(false);

    LoadingScreen((char*)"Loading the Game", (char*)"Ped Init");
    CPed::Initialise();
    CRenderer::Init();

    LoadingScreen((char*)"Loading the Game", (char*)"Setup game variables");
    CRadar::Initialise();
    CRadar::LoadTextures();

    LoadingScreen(nullptr, nullptr);
    CWeapon::InitialiseWeapons();
    CRoadBlocks::Init(datFile);

    LoadingScreen(nullptr, nullptr);
    CPopulation::Initialise();

    LoadingScreen(nullptr, nullptr);
    CWorld::PlayerInFocus = 0;
    CCoronas::Init();
    CShadows::Init();

    LoadingScreen(nullptr, nullptr);
    CWeaponEffects::Init();
    CSkidmarks::Init();
    CGlass::Init();
    CGarages::Init_AfterRestart();

    LoadingScreen((char*)"Loading the Game", (char*)"Load scripts");
    CTheScripts::Init(datFile);
    CGangs::Initialise();

    LoadingScreen((char*)"Loading the Game", (char*)"Setup game variables");
    CClock::Initialise(1000);
    CHeli::InitHelis();
    CCranes::InitCranes();

    LoadingScreen(nullptr, nullptr);
    CMovingThings::Init();
    CDarkel::Init();

    LoadingScreen(nullptr, nullptr);
    CGridRef::Init();
    CStats::Init();
    CClouds::Init();
    CSpecialFX::Init();

    LoadingScreen(nullptr, nullptr);
    CRopes::Init();
    CWaterCannons::Init();
    CBridge::Init();
    CPedGroups::Init();
    CInformFriendsEventQueue::Init();
    CInformGroupEventQueue::Init();

    LoadingScreen(nullptr, nullptr);
    CCredits::m_bCreditsGoing = false;
    CReplay::Init();
    CShopping::Init();
    LoadingScreen(nullptr, nullptr);
}

// 0x5BA400
void CGame::Init3(char const* datFile) {
    plugin::Call<0x5BA400, char const*>(datFile);
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
    plugin::Call<0x5BFA90>();
}

// 0x5BA160
bool CGame::InitialiseEssentialsAfterRW() {
    return plugin::CallAndReturn<bool, 0x5BA160>();

    /*
    TheText.Load(false);
    if (!CCarFXRenderer::Initialise() || !CGrassRenderer::Initialise() || !CCustomBuildingRenderer::Initialise())
        return false;

    CTimer::Initialise();
    return true;
    */
}

// 0x53BB50
void CGame::InitialiseOnceBeforeRW() {
    CMemoryMgr::Init();
    CLocalisation::Initialise();
    CFileMgr::Initialise();
    CdStreamInit(5);
    CPad::Initialise();
}

// 0x5BD600
bool CGame::InitialiseRenderWare() {
    return plugin::CallAndReturn<bool, 0x5BD600>();
}

// 0x53C680
void CGame::InitialiseWhenRestarting() {
    plugin::Call<0x53C680>();
}

// 0x53BEE0
void CGame::Process() {
    plugin::Call<0x53BEE0>();
}

// 0x53BCF0
void CGame::ReInitGameObjectVariables() {
    plugin::Call<0x53BCF0>();
}

// dummy function
// 0x53BED0
void CGame::ReloadIPLs() {
    plugin::Call<0x53BED0>();
}
