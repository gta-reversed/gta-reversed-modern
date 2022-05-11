#include "StdInc.h"

#include "AEVehicleAudioEntity.h"

#include "AEAudioHardware.h"
#include "AEAudioUtility.h"
#include "AESoundManager.h"
#include "AEAudioUtility.h"

CPed*&                  CAEVehicleAudioEntity::s_pPlayerAttachedForRadio = *(CPed**)0xB6B98C;
CPed*&                  CAEVehicleAudioEntity::s_pPlayerDriver = *(CPed**)0xB6B990;
bool&                   CAEVehicleAudioEntity::s_HelicoptorsDisabled = *(bool*)0xB6B994;
int16&                  CAEVehicleAudioEntity::s_NextDummyEngineSlot = *(int16*)0xB6B998;
tVehicleAudioSettings*& CAEVehicleAudioEntity::s_pVehicleAudioSettingsForRadio = *reinterpret_cast<tVehicleAudioSettings**>(0xB6B99C);
tEngineDummySlot (&CAEVehicleAudioEntity::s_DummyEngineSlots)[NUM_DUMMY_ENGINE_SLOTS] = *reinterpret_cast<tEngineDummySlot (*)[NUM_DUMMY_ENGINE_SLOTS]>(0xB6B9A0);


const tVehicleAudioSettings (&gVehicleAudioSettings)[NUM_VEH_AUDIO_SETTINGS] = *reinterpret_cast<const tVehicleAudioSettings (*)[232]>(0x860AF0);

bool IsSurfaceAudioGrass(eSurfaceType surface) {
    return g_surfaceInfos->IsAudioGrass(surface) || g_surfaceInfos->IsAudioLongGrass(surface);
}

bool IsSurfaceAudioEitherGravelWaterSand(eSurfaceType surface) {
    return g_surfaceInfos->IsAudioGravel(surface) || g_surfaceInfos->IsAudioSand(surface) || g_surfaceInfos->IsAudioWater(surface);
}

void CAEVehicleAudioEntity::InjectHooks() {
    RH_ScopedClass(CAEVehicleAudioEntity);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Constructor, 0x4F63E0);
    RH_ScopedInstall(Destructor, 0x6D0A10);
    RH_ScopedInstall(UpdateParameters, 0x4FB6C0);
    RH_ScopedInstall(Initialise, 0x4F7670);
    RH_ScopedInstall(StaticInitialise, 0x5B99F0);
    RH_ScopedInstall(Terminate, 0x4FB8C0);
    RH_ScopedInstall(GetAircraftNearPosition, 0x4F96A0);
    RH_ScopedInstall(GetFlyingMetalVolume, 0x4F6150);
    RH_ScopedInstall(GetVehicleAudioSettings, 0x4F5C10);
    RH_ScopedInstall(RequestBankSlot, 0x4F4D10);
    RH_ScopedInstall(DemandBankSlot, 0x4F4E60);
    RH_ScopedInstall(DoesBankSlotContainThisBank, 0x4F4E30);
    RH_ScopedInstall(StoppedUsingBankSlot, 0x4F4DF0);
    RH_ScopedInstall(EnableHelicoptors, 0x4F4EF0);
    RH_ScopedInstall(DisableHelicoptors, 0x4F4EE0);
    RH_ScopedInstall(EnableHelicoptor, 0x4F5C00);
    RH_ScopedInstall(DisableHelicoptor, 0x4F5BF0);
    RH_ScopedInstall(StaticGetPlayerVehicleAudioSettingsForRadio, 0x4F4ED0);
    // RH_ScopedInstall(StaticService,0x4F4EC0);
    // RH_ScopedInstall(GetVehicleTypeForAudio,0x4F4F00);
    // RH_ScopedInstall(IsAccInhibited,0x4F4F70);
    // RH_ScopedInstall(IsAccInhibitedBackwards,0x4F4FC0);
    // RH_ScopedInstall(IsAccInhibitedForLowSpeed,0x4F4FF0);
    // RH_ScopedInstall(IsAccInhibitedForTime,0x4F5020);

    RH_ScopedInstall(InhibitAccForTime, 0x4F5030);
    RH_ScopedInstall(IsCrzInhibitedForTime, 0x4F5050);
    RH_ScopedInstall(GetAccelAndBrake, 0x4F5080);
    RH_ScopedInstall(GetVolumeForDummyIdle, 0x4F51F0);
    RH_ScopedInstall(GetFrequencyForDummyIdle, 0x4F5310);
    // RH_ScopedInstall(GetVolumeForDummyRev,0x4F53D0);
    // RH_ScopedInstall(GetFrequencyForDummyRev,0x4F54F0);
    // RH_ScopedInstall(CancelVehicleEngineSound,0x4F55C0);
    RH_ScopedInstall(UpdateVehicleEngineSound, 0x4F56D0);
    RH_ScopedInstall(JustGotInVehicleAsDriver, 0x4F5700);
    RH_ScopedInstall(TurnOnRadioForVehicle, 0x4F5B20);
    RH_ScopedInstall(TurnOffRadioForVehicle, 0x4F5B60);
    RH_ScopedInstall(PlayerAboutToExitVehicleAsDriver, 0x4F5BA0);
    RH_ScopedInstall(CopHeli, 0x4F5C40);
    RH_ScopedInstall(GetFreqForIdle, 0x4F5C60);
    RH_ScopedInstall(GetVolForPlayerEngineSound, 0x4F5D00);
    RH_ScopedInstall(JustFinishedAccelerationLoop, 0x4F5E50);
    RH_ScopedInstall(UpdateGasPedalAudio, 0x4F5EB0);
    RH_ScopedInstall(GetVehicleDriveWheelSkidValue, 0x4F5F30);
    RH_ScopedInstall(GetVehicleNonDriveWheelSkidValue, 0x4F6000);
    RH_ScopedInstall(GetBaseVolumeForBicycleTyre, 0x4F60B0);
    // RH_ScopedInstall(GetHornState,0x4F61E0);
    RH_ScopedInstall(GetSirenState, 0x4F62A0);
    RH_ScopedInstall(StopGenericEngineSound, 0x4F6320);
    // RH_ScopedInstall(AddAudioEvent,0x4F6420);
    // RH_ScopedInstall(AddAudioEvent,0x4F7580);
    // RH_ScopedInstall(RequestNewPlayerCarEngineSound,0x4F7A50);
    // RH_ScopedInstall(StartVehicleEngineSound,0x4F7F20);
    // RH_ScopedInstall(GetFreqForPlayerEngineSound,0x4F8070);
    // RH_ScopedInstall(PlaySkidSound,0x4F8360);
    RH_ScopedInstall(PlayRoadNoiseSound, 0x4F84D0);
    RH_ScopedInstall(PlayFlatTyreSound, 0x4F8650);
    // RH_ScopedInstall(PlayReverseSound,0x4F87D0);
    // RH_ScopedInstall(ProcessVehicleFlatTyre,0x4F8940);
    RH_ScopedInstall(ProcessVehicleRoadNoise, 0x4F8B00);
    RH_ScopedInstall(ProcessReverseGear, 0x4F8DF0);
    RH_ScopedInstall(ProcessVehicleSkidding, 0x4F8F10);
    RH_ScopedInstall(ProcessRainOnVehicle, 0x4F92C0);
    // RH_ScopedInstall(PlayAircraftSound,0x4F93C0);
    // RH_ScopedInstall(PlayBicycleSound,0x4F9710);
    // RH_ScopedInstall(PlayHornOrSiren,0x4F99D0);
    RH_ScopedInstall(UpdateBoatSound, 0x4F9E90);
    RH_ScopedInstall(ProcessBoatMovingOverWater, 0x4FA0C0);
    RH_ScopedInstall(UpdateTrainSound, 0x4FA1C0);
    // RH_ScopedInstall(ProcessTrainTrackSound,0x4FA3F0);
    // RH_ScopedInstall(PlayTrainBrakeSound,0x4FA630);
    // RH_ScopedInstall(ProcessDummyRCPlane,0x4FA7C0);
    // RH_ScopedInstall(ProcessDummyRCHeli,0x4FAA80);
    // RH_ScopedInstall(UpdateGenericVehicleSound,0x4FAD40);
    // RH_ScopedInstall(ProcessEngineDamage,0x4FAE20);
    // RH_ScopedInstall(ProcessNitro,0x4FB070);
    RH_ScopedInstall(ProcessMovingParts, 0x4FB260);
    // RH_ScopedInstall(ProcessPlayerVehicleEngine,0x4FBB10);
    // RH_ScopedInstall(ProcessDummyStateTransition,0x4FCA10);
    // RH_ScopedInstall(JustGotOutOfVehicleAsDriver,0x4FCF40);
    // RH_ScopedInstall(JustWreckedVehicle,0x4FD0B0);
    // RH_ScopedInstall(ProcessPlayerProp,0x4FD290);
    // RH_ScopedInstall(ProcessDummyProp,0x4FD8F0);
    // RH_ScopedInstall(ProcessAIProp,0x4FDFD0);
    // RH_ScopedInstall(ProcessPlayerHeli,0x4FE420);
    // RH_ScopedInstall(ProcessDummyHeli,0x4FE940);
    // RH_ScopedInstall(ProcessAIHeli,0x4FEE20);
    // RH_ScopedInstall(ProcessPlayerSeaPlane,0x4FF320);
    // RH_ScopedInstall(ProcessDummySeaPlane,0x4FF7C0);
    // RH_ScopedInstall(ProcessGenericJet,0x4FF900);
    // RH_ScopedInstall(ProcessDummyBicycle,0x4FFDC0);
    // RH_ScopedInstall(ProcessPlayerBicycle,0x500040);
    RH_ScopedInstall(ProcessVehicleSirenAlarmHorn, 0x5002C0);
    // RH_ScopedInstall(ProcessBoatEngine,0x5003A0);
    // RH_ScopedInstall(ProcessDummyTrainEngine,0x500710);
    // RH_ScopedInstall(ProcessPlayerTrainBrakes,0x500AB0);
    // RH_ScopedInstall(ProcessPlayerCombine,0x500CE0);
    // RH_ScopedInstall(ProcessDummyRCCar,0x500DC0);
    // RH_ScopedInstall(ProcessDummyHovercraft,0x500F50);
    // RH_ScopedInstall(ProcessDummyGolfCart,0x501270);
    // RH_ScopedInstall(ProcessDummyVehicleEngine,0x501480);
    // RH_ScopedInstall(ProcessPlayerJet,0x501650);
    // RH_ScopedInstall(ProcessDummyJet,0x501960);
    RH_ScopedInstall(ProcessSpecialVehicle, 0x501AB0);
    RH_ScopedInstall(ProcessAircraft, 0x501C50);
    // RH_ScopedInstall(ProcessVehicle,0x501E10);
    // RH_ScopedInstall(Service,0x502280);
}

// 0x4F63E0
CAEVehicleAudioEntity::CAEVehicleAudioEntity() : CAEAudioEntity(), m_twinSkidSound() {
    m_bEnabled = false;
}

// 0x6D0A10
CAEVehicleAudioEntity::~CAEVehicleAudioEntity() {
    if (m_bEnabled) {
        Terminate();
    }
}

