/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AEAudioEntity.h"
#include "cTransmission.h"
#include "AETwinLoopSoundEntity.h"

#include "eAudioEvents.h"
#include "eRadioID.h"

enum eVehicleSoundType : int8 {
    VEHICLE_SOUND_CAR              = 0x0,
    VEHICLE_SOUND_MOTORCYCLE       = 0x1,
    VEHICLE_SOUND_BICYCLE          = 0x2,
    VEHICLE_SOUND_BOAT             = 0x3,
    VEHICLE_SOUND_HELI             = 0x4,
    VEHICLE_SOUND_PLANE            = 0x5,
    VEHICLE_SOUND_NON_VEH          = 0x6,
    VEHICLE_SOUND_USED_BY_NONE_VEH = 0x7,
    VEHICLE_SOUND_TRAIN            = 0x8,
    VEHICLE_SOUND_TRAILER          = 0x9,
    VEHICLE_SOUND_SPECIAL          = 0xA,
};

enum eRadioType : int8 {
    RADIO_CIVILIAN  = 0x0,
    RADIO_SPECIAL   = 0x1,
    RADIO_UNKNOWN   = 0x2,
    RADIO_EMERGENCY = 0x3,
    RADIO_DISABLED  = -1,
};

struct tEngineDummySlot {
    int16 m_nBankId;
    int16 m_nUsageCount;
};

class CVehicle;

class cVehicleParams {
public:
    uint32         m_vehicleSubType;
    uint32         m_vehicleType;
    char           field_8;
    char           pad1[3];
    int32          field_C;
    CVehicle*      m_pVehicle;
    cTransmission* m_pTransmission;
    uint32         m_nModelType;
    float          m_fVelocity;
    int16          m_nGasState;
    int16          m_nBreakState;
    float          m_fVelocityAbsolute;
    float          m_fZVelocity;
    float          m_fVelocityPercentage;
    int32          field_30;
    float          field_34;
    char           m_nCurrentGear;
    bool           m_bHandbrakeOn;
    char           pad2[2];
    float          m_fVelocityChangingPercentage;
    float          m_fWheelSpinForAudio;
    uint16         m_nNumberOfGears;
    uint8          m_nWheelsOnGround;
    char           field_47;
    int32          field_48;
};
VALIDATE_SIZE(cVehicleParams, 0x4C);

class tVehicleSound {
public:
    uint32    m_nIndex;
    CAESound* m_pSound;

    void Init(auto index) {
        m_nIndex = index;
        m_pSound = nullptr;
    }
};
VALIDATE_SIZE(tVehicleSound, 0x8);

struct tVehicleAudioSettings {
    eVehicleSoundType m_nVehicleSoundType;
    char              _pad;
    int16             m_nEngineOnSoundBankId;
    int16             m_nEngineOffSoundBankId;
    char              m_nBassSetting; // m_nStereo
    char              _pad1;
    float             m_fBassEq;
    float             field_C;
    char              m_nHornToneSoundInBank; // sfx id
    char              _pad2[3];
    float             m_fHornHigh;
    char              m_nDoorSound;
    char              field_19;
    eRadioID          m_nRadioID;
    eRadioType        m_nRadioType;
    char              vehTypeForAudio;
    char              _pad4[3];
    float             m_fHornVolumeDelta;

public:
    [[nodiscard]] bool IsHeli()          const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_HELI; }
    [[nodiscard]] bool IsPlane()         const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_PLANE; }
    [[nodiscard]] bool IsFlyingVehicle() const { return IsPlane() || IsHeli(); }
    [[nodiscard]] bool IsNonVeh()        const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_NON_VEH; }
    [[nodiscard]] bool IsCar()           const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_CAR; }
    [[nodiscard]] bool IsMotorcycle()    const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_MOTORCYCLE; }
    [[nodiscard]] bool IsBicycle()       const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_BICYCLE; }
};
VALIDATE_SIZE(tVehicleAudioSettings, 0x24);

class CPed;

