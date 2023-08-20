/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AEAudioEntity.h"
#include "AESound.h"

enum eAudioPedType : int16 {
    PED_TYPE_GEN    = 0,
    PED_TYPE_EMG    = 1,
    PED_TYPE_PLAYER = 2,
    PED_TYPE_GANG   = 3,
    PED_TYPE_GFD    = 4,
    PED_TYPE_SPC    = 5
};

class CAEPedSpeechAudioEntity;

struct tSpeechSlot {
    uint16 m_nState;
    uint16 field_02;
    CAEPedSpeechAudioEntity* m_PedSpeechAE;
    uint32 field_08;
    uint16 m_nSoundId;
    uint16 m_nBankId;
    uint32 m_nTime;
    uint16 m_nPhraseId;
    uint16 m_nVoiceType;
    uint8 field_18;
    uint8 field_19;
    uint8 field_1A;
    uint8 field_1B;

    void Reset() {
        m_PedSpeechAE = nullptr;
        m_nState = field_08 = m_nTime = 0;
        m_nSoundId = m_nBankId = m_nPhraseId = m_nVoiceType = -1;
        field_19 = field_1A = field_18 = 0;
    }
};
VALIDATE_SIZE(tSpeechSlot, 0x1C);

struct tPhraseMemory {
    int16 m_nSoundId{-1};
    int16 m_nBankId{-1};

    void Reset() {
        m_nSoundId = m_nBankId = -1;
    }
};
VALIDATE_SIZE(tPhraseMemory, 0x04);

class NOTSA_EXPORT_VTABLE CAEPedSpeechAudioEntity : public CAEAudioEntity {
public:
    char      field_7C[20];
    bool      f90;
    char      field_91;
    int16     m_nVoiceType;
    int16     m_nVoiceId;
    int16     m_nVoiceGender;
    bool      m_bTalking;
    bool      m_bSpeechDisabled;
    bool      m_bSpeechForScriptsDisabled;
    int8      m_nVocalEnableFlag;
    char      field_9C;
    char      field_9D;
    char      field_9E;
    char      field_9F;
    CAESound* m_pSound;
    int16     m_nSoundId;
    int16     m_nBankId;
    int16     m_nPedSpeechSlotIndex;
    int16     field_AA;
    float     m_fVoiceVolume;
    int16     m_nCurrentPhraseId;
    int16     field_B2;
    uint32    field_B4[19];

public:
    static int16& s_nCJWellDressed;
    static int16& s_nCJFat;
    static int16& s_nCJGangBanging;
    static int32& s_nCJBasicMood;
    static int32& s_nCJMoodOverrideTime;
    static bool& s_bForceAudible;
    static bool& s_bAPlayerSpeaking;
    static bool& s_bAllSpeechDisabled;
    static int16& s_ConversationLength;
    static int16 (&s_Conversation)[8];
    static bool& s_bPlayerConversationHappening;
    static bool& s_bPedConversationHappening;
    static CPed*& s_pPlayerConversationPed;

    static CPed*& s_pConversationPed1;
    static int16& s_pConversationPedSlot1;

    static CPed*& s_pConversationPed2;
    static int16& s_pConversationPedSlot2;

    static int16& s_NextSpeechSlot;

    static constexpr auto PHRASE_MEMORY_COUNT = 150;
    static inline auto& s_PhraseMemory = *reinterpret_cast<std::array<tPhraseMemory, PHRASE_MEMORY_COUNT>*>(0xB61418);

    static constexpr auto NUM_PED_SPEECH_SLOTS = 6;
    static inline auto& s_PedSpeechSlots = *reinterpret_cast<std::array<tSpeechSlot, NUM_PED_SPEECH_SLOTS>*>(0xB61C38);

public:
    static void InjectHooks();

    CAEPedSpeechAudioEntity();
    ~CAEPedSpeechAudioEntity() = default;

