#include "StdInc.h"

#include "AudioEngine.h"

#include "AEAudioHardware.h"
#include "AEAmbienceTrackManager.h"
#include "AECutsceneTrackManager.h"

#include "AEUserRadioTrackManager.h"
#include "AEAudioUtility.h"

CAudioEngine& AudioEngine = *(CAudioEngine*)0xB6BC90;

void CAudioEngine::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("CAudioEngine", "CAudioEngine", 0x507670, &CAudioEngine::CAudioEngine);   default
    // Install("CAudioEngine", "~CAudioEngine", 0x506CD0, &CAudioEngine::~CAudioEngine); default
    Install("CAudioEngine", "Initialise", 0x5B9C60, &CAudioEngine::Initialise);
    Install("CAudioEngine", "Shutdown", 0x507CB0, &CAudioEngine::Shutdown);
    Install("CAudioEngine", "Restart", 0x506DB0, &CAudioEngine::Restart);
    Install("CAudioEngine", "ResetStatistics", 0x506DA0, &CAudioEngine::ResetStatistics);
    Install("CAudioEngine", "ResetSoundEffects", 0x507C30, &CAudioEngine::ResetSoundEffects);
    Install("CAudioEngine", "Reset", 0x507A90, &CAudioEngine::Reset);
    Install("CAudioEngine", "IsAmbienceRadioActive", 0x507280, &CAudioEngine::IsAmbienceRadioActive);
    Install("CAudioEngine", "DoesAmbienceTrackOverrideRadio", 0x507270, &CAudioEngine::DoesAmbienceTrackOverrideRadio);
    Install("CAudioEngine", "StopAmbienceTrack", 0x507220, &CAudioEngine::StopAmbienceTrack);
    Install("CAudioEngine", "IsAmbienceTrackActive", 0x507210, &CAudioEngine::IsAmbienceTrackActive);
    Install("CAudioEngine", "PauseBeatTrack", 0x507200, &CAudioEngine::PauseBeatTrack);
    Install("CAudioEngine", "RetuneRadio", 0x507E10, &CAudioEngine::RetuneRadio);
    Install("CAudioEngine", "StartRadio", 0x507DF0, static_cast<void (CAudioEngine::*)(tVehicleAudioSettings*)>(&CAudioEngine::StartRadio));
    Install("CAudioEngine", "StartRadio_1", 0x507DC0, static_cast<void (CAudioEngine::*)(RadioStationId, int8)>(&CAudioEngine::StartRadio));
    Install("CAudioEngine", "ServiceLoadingTune", 0x5078A0, &CAudioEngine::ServiceLoadingTune);
    Install("CAudioEngine", "ResumeAllSounds", 0x507440, &CAudioEngine::ResumeAllSounds);
    Install("CAudioEngine", "PauseAllSounds", 0x507430, &CAudioEngine::PauseAllSounds);
    Install("CAudioEngine", "EnableEffectsLoading", 0x506E90, &CAudioEngine::EnableEffectsLoading);
    Install("CAudioEngine", "DisableEffectsLoading", 0x506E80, &CAudioEngine::DisableEffectsLoading);
    Install("CAudioEngine", "SetNonStreamFaderScalingFactor", 0x506E60, &CAudioEngine::SetNonStreamFaderScalingFactor);
    Install("CAudioEngine", "SetEffectsFaderScalingFactor", 0x506E50, &CAudioEngine::SetEffectsFaderScalingFactor);
    Install("CAudioEngine", "SetMusicFaderScalingFactor", 0x506E40, &CAudioEngine::SetMusicFaderScalingFactor);
    Install("CAudioEngine", "SetEffectsMasterVolume", 0x506E10, &CAudioEngine::SetEffectsMasterVolume);
    Install("CAudioEngine", "SetMusicMasterVolume", 0x506DE0, &CAudioEngine::SetMusicMasterVolume);
    Install("CAudioEngine", "SetStreamFaderScalingFactor", 0x506E70, &CAudioEngine::SetStreamFaderScalingFactor);
    Install("CAudioEngine", "SetRadioAutoRetuneOnOff", 0x506F80, &CAudioEngine::SetRadioAutoRetuneOnOff);
    Install("CAudioEngine", "SetRadioBassSetting", 0x506FA0, &CAudioEngine::SetRadioBassSetting);
    Install("CAudioEngine", "SetBassEnhanceOnOff", 0x506F90, &CAudioEngine::SetBassEnhanceOnOff);
    Install("CAudioEngine", "SetMissionAudioPosition", 0x507300, &CAudioEngine::SetMissionAudioPosition);
    Install("CAudioEngine", "GetBeatTrackStatus", 0x507170, &CAudioEngine::GetBeatTrackStatus);
    Install("CAudioEngine", "GetCutsceneTrackStatus", 0x507160, &CAudioEngine::GetCutsceneTrackStatus);
    Install("CAudioEngine", "IsCutsceneTrackActive", 0x507150, &CAudioEngine::IsCutsceneTrackActive);
    Install("CAudioEngine", "PlayPreloadedCutsceneTrack", 0x507070, &CAudioEngine::PlayPreloadedCutsceneTrack);
    Install("CAudioEngine", "IsVehicleRadioActive", 0x507050, &CAudioEngine::IsVehicleRadioActive);
    Install("CAudioEngine", "GetCurrentRadioStationID", 0x507040, &CAudioEngine::GetCurrentRadioStationID);
    Install("CAudioEngine", "StopRadio", 0x506F70, &CAudioEngine::StopRadio);
    Install("CAudioEngine", "DisplayRadioStationName", 0x507030, &CAudioEngine::DisplayRadioStationName);
    Install("CAudioEngine", "GetRadioStationNameKey", 0x507010, &CAudioEngine::GetRadioStationNameKey);
    Install("CAudioEngine", "GetRadioStationName", 0x507000, &CAudioEngine::GetRadioStationName);
    Install("CAudioEngine", "HasRadioRetuneJustStarted", 0x506FE0, &CAudioEngine::HasRadioRetuneJustStarted);
    Install("CAudioEngine", "IsRadioOn", 0x506FD0, &CAudioEngine::IsRadioOn);
    Install("CAudioEngine", "InitialiseRadioStationID", 0x506FC0, &CAudioEngine::InitialiseRadioStationID);
    Install("CAudioEngine", "GetRadioStationListenTimes", 0x507020, &CAudioEngine::GetRadioStationListenTimes);
    Install("CAudioEngine", "AttachMissionAudioToPhysical", 0x507330, &CAudioEngine::AttachMissionAudioToPhysical);
    Install("CAudioEngine", "AttachMissionAudioToObject", 0x507320, &CAudioEngine::AttachMissionAudioToObject);
    Install("CAudioEngine", "AttachMissionAudioToPed", 0x507310, &CAudioEngine::AttachMissionAudioToPed);
    Install("CAudioEngine", "ClearMissionAudio", 0x5072F0, &CAudioEngine::ClearMissionAudio);
    Install("CAudioEngine", "GetMissionAudioPosition", 0x5072E0, &CAudioEngine::GetMissionAudioPosition);
    Install("CAudioEngine", "GetMissionAudioEvent", 0x5072D0, &CAudioEngine::GetMissionAudioEvent);
    Install("CAudioEngine", "IsMissionAudioSampleFinished", 0x5072C0, &CAudioEngine::IsMissionAudioSampleFinished);
    Install("CAudioEngine", "PlayLoadedMissionAudio", 0x5072B0, &CAudioEngine::PlayLoadedMissionAudio);
    Install("CAudioEngine", "GetMissionAudioLoadingStatus", 0x5072A0, &CAudioEngine::GetMissionAudioLoadingStatus);
    Install("CAudioEngine", "PreloadMissionAudio", 0x507290, &CAudioEngine::PreloadMissionAudio);
    Install("CAudioEngine", "PreloadCutsceneTrack", 0x507E30, &CAudioEngine::PreloadCutsceneTrack);
    Install("CAudioEngine", "InitialisePostLoading", 0x5078F0, &CAudioEngine::InitialisePostLoading);
    Install("CAudioEngine", "IsBeatInfoPresent", 0x5071D0, &CAudioEngine::IsBeatInfoPresent);
    Install("CAudioEngine", "StartLoadingTune", 0x507410, &CAudioEngine::StartLoadingTune);
    Install("CAudioEngine", "SayPedless", 0x5073C0, &CAudioEngine::SayPedless);
    Install("CAudioEngine", "Service", 0x507750, &CAudioEngine::Service);
    Install("CAudioEngine", "GetBeatInfo", 0x5071B0, &CAudioEngine::GetBeatInfo);
    Install("CAudioEngine", "StopBeatTrack", 0x5071A0, &CAudioEngine::StopBeatTrack);
    Install("CAudioEngine", "PlayPreloadedBeatTrack", 0x507180, &CAudioEngine::PlayPreloadedBeatTrack);
    Install("CAudioEngine", "ReportWaterSplash_vec", 0x506F10, static_cast<void (CAudioEngine::*)(CVector, float)>(&CAudioEngine::ReportWaterSplash));
    Install("CAudioEngine", "ReportWaterSplash_phs", 0x506F00, static_cast<void (CAudioEngine::*)(CPhysical*, float, bool)>(&CAudioEngine::ReportWaterSplash));
    Install("CAudioEngine", "ReportGlassCollisionEvent", 0x506EE0, &CAudioEngine::ReportGlassCollisionEvent);
    Install("CAudioEngine", "ReportObjectDestruction", 0x506ED0, &CAudioEngine::ReportObjectDestruction);
    Install("CAudioEngine", "ReportBulletHit", 0x506EC0, &CAudioEngine::ReportBulletHit);
    Install("CAudioEngine", "ReportCollision", 0x506EB0, &CAudioEngine::ReportCollision);
    Install("CAudioEngine", "ReportFrontendAudioEvent", 0x506EA0, &CAudioEngine::ReportFrontendAudioEvent);
    Install("CAudioEngine", "ReportWeaponEvent", 0x506F40, &CAudioEngine::ReportWeaponEvent);
    Install("CAudioEngine", "ReportDoorMovement", 0x506F50, &CAudioEngine::ReportDoorMovement);
    Install("CAudioEngine", "ReportMissionAudioEvent_vec", 0x507340, static_cast<void (CAudioEngine::*)(uint16, CVector&)>(&CAudioEngine::ReportMissionAudioEvent));
    Install("CAudioEngine", "ReportMissionAudioEvent_obj", 0x507350, static_cast<void (CAudioEngine::*)(uint16, CObject*)>(&CAudioEngine::ReportMissionAudioEvent));
    Install("CAudioEngine", "ReportMissionAudioEvent_ped", 0x507370, static_cast<void (CAudioEngine::*)(uint16, CPed*)>(&CAudioEngine::ReportMissionAudioEvent));
    Install("CAudioEngine", "ReportMissionAudioEvent_veh", 0x507390, static_cast<void (CAudioEngine::*)(uint16, CVehicle*)>(&CAudioEngine::ReportMissionAudioEvent));
    Install("CAudioEngine", "ReportMissionAudioEvent_phs", 0x5073B0, static_cast<void (CAudioEngine::*)(uint16, CPhysical*, float, float)>(&CAudioEngine::ReportMissionAudioEvent));
    Install("CAudioEngine", "IsLoadingTuneActive", 0x506D90, &CAudioEngine::IsLoadingTuneActive);
    Install("CAudioEngine", "PreloadBeatTrack", 0x507F40, &CAudioEngine::PreloadBeatTrack);
    Install("CAudioEngine", "StopCutsceneTrack", 0x507080, &CAudioEngine::StopCutsceneTrack);
    Install("CAudioEngine", "IsRadioRetuneInProgress", 0x506FF0, &CAudioEngine::IsRadioRetuneInProgress);
}

