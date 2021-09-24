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
tScannerSlot*& CAEPoliceScannerAudioEntity::s_pCurrentSlots = *(tScannerSlot**)0xB61D10;
tScannerSlot* (CAEPoliceScannerAudioEntity::s_ScannerSlotFirst) = new tScannerSlot[NUM_POLICE_SCANNER_SLOTS](); // 0xB61D34
tScannerSlot* (CAEPoliceScannerAudioEntity::s_ScannerSlotSecond) = new tScannerSlot[NUM_POLICE_SCANNER_SLOTS](); // 0xB61D20
bool& CAEPoliceScannerAudioEntity::s_bStoppingScanner = *(bool*)0xB61CFC;
bool& CAEPoliceScannerAudioEntity::s_bScannerDisabled = *(bool*)0xB61D4E;
eScannerPlaybackState& CAEPoliceScannerAudioEntity::s_nScannerPlaybackState = *(eScannerPlaybackState*)0xB61D4C;
uint32& CAEPoliceScannerAudioEntity::s_NextNewScannerDialogueTime = *(uint32*)0xB61D50;

CAEPoliceScannerAudioEntity* CAEPoliceScannerAudioEntity::s_pPSControlling = *(CAEPoliceScannerAudioEntity**)0xB61D48;

// 0x56DA00
CAEPoliceScannerAudioEntity::CAEPoliceScannerAudioEntity() {
    // NOP
}

// 0x4E6E00
CAEPoliceScannerAudioEntity::~CAEPoliceScannerAudioEntity() {
    if (s_pPSControlling == this && s_nScannerPlaybackState == eScannerPlaybackState::ONE) {
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
    s_nScannerPlaybackState      = eScannerPlaybackState::ZERO;
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

            s_SlotState = currentSlot.bankId < 0 || currentSlot.sfxId < 0;
            s_SlotState = (s_SlotState + 2);
        }
    }
}

// 0x4E6CD0
void CAEPoliceScannerAudioEntity::LoadSlots() {
    plugin::Call<0x4E6CD0>();

    /*
    if (!s_pCurrentSlots)
        return;

    int16 bankSlotId = 33;
    bool v1 = true;

    for (auto slotIndex = 0; slotIndex < NUM_POLICE_SCANNER_SLOTS; slotIndex++) {
        if (s_SlotState) {
            if (s_SlotState == 2) {
                bool v5 = AEAudioHardware.IsSoundLoaded(s_pCurrentSlots[slotIndex].bankId, s_pCurrentSlots[slotIndex].sfxId, bankSlotId);
                if (v5)
                    s_SlotState = 3;
                else
                    v1 = false;
            }
        } else if (s_pCurrentSlots[slotIndex].bankId < 0 || s_pCurrentSlots[slotIndex].sfxId < 0) {
            s_SlotState = 1;
        } else {
            if (!CStreaming::IsVeryBusy()) {
                AEAudioHardware.LoadSound(s_pCurrentSlots[slotIndex].bankId, s_pCurrentSlots[slotIndex].sfxId, bankSlotId);
                s_SlotState = 2;
            }
            v1 = false;
        }
        ++bankSlotId;
        s_SlotState = (s_SlotState + 2);
    }

    if (v1)
        s_nScannerPlaybackState = eScannerPlaybackState::FOUR;
    */
}

// 0x4E6DB0
void CAEPoliceScannerAudioEntity::EnableScanner() {
    s_bScannerDisabled = false;
}

// 0x4E71B0
void CAEPoliceScannerAudioEntity::DisableScanner(bool a1, bool bStopSound) {
    s_bScannerDisabled = true;
    if (a1 && s_nScannerPlaybackState == eScannerPlaybackState::ONE) {
        if (s_pPSControlling)
            StopScanner(bStopSound);
    }
}

// 0x4E6DC0
void CAEPoliceScannerAudioEntity::StopScanner(bool bStopSound) {
    if (s_nScannerPlaybackState == eScannerPlaybackState::ZERO)
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
    AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_SCANNER_NOISE_STOP, 0.0f, 1.0f);
    s_SlotState = 0x10001;
    dword_B61D18 = 0x10001;
    s_NextNewScannerDialogueTime = s_NextNewScannerDialogueTime + CTimer::GetTimeInMS();
    s_nScannerPlaybackState = eScannerPlaybackState::ZERO;
    s_pPSControlling = nullptr;
    s_pCurrentSlots = nullptr;
    s_bStoppingScanner = false;
    s_fVolumeOffset = 0;
    word_B61D1C = 1;

    for (auto i = 0; i < NUM_POLICE_SCANNER_SLOTS; i++) {
        s_ScannerSlotFirst[i] = -1;
        s_ScannerSlotSecond[i] = -1;
    }
}

// 0x4E6F60
void CAEPoliceScannerAudioEntity::PlayLoadedDialogue() {
    plugin::CallMethod<0x4E6F60, CAEPoliceScannerAudioEntity*>(this);
}

// 0x4E6B60
void CAEPoliceScannerAudioEntity::PopulateScannerDialogueLists(tScannerSlot* first, tScannerSlot* second) {
    if (s_nScannerPlaybackState == eScannerPlaybackState::ZERO) {
        for (auto slotIndex = 0; slotIndex < NUM_POLICE_SCANNER_SLOTS; slotIndex++) {
            s_ScannerSlotFirst[slotIndex] = first[slotIndex];
            s_ScannerSlotSecond[slotIndex] = second[slotIndex];
        }
    }
}

