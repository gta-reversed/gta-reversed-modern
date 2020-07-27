#include "StdInc.h"
#include "CAEAudioUtility.h"
#include "CAEDataStream.h"
#include "CAEMFDecoder.h"
#include "CAEVorbisDecoder.h"
#include "CAEWaveDecoder.h"
#include "CAEWMADecoder.h"
#include "CAEStreamingDecoder.h"
#include "CAEUserRadioTrackManager.h"
#include "CDebugMenu.h"

void InjectHooksMain(void)
{
    InjectCommonHooks();
    CGame::InjectHooks();
    CPad::InjectHooks();
    CRunningScript::InjectHooks();
    CStreaming::InjectHooks();
    InjectCdStreamHooks();
    CVehicleModelInfo::InjectHooks();
    CFileLoader::InjectHooks();
    CFileMgr::InjectHooks();
    CPhysical::InjectHooks();
    CRenderer::InjectHooks();
    CVisibilityPlugins::InjectHooks();
    CPed::InjectHooks();
    CPedIntelligence::InjectHooks();
    CTrain::InjectHooks();
    CAnimBlendAssociation::InjectHooks();
    CEventEditableResponse::InjectHooks();
    CEventDamage::InjectHooks();
    CEventAttractor::InjectHooks();
    CEventGunShot::InjectHooks();
    CEventDeath::InjectHooks();
    CEventDeadPed::InjectHooks();
    CEventDraggedOutCar::InjectHooks();
    CEventGotKnockedOverByCar::InjectHooks();
    CEventScriptCommand::InjectHooks();
    CEventSoundQuiet::InjectHooks();
    CEventGroupEvent::InjectHooks();
    CEventGunAimedAt::InjectHooks();
    CEventPedToChase::InjectHooks();
    CEventPedToFlee::InjectHooks();
    CEventVehicleToSteal::InjectHooks();
    CEventVehicleDamage::InjectHooks();
    CEventVehicleDamageWeapon::InjectHooks();
    CEventVehicleDied::InjectHooks();
    CEventVehicleOnFire::InjectHooks();
    CEventVehicleHitAndRun::InjectHooks();
    CEventVehicleCollision::InjectHooks();
    CEventVehicleDamageCollision::InjectHooks();
    CEventGroup::InjectHooks();
    CEventGlobalGroup::InjectHooks();
    CPedDamageResponseCalculator::InjectHooks();
    CPedScriptedTaskRecord::InjectHooks();
    CPedScriptedTaskRecordData::InjectHooks();
    CScriptedBrainTaskStore::InjectHooks();
    CTaskManager::InjectHooks();
    CTaskComplexUseSequence::InjectHooks();
    CTaskComplexSequence::InjectHooks();
    CTaskComplexWander::InjectHooks();
    CTaskComplexWanderCop::InjectHooks();
    CTaskSimplePlayerOnFoot::InjectHooks();
    CTaskSimpleSwim::InjectHooks();
    CTaskSimpleGoTo::InjectHooks();
    CTaskSimpleGoToPoint::InjectHooks();
    CTaskSimpleGoToPointFine::InjectHooks();
    CTaskSimpleStandStill::InjectHooks();
    CTaskComplexGoToPointAndStandStill::InjectHooks();
    CTaskComplexGoToPointAndStandStillTimed::InjectHooks();
    CTaskSimplePause::InjectHooks();
    CTaskSimpleHoldEntity::InjectHooks();
    CTaskSimplePutDownEntity::InjectHooks();
    CTaskSimplePickUpEntity::InjectHooks();
    CTaskSimpleStealthKill::InjectHooks();
    cBuoyancy::InjectHooks();
    CWanted::InjectHooks();
    CWeapon::InjectHooks();
    CVehicle::InjectHooks();
    CPlayerPed::InjectHooks();
    CStats::InjectHooks();
    CCarCtrl::InjectHooks();
    CTheZones::InjectHooks();
    CMenuManager::InjectHooks();
    CSprite2d::InjectHooks();
    CCheat::InjectHooks();

    CAEAudioUtility::InjectHooks();
    CAEDataStream::InjectHooks();
    CAEStreamingDecoder::InjectHooks();
    CAEMFDecoder::InjectHooks();
    CAEUserRadioTrackManager::InjectHooks();
    CAEVorbisDecoder::InjectHooks();
    CAEWaveDecoder::InjectHooks();
    CAEWMADecoder::InjectHooks();
}
