/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <Base.h>
#include <Audio/entities/AEAudioEntity.h>
#include <Audio/AESound.h>
#include <Audio/eSoundBank.h>
#include <Audio/eSoundBankSlot.h>
#include <Audio/PedSpeechContexts.h>
#include <Audio/PedSpeechVoices.h>
#include <Audio/ePedAudioType.h>
#include <Enums/eModelID.h>
#include <Tasks/TaskTypes/TaskComplexFacial.h>
#include <Camera.h>
#include <GameLogic.h>
#include <AEAudioUtility.h>
#include <Weather.h>
#include <Streaming.h>
#include <World.h>

class CAEPedSpeechAudioEntity;
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

using tPedSpeechSlotID = int16;
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
    bool                                                 IsPain : 1;                     //!< [NOTSA] Is this context for pain
};

/*!
 * @brief Holds per-type speech context info
 * @details See `eGenSpeechContexts`, `eEmgSpeechContexts`, `ePlySpeechContexts`, `eGngSpeechContexts`, `eGfdSpeechContexts`
 */
struct tSpecificSpeechContextInfo {
    int16 FirstSoundID{-1}, LastSoundID{-1};

    bool   IsUseable()    const noexcept { return FirstSoundID != -1; }
    size_t GetNumSounds() const noexcept { assert(FirstSoundID <= LastSoundID); return LastSoundID - FirstSoundID + 1; }
};
VALIDATE_SIZE(tSpecificSpeechContextInfo, sizeof(int16) * 2);

class NOTSA_EXPORT_VTABLE CAEPedSpeechAudioEntity : public CAEAudioEntity {
public:
    //! Until when the override is active in [TimeMS]
    static inline auto& s_nCJMoodOverrideTime = StaticRef<uint32>(0xB613E0);

    //!< Override as CJ being well dressed (-1 => ignore, 0/1 => false/true) [Used for mood calculation]
    static inline auto& s_nCJWellDressed = StaticRef<int16>(0xB613D0);

    //!< Override as CJ being fat (-1 => ignore, 0/1 => false/true) [Used for mood calculation]
    static inline auto& s_nCJFat = StaticRef<int16>(0xB613D4);

    //!< Override as CJ being with his group (gang) (-1 => ignore, 0/1 => false/true) [Used for mood calculation]
    static inline auto& s_nCJGangBanging = StaticRef<int16>(0xB613D8);

    //!< Override the basic mood that is used to calculate the current mood (-1 => ignore, 0/1 => false/true) [Used for mood calculation]
    static inline auto& s_nCJBasicMood = StaticRef<eCJMood>(0xB613DC);

    //! If any currently active speech is "ForceAudible" (Must be heard (?))
    static inline auto& s_bForceAudible = StaticRef<bool>(0xB613E4);

    //! No speeches should be played
    static inline auto& s_bAllSpeechDisabled = StaticRef<bool>(0xB613E6);

    //! Is the player speaking
    static inline auto& s_bAPlayerSpeaking = StaticRef<bool>(0xB613E5);

    //! Current conversation length (Not array size!)
    static inline auto& s_ConversationLength = StaticRef<int16>(0xB613E8);

    //! Current conversation contexts
    static inline auto& s_Conversation = StaticRef<std::array<eGlobalSpeechContextS16, 8>>(0xB613EC);

    //! Is the player having a conversation with another ped? (With `s_pPlayerConversationPed`)
    static inline auto& s_bPlayerConversationHappening = StaticRef<bool>(0xB613FC);

    //! The ped the player is having a conversation with (If any)
    static inline auto& s_pPlayerConversationPed = StaticRef<CPed*>(0xB61400);

    //! Are 2 peds having a conversation (`s_pConversationPed1` and `s_pConversationPed2`)
    static inline auto& s_bPedConversationHappening = StaticRef<bool>(0xB613FD);

    //! Conversation peds/slots (Valid if `s_bPedConversationHappening`)
    static inline auto& s_pConversationPed1     = StaticRef<CPed*>(0xB61410);
    static inline auto& s_pConversationPedSlot1 = StaticRef<tPedSpeechSlotID>(0xB61408);
    static inline auto& s_pConversationPed2     = StaticRef<CPed*>(0xB6140C);
    static inline auto& s_pConversationPedSlot2 = StaticRef<tPedSpeechSlotID>(0xB61404);

    //! Next speech-slot to use. This is merrily a hint, rather than an obligation
    static inline auto& s_NextSpeechSlot = StaticRef<tPedSpeechSlotID>(0xB61414);

    //! A least-recently-used (FILO) cache of phrases used
    static inline auto& s_PhraseMemory = StaticRef<std::array<tPhraseMemory, 150>>(0xB61418);