// inlined
// 0x4E6C00
bool CAEPoliceScannerAudioEntity::CanWePlayNewScannerDialogue() {
    if (s_nScannerPlaybackState == eScannerPlaybackState::ONE)
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
        s_nScannerPlaybackState = eScannerPlaybackState::TWO;
        s_nPlaybackStartTime = CTimer::GetTimeInMS() + 2000;
        s_nAbortPlaybackTime = CTimer::GetTimeInMS() + 5000;
    }
}

// 0x4E7590
void CAEPoliceScannerAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    if (curPlayPos == -1) {
        s_pSound = nullptr;
        if (s_bStoppingScanner) {
            if (s_nScannerPlaybackState == eScannerPlaybackState::ONE) {
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
    // plugin::CallMethod<0x4E7630, CAEPoliceScannerAudioEntity*>(this);

    static constexpr uint32 startDelay = 300;   // 0x8C8154
    static constexpr float noiseVolume = -6.0f; // 0x8C8158
    static constexpr float clickVolume = 0.0f;  // 0xB61D54

    bool finishPlaying;
    if (TheCamera.m_bWideScreenOn && s_nScannerPlaybackState == eScannerPlaybackState::ONE) {
        finishPlaying = true;
        s_bStoppingScanner = true;
    } else {
        finishPlaying = s_bStoppingScanner;
    }

    if (s_nScannerPlaybackState > eScannerPlaybackState::SEVEN)
        return;

    switch (s_nScannerPlaybackState) {
    case eScannerPlaybackState::TWO:
        if (CTimer::GetTimeInMS() > s_nAbortPlaybackTime || finishPlaying) {
            FinishedPlayingScannerDialogue();
            break;
        }

        LoadSlots();
        break;
    case eScannerPlaybackState::FOUR:
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
            s_nScannerPlaybackState = eScannerPlaybackState::FIVE;
        }
        break;
    case eScannerPlaybackState::FIVE:
        if (finishPlaying) {
            FinishedPlayingScannerDialogue();
            break;
        }

        if (CTimer::GetTimeInMS() >= s_nPlaybackStartTime && s_pPSControlling) {
            s_nScannerPlaybackState = eScannerPlaybackState::SEVEN;
            s_pPSControlling->PlayLoadedDialogue();
        }
        break;
    default:
        return;
    }
}

void CAEPoliceScannerAudioEntity::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CAEPoliceScannerAudioEntity", "Constructor", 0x56DA00, &CAEPoliceScannerAudioEntity::Constructor);
    Install("CAEPoliceScannerAudioEntity", "Destructor", 0x4E6E00, &CAEPoliceScannerAudioEntity::Destructor);
    Install("CAEPoliceScannerAudioEntity", "StaticInitialise", 0x5B9C30, &CAEPoliceScannerAudioEntity::StaticInitialise);
    Install("CAEPoliceScannerAudioEntity", "Reset", 0x4E6E90, &CAEPoliceScannerAudioEntity::Reset);
    // Install("CAEPoliceScannerAudioEntity", "AddAudioEvent", 0x4E71E0, &CAEPoliceScannerAudioEntity::AddAudioEvent);
    Install("CAEPoliceScannerAudioEntity", "PrepSlots", 0x4E6BC0, &CAEPoliceScannerAudioEntity::PrepSlots);
    // Install("CAEPoliceScannerAudioEntity", "LoadSlots", 0x4E6CD0, &CAEPoliceScannerAudioEntity::LoadSlots);
    Install("CAEPoliceScannerAudioEntity", "EnableScanner", 0x4E6DB0, &CAEPoliceScannerAudioEntity::EnableScanner);
    Install("CAEPoliceScannerAudioEntity", "DisableScanner", 0x4E71B0, &CAEPoliceScannerAudioEntity::DisableScanner);
    Install("CAEPoliceScannerAudioEntity", "StopScanner", 0x4E6DC0, &CAEPoliceScannerAudioEntity::StopScanner);
    Install("CAEPoliceScannerAudioEntity", "FinishedPlayingScannerDialogue", 0x4E6C30, &CAEPoliceScannerAudioEntity::FinishedPlayingScannerDialogue);
    // Install("CAEPoliceScannerAudioEntity", "PlayLoadedDialogue", 0x4E6F60, &CAEPoliceScannerAudioEntity::PlayLoadedDialogue);
    Install("CAEPoliceScannerAudioEntity", "PopulateScannerDialogueLists", 0x4E6B60, &CAEPoliceScannerAudioEntity::PopulateScannerDialogueLists);
    Install("CAEPoliceScannerAudioEntity", "CanWePlayNewScannerDialogue", 0x4E6C00, &CAEPoliceScannerAudioEntity::CanWePlayNewScannerDialogue);
    Install("CAEPoliceScannerAudioEntity", "PlayPoliceScannerDialogue", 0x4E6ED0, &CAEPoliceScannerAudioEntity::PlayPoliceScannerDialogue);
    Install("CAEPoliceScannerAudioEntity", "UpdateParameters", 0x4E7590, &CAEPoliceScannerAudioEntity::UpdateParameters_Reversed);
    Install("CAEPoliceScannerAudioEntity", "Service", 0x4E7630, &CAEPoliceScannerAudioEntity::Service);
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