class CAEVehicleAudioEntity : public CAEAudioEntity {
public:
    int16                  field_7C;
    char                   field_7E[2];
    tVehicleAudioSettings  m_settings;
    bool                   m_bEnabled;
    bool                   m_bPlayerDriver;
    bool                   m_bPlayerPassenger;
    bool                   m_bVehicleRadioPaused;
    bool                   m_bSoundsStopped;
    char                   m_nEngineState;
    uint8                  m_nGearRelatedStuff;
    char                   field_AB;
    float                  field_AC;
    bool                   m_bInhibitAccForLowSpeed;
    char                   field_B1;
    int16                  m_nRainDropCounter;
    int16                  field_B4;
    int32                  field_B8;
    char                   field_BC;
    bool                   m_bDisableHeliEngineSounds;
    bool                   m_bPlayHornTone;
    bool                   m_bSirenOrAlarmPlaying;
    bool                   m_bHornPlaying;
    float                  m_fHornVolume;
    bool                   m_bModelWithSiren;
    uint32                 m_nBoatHitWaveLastPlayedTime;
    uint32                 m_nTimeToInhibitAcc;
    uint32                 m_nTimeToInhibitCrz;
    float                  m_fGeneralVehicleSoundVolume;
    int16                  m_nEngineDecelerateSoundBankId;
    int16                  m_nEngineAccelerateSoundBankId;
    int16                  m_nEngineBankSlotId;
    int16                  field_E2;
    tVehicleSound          m_aEngineSounds[12];
    int32                  field_144;
    int16                  m_nEngineSoundPlayPos;
    int16                  m_nEngineSoundLastPlayedPos;
    int16                  m_nAcclLoopCounter;
    int16                  field_14E;
    int32                  field_150;
    int16                  field_154;
    int16                  m_nSkidSoundType;
    CAESound*              m_pSkidSoundMaybe;
    int16                  m_nRoadNoiseSoundType;
    CAESound*              m_pRoadNoiseSound;
    int16                  m_nFlatTyreSoundType;
    CAESound*              m_pFlatTyreSound;
    int16                  m_nReverseGearSoundType;
    CAESound*              m_pReverseGearSound;
    int32                  _pad_174;
    CAESound*              m_pHornTonSound;
    CAESound*              m_pSirenSound;
    CAESound*              m_pPoliceSirenSound;
    CAETwinLoopSoundEntity m_twinSkidSound;
    float                  m_fPlaneSoundSpeed;
    float                  m_fPlaneSoundVolume_Probably;
    float                  field_234;
    float                  field_238;
    float                  field_23C;
    int32                  field_240;
    bool                   m_bNitroSoundPresent;
    char                   field_245[3];
    float                  field_248;

public:
    static CPed*&                  s_pPlayerAttachedForRadio;
    static CPed*&                  s_pPlayerDriver;
    static bool&                   s_HelicoptorsDisabled;
    static int16&                  s_NextDummyEngineSlot;
    static tVehicleAudioSettings*& s_pVehicleAudioSettingsForRadio;

    static constexpr int32 NUM_DUMMY_ENGINE_SLOTS = 10;
    static tEngineDummySlot (&s_DummyEngineSlots)[NUM_DUMMY_ENGINE_SLOTS];

public:
    CAEVehicleAudioEntity();
    ~CAEVehicleAudioEntity();

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;

    void Initialise(CEntity* entity);
    static void StaticInitialise();

    void Terminate();

    static tVehicleAudioSettings* StaticGetPlayerVehicleAudioSettingsForRadio();
    static bool DoesBankSlotContainThisBank(int16 bankSlot, int16 bankId);
    static int16 DemandBankSlot(int16 bankId);
    static int16 RequestBankSlot(int16 bankId);
    static void StoppedUsingBankSlot(int16 bankSlot);
    static tVehicleAudioSettings GetVehicleAudioSettings(int16 vehId);

    void AddAudioEvent(eAudioEvents event, float fVolume);
    void AddAudioEvent(eAudioEvents event, CVehicle* vehicle);

    void Service();
    static void StaticService();

    uint32 GetVehicleTypeForAudio();