// 0x4F7670
void CAEVehicleAudioEntity::Initialise(CEntity* entity) {
    assert(entity);

    field_144 = 0;
    m_pEntity = entity;
    m_bPlayerDriver = false;
    m_bPlayerPassenger = false;
    m_bVehicleRadioPaused = false;
    m_bSoundsStopped = false;
    m_nEngineState = 0;
    m_nGearRelatedStuff = 0;
    field_AC = 0;
    m_nEngineBankSlotId = -1;
    m_nRainDropCounter = 0;
    field_7C = 0;
    field_B4 = 0;
    field_B8 = 0;
    field_BC = 0;
    m_nBoatHitWaveLastPlayedTime = 0;
    m_nTimeToInhibitAcc = 0;
    m_nTimeToInhibitCrz = 0;
    m_bNitroSoundPresent = false;
    m_bDisableHeliEngineSounds = false;
    m_nEngineSoundPlayPos = -1;
    m_nEngineSoundLastPlayedPos = -1;
    field_154 = 0;
    field_14E = 0;
    m_nAcclLoopCounter = 0;

    for (auto i = 0; auto& sound : m_aEngineSounds) {
        sound.Init(i++);
    }

    m_fHornVolume = -100.0f;
    m_fPlaneSoundVolume_Probably = -100.0f;
    m_nSkidSoundType = -1;
    m_nRoadNoiseSoundType = -1;
    m_nFlatTyreSoundType = -1;
    m_nReverseGearSoundType = -1;
    field_234 = -1.0f;
    m_fPlaneSoundSpeed = -1.0f;
    field_248 = -1.0f;

    m_pSkidSoundMaybe   = nullptr;
    m_pRoadNoiseSound   = nullptr;
    m_pFlatTyreSound    = nullptr;
    m_pReverseGearSound = nullptr;
    m_pHornTonSound     = nullptr;
    m_pSirenSound       = nullptr;
    m_pPoliceSirenSound = nullptr;

    field_238 = 0.0f;
    field_23C = 1.0f;
    field_240 = 0;

    m_settings = GetVehicleAudioSettings(entity->m_nModelIndex);
    m_bModelWithSiren = entity->AsVehicle()->UsesSiren();
    if (m_settings.m_nRadioType == eRadioType::RADIO_UNKNOWN)
        m_settings.m_nRadioID = eRadioID::RADIO_OFF;

    m_fGeneralVehicleSoundVolume = CAEAudioEntity::GetDefaultVolume(eAudioEvents::AE_GENERAL_VEHICLE_SOUND);

    switch (entity->m_nModelIndex) {
    case MODEL_PIZZABOY:
    case MODEL_CADDY:
    case MODEL_FAGGIO:
    case MODEL_BAGGAGE:
    case MODEL_FORKLIFT:
    case MODEL_VORTEX:
    case MODEL_KART:
    case MODEL_MOWER:
    case MODEL_SWEEPER:
    case MODEL_TUG:
        m_bInhibitAccForLowSpeed = true;
        break;
    default:
        m_bInhibitAccForLowSpeed = false;
        break;
    }

    switch (m_settings.m_nVehicleSoundType) {
    case VEHICLE_SOUND_CAR:
        m_fGeneralVehicleSoundVolume -= 1.5F;
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;
        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        if (m_bEnabled)
            return;

        if (m_settings.m_nEngineOffSoundBankId != -1 && m_settings.m_nEngineOffSoundBankId != 129)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_MOTORCYCLE:
    case VEHICLE_SOUND_BICYCLE:
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;

        if (m_settings.IsMotorcycle())
            m_fGeneralVehicleSoundVolume = m_fGeneralVehicleSoundVolume - 1.5F;

        if (m_bEnabled)
            return;

        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        if (m_nEngineDecelerateSoundBankId != -1)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_BOAT:
    case VEHICLE_SOUND_TRAIN:
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;
        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        if (m_bEnabled)
            return;

        if (m_settings.m_nEngineOffSoundBankId != -1 && m_settings.m_nEngineOffSoundBankId != 129)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_HELI:
    case VEHICLE_SOUND_NON_VEH:
        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_PLANE:
        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;
        if (m_bEnabled)
            return;

        if (m_settings.m_nEngineOffSoundBankId != -1)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_TRAILER:
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;
        m_fGeneralVehicleSoundVolume = m_fGeneralVehicleSoundVolume - 1.5F;
        if (m_bEnabled)
            return;

        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        if (m_nEngineDecelerateSoundBankId != -1)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    default:
        return;
    }
}

// 0x5B99F0
void CAEVehicleAudioEntity::StaticInitialise() {
    for (auto& dummyEng : s_DummyEngineSlots) {
        dummyEng.m_nBankId = -1;
        dummyEng.m_nUsageCount = 0;
    }

    AEAudioHardware.LoadSoundBank(138, 19);
    AEAudioHardware.LoadSoundBank(13, 18);
    AEAudioHardware.LoadSoundBank(74, 17);

    s_pVehicleAudioSettingsForRadio = nullptr;
    s_pPlayerAttachedForRadio = nullptr;
    s_pPlayerDriver = nullptr;
    s_NextDummyEngineSlot = 0;
    s_HelicoptorsDisabled = false;
}

// 0x4FB8C0
void CAEVehicleAudioEntity::Terminate() {
    if (!m_bEnabled)
        return;

    for (auto& sound : m_aEngineSounds) {
        if (sound.m_pSound) {
            sound.m_pSound->SetIndividualEnvironment(SOUND_REQUEST_UPDATES, false);
            sound.m_pSound->StopSound();
            sound.m_pSound = nullptr;
        }
    }

    PlaySkidSound(-1, 1.0F, -100.0F);
    PlayTrainBrakeSound(-1, 1.0F, -100.0F);

    if (m_pSkidSoundMaybe) {
        m_pSkidSoundMaybe->SetIndividualEnvironment(SOUND_REQUEST_UPDATES, false);
        m_pSkidSoundMaybe->StopSound();
        m_pSkidSoundMaybe = nullptr;
        m_nSkidSoundType = -1;
    }

    if (m_pRoadNoiseSound) {
        m_pRoadNoiseSound->SetIndividualEnvironment(SOUND_REQUEST_UPDATES, false);
        m_pRoadNoiseSound->StopSound();
        m_pRoadNoiseSound = nullptr;
        m_nRoadNoiseSoundType = -1;
    }

    if (m_pFlatTyreSound) {
        m_pFlatTyreSound->SetIndividualEnvironment(SOUND_REQUEST_UPDATES, false);
        m_pFlatTyreSound->StopSound();
        m_pFlatTyreSound = nullptr;
        m_nFlatTyreSoundType = -1;
    }

    if (m_pReverseGearSound) {
        m_pReverseGearSound->SetIndividualEnvironment(SOUND_REQUEST_UPDATES, false);
        m_pReverseGearSound->StopSound();
        m_pReverseGearSound = nullptr;
        m_nReverseGearSoundType = -1;
    }

    if (m_pHornTonSound) {
        m_pHornTonSound->StopSoundAndForget();
        m_pHornTonSound = nullptr;
    }

    if (m_pSirenSound) {
        m_pSirenSound->StopSoundAndForget();
        m_pSirenSound = nullptr;
    }

    if (m_pPoliceSirenSound) {
        m_pPoliceSirenSound->StopSoundAndForget();
        m_pPoliceSirenSound = nullptr;
    }

    if (m_bPlayerDriver) {
        switch (m_settings.m_nRadioType) {
        case RADIO_CIVILIAN:
        case RADIO_UNKNOWN:
        case RADIO_EMERGENCY:
            AudioEngine.StopRadio(&m_settings, false); // inlined
            break;
        }
    }

    if (m_nEngineBankSlotId != -1) {
        const auto usedSlot = m_nEngineBankSlotId - 7;
        auto&      dummyEng = s_DummyEngineSlots[usedSlot];
        if (usedSlot >= 0 && usedSlot < NUM_DUMMY_ENGINE_SLOTS && dummyEng.m_nBankId == m_nEngineDecelerateSoundBankId) {
            dummyEng.m_nUsageCount = std::max(0, dummyEng.m_nUsageCount - 1);
        }

        m_nEngineBankSlotId = -1;
    }

    m_nEngineDecelerateSoundBankId = -1;
    m_nEngineAccelerateSoundBankId = -1;
    m_pEntity = nullptr;
    m_nEngineState = 0;

    if (m_bPlayerDriver) {
        m_bPlayerDriver = false;
        s_pPlayerDriver = nullptr;
    } else if (m_bPlayerPassenger) {
        m_bPlayerPassenger = false;
    } else {
        m_bVehicleRadioPaused = false;
        m_bEnabled = false;
        return;
    }

    s_pPlayerAttachedForRadio = nullptr;
    s_pVehicleAudioSettingsForRadio = nullptr;
    m_bVehicleRadioPaused = false;
    m_bEnabled = false;
}

// 0x4F4ED0
tVehicleAudioSettings* CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio() {
    return s_pVehicleAudioSettingsForRadio;
}

// 0x4F4EE0
void CAEVehicleAudioEntity::EnableHelicoptors() {
    s_HelicoptorsDisabled = true;
}

// 0x4F4EF0
void CAEVehicleAudioEntity::DisableHelicoptors() {
    s_HelicoptorsDisabled = false;
}

// 0x4F5C00
void CAEVehicleAudioEntity::EnableHelicoptor() {
    m_bDisableHeliEngineSounds = false;
}

// 0x4F5BF0
void CAEVehicleAudioEntity::DisableHelicoptor() {
    m_bDisableHeliEngineSounds = true;
}

// 0x4F4E30
bool CAEVehicleAudioEntity::DoesBankSlotContainThisBank(int16 bankSlot, int16 bankId) {
    const auto usedSlot = bankSlot - 7;
    if (usedSlot < 0 || usedSlot > NUM_DUMMY_ENGINE_SLOTS)
        return false;

    return s_DummyEngineSlots[usedSlot].m_nBankId == bankId;
}

// 0x4F4E60
int16 CAEVehicleAudioEntity::DemandBankSlot(int16 bankId) {
    const auto requestResult = RequestBankSlot(bankId);
    if (requestResult != -1)
        return requestResult;

    auto slotToFree = 0;
    for (auto i = 1; i < NUM_DUMMY_ENGINE_SLOTS; ++i) {
        if (s_DummyEngineSlots[i].m_nUsageCount < s_DummyEngineSlots[0].m_nUsageCount) {
            slotToFree = i;
            break;
        }
    }

    s_DummyEngineSlots[slotToFree].m_nUsageCount = 0;
    return RequestBankSlot(bankId);
}

// 0x4F4D10
int16 CAEVehicleAudioEntity::RequestBankSlot(int16 bankId) {
    auto freeSlot = -1;
    for (auto i = 0; i < NUM_DUMMY_ENGINE_SLOTS; ++i) {
        auto& dummyEng = s_DummyEngineSlots[i];
        if (dummyEng.m_nBankId == bankId) {
            dummyEng.m_nUsageCount++;
            return i + 7;
        }

        if (dummyEng.m_nUsageCount <= 0)
            freeSlot = i;
    }

    if (freeSlot == -1)
        return -1;

    for (auto i = 0; i < NUM_DUMMY_ENGINE_SLOTS; ++i) {
        const auto iSlot = (s_NextDummyEngineSlot + i) % NUM_DUMMY_ENGINE_SLOTS;
        auto& dummyEng = s_DummyEngineSlots[iSlot];
        if (dummyEng.m_nUsageCount > 0)
            continue;

        freeSlot = iSlot;
        ++dummyEng.m_nUsageCount;
        s_NextDummyEngineSlot = (freeSlot + 1) % NUM_DUMMY_ENGINE_SLOTS;
        break;
    }

    AESoundManager.CancelSoundsInBankSlot(freeSlot + 7, true);
    AEAudioHardware.LoadSoundBank(bankId, freeSlot + 7);
    s_DummyEngineSlots[freeSlot].m_nBankId = bankId;
    s_DummyEngineSlots[freeSlot].m_nUsageCount = 1;
    return freeSlot + 7;
}

void CAEVehicleAudioEntity::StoppedUsingBankSlot(int16 bankSlot) {
    const auto usedSlot = bankSlot - 7;
    if (usedSlot < 0 || usedSlot > NUM_DUMMY_ENGINE_SLOTS)
        return;

    auto& dummyEng = s_DummyEngineSlots[usedSlot];
    dummyEng.m_nUsageCount = std::max(0, dummyEng.m_nUsageCount - 1);
}

// 0x4F5C10
tVehicleAudioSettings CAEVehicleAudioEntity::GetVehicleAudioSettings(int16 vehId) {
    return gVehicleAudioSettings[vehId - 400];
}

void CAEVehicleAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    CAEVehicleAudioEntity::UpdateParameters_Reversed(sound, curPlayPos);
}
// 0x4FB6C0
void CAEVehicleAudioEntity::UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos) {
    if (!sound)
        return;

    if (sound->m_nEvent == eAudioEvents::AE_BONNET_FLUBBER_FLUBBER) {
        if (!sound->m_pPhysicalEntity)
            return;

        const auto fBaseVolume = static_cast<float>(m_pAudioEventVolumes[eAudioEvents::AE_BONNET_FLUBBER_FLUBBER]);
        sound->m_fVolume = fBaseVolume + CAEVehicleAudioEntity::GetFlyingMetalVolume(sound->m_pPhysicalEntity->AsPhysical());
    }

    if (sound->m_nEvent == eAudioEvents::AE_BOAT_HIT_WAVE) {
        if (curPlayPos == -1)
            return;

        sound->SetPosition(m_pEntity->GetPosition());
        if (CWeather::UnderWaterness >= 0.5F)
            sound->StopSound();
    }

    if (curPlayPos == -1) {
        if (sound == m_pSkidSoundMaybe)
            m_pSkidSoundMaybe = nullptr;
        else if (sound == m_pRoadNoiseSound)
            m_pRoadNoiseSound = nullptr;
        else if (sound == m_pFlatTyreSound)
            m_pFlatTyreSound = nullptr;
        else if (sound == m_pReverseGearSound)
            m_pReverseGearSound = nullptr;
        else if (sound == m_pHornTonSound)
            m_pHornTonSound = nullptr;
        else if (sound == m_pSirenSound)
            m_pSirenSound = nullptr;
        else if (sound == m_pPoliceSirenSound)
            m_pPoliceSirenSound = nullptr;
        else {
            for (auto& engSound : m_aEngineSounds) {
                if (engSound.m_pSound == sound) {
                    engSound.m_pSound = nullptr;
                    break;
                }
            }
        }
    } else {
        if ((m_settings.IsFlyingVehicle() || m_settings.IsNonVeh()) && m_aEngineSounds[3].m_pSound)
            sound->SetPosition(CAEVehicleAudioEntity::GetAircraftNearPosition());
        else
            sound->SetPosition(m_pEntity->GetPosition());
    }

    if ((m_settings.IsCar() || m_settings.IsMotorcycle()) && sound == m_aEngineSounds[4].m_pSound) {
        m_nEngineSoundLastPlayedPos = m_nEngineSoundPlayPos;
        m_nEngineSoundPlayPos = curPlayPos;
    }
}

// 0x4F6420
void CAEVehicleAudioEntity::AddAudioEvent(eAudioEvents event, float fVolume) {
    plugin::CallMethod<0x4F6420, CAEVehicleAudioEntity*, eAudioEvents, float>(this, event, fVolume);
}

// 0x4F7580
void CAEVehicleAudioEntity::AddAudioEvent(eAudioEvents event, CVehicle* vehicle) {
    plugin::CallMethod<0x4F7580, CAEVehicleAudioEntity*, eAudioEvents, CVehicle*>(this, event, vehicle);
}

void CAEVehicleAudioEntity::Service() {
    plugin::CallMethod<0x502280, CAEVehicleAudioEntity*>(this);
}

void CAEVehicleAudioEntity::StaticService() {
    // NOP
}

CVector CAEVehicleAudioEntity::GetAircraftNearPosition() {
    static const int16 snHeliAudioComponent = tComponent::COMPONENT_WING_RR;

    CVector result;
    if (m_settings.IsHeli())
        m_pEntity->AsVehicle()->GetComponentWorldPosition(snHeliAudioComponent, result);
    else
        result = m_pEntity->GetPosition();

    return result;
}

// 0x4F6150
float CAEVehicleAudioEntity::GetFlyingMetalVolume(CPhysical* physical) {
    const auto fTurnSpeedSquared = physical->m_vecTurnSpeed.SquaredMagnitude();
    if (fTurnSpeedSquared >= 0.5625F)
        return CAEAudioUtility::AudioLog10(1.0F) * 10.0F;

    const auto fVol = fTurnSpeedSquared / 0.5625F;
    if (fVol < 1.0e-10F)
        return -100.0F;

    return CAEAudioUtility::AudioLog10(fVol) * 10.0F;
}

// 0x4FA630
void CAEVehicleAudioEntity::PlayTrainBrakeSound(int16 soundType, float speed, float volume) {
    plugin::CallMethod<0x4FA630, CAEAudioEntity*, int16, float, float>(this, soundType, speed, volume);
}

// 0x4F4F00
uint32 CAEVehicleAudioEntity::GetVehicleTypeForAudio() {
    return plugin::CallMethodAndReturn<uint32, 0x4F4F00, CAEVehicleAudioEntity*>(this);
}

// 0x4F4F70
bool CAEVehicleAudioEntity::IsAccInhibited(cVehicleParams& params) {
    return !AEAudioHardware.IsSoundBankLoaded(m_nEngineAccelerateSoundBankId, 40) || params.m_nBreakState > 0 || params.m_bHandbrakeOn || IsAccInhibitedBackwards(params);
}

// inlined?
// 0x4F4FC0
bool CAEVehicleAudioEntity::IsAccInhibitedBackwards(cVehicleParams& params) {
    return params.m_fWheelSpinForAudio > 5.0f || !params.m_nWheelsOnGround;
}

// 0x4F4FF0
bool CAEVehicleAudioEntity::IsAccInhibitedForLowSpeed(cVehicleParams& params) {
    return !m_bInhibitAccForLowSpeed && params.m_fVelocity < 0.1f; // 0.1f is static
}

// inlined?
// 0x4F5020
bool CAEVehicleAudioEntity::IsAccInhibitedForTime() {
    return m_nTimeToInhibitAcc < CTimer::GetTimeInMS();
}

// unused
// [ANDROID IDB] used in CAEVehicleAudioEntity::ProcessPlayerVehicleEngine
// 0x4F5030
void CAEVehicleAudioEntity::InhibitAccForTime(uint32 time) {
    m_nTimeToInhibitAcc = time + CTimer::GetTimeInMS();
}

// inlined?
// 0x4F5050
bool CAEVehicleAudioEntity::IsCrzInhibitedForTime() {
    return m_nTimeToInhibitCrz < CTimer::GetTimeInMS();
}

// 0x4F5080
void CAEVehicleAudioEntity::GetAccelAndBrake(cVehicleParams& vehParams) {
    if (CReplay::Mode == MODE_PLAYBACK) {
        vehParams.m_nGasState   = (int16)(std::clamp(vehParams.m_pVehicle->m_fGasPedal, 0.0f, 1.0f) * 255.0f);
        vehParams.m_nBreakState = (int16)(std::clamp(vehParams.m_pVehicle->m_fBreakPedal, 0.0f, 1.0f) * 255.0f);
    } else {
        if (!s_pPlayerDriver || m_bVehicleRadioPaused || s_pPlayerDriver->m_nPedState == PEDSTATE_ARRESTED || !s_pPlayerDriver->IsAlive()) {
            vehParams.m_nGasState = 0;
            vehParams.m_nBreakState = 0;
        } else {
            CPad* pad = s_pPlayerDriver->AsPlayer()->GetPadFromPlayer();
            vehParams.m_nGasState = pad->GetAccelerate();
            vehParams.m_nBreakState = pad->GetBrake();
        }
    }
}

// 0x4F51F0
float CAEVehicleAudioEntity::GetVolumeForDummyIdle(float fGearRevProgress, float fRevProgressBaseline) {
    if (m_pEntity->m_nModelIndex == MODEL_CADDY)
        return -3.0f - 30.0f;

    auto* vehicle = m_pEntity->AsVehicle();
    const auto fGearRevToMaxProgress = clamp<float>(fGearRevProgress / 0.2f, 0.0f, 1.0f);

    float fVolume = 3.0f * fGearRevToMaxProgress - 3.0f;
    if (vehicle->vehicleFlags.bIsDrowning)
        fVolume -= 6.0f;
    if (vehicle->m_pTrailer)
        fVolume += 6.0f;
    fVolume += m_settings.m_fHornVolumeDelta;

    if (m_nEngineState == 2) {
        static float afVolumePoints[5][2] = { {0.0f, 1.0f}, {0.3f, 1.0f}, {0.5f, 1.0f}, {0.7f, 0.7f}, {1.0f, 0.0f} };
        fVolume += CAEAudioUtility::AudioLog10(CAEAudioUtility::GetPiecewiseLinear(fRevProgressBaseline, 5, afVolumePoints)) * 20.0f;
    } else if (fRevProgressBaseline <= 0.99f) {
        fVolume += CAEAudioUtility::AudioLog10(fRevProgressBaseline) * 10.0f;
    }
    return fVolume;
}

// 0x4F5310
float CAEVehicleAudioEntity::GetFrequencyForDummyIdle(float fGearRevProgress, float fRevProgressBaseline) {
    if (m_pEntity->m_nModelIndex == MODEL_CADDY)
        return 1.0f;

    auto* vehicle = m_pEntity->AsVehicle();
    const auto fGearRevToMaxProgress = clamp<float>(fGearRevProgress / 0.2f, 0.0f, 1.0f);

    float fFreq = 0.35f * fGearRevToMaxProgress + 0.85f;
    if (vehicle->vehicleFlags.bIsDrowning)
        fFreq *= 0.7f;

    if (m_nEngineState == 2) {
        static float afFreqPoints[5][2] = {
            { 0.0f, 1.00f },
            { 0.3f, 1.00f },
            { 0.5f, 0.85f },
            { 0.7f, 0.85f },
            { 1.0f, 0.85f },
        };
        fFreq *= CAEAudioUtility::GetPiecewiseLinear(fRevProgressBaseline, 5, afFreqPoints);
    }
    return fFreq;
}

// 0x4F53D0
float CAEVehicleAudioEntity::GetVolumeForDummyRev(float a, float b) {
    return plugin::CallMethodAndReturn<float, 0x4F53D0, CAEVehicleAudioEntity*, float, float>(this, a, b);
}

// 0x4F54F0
float CAEVehicleAudioEntity::GetFrequencyForDummyRev(float a, float b) {
    return plugin::CallMethodAndReturn<float, 0x4F54F0, CAEVehicleAudioEntity*, float, float>(this, a, b);
}

// 0x4F55C0
void CAEVehicleAudioEntity::CancelVehicleEngineSound(int16 engineSoundStateId) {
    plugin::CallMethod<0x4F55C0, CAEVehicleAudioEntity*, int16>(this, engineSoundStateId);
}

// 0x4F56D0
void CAEVehicleAudioEntity::UpdateVehicleEngineSound(int16 engineState, float speed, float volumeDelta) {
    if (CAESound* sound = m_aEngineSounds[engineState].m_pSound) {
        sound->m_fVolume = m_fGeneralVehicleSoundVolume + volumeDelta;
        sound->m_fSpeed = speed;
    }
}

