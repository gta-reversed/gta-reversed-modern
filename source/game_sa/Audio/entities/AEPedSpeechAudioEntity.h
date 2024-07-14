/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <Audio/entities/AEAudioEntity.h>
#include <Audio/AESound.h>
#include <Audio/eSoundBank.h>
#include <Audio/PedSpeechContexts.h>
#include <Audio/PedSpeechVoices.h>
#include <Audio/ePedAudioType.h>
#include <Enums/eModelID.h>

class CPed;

enum eCJMood : int16 {
    MOOD_UNK = -1, // notsa

    MOOD_AG = 0,
    MOOD_AR = 1,

    MOOD_CD = 2,
    MOOD_CF = 3, //!< CJ Is fat (?)
    MOOD_CG = 4, //!< CJ Gang banging (?)
    MOOD_CR = 5,

    MOOD_PG = 6,
    MOOD_PR = 7,

    MOOD_WG = 8,
    MOOD_WR = 9,

    //
    // Add above
    //
    MOOD_END // = 10
};

class CAEPedSpeechAudioEntity;

struct CAEPedSpeechSlot {
    enum class eStatus : int16 {
        FREE      = 0,
        LOADING   = 1,
        WAITING   = 2,
        REQUESTED = 3,
        RESERVED  = 4,
        PLAYING   = 5,
    };

    eStatus                  Status{};
    CAEPedSpeechAudioEntity* AudioEntity{};
    CAESound*                Sound{};
    int16                    SoundID{ -1 };
    eSoundBankS16            SoundBankID{ SND_BANK_UNK };
    uint32                   StartPlaybackTime{};
    eGlobalSpeechContextS16  GCtx{ CTX_GLOBAL_UNK };
    eAudioPedType            PedAudioType{ PED_TYPE_UNK };
    bool                     ForceAudible{};
    bool                     IsReservedForPedConversation{};
    bool                     IsReservedForPlayerConversation{};
};
VALIDATE_SIZE(CAEPedSpeechSlot, 0x1C);

struct tPhraseMemory {
    int16         SoundID{ -1 };
    eSoundBankS16 BankID{ SND_BANK_UNK };
};
VALIDATE_SIZE(tPhraseMemory, 0x04);

/*!
 * @brief Holds context info entries
 * @details This is just a made up structure, they just used a huge multi-dim array...
 * @details But it doesn't make a whole lot of sense why they stored the index in
 * @details the array (GCtx) and did a search, when the index matches the array index
 * @details perhaps they meant to make this configurable (to be loaded from a file?)
 * @details but gave up on it? 
 */
struct tGlobalSpeechContextInfo {
    eGlobalSpeechContext                                 GCtx;                           //!< The global context this entry is for
    std::array<eSpecificSpeechContext, PED_TYPE_NUM - 1> SpecificSpeechContext;          //!< Holds values from enums: `eGenSpeechContexts`, `eEmgSpeechContexts`, `ePlySpeechContexts`, `eGngSpeechContexts`, `eGfdSpeechContexts` (But nothing for the SPC ped type)
    int16                                                RepeatTime;                     //!< For how much time this context can't be played
    int16                                                Zero;                           //!< Always zero
    bool                                                 IsImportantForStreaming : 1;    //!< [NOTSA] (?)
    bool                                                 IsImportantForInterrupting : 1; //!< [NOTSA] (?)
    bool                                                 IsImportantForWidescreen : 1;   //!< [NOTSA] (?)
};

/*!
 * @brief Holds per-type speech context info
 * @details See `eGenSpeechContexts`, `eEmgSpeechContexts`, `ePlySpeechContexts`, `eGngSpeechContexts`, `eGfdSpeechContexts`
 */
struct tSpecificSpeechContextInfo {
    int16 FirstSoundID{-1}, LastSoundID{-1};
};
VALIDATE_SIZE(tSpecificSpeechContextInfo, sizeof(int16) * 2);

