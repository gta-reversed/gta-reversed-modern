#include "StdInc.h"

// Audio
#include "AEAudioChannel.h"
#include "AEAudioEnvironment.h"
#include "AEAudioHardware.h"
#include "AEAudioUtility.h"
#include "AEDataStream.h"
#include "AEMFDecoder.h"
#include "AESmoothFadeThread.h"
#include "AESoundManager.h"
#include "AEStaticChannel.h"
#include "AEVorbisDecoder.h"
#include "AEWaveDecoder.h"
#include "AEWMADecoder.h"
#include "AEStreamingDecoder.h"
#include "AEUserRadioTrackManager.h"
#include "AEWaterCannonAudioEntity.h"
#include "AEDoorAudioEntity.h"
#include "AEStreamThread.h"
#include "AEFrontendAudioEntity.h"
#include "AEScriptAudioEntity.h"
#include "AERadioTrackManager.h"
#include "AEAmbienceTrackManager.h"
#include "AECutsceneTrackManager.h"
#include "AECollisionAudioEntity.h"
#include "AEGlobalWeaponAudioEntity.h"
#include "AEPedAudioEntity.h"
#include "AEPedlessSpeechAudioEntity.h"
#include "AEPoliceScannerAudioEntity.h"
#include "AudioEngine.h"

#include "CDebugMenu.h"

#include "CarGenerator.h"
#include "TheCarGenerators.h"
#include "Radar.h"
#include "WaterCannons.h"
#include "Lines.h"
#include "Escalators.h"
#include "MovingThings.h"
#include "MovingThings.h"
#include "PlaneTrail.h"
#include "PlaneTrails.h"
#include "Gamma.h"
#include "CustomBuildingPipeline.h"
#include "CustomBuildingDNPipeline.h"
#include "CustomCarEnvMapPipeline.h"
#include "CustomBuildingRenderer.h"
#include "PlantMgr.h"
#include "PedType.h"
#include "Occlusion.h"
#include "Occluder.h"
#include "ActiveOccluder.h"
#include "MotionBlurStreaks.h"
#include "GroupEventHandler.h"
#include "SimpleVariablesSaveStructure.h"
#include "BreakManager_c.h"
#include "Buoyancy.h"
#include "CreepingFire.h"
#include "Restart.h"
#include "BulletInfo.h"
#include "Explosion.h"
#include "C_PcSave.h"
#include "FireManager.h"
#include "Skidmarks.h"
#include "CarCtrl.h"
#include "TagManager.h"
#include "Clouds.h"
#include "StuntJumpManager.h"
#include "CustomCarPlateMgr.h"
#include "WindModifiers.h"
#include "PedPlacement.h"
#include "UpsideDownCarCheck.h"
#include "PedClothesDesc.h"
#include "WaterCannon.h"
#include "EntryExitManager.h"
#include "ObjectSaveStructure.h"
#include "PedStats.h"
#include "TrafficLights.h"
#include "CurrentVehicle.h"
#include "PlaceName.h"
#include "UserDisplay.h"
#include "OnscreenTimer.h"
#include "OnscreenCounterEntry.h"
#include "PostEffects.h"
#include "Rope.h"
#include "Ropes.h"
#include "FallingGlassPane.h"
#include "Glass.h"
#include "FurnitureGroup_c.h"
#include "FurnitureManager_c.h"
#include "FurnitureSubGroup_c.h"
#include "Interior_c.h"
#include "InteriorGroup_c.h"
#include "InteriorManager_c.h"
#include "Checkpoint.h"
#include "Checkpoints.h"
#include "IKChain_c.h"
#include "IKChainManager_c.h"
#include "BoneNode_c.h"
#include "BoneNodeManager_c.h"
#include "TheScripts.h"
#include "RunningScript.h"
#include "Scripted2dEffects.h"
#include "ScriptResourceManager.h"
#include "PedAttractorManager.h"
#include "LoadingScreen.h"
#include "Securom.h"
#include "GridRef.h"
#include "MenuSystem.h"
#include "InterestingEvents.h"
#include "Shadows.h"
#include "ShadowCamera.h"
#include "VehicleRecording.h"
#include "Birds.h"
#include "Hud.h"
#include "CarFXRenderer.h"

