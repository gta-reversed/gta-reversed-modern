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
    void ReportBulletHit(CEntity*, uchar, CVector&, float);
    void ReportObjectDestruction(CEntity* pEntity);
    void ReportGlassCollisionEvent(int, CVector&);
    void ReportWaterSplash(CPhysical* pPhysical, float volume, bool forcePlaySplashSound);
    void ReportWaterSplash(CVector, float);
    void ReportWeaponEvent(int32_t audioEvent, eWeaponType weaponType, CPhysical* physical);
    void ReportDoorMovement(CPhysical* pPhysical);
    void StopRadio(tVehicleAudioSettings* audioSettings, unsigned char bDuringPause);
    void SetRadioAutoRetuneOnOff(uchar);
    void SetBassEnhanceOnOff(uchar);
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
    void PlayRadioAnnouncement(uint);
    void PlayPreloadedCutsceneTrack();
    void StopCutsceneTrack(uchar);
    bool IsCutsceneTrackActive();
    void GetCutsceneTrackStatus();
    void GetBeatTrackStatus();
    void RetuneRadio(signed char);
    void StartRadio(tVehicleAudioSettings*);
    void StartRadio(signed char, signed char);
    void PlayPreloadedBeatTrack(uchar);
    void StopBeatTrack();
    void GetBeatInfo();
    void IsBeatInfoPresent();
    void PauseBeatTrack(uchar);
    void IsAmbienceTrackActive();
    void StopAmbienceTrack(uchar);
    void PreloadBeatTrack(short);
    void PreloadCutsceneTrack(short, uchar);
    void Shutdown();
    void Reset();
    void DoesAmbienceTrackOverrideRadio();
    void IsAmbienceRadioActive();
    void PreloadMissionAudio(uchar, int);
    void GetMissionAudioLoadingStatus(uchar);
    void PlayLoadedMissionAudio(uchar);
    void IsMissionAudioSampleFinished(uchar);
    void GetMissionAudioEvent(uchar);
    void GetMissionAudioPosition(uchar);
    void ClearMissionAudio(uchar);
    void SetMissionAudioPosition(uchar, CVector&);
    void AttachMissionAudioToPed(uchar, CPed*);
    void AttachMissionAudioToObject(uchar, CObject*);
    void AttachMissionAudioToPhysical(uchar, CPhysical*);
    void ReportMissionAudioEvent(ushort, CVector&);
    void ReportMissionAudioEvent(ushort eventId, CObject* pObject);
    void ReportMissionAudioEvent(ushort, CPed*);
    void ReportMissionAudioEvent(ushort, CVehicle*);
    void ReportMissionAudioEvent(ushort, CPhysical*, float, float);
    void SayPedless(int, short, CEntity*, uint, float, uchar, uchar, uchar);
    void DisablePoliceScanner(uchar, uchar);
    void EnablePoliceScanner();
    void StopPoliceScanner(uchar);
    void StartLoadingTune();
    void PauseAllSounds();
    void ResumeAllSounds();
    void Initialise();
    // void Save(); // Only in android IDB
    // void Load(); // Only in android IDB
};

extern CAudioEngine& AudioEngine;