// 0x5B9C60
bool CAudioEngine::Initialise() {
    CLoadingScreen::Pause();

    if (!AEAudioHardware.Initialise()) {
        return false;
    }

    m_nBackgroundAudioChannel = AEAudioHardware.AllocateChannels(1);

    if (!AERadioTrackManager.Initialise(m_nBackgroundAudioChannel)) {
        return false;
    }

    if (!AECutsceneTrackManager.Initialise(m_nBackgroundAudioChannel)) {
        return false;
    }

    if (!AEAmbienceTrackManager.Initialise(m_nBackgroundAudioChannel)) {
        return false;
    }

    if (!AESoundManager.Initialise()) {
        return false;
    }

    CAEAudioEntity::m_pAudioEventVolumes = new int8[45401];
    FILESTREAM file = CFileMgr::OpenFile("AUDIO\\CONFIG\\EVENTVOL.DAT", "r");
    if (!file) {
        return false;
    }
    if (CFileMgr::Read(file, CAEAudioEntity::m_pAudioEventVolumes, 45401) != 45401) {
        CFileMgr::CloseFile(file);
        return false;
    }
    CFileMgr::CloseFile(file);

    m_FrontendAE.Initialise();
    CAudioEngine::SetEffectsFaderScalingFactor(0.0);
    CAEAudioUtility::StaticInitialise();
    CAEPedAudioEntity::StaticInitialise();
    CAEPedSpeechAudioEntity::StaticInitialise();
    CAEVehicleAudioEntity::StaticInitialise();
    CAEExplosionAudioEntity::StaticInitialise();
    CAEWeatherAudioEntity::StaticInitialise();
    CAEDoorAudioEntity::StaticInitialise();
    CAEFireAudioEntity::StaticInitialise();
    CAEPoliceScannerAudioEntity::StaticInitialise();
    m_ScriptAE.Initialise();
    m_PedlessSpeechAE.Initialise();
    m_CollisionAE.Initialise();

    m_nCurrentRadioStationId = -1;
    field_0 = false;
    field_1 = false;

    CLoadingScreen::Continue();

    return true;
}

