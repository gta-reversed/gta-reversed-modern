#pragma once

#include "eAudioEvents.h"

class CEntity;
class CColPoint;
class CVector;

class CAudioEngine {
public:
/*
    char                        field_0;
    char                        field_1;
    char                        m_nCurrentRadiostationId;
    char                        field_3;
    int32                       field_4;
    char                        field_8[152];
    char                        field_A0;
    char                        field_A1[15];
    char                        field_B0;
    char                        field_B1[3];
    CAEFrontendAudioEntity      m_FrontendAudio;
    CAETwinLoopSoundEntity      field_150;
    CAETwinLoopSoundEntity      field_1F8;
    CAEScriptAudioEntity        m_scriptAudio;
    CAECollisionAudioEntity     m_collisionAudio;
    int32                       m_pWeaponAudio;
    CAEPedlessSpeechAudioEntity m_pedlessSpeechAudio;
    char                        field_1F38[24];
    CAEDoorAudioEntity          m_doorAudio;
*/

public:
    static void InjectHooks();

    CAudioEngine();
    ~CAudioEngine();

    bool IsLoadingTuneActive();
    void ResetStatistics();
    void Restart();
    void SetMusicMasterVolume(int8);
    void SetEffectsMasterVolume(int8);
    void SetMusicFaderScalingFactor(float);
    void SetEffectsFaderScalingFactor(float);
    void ServiceLoadingTune(float);
    void SetStreamFaderScalingFactor(float);
    void SetNonStreamFaderScalingFactor(float);
    void DisableEffectsLoading();
    void EnableEffectsLoading();
    void ReportFrontendAudioEvent(eAudioEvents audioEventId, float a2, float a3);
    void ResetSoundEffects();
    void ReportCollision(CEntity* pEntity1, CEntity* pEntity2, int32 surface1, int32 surface2, CColPoint* pColPoint, CVector* normal, float fCollisionImpact1, float fCollisionImpact2, int32 bOnlyPlayOneShotCollisionSound, bool bUnknown);
    void ReportBulletHit(CEntity*, uint8, CVector&, float);
    void ReportObjectDestruction(CEntity* pEntity);
    void ReportGlassCollisionEvent(int32, CVector&);
    void ReportWaterSplash(CPhysical* pPhysical, float volume, bool forcePlaySplashSound);
    void ReportWaterSplash(CVector, float);
    void ReportWeaponEvent(int32 audioEvent, eWeaponType weaponType, CPhysical* physical);
    void ReportDoorMovement(CPhysical* pPhysical);
    void StopRadio(tVehicleAudioSettings* audioSettings, uint8 bDuringPause);
    void SetRadioAutoRetuneOnOff(uint8);
    void SetBassEnhanceOnOff(uint8);
    void SetRadioBassSetting(int8);
    void InitialiseRadioStationID(int8);
    void IsRadioOn();
    void HasRadioRetuneJustStarted();
    void IsRadioRetuneInProgress();
    void GetRadioStationName(int8);
    void GetRadioStationNameKey(int8, char*);
    void GetRadioStationListenTimes();
    void DisplayRadioStationName();
    void GetCurrentRadioStationID();
    void IsVehicleRadioActive();
    void Service();
    void InitialisePostLoading();
    void PlayRadioAnnouncement(uint32);
    void PlayPreloadedCutsceneTrack();
    void StopCutsceneTrack(uint8);
    bool IsCutsceneTrackActive();
    void GetCutsceneTrackStatus();
    void GetBeatTrackStatus();
    void RetuneRadio(int8);
    void StartRadio(tVehicleAudioSettings*);
    void StartRadio(int8, int8);
    void PlayPreloadedBeatTrack(uint8);
    void StopBeatTrack();
    void GetBeatInfo();
    void IsBeatInfoPresent();
    void PauseBeatTrack(uint8);
    void IsAmbienceTrackActive();
    void StopAmbienceTrack(uint8);
    void PreloadBeatTrack(int16);
    void PreloadCutsceneTrack(int16, uint8);
    void Shutdown();
    void Reset();
    void DoesAmbienceTrackOverrideRadio();
    void IsAmbienceRadioActive();
    void PreloadMissionAudio(uint8, int32);
    void GetMissionAudioLoadingStatus(uint8);
    void PlayLoadedMissionAudio(uint8);
    void IsMissionAudioSampleFinished(uint8);
    void GetMissionAudioEvent(uint8);
    void GetMissionAudioPosition(uint8);
    void ClearMissionAudio(uint8);
    void SetMissionAudioPosition(uint8, CVector&);
    void AttachMissionAudioToPed(uint8, CPed*);
    void AttachMissionAudioToObject(uint8, CObject*);
    void AttachMissionAudioToPhysical(uint8, CPhysical*);
    void ReportMissionAudioEvent(uint16, CVector&);
    void ReportMissionAudioEvent(uint16 eventId, CObject* pObject);
    void ReportMissionAudioEvent(uint16, CPed*);
    void ReportMissionAudioEvent(uint16, CVehicle*);
    void ReportMissionAudioEvent(uint16, CPhysical*, float, float);
    void SayPedless(int32, int16, CEntity*, uint32, float, uint8, uint8, uint8);
    void DisablePoliceScanner(uint8, uint8);
    void EnablePoliceScanner();
    void StopPoliceScanner(uint8);
    void StartLoadingTune();
    void PauseAllSounds();
    void ResumeAllSounds();
    void Initialise();
    // void Save(); // Only in android IDB
    // void Load(); // Only in android IDB
};

extern CAudioEngine& AudioEngine;