// Tasks
#include "EntitySeekPosCalculator.h"
#include "EntitySeekPosCalculatorStandard.h"
#include "EntitySeekPosCalculatorRadiusAngleOffset.h"
#include "EntitySeekPosCalculatorXYOffset.h"
#include "TaskComplexSmartFleeEntity.h"
#include "TaskSimpleArrestPed.h"
#include "TaskComplexDragPedFromCar.h"
#include "TaskComplexDestroyCar.h"
#include "TaskSimpleAbseil.h"
#include "TaskComplexWanderCop.h"
#include "TaskComplexUseMobilePhone.h"
#include "TaskSimpleStandStill.h"
#include "TaskSimpleCarDrive.h"
#include "TaskSimpleScratchHead.h"
#include "TaskSimpleChoking.h"
#include "TaskComplexPartnerChat.h"
#include "TaskSimpleUseGun.h"
#include "TaskSimpleGangDriveBy.h"
#include "TaskComplexObserveTrafficLightsAndAchieveHeading.h"
#include "TaskSimpleInAir.h"
#include "TaskComplexHitPedWithCar.h"
#include "TaskSimplePlayerOnFoot.h"
#include "TaskComplexFollowPedFootsteps.h"
#include "TaskComplexGetUpAndStandStill.h"
#include "TaskComplexGoPickUpEntity.h"
#include "TaskSimpleDie.h"
#include "TaskSimpleDuck.h"
#include "TaskComplexPolicePursuit.h"
#include "TaskSimpleFacial.h"
#include "TaskComplexCopInCar.h"
#include "TaskComplexFacial.h"
#include "TaskComplexInAirAndLand.h"
#include "TaskSimpleGetUp.h"
#include "TaskSimpleUninterruptable.h"
#include "TaskComplexFallAndGetUp.h"
#include "TaskComplexFollowNodeRoute.h"
#include "TaskComplexFollowLeaderInFormation.h"
#include "TaskSimpleTriggerLookAt.h"
#include "TaskSimpleHitHead.h"
#include "TaskUtilityLineUpPedWithCar.h"
#include "TaskSimpleLand.h"
#include "TaskSimpleJetPack.h"
#include "TaskSimpleSetStayInSamePlace.h"
#include "TaskSimpleJump.h"
#include "TaskSimpleFall.h"
#include "TaskSimpleClimb.h"
#include "TaskComplexPlayHandSignalAnim.h"
#include "TaskComplexWaitForPed.h"
#include "TaskComplexJump.h"
#include "TaskComplexWanderStandard.h"
#include "TaskComplexSunbathe.h"
#include "TaskComplexEnterCar.h"
#include "TaskSimpleTogglePedThreatScanner.h"
#include "TaskComplexUseGoggles.h"
#include "TaskComplexCrossRoadLookAndAchieveHeading.h"
#include "TaskComplexGoToPointAndStandStill.h"
#include "TaskSimpleAchieveHeading.h"
#include "TaskSimpleGiveCPR.h"
#include "TaskSimpleCarSetPedInAsPassenger.h"
#include "TaskComplexDriveFireTruck.h"
#include "TaskSimpleSwim.h"
#include "TaskComplexWalkRoundObject.h"
#include "TaskSimplePause.h"
#include "TaskComplexEnterCarAsPassenger.h"
#include "TaskComplexEnterCarAsDriver.h"
#include "TaskSimpleNone.h"
#include "TaskComplexKillPedOnFoot.h"
#include "TaskSimpleThrowProjectile.h"
#include "TaskSimpleGoToPoint.h"
#include "TaskComplexWanderMedic.h"
#include "TaskSimpleCarDriveTimed.h"
#include "TaskComplexDriveWander.h"
#include "TaskSimpleStealthKill.h"
#include "TaskSimpleCarSetPedOut.h"
#include "TaskSimpleAnim.h"
#include "TaskSimpleRunAnim.h"
#include "TaskComplexWanderCriminal.h"
#include "TaskComplexWanderProstitute.h"
#include "TaskComplexPartnerGreet.h"
#include "TaskComplexWalkRoundCar.h"
#include "TaskSimpleDuck.h"
#include "TaskComplexMedicTreatInjuredPed.h"
#include "TaskSimplePlayHandSignalAnim.h"
#include "TaskComplexCarDrive.h"
#include "TaskComplexKillPedFromBoat.h"
#include "TaskComplexLeaveCar.h"
#include "TaskComplexTreatAccident.h"
#include "TaskComplexGoToPointAndStandStillTimed.h"
#include "TaskComplexPartnerShove.h"
#include "TaskSimpleRunNamedAnim.h"
#include "TaskComplexProstituteSolicit.h"
#include "TaskComplexStuckInAir.h"
#include "TaskSimpleHoldEntity.h"
#include "TaskSimpleGoTo.h"
#include "TaskComplexPartner.h"
#include "TaskSimpleCarSetPedInAsDriver.h"
#include "TaskComplexWander.h"
#include "TaskSimplePutDownEntity.h"
#include "TaskComplexUseSwatRope.h"
#include "TaskSimpleGoToPointFine.h"
#include "TaskComplexDie.h"
#include "TaskComplexEnterBoatAsDriver.h"
#include "TaskSimpleFight.h"
#include "TaskComplexUseWaterCannon.h"
#include "TaskComplexDriveToPoint.h"
#include "TaskSimpleSlideToCoord.h"
#include "TaskComplexPartnerDeal.h"
#include "TaskSimplePickUpEntity.h"
#include "TaskComplexBeInGroup.h"
#include "TaskComplexBeCop.h"
#include "TaskComplexAvoidOtherPedWhileWandering.h"
#include "TaskComplexArrestPed.h"
#include "TaskComplexEnterAnyCarAsDriver.h"
#include "TaskComplexCarDriveMission.h"
#include "TaskComplexLeaveAnyCar.h"
#include "TaskSimpleCreateCarAndGetIn.h"
#include "TaskSimpleIKChain.h"
#include "TaskSimpleIKLookAt.h"
#include "TaskSimpleIKManager.h"
#include "TaskSimpleIKPointArm.h"
#include "TaskSimpleCarSlowDragPedOut.h"
#include "TaskSimpleWaitUntilPedIsOutCar.h"
#include "TaskComplexAvoidEntity.h"
#include "TaskGangHasslePed.h"
#include "TaskGangHassleVehicle.h"
#include "TaskGoToVehicleAndLean.h"
#include "TaskLeanOnVehicle.h"
#include "TaskComplexCarSlowBeDraggedOut.h"
#include "TaskComplexCarSlowBeDraggedOutAndStandUp.h"
#include "TaskComplexGangFollower.h"
#include "TaskComplexGangJoinRespond.h"
#include "TaskComplexGangLeader.h"
#include "TaskComplexGetOnBoatSeat.h"
#include "TaskComplexGoToAttractor.h"
#include "TaskComplexGoToBoatSteeringWheel.h"
#include "TaskComplexGoToCarDoorAndStandStill.h"
#include "TaskComplexGoToPointAiming.h"
#include "TaskComplexGoToPointAndStandStillAndAchieveHeading.h"
#include "TaskComplexGoToPointAnyMeans.h"
#include "TaskComplexGoToPointShooting.h"
#include "TaskComplexGotoDoorAndOpen.h"
#include "TaskComplexHitByGunResponse.h"
#include "TaskComplexHitResponse.h"
#include "TaskSimpleDrown.h"
#include "TaskComplexDieInCar.h"
#include "TaskComplexFallToDeath.h"
#include "TaskSimpleDrownInCar.h"
#include "TaskSimpleDieInCar.h"
#include "TaskComplexTurnToFaceEntityOrCoord.h"
#include "TaskSimpleTired.h"
#include "Input.h"

#include "EventSeenPanickedPed.h"
#include "EventCarUpsideDown.h"
#include "EventPassObject.h"
#include "EventLeanOnVehicle.h"
#include "EventOnFire.h"
#include "EventEscalator.h"
#include "EventCopCarBeingStolen.h"
#include "EventDanger.h"

#include "Plugins/BreakablePlugin/BreakablePlugin.h"

#include "app_input.h"
#include "platform/win/VideoPlayer/VideoPlayer.h"
#include "platform/win/win.h"
#include "platform/platform.h"

#include "extensions/utility.hpp"