// 0x5078F0
void CAudioEngine::InitialisePostLoading() {
    m_FrontendAE.AddAudioEvent(AE_FRONTEND_LOADING_TUNE_STOP, 0.0f, 1.0f);
    AudioEngine.Service();
    CAECollisionAudioEntity::InitialisePostLoading();

    m_GlobalWeaponAE = new CAEGlobalWeaponAudioEntity();
    m_GlobalWeaponAE->Initialise();

    while ( !AEAudioHardware.IsSoundBankLoaded(39, SLOT_LOADING_TUNE_LEFT)
           || !AEAudioHardware.IsSoundBankLoaded(27, 3)
           || !AEAudioHardware.IsSoundBankLoaded(138, 19)
           || !AEAudioHardware.IsSoundBankLoaded(0, 41)
           || !AEAudioHardware.IsSoundBankLoaded(BANK_EXTRAS, SLOT_EXTRAS)
           || !AEAudioHardware.IsSoundBankLoaded(52, 4)
           || !AEAudioHardware.IsSoundBankLoaded(143, SLOT_LOADING_TUNE_RIGHT)
           || !AEAudioHardware.IsSoundBankLoaded(51, 31)
           || !AEAudioHardware.IsSoundBankLoaded(105, 6)
           || !AEAudioHardware.IsSoundBankLoaded(74, 17)
           || !AEAudioHardware.IsSoundBankLoaded(128, 32)
           || !AEAudioHardware.IsSoundBankLoaded(13, 18)
   ) {
        AEAudioHardware.Service();
    }
}