class NOTSA_EXPORT_VTABLE CAEPedSpeechAudioEntity : public CAEAudioEntity {
public:
    std::array<CAESound*, 5>                                m_Sounds{};
    bool                                                    m_IsInitialized{};
    eAudioPedType                                           m_PedAudioType{};
    ePedSpeechVoiceS16                                      m_VoiceID{};  //!< Exact enum to use depends on `m_PedAudioType` (See `PedSpeechVoices.h`)
    int16                                                   m_IsFemale{};
    bool                                                    m_IsPlayingSpeech{};
    bool                                                    m_IsSpeechDisabled{};
    bool                                                    m_IsSpeechForScriptsDisabled{};
    bool                                                    m_IsFrontend{};
    bool                                                    m_IsForcedAudible{};
    CAESound*                                               m_Sound{};
    int16                                                   m_SoundID{ -1 };
    eSoundBankS16                                           m_BankID{ SND_BANK_UNK };
    int16                                                   m_PedSpeechSlotID{ -1 }; // [0, 5] (See SND_BANK_SLOT_SPEECH1 -> SND_BANK_SLOT_SPEECH6)
    float                                                   m_EventVolume{ -100.f };
    eGlobalSpeechContextS16                                 m_LastGCtx{ CTX_GLOBAL_UNK };
    std::array<uint32, CTX_GLOBAL_PAIN_END - CTX_GLOBAL_PAIN_START - 1> m_NextTimeCanSayPain{};

public:
    static inline auto& s_nCJMoodOverrideTime = StaticRef<uint32>(0xB613E0);  //!< Until when the override is active in [TimeMS]
    static inline auto& s_nCJWellDressed      = StaticRef<int16>(0xB613D0);   //!< Override as CJ being well dressed (-1 => ignore, 0/1 => false/true)
    static inline auto& s_nCJFat              = StaticRef<int16>(0xB613D4);   //!< Override as CJ being fat (-1 => ignore, 0/1 => false/true)
    static inline auto& s_nCJGangBanging      = StaticRef<int16>(0xB613D8);   //!< Override as CJ being with his group (gang) (-1 => ignore, 0/1 => false/true)
    static inline auto& s_nCJBasicMood        = StaticRef<eCJMood>(0xB613DC); //!< Override the basic mood that is used to calculate the current mood (-1 => ignore, 0/1 => false/true)

    static inline auto& s_bForceAudible                  = StaticRef<bool>(0xB613E4);
    static inline auto& s_bAPlayerSpeaking               = StaticRef<bool>(0xB613E5);
    static inline auto& s_bAllSpeechDisabled             = StaticRef<bool>(0xB613E6);

    static inline auto& s_ConversationLength             = StaticRef<int16>(0xB613E8);
    static inline auto& s_Conversation                   = StaticRef<std::array<eGlobalSpeechContextS16, 8>>(0xB613EC);

    static inline auto& s_bPlayerConversationHappening   = StaticRef<bool>(0xB613FC);
    static inline auto& s_bPedConversationHappening      = StaticRef<bool>(0xB613FD);
    static inline auto& s_pPlayerConversationPed         = StaticRef<CPed*>(0xB61400);
    static inline auto& s_pConversationPedSlot2          = StaticRef<int16>(0xB61404);
    static inline auto& s_pConversationPedSlot1          = StaticRef<int16>(0xB61408);
    static inline auto& s_pConversationPed2              = StaticRef<CPed*>(0xB6140C);
    static inline auto& s_pConversationPed1              = StaticRef<CPed*>(0xB61410);
    static inline auto& s_NextSpeechSlot                 = StaticRef<uint16>(0xB61414);

    //! A least-recently-used (FILO) cache of phrases used
    static inline auto& s_PhraseMemory                   = StaticRef<std::array<tPhraseMemory, 150>>(0xB61418);
    static inline auto& s_PedSpeechSlots                 = StaticRef<std::array<CAEPedSpeechSlot, PED_TYPE_NUM>>(0xB61C38);
    static inline auto& gGlobalSpeechContextNextPlayTime = StaticRef<std::array<uint32, CTX_GLOBAL_NUM>>(0xB61670); // PAIN (CTX_GLOBAL_PAIN_START -> CTX_GLOBAL_PAIN_END) is ignored, and `m_NextTimeCanSayPain` is used instead

public:
    static void InjectHooks();

    CAEPedSpeechAudioEntity() noexcept;
    CAEPedSpeechAudioEntity(CPed* ped) noexcept;
    ~CAEPedSpeechAudioEntity() = default;

    static bool IsGlobalContextUberImportant(int16 gCtx);
    static int16 __stdcall GetNextMoodToUse(eCJMood lastMood);
    static int32 __stdcall GetVoiceForMood(int16 mood);
    static int16 CanWePlayScriptedSpeech();
    static float GetSpeechContextVolumeOffset(eGlobalSpeechContextS16 gctx);
    static bool RequestPedConversation(CPed* pedA, CPed* pedB);
    static void ReleasePedConversation();
    static int16 GetCurrentCJMood();
    static void StaticInitialise();
    static eSpecificSpeechContext GetSpecificSpeechContext(eGlobalSpeechContext gCtx, eAudioPedType pedAudioType);
    static void Service();
    static void Reset();
    static bool ReservePedConversationSpeechSlots();
    static bool ReservePlayerConversationSpeechSlot();
    static bool RequestPlayerConversation(CPed* ped);
    static void ReleasePlayerConversation();
    static void SetUpConversation();
    static eAudioPedType GetAudioPedType(const char* name);
    static ePedSpeechVoiceS16 GetVoice(const char* name, eAudioPedTypeS16 type);
    static void DisableAllPedSpeech();
    static bool __stdcall IsGlobalContextPain(eGlobalSpeechContext gCtx);
    static const tGlobalSpeechContextInfo* GetGlobalSpeechContextInfo(eGlobalSpeechContext gCtx);
    static const tSpecificSpeechContextInfo* GetSpecificSpeechContextInfo(eSpecificSpeechContext sCtx, eGlobalSpeechContext gCtx, eAudioPedType pt, ePedSpeechVoiceS16 voice);
    static eSoundBank GetVoiceSoundBank(eGlobalSpeechContext gCtx, eAudioPedType pt, ePedSpeechVoiceS16 voice);

