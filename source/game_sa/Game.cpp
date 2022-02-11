#include "StdInc.h"

#include "CDebugMenu.h"

#include "WaterCannons.h"
#include "TheCarGenerators.h"
#include "Radar.h"
#include "Credits.h"
#include "MovingThings.h"
#include "PlantMgr.h"
#include "Occlusion.h"
// todo: #include "InteriorManager_c.h"
// todo: #include "ProcObjectMan_c.h"
#include "WaterCreatureManager_c.h"
#include "MenuManager.h"
#include "FireManager.h"
#include "Fx_c.h"
#include "BreakManager_c.h"
// todo: #include "BoneNodeManager_c.h"
// todo: #include "ShadowManager.h"
#include "PedType.h"
#include "IKChainManager_c.h"
#include "CreepingFire.h"
#include "Skidmarks.h"
#include "CarCtrl.h"
#include "TagManager.h"
#include "Clouds.h"
#include "StuntJumpManager.h"
#include "CustomCarPlateMgr.h"
#include "TaskSimpleFight.h"
#include "Conversations.h"
#include "EntryExitManager.h"
#include "TempColModels.h"
#include "PedStats.h"
#include "UserDisplay.h"
#include "PostEffects.h"
#include "Rope.h"
#include "Ropes.h"

char (&CGame::aDatFile)[32] = *reinterpret_cast<char (*)[32]>(0xB728EC);
int32& CGame::currLevel = *reinterpret_cast<int32*>(0xB7290C);
uint8& CGame::bMissionPackGame = *reinterpret_cast<uint8*>(0xB72910);
int32& CGame::currArea = *reinterpret_cast<int32*>(0xB72914);
RwMatrix*& CGame::m_pWorkingMatrix1 = *reinterpret_cast<RwMatrix**>(0xB72920);
RwMatrix*& CGame::m_pWorkingMatrix2 = *reinterpret_cast<RwMatrix**>(0xB72924);
int32& gameTxdSlot = *reinterpret_cast<int32*>(0xB728E8);

bool& gbLARiots = *(bool*)0xB72958;
bool& gbLARiots_NoPoliceCars = *(bool*)0xB72959;