// 0x507CB0
void CAudioEngine::Shutdown() {
    if (AERadioTrackManager.IsRadioOn()) {
        AERadioTrackManager.StopRadio(nullptr, true);
    } else if (AEAmbienceTrackManager.IsAmbienceTrackActive()) {
        StopAmbienceTrack(true);
    } else if (AECutsceneTrackManager.IsCutsceneTrackActive()) {
        AECutsceneTrackManager.StopCutsceneTrack();
    }
    m_CollisionAE.Reset();
    AERadioTrackManager.Reset();
    m_FrontendAE.AddAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP_PAUSED, 0.0f, 1.0f);
    m_FrontendAE.AddAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP, 0.0f, 1.0f);
    m_FrontendAE.Reset();
    m_ScriptAE.Reset();
    CAEWeatherAudioEntity::StaticReset();
    CAEPedSpeechAudioEntity::Reset();
    delete m_GlobalWeaponAE;
    AESoundManager.Reset();
    AESoundManager.Terminate();
    AEAudioHardware.Terminate();

    delete[] CAEAudioEntity::m_pAudioEventVolumes;
    CAEAudioEntity::m_pAudioEventVolumes = nullptr;

    AEUserRadioTrackManager.Shutdown();
}

// 0x506EB0
void CAudioEngine::ReportCollision(CEntity* entity1, CEntity* entity2, uint8 surface1, uint8 surface2, CVector& point, CVector* normal, float fCollisionImpact1, float fCollisionImpact2, bool playOnlyOneShotCollisionSound, bool unknown) {
    m_CollisionAE.ReportCollision(entity1, entity2, surface1, surface2, point, normal, fCollisionImpact1, fCollisionImpact2, playOnlyOneShotCollisionSound, unknown);
}

// 0x507350
void CAudioEngine::ReportMissionAudioEvent(uint16 eventId, CObject* object) {
    m_ScriptAE.ReportMissionAudioEvent(static_cast<eAudioEvents>(eventId), object, 0, 1.0f);
}

// 0x506F40
void CAudioEngine::ReportWeaponEvent(int32 audioEvent, eWeaponType weaponType, CPhysical* physical) {
    m_GlobalWeaponAE->AddAudioEvent(static_cast<eAudioEvents>(audioEvent), weaponType, physical);
}

// 0x506F50
void CAudioEngine::ReportDoorMovement(CPhysical* physical) {
    m_DoorAE.AddAudioEvent(AE_ENTRY_EXIT_DOOR_MOVING, physical);
}

// 0x506ED0
void CAudioEngine::ReportObjectDestruction(CEntity* entity) {
    m_CollisionAE.ReportObjectDestruction(entity);
}

// 0x506F70
void CAudioEngine::StopRadio(tVehicleAudioSettings* settings, bool bDuringPause) {
    AERadioTrackManager.StopRadio(settings, bDuringPause);
}

// 0x507150
bool CAudioEngine::IsCutsceneTrackActive() {
    return AECutsceneTrackManager.IsCutsceneTrackActive();
}

// 0x507E10
void CAudioEngine::RetuneRadio(int8 radioId) {
    if (!GetBeatTrackStatus())
        AERadioTrackManager.RetuneRadio(radioId);
}

// 0x5072A0
int8 CAudioEngine::GetMissionAudioLoadingStatus(uint8 sampleId) {
    return m_ScriptAE.GetMissionAudioLoadingStatus(sampleId);
}

// 0x5072C0
bool CAudioEngine::IsMissionAudioSampleFinished(uint8 sampleId) {
    return m_ScriptAE.IsMissionAudioSampleFinished(sampleId);
}

// 0x507F40
void CAudioEngine::PreloadBeatTrack(int16 trackId) {
    if (AERadioTrackManager.IsRadioOn()) {
        m_nCurrentRadioStationId = AERadioTrackManager.GetCurrentRadioStationID();
        tVehicleAudioSettings* settings = CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio();
        AERadioTrackManager.StopRadio(settings, true);
        m_FrontendAE.AddAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP, 0.0f, 1.0f);
        while (AERadioTrackManager.IsRadioOn()) {
            AERadioTrackManager.Service(AEAudioHardware.GetTrackPlayTime());
            AEAudioHardware.Service();
        }
    } else if (AEAmbienceTrackManager.IsAmbienceTrackActive()) {
        StopAmbienceTrack(true);
    } else {
        if (AECutsceneTrackManager.IsCutsceneTrackActive())
            AECutsceneTrackManager.StopCutsceneTrack();

        while (AECutsceneTrackManager.IsCutsceneTrackActive()) {
            AECutsceneTrackManager.Service(AEAudioHardware.GetTrackPlayTime());
            AEAudioHardware.Service();
        }
    }
    return AECutsceneTrackManager.PreloadBeatTrack(trackId, false);
}