    void InhibitAccForTime(uint32 time);
    bool IsAccInhibited(cVehicleParams& params);
    bool IsAccInhibitedBackwards(cVehicleParams& params);
    bool IsAccInhibitedForLowSpeed(cVehicleParams& params);
    bool IsAccInhibitedForTime();
    bool IsCrzInhibitedForTime();

    void JustGotInVehicleAsDriver();
    void TurnOnRadioForVehicle();
    void TurnOffRadioForVehicle();
    void PlayerAboutToExitVehicleAsDriver();
    bool CopHeli();
    bool JustFinishedAccelerationLoop();
    void PlaySkidSound(int16 soundType, float speed, float volumeDelta);
    void JustWreckedVehicle();
    CVector GetAircraftNearPosition();
    float GetFlyingMetalVolume(CPhysical* physical);
    void GetSirenState(bool& bSirenOrAlarm, bool& bHorn, cVehicleParams& params);
    void PlayTrainBrakeSound(int16 soundType, float speed, float volume);
    void JustGotOutOfVehicleAsDriver();

    void InhibitCrzForTime(uint32);

    void CancelVehicleEngineSound(int16 engineSoundStateId);
    void RequestNewPlayerCarEngineSound(int16 vehicleSoundId, float speed, float changeSound);

    void StartVehicleEngineSound(int16, float, float);

    void UpdateVehicleEngineSound(int16, float, float);
    static void UpdateGasPedalAudio(CVehicle* vehicle, int32 vehType);
    void UpdateBoatSound(int16 engineState, int16 bankSlotId, int16 soundId, float speed, float volumeDelta);
    void UpdateTrainSound(int16, int16, int16, float, float);
    void UpdateGenericVehicleSound(int16 soundId, int16 bankSlotId, int16 bankId, int16 sfxId, float speed, float volume, float distance);

    static void EnableHelicoptors();
    static void DisableHelicoptors();
    void EnableHelicoptor();
    void DisableHelicoptor();

    float GetVolumeForDummyIdle(float fGearRevProgress, float fRevProgressBaseline);
    float GetFrequencyForDummyIdle(float fGearRevProgress, float fRevProgressBaseline);
    float GetVolumeForDummyRev(float, float);
    float GetFrequencyForDummyRev(float, float);
    float GetFreqForIdle(float velocityPercentage);
    float GetFreqForPlayerEngineSound(cVehicleParams& vehParams, int16 engineState_QuestionMark);
    float GetVolForPlayerEngineSound(cVehicleParams& vehParams, int16 gear);
    float GetVehicleDriveWheelSkidValue(CVehicle* vehicle, int32 wheelState, float fUnk, cTransmission& transmission, float fVelocity);
    float GetVehicleNonDriveWheelSkidValue(CVehicle* vehicle, int32 wheelState, cTransmission& transmission, float fVelocity);
    float GetBaseVolumeForBicycleTyre(float fGearVelocityProgress);
    void  GetHornState(bool* out, cVehicleParams& params);
    void  GetAccelAndBrake(cVehicleParams& params);

    void PlayAircraftSound(int16 engineState, int16 bankSlotId, int16 sfxId, float speed, float volumeDelta);
    void PlayRoadNoiseSound(int16 newRoadNoiseSoundType, float speed, float volume);
    void PlayFlatTyreSound(int16 soundType, float speed, float volume);
    void PlayReverseSound(int16 soundType, float speed, float volume);
    void PlayHornOrSiren(bool hornState, char sirenOrAlarm, bool mrWhoopie, cVehicleParams& params);
    void PlayBicycleSound(int16 engineState, int16 bankSlotId, int16 sfxId, float speed, float fVolume);