void CGame::InjectHooks() {
    RH_ScopedClass(CGame);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(CanSeeOutSideFromCurrArea, 0x53C4A0);
    // RH_ScopedInstall(CanSeeWaterFromCurrArea, 0x53C4B0);
    RH_ScopedInstall(Init1, 0x5BF840);
    RH_ScopedInstall(Init2, 0x5BA1A0);
    // RH_ScopedInstall(Init3, 0x5BA400);
    RH_ScopedInstall(Initialise, 0x53BC80);
    // RH_ScopedInstall(InitialiseCoreDataAfterRW, 0x5BFA90);
    // RH_ScopedInstall(InitialiseEssentialsAfterRW, 0x5BA160);
    RH_ScopedInstall(InitialiseOnceBeforeRW, 0x53BB50);
    // RH_ScopedInstall(InitialiseRenderWare, 0x5BD600);
    // RH_ScopedInstall(InitialiseWhenRestarting, 0x53C680);
    // RH_ScopedInstall(Process, 0x53BEE0);
    // RH_ScopedInstall(ReInitGameObjectVariables, 0x53BCF0);
    // RH_ScopedInstall(ReloadIPLs, 0x53BED0);
    // RH_ScopedInstall(ShutDownForRestart, 0x53C550);
    // RH_ScopedInstall(Shutdown, 0x53C900);
    RH_ScopedInstall(ShutdownRenderWare, 0x53BB80);
    // RH_ScopedInstall(DrasticTidyUpMemory, 0x53C810);
    // RH_ScopedInstall(FinalShutdown, 0x53BC30);
    // RH_ScopedInstall(TidyUpMemory, 0x53C500);
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
    for (int32 i = 0; i < CWorld::TOTAL_PLAYERS; i++) {
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
    return currArea == AREA_CODE_NORMAL_WORLD;
}

// 0x53C4B0
bool CGame::CanSeeWaterFromCurrArea() {
    return plugin::CallAndReturn<bool, 0x53C4B0>();
}

// 0x53C500
void CGame::TidyUpMemory(bool a1, bool clearD3Dmem) {
    if (FindPlayerPed(0)) {
        if (clearD3Dmem) {
            D3DResourceSystem::TidyUpD3DTextures(100);
            D3DResourceSystem::TidyUpD3DIndexBuffers(200);
        }
    }
}

// 0x53C810
void CGame::DrasticTidyUpMemory(bool a1) {
    D3DResourceSystem::TidyUpD3DTextures(100);
    D3DResourceSystem::TidyUpD3DIndexBuffers(200);
}

// 0x53C900
bool CGame::Shutdown() {
    return plugin::CallAndReturn<bool, 0x53C900>();
}

// 0x53C550
void CGame::ShutDownForRestart() {
    return plugin::Call<0x53C550>();

    D3DResourceSystem::SetUseD3DResourceBuffering(false);
    // todo: CVehicleRecording::ShutDown();
    CReplay::FinishPlayback();
    CReplay::EmptyReplayBuffer();
    CMovingThings::Shutdown();

    for (int32 i = 0; i < CWorld::TOTAL_PLAYERS; ++i) {
        CWorld::Players[i].Clear();
    }
    
    memset(CTheZones::ZonesVisited, 0, sizeof(CTheZones::ZonesVisited));
    CTheScripts::UndoBuildingSwaps();
    CTheScripts::UndoEntityInvisibilitySettings();
    // todo: g_interiorMan.Exit();
    // todo: g_procObjMan.Exit();
    g_waterCreatureMan.Exit();
    CRopes::Shutdown();
    CWorld::ClearForRestart();
    CGameLogic::ClearSkip(false);
    CTimer::Shutdown();
    CStreaming::ReInit();
    CRadar::RemoveRadarSections();
    FrontEndMenuManager.UnloadTextures();
    CSetPieces::Init();
    CConversations::Clear();
    CPedToPlayerConversations::Clear();
    CPedType::Shutdown();
    CSpecialFX::Shutdown();
    gFireManager.Shutdown();
    g_fx.Reset();
    g_breakMan.ResetAll();
    // todo: g_boneNodeMan.Reset();
    g_ikChainMan.Reset();
    // todo: g_realTimeShadowMan.Shutdown();
    CTheZones::ResetZonesRevealed();
    CEntryExitManager::ShutdownForRestart();
    CShopping::ShutdownForRestart();
    CTagManager::ShutdownForRestart();
    CStuntJumpManager::ShutdownForRestart();
    FindPlayerPed(0);
    CVehicle::ms_forceVehicleLightsOff = false;
}

// 0x53BC30
void CGame::FinalShutdown() {
    ThePaths.Shutdown();
    CTempColModels::Shutdown();
    CTxdStore::Shutdown();
    CPedStats::Shutdown();
    TheText.Unload(false);
    CdStreamShutdown();
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
    int32 slot = CTxdStore::AddTxdSlot("particle");
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

// 0x5BA1A0
void CGame::Init2(const char* datFile) {
    LoadingScreen("Loading the Game", "Add Particles");
    CTheZones::PostZoneCreation();
    CEntryExitManager::PostEntryExitsCreation();

    LoadingScreen("Loading the Game", "Setup paths");
    CPathFind::PreparePathData();

    for (int32 i = 0; i < CWorld::TOTAL_PLAYERS; ++i) {
        CWorld::Players[i].Clear();
        CWorld::Players[i].LoadPlayerSkin();
    }

    TestModelIndices();
    LoadingScreen("Loading the Game", "Setup water");
    CClothes::Init();
    CWaterLevel::WaterLevelInitialise();
    CDraw::SetFOV(120.0f);
    CDraw::ms_fLODDistance = 0.0f;

    if (!CCustomCarPlateMgr::Initialise()) {
        return;
    }

    LoadingScreen("Loading the Game", "Setup streaming");
    CStreaming::LoadInitialVehicles();
    CStreaming::LoadInitialPeds();
    CStreaming::LoadAllRequestedModels(false);

    LoadingScreen("Loading the Game", "Load animations");
    CAnimManager::LoadAnimFiles();

    LoadingScreen("Loading the Game", "Setup streaming");
    CStreaming::LoadInitialWeapons();
    CStreaming::LoadAllRequestedModels(false);

    LoadingScreen("Loading the Game", "Ped Init");
    CPed::Initialise();
    CRenderer::Init();

    LoadingScreen("Loading the Game", "Setup game variables");
    CRadar::Initialise();
    CRadar::LoadTextures();

    LoadingScreen(nullptr, nullptr);
    CWeapon::InitialiseWeapons();
    CRoadBlocks::Init();

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

    LoadingScreen("Loading the Game", "Load scripts");
    CTheScripts::Init();
    CGangs::Initialise();

    LoadingScreen("Loading the Game", "Setup game variables");
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
    CCredits::bCreditsGoing = false;
    CReplay::Init();
    CShopping::Init();
    LoadingScreen(nullptr, nullptr);
}

// 0x5BA400
void CGame::Init3(const char* datFile) {
    plugin::Call<0x5BA400, const char*>(datFile);
}

// 0x53BC80
void CGame::Initialise(char const *datFile) {
    CGame::Init1(datFile);
    CColAccel::startCache();
    CFileLoader::LoadLevel("DATA\\DEFAULT.DAT");
    CFileLoader::LoadLevel(datFile);
    CColAccel::endCache();
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
    return plugin::Call<0x53BCF0>();

    TheCamera.Init();
    CGameLogic::InitAtStartOfGame();
    CGangWars::InitAtStartOfGame();
    CWanted::InitialiseStaticVariables();
    TheCamera.Init();
    TheCamera.SetRwCamera(Scene.m_pRwCamera);
    CSkidmarks::Clear();
    CWeather::Init();
    CCover::Init();
    CUserDisplay::Init();
    CMessages::Init();
    CRestart::Initialise();
    CPostEffects::ScriptResetForEffects();
    CWorld::bDoingCarCollisions = false;
    CHud::ReInitialise();
    CRadar::Initialise();
    CCarCtrl::ReInit();
    // todo: ThePaths.ReInit();
    CTimeCycle::Initialise();
    CPopCycle::Initialise();
    CDraw::SetFOV(120.0f);
    CDraw::ms_fLODDistance = 500.0f;
    CGame::currArea = AREA_CODE_NORMAL_WORLD;
    CPed::Initialise();
    CWeapon::InitialiseWeapons();
    CPopulation::Initialise();

    for (int32 i = 0; i < CWorld::TOTAL_PLAYERS; ++i) {
        CWorld::Players[i].Clear();
    }

    CWorld::PlayerInFocus = 0;
    CGlass::Init();
    gbLARiots_NoPoliceCars = false;
    gbLARiots = false;
    CTheScripts::Init();
    CMenuSystem::Initialise();
    CGangs::Initialise();
    CTimer::Initialise();
    CClock::Initialise(1000u);
    CTheCarGenerators::Init();
    CHeli::InitHelis();
    CMovingThings::Init();
    CDarkel::Init();
    CStats::Init();
    CGarages::Init_AfterRestart();
    CRoadBlocks::Init();
    CStreaming::DisableCopBikes(false);
    CSpecialFX::Init();
    CRopes::Init();
    CWaterCannons::Init();
    // todo: CDecisionMakerTypesFileLoader::ReStart();
    CVehicleRecording::Init();
    gFireManager.Init();
    // todo: g_interiorMan.Init();
    // todo: g_procObjMan.Init();
    g_waterCreatureMan.Init();
    g_realTimeShadowMan.Init();
    CStreaming::RemoveInappropriatePedModels();
    AudioEngine.ResetStatistics();
    if ( !FrontEndMenuManager.m_bLoadingData )
    {
        CCranes::InitCranes();
        CTheScripts::StartTestScript();
        CTheScripts::Process();
        TheCamera.Process();
        CTrain::InitTrains();
    }
    CPad::GetPad(0)->Clear(true, true);
    CPad::GetPad(1)->Clear(true, true);
}

// dummy function
// 0x53BED0
void CGame::ReloadIPLs() {
    plugin::Call<0x53BED0>();
}