// 0x507200
void CAudioEngine::PauseBeatTrack(bool pause) {
    AECutsceneTrackManager.PauseTrack(pause);
}

bool CAudioEngine::IsLoadingTuneActive() {
    return m_FrontendAE.IsLoadingTuneActive();
}

// 0x506DA0
void CAudioEngine::ResetStatistics() {
    CAERadioTrackManager::ResetStatistics();
}

// 0x506DB0
void CAudioEngine::Restart() {
    AESoundManager.PauseManually(false);
}

// 0x506DE0
void CAudioEngine::SetMusicMasterVolume(int8 volume) {
    AEAudioHardware.SetMusicMasterScalingFactor(static_cast<float>(volume) / 64.0f);
}

// 0x506E10
void CAudioEngine::SetEffectsMasterVolume(int8 volume) {
    AEAudioHardware.SetEffectsMasterScalingFactor(static_cast<float>(volume) / 64.0f);
}

// 0x506E40
void CAudioEngine::SetMusicFaderScalingFactor(float factor) {
    AEAudioHardware.SetMusicFaderScalingFactor(factor);
}

void CAudioEngine::SetEffectsFaderScalingFactor(float factor) {
    AEAudioHardware.SetEffectsFaderScalingFactor(factor);
}

// 0x506E60
void CAudioEngine::SetNonStreamFaderScalingFactor(float factor) {
    AEAudioHardware.SetNonStreamFaderScalingFactor(factor);
}

// 0x506E70
void CAudioEngine::SetStreamFaderScalingFactor(float factor) {
    AEAudioHardware.SetStreamFaderScalingFactor(factor);
}
// 0x506E90
void CAudioEngine::EnableEffectsLoading() {
    AEAudioHardware.EnableEffectsLoading();
}

// 0x506E80
void CAudioEngine::DisableEffectsLoading() {
    AEAudioHardware.DisableEffectsLoading();
}

// 0x506EA0
void CAudioEngine::ReportFrontendAudioEvent(eAudioEvents eventId, float volumeChange, float speed) {
    m_FrontendAE.AddAudioEvent(eventId, volumeChange, speed);
}

// 0x506EC0
void CAudioEngine::ReportBulletHit(CEntity* entity, uint8 surface, CVector& posn, float angleWithColPointNorm) {
    m_CollisionAE.ReportBulletHit(entity, surface, posn, angleWithColPointNorm);
}

// 0x506EE0
void CAudioEngine::ReportGlassCollisionEvent(eAudioEvents glassSoundType, CVector& posn) {
    m_CollisionAE.ReportGlassCollisionEvent(glassSoundType, posn, 0);
}

// 0x506F10
void CAudioEngine::ReportWaterSplash(CVector posn, float volume) {
    m_CollisionAE.ReportWaterSplash(posn, volume);
}

// 0x506F00
void CAudioEngine::ReportWaterSplash(CPhysical* physical, float volume, bool forcePlaySplashSound) {
    m_CollisionAE.ReportWaterSplash(physical, volume, forcePlaySplashSound);
}

// 0x507340
void CAudioEngine::ReportMissionAudioEvent(uint16 eventId, CVector& posn) {
    m_ScriptAE.ReportMissionAudioEvent(static_cast<eAudioEvents>(eventId), posn);
}

// 0x507370
void CAudioEngine::ReportMissionAudioEvent(uint16 eventId, CPed* ped) {
    m_ScriptAE.ReportMissionAudioEvent(static_cast<eAudioEvents>(eventId), ped, 0, 1.0f);
}

// 0x507390
void CAudioEngine::ReportMissionAudioEvent(uint16 eventId, CVehicle* vehicle) {
    m_ScriptAE.ReportMissionAudioEvent(static_cast<eAudioEvents>(eventId), vehicle, 0.0, 1.0f);
}

// 0x5073B0
void CAudioEngine::ReportMissionAudioEvent(uint16 eventId, CPhysical* physical, float a3, float a4) {
    m_ScriptAE.ReportMissionAudioEvent(static_cast<eAudioEvents>(eventId), physical, a3, a4);
}

// 0x507050
bool CAudioEngine::IsVehicleRadioActive() {
    return AERadioTrackManager.IsVehicleRadioActive();
}

// Used in III
// 0x507060
void CAudioEngine::PlayRadioAnnouncement(uint32 a1) {
    // NOP
}

