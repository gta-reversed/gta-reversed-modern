#include "StdInc.h"

#include "CSimpleVariablesSaveStructure.h"

// Audio
#include "CAEAudioChannel.h"
#include "CAEAudioEnvironment.h"
#include "CAEAudioHardware.h"
#include "CAEAudioUtility.h"
#include "CAEDataStream.h"
#include "CAEMFDecoder.h"
#include "CAESmoothFadeThread.h"
#include "CAESoundManager.h"
#include "CAEStaticChannel.h"
#include "CAEVorbisDecoder.h"
#include "CAEWaveDecoder.h"
#include "CAEWMADecoder.h"
#include "CAEStreamingDecoder.h"
#include "CAEUserRadioTrackManager.h"
#include "CAEWaterCannonAudioEntity.h"
#include "CAEDoorAudioEntity.h"

#include "CDebugMenu.h"

#include "CCarGenerator.h"
#include "CTheCarGenerators.h"
#include "CRadar.h"
#include "CWaterCannons.h"

void WaitForDebugger() {
    while (!::IsDebuggerPresent()) {
        printf("Debugger not present\n");
        ::Sleep(100);
    }
}

void InjectHooksMain()
{
    // WaitForDebugger();

    CDebug::InjectHooks();
    InjectCommonHooks();
    CGame::InjectHooks();
    CPools::InjectHooks();
    CControllerState::InjectHooks();
    CKeyboardState::InjectHooks();
    CMouseControllerState::InjectHooks();
    CPad::InjectHooks();
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
    CRunningScript::InjectHooks();
    CTheScripts::InjectHooks();
    CStreamingInfo::InjectHooks();
    CStreaming::InjectHooks();
    InjectCdStreamHooks();
    CReferences::InjectHooks();
    CPopulation::InjectHooks();
    CModelInfo::InjectHooks();
    CModelInfoAccelerator::InjectHooks();
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
    CFileLoader::InjectHooks();
    CFileMgr::InjectHooks();
    CPlaceable::InjectHooks();
    CEntity::InjectHooks();;
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
    CTrain::InjectHooks();
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
    CAnimBlendAssociation::InjectHooks();
    CAnimBlendSequence::InjectHooks();
    CTrafficLights::InjectHooks();
    CMotionBlurStreaks::InjectHooks();
    CRegisteredMotionBlurStreak::InjectHooks();
    CCover::InjectHooks();
    CVehicleAnimGroup::InjectHooks();
    CVehicleAnimGroupData::InjectHooks();
    CEvent::InjectHooks();
    CEventSeenPanickedPed::InjectHooks();
    CEventCarUpsideDown::InjectHooks();
    CEventPassObject::InjectHooks();
    CEventLeanOnVehicle::InjectHooks();
    CEventSeenCop::InjectHooks();
    CEventOnFire::InjectHooks();
    CEventRevived::InjectHooks();
    CEventHandlerHistory::InjectHooks();
    CEventEditableResponse::InjectHooks();
    CEventDamage::InjectHooks();
    CEventAttractor::InjectHooks();
    CEventScriptedAttractor::InjectHooks();
    CEventGunShot::InjectHooks();
    CEventGunShotWhizzedBy::InjectHooks();
    CEventGunAimedAt::InjectHooks();
    CEventDeath::InjectHooks();
    CEventDeadPed::InjectHooks();
    CEventDraggedOutCar::InjectHooks();
    CEventGotKnockedOverByCar::InjectHooks();
    CEventKnockOffBike::InjectHooks();
    CEventScriptCommand::InjectHooks();
    CEventSoundQuiet::InjectHooks();
    CEventPedToChase::InjectHooks();
    CEventPedToFlee::InjectHooks();
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
    CEventInWater::InjectHooks();
    CEventCreatePartnerTask::InjectHooks();
    CEventInAir::InjectHooks();
    CEventStuckInAir::InjectHooks();
    CEventAcquaintancePed::InjectHooks();
    CEventLeaderEnteredCarAsDriver::InjectHooks();
    CEventLeaderExitedCarAsDriver::InjectHooks();
    CEventLeaderQuitEnteringCarAsDriver::InjectHooks();
    CEventAreaCodes::InjectHooks();
    CEventLeaderEntryExit::InjectHooks();
    CEventSpecial::InjectHooks();
    CEventFireNearby::InjectHooks();
    CEventGroupEvent::InjectHooks();
    CEventGroup::InjectHooks();
    CEventGlobalGroup::InjectHooks();
    CEventPlayerCommandToGroup::InjectHooks();
    CEventPlayerCommandToGroupAttack::InjectHooks();
    CEventPlayerCommandToGroupGather::InjectHooks();
    CEventDontJoinPlayerGroup::InjectHooks();
    CEventNewGangMember::InjectHooks();
    CEventEscalator::InjectHooks();
    CEventDanger::InjectHooks();
    CEventSexyVehicle::InjectHooks();
    CEventChatPartner::InjectHooks();
    CEventCopCarBeingStolen::InjectHooks();
    CPedDamageResponseCalculator::InjectHooks();
    CPedScriptedTaskRecord::InjectHooks();
    CPedScriptedTaskRecordData::InjectHooks();
    CPedClothesDesc::InjectHooks();
    CScriptedBrainTaskStore::InjectHooks();
    CTaskManager::InjectHooks();
    CTaskComplexUseSequence::InjectHooks();
    CTaskComplexSequence::InjectHooks();
    CTaskComplexWander::InjectHooks();
    CTaskComplexWanderCop::InjectHooks();
    CTaskComplexPartner::InjectHooks();
    CTaskComplexPartnerChat::InjectHooks();
    CTaskComplexPartnerDeal::InjectHooks();
    CTaskComplexPartnerGreet::InjectHooks();
    CTaskComplexPartnerShove::InjectHooks();
    CTaskSimplePlayerOnFoot::InjectHooks();
    CTaskSimpleSwim::InjectHooks();
    CTaskSimpleGoTo::InjectHooks();
    CTaskSimpleGoToPoint::InjectHooks();
    CTaskSimpleGoToPointFine::InjectHooks();
    CTaskSimpleStandStill::InjectHooks();
    CTaskSimpleAnim::InjectHooks();
    CTaskSimplePlayHandSignalAnim::InjectHooks();
    CTaskComplexGoToPointAndStandStill::InjectHooks();
    CTaskComplexGoToPointAndStandStillTimed::InjectHooks();
    CTaskComplexAvoidOtherPedWhileWandering::InjectHooks();
    CTaskComplexWalkRoundObject::InjectHooks();
    CTaskComplexFollowPedFootsteps::InjectHooks();
    CTaskComplexKillPedOnFoot::InjectHooks();
    CTaskComplexArrestPed::InjectHooks();
    CTaskSimplePause::InjectHooks();
    CTaskSimpleHoldEntity::InjectHooks();
    CTaskSimplePutDownEntity::InjectHooks();
    CTaskSimplePickUpEntity::InjectHooks();
    CTaskSimpleStealthKill::InjectHooks();
    CTimer::InjectHooks();
    CTagManager::InjectHooks();
    CWaterLevel::InjectHooks();
    cBuoyancy::InjectHooks();
    CWanted::InjectHooks();
    CWeapon::InjectHooks();
    CWorld::InjectHooks();
    cTransmission::InjectHooks();
    CVehicle::InjectHooks();
    CAutomobile::InjectHooks();
    CBike::InjectHooks();
    CBoat::InjectHooks();
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
    CGlass::InjectHooks();
    CPedGroups::InjectHooks();
    CClock::InjectHooks();
    CClouds::InjectHooks();
    CCoronas::InjectHooks();
    CCustomCarPlateMgr::InjectHooks();
    CDraw::InjectHooks();
    CEntryExitManager::InjectHooks();
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
    CTaskComplexMedicTreatInjuredPed::InjectHooks();
    CTaskComplexTreatAccident::InjectHooks();
    CTaskSimpleGiveCPR::InjectHooks();
    CTaskComplexDriveFireTruck::InjectHooks();
    CTaskComplexUseWaterCannon::InjectHooks();
    CTaskSimpleRunAnim::InjectHooks();
    CTaskComplexUseSwatRope::InjectHooks();
    CStuntJumpManager::InjectHooks();
    CLocalisation::InjectHooks();
    CSimpleVariablesSaveStructure::InjectHooks();
    CPedGeometryAnalyser::InjectHooks();
    CPlane::InjectHooks();
    CHeli::InjectHooks();
    CBmx::InjectHooks();
    CTrailer::InjectHooks();
    CQuadBike::InjectHooks();
    NodeNamePlugin::InjectHooks();
    JPegPlugin::InjectHooks();
    PipelinePlugin::InjectHooks();
    CCollisionPlugin::InjectHooks();
    CIplStore::InjectHooks();
    cHandlingDataMgr::InjectHooks();
    CLoadingScreen::InjectHooks();
    CRadar::InjectHooks();
    CText::InjectHooks();
    CTaskSimpleUninterruptable::InjectHooks();
    CTaskSimpleSetStayInSamePlace::InjectHooks();
    CTaskSimpleGetUp::InjectHooks();
    CTaskComplexGetUpAndStandStill::InjectHooks();
    CTaskSimpleFall::InjectHooks();
    CTaskComplexFallAndGetUp::InjectHooks();
    CTaskSimpleJump::InjectHooks();
    CTaskSimpleInAir::InjectHooks();
    CTaskSimpleLand::InjectHooks();
    CTaskSimpleClimb::InjectHooks();
    CTaskSimpleHitHead::InjectHooks();
    CTaskComplexInAirAndLand::InjectHooks();
    CTaskComplexJump::InjectHooks();
    ModelIndices::InjectHooks();
    CWaterCannons::InjectHooks();

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
}
