#include "StdInc.h"

#include "CAEAudioHardware.h"
#include "CAEAudioUtility.h"
#include "CAESoundManager.h"

CPed*&                  CAEVehicleAudioEntity::s_pPlayerAttachedForRadio = *(CPed**)0xB6B98C;
CPed*&                  CAEVehicleAudioEntity::s_pPlayerDriver = *(CPed**)0xB6B990;
bool&                   CAEVehicleAudioEntity::s_HelicoptorsDisabled = *(bool*)0xB6B994;
int16&                  CAEVehicleAudioEntity::s_NextDummyEngineSlot = *(int16*)0xB6B998;
tVehicleAudioSettings*& CAEVehicleAudioEntity::s_pVehicleAudioSettingsForRadio = *reinterpret_cast<tVehicleAudioSettings**>(0xB6B99C);
tEngineDummySlot (&CAEVehicleAudioEntity::s_DummyEngineSlots)[NUM_DUMMY_ENGINE_SLOTS] = *reinterpret_cast<tEngineDummySlot (*)[NUM_DUMMY_ENGINE_SLOTS]>(0xB6B9A0);

tVehicleAudioSettings const (&gVehicleAudioSettings)[NUM_VEH_AUDIO_SETTINGS] = *reinterpret_cast<tVehicleAudioSettings const (*)[232]>(0x860AF0);

void CAEVehicleAudioEntity::InjectHooks() {
    // VIRTUAL
    ReversibleHooks::Install("CAEVehicleAudioEntity", "UpdateParameters", 0x4FB6C0, &CAEVehicleAudioEntity::UpdateParameters_Reversed);

    // CLASS
    ReversibleHooks::Install("CAEVehicleAudioEntity", "Initialise", 0x4F7670, &CAEVehicleAudioEntity::Initialise);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "Terminate", 0x4FB8C0, &CAEVehicleAudioEntity::Terminate);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "GetAircraftNearPosition", 0x4F96A0, &CAEVehicleAudioEntity::GetAircraftNearPosition);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "GetFlyingMetalVolume", 0x4F6150, &CAEVehicleAudioEntity::GetFlyingMetalVolume);

    // STATIC
    ReversibleHooks::Install("CAEVehicleAudioEntity", "GetVehicleAudioSettings", 0x4F5C10, &CAEVehicleAudioEntity::GetVehicleAudioSettings);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "RequestBankSlot", 0x4F4D10, &CAEVehicleAudioEntity::RequestBankSlot);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "DemandBankSlot", 0x4F4E60, &CAEVehicleAudioEntity::DemandBankSlot);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "DoesBankSlotContainThisBank", 0x4F4E30, &CAEVehicleAudioEntity::DoesBankSlotContainThisBank);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "StoppedUsingBankSlot", 0x4F4DF0, &CAEVehicleAudioEntity::StoppedUsingBankSlot);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "EnableHelicoptors", 0x4F4EF0, &CAEVehicleAudioEntity::EnableHelicoptors);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "DisableHelicoptors", 0x4F4EE0, &CAEVehicleAudioEntity::DisableHelicoptors);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "StaticGetPlayerVehicleAudioSettingsForRadio", 0x4F4ED0, &CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "StaticInitialise", 0x5B99F0, &CAEVehicleAudioEntity::StaticInitialise);
}

CAEVehicleAudioEntity::CAEVehicleAudioEntity() : CAEAudioEntity(), m_twinSkidSound() {
    m_bEnabled = false;
    m_pEntity = nullptr;
}

CAEVehicleAudioEntity::~CAEVehicleAudioEntity() {
    if (m_bEnabled)
        CAEVehicleAudioEntity::Terminate();
}

void CAEVehicleAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    CAEVehicleAudioEntity::UpdateParameters_Reversed(sound, curPlayPos);
}