void CAudioEngine::PreloadCutsceneTrack(int16 trackId, bool wait) {
    if (AERadioTrackManager.IsRadioOn()) {
        m_nCurrentRadioStationId = AERadioTrackManager.GetCurrentRadioStationID();
        tVehicleAudioSettings* settings = CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio();
        AERadioTrackManager.StopRadio(settings, true);
        m_FrontendAE.AddAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP, 0.0f, 1.0f);
        while (AERadioTrackManager.IsRadioOn()) {
            AERadioTrackManager.Service(AEAudioHardware.GetTrackPlayTime());
            AEAudioHardware.Service();
        }
    } else {
        if (AEAmbienceTrackManager.IsAmbienceTrackActive()) {
            StopAmbienceTrack(true);
            AECutsceneTrackManager.PreloadCutsceneTrack(trackId, wait);
            return;
        }

        if (AECutsceneTrackManager.IsCutsceneTrackActive())
            AECutsceneTrackManager.StopCutsceneTrack();

        while (AECutsceneTrackManager.IsCutsceneTrackActive()) {
            AECutsceneTrackManager.Service(AEAudioHardware.GetTrackPlayTime());
            AEAudioHardware.Service();
        }
    }

    AECutsceneTrackManager.PreloadCutsceneTrack(trackId, wait);
}

// 0x507070
void CAudioEngine::PlayPreloadedCutsceneTrack() {
    AECutsceneTrackManager.PlayPreloadedCutsceneTrack();
}

// 0x507080
void CAudioEngine::StopCutsceneTrack(bool a2) {
    AECutsceneTrackManager.StopCutsceneTrack();

    if (!a2) {
        if (!field_0)
            return;

        field_1 = true;
        field_0 = false;
        return;
    }

    while (AECutsceneTrackManager.IsCutsceneTrackActive()) {
        AECutsceneTrackManager.Service(AEAudioHardware.GetTrackPlayTime());
        AEAudioHardware.Service();
    }
    if (m_nCurrentRadioStationId < 0) {
        if (AERadioTrackManager.IsVehicleRadioActive()) {
            tVehicleAudioSettings* settings = CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio();
            AERadioTrackManager.StartRadio(settings);
            field_0 = false;
            return;
        }
        field_0 = false;
        return;
    }
    if (AERadioTrackManager.IsVehicleRadioActive())
        AERadioTrackManager.StartRadio(m_nCurrentRadioStationId, 0, 0, 0);
    m_nCurrentRadioStationId = -1;
    field_0 = false;
}

// 0x507180
void CAudioEngine::PlayPreloadedBeatTrack(bool a2) {
    AECutsceneTrackManager.PlayPreloadedCutsceneTrack();
    field_0 = a2;
}

// 0x5071A0
void CAudioEngine::StopBeatTrack() {
    StopCutsceneTrack(true);
}

// 0x5071B0
tBeatInfo* CAudioEngine::GetBeatInfo() {
    AEAudioHardware.GetBeatInfo(&m_BeatInfo);
    return &m_BeatInfo;
}

// win32
// 0x5071D0
bool CAudioEngine::IsBeatInfoPresent() {
    auto beatInfo = GetBeatInfo();
    return beatInfo && beatInfo->m_beatInfoPresent;
}

// 0x507210
bool CAudioEngine::IsAmbienceTrackActive() {
    return AEAmbienceTrackManager.IsAmbienceTrackActive();
}

// 0x507220
void CAudioEngine::StopAmbienceTrack(bool a1) {
    AEAmbienceTrackManager.StopAmbienceTrack();
    if (a1 && AEAmbienceTrackManager.IsAmbienceTrackActive()) {
        do {
            AEAmbienceTrackManager.Service(AEAudioHardware.GetTrackPlayTime());
            AEAudioHardware.Service();
        } while (AEAmbienceTrackManager.IsAmbienceTrackActive());
    }
}

// 0x507270
bool CAudioEngine::DoesAmbienceTrackOverrideRadio() {
    return AEAmbienceTrackManager.m_bStop;
}

// 0x507280
bool CAudioEngine::IsAmbienceRadioActive() {
    return AEAmbienceTrackManager.IsAmbienceRadioActive();
}

// 0x507290
void CAudioEngine::PreloadMissionAudio(uint8 sampleId, int32 a3) {
    m_ScriptAE.PreloadMissionAudio(sampleId, a3);
}

// 0x5072B0
void CAudioEngine::PlayLoadedMissionAudio(uint8 sampleId) {
    m_ScriptAE.PlayLoadedMissionAudio(sampleId);
}

// 0x5072D0
int32 CAudioEngine::GetMissionAudioEvent(uint8 sampleId) {
    return m_ScriptAE.GetMissionAudioEvent(sampleId);
}

// 0x5072E0
CVector* CAudioEngine::GetMissionAudioPosition(uint8 sampleId) {
    return m_ScriptAE.GetMissionAudioPosition(sampleId);
}

// 0x5072F0
void CAudioEngine::ClearMissionAudio(uint8 sampleId) {
    m_ScriptAE.ClearMissionAudio(sampleId);
}

// 0x507300
void CAudioEngine::SetMissionAudioPosition(uint8 sampleId, CVector& posn) {
    m_ScriptAE.SetMissionAudioPosition(sampleId, posn);
}