    //! Speech slots (Last one is always reserved for the player!)
    static inline auto&      s_PedSpeechSlots   = StaticRef<std::array<CAEPedSpeechSlot, SND_BANK_SLOT_SPEECH6 - SND_BANK_SLOT_SPEECH1 + 1>>(0xB61C38);
    static inline const auto PLAYER_SPEECH_SLOT = (tPedSpeechSlotID)(s_PedSpeechSlots.size() - 1);

    //! Time when a global context can be played again
    static inline auto& gGlobalSpeechContextNextPlayTime = StaticRef<std::array<uint32, CTX_GLOBAL_NUM>>(0xB61670); // PAIN (CTX_GLOBAL_PAIN_START -> CTX_GLOBAL_PAIN_END) is ignored, and `m_NextTimeCanSayPain` is used instead

    //! Default sound volume of speeches
    static inline const auto SPEECH_SOUND_DEFAULT_VOLUME = 3.f; // 0x8C80EC
public:
    static void InjectHooks();

    CAEPedSpeechAudioEntity(eAudioPedType pt = PED_TYPE_UNK) noexcept;
    CAEPedSpeechAudioEntity(CPed* ped) noexcept;
    ~CAEPedSpeechAudioEntity() = default;

    void Initialise(CEntity* ped);

    bool  IsGlobalContextImportantForWidescreen(eGlobalSpeechContext gCtx);
    bool  IsGlobalContextImportantForStreaming(eGlobalSpeechContext gCtx);
    bool  CanPedSayGlobalContext(eGlobalSpeechContext gCtx) const;
    int16 CanWePlayGlobalSpeechContext(eGlobalSpeechContext gCtx);
    bool  CanPedHoldConversation() const;

    uint32 GetNextPlayTime(eGlobalSpeechContext gCtx) const;
    void   SetNextPlayTime(eGlobalSpeechContext gCtx);

    void  EnablePedSpeech();
    void  DisablePedSpeech(int16 a1);
    void  DisablePedSpeechForScriptSpeech(int16 a1);
    void  EnablePedSpeechForScriptSpeech();
    bool  IsAllSpeechDisabled() const { return m_IsSpeechDisabled || m_IsSpeechForScriptsDisabled; }

    void  StopCurrentSpeech();
    void  LoadAndPlaySpeech(uint32 playbackTimeOffsetMS = 0);
    int16 AddSayEvent(eAudioEvents audioEvent, eGlobalSpeechContext gCtx, uint32 startTimeDelay, float probability, bool overideSilence, bool isForceAudible, bool isFrontEnd);

    bool  GetSexFromModel(eModelID model);
    bool  GetVoiceAndTypeFromModel(eModelID modelId);
    bool  GetSoundAndBankIDsForScriptedSpeech(eAudioEvents ae);
    bool  GetVoiceAndTypeForSpecialPed(uint32 modelNameHash);
    bool  GetSexForSpecialPed(uint32) const { return true; }
    int16 GetRepeatTime(eGlobalSpeechContext gCtx) const;
    int16 GetSoundAndBankIDs(eGlobalSpeechContext gCtx, eSpecificSpeechContext& outSpecificSpeechContext);
    int32 GetNumSlotsPlayingContext(eGlobalSpeechContext gCtx);

    bool              GetPedTalking() const;
    ePainSpeechVoices GetPainVoice() const;

    void                       UpdateParameters(CAESound* sound, int16 playTime) override { return I_UpdateParameters<false>(sound, playTime); }
    virtual void               AddScriptSayEvent(eAudioEvents audioEvent, eAudioEvents scriptID, bool overrideSilence, bool isForceAudible, bool isFrontEnd);
    virtual void               Terminate();
    virtual void               PlayLoadedSound();
    virtual ePedSpeechVoiceS16 GetAllocatedVoice();
    virtual bool               WillPedChatAboutTopic(int16 topic);
    virtual eAudioPedType      GetPedType();
    virtual bool               IsPedFemaleForAudio();

protected:
    // NOTSA
    CAEPedSpeechSlot* GetCurrentSpeech() const {
        assert(!m_IsPlayingSpeech || m_PedSpeechSlotID != -1);
        return m_IsPlayingSpeech
            ? &s_PedSpeechSlots[m_PedSpeechSlotID]
            : nullptr;
    }

private:
    auto&& GetNextPlayTimeRef(this auto&& self, eGlobalSpeechContext gCtx) {
        return IsGlobalContextPain(gCtx)
            ? self.m_NextTimeCanSayPain[gCtx - CTX_GLOBAL_PAIN_START + 1]
            : gGlobalSpeechContextNextPlayTime[gCtx];
    }

public:
    static void StaticInitialise();
    static void Service();
    static void Reset();

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