void InjectHooksMain() {
    HookInstall(0x53E230, &Render2dStuff);   // [ImGui] This one shouldn't be reversible, it contains imgui debug menu logic, and makes game unplayable without
    HookInstall(0x541DD0, CPad::UpdatePads); // [ImGui] Changes logic of the function and shouldn't be toggled on/off
    HookInstall(0x459F70, CVehicleRecording::Render); // [ImGui] Debug stuff rendering
    CFileMgr::InjectHooks();

    RwHelperInjectHooks();
    CPad::InjectHooks();
    InjectCommonHooks();
    CEscalator::InjectHooks();
    CShadowCamera::InjectHooks();
    CInterestingEvents::InjectHooks();
    CShadows::InjectHooks();
    CCam::InjectHooks();
    CCarAI::InjectHooks();
    CMenuSystem::InjectHooks();
    CCarFXRenderer::InjectHooks();
    CPedAttractorManager::InjectHooks();
    BoneNode_c::InjectHooks();
    BoneNodeManager_c::InjectHooks();
    CAnimBlendClumpData::InjectHooks();
    IKChainManager_c::InjectHooks();
    IKChain_c::InjectHooks();
    CCheckpoint::InjectHooks();
    CCheckpoints::InjectHooks();
    CWeaponEffects::InjectHooks();
    CPedList::InjectHooks();
    CBouncingPanel::InjectHooks();
    CRope::InjectHooks();
    CRopes::InjectHooks();
    CWeaponInfo::InjectHooks();
    CCurrentVehicle::InjectHooks();
    CPlaceName::InjectHooks();
    CUserDisplay::InjectHooks();
    COnscreenTimer::InjectHooks();
    COnscreenCounterEntry::InjectHooks();
    CPedPlacement::InjectHooks();
    CWindModifiers::InjectHooks();
    CGenericGameStorage::InjectHooks();
    C_PcSave::InjectHooks();
    CFileLoader::InjectHooks();
    CWorld::InjectHooks();
    CStreamingInfo::InjectHooks();
    CStreaming::InjectHooks();
    InjectCdStreamHooks();
    CMirrors::InjectHooks();
    CFire::InjectHooks();
    CExplosion::InjectHooks();
    CClothesBuilder::InjectHooks();
    CClothes::InjectHooks();
    CBulletInfo::InjectHooks();
    CRestart::InjectHooks();
    CCopPed::InjectHooks();
    CDamageManager::InjectHooks();
    CCreepingFire::InjectHooks();
    CPtrList::InjectHooks();
    BreakManager_c::InjectHooks();
    BreakObject_c::InjectHooks();
    CFireManager::InjectHooks();
    CGroupEventHandler::InjectHooks();
    CVehicleRecording::InjectHooks();
    Fx_c::InjectHooks();
    CBrightLights::InjectHooks();
    CShinyTexts::InjectHooks();
    CPedTaskPair::InjectHooks();
    CDirectory::InjectHooks();
    CBulletTraces::InjectHooks();
    CDebug::InjectHooks();
    CGame::InjectHooks();
    CPools::InjectHooks();
    CControllerState::InjectHooks();
    CKeyboardState::InjectHooks();
    CMouseControllerState::InjectHooks();
    CRect::InjectHooks();
    CVector2D::InjectHooks();
    CQuaternion::InjectHooks();
    CMatrix::InjectHooks();
    CMatrixLink::InjectHooks();
    CMatrixLinkList::InjectHooks();
    CEntryInfoNode::InjectHooks();
    CEntryInfoList::InjectHooks();
    CPtrNodeDoubleLink::InjectHooks();
    CPtrListDoubleLink::InjectHooks();
    CPtrNodeSingleLink::InjectHooks();
    CPtrListSingleLink::InjectHooks();
    List_c::InjectHooks();
    CReferences::InjectHooks();
    CPopulation::InjectHooks();
    CModelInfo::InjectHooks();
    CBaseModelInfo::InjectHooks();
    CAtomicModelInfo::InjectHooks();
    CLodAtomicModelInfo::InjectHooks();
    CVehicleModelInfo::InjectHooks();
    CClumpModelInfo::InjectHooks();
    CTimeModelInfo::InjectHooks();
    CDamageAtomicModelInfo::InjectHooks();
    CWeaponModelInfo::InjectHooks();
    CPedModelInfo::InjectHooks();
    CTimeInfo::InjectHooks();
    SurfaceInfos_c::InjectHooks();
    CPlaceable::InjectHooks();
    CEntity::InjectHooks();
    CPhysical::InjectHooks();
    CRenderer::InjectHooks();
    CDummy::InjectHooks();
    CDummyObject::InjectHooks();
    CObject::InjectHooks();
    CObjectData::InjectHooks();
    CObjectSaveStructure::InjectHooks();
    CCutsceneObject::InjectHooks();
    CHandObject::InjectHooks();
    CBuilding::InjectHooks();
    CAnimatedBuilding::InjectHooks();
    CCompressedMatrixNotAligned::InjectHooks();
    CVisibilityPlugins::InjectHooks();
    CPed::InjectHooks();
    CPedIntelligence::InjectHooks();
    CCollision::InjectHooks();
    CColSphere::InjectHooks();
    CColLine::InjectHooks();
    CColTrianglePlane::InjectHooks();
    CBox::InjectHooks();
    CColModel::InjectHooks();
    CCollisionData::InjectHooks();
    CQuadTreeNode::InjectHooks();
    CColStore::InjectHooks();
    CColAccel::InjectHooks();
    CTrafficLights::InjectHooks();
    CMotionBlurStreaks::InjectHooks();
    CRegisteredMotionBlurStreak::InjectHooks();
    CCover::InjectHooks();
    CVehicleAnimGroup::InjectHooks();
    CVehicleAnimGroupData::InjectHooks();
    CPedDamageResponseCalculator::InjectHooks();
    CPedScriptedTaskRecord::InjectHooks();
    CPedScriptedTaskRecordData::InjectHooks();
    CPedClothesDesc::InjectHooks();
    CScriptedBrainTaskStore::InjectHooks();
    CTimer::InjectHooks();
    CTagManager::InjectHooks();
    CWaterLevel::InjectHooks();
    cBuoyancy::InjectHooks();
    CWanted::InjectHooks();
    CEscalators::InjectHooks();
    CWeapon::InjectHooks();
    cTransmission::InjectHooks();
    CPlayerPed::InjectHooks();
    CStats::InjectHooks();
    CCarCtrl::InjectHooks();
    CTheZones::InjectHooks();
    CMenuManager::InjectHooks();
    CSprite2d::InjectHooks();
    CCheat::InjectHooks();
    CBirds::InjectHooks();
    WaterCreature_c::InjectHooks();
    WaterCreatureManager_c::InjectHooks();
    C2dEffect::InjectHooks();
    CCustomRoadsignMgr::InjectHooks();
    COcclusion::InjectHooks();
    COccluder::InjectHooks();
    CActiveOccluder::InjectHooks();
    CGarage::InjectHooks();
    CGarages::InjectHooks();
    CPostEffects::InjectHooks();
    CIniFile::InjectHooks();
    CStencilShadowObject::InjectHooks();
    CStencilShadowObjects::InjectHooks();
    CStencilShadows::InjectHooks();
    CFont::InjectHooks();
    CGameLogic::InjectHooks();
    CStuckCarCheck::InjectHooks();
    CUpsideDownCarCheck::InjectHooks();
    CCamera::InjectHooks();
    CMessages::InjectHooks();
    CGangWars::InjectHooks();
    CPlayerPedData::InjectHooks();
    CTimeCycle::InjectHooks();
    CSkidmarks::InjectHooks();
    CMovingThings::InjectHooks();
    CRoadBlocks::InjectHooks();
    CBridge::InjectHooks();
    CCranes::InjectHooks();
    CGridRef::InjectHooks();
    CShopping::InjectHooks();
    CInformFriendsEventQueue::InjectHooks();
    C3dMarkers::InjectHooks();
    CSpecialFX::InjectHooks();
    CFallingGlassPane::InjectHooks();
    CGlass::InjectHooks();
    CPedGroups::InjectHooks();
    CClock::InjectHooks();
    CClouds::InjectHooks();
    CCoronas::InjectHooks();
    CCustomCarPlateMgr::InjectHooks();
    CDraw::InjectHooks();
    CEntryExitManager::InjectHooks();
    CEntryExit::InjectHooks();
    CInformGroupEventQueue::InjectHooks();
    CGangs::InjectHooks();
    CPlayerInfo::InjectHooks();
    CReplay::InjectHooks();
    CDarkel::InjectHooks();
    CGeneral::InjectHooks();
    CGamma::InjectHooks();
    CHudColours::InjectHooks();
    CTxdStore::InjectHooks();
    CCarEnterExit::InjectHooks();
    CEntityScanner::InjectHooks();
    CPedType::InjectHooks();
    CAcquaintance::InjectHooks();
    CWeather::InjectHooks();
    CPathFind::InjectHooks();
    CPathNode::InjectHooks();
    CNodeRoute::InjectHooks();
    CLoadMonitor::InjectHooks();
    CPlantMgr::InjectHooks();
    CDecisionMakerTypes::InjectHooks();
    CDecisionMakerTypesFileLoader::InjectHooks();
    CPedStats::InjectHooks();
    CCarGenerator::InjectHooks();
    CTheCarGenerators::InjectHooks();
    CCullZones::InjectHooks();
    CSpecialPlateHandler::InjectHooks();
    CKeyGen::InjectHooks();
    CAccidentManager::InjectHooks();
    CStuntJumpManager::InjectHooks();
    CLocalisation::InjectHooks();
    CSimpleVariablesSaveStructure::InjectHooks();
    CPedGeometryAnalyser::InjectHooks();
    NodeNamePlugin::InjectHooks();
    JPegPlugin::InjectHooks();
    PipelinePlugin::InjectHooks();
    CCollisionPlugin::InjectHooks();
    BreakablePlugin::InjectHooks();
    CIplStore::InjectHooks();
    cHandlingDataMgr::InjectHooks();
    CLoadingScreen::InjectHooks();
    CRadar::InjectHooks();
    CText::InjectHooks();
    ModelIndices::InjectHooks();
    CWaterCannons::InjectHooks();
    CWaterCannon::InjectHooks();
    CSprite::InjectHooks();
    CPlaneTrail::InjectHooks();
    CPlaneTrails::InjectHooks();

    CCustomBuildingPipeline::InjectHooks();
    CCustomBuildingRenderer::InjectHooks();
    CCustomBuildingDNPipeline::InjectHooks();
    CCustomCarEnvMapPipeline::InjectHooks();

    const auto Audio = []() {
        CAEVehicleAudioEntity::InjectHooks();
        CAESoundManager::InjectHooks();
        CAESound::InjectHooks();
        CAEAudioHardware::InjectHooks();
        CAEAudioEnvironment::InjectHooks();
        CAEAudioUtility::InjectHooks();
        CAEAudioChannel::InjectHooks();
        CAEStaticChannel::InjectHooks();
        CAESmoothFadeThread::InjectHooks();
        CAEDataStream::InjectHooks();
        CAEStreamingDecoder::InjectHooks();
        CAEMFDecoder::InjectHooks();
        CAEUserRadioTrackManager::InjectHooks();
        CAEVorbisDecoder::InjectHooks();
        CAEWaveDecoder::InjectHooks();
        CAEWMADecoder::InjectHooks();
        CAEWaterCannonAudioEntity::InjectHooks();
        CAETwinLoopSoundEntity::InjectHooks();
        CAEDoorAudioEntity::InjectHooks();
        CAEWeatherAudioEntity::InjectHooks();
        CAEStreamThread::InjectHooks();
        CAEFrontendAudioEntity::InjectHooks();
        CAEWeaponAudioEntity::InjectHooks();
        CAEScriptAudioEntity::InjectHooks();
        CAERadioTrackManager::InjectHooks();
        CAEAmbienceTrackManager::InjectHooks();
        CAECutsceneTrackManager::InjectHooks();
        CAECollisionAudioEntity::InjectHooks();
        CAEGlobalWeaponAudioEntity::InjectHooks();
        CAEPedAudioEntity::InjectHooks();
        CAEPedlessSpeechAudioEntity::InjectHooks();
        CAEPoliceScannerAudioEntity::InjectHooks();
        CAudioEngine::InjectHooks();
        CAEFireAudioEntity::InjectHooks();
        CAEExplosionAudioEntity::InjectHooks();
    };

    const auto Tasks = []() {
        CTaskGangHasslePed::InjectHooks();
        CTaskGangHassleVehicle::InjectHooks();
        CTaskGoToVehicleAndLean::InjectHooks();
        // CTaskInteriorBeInHouse::InjectHooks();
        // CTaskInteriorBeInOffice::InjectHooks();
        // CTaskInteriorBeInShop::InjectHooks();
        // CTaskInteriorGoToInfo::InjectHooks();
        // CTaskInteriorLieInBed::InjectHooks();
        // CTaskInteriorShopKeeper::InjectHooks();
        // CTaskInteriorSitAtDesk::InjectHooks();
        // CTaskInteriorSitInChair::InjectHooks();
        // CTaskInteriorUseInfo::InjectHooks();
        CTaskLeanOnVehicle::InjectHooks();
        CTaskComplexCarSlowBeDraggedOut::InjectHooks();
        CTaskComplexCarSlowBeDraggedOutAndStandUp::InjectHooks();
        CTaskComplexDestroyCar__InjectHooks();
        // CTaskComplexDestroyCarArmed::InjectHooks();
        // CTaskComplexDestroyCarMelee::InjectHooks();
        CTaskComplexDieInCar::InjectHooks();
        // CTaskComplexDiveFromAttachedEntityAndGetUp::InjectHooks();
        CTaskComplexDragPedFromCar__InjectHooks();
        // CTaskComplexDrivePointRoute::InjectHooks();
        // CTaskComplexEnterCarAsDriverTimed::InjectHooks();
        // CTaskComplexEnterCarAsPassengerTimed::InjectHooks();
        // CTaskComplexEnterCarAsPassengerWait::InjectHooks();
        // CTaskComplexEvasiveCower::InjectHooks();
        // CTaskComplexEvasiveDiveAndGetUp::InjectHooks();
        // CTaskComplexEvasiveStep::InjectHooks();
        // CTaskComplexExtinguishFireOnFoot::InjectHooks();
        // CTaskComplexExtinguishFires::InjectHooks();
        // CTaskComplexFallAndStayDown::InjectHooks();
        CTaskComplexFallToDeath::InjectHooks();
        // CTaskComplexFleeAnyMeans::InjectHooks();
        // CTaskComplexFleeEntity::InjectHooks();
        // CTaskComplexFleePoint::InjectHooks();
        // CTaskComplexFleeShooting::InjectHooks();
        // CTaskComplexFollowLeaderAnyMeans::InjectHooks();
        // CTaskComplexFollowNodeRouteShooting::InjectHooks();
        // CTaskComplexFollowPatrolRoute::InjectHooks();
        // CTaskComplexFollowPointRoute::InjectHooks();
        CTaskComplexGangFollower::InjectHooks();
        CTaskComplexGangJoinRespond::InjectHooks();
        CTaskComplexGangLeader::InjectHooks();
        CTaskComplexGetOnBoatSeat::InjectHooks();
        CTaskComplexGoToAttractor::InjectHooks();
        CTaskComplexGoToBoatSteeringWheel::InjectHooks();
        CTaskComplexGoToCarDoorAndStandStill::InjectHooks();
        CTaskComplexGoToPointAiming::InjectHooks();
        CTaskComplexGoToPointAndStandStillAndAchieveHeading::InjectHooks();
        CTaskComplexGoToPointAnyMeans::InjectHooks();
        CTaskComplexGoToPointShooting::InjectHooks();
        // CTaskComplexGoToPointUntilCollisionAndStandStill::InjectHooks();
        CTaskComplexGotoDoorAndOpen::InjectHooks();
        CTaskComplexHitByGunResponse::InjectHooks();
        CTaskComplexHitResponse::InjectHooks();
        // CTaskComplexInWater::InjectHooks();
        // CTaskComplexInvestigateDeadPed::InjectHooks();
        // CTaskComplexInvestigateDisturbance::InjectHooks();
        // CTaskComplexKillAllThreats::InjectHooks();
        // CTaskComplexKillCriminal::InjectHooks();
        // CTaskComplexKillPedGroupOnFoot::InjectHooks();
        // CTaskComplexKillPedOnFootArmed::InjectHooks();
        // CTaskComplexKillPedOnFootMelee::InjectHooks();
        // CTaskComplexKillPedOnFootStealth::InjectHooks();
        // CTaskComplexLeaveBoat::InjectHooks();
        // CTaskComplexLeaveCarAndDie::InjectHooks();
        // CTaskComplexLeaveCarAndFlee::InjectHooks();
        // CTaskComplexLeaveCarAndWander::InjectHooks();
        // CTaskComplexLeaveCarAsPassengerWait::InjectHooks();
        // CTaskComplexMoveBackAndJump::InjectHooks();
        // CTaskComplexOnFire::InjectHooks();
        // CTaskComplexOpenDriverDoor::InjectHooks();
        // CTaskComplexOpenPassengerDoor::InjectHooks();
        // CTaskComplexPassObject::InjectHooks();
        // CTaskComplexPresentIDToCop::InjectHooks();
        // CTaskComplexReactToAttack::InjectHooks();
        // CTaskComplexReactToGunAimedAt::InjectHooks();
        // CTaskComplexRoadRage::InjectHooks();
        // CTaskComplexScreamInCarThenLeave::InjectHooks();
        // CTaskComplexSeekCoverUntilTargetDead::InjectHooks();
        // CTaskComplexSeekEntity<CEntitySeekPosCalculator>::InjectHooks();
        // CTaskComplexSeekEntity<CEntitySeekPosCalculatorDriving>::InjectHooks();
        // CTaskComplexSeekEntity<CEntitySeekPosCalculatorEntitySurface>::InjectHooks();
        // CTaskComplexSeekEntity<CEntitySeekPosCalculatorFixedPos>::InjectHooks();
        // CTaskComplexSeekEntity<CEntitySeekPosCalculatorRadiusAngleOffset>::InjectHooks();
        // CTaskComplexSeekEntity<CEntitySeekPosCalculatorStandard>::InjectHooks();
        // CTaskComplexSeekEntity<CEntitySeekPosCalculatorVehicleId>::InjectHooks();
        // CTaskComplexSeekEntity<CEntitySeekPosCalculatorXYOffset>::InjectHooks();
        // CTaskComplexSeekEntityAiming::InjectHooks();
        // CTaskComplexSeekEntityAnyMeans<CEntitySeekPosCalculatorXYOffset>::InjectHooks();
        // CTaskComplexShuffleSeats::InjectHooks();
        // CTaskComplexSignalAtPed::InjectHooks();
        // CTaskComplexSitDownThenIdleThenStandUp::InjectHooks();
        CTaskComplexSmartFleeEntity::InjectHooks();
        // CTaskComplexSmartFleePoint::InjectHooks();
        // CTaskComplexStareAtPed::InjectHooks();
        // CTaskComplexStealCar::InjectHooks();
        // CTaskComplexTrackEntity::InjectHooks();
        CTaskComplexTurnToFaceEntityOrCoord::InjectHooks();
        // CTaskComplexUseAttractor::InjectHooks();
        // CTaskComplexUseAttractorPartner::InjectHooks();
        // CTaskComplexUseClosestFreeScriptedAttractor::InjectHooks();
        // CTaskComplexUseClosestFreeScriptedAttractorRun::InjectHooks();
        // CTaskComplexUseClosestFreeScriptedAttractorSprint::InjectHooks();
        // CTaskComplexUseEffect::InjectHooks();
        // CTaskComplexUseEffectRunning::InjectHooks();
        // CTaskComplexUseEffectSprinting::InjectHooks();
        // CTaskComplexUseEntryExit::InjectHooks();
        // CTaskComplexUsePairedAttractor::InjectHooks();
        // CTaskComplexUseScriptedAttractor::InjectHooks();
        // CTaskComplexUseScriptedBrain::InjectHooks();
        // CTaskComplexWaitAtAttractor::InjectHooks();
        // CTaskComplexWaitForBackup::InjectHooks();
        // CTaskComplexWaitForBus::InjectHooks();
        // CTaskComplexWaitForDryWeather::InjectHooks();
        // CTaskComplexWalkAlongsidePed::InjectHooks();
        // CTaskComplexWalkRoundBuildingAttempt::InjectHooks();
        // CTaskComplexWalkRoundFire::InjectHooks();
        // CTaskComplexWanderFlee::InjectHooks();
        // CTaskSimpleAffectSecondaryBehaviour::InjectHooks();
        CTaskSimpleArrestPed__InjectHooks();
        // CTaskSimpleBeHit::InjectHooks();
        // CTaskSimpleBeHitWhileMoving::InjectHooks();
        // CTaskSimpleBeKickedOnGround::InjectHooks();
        // CTaskSimpleBikeJacked::InjectHooks();
        // CTaskSimpleCarAlign::InjectHooks();
        // CTaskSimpleCarCloseDoorFromInside::InjectHooks();
        // CTaskSimpleCarCloseDoorFromOutside::InjectHooks();
        // CTaskSimpleCarFallOut::InjectHooks();
        // CTaskSimpleCarForcePedOut::InjectHooks();
        // CTaskSimpleCarGetIn::InjectHooks();
        // CTaskSimpleCarGetOut::InjectHooks();
        // CTaskSimpleCarGoToPointNearDoorUntilDoorNotInUse::InjectHooks();
        // CTaskSimpleCarJumpOut::InjectHooks();
        // CTaskSimpleCarOpenDoorFromOutside::InjectHooks();
        // CTaskSimpleCarOpenLockedDoorFromOutside::InjectHooks();
        // CTaskSimpleCarSetPedSlowDraggedOut::InjectHooks();
        // CTaskSimpleCarSetTempAction::InjectHooks();
        // CTaskSimpleCarShuffle::InjectHooks();
        // CTaskSimpleCarSlowBeDraggedOut::InjectHooks();
        // CTaskSimpleCarWaitForDoorNotToBeInUse::InjectHooks();
        // CTaskSimpleCarWaitToSlowDown::InjectHooks();
        // CTaskSimpleChat::InjectHooks();
        // CTaskSimpleClearLookAt::InjectHooks();
        // CTaskSimpleCower::InjectHooks();
        // CTaskSimpleDead::InjectHooks();
        // CTaskSimpleDetonate::InjectHooks();
        // + CTaskSimpleDieInCar
        // CTaskSimpleDoHandSignal::InjectHooks();
        CTaskSimpleDrown::InjectHooks();
        CTaskSimpleDrownInCar::InjectHooks();
        // CTaskSimpleDuckToggle::InjectHooks();
        // CTaskSimpleDuckWhileShotsWhizzing::InjectHooks();
        // CTaskSimpleEvasiveDive::InjectHooks();
        // CTaskSimpleEvasiveStep::InjectHooks();
        // CTaskSimpleFightingControl::InjectHooks();
        // CTaskSimpleFinishBrain::InjectHooks();
        // CTaskSimpleGunControl::InjectHooks();
        // CTaskSimpleHailTaxi::InjectHooks();
        // CTaskSimpleHailTaxiAndPause::InjectHooks();
        // CTaskSimpleHandsUp::InjectHooks();
        // CTaskSimpleHitByGunFromFront::InjectHooks();
        // CTaskSimpleHitByGunFromLeft::InjectHooks();
        // CTaskSimpleHitByGunFromRear::InjectHooks();
        // CTaskSimpleHitByGunFromRight::InjectHooks();
        // CTaskSimpleHitFromBack::InjectHooks();
        // CTaskSimpleHitFromBehind::InjectHooks();
        // CTaskSimpleHitFromFront::InjectHooks();
        // CTaskSimpleHitFromLeft::InjectHooks();
        // CTaskSimpleHitFromRight::InjectHooks();
        // CTaskSimpleHitWall::InjectHooks();
        // CTaskSimpleHurtPedWithCar::InjectHooks();
        // CTaskSimpleKillPedWithCar::InjectHooks();
        // CTaskSimpleLookAbout::InjectHooks();
        // CTaskSimpleOnEscalator::InjectHooks();
        // CTaskSimplePickUpBike::InjectHooks();
        // CTaskSimplePlayerOnFire::InjectHooks();
        // CTaskSimpleRunAnimLoopedMiddle::InjectHooks();
        // CTaskSimpleRunTimedAnim::InjectHooks();
        // CTaskSimpleSay::InjectHooks();
        // CTaskSimpleSetCharDecisionMaker::InjectHooks();
        // CTaskSimpleSetCharIgnoreWeaponRangeFlag::InjectHooks();
        // CTaskSimpleSetKindaStayInSamePlace::InjectHooks();
        // CTaskSimpleSetPedAsAutoDriver::InjectHooks();
        // CTaskSimpleShakeFist::InjectHooks();
        // CTaskSimpleSitDown::InjectHooks();
        // CTaskSimpleSitIdle::InjectHooks();
        // CTaskSimpleStandUp::InjectHooks();
        // CTaskSimpleThrowControl::InjectHooks();
        CTaskSimpleTired::InjectHooks();
        // CTaskSimpleTriggerEvent::InjectHooks();
        // CTaskSimpleTurn180::InjectHooks();
        // CTaskSimpleUseAtm::InjectHooks();
        // CTaskSimpleWaitForBus::InjectHooks();
        // CTaskSimpleWaitForPizza::InjectHooks();
        // CTaskSimpleWaitUntilAreaCodesMatch::InjectHooks();
        // CTaskSimpleWaitUntilLeaderAreaCodesMatch::InjectHooks();
        // CTaskSimpleWaitUntilPedIsInCar::InjectHooks();
        CTaskComplexAvoidEntity::InjectHooks();
        CTaskSimpleWaitUntilPedIsOutCar::InjectHooks();
        CTaskComplexSequence::InjectHooks();
        CTaskSimpleCarSlowDragPedOut::InjectHooks();
        CTaskManager::InjectHooks();
        CTaskSimpleCreateCarAndGetIn::InjectHooks();
        CTaskComplexEnterAnyCarAsDriver::InjectHooks();
        CTaskComplexLeaveAnyCar::InjectHooks();
        // CTaskSimpleAbseil::InjectHooks();
        CTaskComplexWanderCop::InjectHooks();
        // CTaskComplexUseMobilePhone::InjectHooks();
        CTaskSimpleStandStill::InjectHooks();
        CTaskSimpleCarDrive::InjectHooks();
        // CTaskSimpleScratchHead::InjectHooks();
        // CTaskSimpleChoking::InjectHooks();
        CTaskComplexPartnerChat::InjectHooks();
        CTaskSimpleUseGun::InjectHooks();
        // CTaskSimpleGangDriveBy::InjectHooks();
        CTaskComplexObserveTrafficLightsAndAchieveHeading::InjectHooks();
        CTaskSimpleInAir::InjectHooks();
        // CTaskComplexHitPedWithCar::InjectHooks();
        CTaskSimplePlayerOnFoot::InjectHooks();
        CTaskComplexFollowPedFootsteps::InjectHooks();
        CTaskComplexGetUpAndStandStill::InjectHooks();
        // CTaskComplexGoPickUpEntity::InjectHooks();
        CTaskSimpleDie__InjectHooks();
        CTaskSimpleDuck::InjectHooks();
        CTaskComplexPolicePursuit::InjectHooks();
        // CTaskSimpleFacial::InjectHooks();
        CTaskComplexCopInCar::InjectHooks();
        CTaskComplexFacial::InjectHooks();
        CTaskComplexInAirAndLand::InjectHooks();
        CTaskSimpleGetUp::InjectHooks();
        CTaskSimpleUninterruptable::InjectHooks();
        CTaskComplexFallAndGetUp::InjectHooks();
        CTaskComplexFollowNodeRoute::InjectHooks();
        CTaskComplexFollowLeaderInFormation::InjectHooks();
        // CTaskSimpleTriggerLookAt::InjectHooks();
        CTaskSimpleHitHead::InjectHooks();
        CTaskUtilityLineUpPedWithCar::InjectHooks();
        CTaskSimpleLand::InjectHooks();
        CTaskSimpleJetPack::InjectHooks();
        // + CTaskSimpleSetStayInSamePlace::InjectHooks();
        CTaskSimpleJump::InjectHooks();
        CTaskSimpleFall::InjectHooks();
        CTaskSimpleClimb::InjectHooks();
        // CTaskComplexPlayHandSignalAnim::InjectHooks();
        // CTaskComplexWaitForPed::InjectHooks();
        CTaskComplexJump::InjectHooks();
        // CTaskComplexWanderStandard::InjectHooks();
        // CTaskComplexSunbathe::InjectHooks();
        // CTaskComplexEnterCar::InjectHooks();
        // CTaskSimpleTogglePedThreatScanner::InjectHooks();
        CTaskComplexUseGoggles::InjectHooks();
        // CTaskComplexCrossRoadLookAndAchieveHeading::InjectHooks();
        CTaskComplexGoToPointAndStandStill::InjectHooks();
        // CTaskSimpleAchieveHeading::InjectHooks();
        CTaskSimpleGiveCPR::InjectHooks();
        // CTaskSimpleCarSetPedInAsPassenger::InjectHooks();
        CTaskComplexDriveFireTruck::InjectHooks();
        CTaskSimpleSwim::InjectHooks();
        CTaskComplexWalkRoundObject::InjectHooks();
        CTaskSimplePause::InjectHooks();
        // CTaskComplexEnterCarAsPassenger::InjectHooks();
        // + CTaskComplexEnterCarAsDriver::InjectHooks();
        // CTaskSimpleNone::InjectHooks();
        CTaskComplexKillPedOnFoot::InjectHooks();
        CTaskSimpleThrowProjectile::InjectHooks();
        CTaskSimpleGoToPoint::InjectHooks();
        // CTaskComplexWanderMedic::InjectHooks();
        // CTaskSimpleCarDriveTimed::InjectHooks();
        // CTaskComplexDriveWander::InjectHooks();
        CTaskSimpleStealthKill::InjectHooks();
        // CTaskSimpleCarSetPedOut::InjectHooks();
        CTaskSimpleAnim::InjectHooks();
        CTaskSimpleRunAnim::InjectHooks();
        // CTaskComplexWanderCriminal::InjectHooks();
        // CTaskComplexWanderProstitute::InjectHooks();
        CTaskComplexPartnerGreet::InjectHooks();
        // CTaskComplexWalkRoundCar::InjectHooks();
        // CTaskSimpleDuck::InjectHooks();
        CTaskComplexMedicTreatInjuredPed::InjectHooks();
        CTaskSimplePlayHandSignalAnim::InjectHooks();
        CTaskComplexCarDrive::InjectHooks();
        CTaskComplexCarDriveMission::InjectHooks();
        // CTaskComplexKillPedFromBoat::InjectHooks();
        // CTaskComplexLeaveCar::InjectHooks();
        CTaskComplexTreatAccident::InjectHooks();
        CTaskComplexGoToPointAndStandStillTimed::InjectHooks();
        CTaskComplexPartnerShove::InjectHooks();
        // CTaskSimpleRunNamedAnim::InjectHooks();
        // CTaskComplexProstituteSolicit::InjectHooks();
        CTaskComplexStuckInAir::InjectHooks();
        CTaskSimpleHoldEntity::InjectHooks();
        CTaskSimpleGoTo::InjectHooks();
        CTaskComplexPartner::InjectHooks();
        // CTaskSimpleCarSetPedInAsDriver::InjectHooks();
        CTaskComplexWander::InjectHooks();
        CTaskSimplePutDownEntity::InjectHooks();
        CTaskComplexUseSwatRope::InjectHooks();
        CTaskSimpleGoToPointFine::InjectHooks();
        CTaskSimpleIKChain::InjectHooks();
        CTaskSimpleIKManager::InjectHooks();
        CTaskSimpleIKPointArm::InjectHooks();
        CTaskSimpleIKLookAt::InjectHooks();
        CTaskComplexDie::InjectHooks();
        // CTaskComplexEnterBoatAsDriver::InjectHooks();
        CTaskSimpleFight::InjectHooks();
        CTaskComplexUseWaterCannon::InjectHooks();
        // CTaskComplexDriveToPoint::InjectHooks();
        // CTaskSimpleSlideToCoord::InjectHooks();
        // CTaskComplexPartnerDeal::InjectHooks();
        CTaskSimplePickUpEntity::InjectHooks();
        CTaskComplexBeInGroup::InjectHooks();
        // CTaskComplexBeCop::InjectHooks();
        CTaskComplexAvoidOtherPedWhileWandering::InjectHooks();
        CTaskComplexArrestPed::InjectHooks();

        const auto EntitySeekPosCalculators = [] {
            CEntitySeekPosCalculator::InjectHooks();
            CEntitySeekPosCalculatorStandard::InjectHooks();
            CEntitySeekPosCalculatorRadiusAngleOffset::InjectHooks();
            CEntitySeekPosCalculatorXYOffset::InjectHooks();
        };
        EntitySeekPosCalculators();
    };

    const auto Events = []() {
        CEvent::InjectHooks();
        CEventSeenPanickedPed::InjectHooks();
        CEventCarUpsideDown::InjectHooks();
        CEventPassObject::InjectHooks();
        CEventLeanOnVehicle::InjectHooks();
        CEventSeenCop::InjectHooks();
        CEventOnFire::InjectHooks();
        // + CEventRevived::InjectHooks();
        CEventHandlerHistory::InjectHooks();
        CEventEditableResponse::InjectHooks();
        CEventDamage::InjectHooks();
        CEventAttractor::InjectHooks();
        CEventScriptedAttractor::InjectHooks();
        CEventGunShot::InjectHooks();
        CEventGunShotWhizzedBy::InjectHooks();
        // + CEventGunAimedAt::InjectHooks();
        // + CEventDeath::InjectHooks();
        // + CEventDeadPed::InjectHooks();
        // + CEventDraggedOutCar::InjectHooks();
        // + CEventGotKnockedOverByCar::InjectHooks();
        CEventKnockOffBike::InjectHooks();
        CEventScriptCommand::InjectHooks();
        CEventSoundQuiet::InjectHooks();
        // + CEventPedToChase::InjectHooks();
        // + CEventPedToFlee::InjectHooks();
        CEventPotentialWalkIntoVehicle::InjectHooks();
        CEventPotentialWalkIntoObject::InjectHooks();
        CEventPotentialWalkIntoFire::InjectHooks();
        CEventPotentialWalkIntoPed::InjectHooks();
        CEventPedCollisionWithPed::InjectHooks();
        CEventPedCollisionWithPlayer::InjectHooks();
        CEventPlayerCollisionWithPed::InjectHooks();
        CEventObjectCollision::InjectHooks();
        CEventBuildingCollision::InjectHooks();
        CEventVehicleToSteal::InjectHooks();
        CEventVehicleDamage::InjectHooks();
        CEventVehicleDamageWeapon::InjectHooks();
        CEventVehicleDied::InjectHooks();
        CEventVehicleOnFire::InjectHooks();
        CEventVehicleHitAndRun::InjectHooks();
        CEventVehicleCollision::InjectHooks();
        CEventVehicleDamageCollision::InjectHooks();
        CEventHitByWaterCannon::InjectHooks();
        // + CEventInWater::InjectHooks();
        // + CEventCreatePartnerTask::InjectHooks();
        CEventInAir::InjectHooks();
        CEventStuckInAir::InjectHooks();
        CEventAcquaintancePed::InjectHooks();
        CEventLeaderEnteredCarAsDriver::InjectHooks();
        CEventLeaderExitedCarAsDriver::InjectHooks();
        CEventLeaderQuitEnteringCarAsDriver::InjectHooks();
        CEventAreaCodes::InjectHooks();
        CEventLeaderEntryExit::InjectHooks();
        // + CEventSpecial::InjectHooks();
        // + CEventFireNearby::InjectHooks();
        // + CEventGroupEvent::InjectHooks();
        CEventGroup::InjectHooks();
        CEventGlobalGroup::InjectHooks();
        CEventPlayerCommandToGroup::InjectHooks();
        CEventPlayerCommandToGroupAttack::InjectHooks();
        CEventPlayerCommandToGroupGather::InjectHooks();
        CEventDontJoinPlayerGroup::InjectHooks();
        CEventNewGangMember::InjectHooks();
        CEventEscalator::InjectHooks();
        CEventDanger::InjectHooks();
        // + CEventSexyVehicle::InjectHooks();
        // + CEventChatPartner::InjectHooks();
        CEventCopCarBeingStolen::InjectHooks();
        CEventHandler::InjectHooks();
        CEventAcquaintancePedHate::InjectHooks();
        CEventAcquaintancePedHateBadlyLit::InjectHooks();
        // + CEventInteriorUseInfo
        // + CEventLowAngerAtPlayer
        // + CEventPedEnteredMyVehicle
        // + CEventPotentialGetRunOver
        // + CEventPotentialWalkIntoBuilding::InjectHooks();
        // + CEventSexyPed
        // + CEventSignalAtPed
        // + CEventSoundLoud
        // - CEventSource::InjectHooks();
        // - CEventScanner::InjectHooks();
    };

    const auto Fx = []() {
        FxManager_c::InjectHooks();
        FxSystemBP_c::InjectHooks();
        // FxSystem_c::InjectHooks();
        FxPrimBP_c::InjectHooks();
    };

    const auto Vehicle = []() {
        CAutomobile::InjectHooks();
        CBike::InjectHooks();
        CBmx::InjectHooks();
        CBoat::InjectHooks();
        CHeli::InjectHooks();
        CMonsterTruck::InjectHooks();
        CPlane::InjectHooks();
        CQuadBike::InjectHooks();
        CTrailer::InjectHooks();
        CTrain::InjectHooks();
        CVehicle::InjectHooks();
    };

    const auto Interior = []() {
        FurnitureGroup_c::InjectHooks();
        FurnitureManager_c::InjectHooks();
        FurnitureSubGroup_c::InjectHooks();
        Interior_c::InjectHooks();
        InteriorGroup_c::InjectHooks();
        InteriorManager_c::InjectHooks();
    };

    const auto Scripts = []() {
        CRunningScript::InjectHooks();
        CTheScripts::InjectHooks();
        CStreamedScripts::InjectHooks();
        CScripted2dEffects::InjectHooks();
        CScriptResourceManager::InjectHooks();
    };

    const auto App = []() {
        VideoPlayer::InjectHooks();
        Securom::InjectHooks();
        Win32InjectHooks();
        RsInjectHooks();
        PsInjectHooks();
        RwHelperInjectHooks();
        AppInjectHooks();
        AppInputInjectHooks();
        AppLightInjectHooks();
        WinInput::InjectHooks();
    };

    const auto Animation = []() {
        //CAnimBlendAssocGroup::InjectHooks();
        CAnimBlendAssociation::InjectHooks();
        CAnimBlendClumpData::InjectHooks();
        CAnimBlendHierarchy::InjectHooks();
        CAnimBlendNode::InjectHooks();
        CAnimBlendSequence::InjectHooks();
        CAnimBlendStaticAssociation::InjectHooks();
        CAnimManager::InjectHooks();
    };

    App();
    Audio();
    Tasks();
    Events();
    Fx();
    Vehicle();
    Scripts();
}

void InjectHooksMain(HMODULE hThisDLL) {
    ReversibleHooks::OnInjectionBegin(hThisDLL);
    InjectHooksMain();
    ReversibleHooks::OnInjectionEnd();
}