    void ProcessVehicleFlatTyre(cVehicleParams& params);
    void ProcessVehicleRoadNoise(cVehicleParams& params);
    void ProcessReverseGear(cVehicleParams& params);
    void ProcessVehicleSkidding(cVehicleParams& params);
    void ProcessRainOnVehicle(cVehicleParams& params);
    void ProcessGenericJet(uint8 a1, cVehicleParams& params, float a3, float a4, float a5, float a6, float a7);
    void ProcessDummyJet(cVehicleParams& params);
    void ProcessPlayerJet(cVehicleParams& params);
    void ProcessDummySeaPlane(cVehicleParams& params);
    void ProcessPlayerSeaPlane(cVehicleParams& params);
    void ProcessAIHeli(cVehicleParams& params);
    void ProcessDummyHeli(cVehicleParams& params);
    void ProcessPlayerHeli(cVehicleParams& params);
    void ProcessAIProp(cVehicleParams& params);
    void ProcessDummyProp(cVehicleParams& params);
    void ProcessPlayerProp(cVehicleParams& params);
    void ProcessAircraft(cVehicleParams& params);
    void ProcessPlayerBicycle(cVehicleParams& params);
    void ProcessDummyBicycle(cVehicleParams& params);
    void ProcessDummyStateTransition(int16, float, cVehicleParams& params);
    void ProcessDummyVehicleEngine(cVehicleParams& params);
    void ProcessPlayerVehicleEngine(cVehicleParams& params);
    void ProcessVehicleSirenAlarmHorn(cVehicleParams& params);
    void ProcessBoatEngine(cVehicleParams& params);
    void ProcessBoatMovingOverWater(cVehicleParams& params);
    void ProcessDummyTrainEngine(cVehicleParams& params);
    void ProcessTrainTrackSound(cVehicleParams& params);
    void ProcessPlayerTrainEngine(cVehicleParams& params);
    void ProcessPlayerTrainBrakes(cVehicleParams& params);
    void ProcessDummyRCPlane(cVehicleParams& params);
    void ProcessPlayerRCPlane(cVehicleParams& params);
    void ProcessDummyRCHeli(cVehicleParams& params);
    void ProcessPlayerRCHeli(cVehicleParams& params);
    void ProcessPlayerRCCar(cVehicleParams& params);
    void ProcessPlayerHovercraft(cVehicleParams& params);
    void ProcessPlayerGolfCart(cVehicleParams& params);
    void ProcessDummyGolfCart(cVehicleParams& params);
    void ProcessDummyHovercraft(cVehicleParams& params);
    void ProcessDummyRCCar(cVehicleParams& params);
    void ProcessPlayerCombine(cVehicleParams& params);
    void ProcessEngineDamage(cVehicleParams& params);
    void ProcessSpecialVehicle(cVehicleParams& params);
    void ProcessNitro(cVehicleParams& params);
    void ProcessMovingParts(cVehicleParams& params);
    void ProcessVehicle(CPhysical* vehicle);

    // Seems to be inlined, so whenever you see something similar, replace it with a call
    void StopGenericEngineSound(int16 index);

    // NOTSA, Custom (Most likely originally existed, but got inlined):
    bool UpdateGenericEngineSound(int16 index, float fVolume = 1.0f, float fSpeed = 1.0f);
    bool PlayGenericEngineSound(int16 index, int16 bank, int16 slotInBank,
                                float fVolume = 1.0f, float fSpeed = 1.0f, float fSoundDistance = 1.0f,
                                float fTimeScale = 1.0f, eSoundEnvironment individualEnvironment = eSoundEnvironment::SOUND_REQUEST_UPDATES, int16 playPos = 0);
#undef PlaySound
    CAESound* PlaySound(int16 bank, int16 slotInBank,
                        float fVolume = 1.0f, float fSpeed = 1.0f, float fSoundDistance = 1.0f,
                        float fTimeScale = 1.0f, eSoundEnvironment individualEnvironment = eSoundEnvironment::SOUND_REQUEST_UPDATES, int16 playPos = 0);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEVehicleAudioEntity* Constructor() { this->CAEVehicleAudioEntity::CAEVehicleAudioEntity(); return this; }
    CAEVehicleAudioEntity* Destructor() { this->CAEVehicleAudioEntity::~CAEVehicleAudioEntity(); return this; }
    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos);
};
VALIDATE_SIZE(CAEVehicleAudioEntity, 0x24C);

// indexes = (Vehicles modelid - 400)
static constexpr int32 NUM_VEH_AUDIO_SETTINGS = 232;
extern tVehicleAudioSettings const (&gVehicleAudioSettings)[NUM_VEH_AUDIO_SETTINGS];
