/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CAEAudioEntity.h"
#include "cTransmission.h"
#include "CAETwinLoopSoundEntity.h"
#include "eAudioEvents.h"
#include "eRadioID.h"

enum eVehicleSoundType : char
{
    VEHICLE_SOUND_CAR = 0x0,
    VEHICLE_SOUND_MOTORCYCLE = 0x1,
    VEHICLE_SOUND_BICYCLE = 0x2,
    VEHICLE_SOUND_BOAT = 0x3,
    VEHICLE_SOUND_HELI = 0x4,
    VEHICLE_SOUND_PLANE = 0x5,
    VEHICLE_SOUND_NON_VEH = 0x6,
    VEHICLE_SOUND_USED_BY_NONE_VEH = 0x7,
    VEHICLE_SOUND_TRAIN = 0x8,
    VEHICLE_SOUND_TRAILER = 0x9,
    VEHICLE_SOUND_SPECIAL = 0xA,
};

enum eRadioType : char
{
    RADIO_CIVILIAN = 0x0,
    RADIO_SPECIAL = 0x1,
    RADIO_UNKNOWN = 0x2,
    RADIO_EMERGENCY = 0x3,
    RADIO_DISABLED = -1,
};

struct  tEngineDummySlot {
    short m_nBankId;
    short m_nUsageCount;
};

class cVehicleParams {
public:
    unsigned int    m_vehicleSubType;
    unsigned int    m_vehicleType;
    char field_8;
    char pad1[3];
    int field_C;
    class CVehicle       *m_pVehicle;
    cTransmission  *m_pTransmission;
    unsigned int    m_nModelType;
    float           m_fVelocity;
    short           m_nGasState;
    short           m_nBreakState;
    float           m_fVelocityAbsolute;
    float           m_fZVelocity;
    float           m_fVelocityPercentage;
    int field_30;
    float field_34;
    char            m_nCurrentGear;
    bool            m_bHandbrakeOn;
    char pad2[2];
    float           m_fVelocityChangingPercentage;
    float           m_fWheelSpinForAudio;
    unsigned short  m_nNumberOfGears;
    unsigned char   m_nWheelsOnGround;
    char field_47;
    int field_48;
};
VALIDATE_SIZE(cVehicleParams, 0x4C);

struct  tVehicleSound {
    unsigned int  m_nIndex;
    CAESound     *m_pSound;
};
VALIDATE_SIZE(tVehicleSound, 0x8);