// 0x4F5700
void CAEVehicleAudioEntity::JustGotInVehicleAsDriver() {
    s_pPlayerDriver = m_pEntity->AsVehicle()->m_pDriver;

    m_fGeneralVehicleSoundVolume = (float)CAEAudioEntity::m_pAudioEventVolumes[AE_GENERAL_VEHICLE_SOUND];

    switch (m_settings.m_nVehicleSoundType) {
    case VEHICLE_SOUND_CAR:
    case VEHICLE_SOUND_MOTORCYCLE: {
        m_nGearRelatedStuff = 0;
        field_AC = 0;
        m_nEngineSoundPlayPos = -1;
        m_nEngineSoundLastPlayedPos = -1;

        if (AESoundManager.AreSoundsPlayingInBankSlot(40))
            AESoundManager.CancelSoundsInBankSlot(40, false);

        if (m_nEngineDecelerateSoundBankId == -1 || m_nEngineAccelerateSoundBankId == -1)
            return;

        if (m_nEngineBankSlotId == -1)
            m_nEngineBankSlotId = DemandBankSlot(m_nEngineDecelerateSoundBankId);

        if (AEAudioHardware.IsSoundBankLoaded(m_nEngineAccelerateSoundBankId, 40))
            AEAudioHardware.LoadSoundBank(m_nEngineAccelerateSoundBankId, 40);

        if (m_nEngineState != 1 || m_nEngineBankSlotId == -1) {
            for (auto i = 0; i < std::size(m_aEngineSounds); i++) {
                CancelVehicleEngineSound(i);
            }
            m_nEngineState = 0;
        } else {
            for (auto i = 0; i < std::size(m_aEngineSounds); i++) {
                if (i != 2)
                    CancelVehicleEngineSound(i);
            }
            m_nEngineState = 0;
        }
        break;
    }
    case VEHICLE_SOUND_PLANE:
    case VEHICLE_SOUND_HELI:
    case VEHICLE_SOUND_NON_VEH: {
        for (auto i = 0; i < std::size(m_aEngineSounds); i++) {
            CancelVehicleEngineSound(i);
        }

        if (m_nEngineAccelerateSoundBankId != -1 && !AEAudioHardware.IsSoundBankLoaded(m_nEngineAccelerateSoundBankId, 40)) {
            if (AESoundManager.AreSoundsPlayingInBankSlot(40))
                AESoundManager.CancelSoundsInBankSlot(40, false);
            AEAudioHardware.LoadSoundBank(m_nEngineAccelerateSoundBankId, 40);
        }

        if (m_nEngineDecelerateSoundBankId != -1 && m_nEngineBankSlotId == -1)
            m_nEngineBankSlotId = DemandBankSlot(m_nEngineDecelerateSoundBankId);

        m_fPlaneSoundSpeed = -1.0f;
        m_fPlaneSoundVolume_Probably = -100.0f;
        break;
    }
    case VEHICLE_SOUND_BICYCLE: {
        if (AESoundManager.AreSoundsPlayingInBankSlot(40))
            AESoundManager.CancelSoundsInBankSlot(40, false);

        for (auto i = 0; i < std::size(m_aEngineSounds); i++) {
            CancelVehicleEngineSound(i);
        }

        if (m_nEngineBankSlotId == -1)
            m_nEngineBankSlotId = DemandBankSlot(m_nEngineDecelerateSoundBankId);

        if (AEAudioHardware.IsSoundBankLoaded(m_nEngineDecelerateSoundBankId, 40))
            AEAudioHardware.LoadSoundBank(m_nEngineDecelerateSoundBankId, 40);
        break;
    }
    case VEHICLE_SOUND_BOAT: {
        if (m_nEngineBankSlotId == -1)
            m_nEngineBankSlotId = DemandBankSlot(m_nEngineDecelerateSoundBankId);
        break;
    }
    case VEHICLE_SOUND_TRAIN: {
        if (AESoundManager.AreSoundsPlayingInBankSlot(40))
            AESoundManager.CancelSoundsInBankSlot(40, false);

        if (m_nEngineBankSlotId == -1)
            m_nEngineBankSlotId = DemandBankSlot(m_nEngineDecelerateSoundBankId);

        if (AEAudioHardware.IsSoundBankLoaded(m_nEngineDecelerateSoundBankId, 40))
            AEAudioHardware.LoadSoundBank(m_nEngineDecelerateSoundBankId, 40);

        break;
    }
    case VEHICLE_SOUND_TRAILER: {
        if (AESoundManager.AreSoundsPlayingInBankSlot(40)) {
            AESoundManager.CancelSoundsInBankSlot(40, false);
        }

        for (auto i = 0; i < std::size(m_aEngineSounds); i++) {
            CancelVehicleEngineSound(i);
        }
        if (m_nEngineDecelerateSoundBankId != -1 && m_nEngineBankSlotId == -1) {
            m_nEngineBankSlotId = DemandBankSlot(m_nEngineDecelerateSoundBankId);
            if (AEAudioHardware.IsSoundBankLoaded(m_nEngineDecelerateSoundBankId, 40))
                AEAudioHardware.LoadSoundBank(m_nEngineDecelerateSoundBankId, 40);
        }
        break;
    }
    }
}

// 0x4F5B20
void CAEVehicleAudioEntity::TurnOnRadioForVehicle() {
    s_pVehicleAudioSettingsForRadio = &m_settings;
    s_pPlayerAttachedForRadio = m_pEntity->AsVehicle()->m_pDriver;
    switch (m_settings.m_nRadioType) {
    case 0:
    case 1:
    case 2: {
        AudioEngine.StartRadio(&m_settings);
        break;
    }
    }
}

// 0x4F5B60
void CAEVehicleAudioEntity::TurnOffRadioForVehicle() {
    s_pVehicleAudioSettingsForRadio = nullptr;
    s_pPlayerAttachedForRadio = nullptr;
    switch (m_settings.m_nRadioType) {
    case RADIO_CIVILIAN:
    case RADIO_SPECIAL:
    case RADIO_UNKNOWN: {
        AudioEngine.StopRadio(&m_settings, false); // inlined
        break;
    }
    }
}

// 0x4F5BA0
void CAEVehicleAudioEntity::PlayerAboutToExitVehicleAsDriver() {
    m_bVehicleRadioPaused = true;
    if (m_bPlayerDriver) {
        TurnOffRadioForVehicle();
    }
}

// 0x4F5C40
bool CAEVehicleAudioEntity::CopHeli() {
    const auto modelIndex = m_pEntity->m_nModelIndex;
    return modelIndex == MODEL_MAVERICK || modelIndex == MODEL_VCNMAV;
}

// 0x4F5C60
float CAEVehicleAudioEntity::GetFreqForIdle(float velocityPercentage) {
    static float points[][2] = {
        { 0.000f, 0.00f },
        { 0.075f, 0.70f },
        { 0.150f, 1.10f },
        { 0.250f, 1.25f },
        { 1.000f, 1.70f }, // 1.0001f?
    };
    return CAEAudioUtility::GetPiecewiseLinear(velocityPercentage, std::size(points), points);
}

// 0x4F5D00
float CAEVehicleAudioEntity::GetVolForPlayerEngineSound(cVehicleParams& vehParams, int16 gear) {
    constexpr float fLowSpeedVol = -2.0f;

    float fVolume = 0.0f;
    switch (gear) {
    case 1:
        fVolume = 4.0f * vehParams.m_fVelocityChangingPercentage - 4.0f;
        break;
    case 2: {
        if (vehParams.m_pVehicle->m_nModelIndex == MODEL_CADDY)
            fVolume = -30.0f - 3.0f;
        else
            fVolume = 1.5f * vehParams.m_fVelocityChangingPercentage - 3.0f;
        break;
    }
    case 3: {
        if (m_bInhibitAccForLowSpeed)
            fVolume = fLowSpeedVol;
        else
            fVolume = -0.013333f * field_AC;
        break;
    }
    case 4: {
        if (m_bInhibitAccForLowSpeed)
            fVolume = fLowSpeedVol;
        else
            fVolume = 0.4f * float(m_nGearRelatedStuff) + fLowSpeedVol;
        break;
    }
    case 5:
        return GetVolForPlayerEngineSound(vehParams, 2);
    }

    CVehicle* vehicle = m_pEntity->AsVehicle();

    fVolume += m_settings.m_fHornVolumeDelta;
    if (vehicle->vehicleFlags.bIsDrowning)
        fVolume -= 6.0f;

    if (vehicle->m_pTrailer)
        fVolume += 6.0f;

    if (m_bNitroSoundPresent && field_248 <= 1.0f && field_248 >= 0.0f)
        fVolume += 3.0f * field_248;

    return fVolume;
}

// 0x4F5E50
bool CAEVehicleAudioEntity::JustFinishedAccelerationLoop() {
    if (m_nAcclLoopCounter < 10) {
        m_nAcclLoopCounter++;
        return false;
    }

    if (m_nEngineSoundPlayPos < 0)
        return false;

    if (m_nEngineSoundLastPlayedPos < 0)
        return false;

    CAESound* sound = m_aEngineSounds[4].m_pSound;
    if (!sound || m_nEngineSoundPlayPos <= sound->m_nSoundLength - 120)
        return false;

    m_nAcclLoopCounter = 0;
    return true;
}

// 0x4F5EB0
void CAEVehicleAudioEntity::UpdateGasPedalAudio(CVehicle* vehicle, int32 vehicleType) {
    const float fAbsGasPedal = fabs(vehicle->m_fGasPedal);
    float& fSomeGasPedalStuff = ((eVehicleType)vehicleType == VEHICLE_TYPE_BIKE) ? vehicle->AsBike()->m_fGasPedalAudio : vehicle->AsAutomobile()->m_fSomeGasPedalStuff;
    if (fAbsGasPedal <= fSomeGasPedalStuff)
        fSomeGasPedalStuff = std::max(fAbsGasPedal, fSomeGasPedalStuff - 0.07f);
    else
        fSomeGasPedalStuff = std::min(fAbsGasPedal, fSomeGasPedalStuff + 0.09f);
}

// 0x4F5F30
float CAEVehicleAudioEntity::GetVehicleDriveWheelSkidValue(CVehicle* vehicle, int32 wheelState, float fSomeGasPedalAudioStuff, cTransmission& transmission, float fVelocity) {
    /* useless
    if (!*(bool*)0x8CBD80)
        return 0.0f;
    */

    switch (wheelState) {
    case WHEEL_STATE_SPINNING: {
        if (fSomeGasPedalAudioStuff > 0.4f)
            return (fSomeGasPedalAudioStuff - 0.4f) * 1.66f * 0.75f;
        break;
    }
    case WHEEL_STATE_SKIDDING: {
        return std::min(1.0f, fabs(fVelocity)) * 0.75f;
    }
    case WHEEL_STATE_FIXED: {
        const float fAbsVelocity = fabs(fVelocity);
        if (fAbsVelocity > 0.04f)
            return std::min(fAbsVelocity * 5.0f, 1.0f) * 1.2f;
        break;
    }
    }
    return 0.0f;
}

// 0x4F6000
float CAEVehicleAudioEntity::GetVehicleNonDriveWheelSkidValue(CVehicle* vehicle, int32 wheelState, cTransmission& transmission, float fVelocity) {
    static bool s_bUnknown = true; // 0x8CBD81
    if (!s_bUnknown) {
        return 0.0f;
    }

    switch (wheelState) {
    case WHEEL_STATE_SKIDDING: {
        const float fAbsVelocity = std::min(1.0f, fabs(fVelocity)); // at most 1.0f
        if (m_settings.m_nVehicleSoundType == VEHICLE_SOUND_BICYCLE)
            return fAbsVelocity * 0.75f * 0.2f;
        else
            return fAbsVelocity * 0.75f;
    }
    case WHEEL_STATE_FIXED: {
        const float fAbsVelocity = fabs(fVelocity);
        if (fAbsVelocity > 0.04f)
            return std::min(fAbsVelocity * 5.0f, 1.0f) * 1.2f;
        break;
    }
    default:
        return 0.0f;
    }
}

// 0x4F60B0
float CAEVehicleAudioEntity::GetBaseVolumeForBicycleTyre(float fGearVelocityProgress) {
    static float points[5][2] = {
        { 0.0f,    0.0f  },
        { 0.075f,  0.7f  },
        { 0.15f,   1.1f  },
        { 0.25f,   1.25f },
        { 1.0001f, 1.7f  },
    };
    return CAEAudioUtility::GetPiecewiseLinear(fGearVelocityProgress, std::size(points), points);
}

// 0x4F61E0
void CAEVehicleAudioEntity::GetHornState(bool* out, cVehicleParams& params) {
    plugin::CallMethod<0x4F61E0, CAEVehicleAudioEntity*, bool*, cVehicleParams&>(this, out, params);
}

// 0x4F62A0
void CAEVehicleAudioEntity::GetSirenState(bool& bSirenOrAlarm, bool& bHorn, cVehicleParams& params) {
    // NOTSA: GTA doesn't set these variables to false, but we do (so the caller doesn't have to)
    bSirenOrAlarm = false;
    bHorn = false;

    if (m_bSoundsStopped)
        return;

    if (!m_bModelWithSiren)
        return;

    CVehicle* vehicle = params.m_pVehicle;
    if (vehicle->vehicleFlags.bSirenOrAlarm != 0 && vehicle->m_nStatus != STATUS_ABANDONED) {
        bHorn = vehicle->m_nModelIndex != MODEL_MRWHOOP && vehicle->m_nHornCounter;
        bSirenOrAlarm = true;
    }
}

