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
    char              m_bHornTon; // sfx id
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
    bool IsHeli() const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_HELI; }
    bool IsPlane() const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_PLANE; }
    bool IsFlyingVehicle() const { return IsPlane() || IsHeli(); }
    bool IsNonVeh() const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_NON_VEH; }
    bool IsCar() const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_CAR; }
    bool IsMotorcycle() const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_MOTORCYCLE; }
    bool IsBicycle() const { return m_nVehicleSoundType == eVehicleSoundType::VEHICLE_SOUND_BICYCLE; }
};
VALIDATE_SIZE(tVehicleAudioSettings, 0x24);

class CPed;

class NOTSA_EXPORT_VTABLE CAEVehicleAudioEntity : public CAEAudioEntity {
public:
    CAEVehicleAudioEntity();
    ~CAEVehicleAudioEntity();

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
    char                   field_AA;
    char                   field_AB;
    int32                  field_AC;
    bool                   m_bInhibitAccForLowSpeed;
    char                   field_B1;
    int16                  m_nRainDropCounter;
    int16                  field_B4;
    char                   _pad_B6[2];
    int32                  field_B8;
    char                   field_BC;
    bool                   m_bDisableHeliEngineSounds;
    char                   field_BE;
    bool                   m_bSirenOrAlarmPlaying;
    bool                   m_bHornPlaying;
    char                   _pad_C1[3];
    float                  m_fSirenVolume;
    bool                   m_bModelWithSiren;
    char                   _pad_C9[3];
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
    int16                  m_nSomeCurPlayPos;
    int16                  m_nSomePrevPlayPos;
    int16                  field_14C;
    int16                  field_14E;
    int32                  field_150;
    int16                  field_154;
    int16                  m_nSkidSoundType;
    CAESound*              m_pSkidSoundMaybe;
    int16                  m_nRoadNoiseSoundType;
    char                   _pad_15E[2];
    CAESound*              m_pRoadNoiseSound;
    int16                  m_nFlatTyreSoundType;
    char                   _pad_166[2];
    CAESound*              m_pFlatTyreSound;
    int16                  m_nReverseGearSoundType;
    char                   _pad_16E[2];
    CAESound*              m_pReverseGearSound;
    char                   _pad_174[4];
    CAESound*              m_pHornTonSound;
    CAESound*              m_pSirenSound;
    CAESound*              m_pPoliceSirenSound;
    CAETwinLoopSoundEntity m_twinSkidSound;
    float                  field_22C;
    float                  field_230;
    float                  field_234;
    float                  field_238;
    float                  field_23C;
    int32                  field_240;
    bool                   m_bNitroSoundPresent;
    char                   field_245[3];
    float                  field_248;

public:
    // VTABLE
    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;