struct  tVehicleAudioSettings {
    eVehicleSoundType  m_nVehicleSoundType;
    char              _pad;
    short              m_nEngineOnSoundBankId;
    short              m_nEngineOffSoundBankId;
    char               m_nBassSetting;   // m_nStereo
    char              _pad1;
    float              m_fBassEq;
    float              field_C;
    char               m_bHornTon;   // sfx id
    char              _pad2[3];
    float              m_fHornHigh;
    char               m_nDoorSound;
    char               field_19;
    eRadioID           m_nRadioID;
    eRadioType         m_nRadioType;
    char               vehTypeForAudio;
    char              _pad4[3];
    float              m_fHornVolumeDelta;

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

class CAEVehicleAudioEntity : public CAEAudioEntity {
public:
    CAEVehicleAudioEntity();
    ~CAEVehicleAudioEntity();

public:
    short field_7C;
    char field_7E[2];
    tVehicleAudioSettings   m_settings;
    bool                    m_bEnabled;
    bool                    m_bPlayerDriver;
    bool                    m_bPlayerPassenger;
    bool                    m_bVehicleRadioPaused;
    bool                    m_bSoundsStopped;
    char                    m_nEngineState;
    char field_AA;
    char field_AB;
    int field_AC;
    bool                    m_bInhibitAccForLowSpeed;
    char field_B1;
    short                   m_nRainDropCounter;
    short field_B4;
    char gap_B6[2];
    int field_B8;
    char field_BC;
    bool                    m_bDisableHeliEngineSounds;
    char field_BE;
    bool                    m_bSirenOrAlarmPlaying;
    bool                    m_bHornPlaying;
    char gap_C1[3];
    float                   m_fSirenVolume;
    bool                    m_bModelWithSiren;
    char gap_C9[3];
    unsigned int            m_nBoatHitWaveLastPlayedTime;
    unsigned int            m_nTimeToInhibitAcc;
    unsigned int            m_nTimeToInhibitCrz;
    float                   m_fGeneralVehicleSoundVolume;
    short                   m_nEngineDecelerateSoundBankId;
    short                   m_nEngineAccelerateSoundBankId;
    short                   m_nEngineBankSlotId;
    short field_E2;
    tVehicleSound           m_aEngineSounds[12];
    int field_144;
    short m_nSomeCurPlayPos;
    short m_nSomePrevPlayPos;
    short field_14C;
    short field_14E;
    int field_150;
    short field_154;
    short                   m_nSkidSoundType;
    CAESound               *m_pSkidSoundMaybe;
    short                   m_nRoadNoiseSoundType;
    char gap_15E[2];
    CAESound               *m_pRoadNoiseSound;
    short                   m_nFlatTyreSoundType;
    char gap_166[2];
    CAESound               *m_pFlatTyreSound;
    short                   m_nReverseGearSoundType;
    char gap_16E[2];
    CAESound               *m_pReverseGearSound;
    char gap_174[4];
    CAESound               *m_pHornTonSound;
    CAESound               *m_pSirenSound;
    CAESound               *m_pPoliceSirenSound;
    CAETwinLoopSoundEntity  m_twinSkidSound;
    float field_22C;
    float field_230;
    float field_234;
    float field_238;
    float field_23C;
    int field_240;
    bool                    m_bNitroSoundPresent;
    char field_245[3];
    float field_248;

public:
    static void InjectHooks();

// VTABLE
    void UpdateParameters(CAESound* sound, short curPlayPos) override;

// CLASS
    void AddAudioEvent(eAudioEvents audioEvent, float fVolume);
    void Service();
    void Initialise(CEntity* entity);
    void Terminate();
    void GetVehicleTypeForAudio();
    void IsAccInhibited(cVehicleParams&);
    void IsAccInhibitedBackwards(cVehicleParams&);
    void IsAccInhibitedForLowSpeed(cVehicleParams&);
    void IsAccInhibitedForTime();
    void InhibitAccForTime(uint);
    void IsCrzInhibitedForTime();
    void InhibitCrzForTime(uint);
    void GetAccelAndBrake(cVehicleParams&);
    float GetVolumeForDummyIdle(float, float);
    float GetFrequencyForDummyIdle(float, float);
    float GetVolumeForDummyRev(float, float);
    float GetFrequencyForDummyRev(float, float);
    void CancelVehicleEngineSound(short);
    void RequestNewPlayerCarEngineSound(short, float, float);
    void UpdateVehicleEngineSound(short, float, float);
    void StartVehicleEngineSound(short, float, float);
    void ProcessDummyStateTransition(short, float, cVehicleParams&);
    void ProcessDummyVehicleEngine(cVehicleParams&);
    void JustGotInVehicleAsDriver();
    void TurnOnRadioForVehicle();
    void TurnOffRadioForVehicle();
    void PlayerAboutToExitVehicleAsDriver();
    void DisableHelicoptor();
    void EnableHelicoptor();
    void CopHeli();
    float GetFreqForIdle(float);
    float GetFreqForPlayerEngineSound(cVehicleParams&, short);
    float GetVolForPlayerEngineSound(cVehicleParams&, short);
    void JustFinishedAccelerationLoop();
    void ProcessPlayerVehicleEngine(cVehicleParams&);
    void PlaySkidSound(short soundType, float speed, float volume);
    void JustWreckedVehicle();
    void PlayRoadNoiseSound(short soundType, float speed, float volume);
    void PlayFlatTyreSound(short soundType, float speed, float volume);
    void PlayReverseSound(short soundType, float speed, float volume);
    void UpdateGasPedalAudio(CVehicle* veh, int vehType);
    void ProcessVehicleFlatTyre(cVehicleParams&);
    void ProcessVehicleRoadNoise(cVehicleParams&);
    void ProcessReverseGear(cVehicleParams&);
    float GetVehicleDriveWheelSkidValue(CVehicle*, int, float, cTransmission*, float);
    float GetVehicleNonDriveWheelSkidValue(CVehicle*, int, cTransmission*, float);
    void ProcessVehicleSkidding(cVehicleParams&);
    void ProcessRainOnVehicle(cVehicleParams&);
    void PlayAircraftSound(short, short, short, float, float);
    void ProcessGenericJet(uchar, cVehicleParams&, float, float, float, float, float);
    void ProcessDummyJet(cVehicleParams&);
    void ProcessPlayerJet(cVehicleParams&);
    void ProcessDummySeaPlane(cVehicleParams&);
    void ProcessPlayerSeaPlane(cVehicleParams&);
    void ProcessAIHeli(cVehicleParams&);
    void ProcessDummyHeli(cVehicleParams&);
    void ProcessPlayerHeli(cVehicleParams&);
    void ProcessAIProp(cVehicleParams&);
    void ProcessDummyProp(cVehicleParams&);
    void ProcessPlayerProp(cVehicleParams&);
    void ProcessAircraft(cVehicleParams&);
    CVector GetAircraftNearPosition();
    void GetBaseVolumeForBicycleTyre(float);
    void PlayBicycleSound(short, short, short, float, float);
    void ProcessPlayerBicycle(cVehicleParams&);
    void ProcessDummyBicycle(cVehicleParams&);
    float GetFlyingMetalVolume(CPhysical*);
    void AddAudioEvent(int, CEntity*);
    void GetHornState(uchar*, cVehicleParams&);
    void GetSirenState(uchar*, uchar*, cVehicleParams&);
    void PlayHornOrSiren(uchar, uchar, uchar, cVehicleParams&);
    void ProcessVehicleSirenAlarmHorn(cVehicleParams&);
    void UpdateBoatSound(short, short, short, float, float);
    void StopGenericEngineSound(short);
    void ProcessBoatEngine(cVehicleParams&);
    void ProcessBoatMovingOverWater(cVehicleParams&);
    void UpdateTrainSound(short, short, short, float, float);
    void ProcessDummyTrainEngine(cVehicleParams&);
    void ProcessTrainTrackSound(cVehicleParams&);
    void ProcessPlayerTrainEngine(cVehicleParams&);
    void PlayTrainBrakeSound(short soundType, float speed, float volume);
    void ProcessPlayerTrainBrakes(cVehicleParams&);
    void JustGotOutOfVehicleAsDriver();
    void ProcessDummyRCPlane(cVehicleParams&);
    void ProcessPlayerRCPlane(cVehicleParams&);
    void ProcessDummyRCHeli(cVehicleParams&);
    void ProcessPlayerRCHeli(cVehicleParams&);
    void ProcessPlayerRCCar(cVehicleParams&);
    void ProcessPlayerHovercraft(cVehicleParams&);
    void ProcessPlayerGolfCart(cVehicleParams&);
    void UpdateGenericVehicleSound(short, short, short, short, float, float, float);
    void ProcessDummyGolfCart(cVehicleParams&);
    void ProcessDummyHovercraft(cVehicleParams&);
    void ProcessDummyRCCar(cVehicleParams&);
    void ProcessPlayerCombine(cVehicleParams&);
    void ProcessEngineDamage(cVehicleParams&);
    void ProcessSpecialVehicle(cVehicleParams&);
    void ProcessNitro(cVehicleParams&);
    void ProcessMovingParts(cVehicleParams&);
    void ProcessVehicle(CPhysical*);

public:
    static void StaticInitialise();
    static void StaticService() { /* Empty on purpose */ }
    static tVehicleAudioSettings* StaticGetPlayerVehicleAudioSettingsForRadio();
    static void EnableHelicoptors();
    static void DisableHelicoptors();
    static bool DoesBankSlotContainThisBank(short bankSlot, short bankId);
    static short DemandBankSlot(short bankId);
    static short RequestBankSlot(short bankId);
    static void StoppedUsingBankSlot(short bankSlot);
    static tVehicleAudioSettings GetVehicleAudioSettings(short vehId);

private:
    void UpdateParameters_Reversed(CAESound* sound, short curPlayPos);

public:
    static CPed*& s_pPlayerAttachedForRadio;
    static CPed*& s_pPlayerDriver;
    static bool& s_HelicoptorsDisabled;
    static short& s_NextDummyEngineSlot;
    static tVehicleAudioSettings*& s_pVehicleAudioSettingsForRadio;

    static constexpr int NUM_DUMMY_ENGINE_SLOTS = 10;
    static tEngineDummySlot(&s_DummyEngineSlots)[NUM_DUMMY_ENGINE_SLOTS];
};
VALIDATE_SIZE(CAEVehicleAudioEntity, 0x24C);

// indexes = (Vehicles modelid - 400)
static constexpr int NUM_VEH_AUDIO_SETTINGS = 232;
extern tVehicleAudioSettings const(&gVehicleAudioSettings)[NUM_VEH_AUDIO_SETTINGS];