// 0x507310
CVector* CAudioEngine::AttachMissionAudioToPed(uint8 sampleId, CPed* ped) {
    return m_ScriptAE.AttachMissionAudioToPhysical(sampleId, ped);
}

// 0x507320
CVector* CAudioEngine::AttachMissionAudioToObject(uint8 sampleId, CObject* object) {
    return m_ScriptAE.AttachMissionAudioToPhysical(sampleId, object);
}

// 0x507330
CVector* CAudioEngine::AttachMissionAudioToPhysical(uint8 sampleId, CPhysical* physical) {
    return m_ScriptAE.AttachMissionAudioToPhysical(sampleId, physical);
}

// 0x5073C0
void CAudioEngine::SayPedless(int32 a1, int16 a2, CEntity* entity, uint32 playOffset, float a5, uint8 a6, uint8 a7, uint8 a8) {
    m_PedlessSpeechAE.AddSayEvent(a1, a2, entity, playOffset, a5, a6, a7, a8);
}

// unused
// 0x5073D0
void CAudioEngine::DisablePoliceScanner(uint8 a1, uint8 a2) {
    CAEPoliceScannerAudioEntity::DisableScanner(a1, a2);
}

// unused
// 0x5073F0
void CAudioEngine::EnablePoliceScanner() {
    CAEPoliceScannerAudioEntity::EnableScanner();
}

// 0x507400
void CAudioEngine::StopPoliceScanner(uint8 a1) {
    CAEPoliceScannerAudioEntity::StopScanner(a1);
}

// 0x507410
void CAudioEngine::StartLoadingTune() {
    m_FrontendAE.AddAudioEvent(AE_FRONTEND_LOADING_TUNE_START, 0.0f, 1.0f);
    AESoundManager.Service();
}

// 0x507430
void CAudioEngine::PauseAllSounds() {
    AEAudioHardware.PauseAllSounds();
}

// 0x507440
void CAudioEngine::ResumeAllSounds() {
    AEAudioHardware.ResumeAllSounds();
}

// 0x507750
void CAudioEngine::Service() {
    m_FrontendAE.AddAudioEvent(AE_FRONTEND_WAKEUP_AMPLIFIER, 0.0f, 1.0f);
    if (!CTimer::GetIsPaused())
        m_FrontendAE.AddAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP_PAUSED, 0.0f, 1.0f);

    int32 trackPlayTime = AEAudioHardware.GetTrackPlayTime();
    AEAudioHardware.GetChannelPlayTimes(m_nBackgroundAudioChannel, nullptr);
    if (field_0 && trackPlayTime == -4) {
        field_1 = true;
    } else if (field_1) {
        if (trackPlayTime == -6) {
            field_1 = false;
            if (CAERadioTrackManager::IsVehicleRadioActive()) {
                AERadioTrackManager.StartRadio(CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio());
            }
        }
    }

    AECutsceneTrackManager.Service(trackPlayTime);
    AEAmbienceTrackManager.Service(trackPlayTime);
    AERadioTrackManager.Service(trackPlayTime);
    if (FindPlayerPed(0))
        m_GlobalWeaponAE->ServiceAmbientGunFire();

    m_CollisionAE.Service();

    if (CTimer::GetIsPaused()) {
        AEAudioHardware.SetMusicFaderScalingFactor(1.0f);
        AEAudioHardware.SetEffectsFaderScalingFactor(1.0f);
        AEAudioHardware.SetStreamFaderScalingFactor(1.0f);
        m_ScriptAE.Service();
        CAEPedSpeechAudioEntity::Service();
        AESoundManager.Service();
        CAEPoliceScannerAudioEntity::Service();
        return;
    }

    if (!CCutsceneMgr::ms_running) {
        AEAudioHardware.SetStreamFaderScalingFactor(1.0f);
        m_ScriptAE.Service();
        CAEPedSpeechAudioEntity::Service();
        AESoundManager.Service();
        CAEPoliceScannerAudioEntity::Service();
        return;
    }

    AEAudioHardware.SetStreamFaderScalingFactor(0.0f);
    m_ScriptAE.Service();
    CAEPedSpeechAudioEntity::Service();
    AESoundManager.Service();
    CAEPoliceScannerAudioEntity::Service();
}

// 0x5078A0
void CAudioEngine::ServiceLoadingTune(float fScalingFactor) {
    float fCurrentScalingFactor = AEAudioHardware.GetEffectsFaderScalingFactor();
    if (fScalingFactor > fCurrentScalingFactor) {
        float fNewScalingFactor = fCurrentScalingFactor + 0.005f;
        if (fNewScalingFactor < fScalingFactor)
            fScalingFactor = fNewScalingFactor;
    }
    AEAudioHardware.SetEffectsFaderScalingFactor(fScalingFactor);
    AESoundManager.Service();
}