    /*!
     * @addr 0x4E53B0
     * @brief Calculate (derive) CJ's mood from current game state
     */
    static eCJMood GetCurrentCJMood();

    /*!
     * @addr 0x4E4700
     * @brief Calculate (derive) next mood 
     * @param currMood The current mood
     */
    static eCJMood __stdcall GetNextMoodToUse(eCJMood currMood);

    /*!
     * @addr 0x4E4760
     * @brief Get a random voice for CJ's mood
     * @param mood The mood to get the voice for
     */
    static ePedSpeechVoiceS16 __stdcall GetVoiceForMood(eCJMood mood);

    static bool IsCJDressedInForGangSpeech();

    static void  EnableAllPedSpeech();
    static void  DisableAllPedSpeech();

    static bool __stdcall IsGlobalContextImportantForInterupting(eGlobalSpeechContext gCtx); // typo: Interrupting
    static bool           IsGlobalContextUberImportant(int16 gCtx);
    static bool __stdcall IsGlobalContextPain(eGlobalSpeechContext gCtx);

    static bool  RequestPedConversation(CPed* pedA, CPed* pedB);
    static void  ReleasePedConversation();
    static bool  ReservePedConversationSpeechSlots();
    static bool  ReservePlayerConversationSpeechSlot();
    static bool  RequestPlayerConversation(CPed* ped);
    static void  ReleasePlayerConversation();
    static void  SetUpConversation();

    static eAudioPedType      GetAudioPedType(const char* name);
    static ePedSpeechVoiceS16 GetVoice(const char* name, eAudioPedTypeS16 type);

    static float                             GetSpeechContextVolumeOffset(eGlobalSpeechContextS16 gctx);
    static eSpecificSpeechContext            GetSpecificSpeechContext(eGlobalSpeechContext gCtx, eAudioPedType pedAudioType);
    static const tGlobalSpeechContextInfo*   GetGlobalSpeechContextInfo(eGlobalSpeechContext gCtx);
    static const tSpecificSpeechContextInfo* GetSpecificSpeechContextInfo(eSpecificSpeechContext sCtx, eGlobalSpeechContext gCtx, eAudioPedType pt, ePedSpeechVoiceS16 voice);
    static eSoundBank                        GetVoiceSoundBank(eGlobalSpeechContext gCtx, eAudioPedType pt, ePedSpeechVoiceS16 voice);

private:
    static tPedSpeechSlotID CanWePlayScriptedSpeech();
    static tPedSpeechSlotID GetFreeSpeechSlot();

protected:
    // 0x4E6550 / 0x4E60D0
    template<bool IsPedless>
    int16 I_AddSayEvent(CVector pos, eAudioEvents audioEvent, eGlobalSpeechContext gCtx, uint32 startTimeDelayMs, float probability, bool overrideSilence, bool isForceAudible, bool isFrontEnd);

    // 0x4E3520 / 0x4E4D10
    template<bool IsPedless>
    void I_UpdateParameters(CAESound* sound, int16 playTime);

    // 0x4E5CD0 / 0x4E6380
    template<bool IsPedless>
    void I_PlayLoadedSound(CEntity* attachTo);

protected:
    std::array<CAESound*, 5>                                            m_Sounds{}; //!< Not actually used
    bool                                                                m_IsInitialized{};
    eAudioPedType                                                       m_PedAudioType{ PED_TYPE_UNK };
    ePedSpeechVoiceS16                                                  m_VoiceID{ VOICE_UNK }; //!< Exact enum to use depends on `m_PedAudioType` (See `PedSpeechVoices.h`)
    int16                                                               m_IsFemale{};
    bool                                                                m_IsPlayingSpeech{};
    bool                                                                m_IsSpeechDisabled{};
    bool                                                                m_IsSpeechForScriptsDisabled{};
    bool                                                                m_IsFrontend{};
    bool                                                                m_IsForcedAudible{};
    CAESound*                                                           m_Sound{};
    int16                                                               m_SoundID{ -1 };
    eSoundBankS16                                                       m_BankID{ SND_BANK_UNK };
    tPedSpeechSlotID                                                    m_PedSpeechSlotID{ -1 };
    float                                                               m_EventVolume{ -100.f };
    eGlobalSpeechContextS16                                             m_LastGCtx{ CTX_GLOBAL_UNK };
    std::array<uint32, CTX_GLOBAL_PAIN_END - CTX_GLOBAL_PAIN_START - 1> m_NextTimeCanSayPain{};

private:
    // 0x4E4F10
    CAEPedSpeechAudioEntity* Constructor() {
        this->CAEPedSpeechAudioEntity::CAEPedSpeechAudioEntity();
        return this;
    }
};

VALIDATE_SIZE(CAEPedSpeechAudioEntity, 0x100);
