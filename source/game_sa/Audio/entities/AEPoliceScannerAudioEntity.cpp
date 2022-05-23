#include "StdInc.h"

#include "AEPoliceScannerAudioEntity.h"

#include "AEAudioHardware.h"

#define NUM_POLICE_SCANNER_SLOTS 5

int32& CAEPoliceScannerAudioEntity::dword_B61D18 = *(int32*)0xB61D18; // unused
int16& CAEPoliceScannerAudioEntity::word_B61D1C = *(int16*)0xB61D1C; // unused

float& CAEPoliceScannerAudioEntity::s_fVolumeOffset = *(float*)0xB61CF8;
CAESound*& CAEPoliceScannerAudioEntity::s_pSound = *(CAESound**)0xB61D00;
uint32& CAEPoliceScannerAudioEntity::s_nAbortPlaybackTime = *(uint32*)0xB61D08;
uint32& CAEPoliceScannerAudioEntity::s_nPlaybackStartTime = *(uint32*)0xB61D0C;
int16& CAEPoliceScannerAudioEntity::s_nSectionPlaying = *(int16*)0xB61D04;

int32& CAEPoliceScannerAudioEntity::s_SlotState = *(int32*)0xB61D14;
tScannerSlot* &CAEPoliceScannerAudioEntity::s_pCurrentSlots = *(tScannerSlot**)0xB61D10;
tScannerSlot (&CAEPoliceScannerAudioEntity::s_ScannerSlotFirst)[NUM_POLICE_SCANNER_SLOTS] = *(tScannerSlot (*)[NUM_POLICE_SCANNER_SLOTS])0xB61D34;
tScannerSlot (&CAEPoliceScannerAudioEntity::s_ScannerSlotSecond)[NUM_POLICE_SCANNER_SLOTS] = *(tScannerSlot (*)[NUM_POLICE_SCANNER_SLOTS])0xB61D20;
bool& CAEPoliceScannerAudioEntity::s_bStoppingScanner = *(bool*)0xB61CFC;
bool& CAEPoliceScannerAudioEntity::s_bScannerDisabled = *(bool*)0xB61D4E;
CAEPoliceScannerAudioEntity::State& CAEPoliceScannerAudioEntity::s_nScannerPlaybackState = *(CAEPoliceScannerAudioEntity::State*)0xB61D4C;
uint32& CAEPoliceScannerAudioEntity::s_NextNewScannerDialogueTime = *(uint32*)0xB61D50;

CAEPoliceScannerAudioEntity* CAEPoliceScannerAudioEntity::s_pPSControlling = *(CAEPoliceScannerAudioEntity**)0xB61D48;

// 0x4E6E00
CAEPoliceScannerAudioEntity::~CAEPoliceScannerAudioEntity() {
    if (s_pPSControlling == this && s_nScannerPlaybackState == ONE) {
        s_bStoppingScanner = true;
        if (s_pSound) {
            s_pSound->StopSoundAndForget();
            s_pSound = nullptr;
        }
        FinishedPlayingScannerDialogue();
    }
}

// 0x5B9C30
void CAEPoliceScannerAudioEntity::StaticInitialise() {
    s_fVolumeOffset              = 0;
    s_pCurrentSlots              = nullptr;
    s_pPSControlling             = nullptr;
    s_bScannerDisabled           = false;
    s_nScannerPlaybackState      = STATE_INITIAL;
    s_NextNewScannerDialogueTime = 0;
}

// 0x4E6E90
void CAEPoliceScannerAudioEntity::Reset() {
    StopScanner(true);
    FinishedPlayingScannerDialogue();
}

// 0x4E71E0
void CAEPoliceScannerAudioEntity::AddAudioEvent(eAudioEvents event, eCrimeType crimeType, const CVector& point) {
    plugin::CallMethod<0x4E71E0, CAEPoliceScannerAudioEntity*, eAudioEvents, eCrimeType, const CVector&>(this, event, crimeType, point);
}

// 0x4E6BC0
void CAEPoliceScannerAudioEntity::PrepSlots() {
    if (s_pCurrentSlots) {
        for (auto slotIndex = 0; slotIndex < NUM_POLICE_SCANNER_SLOTS; slotIndex++) {
            auto& currentSlot = s_pCurrentSlots[slotIndex];

            s_SlotState = currentSlot.IsNotInitialized();
            s_SlotState = (s_SlotState + 2);
        }
    }
}