    static bool __stdcall IsGlobalContextImportantForInterupting(int16 globalCtx); // typo: Interrupting
    static bool IsGlobalContextUberImportant(int16 globalCtx);
    static int16 __stdcall GetNextMoodToUse(int16 lastMood);
    static int32 __stdcall GetVoiceForMood(int16 mood);
    static int16 CanWePlayScriptedSpeech();
    static float GetSpeechContextVolumeOffset(int16 a1);
    static int8 RequestPedConversation(CPed* ped1, CPed* ped2);
    static void ReleasePedConversation();
    static int16 GetCurrentCJMood();
    static void StaticInitialise();
    static int16 GetSpecificSpeechContext(int16, int16 voiceType);
    static void Service();
    static void Reset();
    static int8 ReservePedConversationSpeechSlots();
    static int8 ReservePlayerConversationSpeechSlot();
    static bool RequestPlayerConversation(CPed* ped);
    static void ReleasePlayerConversation();
    static void SetUpConversation();
    static int16 GetAudioPedType(Const char* name);
    static int32 GetVoice(char* name, int16 type);
    static void DisableAllPedSpeech();
    bool        IsGlobalContextPain(int16 globalCtx);
    static void SetCJMood(int16, uint32, int16, int16, int16);
    static void EnableAllPedSpeech();
    static bool IsCJDressedInForGangSpeech();
    int8        GetSexForSpecialPed(uint32 a1);

    bool IsGlobalContextImportantForWidescreen(int16 globalCtx);
    int32 GetRepeatTime(int16 a1);
    void LoadAndPlaySpeech(uint32 offset);
    int32 GetNumSlotsPlayingContext(int16 context);
    uint32 GetNextPlayTime(int16 globalCtx);
    void SetNextPlayTime(int16 globalCtx);
    void DisablePedSpeech(int16 a1);
    void DisablePedSpeechForScriptSpeech(int16 a1);
    int8 CanPedSayGlobalContext(int16 a2);
    int8 GetVoiceAndTypeFromModel(eModelID modelId);
    int16 GetSoundAndBankIDs(int16 phraseId, int16* a3);
    bool CanWePlayGlobalSpeechContext(int16 a2);
    int16 AddSayEvent(eAudioEvents audioEvent, int16 phraseId, uint32 a4, float a5, uint8 a6, uint8 a7, uint8 a8);
    void Initialise(CEntity* ped);
    bool CanPedHoldConversation();
    bool IsGlobalContextImportantForStreaming(int16 a1);
    void EnablePedSpeech();
    void EnablePedSpeechForScriptSpeech();
    void StopCurrentSpeech();
    int8 GetSoundAndBankIDsForScriptedSpeech(int32 a2);
    int8 GetSexFromModel(int32);
    bool GetPedTalking();
    int8 GetVoiceAndTypeForSpecialPed(uint32 modelNameHash);

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;
    virtual void AddScriptSayEvent(int32, int32, uint8, uint8, uint8);
    virtual void Terminate();
    virtual void PlayLoadedSound();
    virtual int16 GetAllocatedVoice();
    virtual bool WillPedChatAboutTopic(int16 topic);
    virtual int16 GetPedType();
    virtual bool IsPedFemaleForAudio();

private:
    CAEPedSpeechAudioEntity* Constructor();

    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos);
    void AddScriptSayEvent_Reversed(int32, int32, uint8, uint8, uint8);
    void Terminate_Reversed();
    void PlayLoadedSound_Reversed();
    int16 GetAllocatedVoice_Reversed();
    bool WillPedChatAboutTopic_Reversed(int16 topic);
    int16 GetPedType_Reversed();
    bool IsPedFemaleForAudio_Reversed();

    // NOTSA
    tSpeechSlot& GetCurrentPedSpeech() {
        assert(m_nPedSpeechSlotIndex >= 0 && (size_t)(m_nPedSpeechSlotIndex) < std::size(s_PedSpeechSlots));
        return s_PedSpeechSlots[m_nPedSpeechSlotIndex];
    }
};

VALIDATE_SIZE(CAEPedSpeechAudioEntity, 0x100);
