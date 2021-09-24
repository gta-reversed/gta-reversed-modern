#pragma once

#include "AEAudioEntity.h"

enum class eSlotState : int32 {
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
};

enum class eScannerPlaybackState : int32 {
    ZERO = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
};

struct tScannerSlot {
    int16 bankId;
    int16 sfxId;

    tScannerSlot() {
        bankId = -1;
        sfxId = -1;
    }

    tScannerSlot& operator=(int16 value) {
        bankId = value;
        sfxId = value;
        return *this;
    }

    tScannerSlot& operator=(const tScannerSlot& right) {
        bankId = right.bankId;
        sfxId = right.sfxId;
        return *this;
    }
};

class CAEPoliceScannerAudioEntity : public CAEAudioEntity {
public:
    static float&     s_fVolumeOffset;
    static bool&      s_bStoppingScanner;
    static CAESound*& s_pSound;
    static int16&     word_B61D04;
    static uint32&    s_nAbortPlaybackTime;
    static uint32&    s_nPlaybackStartTime;
    static int16&     s_nSectionPlaying;
    static int32&     s_SlotState;
    static int32&     dword_B61D18;
    static int16&     word_B61D1C;

    static tScannerSlot*& s_pCurrentSlots;
    static tScannerSlot*  s_ScannerSlotSecond;
    static tScannerSlot*  s_ScannerSlotFirst;

    static CAEPoliceScannerAudioEntity* s_pPSControlling;
    static eScannerPlaybackState&       s_nScannerPlaybackState;
    static bool&                        s_bScannerDisabled;
    static uint32&                      s_NextNewScannerDialogueTime;

public:
    CAEPoliceScannerAudioEntity();
    ~CAEPoliceScannerAudioEntity();

    static void StaticInitialise();
    static void Reset();

    void AddAudioEvent(eAudioEvents event, eCrimeType crimeType, const CVector& point);

    static void PrepSlots();
    static void LoadSlots();

    static void EnableScanner();
    static void DisableScanner(bool a1, bool bStopSound);
    static void StopScanner(bool bStopSound);

    static void FinishedPlayingScannerDialogue();
    void PlayLoadedDialogue();

    static void PopulateScannerDialogueLists(tScannerSlot* first, tScannerSlot* second);
    static bool CanWePlayNewScannerDialogue();
    void PlayPoliceScannerDialogue(tScannerSlot* first, tScannerSlot* second);

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;

    void Service();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEPoliceScannerAudioEntity* Constructor();
    CAEPoliceScannerAudioEntity* Destructor();

    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos);
};

VALIDATE_SIZE(CAEPoliceScannerAudioEntity, 0x7C);