// 0x4F6320
void CAEVehicleAudioEntity::StopGenericEngineSound(int16 index) {
    if (CAESound*& sound = m_aEngineSounds[index].m_pSound) {
        sound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        sound->StopSound();
        sound = nullptr;
    }
}

// 0x4F7A50
void CAEVehicleAudioEntity::RequestNewPlayerCarEngineSound(int16 vehicleSoundId, float speed, float changeSound) {
    plugin::CallMethod<0x4F7A50, CAEVehicleAudioEntity*, int16, float, float>(this, vehicleSoundId, speed, changeSound);
}

// 0x4F7F20
void CAEVehicleAudioEntity::StartVehicleEngineSound(int16 engineState, float engineSoundSpeed, float volume) {
    plugin::CallMethod<0x4F7F20, CAEVehicleAudioEntity*, int16, float, float>(this, engineState, engineSoundSpeed, volume);
}

// 0x4F8070
float CAEVehicleAudioEntity::GetFreqForPlayerEngineSound(cVehicleParams& vehParams, int16 engineState_QuestionMark) {
    return plugin::CallMethodAndReturn<float, 0x4F8070, CAEVehicleAudioEntity*, cVehicleParams&, int32>(this, vehParams, engineState_QuestionMark);
}

// 0x4F8360
void CAEVehicleAudioEntity::PlaySkidSound(int16 newSkidSoundType, float speed, float volumeDelta) {
    const float volume = m_fGeneralVehicleSoundVolume + volumeDelta;
    if (m_nSkidSoundType == newSkidSoundType) {
        if (m_nSkidSoundType != -1) {
            const auto& posn = m_pEntity->GetPosition();
            m_twinSkidSound.UpdateTwinLoopSound(posn, volumeDelta, speed);
        }
    } else {
        if (m_twinSkidSound.m_bIsInitialised)
            m_twinSkidSound.StopSoundAndForget();
        m_nSkidSoundType = newSkidSoundType;
        if (newSkidSoundType != -1) {
            m_twinSkidSound.Initialise(19, newSkidSoundType, newSkidSoundType + 1, this, 200, 1000, -1, -1);
            const auto& posn = m_pEntity->GetPosition();
            m_twinSkidSound.PlayTwinLoopSound(posn, volumeDelta, speed, 2.5f, 1.0f, SOUND_DEFAULT);
        }
    }
}

// 0x4F84D0
void CAEVehicleAudioEntity::PlayRoadNoiseSound(int16 newRoadNoiseSoundType, float speed, float volumeDelta) {
    const float volume = m_fGeneralVehicleSoundVolume + volumeDelta;
    if (m_nRoadNoiseSoundType != newRoadNoiseSoundType) {
        if (m_pRoadNoiseSound) {
            m_pRoadNoiseSound->SetIndividualEnvironment(SOUND_REQUEST_UPDATES, false);
            m_pRoadNoiseSound->StopSound();
            m_pRoadNoiseSound = nullptr;
        }

        // Create new sound
        m_nRoadNoiseSoundType = newRoadNoiseSoundType;
        if (newRoadNoiseSoundType != -1) {
            const auto& pos = m_pEntity->GetPosition();
            CAESound sound;
            sound.Initialise(19, newRoadNoiseSoundType, this, pos, volume, 1.0f, 1.0f, 1.0f, false, SOUND_REQUEST_UPDATES, 0.0f, 0);
            sound.m_fSpeed = speed;
            sound.m_fSoundDistance = 3.0f;
            m_pRoadNoiseSound = AESoundManager.RequestNewSound(&sound);
        }
    } else if (m_nRoadNoiseSoundType != -1 && m_pRoadNoiseSound) {
        // Same sound type already initialised, just set speed and volume
        m_pRoadNoiseSound->m_fSpeed = speed;
        m_pRoadNoiseSound->m_fVolume = volume;
    }
}

// 0x4F8650
void CAEVehicleAudioEntity::PlayFlatTyreSound(int16 newFlatTyreSoundType, float speed, float volumeDelta) {
    const float volume = m_fGeneralVehicleSoundVolume + volumeDelta;
    if (m_nFlatTyreSoundType != newFlatTyreSoundType) {
        if (m_pFlatTyreSound) {
            m_pFlatTyreSound->SetIndividualEnvironment(4, false);
            m_pFlatTyreSound->StopSound();
            m_pFlatTyreSound = nullptr;
        }

        // Create new sound
        m_nFlatTyreSoundType = newFlatTyreSoundType;
        if (newFlatTyreSoundType != -1) {
            const auto& pos = m_pEntity->GetPosition();
            CAESound sound;
            sound.Initialise(19, newFlatTyreSoundType, this, pos, volume, 1.0f, 1.0f, 1.0f, false, SOUND_REQUEST_UPDATES, 0.0f, 0);
            sound.m_fSpeed = speed;
            sound.m_fSoundDistance = 2.0f;
            m_pFlatTyreSound = AESoundManager.RequestNewSound(&sound);
        }
    } else if (m_nFlatTyreSoundType != -1 && m_pFlatTyreSound) {
        // Same sound type already initialised, just set speed and volume
        m_pFlatTyreSound->m_fSpeed = speed;
        m_pFlatTyreSound->m_fVolume = volume;
    }
}

// 0x4F87D0
void CAEVehicleAudioEntity::PlayReverseSound(int16 newReverseGearSoundType, float speed, float volumeDelta) {
    const float volume = m_fGeneralVehicleSoundVolume + volumeDelta;
    if (m_nReverseGearSoundType != newReverseGearSoundType) {
        if (m_pReverseGearSound) {
            m_pReverseGearSound->SetIndividualEnvironment(4, false);
            m_pReverseGearSound->StopSound();
            m_pReverseGearSound = nullptr;
        }

        // Create new sound
        m_nReverseGearSoundType = newReverseGearSoundType;
        if (newReverseGearSoundType != -1) {
            const auto& posn = m_pEntity->GetPosition();
            CAESound sound;
            sound.Initialise(19, newReverseGearSoundType, this, posn, volume, 1.0f, 1.0f, 1.0f, false, SOUND_REQUEST_UPDATES, 0.0f, 0);
            sound.m_fSpeed = speed;
            m_pReverseGearSound = AESoundManager.RequestNewSound(&sound);
        }
    } else if (m_nReverseGearSoundType != -1 && m_pReverseGearSound) {
        // Same sound type already initialised, just set speed and volume
        m_pReverseGearSound->m_fSpeed = speed;
        m_pReverseGearSound->m_fVolume = volume;
    }
}

// 0x4F9E90
void CAEVehicleAudioEntity::UpdateBoatSound(int16 engineState, int16 bankSlotId, int16 sfxId, float speed, float volumeDelta) {
    if (m_settings.m_nVehicleSoundType != VEHICLE_SOUND_NON_VEH)
        if (engineState != 6 && m_nEngineBankSlotId == -1)
            return;

    const float fVolume = m_fGeneralVehicleSoundVolume + volumeDelta;
    if (UpdateGenericEngineSound(engineState, fVolume, speed))
        return;

    const auto DoPlaySound = [&](float fSoundDistance) {
        PlayGenericEngineSound(engineState, bankSlotId, sfxId, fVolume, speed, fSoundDistance);
    };

    switch (engineState) {
    case 2: {
        if (AEAudioHardware.IsSoundBankLoaded(m_nEngineDecelerateSoundBankId, m_nEngineBankSlotId))
            DoPlaySound(3.5f);
        break;
    }
    case 3: {
        if (AEAudioHardware.IsSoundBankLoaded(138u, 19))
            DoPlaySound(5.0f);
        break;
    }
    case 6: {
        if (AEAudioHardware.IsSoundBankLoaded(39u, 2))
            DoPlaySound(5.0f);
        break;
    }
    }
}

// 0x4FA1C0
void CAEVehicleAudioEntity::UpdateTrainSound(int16 engineState, int16 bankSlotId, int16 sfxId, float speed, float volumeDelta) {
    if (m_nEngineBankSlotId == -1)
        return;

    const float fVolume = m_fGeneralVehicleSoundVolume + volumeDelta;

    if (UpdateGenericEngineSound(engineState, fVolume, speed))
        return;

    const auto DoPlaySound = [&](float fSoundDistance) {
        PlayGenericEngineSound(engineState, bankSlotId, sfxId, fVolume, speed, fSoundDistance);
    };

    switch (engineState) {
    case 1: {
        if (AEAudioHardware.IsSoundBankLoaded(m_nEngineDecelerateSoundBankId, m_nEngineBankSlotId))
            DoPlaySound(m_nEngineDecelerateSoundBankId == 133 ? 4.0f : 4.5f);
        break;
    }
    case 2: {
        if (AEAudioHardware.IsSoundBankLoaded(m_nEngineDecelerateSoundBankId, m_nEngineBankSlotId))
            DoPlaySound(m_nEngineDecelerateSoundBankId == 133 ? 5.0f : 4.5f);
        break;
    }
    case 3: {
        if (AEAudioHardware.IsSoundBankLoaded(39u, 2))
            DoPlaySound(4.5f);
        break;
    }
    }
}

// 0x4F93C0
void CAEVehicleAudioEntity::PlayAircraftSound(int16 engineState, int16 bankSlotId, int16 sfxId, float speed, float volumeDelta) {
    const float fVolume = m_fGeneralVehicleSoundVolume + volumeDelta;
    if (CAESound* pThisEngineSound = m_aEngineSounds[engineState].m_pSound) {
        pThisEngineSound->m_fVolume = fVolume;
        pThisEngineSound->m_fSpeed = speed;
        return; // Sound exists, update params, and early out
    }

    const auto DoPlaySound = [&](float fSoundDistance, float fTimeScale = 1.0f) {
        PlayGenericEngineSound(engineState, bankSlotId, sfxId, fVolume, speed, fSoundDistance, fTimeScale);
    };

    switch (engineState) {
    case 1:
        DoPlaySound(6.0f);
        break;
    case 2:
    case 4:
        DoPlaySound(4.0f);
        break;
    case 3:
        DoPlaySound(1.0f, 0.4f);
        break;
    case 5:
        DoPlaySound(4.5f);
        break;
    case 7:
        DoPlaySound(5.0f);
        break;
    }
}

// 0x4F9710
void CAEVehicleAudioEntity::PlayBicycleSound(int16 engineState, int16 bankSlotId, int16 sfxId, float speed, float fVolume) {
    if (m_nEngineBankSlotId == -1)
        return;

    if (engineState == 3) {
        if (m_aEngineSounds[3].m_pSound)
            return;
        if (!AEAudioHardware.IsSoundBankLoaded(39, 2))
            return;

        static constexpr struct { // 0x8CC1D8
            int16 sfxId, playPos;
        } RandomArray[] = {
            { 5, 38 },
            { 7, 25 },
            { 8, 25 },
            { 9, 50 }
        };
        const auto random = CGeneral::GetRandomNumberInRange(0, std::size(RandomArray));
        const auto& toPlay = RandomArray[random];

        PlayGenericEngineSound(
            engineState,
            2,
            toPlay.sfxId,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
            eSoundEnvironment(SOUND_REQUEST_UPDATES | SOUND_START_PERCENTAGE),
            toPlay.playPos
        );
    } else {
        if (UpdateGenericEngineSound(engineState, fVolume, speed))
            return;

        switch (engineState) {
        case 1: {
            if (AEAudioHardware.IsSoundBankLoaded(m_nEngineDecelerateSoundBankId, m_nEngineBankSlotId))
                PlayGenericEngineSound(engineState, bankSlotId, sfxId, fVolume, speed, 2.5f);
            break;
        }
        case 2: {
            if (AEAudioHardware.IsSoundBankLoaded(m_nEngineAccelerateSoundBankId, 40)) {
                PlayGenericEngineSound(engineState, bankSlotId, sfxId, fVolume, speed, 1.5f);
            }
            break;
        }
        }
    }
}