// 0x4E6CD0
void CAEPoliceScannerAudioEntity::LoadSlots() {
    // return plugin::Call<0x4E6CD0>();

    if (!s_pCurrentSlots)
        return;

    int16 bankSlotId = 33;
    bool v1 = true;

    for (auto slotIndex = 0; slotIndex < NUM_POLICE_SCANNER_SLOTS; slotIndex++) {
        const auto& currentSlot = s_pCurrentSlots[slotIndex];

        if (s_SlotState) {
            if (s_SlotState == 2) {
                bool v5 = AEAudioHardware.IsSoundLoaded(currentSlot.bankId, currentSlot.sfxId, bankSlotId);
                if (v5)
                    s_SlotState = 3;
                else
                    v1 = false;
            }
        } else if (currentSlot.IsNotInitialized()) {
            s_SlotState = 1;
        } else {
            if (!CStreaming::IsVeryBusy()) {
                AEAudioHardware.LoadSound(currentSlot.bankId, currentSlot.sfxId, bankSlotId);
                s_SlotState = 2;
            }
            v1 = false;
        }
        ++bankSlotId;
        s_SlotState = (s_SlotState + 2);
    }

    if (v1)
        s_nScannerPlaybackState = FOUR;
}

// 0x4E6DB0
void CAEPoliceScannerAudioEntity::EnableScanner() {
    s_bScannerDisabled = false;
}

// 0x4E71B0
void CAEPoliceScannerAudioEntity::DisableScanner(bool a1, bool bStopSound) {
    s_bScannerDisabled = true;
    if (a1 && s_nScannerPlaybackState == ONE) {
        if (s_pPSControlling)
            StopScanner(bStopSound);
    }
}

// 0x4E6DC0
void CAEPoliceScannerAudioEntity::StopScanner(bool bStopSound) {
    if (s_nScannerPlaybackState == STATE_INITIAL)
        return;

    s_bStoppingScanner = true;
    if (bStopSound) {
        if (s_pSound) {
            s_pSound->StopSoundAndForget();
            s_pSound = nullptr;
        }
        FinishedPlayingScannerDialogue();
    }
}

// 0x4E6C30
void CAEPoliceScannerAudioEntity::FinishedPlayingScannerDialogue() {
    AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_SCANNER_NOISE_STOP);
    s_nScannerPlaybackState      = STATE_INITIAL;
    s_SlotState                  = 0x10001;
    dword_B61D18                 = 0x10001;
    word_B61D1C                  = 1;
    s_pPSControlling             = nullptr;
    s_pCurrentSlots              = nullptr;
    s_bStoppingScanner           = false;
    s_fVolumeOffset              = 0;
    s_NextNewScannerDialogueTime = s_NextNewScannerDialogueTime + CTimer::GetTimeInMS();

    for (auto i = 0; i < NUM_POLICE_SCANNER_SLOTS; i++) {
        s_ScannerSlotFirst[i].Clear();
        s_ScannerSlotSecond[i].Clear();
    }
}

// 0x4E6F60
void CAEPoliceScannerAudioEntity::PlayLoadedDialogue() {
    plugin::CallMethod<0x4E6F60, CAEPoliceScannerAudioEntity*>(this);
}

// 0x4E6B60
void CAEPoliceScannerAudioEntity::PopulateScannerDialogueLists(tScannerSlot* first, tScannerSlot* second) {
    if (s_nScannerPlaybackState == STATE_INITIAL) {
        for (auto slotIndex = 0; slotIndex < NUM_POLICE_SCANNER_SLOTS; slotIndex++) {
            s_ScannerSlotFirst[slotIndex] = first[slotIndex];
            s_ScannerSlotSecond[slotIndex] = second[slotIndex];
        }
    }
}

// inlined
// 0x4E6C00
bool CAEPoliceScannerAudioEntity::CanWePlayNewScannerDialogue() {
    if (s_nScannerPlaybackState == ONE)
        return false;

    if (s_NextNewScannerDialogueTime > CTimer::GetTimeInMS())
        return false;

    if (TheCamera.m_bWideScreenOn)
        return false;

    if (s_bScannerDisabled)
        return false;

    return true;
}

// 0x4E6ED0
void CAEPoliceScannerAudioEntity::PlayPoliceScannerDialogue(tScannerSlot* first, tScannerSlot* second) {
    if (CanWePlayNewScannerDialogue()) {
        PopulateScannerDialogueLists(first, second);
        s_pPSControlling = this;
        s_nSectionPlaying = 0;
        s_pCurrentSlots = s_ScannerSlotFirst;
        PrepSlots();
        s_nScannerPlaybackState = TWO;
        s_nPlaybackStartTime = CTimer::GetTimeInMS() + 2000;
        s_nAbortPlaybackTime = CTimer::GetTimeInMS() + 5000;
    }
}

