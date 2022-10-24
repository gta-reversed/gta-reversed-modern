#include "StdInc.h"

#include "CDebugMenu.h"

#include "WaterCannons.h"
#include "TheCarGenerators.h"
#include "Radar.h"
#include "Credits.h"
#include "Birds.h"
#include "MovingThings.h"
#include "PlantMgr.h"
#include "Occlusion.h"
#include "InteriorManager_c.h"
// #include "ProcObjectMan_c.h"
#include "WaterCreatureManager_c.h"
#include "MenuManager.h"
#include "FireManager.h"
#include "Fx.h"
#include "BreakManager_c.h"
#include "BoneNodeManager_c.h"
#include "Shadows.h"
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
#include "Glass.h"
#include "TheScripts.h"
#include "LoadingScreen.h"
#include "GridRef.h"
#include "MenuSystem.h"
#include "RealTimeShadowManager.h"
#include "VehicleRecording.h"
#include "ColAccel.h"
#include "app.h"
#include "Garages.h"
#include "TaskSimpleClimb.h"
#include "PedAttractor.h"
#include "MBlur.h"
#include "CustomBuildingRenderer.h"
#include "Hud.h"
#include "CarFXRenderer.h"
#include "GrassRenderer.h"

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

    RH_ScopedInstall(CanSeeOutSideFromCurrArea, 0x53C4A0);
    RH_ScopedInstall(CanSeeWaterFromCurrArea, 0x53C4B0);
    RH_ScopedInstall(Init1, 0x5BF840);
    RH_ScopedInstall(Init2, 0x5BA1A0);
    RH_ScopedInstall(Init3, 0x5BA400, { .reversed = false });
    RH_ScopedInstall(Initialise, 0x53BC80);
    RH_ScopedInstall(InitialiseCoreDataAfterRW, 0x5BFA90, { .reversed = false });
    RH_ScopedInstall(InitialiseEssentialsAfterRW, 0x5BA160, { .reversed = false });
    RH_ScopedInstall(InitialiseOnceBeforeRW, 0x53BB50);
    RH_ScopedInstall(InitialiseRenderWare, 0x5BD600, { .reversed = false });
    RH_ScopedInstall(InitialiseWhenRestarting, 0x53C680);
    RH_ScopedInstall(Process, 0x53BEE0, { .reversed = false });
    RH_ScopedInstall(ReInitGameObjectVariables, 0x53BCF0, { .reversed = false });
    RH_ScopedInstall(ReloadIPLs, 0x53BED0);
    RH_ScopedInstall(ShutDownForRestart, 0x53C550, { .reversed = false });
    RH_ScopedInstall(Shutdown, 0x53C900, { .reversed = false });
    RH_ScopedInstall(ShutdownRenderWare, 0x53BB80);
    RH_ScopedInstall(DrasticTidyUpMemory, 0x53C810);
    RH_ScopedInstall(FinalShutdown, 0x53BC30);
    RH_ScopedInstall(TidyUpMemory, 0x53C500);

    RH_ScopedGlobalInstall(CameraDestroy, 0x72FD90);
}

// 0x72FD90
static void CameraDestroy(RwCamera *rwCamera) {
    if (!rwCamera)
        return;

    if (auto obj = rwCamera->object.object; obj.parent) {
        rwObjectHasFrameSetFrame(&obj, NULL);
        RwFrameDestroy((RwFrame*)obj.parent);
    }

    if (auto frameBuffer = rwCamera->frameBuffer; frameBuffer) {
        RwRasterDestroy(frameBuffer);
        if (auto parent = frameBuffer->parent; parent && parent != frameBuffer) {
            RwRasterDestroy(parent);
        }
    }

    if (auto zBuffer = rwCamera->zBuffer; zBuffer) {
        RwRasterDestroy(zBuffer);
        if (auto parent = zBuffer->parent; parent && parent != zBuffer) {
            RwRasterDestroy(parent);
        }
    }

    RwCameraDestroy(rwCamera);
}

// 0x53BB80
void CGame::ShutdownRenderWare() {
    CDebugMenu::Shutdown();
    RwMatrixDestroy(m_pWorkingMatrix1);
    RwMatrixDestroy(m_pWorkingMatrix2);
    CLoadingScreen::Shutdown();
    CHud::Shutdown();
    CFont::Shutdown();
    rng::for_each(CWorld::Players, [](auto& info) { info.DeletePlayerSkin(); });
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
    return !CanSeeOutSideFromCurrArea() || currArea == AREA_CODE_5;
}