// 0x4F99D0
void CAEVehicleAudioEntity::PlayHornOrSiren(bool bPlayHornTone, char bPlaySirenOrAlarm, bool bPlayHorn, cVehicleParams& params) {
    const auto nHornToneSoundInBank = m_settings.m_nHornToneSoundInBank;
    const auto DoTryStopHornSound = [&] {
        if (m_pHornTonSound) {
            m_pHornTonSound->StopSoundAndForget();
            m_pHornTonSound = nullptr;
        }
    };
    if (!m_bPlayHornTone && bPlayHornTone) {
        const bool bBanksLoaded = AEAudioHardware.IsSoundBankLoaded(74u, 17) && AEAudioHardware.IsSoundBankLoaded(138u, 19);
        const auto DoPlayHornSound = [&](float fSpeed) {
            const auto& posn = m_pEntity->GetPosition();
            m_tempSound.Initialise(17, nHornToneSoundInBank, this, posn, m_fHornVolume, 2.5f, fSpeed, 0.17f, false, SOUND_REQUEST_UPDATES, 0.0f, 0);
            m_pHornTonSound = AESoundManager.RequestNewSound(&m_tempSound);
            return true;
        };

        if (!nHornToneSoundInBank) {
            DoTryStopHornSound();
            m_fHornVolume = (float)m_pAudioEventVolumes[AE_BIKE_BELL];
            if (!bBanksLoaded)
                return;
            DoPlayHornSound(1.0f);
        } else {
            if (m_pHornTonSound)
                return;

            if (nHornToneSoundInBank <= 0 || nHornToneSoundInBank > 9)
                return;

            m_fHornVolume = m_settings.m_fHornVolumeDelta + (float)m_pAudioEventVolumes[AE_CAR_HORN];
            if (!bBanksLoaded)
                return;

            DoPlayHornSound(m_settings.m_fHornHigh);
        }
    } else {
        if (nHornToneSoundInBank == 0) {
            m_fHornVolume = std::max(m_fHornVolume - 1.5f, -100.0f);
            if (m_fHornVolume <= -100.0f)
                DoTryStopHornSound();
            else if (m_pHornTonSound)
                m_pHornTonSound->m_fVolume = m_fHornVolume; // Just modify speed
        }
    }

    if (bPlaySirenOrAlarm && !bPlayHorn) {
        if (!m_bSirenOrAlarmPlaying || m_bHornPlaying) {
            // there was no siren last frame OR
            // horn was playing and siren should've been playing, but couldn't have been
            // because the horn was playing (and not it isn't)

            if (m_pSirenSound || !AEAudioHardware.IsSoundBankLoaded(74u, 17))
                return;

            const bool bIsWhoopieModel = params.m_pVehicle->m_nModelIndex == MODEL_MRWHOOP;
            if (bIsWhoopieModel)
                if (!AEAudioHardware.IsSoundBankLoaded(79u, 40))
                    return;
            m_pSirenSound = PlaySound(bIsWhoopieModel ? 40 : 17, bIsWhoopieModel ? 3 : 10, (float)m_pAudioEventVolumes[AE_SIREN], 1.0f, 3.0f, 0.25f);
        }
    } else if (m_bSirenOrAlarmPlaying && !m_bHornPlaying && m_pSirenSound) {
        m_pSirenSound->StopSoundAndForget();
        m_pSirenSound = nullptr;
    }

    if (bPlayHorn) {
        if (!m_bHornPlaying && !m_pPoliceSirenSound && AEAudioHardware.IsSoundBankLoaded(74u, 17)) {
            m_pPoliceSirenSound = PlaySound(17, 11, (float)m_pAudioEventVolumes[AE_SIREN], 1.0f, 3.0f, 0.25f);
        }
    } else if (m_bHornPlaying) {
        if (m_pPoliceSirenSound) {
            m_pPoliceSirenSound->StopSoundAndForget();
            m_pPoliceSirenSound = nullptr;
        }
    }
}

// 0x4FCF40
void CAEVehicleAudioEntity::JustGotOutOfVehicleAsDriver() {
    // return plugin::CallMethod<0x4FCF40, CAEVehicleAudioEntity*>(this);
    m_bVehicleRadioPaused = false;
    switch (m_settings.m_nVehicleSoundType) {
    case VEHICLE_SOUND_CAR:
    case VEHICLE_SOUND_MOTORCYCLE: {
        m_fGeneralVehicleSoundVolume = m_pAudioEventVolumes[AE_GENERAL_VEHICLE_SOUND] - 1.5f;
        field_23C = 1.0f;
        field_240 = 1.0f;

        if (m_nEngineState == 6) {
            for (auto i = 0; i < std::size(m_aEngineSounds); i++) {
                if (i != 2)
                    CancelVehicleEngineSound(i);
            }
            m_nEngineState = 1;
        } else {
            for (auto i = 0; i < std::size(m_aEngineSounds); i++) {
                CancelVehicleEngineSound(i);
            }
            if (m_nEngineState != 0)
                m_nEngineState = 10;
        }
        PlayReverseSound(-1, 1.0f, -100.0f);
        m_nGearRelatedStuff = 0;
        s_pPlayerDriver = nullptr;
        break;
    }
    case VEHICLE_SOUND_TRAIN: {
        PlayTrainBrakeSound(-1, 1.0f, -100.0f);
        s_pPlayerDriver = nullptr;
        break;
    }
    case VEHICLE_SOUND_TRAILER: {
        m_fGeneralVehicleSoundVolume = m_pAudioEventVolumes[AE_GENERAL_VEHICLE_SOUND] - 1.5f;
        s_pPlayerDriver = nullptr;
        break;
    }
    case VEHICLE_SOUND_PLANE:
    case VEHICLE_SOUND_HELI:
    case VEHICLE_SOUND_NON_VEH: {
        for (auto i = 0u; i < std::size(m_aEngineSounds); i++) {
            CancelVehicleEngineSound(i);
        }
        m_fPlaneSoundSpeed = -1.0f;
        m_fPlaneSoundVolume_Probably = -100.0f;
        break;
    }
    case VEHICLE_SOUND_BICYCLE: {
        s_pPlayerDriver = nullptr;
        break;
    }
    }
}

// 0x4FD0B0
void CAEVehicleAudioEntity::JustWreckedVehicle() {
    if (m_bPlayerDriver) {
        switch (m_settings.m_nRadioType) {
        case RADIO_CIVILIAN:
        case RADIO_UNKNOWN:
        case RADIO_EMERGENCY: {
            AudioEngine.StopRadio(&m_settings, false); // inlined TurnOffRadioForVehicle
            break;
        }
        }
        s_pVehicleAudioSettingsForRadio = nullptr;
        s_pPlayerAttachedForRadio = nullptr;
    }

    switch (m_settings.m_nVehicleSoundType) {
    case VEHICLE_SOUND_CAR:
    case VEHICLE_SOUND_MOTORCYCLE:
    case VEHICLE_SOUND_BICYCLE:
    case VEHICLE_SOUND_BOAT:
    case VEHICLE_SOUND_HELI:
    case VEHICLE_SOUND_PLANE:
    case VEHICLE_SOUND_NON_VEH:
    case VEHICLE_SOUND_TRAIN:
    case VEHICLE_SOUND_TRAILER: {
        for (auto i = 0; i < std::size(m_aEngineSounds); i++) {
            CancelVehicleEngineSound(i);
        }
        break;
    }
    }

    PlaySkidSound(-1, 1.0f, -100.0f);

    // todo: do better
    // Originally copied and pasted code, but this is way more readable
    struct {
        CAESound** ppSound;
        int16*     pnSoundType;
    } SoundsToStop[] = {
        { &m_pSkidSoundMaybe,   &m_nSkidSoundType        },
        { &m_pRoadNoiseSound,   &m_nRoadNoiseSoundType   },
        { &m_pFlatTyreSound,    &m_nFlatTyreSoundType    },
        { &m_pReverseGearSound, &m_nReverseGearSoundType },
        { &m_pHornTonSound,     nullptr                  },
        { &m_pSirenSound,       nullptr                  },
        { &m_pPoliceSirenSound, nullptr                  }
    };

    // Stop sounds, and reset member variables (that's why we use float pointers)
    for (const auto& sounds : SoundsToStop) {
        if (CAESound*& sound = *sounds.ppSound) {
            sound->SetIndividualEnvironment(SOUND_REQUEST_UPDATES, false);
            sound->StopSound();
            sound = nullptr;
            if (*sounds.pnSoundType) {
                *sounds.pnSoundType = -1;
            }
        }
    }
}

// 0x4FAD40
void CAEVehicleAudioEntity::UpdateGenericVehicleSound(int16 engineStateSoundIndex, int16 bankSlotId, int16 gameBank, int16 sfxId, float speed, float volume, float distance) {
    const float finalVolume = m_fGeneralVehicleSoundVolume + volume;
    if (CAESound* sound = m_aEngineSounds[engineStateSoundIndex].m_pSound) {
        sound->m_fSpeed = speed;
        sound->m_fVolume = finalVolume;
    } else if (AEAudioHardware.IsSoundBankLoaded(gameBank, bankSlotId)) {
        m_aEngineSounds[engineStateSoundIndex].m_pSound = PlaySound(bankSlotId, sfxId, finalVolume, speed);
    }
}