// 0x507A90
void CAudioEngine::Reset() {
    AESoundManager.Service();

    if (AERadioTrackManager.IsRadioOn())
    {
        AERadioTrackManager.StopRadio(nullptr, true);
        while (AERadioTrackManager.IsRadioOn()) {
            AERadioTrackManager.Service(AEAudioHardware.GetTrackPlayTime());
            AEAudioHardware.Service();
        }
    }
    else if (AEAmbienceTrackManager.IsAmbienceTrackActive())
    {
        StopAmbienceTrack(true);
        AEAmbienceTrackManager.StopSpecialMissionAmbienceTrack();
    }
    else if (AECutsceneTrackManager.IsCutsceneTrackActive())
    {
        AECutsceneTrackManager.StopCutsceneTrack();
        while (AECutsceneTrackManager.IsCutsceneTrackActive()) {
            AECutsceneTrackManager.Service(AEAudioHardware.GetTrackPlayTime());
            AEAudioHardware.Service();
        }
    }

    m_CollisionAE.Reset();
    AERadioTrackManager.Reset();
    AEAmbienceTrackManager.Reset();
    m_FrontendAE.AddAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP_PAUSED, 0.0f, 1.0f);
    m_FrontendAE.AddAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP, 0.0f, 1.0f);
    m_FrontendAE.Reset();
    m_ScriptAE.Reset();
    if (m_GlobalWeaponAE)
        m_GlobalWeaponAE->Reset();
    CAEWeatherAudioEntity::StaticReset();
    CAEPedSpeechAudioEntity::Reset();
    CAEPoliceScannerAudioEntity::Reset();
    AESoundManager.Reset();
    AESoundManager.Service();
    AESoundManager.PauseManually(true);
    m_nCurrentRadioStationId = -1;
    field_0 = false;
    field_1 = false;
}

// 0x507C30
void CAudioEngine::ResetSoundEffects() {
    AESoundManager.Service();
    m_CollisionAE.Reset();
    m_FrontendAE.AddAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP_PAUSED, 0.0f, 1.0f);
    m_FrontendAE.AddAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP, 0.0f, 1.0f);
    m_FrontendAE.Reset();
    m_ScriptAE.Reset();
    CAEWeatherAudioEntity::StaticReset();
    CAEPedSpeechAudioEntity::Reset();
    AESoundManager.Reset();
    AESoundManager.Service();
    AESoundManager.PauseManually(true);
}

// 0x507160
int8 CAudioEngine::GetCutsceneTrackStatus() {
    return AECutsceneTrackManager.GetCutsceneTrackStatus();
}

// 0x507170
int8 CAudioEngine::GetBeatTrackStatus() {
    return AECutsceneTrackManager.GetCutsceneTrackStatus();
}

// 0x507DC0
void CAudioEngine::StartRadio(RadioStationId id, int8 bassValue) {
    if (!GetBeatTrackStatus())
        AERadioTrackManager.StartRadio(id, bassValue, 0, 0);
}

// 0x507DF0
void CAudioEngine::StartRadio(tVehicleAudioSettings* settings) {
    if (!GetBeatTrackStatus())
        AERadioTrackManager.StartRadio(settings);
}

// 0x506F80
void CAudioEngine::SetRadioAutoRetuneOnOff(bool enable) {
    AERadioTrackManager.SetRadioAutoRetuneOnOff(enable);
}

// 0x506F90
void CAudioEngine::SetBassEnhanceOnOff(bool enable) {
    AERadioTrackManager.SetBassEnhanceOnOff(enable);
}

// 0x506FA0
void CAudioEngine::SetRadioBassSetting(int8 nBassSet) {
    AERadioTrackManager.SetBassSetting(nBassSet, 1.0f);
}

// 0x506FC0
void CAudioEngine::InitialiseRadioStationID(RadioStationId id) {
    AERadioTrackManager.InitialiseRadioStationID(id);
}

// 0x506FD0
bool CAudioEngine::IsRadioOn() {
    return AERadioTrackManager.IsRadioOn();
}

// 0x506FE0
bool CAudioEngine::HasRadioRetuneJustStarted() {
    return AERadioTrackManager.HasRadioRetuneJustStarted();
}

// 0x506FF0
bool CAudioEngine::IsRadioRetuneInProgress() {
    return m_FrontendAE.IsRadioTuneSoundActive();
}

// 0x507000
char* CAudioEngine::GetRadioStationName(RadioStationId id) {
    return AERadioTrackManager.GetRadioStationName(id);
}

// 0x507010
void CAudioEngine::GetRadioStationNameKey(RadioStationId id, char* outStr) {
    AERadioTrackManager.GetRadioStationNameKey(id, outStr);
}

// 0x507020
int32* CAudioEngine::GetRadioStationListenTimes() {
    return AERadioTrackManager.GetRadioStationListenTimes();
}

// 0x507040
RadioStationId CAudioEngine::GetCurrentRadioStationID() {
    return AERadioTrackManager.GetCurrentRadioStationID();
}

// 0x507030
void CAudioEngine::DisplayRadioStationName() {
    AERadioTrackManager.DisplayRadioStationName();
}