// 0x4E7590
void CAEPoliceScannerAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    if (curPlayPos == -1) {
        s_pSound = nullptr;
        if (s_bStoppingScanner) {
            if (s_nScannerPlaybackState == ONE) {
                s_bStoppingScanner = true;
                FinishedPlayingScannerDialogue();
            }
            return;
        }
        PlayLoadedDialogue();
        return;
    }

    if (s_bStoppingScanner) {
        sound->m_fVolume = sound->m_fVolume - 6.0f;
        return;
    }

    if (sound->m_nSoundLength > 0 && curPlayPos > sound->m_nSoundLength - 40 && sound->m_nBankSlotId != 37) {
        sound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        s_pSound = nullptr;
        PlayLoadedDialogue();
        return;
    }
}

// 0x4E7630
void CAEPoliceScannerAudioEntity::Service() {
    // return plugin::Call<0x4E7630>();

    static constexpr uint32 startDelay = 300;   // 0x8C8154
    static constexpr float noiseVolume = -6.0f; // 0x8C8158
    static constexpr float clickVolume = 0.0f;  // 0xB61D54

    bool finishPlaying;
    if (TheCamera.m_bWideScreenOn && s_nScannerPlaybackState == ONE) {
        finishPlaying = true;
        s_bStoppingScanner = true;
    } else {
        finishPlaying = s_bStoppingScanner;
    }

    if (s_nScannerPlaybackState > SEVEN)
        return;

    switch (s_nScannerPlaybackState) {
    case TWO:
        if (CTimer::GetTimeInMS() > s_nAbortPlaybackTime || finishPlaying) {
            FinishedPlayingScannerDialogue();
            break;
        }

        LoadSlots();
        break;
    case FOUR:
        if (finishPlaying) {
            FinishedPlayingScannerDialogue();
            break;
        }

        if (CTimer::GetTimeInMS() >= s_nPlaybackStartTime) {
            if (CAEVehicleAudioEntity::s_pVehicleAudioSettingsForRadio)
                s_fVolumeOffset = 0.0f;
            else
                s_fVolumeOffset = -8.0f;

            AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_SCANNER_CLICK, s_fVolumeOffset + clickVolume, 1.0f);
            AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_SCANNER_NOISE_START, s_fVolumeOffset + noiseVolume, 1.0f);
            s_nPlaybackStartTime = startDelay + CTimer::GetTimeInMS();
            s_nScannerPlaybackState = FIVE;
        }
        break;
    case FIVE:
        if (finishPlaying) {
            FinishedPlayingScannerDialogue();
            break;
        }

        if (CTimer::GetTimeInMS() >= s_nPlaybackStartTime && s_pPSControlling) {
            s_nScannerPlaybackState = SEVEN;
            s_pPSControlling->PlayLoadedDialogue();
        }
        break;
    default:
        return;
    }
}

void CAEPoliceScannerAudioEntity::InjectHooks() {
    RH_ScopedClass(CAEPoliceScannerAudioEntity);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Constructor, 0x56DA00);
    RH_ScopedInstall(Destructor, 0x4E6E00);
    RH_ScopedInstall(StaticInitialise, 0x5B9C30);
    RH_ScopedInstall(Reset, 0x4E6E90);
    // RH_ScopedInstall(AddAudioEvent, 0x4E71E0);
    RH_ScopedInstall(PrepSlots, 0x4E6BC0);
    // RH_ScopedInstall(LoadSlots, 0x4E6CD0);
    RH_ScopedInstall(EnableScanner, 0x4E6DB0);
    RH_ScopedInstall(DisableScanner, 0x4E71B0);
    RH_ScopedInstall(StopScanner, 0x4E6DC0);
    RH_ScopedInstall(FinishedPlayingScannerDialogue, 0x4E6C30);
    // RH_ScopedInstall(PlayLoadedDialogue, 0x4E6F60);
    RH_ScopedInstall(PopulateScannerDialogueLists, 0x4E6B60);
    RH_ScopedInstall(CanWePlayNewScannerDialogue, 0x4E6C00);
    RH_ScopedInstall(PlayPoliceScannerDialogue, 0x4E6ED0);
    RH_ScopedVirtualInstall(UpdateParameters, 0x4E7590);
    // RH_ScopedInstall(Service, 0x4E7630);
}

CAEPoliceScannerAudioEntity* CAEPoliceScannerAudioEntity::Constructor() {
    this->CAEPoliceScannerAudioEntity::CAEPoliceScannerAudioEntity();
    return this;
}

CAEPoliceScannerAudioEntity* CAEPoliceScannerAudioEntity::Destructor() {
    this->CAEPoliceScannerAudioEntity::~CAEPoliceScannerAudioEntity();
    return this;
}

void CAEPoliceScannerAudioEntity::UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos) {
    CAEPoliceScannerAudioEntity::UpdateParameters(sound, curPlayPos);
}