// 0x4F8940
void CAEVehicleAudioEntity::ProcessVehicleFlatTyre(cVehicleParams& params) {
    plugin::CallMethod<0x4F8940, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4F8B00
void CAEVehicleAudioEntity::ProcessVehicleRoadNoise(cVehicleParams& params) {
    // return plugin::CallMethod<0x4F8B00, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);

    CVehicle* vehicle = params.m_pVehicle;

    const auto CancelRoadNoise = [=] { PlayRoadNoiseSound(-1, 0.0f, 0.0f); };

    // Check if any wheels touch the ground. (Perhaps params.m_nWheelsOnGround could be used?)
    /* Izzotop: bad
    switch (params.m_vehicleType) {
    case VEHICLE_AUTOMOBILE: {
        if (!vehicle->AsAutomobile()->m_nNumContactWheels) {
            CancelRoadNoise();
            return;
        }
    }
    case VEHICLE_BIKE: {
        if (!vehicle->AsBike()->m_nNumContactWheels) {
            CancelRoadNoise();
            return;
        }
    }
    }
    */

    switch (vehicle->m_nModelIndex) {
    case MODEL_ARTICT1:
    case MODEL_ARTICT2:
    case MODEL_PETROTR:
    case MODEL_ARTICT3:
        break; // No transmission check for these models
    default: {
        if (!params.m_pTransmission) {
            CancelRoadNoise();
            return;
        }
    }
    }

    const float fAbsVelocity = fabs(params.m_fVelocity);
    if (fAbsVelocity <= 0.0f) {
        CancelRoadNoise();
        return;
    }

    float fSpeed = 1.0f;
    {
        const CVector camPos = TheCamera.GetPosition();
        const CVector vehAudioPos = m_pEntity->GetPosition();

        const float someDistance = 72.0f; // 0x8CBD10
        const float distanceProgress = (vehAudioPos - camPos).Magnitude() / someDistance;

        fSpeed = 0.75f + std::max(1.0f, distanceProgress) / 2.0f;
    }

    int16 nRoadNoiseSound = -1;
    float fVolumeBase = -12.0f;
    if (IsSurfaceAudioGrass(vehicle->m_nContactSurface)) {
        fSpeed *= 1.3f;
        fVolumeBase += 0.0f; // 0xB6B9E4
        nRoadNoiseSound = 21;
    } else if (IsSurfaceAudioEitherGravelWaterSand(vehicle->m_nContactSurface)) {
        fVolumeBase += 4.5f;
        nRoadNoiseSound = 22;
    }

    const float logarithmicVolume = std::min(1.0f, 2 * fAbsVelocity);
    float fVolume = -100.0f;
    if (logarithmicVolume > 0.0008f) {
        fVolume = fVolumeBase + CAEAudioUtility::AudioLog10(logarithmicVolume) * 20.0f;
    }

    // Playing sound with -100.0f volume, in case logarithmicVolume <= 0.0008f, doesn't make much sense..
    PlayRoadNoiseSound(nRoadNoiseSound, fSpeed, fVolume);
}

// 0x4F8DF0
void CAEVehicleAudioEntity::ProcessReverseGear(cVehicleParams& params) {
    // plugin::CallMethod<0x4F8DF0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);

    static constexpr float BASE_SPEED  = +0.75f; // 0x8CBD24
    static constexpr float SPEED_MULT  = +0.20f; // 0x8CBD28
    static constexpr float BASE_VOLUME = -6.00f; // 0x8CBD28

    const auto vehicle = params.m_pVehicle->AsAutomobile();
    if (vehicle->vehicleFlags.bEngineOn && (vehicle->m_fGasPedal < 0.0f || !vehicle->m_nCurrentGear)) { // Check if we are reversing

        float fReverseGearVelocityProgress = 0.0f;
        if (vehicle->m_nWheelsOnGround) {
            fReverseGearVelocityProgress = params.m_fVelocity / params.m_pTransmission->m_maxReverseGearVelocity;
        } else {
            if (vehicle->m_wheelsOnGrounPrev)
                vehicle->m_fSomeGasPedalStuff *= 0.4f;
            fReverseGearVelocityProgress = vehicle->m_fSomeGasPedalStuff;
        }
        fReverseGearVelocityProgress = fabs(fReverseGearVelocityProgress);

        PlayReverseSound(
            vehicle->m_fGasPedal >= 0.0f ? 20 : 19,                 // soundType
            BASE_SPEED + fReverseGearVelocityProgress * SPEED_MULT, // speed
            fReverseGearVelocityProgress > 0.0f                     // volume
                ? BASE_VOLUME + CAEAudioUtility::AudioLog10(fReverseGearVelocityProgress) * 20.0f
                : -100.0f
        );
    } else { // Cancel sound otherwise
        PlayReverseSound(-1, 0.0f, 0.0f);
    }
}

// 0x4F8F10
void CAEVehicleAudioEntity::ProcessVehicleSkidding(cVehicleParams& params) {
    // plugin::CallMethod<0x4F8F10, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);

    tWheelState* wheelStates = nullptr;
    float* aWheelTimers = nullptr;

    bool bAreRearWheelsNotSkidding = false;
    float fUnk = 0.0f;
    auto nWheels = 0;

    switch (params.m_vehicleType) {
    case VEHICLE_TYPE_AUTOMOBILE: {
        nWheels = 4;

        auto vehicle = params.m_pVehicle->AsAutomobile();
        fUnk = vehicle->m_fSomeGasPedalStuff;

        bAreRearWheelsNotSkidding = vehicle->m_aWheelState[CAR_WHEEL_REAR_LEFT] != WHEEL_STATE_SKIDDING && vehicle->m_aWheelState[CAR_WHEEL_REAR_RIGHT] != WHEEL_STATE_SKIDDING;
        // todo: aWheelTimers = vehicle->m_anWheelTimer;
        // todo: wheelStates = vehicle->m_anWheelState;
        break;
    }
    case VEHICLE_TYPE_BIKE: {
        nWheels = 2;

        auto* bike = params.m_pVehicle->AsBike();
        fUnk = bike->m_fGasPedalAudio;
        bAreRearWheelsNotSkidding = bike->m_anWheelState[1] != WHEEL_STATE_SKIDDING;
        wheelStates = bike->m_anWheelState;
        // todo: aWheelTimers = bike->m_wheelCollisionState;
        break;
    }
    default:
        return;
    }

    // Calculate skid values sum of all wheels
    float fTotalSkidValue = 0.0f;
    for (auto i = 0; i < nWheels; i++) {
        const bool bIsFrontWheel = i == CAR_WHEEL_FRONT_LEFT || i == CAR_WHEEL_FRONT_RIGHT;
        const tWheelState thisWheelState = wheelStates[i];

        if (thisWheelState == WHEEL_STATE_NORMAL)
            continue;
        if (aWheelTimers[i] == 0.0f)
            continue;
        if (bAreRearWheelsNotSkidding)
            if (bIsFrontWheel)
                if (thisWheelState == WHEEL_STATE_SKIDDING)
                    continue;

        const auto dt = params.m_pTransmission->m_nDriveType;
        if (dt == '4' || dt == 'F' && bIsFrontWheel || dt == 'R' && !bIsFrontWheel) {
            fTotalSkidValue += GetVehicleDriveWheelSkidValue(params.m_pVehicle, thisWheelState, fUnk, *params.m_pTransmission, params.m_fVelocity);
        } else {
            fTotalSkidValue += GetVehicleNonDriveWheelSkidValue(params.m_pVehicle, thisWheelState, *params.m_pTransmission, params.m_fVelocity);
        }
    }

    const auto StopSkidSound = [&] { PlaySkidSound(-1, 0.0f, 0.0f); };
    if (fTotalSkidValue <= 0.0) {
        StopSkidSound();
        return;
    }

    int16 soundId = -1;
    float fBaseVolume = 0.0f, fSpeed = 1.0f;

    if (m_settings.m_nVehicleSoundType == VEHICLE_SOUND_BICYCLE) {
        soundId = 0;
        fBaseVolume = -12.0f;
        fSpeed = 0.9f + fTotalSkidValue * 0.25f;
    } else {
        if (IsSurfaceAudioGrass(params.m_pVehicle->m_nContactSurface)) {
            soundId = 6;
            fBaseVolume = -12.0f;
            fSpeed = 0.2f * fTotalSkidValue + 0.9f;
        } else if (IsSurfaceAudioEitherGravelWaterSand(params.m_pVehicle->m_nContactSurface)) {
            soundId = 8;
            fBaseVolume = -9.0;
            fSpeed = 0.2f * fTotalSkidValue + 0.9f;
        } else {
            soundId = 24;
            fSpeed = 0.125f * fTotalSkidValue + 0.8f;

            if (m_settings.IsMotorcycle()) {
                fSpeed *= 1.2f;
            }
        }

        switch (m_settings.m_nVehicleSoundType) {
        case VEHICLE_SOUND_PLANE:
        case VEHICLE_SOUND_HELI: {
            fBaseVolume += 12.0f;
            break;
        }
        }
    }

    const float fAvgSkidValPerWheel = fTotalSkidValue / (float)nWheels;
    if (fAvgSkidValPerWheel > 0.00001f) {
        const float fVolume = 0.0f + fBaseVolume + CAEAudioUtility::AudioLog10(fAvgSkidValPerWheel) * 20.0f;
        if (fVolume >= -100.0f) {
            PlaySkidSound(soundId, fSpeed, fVolume);
        } else
            StopSkidSound();
    } else
        StopSkidSound();
}

// 0x4F92C0
void CAEVehicleAudioEntity::ProcessRainOnVehicle(cVehicleParams& params) {
    // plugin::CallMethod<0x4F92C0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);

    if (!AEAudioHardware.IsSoundBankLoaded(BANK_RAIN_SOUNDS, 6))
        return;

    if (CAEWeatherAudioEntity::m_sfRainVolume <= -100.0f)
        return;

    if (++m_nRainDropCounter < 3)
        return;

    m_nRainDropCounter = 0;

    const auto sfxId = CAEAudioUtility::GetRandomNumberInRange(12, 15);
    const auto volume = 0.0f + CAEWeatherAudioEntity::m_sfRainVolume;
    m_tempSound.Initialise(6, sfxId, this, m_pEntity->GetPosition(), volume, 0.1f, 1.0f, 1.0f, 0, SOUND_DEFAULT, 0.0f, 0);
    m_tempSound.m_nEvent = AE_RAIN_COLLISION;
    AESoundManager.RequestNewSound(&m_tempSound);
}

// 0x4FA0C0
void CAEVehicleAudioEntity::ProcessBoatMovingOverWater(cVehicleParams& params) {
    // plugin::CallMethod<0x4FA0C0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
    auto* boat = params.m_pVehicle->AsBoat();

    // Originally there was a multiply by 1.33, that's the recp. of 0.75, which makes sense
    // because the abs. velocity is clamped to 0,75
    const float fVelocityProgress = std::min(0.75f, fabs(params.m_fVelocity)) / 0.75f;

    float fVolume = -100.0f;
    if (boat->m_nBoatFlags.bOnWater && fVelocityProgress >= 0.00001f) {
        fVolume = CAEAudioUtility::AudioLog10(fVelocityProgress) * 20.0f;
        fVolume += (m_settings.m_nVehicleSoundType == VEHICLE_SOUND_NON_VEH) ? 12.0f : 3.0f;
    }

    float fSpeed = 0.8f + fVelocityProgress * 0.2f;
    if (CWeather::UnderWaterness >= 0.5f) {
        fSpeed *= 0.185f;
        fVolume += 6.0f;
    }

    UpdateBoatSound(6, 2, 3, fSpeed, fVolume);
}

// 0x4FA3F0
void CAEVehicleAudioEntity::ProcessTrainTrackSound(cVehicleParams& params) {
    plugin::CallMethod<0x4FA3F0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// Android
void CAEVehicleAudioEntity::ProcessPlayerTrainEngine(cVehicleParams& params) {
    // NOP
}

// 0x4FA7C0
void CAEVehicleAudioEntity::ProcessDummyRCPlane(cVehicleParams& params) {
    plugin::CallMethod<0x4FA7C0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// Android
void CAEVehicleAudioEntity::ProcessPlayerRCPlane(cVehicleParams& params) {
    // NOP
}

// 0x4FAA80
void CAEVehicleAudioEntity::ProcessDummyRCHeli(cVehicleParams& params) {
    plugin::CallMethod<0x4FAA80, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// Android
void CAEVehicleAudioEntity::ProcessPlayerRCHeli(cVehicleParams& params) {
    // NOP
}

// Android
void CAEVehicleAudioEntity::ProcessPlayerRCCar(cVehicleParams& params) {
    // NOP
}

// Android
void CAEVehicleAudioEntity::ProcessPlayerHovercraft(cVehicleParams& params) {
    // NOP
}

// Android
void CAEVehicleAudioEntity::ProcessPlayerGolfCart(cVehicleParams& params) {
    // NOP
}

// 0x4FAE20
void CAEVehicleAudioEntity::ProcessEngineDamage(cVehicleParams& params) {
    plugin::CallMethod<0x4FAE20, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FB070
void CAEVehicleAudioEntity::ProcessNitro(cVehicleParams& params) {
    plugin::CallMethod<0x4FB070, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FB260
void CAEVehicleAudioEntity::ProcessMovingParts(cVehicleParams& params) {
    // plugin::CallMethod<0x4FB260, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
    switch (params.m_pVehicle->m_nModelIndex) {
    case MODEL_PACKER:
    case MODEL_DOZER:
    case MODEL_DUMPER:

        // Note: Rockstar originally may have wanted it to have sound,
        // but they've only left it in the first `if` check, it has no `case` in the `switch` below.
        // case MODEL_CEMENT:

    case MODEL_ANDROM:
    case MODEL_FORKLIFT:
        break;
    default:
        return;
    }

    auto vehicle = params.m_pVehicle->AsAutomobile();

    float fComponentMoveProgress = (float)(vehicle->m_wMiscComponentAngle - vehicle->m_wMiscComponentAnglePrev) / 30.0f;
    fComponentMoveProgress = clamp<float>(fabs(fComponentMoveProgress), 0.0f, 1.0f);
    if (fComponentMoveProgress <= field_238)
        fComponentMoveProgress = std::max(field_238 - 0.2f, fComponentMoveProgress);
    else
        fComponentMoveProgress = std::min(field_238 + 0.2f, fComponentMoveProgress);
    field_238 = fComponentMoveProgress;

    float fSpeed = 1.0f, fVolume = 0.0f;
    int16 bankSlot = -1, bank = -1, sfxId = -1;

    switch (vehicle->m_nModelIndex) {
    case MODEL_DUMPER: {
        bankSlot = 19;
        bank = 138;
        sfxId = 15;
        if (fComponentMoveProgress <= 0.0f) {
            fSpeed = 0.9f;
            fVolume = 14.0f;
        } else {
            fSpeed = 1.1f;
            fVolume = 20.f;
        }
        break;
    }
    case MODEL_PACKER: {
        bankSlot = 19;
        bank = 138;
        sfxId = 15;
        if (fComponentMoveProgress <= 0.0f) {
            fSpeed = 0.8f;
            fVolume = 3.0f;
        } else {
            fSpeed = 1.0f;
            fVolume = 9.0f;
        }
        break;
    }
    case MODEL_DOZER: {
        bankSlot = 19;
        bank = 138;
        sfxId = 15;
        if (fComponentMoveProgress <= 0.0f) {
            fSpeed = 0.9f;
            fVolume = 2.0f;
        } else {
            fSpeed = 1.1f;
            fVolume = 6.0f;
        }
        break;
    }
    case MODEL_FORKLIFT: {
        bankSlot = m_nEngineBankSlotId;
        bank = 57;
        sfxId = 2;
        if (fComponentMoveProgress <= 0.0f) {
            fSpeed = 0.8f;
            fVolume = -18.0f;
        } else {
            fSpeed = 1.0f;
            fVolume = -6.0f;
        }
        break;
    }
    case MODEL_ANDROM: {
        bankSlot = 19;
        bank = 138;
        sfxId = 15;
        if (fComponentMoveProgress <= 0.0f) {
            fSpeed = 0.8f;
            fVolume = 21.0f;
        } else {
            fSpeed = 1.0f;
            fVolume = 24.0f;
        }
        break;
    }
    }

    fVolume += CAEAudioUtility::AudioLog10(field_238) * 20.0f;
    if (fVolume <= -100.0f) {
        if (auto& sound = m_aEngineSounds[11].m_pSound) {
            sound->SetIndividualEnvironment(4, 0);
            sound->StopSound();
            sound = nullptr;
        }
    } else {
        UpdateGenericVehicleSound(11, bankSlot, bank, sfxId, fSpeed, fVolume, 1.5f);
    }
}

// 0x4FBB10
void CAEVehicleAudioEntity::ProcessPlayerVehicleEngine(cVehicleParams& params) {
    plugin::CallMethod<0x4FBB10, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FCA10
void CAEVehicleAudioEntity::ProcessDummyStateTransition(int16 a1, float a2, cVehicleParams& params) {
    plugin::CallMethod<0x4FCA10, CAEVehicleAudioEntity*, int16, float, cVehicleParams&>(this, a1, a2, params);
}

// 0x4FD290
void CAEVehicleAudioEntity::ProcessPlayerProp(cVehicleParams& params) {
    plugin::CallMethod<0x4FD290, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FD8F0
void CAEVehicleAudioEntity::ProcessDummyProp(cVehicleParams& params) {
    plugin::CallMethod<0x4FD8F0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FDFD0
void CAEVehicleAudioEntity::ProcessAIProp(cVehicleParams& params) {
    plugin::CallMethod<0x4FDFD0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FE420
void CAEVehicleAudioEntity::ProcessPlayerHeli(cVehicleParams& params) {
    plugin::CallMethod<0x4FE420, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FE940
void CAEVehicleAudioEntity::ProcessDummyHeli(cVehicleParams& params) {
    plugin::CallMethod<0x4FE940, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FEE20
void CAEVehicleAudioEntity::ProcessAIHeli(cVehicleParams& params) {
    plugin::CallMethod<0x4FEE20, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FF320
void CAEVehicleAudioEntity::ProcessPlayerSeaPlane(cVehicleParams& params) {
    plugin::CallMethod<0x4FF320, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FF7C0
void CAEVehicleAudioEntity::ProcessDummySeaPlane(cVehicleParams& params) {
    plugin::CallMethod<0x4FF7C0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x4FF900
void CAEVehicleAudioEntity::ProcessGenericJet(uint8 a1, cVehicleParams& params, float a3, float a4, float a5, float a6, float a7) {
    plugin::CallMethod<0x4FF900, CAEVehicleAudioEntity*, uint8, cVehicleParams&, float, float, float, float, float>(this, a1, params, a3, a4, a5, a6, a7);
}

// 0x4FFDC0
void CAEVehicleAudioEntity::ProcessDummyBicycle(cVehicleParams& params) {
    plugin::CallMethod<0x4FFDC0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x500040
void CAEVehicleAudioEntity::ProcessPlayerBicycle(cVehicleParams& params) {
    plugin::CallMethod<0x500040, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x5002C0
void CAEVehicleAudioEntity::ProcessVehicleSirenAlarmHorn(cVehicleParams& params) {
    bool bHorn, bSirenOrAlarm;
    GetSirenState(bSirenOrAlarm, bHorn, params);

    if (!bSirenOrAlarm) {
        CVehicle* vehicle = params.m_pVehicle;
        if (!vehicle->m_nAlarmState || vehicle->m_nAlarmState == -1 || vehicle->m_nStatus == STATUS_WRECKED)
            GetHornState(&bHorn, params);
        else {
            const auto time = CTimer::GetTimeInMS();
            if (time > vehicle->m_nHornCounter)
                vehicle->m_nHornCounter = time + 750;
            m_bPlayHornTone = vehicle->m_nHornCounter < time + 750 / 2;
        }
    }

    PlayHornOrSiren(m_bPlayHornTone, bSirenOrAlarm, bHorn, params);
    m_bSirenOrAlarmPlaying = bSirenOrAlarm;
    m_bHornPlaying = bHorn;
}

// 0x5003A0
void CAEVehicleAudioEntity::ProcessBoatEngine(cVehicleParams& params) {
    plugin::CallMethod<0x5003A0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x500710
void CAEVehicleAudioEntity::ProcessDummyTrainEngine(cVehicleParams& params) {
    plugin::CallMethod<0x500710, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x500AB0
void CAEVehicleAudioEntity::ProcessPlayerTrainBrakes(cVehicleParams& params) {
    plugin::CallMethod<0x500AB0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x500CE0
void CAEVehicleAudioEntity::ProcessPlayerCombine(cVehicleParams& params) {
    plugin::CallMethod<0x500CE0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x500DC0
void CAEVehicleAudioEntity::ProcessDummyRCCar(cVehicleParams& params) {
    plugin::CallMethod<0x500DC0, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x500F50
void CAEVehicleAudioEntity::ProcessDummyHovercraft(cVehicleParams& params) {
    plugin::CallMethod<0x500F50, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x501270
void CAEVehicleAudioEntity::ProcessDummyGolfCart(cVehicleParams& params) {
    plugin::CallMethod<0x501270, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x501480
void CAEVehicleAudioEntity::ProcessDummyVehicleEngine(cVehicleParams& params) {
    plugin::CallMethod<0x501480, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x501650
void CAEVehicleAudioEntity::ProcessPlayerJet(cVehicleParams& params) {
    plugin::CallMethod<0x501650, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x501960
void CAEVehicleAudioEntity::ProcessDummyJet(cVehicleParams& params) {
    plugin::CallMethod<0x501960, CAEVehicleAudioEntity*, cVehicleParams&>(this, params);
}

// 0x501C50
void CAEVehicleAudioEntity::ProcessAircraft(cVehicleParams& vehParams) {
    // plugin::CallMethod<0x501C50, CAEVehicleAudioEntity*>(this, params);
    if (m_bSoundsStopped)
        return;

    if (!AEAudioHardware.IsSoundBankLoaded(138u, 19))
        return;

    auto* vehicle = vehParams.m_pVehicle;
    switch (m_settings.m_nVehicleSoundType) {
    case VEHICLE_SOUND_HELI: {
        if (s_HelicoptorsDisabled || m_bDisableHeliEngineSounds)
            JustWreckedVehicle();
        else if (m_bPlayerDriver)
            ProcessPlayerHeli(vehParams);
        else if (vehicle->m_nStatus == STATUS_PHYSICS)
            ProcessAIHeli(vehParams);
        else
            ProcessDummyHeli(vehParams);
        break;
    }
    case VEHICLE_SOUND_PLANE: {
        switch (vehicle->m_nModelIndex) {
        case MODEL_SHAMAL:
        case MODEL_HYDRA:
        case MODEL_AT400:
        case MODEL_ANDROM: { // Originally there was an `isPlane` variable. I just rearranged stuff, to look nicer
            if (m_bPlayerDriver)
                ProcessPlayerJet(vehParams);
            else
                ProcessDummyJet(vehParams);
            break;
        }
        default: {
            if (m_bPlayerDriver)
                ProcessPlayerProp(vehParams);
            else if (vehicle->m_nStatus == STATUS_PHYSICS || vehicle->m_autoPilot.m_vehicleRecordingId >= 0)
                ProcessAIProp(vehParams);
            else
                ProcessDummyProp(vehParams);
        }
        }
        break;
    }
    case VEHICLE_SOUND_NON_VEH: {
        if (m_bPlayerDriver)
            ProcessPlayerSeaPlane(vehParams);
        else
            ProcessDummySeaPlane(vehParams);
        break;
    }
    }
}

// 0x501E10
void CAEVehicleAudioEntity::ProcessVehicle(CPhysical* vehicle) {
    return plugin::CallMethod<0x501E10, CAEVehicleAudioEntity*, CPhysical*>(this, vehicle);
}

// 0x501AB0
void CAEVehicleAudioEntity::ProcessSpecialVehicle(cVehicleParams& vehParams) {
    switch (vehParams.m_pVehicle->m_nModelIndex) {
    case MODEL_ARTICT1:
    case MODEL_ARTICT2:
    case MODEL_PETROTR:
    case MODEL_ARTICT3: {
        ProcessVehicleRoadNoise(vehParams);
        ProcessRainOnVehicle(vehParams);
        break;
    }
    case MODEL_RCBANDIT:
    case MODEL_RCTIGER: {
        ProcessDummyRCCar(vehParams);
    }
    case MODEL_CADDY: {
        ProcessVehicleRoadNoise(vehParams);
        ProcessVehicleSkidding(vehParams);
        ProcessVehicleFlatTyre(vehParams);
        ProcessVehicleSirenAlarmHorn(vehParams);
        ProcessDummyGolfCart(vehParams);
        ProcessRainOnVehicle(vehParams);
        if (vehParams.m_pVehicle->m_nStatus != STATUS_SIMPLE)
            ProcessEngineDamage(vehParams);
        break;
    }
    case MODEL_RCBARON: {
        ProcessDummyRCPlane(vehParams);
        break;
    }
    case MODEL_RCRAIDER:
    case MODEL_RCGOBLIN: {
        ProcessDummyRCHeli(vehParams);
        break;
    }
    case MODEL_VORTEX: {
        ProcessDummyHovercraft(vehParams);
        ProcessRainOnVehicle(vehParams);
        ProcessVehicleSirenAlarmHorn(vehParams);
        break;
    }
    }
}

bool CAEVehicleAudioEntity::UpdateGenericEngineSound(int16 index, float fVolume, float fSpeed) {
    if (CAESound* sound = m_aEngineSounds[index].m_pSound) {
        sound->m_fSpeed = fSpeed;
        sound->m_fVolume = fVolume;
        return true;
    }
    return false;
}

bool CAEVehicleAudioEntity::PlayGenericEngineSound(int16 index, int16 bankSlotId, int16 sfxId, float fVolume, float fSpeed, float fSoundDistance, float fTimeScale, eSoundEnvironment individualEnvironment, int16 playPos) {
    if (m_aEngineSounds[index].m_pSound) {
        // Early out if sound already being played. For safety.
        return false;
    }

    m_aEngineSounds[index].m_pSound = PlaySound(bankSlotId, sfxId, fVolume, fSpeed, fSoundDistance, fTimeScale, individualEnvironment, playPos);
    return true;
}

CAESound* CAEVehicleAudioEntity::PlaySound(int16 bankSlotId, int16 sfxId, float fVolume, float fSpeed, float fSoundDistance, float fTimeScale, eSoundEnvironment individualEnvironment, int16 playPos) {
    m_tempSound.Initialise(bankSlotId, sfxId, this, m_pEntity->GetPosition(), fVolume, fSoundDistance, fSpeed, fTimeScale, false, individualEnvironment, 0.0, playPos);
    return AESoundManager.RequestNewSound(&m_tempSound);
}