// 0x53C500
void CGame::TidyUpMemory(bool a1, bool clearD3Dmem) {
    if (FindPlayerPed(PED_TYPE_PLAYER1) && clearD3Dmem) {
        DrasticTidyUpMemory(a1);
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

    g_breakMan.Exit();
    // g_interiorMan.Exit();
    // g_procObjMan.Exit();
    g_waterCreatureMan.Exit();
    D3DResourceSystem::SetUseD3DResourceBuffering(false);
    CStencilShadowObject::Shutdown();
    CPlantMgr::Shutdown();
    CGrassRenderer::Shutdown();
    CRopes::Shutdown();
    CVehicleRecording::ShutDown();
    CReplay::FinishPlayback();
    CReplay::EmptyReplayBuffer();
    CTrain::Shutdown();
    CBirds::Shutdown();
    CSpecialFX::Shutdown();
    CGarages::Shutdown();
    CStuntJumpManager::Shutdown();
    CMovingThings::Shutdown();
    CWeapon::ShutdownWeapons();
    CPedType::Shutdown();

    for (auto& playerInfo : CWorld::Players) {
        if (playerInfo.m_pPed) {
            CWorld::Remove(playerInfo.m_pPed);
            delete playerInfo.m_pPed;
            playerInfo.m_pPed = nullptr;
        }
        playerInfo.Clear();
    }

    CRenderer::Shutdown();
    CWorld::ShutDown();
    CEntryExitManager::Shutdown();
    g_fx.Exit();
    g_boneNodeMan.Exit();
    g_ikChainMan.Exit();
    g_realTimeShadowMan.Exit();
    CModelInfo::ShutDown();
    CAnimManager::Shutdown();
    CCutsceneMgr::Shutdown();
    CVehicleModelInfo::DeleteVehicleColourTextures();
    CVehicleModelInfo::ShutdownEnvironmentMaps();
    CRadar::Shutdown();
    CStreaming::Shutdown();
    CTxdStore::GameShutdown();
    CCollision::Shutdown();
    CWaterLevel::Shutdown();
    CClouds::Shutdown();
    CShadows::Shutdown();
    CCoronas::Shutdown();
    CSkidmarks::Shutdown();
    CWeaponEffects::Shutdown();
    CTimeCycle::Shutdown();
    CCover::m_ListOfProcessedBuildings.Flush();
    CPedGroups::CleanUpForShutDown();
    CTaskSequences::CleanUpForShutdown();
    CInformGroupEventQueue::Flush();
    CInformFriendsEventQueue::Flush();
    CPools::ShutDown();
    CCarFXRenderer::Shutdown();
    CCustomBuildingRenderer::Shutdown();
    CVehicleModelInfo::ShutdownLightTexture();
    CVehicle::Shutdown();
    CCarFXRenderer::Shutdown();
    CCustomCarPlateMgr::Shutdown();
    CCustomRoadsignMgr::Shutdown();
    CHud::ReInitialise();
    CTxdStore::RemoveTxdSlot(gameTxdSlot);
    CTxdStore::RemoveTxdSlot(CTxdStore::FindTxdSlot("particle"));
    // col1[1].m_boundBox.m_vecMin.z = 0.0;
    // col1[0].m_pColData = 0;
    CTaskSimpleClimb::Shutdown();

    { // todo: move to CPedAttractor::Shutdown() or something
    // delete CPedAttractor::ms_tasks.First;
    // CPedAttractor::ms_tasks.First = 0;
    // CPedAttractor::ms_tasks.Last = 0;
    // CPedAttractor::ms_tasks.End = 0;
    }

    CTheScripts::RemoveScriptTextureDictionary();
    CMBlur::MotionBlurClose();
    CdStreamRemoveImages();
    D3DResourceSystem::Shutdown();
    return true;
}

// 0x53C550
void CGame::ShutDownForRestart() {
    return plugin::Call<0x53C550>();

    D3DResourceSystem::SetUseD3DResourceBuffering(false);
    CVehicleRecording::ShutDown();
    CReplay::FinishPlayback();
    CReplay::EmptyReplayBuffer();
    CMovingThings::Shutdown();
    rng::for_each(CWorld::Players, [](auto& info) { info.Clear(); });
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
    g_boneNodeMan.Reset();
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

// 0x
void CGame::GenerateTempPedAtStartOfNetworkGame() {
    // NOP
}

// 0x5BF840
bool CGame::Init1(char const *datFile) {
    CMaths::InitMathsTables();
    strcpy(aDatFile, datFile);
    CPools::Initialise();
    CPlaceable::InitMatrixArray();
    CIniFile::LoadIniFile();
    D3DResourceSystem::SetUseD3DResourceBuffering(false);
    currLevel = LEVEL_NAME_COUNTRY_SIDE;
    currArea = AREA_CODE_NORMAL_WORLD;

    CMemoryMgr::PushMemId(MEM_TEXTURES);
    gameTxdSlot = CTxdStore::AddTxdSlot("generic");
    CTxdStore::Create(gameTxdSlot);
    CTxdStore::AddRef(gameTxdSlot);

    int32 slot = CTxdStore::AddTxdSlot("particle");
    CTxdStore::LoadTxd(slot, "MODELS\\PARTICLE.TXD");
    CTxdStore::AddRef(slot);
    CTxdStore::SetCurrentTxd(gameTxdSlot);
    CMemoryMgr::PopMemId();

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

    CMemoryMgr::PushMemId(MEM_WORLD);
    CWorld::Initialise();
    CMemoryMgr::PopMemId();

    CMemoryMgr::PushMemId(MEM_ANIMATION);
    CAnimManager::Initialise();
    CCutsceneMgr::Initialise();
    CMemoryMgr::PopMemId();

    CMemoryMgr::PushMemId(MEM_CARS);
    CCarCtrl::Init();
    CMemoryMgr::PopMemId();

    // CMemoryMgr::PushMemId(MEM_DEFAULT_MODELS);
    InitModelIndices();

    CModelInfo::Initialise();
    CPickups::Init();
    CTheCarGenerators::Init();
    CGarages::Init();
    CAudioZones::Init();
    CStreaming::InitImageList();
    CStreaming::ReadIniFile();

    CMemoryMgr::PushMemId(MEM_PATHS);
    ThePaths.Init();
    CPathFind::AllocatePathFindInfoMem();
    CMemoryMgr::PopMemId();

    CTaskSimpleFight::LoadMeleeData();
    CCheat::ResetCheats();

    CMemoryMgr::PushMemId(MEM_FX);
    g_fx.Init();
    CMemoryMgr::PopMemId();

    return true;
}

// 0x5BA1A0
bool CGame::Init2(const char* datFile) {
    LoadingScreen("Loading the Game", "Add Particles");
    CTheZones::PostZoneCreation();
    CEntryExitManager::PostEntryExitsCreation();

    LoadingScreen("Loading the Game", "Setup paths");
    CPathFind::PreparePathData();

    rng::for_each(CWorld::Players, [](auto& info) {
        info.Clear();
        info.LoadPlayerSkin();
    });

    TestModelIndices();
    LoadingScreen("Loading the Game", "Setup water");
    CClothes::Init();
    CWaterLevel::WaterLevelInitialise();
    CDraw::SetFOV(120.0f);
    CDraw::ms_fLODDistance = 0.0f;

    if (!CCustomCarPlateMgr::Initialise()) {
        DEV_LOG("[CGame::Init2] CCustomCarPlateMgr::Initialise() failed");
        return false;
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

    return true;
}

// 0x5BA400
bool CGame::Init3(const char* datFile) {
    return plugin::CallAndReturn<bool, 0x5BA400, const char*>(datFile);

    LoadingScreen("Loading the Game", "Load scene");
    CPad::GetPad(0)->Clear(true, true);
    CPad::GetPad(1)->Clear(true, true);
    D3DResourceSystem::SetUseD3DResourceBuffering(true);
    LoadingScreen("Loading the Game", "Procedural Interiors");
    // g_interiorMan.Init();
    // g_procObjMan.Init();
    g_waterCreatureMan.Init();
    g_realTimeShadowMan.Init();
    return true;
}

// 0x53BC80
void CGame::Initialise(const char* datFile) {
    Init1(datFile);
    CColAccel::startCache();
    CFileLoader::LoadLevel("DATA\\DEFAULT.DAT");
    CFileLoader::LoadLevel(datFile);
    CColAccel::endCache();
    Init2(datFile);
    CStencilShadows::Init();
    LoadingScreen("Loading the Game", "Start script");
    CTheScripts::StartTestScript();
    CTheScripts::Process();
    TheCamera.Process();
    Init3(datFile);
}

// 0x5BFA90
void CGame::InitialiseCoreDataAfterRW() {
    plugin::Call<0x5BFA90>();
}

// 0x5BA160
bool CGame::InitialiseEssentialsAfterRW() {
    return plugin::CallAndReturn<bool, 0x5BA160>();

    CMemoryMgr::PushMemId(MEM_30);
    TheText.Load(false);
    if (!CCarFXRenderer::Initialise() || !CGrassRenderer::Initialise() || !CCustomBuildingRenderer::Initialise()) {
        return false;
    }
    CMemoryMgr::PopMemId();

    CTimer::Initialise();
    return true;
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
    const auto color = CRGBA(255, 255, 255, 255); // unused

    CTimer::Initialise();
    CEventScanner::m_sDeadPedWalkingTimer = 0;

    if (FrontEndMenuManager.m_bLoadingData) {
        FrontEndMenuManager.MessageScreen("FELD_WR", true, false);
        if (FrontEndMenuManager.m_bLoadingData) {
            CGenericGameStorage::RestoreForStartLoad();
            CStreaming::RemoveBigBuildings();
        }
    }

    ReInitGameObjectVariables();
    CTimeCycle::InitForRestart();
    CWeaponEffects::Init();
    CPlane::InitPlaneGenerationAndRemoval();

    if (FrontEndMenuManager.m_bLoadingData) {
        FrontEndMenuManager.m_bLoadingData = false;
        CGenericGameStorage::InitRadioStationPositionList();
        bool loaded = false;
        if (CGenericGameStorage::GenericLoad(loaded)) {
            CTrain::InitTrains();
        } else {
            for (auto i = 50; i > 0; --i) {
                MessageLoop();
                if (loaded) {
                    FrontEndMenuManager.MessageScreen("FES_LOC", true, false);
                } else {
                    FrontEndMenuManager.MessageScreen("FED_LFL", true, false);
                }
            }
            TheCamera.SetFadeColour(0, 0, 0);
            ShutDownForRestart();
            CTimer::Stop();
            CTimer::Initialise();
            FrontEndMenuManager.m_bLoadingData = false;
            ReInitGameObjectVariables();
            currLevel = 0;
            bMissionPackGame = 0;
            CCollision::SortOutCollisionAfterLoad();
        }
    }
    CTimer::Update();

    AudioEngine.ResetSoundEffects();
    AudioEngine.Restart();
    AudioEngine.SetMusicMasterVolume(FrontEndMenuManager.m_nRadioVolume);
    AudioEngine.SetEffectsMasterVolume(FrontEndMenuManager.m_nSfxVolume);
    AudioEngine.SetBassEnhanceOnOff(FrontEndMenuManager.m_bRadioEq);
    AudioEngine.SetRadioAutoRetuneOnOff(FrontEndMenuManager.m_bRadioAutoSelect);
    AudioEngine.InitialiseRadioStationID(FrontEndMenuManager.m_nRadioStation);
    D3DResourceSystem::SetUseD3DResourceBuffering(true);
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
    ThePaths.ReInit();
    CTimeCycle::Initialise();
    CPopCycle::Initialise();
    CDraw::SetFOV(120.0f);
    CDraw::ms_fLODDistance = 500.0f;
    currArea = AREA_CODE_NORMAL_WORLD;
    CPed::Initialise();
    CWeapon::InitialiseWeapons();
    CPopulation::Initialise();
    rng::for_each(CWorld::Players, [](auto& info) { info.Clear(); });
    CWorld::PlayerInFocus = PED_TYPE_PLAYER1;
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
    if (!FrontEndMenuManager.m_bLoadingData) {
        CCranes::InitCranes();
        CTheScripts::StartTestScript();
        CTheScripts::Process();
        TheCamera.Process();
        CTrain::InitTrains();
    }
    CPad::GetPad(PED_TYPE_PLAYER1)->Clear(true, true);
    CPad::GetPad(PED_TYPE_PLAYER2)->Clear(true, true);
}

// 0x53BED0
void CGame::ReloadIPLs() {
    // NOP
}
