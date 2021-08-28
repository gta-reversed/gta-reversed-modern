#pragma once

#include "eAudioEvents.h"

class CEntity;
class CColPoint;
class CVector;

class CAudioEngine
{
public:
    CAudioEngine();
    ~CAudioEngine();

public:
    /*char field_0;
    char field_1;
    char m_nCurrentRadiostationId;
    char field_3;
    int field_4;
    char field_8[152];
    char field_A0;
    char field_A1[15];
    char field_B0;
    char field_B1[3];
    CAEFrontendAudioEntity m_FrontendAudio;
    CAETwinLoopSoundEntity field_150;
    CAETwinLoopSoundEntity field_1F8;
    CAEScriptAudioEntity m_scriptAudio;
    CAECollisionAudioEntity m_collisionAudio;
    int m_pWeaponAudio;
    CAEPedlessSpeechAudioEntity m_pedlessSpeechAudio;
    char field_1F38[24];
    CAEDoorAudioEntity m_doorAudio;*/

public:
    static void InjectHooks();

    void IsLoadingTuneActive();
    void ResetStatistics();
    void Restart();
    void SetMusicMasterVolume(signed char);
    void SetEffectsMasterVolume(signed char);
    void SetMusicFaderScalingFactor(float);
    void SetEffectsFaderScalingFactor(float);
    void ServiceLoadingTune(float);
    void SetStreamFaderScalingFactor(float);
    void SetNonStreamFaderScalingFactor(float);
    void DisableEffectsLoading();
    void EnableEffectsLoading();
    void ReportFrontendAudioEvent(eAudioEvents audioEventId, float a2, float a3);
    void ResetSoundEffects();
    void ReportCollision(CEntity* pEntity1, CEntity* pEntity2, int surface1, int surface2, CColPoint* pColPoint, CVector* normal, float fCollisionImpact1, float fCollisionImpact2, int bOnlyPlayOneShotCollisionSound, bool bUnknown);
    void ReportBulletHit(CEntity*, uint8_t, CVector&, float);
    void ReportObjectDestruction(CEntity* pEntity);
    void ReportGlassCollisionEvent(int, CVector&);
    void ReportWaterSplash(CPhysical* pPhysical, float volume, bool forcePlaySplashSound);
    void ReportWaterSplash(CVector, float);
    void ReportWeaponEvent(int32_t audioEvent, eWeaponType weaponType, CPhysical* physical);
    void ReportDoorMovement(CPhysical* pPhysical);
    void StopRadio(tVehicleAudioSettings* audioSettings, unsigned char bDuringPause);
    void SetRadioAutoRetuneOnOff(uint8_t);
    void SetBassEnhanceOnOff(uint8_t);
    void SetRadioBassSetting(signed char);
    void InitialiseRadioStationID(signed char);
    void IsRadioOn();
    void HasRadioRetuneJustStarted();
    void IsRadioRetuneInProgress();
    void GetRadioStationName(signed char);
    void GetRadioStationNameKey(signed char, char*);
    void GetRadioStationListenTimes();
    void DisplayRadioStationName();
    void GetCurrentRadioStationID();
    void IsVehicleRadioActive();
    void Service();
    void InitialisePostLoading();
    void PlayRadioAnnouncement(uint32);
    void PlayPreloadedCutsceneTrack();
    void StopCutsceneTrack(uint8_t);
    bool IsCutsceneTrackActive();
    void GetCutsceneTrackStatus();
    void GetBeatTrackStatus();
    void RetuneRadio(signed char);
    void StartRadio(tVehicleAudioSettings*);
    void StartRadio(signed char, signed char);
    void PlayPreloadedBeatTrack(uint8_t);
    void StopBeatTrack();
    void GetBeatInfo();
    void IsBeatInfoPresent();
    void PauseBeatTrack(uint8_t);
    void IsAmbienceTrackActive();
    void StopAmbienceTrack(uint8_t);
    void PreloadBeatTrack(short);
    void PreloadCutsceneTrack(short, uint8_t);
    void Shutdown();
    void Reset();
    void DoesAmbienceTrackOverrideRadio();
    void IsAmbienceRadioActive();
    void PreloadMissionAudio(uint8_t, int);
    void GetMissionAudioLoadingStatus(uint8_t);
    void PlayLoadedMissionAudio(uint8_t);
    void IsMissionAudioSampleFinished(uint8_t);
    void GetMissionAudioEvent(uint8_t);
    void GetMissionAudioPosition(uint8_t);
    void ClearMissionAudio(uint8_t);
    void SetMissionAudioPosition(uint8_t, CVector&);
    void AttachMissionAudioToPed(uint8_t, CPed*);
    void AttachMissionAudioToObject(uint8_t, CObject*);
    void AttachMissionAudioToPhysical(uint8_t, CPhysical*);
    void ReportMissionAudioEvent(uint16_t, CVector&);
    void ReportMissionAudioEvent(uint16_t eventId, CObject* pObject);
    void ReportMissionAudioEvent(uint16_t, CPed*);
    void ReportMissionAudioEvent(uint16_t, CVehicle*);
    void ReportMissionAudioEvent(uint16_t, CPhysical*, float, float);
    void SayPedless(int, short, CEntity*, uint32, float, uint8_t, uint8_t, uint8_t);
    void DisablePoliceScanner(uint8_t, uint8_t);
    void EnablePoliceScanner();
    void StopPoliceScanner(uint8_t);
    void StartLoadingTune();
    void PauseAllSounds();
    void ResumeAllSounds();
    void Initialise();
    // void Save(); // Only in android IDB
    // void Load(); // Only in android IDB
};

extern CAudioEngine& AudioEngine;