void CAEVehicleAudioEntity::StaticInitialise() {
    for (tEngineDummySlot& dummyEng : s_DummyEngineSlots) {
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

tVehicleAudioSettings* CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio() {
    return s_pVehicleAudioSettingsForRadio;
}

void CAEVehicleAudioEntity::EnableHelicoptors() {
    s_HelicoptorsDisabled = false;
}

void CAEVehicleAudioEntity::DisableHelicoptors() {
    s_HelicoptorsDisabled = true;
}

bool CAEVehicleAudioEntity::DoesBankSlotContainThisBank(int16 bankSlot, int16 bankId) {
    const auto usedSlot = bankSlot - 7;
    if (usedSlot < 0 || usedSlot > NUM_DUMMY_ENGINE_SLOTS)
        return false;

    return s_DummyEngineSlots[usedSlot].m_nBankId == bankId;
}

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
        auto&      dummyEng = s_DummyEngineSlots[iSlot];
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

tVehicleAudioSettings CAEVehicleAudioEntity::GetVehicleAudioSettings(int16 vehId) {
    return gVehicleAudioSettings[vehId - 400];
}

void CAEVehicleAudioEntity::UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos) {
    if (!sound)
        return;

    if (sound->m_nEvent == eAudioEvents::AE_BONNET_FLUBBER_FLUBBER) {
        if (!sound->m_pPhysicalEntity)
            return;

        const auto fBaseVolume = static_cast<float>(m_pAudioEventVolumes[eAudioEvents::AE_BONNET_FLUBBER_FLUBBER]);
        sound->m_fVolume = fBaseVolume + GetFlyingMetalVolume(sound->m_pPhysicalEntity->AsPhysical());
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
            sound->SetPosition(GetAircraftNearPosition());
        else
            sound->SetPosition(m_pEntity->GetPosition());
    }

    if ((m_settings.IsCar() || m_settings.IsMotorcycle()) && sound == m_aEngineSounds[4].m_pSound) {
        m_nSomePrevPlayPos = m_nSomeCurPlayPos;
        m_nSomeCurPlayPos = curPlayPos;
    }
}

void CAEVehicleAudioEntity::AddAudioEvent(eAudioEvents audioEvent, float fVolume) {
    plugin::CallMethod<0x4F6420, CAEVehicleAudioEntity*, int32, float>(this, audioEvent, fVolume);
}

void CAEVehicleAudioEntity::Service() {
    plugin::CallMethod<0x502280, CAEVehicleAudioEntity*>(this);
}

void CAEVehicleAudioEntity::Initialise(CEntity* entity) {
    field_144 = 0;
    m_pEntity = entity;
    m_bPlayerDriver = false;
    m_bPlayerPassenger = false;
    m_bVehicleRadioPaused = false;
    m_bSoundsStopped = false;
    m_nEngineState = 0;
    field_AA = 0;
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
    m_nSomeCurPlayPos = -1;
    m_nSomePrevPlayPos = -1;
    field_154 = 0;
    field_14E = 0;
    field_14C = 0;

    for (auto i = 0; i < 12; ++i) {
        m_aEngineSounds[i].m_nIndex = i;
        m_aEngineSounds[i].m_pSound = nullptr;
    }

    m_fSirenVolume = -100.0f;
    field_230 = -100.0f;
    m_nSkidSoundType = -1;
    m_nRoadNoiseSoundType = -1;
    m_nFlatTyreSoundType = -1;
    m_nReverseGearSoundType = -1;
    field_234 = -1.0f;
    field_22C = -1.0f;
    field_248 = -1.0f;
    m_pSkidSoundMaybe = nullptr;
    m_pRoadNoiseSound = nullptr;
    m_pFlatTyreSound = nullptr;
    m_pReverseGearSound = nullptr;
    m_pHornTonSound = nullptr;
    m_pSirenSound = nullptr;
    m_pPoliceSirenSound = nullptr;
    field_238 = 0.0;
    field_23C = 1.0;
    field_240 = 0;

    m_settings = CAEVehicleAudioEntity::GetVehicleAudioSettings(entity->m_nModelIndex);
    m_bModelWithSiren = entity->AsVehicle()->UsesSiren();
    if (m_settings.m_nRadioType == eRadioType::RADIO_UNKNOWN)
        m_settings.m_nRadioID = eRadioID::RADIO_NONE;

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

void CAEVehicleAudioEntity::Terminate() {
    if (!m_bEnabled)
        return;

    for (auto& engSound : m_aEngineSounds) {
        if (engSound.m_pSound) {
            engSound.m_pSound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
            engSound.m_pSound->StopSound();
            engSound.m_pSound = nullptr;
        }
    }

    PlaySkidSound(-1, 1.0F, -100.0F);
    PlayTrainBrakeSound(-1, 1.0F, -100.0F);

    if (m_pSkidSoundMaybe) {
        m_pSkidSoundMaybe->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        m_pSkidSoundMaybe->StopSound();
        m_pSkidSoundMaybe = nullptr;
        m_nSkidSoundType = -1;
    }

    if (m_pRoadNoiseSound) {
        m_pRoadNoiseSound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        m_pRoadNoiseSound->StopSound();
        m_pRoadNoiseSound = nullptr;
        m_nRoadNoiseSoundType = -1;
    }

    if (m_pFlatTyreSound) {
        m_pFlatTyreSound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        m_pFlatTyreSound->StopSound();
        m_pFlatTyreSound = nullptr;
        m_nFlatTyreSoundType = -1;
    }

    if (m_pReverseGearSound) {
        m_pReverseGearSound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
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

    auto const radioType = m_settings.m_nRadioType;
    if (m_bPlayerDriver && (radioType == RADIO_CIVILIAN || radioType == RADIO_UNKNOWN || radioType == RADIO_EMERGENCY))
        AudioEngine.StopRadio(&m_settings, false);

    if (m_nEngineBankSlotId != -1) {
        const auto usedSlot = m_nEngineBankSlotId - 7;
        auto&      dummyEng = s_DummyEngineSlots[usedSlot];
        if (usedSlot >= 0 && usedSlot < NUM_DUMMY_ENGINE_SLOTS && dummyEng.m_nBankId == m_nEngineDecelerateSoundBankId)
            dummyEng.m_nUsageCount = std::max(0, dummyEng.m_nUsageCount - 1);

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

void CAEVehicleAudioEntity::PlaySkidSound(int16 soundType, float speed, float volume) {
    plugin::CallMethod<0x4F8360, CAEAudioEntity*, int16, float, float>(this, soundType, speed, volume);
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

float CAEVehicleAudioEntity::GetFlyingMetalVolume(CPhysical* physical) {
    const auto fTurnSpeedSquared = physical->m_vecTurnSpeed.SquaredMagnitude();
    if (fTurnSpeedSquared >= 0.5625F)
        return CAEAudioUtility::AudioLog10(1.0F) * 10.0F;

    const auto fVol = fTurnSpeedSquared / 0.5625F;
    if (fVol < 1.0e-10F)
        return -100.0F;

    return CAEAudioUtility::AudioLog10(fVol) * 10.0F;
}

void CAEVehicleAudioEntity::PlayTrainBrakeSound(int16 soundType, float speed, float volume) {
    plugin::CallMethod<0x4FA630, CAEAudioEntity*, int16, float, float>(this, soundType, speed, volume);
}