    /*!
     * @addr 0x4E3ED0
     * @brief Set mood override for CJ
     * @param basicMood Use `-1` to not override
     * @param overrideTimeMS
     * @param isGangBanging Use `-1` to not override
     * @param isFat Use `-1` to not override
     * @param isWellDressed Use `-1` to not override
     */
    static void SetCJMood(eCJMood basicMood, uint32 overrideTimeMS, int16 isGangBanging = -1, int16 isFat = -1, int16 isWellDressed = -1);
    static void EnableAllPedSpeech();
    static bool IsCJDressedInForGangSpeech();
    static bool __stdcall IsGlobalContextImportantForInterupting(eGlobalSpeechContext gCtx); // typo: Interrupting

    bool IsGlobalContextImportantForWidescreen(eGlobalSpeechContext gCtx);
    bool IsGlobalContextImportantForStreaming(eGlobalSpeechContext gCtx);
    int8        GetSexForSpecialPed(uint32 a1);
    int16 GetRepeatTime(eGlobalSpeechContext gCtx);
    void LoadAndPlaySpeech(uint32 offset);
    int32 GetNumSlotsPlayingContext(int16 context);
    uint32 GetNextPlayTime(eGlobalSpeechContext gCtx);
    void SetNextPlayTime(eGlobalSpeechContext gCtx);
    void DisablePedSpeech(int16 a1);
    void DisablePedSpeechForScriptSpeech(int16 a1);
    bool CanPedSayGlobalContext(eGlobalSpeechContext gCtx) const;
    int8 GetVoiceAndTypeFromModel(eModelID modelId);
    int16 GetSoundAndBankIDs(eGlobalSpeechContext gCtx, eSpecificSpeechContext& outSpecificSpeechContext);
    int16 CanWePlayGlobalSpeechContext(eGlobalSpeechContext gCtx);
    int16 AddSayEvent(eAudioEvents audioEvent, eGlobalSpeechContext gCtx, uint32 startTimeDelay, float probability, bool overideSilence, bool isForceAudible, bool isFrontEnd);
    void Initialise(CEntity* ped);
    bool CanPedHoldConversation();
    void EnablePedSpeech();
    void EnablePedSpeechForScriptSpeech();
    void StopCurrentSpeech();
    bool GetSoundAndBankIDsForScriptedSpeech(eAudioEvents ae);
    bool GetSexFromModel(eModelID model);
    bool GetPedTalking() const;
    bool GetVoiceAndTypeForSpecialPed(uint32 modelNameHash);
    ePainSpeechVoices GetPainVoice() const;

    bool IsAllSpeechDisabled() const noexcept { return m_IsSpeechDisabled || m_IsSpeechForScriptsDisabled; }

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;
    virtual void AddScriptSayEvent(int32, int32, uint8, uint8, uint8);
    virtual void Terminate();
    virtual void PlayLoadedSound();
    virtual int16 GetAllocatedVoice();
    virtual bool WillPedChatAboutTopic(int16 topic);
    virtual int16 GetPedType();
    virtual bool IsPedFemaleForAudio();

private:
    static int32 GetFreeSpeechSlot();
    uint32& GetNextPlayTimeRef(eGlobalSpeechContext gCtx);

private:
    // 0x4E4F10
    CAEPedSpeechAudioEntity* Constructor() {
        this->CAEPedSpeechAudioEntity::CAEPedSpeechAudioEntity();
        return this;
    }

    // NOTSA
    CAEPedSpeechSlot* GetCurrentSpeech() const {
        assert(!m_IsPlayingSpeech || m_PedSpeechSlotID != -1);
        return m_IsPlayingSpeech
            ? &s_PedSpeechSlots[m_PedSpeechSlotID]
            : nullptr;
    }
};

VALIDATE_SIZE(CAEPedSpeechAudioEntity, 0x100);