    // CLASS
    void    AddAudioEvent(eAudioEvents audioEvent, float fVolume);
    void    Service();
    void    Initialise(CEntity* entity);
    void    Terminate();
    uint32    GetVehicleTypeForAudio();
    void    IsAccInhibited(cVehicleParams& params);
    void    IsAccInhibitedBackwards(cVehicleParams& params);
    void    IsAccInhibitedForLowSpeed(cVehicleParams& params);
    void    IsAccInhibitedForTime();
    void    InhibitAccForTime(uint32);
    void    IsCrzInhibitedForTime();
    void    InhibitCrzForTime(uint32);
    void    GetAccelAndBrake(cVehicleParams& params);
    float   GetVolumeForDummyIdle(float, float);
    float   GetFrequencyForDummyIdle(float, float);
    float   GetVolumeForDummyRev(float, float);
    float   GetFrequencyForDummyRev(float, float);
    void    CancelVehicleEngineSound(int16);
    void    RequestNewPlayerCarEngineSound(int16, float, float);
    void    UpdateVehicleEngineSound(int16, float, float);
    void    StartVehicleEngineSound(int16, float, float);
    void    ProcessDummyStateTransition(int16, float, cVehicleParams& params);
    void    ProcessDummyVehicleEngine(cVehicleParams& params);
    void    JustGotInVehicleAsDriver();
    void    TurnOnRadioForVehicle();
    void    TurnOffRadioForVehicle();
    void    PlayerAboutToExitVehicleAsDriver();
    void    DisableHelicoptor();
    void    EnableHelicoptor();
    void    CopHeli();
    float   GetFreqForIdle(float);
    float   GetFreqForPlayerEngineSound(cVehicleParams& params, int16);
    float   GetVolForPlayerEngineSound(cVehicleParams& params, int16);
    void    JustFinishedAccelerationLoop();
    void    ProcessPlayerVehicleEngine(cVehicleParams& params);
    void    PlaySkidSound(int16 soundType, float speed, float volume);
    void    JustWreckedVehicle();
    void    PlayRoadNoiseSound(int16 soundType, float speed, float volume);
    void    PlayFlatTyreSound(int16 soundType, float speed, float volume);
    void    PlayReverseSound(int16 soundType, float speed, float volume);
    void    UpdateGasPedalAudio(CVehicle* veh, int32 vehType);
    void    ProcessVehicleFlatTyre(cVehicleParams& params);
    void    ProcessVehicleRoadNoise(cVehicleParams& params);
    void    ProcessReverseGear(cVehicleParams& params);
    float   GetVehicleDriveWheelSkidValue(CVehicle*, int32, float, cTransmission*, float);
    float   GetVehicleNonDriveWheelSkidValue(CVehicle*, int32, cTransmission*, float);
    void    ProcessVehicleSkidding(cVehicleParams& params);
    void    ProcessRainOnVehicle(cVehicleParams& params);
    void    PlayAircraftSound(int16, int16, int16, float, float);
    void    ProcessGenericJet(uint8, cVehicleParams& params, float, float, float, float, float);
    void    ProcessDummyJet(cVehicleParams& params);
    void    ProcessPlayerJet(cVehicleParams& params);
    void    ProcessDummySeaPlane(cVehicleParams& params);
    void    ProcessPlayerSeaPlane(cVehicleParams& params);
    void    ProcessAIHeli(cVehicleParams& params);
    void    ProcessDummyHeli(cVehicleParams& params);
    void    ProcessPlayerHeli(cVehicleParams& params);
    void    ProcessAIProp(cVehicleParams& params);
    void    ProcessDummyProp(cVehicleParams& params);
    void    ProcessPlayerProp(cVehicleParams& params);
    void    ProcessAircraft(cVehicleParams& params);
    CVector GetAircraftNearPosition();
    void    GetBaseVolumeForBicycleTyre(float);
    void    PlayBicycleSound(int16, int16, int16, float, float);
    void    ProcessPlayerBicycle(cVehicleParams& params);
    void    ProcessDummyBicycle(cVehicleParams& params);
    float   GetFlyingMetalVolume(CPhysical*);
    void    AddAudioEvent(eAudioEvents eventId, CEntity* entity);
    void    GetHornState(uint8*, cVehicleParams& params);
    void    GetSirenState(uint8*, uint8*, cVehicleParams& params);
    void    PlayHornOrSiren(uint8, uint8, uint8, cVehicleParams& params);
    void    ProcessVehicleSirenAlarmHorn(cVehicleParams& params);
    void    UpdateBoatSound(int16, int16, int16, float, float);
    void    StopGenericEngineSound(int16);
    void    ProcessBoatEngine(cVehicleParams& params);
    void    ProcessBoatMovingOverWater(cVehicleParams& params);
    void    UpdateTrainSound(int16, int16, int16, float, float);
    void    ProcessDummyTrainEngine(cVehicleParams& params);
    void    ProcessTrainTrackSound(cVehicleParams& params);
    void    ProcessPlayerTrainEngine(cVehicleParams& params);
    void    PlayTrainBrakeSound(int16 soundType, float speed, float volume);
    void    ProcessPlayerTrainBrakes(cVehicleParams& params);
    void    JustGotOutOfVehicleAsDriver();
    void    ProcessDummyRCPlane(cVehicleParams& params);
    void    ProcessPlayerRCPlane(cVehicleParams& params);
    void    ProcessDummyRCHeli(cVehicleParams& params);
    void    ProcessPlayerRCHeli(cVehicleParams& params);
    void    ProcessPlayerRCCar(cVehicleParams& params);
    void    ProcessPlayerHovercraft(cVehicleParams& params);
    void    ProcessPlayerGolfCart(cVehicleParams& params);
    void    UpdateGenericVehicleSound(int16, int16, int16, int16, float, float, float);
    void    ProcessDummyGolfCart(cVehicleParams& params);
    void    ProcessDummyHovercraft(cVehicleParams& params);
    void    ProcessDummyRCCar(cVehicleParams& params);
    void    ProcessPlayerCombine(cVehicleParams& params);
    void    ProcessEngineDamage(cVehicleParams& params);
    void    ProcessSpecialVehicle(cVehicleParams& params);
    void    ProcessNitro(cVehicleParams& params);
    void    ProcessMovingParts(cVehicleParams& params);
    void    ProcessVehicle(CPhysical*);

public:
    static void StaticInitialise();
    static void StaticService() { /* Empty on purpose */ }
    static tVehicleAudioSettings* StaticGetPlayerVehicleAudioSettingsForRadio();
    static void                   EnableHelicoptors();
    static void                   DisableHelicoptors();
    static bool                   DoesBankSlotContainThisBank(int16 bankSlot, int16 bankId);
    static int16                  DemandBankSlot(int16 bankId);
    static int16                  RequestBankSlot(int16 bankId);
    static void                   StoppedUsingBankSlot(int16 bankSlot);
    static tVehicleAudioSettings  GetVehicleAudioSettings(int16 vehId);

public:
    static CPed*&                  s_pPlayerAttachedForRadio;
    static CPed*&                  s_pPlayerDriver;
    static bool&                   s_HelicoptorsDisabled;
    static int16&                  s_NextDummyEngineSlot;
    static tVehicleAudioSettings*& s_pVehicleAudioSettingsForRadio;

    static constexpr int32 NUM_DUMMY_ENGINE_SLOTS = 10;
    static tEngineDummySlot (&s_DummyEngineSlots)[NUM_DUMMY_ENGINE_SLOTS];

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos);
};
VALIDATE_SIZE(CAEVehicleAudioEntity, 0x24C);

// indexes = (Vehicles modelid - 400)
static constexpr int32 NUM_VEH_AUDIO_SETTINGS = 232;
extern tVehicleAudioSettings const (&gVehicleAudioSettings)[NUM_VEH_AUDIO_SETTINGS];
