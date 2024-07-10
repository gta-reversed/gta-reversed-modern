#include "StdInc.h"

#include "AEPedSpeechAudioEntity.h"
#include "AEAudioUtility.h"
#include "PedClothesDesc.h"
#include <AEAudioHardware.h>
#include <Audio/eSoundBankSlot.h>

void CAEPedSpeechAudioEntity::InjectHooks() {
    RH_ScopedVirtualClass(CAEPedSpeechAudioEntity, 0x85F310, 8);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Constructor, 0x4E4F10);
    RH_ScopedInstall(IsGlobalContextImportantForInterupting, 0x4E4600);
    RH_ScopedInstall(IsGlobalContextUberImportant, 0x4E46F0);
    RH_ScopedInstall(GetNextMoodToUse, 0x4E4700);
    RH_ScopedInstall(GetVoiceForMood, 0x4E4760);
    RH_ScopedInstall(CanWePlayScriptedSpeech, 0x4E4950);
    RH_ScopedInstall(GetSpeechContextVolumeOffset, 0x4E4AE0);
    RH_ScopedInstall(RequestPedConversation, 0x4E50E0);
    RH_ScopedInstall(ReleasePedConversation, 0x4E52A0);
    RH_ScopedInstall(GetCurrentCJMood, 0x4E53B0, { .reversed = false });
    RH_ScopedInstall(StaticInitialise, 0x5B98C0);
    RH_ScopedInstall(GetSpecificSpeechContext, 0x4E4470);
    RH_ScopedInstall(Service, 0x4E3710);
    RH_ScopedInstall(Reset, 0x4E37B0);
    RH_ScopedInstall(ReservePedConversationSpeechSlots, 0x4E37F0, { .reversed = false });
    RH_ScopedInstall(ReservePlayerConversationSpeechSlot, 0x4E3870, { .reversed = false });
    RH_ScopedInstall(RequestPlayerConversation, 0x4E38C0);
    RH_ScopedInstall(ReleasePlayerConversation, 0x4E3960, { .reversed = false });
    RH_ScopedInstall(SetUpConversation, 0x4E3A00, { .reversed = false });
    RH_ScopedInstall(GetAudioPedType, 0x4E3C60);
    RH_ScopedInstall(GetVoice, 0x4E3CD0, { .reversed = false });
    RH_ScopedInstall(DisableAllPedSpeech, 0x4E3EB0);
    RH_ScopedInstall(IsGlobalContextPain, 0x4E44F0);
    RH_ScopedInstall(SetCJMood, 0x4E3ED0, { .reversed = false });
    RH_ScopedInstall(EnableAllPedSpeech, 0x4E3EC0);
    RH_ScopedInstall(IsCJDressedInForGangSpeech, 0x4E4270);
    RH_ScopedInstall(GetSexForSpecialPed, 0x4E4260);
    RH_ScopedInstall(IsGlobalContextImportantForWidescreen, 0x4E46B0);
    RH_ScopedInstall(GetRepeatTime, 0x4E47E0, { .reversed = false });
    RH_ScopedInstall(LoadAndPlaySpeech, 0x4E4840);
    RH_ScopedInstall(GetNumSlotsPlayingContext, 0x4E49B0);
    RH_ScopedInstall(GetNextPlayTime, 0x4E49E0);
    RH_ScopedInstall(SetNextPlayTime, 0x4E4A20);
    RH_ScopedInstall(DisablePedSpeech, 0x4E56D0);
    RH_ScopedInstall(DisablePedSpeechForScriptSpeech, 0x4E5700);
    RH_ScopedInstall(CanPedSayGlobalContext, 0x4E5730, { .reversed = false });
    RH_ScopedInstall(GetVoiceAndTypeFromModel, 0x4E58C0);
    RH_ScopedInstall(GetSoundAndBankIDs, 0x4E5920, { .reversed = false });
    RH_ScopedInstall(CanWePlayGlobalSpeechContext, 0x4E5F10, { .reversed = false });
    RH_ScopedInstall(AddSayEvent, 0x4E6550, { .reversed = false });
    RH_ScopedInstall(Initialise, 0x4E68D0, { .reversed = false });
    RH_ScopedInstall(CanPedHoldConversation, 0x4E69E0, { .reversed = false });
    RH_ScopedInstall(IsGlobalContextImportantForStreaming, 0x4E4510, { .reversed = false });
    RH_ScopedInstall(EnablePedSpeech, 0x4E3F70);
    RH_ScopedInstall(EnablePedSpeechForScriptSpeech, 0x4E3F90);
    RH_ScopedInstall(StopCurrentSpeech, 0x4E3FB0, { .reversed = false });
    RH_ScopedInstall(GetSoundAndBankIDsForScriptedSpeech, 0x4E4400, { .reversed = false });
    RH_ScopedInstall(GetSexFromModel, 0x4E4200, { .reversed = false });
    RH_ScopedInstall(GetPedTalking, 0x4E3F50);
    RH_ScopedInstall(GetVoiceAndTypeForSpecialPed, 0x4E4170, { .reversed = false });
    RH_ScopedVMTInstall(UpdateParameters, 0x4E3520, { .reversed = false });
    RH_ScopedVMTInstall(AddScriptSayEvent, 0x4E4F70, { .reversed = false });
    RH_ScopedVMTInstall(Terminate, 0x4E5670, { .reversed = false });
    RH_ScopedVMTInstall(PlayLoadedSound, 0x4E5CD0, { .reversed = false });
    RH_ScopedVMTInstall(GetAllocatedVoice, 0x4E4120);
    RH_ScopedVMTInstall(WillPedChatAboutTopic, 0x4E5800);
    RH_ScopedVMTInstall(GetPedType, 0x4E4130);
    RH_ScopedVMTInstall(IsPedFemaleForAudio, 0x4E4150);
}

// 0x4E4600
bool __stdcall CAEPedSpeechAudioEntity::IsGlobalContextImportantForInterupting(int16 globalCtx) {
    switch (globalCtx) {
    case 13:
    case 15:
    case 125:
    case 126:
    case 127:
        return true;
    default:
        return false;
    }
}

// 0x4E46F0 - unused
bool CAEPedSpeechAudioEntity::IsGlobalContextUberImportant(int16 globalCtx) {
    return false;
}

// 0x4E4700
int16 __stdcall CAEPedSpeechAudioEntity::GetNextMoodToUse(eCJMood lastMood) {
    switch (lastMood) {
    case MOOD_AG:
    case MOOD_PR: return MOOD_AR;
    case MOOD_PG: return MOOD_AG;
    case MOOD_WG: return MOOD_CG;
    default:      return MOOD_CR;
    }
}

// 0x4E4760
int32 __stdcall CAEPedSpeechAudioEntity::GetVoiceForMood(int16 mood) {
    auto rnd = CAEAudioUtility::GetRandomNumberInRange(0, 1);
    if (mood < 0 || mood >= 10)
        return rnd + 10;
    return rnd + 2 * mood;
}

// 0x4E4950
int16 CAEPedSpeechAudioEntity::CanWePlayScriptedSpeech() {
    for (auto i = 0; i < PED_TYPE_SPC; i++) {
        const auto slot = (s_NextSpeechSlot + i) % PED_TYPE_SPC;
        if (s_PedSpeechSlots[slot].Status == CAEPedSpeechSlot::eStatus::FREE) {
            s_NextSpeechSlot = slot;
            return slot;
        }
    }
    return -1;
}

// 0x4E4AE0
float CAEPedSpeechAudioEntity::GetSpeechContextVolumeOffset(eGlobalSpeechContextS16 gctx) {
    const auto CalculateStrainVolumeOffset = [](float base) {
        const auto t = std::clamp(CStats::GetStatValue(STAT_FAT) - CStats::GetStatValue(STAT_MUSCLE), -1.f, 1.f);
        return (t + 1.f) * 0.5f * base + base;
    };
    switch (gctx) {
    case GCTX_STOMACH_RUMBLE:        return -6.f; // 0x4E4CBB
    case GCTX_BREATHING:             return -12.f; // 0x4E4CC7
    case GCTX_PAIN_CJ_STRAIN:        return CalculateStrainVolumeOffset(-18.f); // 0x4E4B08
    case GCTX_PAIN_CJ_STRAIN_EXHALE: return CalculateStrainVolumeOffset(-21.f); // 0x4E4BE2
    case GCTX_PAIN_CJ_DROWNING:      return 3.f; // 0x4E4CBE
    default:                         return 0.f; // 0x4E4CD0
    }
}

// 0x4E50E0
bool CAEPedSpeechAudioEntity::RequestPedConversation(CPed* pedA, CPed* pedB) {
    if (s_bAllSpeechDisabled || s_bPedConversationHappening || s_bPlayerConversationHappening) {
        return false;
    }
    if (pedA->m_pedSpeech.GetAllocatedVoice() == pedB->m_pedSpeech.GetAllocatedVoice()) {
        return false;
    }
    const auto CheckCanPedTalk = [](CPed* p) {
        return !p->m_pedSpeech.IsAllSpeechDisabled()
            && p->CanPedHoldConversation()
            && !p->GetPedTalking()
            && CVector::DistSqr(TheCamera.GetPosition(), p->GetPosition()) <= sq(40.f);
    };
    if (!CheckCanPedTalk(pedA) || !CheckCanPedTalk(pedB)) {
        return false;
    }
    if (!ReservePedConversationSpeechSlots()) {
        return false;
    }
    s_bPedConversationHappening = true;
    s_pConversationPed1         = pedA;
    s_pConversationPed2         = pedB;
    SetUpConversation();
    return true;
}

// 0x4E52A0
void CAEPedSpeechAudioEntity::ReleasePedConversation() {
    if (!s_bPedConversationHappening) {
        return;
    }
    if (s_pConversationPedSlot1 == -1 || s_pConversationPedSlot2 == -1) {
        return;
    }

    const auto ReleaseConversationFromSlot = [](CPed*& convoPed, auto& slotID) {
        auto& ss = s_PedSpeechSlots[slotID];
        switch (ss.Status) {
        case CAEPedSpeechSlot::eStatus::FREE:
        case CAEPedSpeechSlot::eStatus::RESERVED:
            break;
        default:
            ss.AudioEntity->StopCurrentSpeech();
        }
        ss        = CAEPedSpeechSlot{}; // Reset slot
        slotID   = -1;
        convoPed = nullptr;
    };
    ReleaseConversationFromSlot(s_pConversationPed1, s_pConversationPedSlot1);
    ReleaseConversationFromSlot(s_pConversationPed2, s_pConversationPedSlot2);

    s_bPedConversationHappening = false;
}

// 0x4E53B0
int16 CAEPedSpeechAudioEntity::GetCurrentCJMood() {
    return plugin::CallAndReturn<int16, 0x4E53B0>();
}

// 0x5B98C0
void CAEPedSpeechAudioEntity::StaticInitialise() {
    rng::fill(s_PedSpeechSlots, CAEPedSpeechSlot{});
    rng::fill(s_PhraseMemory, tPhraseMemory{});
    s_NextSpeechSlot = 0;
    Reset();
    s_pConversationPed1 = s_pConversationPed2 = nullptr;
    s_pConversationPedSlot1 = s_pConversationPedSlot2 = 0;
    s_pPlayerConversationPed = nullptr;
    s_bPedConversationHappening = s_bPlayerConversationHappening = false;
    rng::fill(s_Conversation, -1);
    s_nCJBasicMood = s_nCJGangBanging = s_nCJFat = s_nCJWellDressed = -1;
    s_NextSpeechSlot = s_nCJMoodOverrideTime = 0;
    s_bAllSpeechDisabled = s_bAPlayerSpeaking = s_bForceAudible = 0;
}

// 0x4E4470
int16 CAEPedSpeechAudioEntity::GetSpecificSpeechContext(eGlobalSpeechContext gCtx, eAudioPedType pedAudioType) {
    assert(gCtx > GCTX_UNK);             // notsa
    assert(gCtx < GCTX_NUM);             // OG: return -1; (silent error)
    assert(pedAudioType < PED_TYPE_NUM); // OG: return -1; (silent error)

    for (int32 i = 0; ; i++) { // NOTE/BUG: No `i` check at all? (Eg.: i < gSpeechContextLookup.size()?)
        const auto& contexts = gSpeechContextLookup[i];
        if (contexts[0] == GCTX_UNK) {
            break;
        } else if (contexts[0] == gCtx) {
            return contexts[pedAudioType + 1];
        }
    }
    return -1;
}

// 0x4E3710
void CAEPedSpeechAudioEntity::Service() {
    s_bForceAudible = false;
    for (auto&& [i, ss] : notsa::enumerate(s_PedSpeechSlots)) {
        // Waiting for sound to load, and has loaded?
        if (ss.Status == CAEPedSpeechSlot::eStatus::LOADING && AEAudioHardware.IsSoundLoaded(ss.SoundBankID, ss.SoundID, SND_BANK_SLOT_SPEECH1 + i)) {
            ss.Status = CAEPedSpeechSlot::eStatus::WAITING;
        }

        // Sound is now loaded, waiting to be played
        if (ss.Status == CAEPedSpeechSlot::eStatus::WAITING) {
            if (ss.StartPlaybackTime >= CTimer::GetTimeInMS()) {
                if (const auto ae = ss.AudioEntity) {
                    ae->PlayLoadedSound();
                } else {
                    ss.Status = CAEPedSpeechSlot::eStatus::FREE;
                }
            }
        }

        // `PlayLoadedSound` above might've modified the status, must check it again (can't use switch for whole code)
        switch (ss.Status) {
        case CAEPedSpeechSlot::eStatus::REQUESTED:
        case CAEPedSpeechSlot::eStatus::PLAYING: {
            s_bForceAudible |= ss.ForceAudible;
        }
        }
    }
}

// 0x4E37B0
void CAEPedSpeechAudioEntity::Reset() {
    for (auto& time : gGlobalSpeechContextNextPlayTime) {
        time = CTimer::GetTimeInMS() + CAEAudioUtility::GetRandomNumberInRange(3000, 7000);
    }
    s_nCJMoodOverrideTime = 0;
}

// 0x4E37F0
int8 CAEPedSpeechAudioEntity::ReservePedConversationSpeechSlots() {
    return plugin::CallAndReturn<int8, 0x4E37F0>();
}

// 0x4E3870
int8 CAEPedSpeechAudioEntity::ReservePlayerConversationSpeechSlot() {
    return plugin::CallAndReturn<int8, 0x4E3870>();
}

// 0x4E38C0
bool CAEPedSpeechAudioEntity::RequestPlayerConversation(CPed* ped) {
    if (s_bAllSpeechDisabled)
        return false;

    if (ped->m_pedSpeech.m_IsSpeechForScriptsDisabled || ped->m_pedSpeech.m_IsSpeechDisabled) {
        return false;
    }

    const auto player = FindPlayerPed();
    if (!player || player->m_pedSpeech.m_IsSpeechDisabled || player->m_pedSpeech.m_IsSpeechForScriptsDisabled) {
        return false;
    }

    if (   s_bPedConversationHappening
        || s_bPlayerConversationHappening
        || ped->GetPedTalking()
        || !CAEPedSpeechAudioEntity::ReservePlayerConversationSpeechSlot()
    ) {
        return false;
    }

    s_pPlayerConversationPed = ped;
    s_bPlayerConversationHappening = true;
    return true;
}

// 0x4E3960
void CAEPedSpeechAudioEntity::ReleasePlayerConversation() {
    plugin::Call<0x4E3960>();
}

// 0x4E3A00
void CAEPedSpeechAudioEntity::SetUpConversation() {
    plugin::Call<0x4E3A00>();
}

// 0x4E3C60
int16 CAEPedSpeechAudioEntity::GetAudioPedType(Const char* name) {
    static constexpr const char* aAudioPedTypeNames[] = { // 0x8C8108
        "PED_TYPE_GEN",
        "PED_TYPE_EMG",
        "PED_TYPE_PLAYER",
        "PED_TYPE_GANG",
        "PED_TYPE_GFD",
        "PED_TYPE_SPC"
    };

    for (int16 index = 0; const auto& pedName : aAudioPedTypeNames) {
        if (!strcmp(name, pedName)) {
            return index;
        }
        index++;
    }
    return -1;
}

// 0x4E3CD0
int32 CAEPedSpeechAudioEntity::GetVoice(char* name, int16 type) {
    return plugin::CallAndReturn<int32, 0x4E3CD0, char*, int16>(name, type);
}

// 0x4E3EB0
void CAEPedSpeechAudioEntity::DisableAllPedSpeech() {
    s_bAllSpeechDisabled = true;
}

// 0x4E44F0
bool CAEPedSpeechAudioEntity::IsGlobalContextPain(int16 globalCtx) {
    return GCTX_PAIN_START < globalCtx && globalCtx < GCTX_PAIN_END;
}

// 0x4E3ED0
void CAEPedSpeechAudioEntity::SetCJMood(int16 a1, uint32 a2, int16 a3, int16 a4, int16 a5) {
    plugin::Call<0x4E3ED0, int16, uint32, int16, int16, int16>(a1, a2, a3, a4, a5);
}

// 0x4E3EC0
void CAEPedSpeechAudioEntity::EnableAllPedSpeech() {
    s_bAllSpeechDisabled = false;
}

// 0x4E4270
bool CAEPedSpeechAudioEntity::IsCJDressedInForGangSpeech() {
    static constexpr struct {
        eClothesTexturePart ClothesPart;
        const char*         TexName;
    } GANG_SPEECH_CLOTHES[] = {
        { CLOTHES_TEXTURE_TORSO,   "hoodyagreen" },
        { CLOTHES_TEXTURE_TORSO,   "shirtbgang"  },
        { CLOTHES_TEXTURE_LEGS,    "tracktrgang" },
        { CLOTHES_TEXTURE_LEGS,    "denimsgang"  },
        { CLOTHES_TEXTURE_HATS,    "bandgang"    },
        { CLOTHES_TEXTURE_HATS,    "hockey"      },
        { CLOTHES_TEXTURE_HATS,    "capgang"     },
        { CLOTHES_TEXTURE_HATS,    "capgangback" },
        { CLOTHES_TEXTURE_HATS,    "capgangside" },
        { CLOTHES_TEXTURE_HATS,    "capgangover" },
        { CLOTHES_TEXTURE_HATS,    "capgangup"   },
        { CLOTHES_TEXTURE_GLASSES, "bandred3"    },
        { CLOTHES_TEXTURE_GLASSES, "bandblue3"   },
        { CLOTHES_TEXTURE_GLASSES, "bandgang3"   },
        { CLOTHES_TEXTURE_GLASSES, "bandblack3"  },
    };

    if (!FindPlayerPed(PED_TYPE_PLAYER1)) {
        return false;
    }

    if (CGameLogic::FindCityClosestToPoint(FindPlayerCoors()) != LEVEL_NAME_LOS_SANTOS) {
        return false;
    }

    return rng::any_of(GANG_SPEECH_CLOTHES, [pcd = FindPlayerPed()->GetClothesDesc()](auto& gc) {
        return pcd->m_anTextureKeys[gc.ClothesPart] == CKeyGen::GetUppercaseKey(gc.TexName);
    });
}

// 0x4E4260
int8 CAEPedSpeechAudioEntity::GetSexForSpecialPed(uint32 a1) {
    return 1;
}

// Methods
// 0x4E46B0
bool CAEPedSpeechAudioEntity::IsGlobalContextImportantForWidescreen(int16 globalCtx) {
    return notsa::contains<int>({4, 2}, m_PedAudioType) || notsa::contains<int>({13, 15, 116}, globalCtx);
}

// 0x4E47E0
int32 CAEPedSpeechAudioEntity::GetRepeatTime(int16 a1) {
    return plugin::CallMethodAndReturn<int32, 0x4E47E0, CAEPedSpeechAudioEntity*, int16>(this, a1);
}

// 0x4E4840
void CAEPedSpeechAudioEntity::LoadAndPlaySpeech(uint32 offset) {
    auto& s = GetSpeech();
    switch (s.Status) {
    case CAEPedSpeechSlot::eStatus::FREE:
    case CAEPedSpeechSlot::eStatus::RESERVED:
        break;
    default:
        return;
    }

    AEAudioHardware.LoadSound(m_BankID, m_SoundID, SND_BANK_SLOT_SPEECH1 + m_PedSpeechSlotID); // TODO: Helper
    s.Status            = CAEPedSpeechSlot::eStatus::LOADING;
    s.SoundBankID       = m_BankID;
    s.SoundID           = m_SoundID;
    s.AudioEntity       = this;
    s.StartPlaybackTime = CTimer::GetTimeInMS() + offset;
    s.PedAudioType      = m_PedAudioType;
    s.GCtx              = m_LastGCtx;
    s.ForceAudible      = m_IsForcedAudible;
}

// 0x4E49B0
int32 CAEPedSpeechAudioEntity::GetNumSlotsPlayingContext(int16 context) {
    return rng::count_if(s_PedSpeechSlots, [&](CAEPedSpeechSlot& speech) {
        return speech.Status != CAEPedSpeechSlot::eStatus::FREE && speech.GCtx == context;
    });
}

// 0x4E49E0
uint32 CAEPedSpeechAudioEntity::GetNextPlayTime(int16 globalCtx) {
    if (globalCtx >= GCTX_NUM) {
        return 0;
    }
    return IsGlobalContextPain(globalCtx)
        ? m_NextTimeCanSayPain[globalCtx - GCTX_PAIN_START + 1]
        : gGlobalSpeechContextNextPlayTime[globalCtx];
}

// 0x4E4A20
void CAEPedSpeechAudioEntity::SetNextPlayTime(int16 globalCtx) {
    // plugin::CallMethod<0x4E4A20>(this, globalCtx);

    if (globalCtx >= GCTX_NUM)
        return;

    for (auto& lookup : gSpeechContextLookup) {
        if (lookup[0] == -1)
            break;

        if (lookup[0] != globalCtx)
            continue;

        const auto playTime = lookup[6] + CAEAudioUtility::GetRandomNumberInRange(1, 1000);
        auto& ctxNextPlayTime = [&]() -> uint32& {
            if (IsGlobalContextPain(globalCtx))
                return m_NextTimeCanSayPain[globalCtx - 340];
            else
                return gGlobalSpeechContextNextPlayTime[globalCtx];
        }() = CTimer::GetTimeInMS() + playTime;
        return;
    }
}

// 0x4E56D0
void CAEPedSpeechAudioEntity::DisablePedSpeech(int16 a1) {
    if (m_IsInitialized) {
        m_IsSpeechDisabled = true;
        if (a1)
            StopCurrentSpeech();
    }
}

// 0x4E5700
void CAEPedSpeechAudioEntity::DisablePedSpeechForScriptSpeech(int16 a1) {
    if (m_IsInitialized) {
        m_IsSpeechForScriptsDisabled = true;
        if (a1)
            StopCurrentSpeech();
    }
}

// 0x4E5730
int8 CAEPedSpeechAudioEntity::CanPedSayGlobalContext(int16 a2) {
    return plugin::CallMethodAndReturn<int8, 0x4E5730>(this, a2);
}

// 0x4E58C0
int8 CAEPedSpeechAudioEntity::GetVoiceAndTypeFromModel(eModelID modelId) {
    auto* const mi = CModelInfo::GetModelInfo(modelId)->AsPedModelInfoPtr();
    if (mi->m_nPedAudioType < 0 || mi->m_nPedAudioType >= 6) {
        return 0;
    }

    if (mi->m_nPedAudioType == PED_TYPE_SPC) {
        return GetVoiceAndTypeForSpecialPed(mi->m_nKey);
    }

    m_VoiceID = mi->m_nVoiceId;
    if (m_VoiceID == PED_TYPE_UNK) {
        return 0;
    }

    mi->IncrementVoice();

    return 1;
}

// 0x4E5920
int16 CAEPedSpeechAudioEntity::GetSoundAndBankIDs(int16 phraseId, int16* a3) {
    return plugin::CallMethodAndReturn<int16, 0x4E5920, CAEPedSpeechAudioEntity*, int16, int16*>(this, phraseId, a3);
}

// 0x4E5F10
bool CAEPedSpeechAudioEntity::CanWePlayGlobalSpeechContext(int16 a2) {
    return plugin::CallMethodAndReturn<bool, 0x4E5F10, CAEPedSpeechAudioEntity*, int16>(this, a2);
}

// 0x4E6550
int16 CAEPedSpeechAudioEntity::AddSayEvent(eAudioEvents audioEvent, int16 phraseId, uint32 a4, float a5, uint8 a6, uint8 a7, uint8 a8) {
    return plugin::CallMethodAndReturn<int16, 0x4E6550, CAEPedSpeechAudioEntity*, int32, int16, uint32, float, uint8, uint8>(this, audioEvent, phraseId, a4, a5, a6, a7, a8);
}

// 0x4E68D0
void CAEPedSpeechAudioEntity::Initialise(CEntity* ped) {
    plugin::CallMethod<0x4E68D0, CAEPedSpeechAudioEntity*, CEntity*>(this, ped);
}

// 0x4E69E0
bool CAEPedSpeechAudioEntity::CanPedHoldConversation() {
    return plugin::CallMethodAndReturn<bool, 0x4E69E0, CAEPedSpeechAudioEntity*>(this);
}

// 0x4E4510
bool CAEPedSpeechAudioEntity::IsGlobalContextImportantForStreaming(int16 a1) {
    return plugin::CallMethodAndReturn<bool, 0x4E4510, CAEPedSpeechAudioEntity*, int16>(this, a1);
}

// 0x4E3F70
void CAEPedSpeechAudioEntity::EnablePedSpeech() {
    if (m_IsInitialized)
        m_IsSpeechDisabled = false;
}

// 0x4E3F90
void CAEPedSpeechAudioEntity::EnablePedSpeechForScriptSpeech() {
    if (m_IsInitialized)
        m_IsSpeechForScriptsDisabled = false;
}

// 0x4E3FB0
void CAEPedSpeechAudioEntity::StopCurrentSpeech() {
    plugin::CallMethod<0x4E3FB0, CAEPedSpeechAudioEntity*>(this);
}

// 0x4E4400
int8 CAEPedSpeechAudioEntity::GetSoundAndBankIDsForScriptedSpeech(int32 a2) {
    return plugin::CallMethodAndReturn<int8, 0x4E4400, CAEPedSpeechAudioEntity*, int32>(this, a2);
}

// 0x4E4200
int8 CAEPedSpeechAudioEntity::GetSexFromModel(int32 a1) {
    return plugin::CallMethodAndReturn<int8, 0x4E4200, CAEPedSpeechAudioEntity*, int32>(this, a1);
}

// 0x4E3F50
bool CAEPedSpeechAudioEntity::GetPedTalking() {
    return m_IsInitialized && m_IsPlayingSpeech;
}

// 0x4E4170
int8 CAEPedSpeechAudioEntity::GetVoiceAndTypeForSpecialPed(uint32 modelNameHash) {
    return plugin::CallMethodAndReturn<int8, 0x4E4170, CAEPedSpeechAudioEntity*, uint32>(this, modelNameHash);
}

// 0x4E3520
void CAEPedSpeechAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    plugin::CallMethod<0x4E3520, CAEPedSpeechAudioEntity*, CAESound*, int16>(this, sound, curPlayPos);
}

// 0x4E4F70
void CAEPedSpeechAudioEntity::AddScriptSayEvent(int32 a1, int32 a2, uint8 a3, uint8 a4, uint8 a5) {
    plugin::CallMethod<0x4E4F70, CAEPedSpeechAudioEntity*, int32, int32, uint8, uint8, uint8>(this, a1, a2, a3, a4, a5);
}

// 0x4E5670
void CAEPedSpeechAudioEntity::Terminate() {
    plugin::CallMethod<0x4E5670, CAEPedSpeechAudioEntity*>(this);
}

// 0x4E5CD0
void CAEPedSpeechAudioEntity::PlayLoadedSound() {
    plugin::CallMethod<0x4E5CD0, CAEPedSpeechAudioEntity*>(this);
}

// 0x4E4120
int16 CAEPedSpeechAudioEntity::GetAllocatedVoice() {
    return m_VoiceID;
}

// 0x4E5800
bool CAEPedSpeechAudioEntity::WillPedChatAboutTopic(int16 topic) {
    switch (topic) {
    case 0:  return CanPedSayGlobalContext(48);
    case 1:  return CanPedSayGlobalContext(49);
    case 2:  return CanPedSayGlobalContext(50);
    case 3:  return CanPedSayGlobalContext(51);
    case 4:  return CanPedSayGlobalContext(52);
    case 5:  return CanPedSayGlobalContext(53);
    case 6:  return CanPedSayGlobalContext(54);
    case 7:  return CanPedSayGlobalContext(55);
    case 8:
    case 9:  return true;
    default: return false;
    }
}

// 0x4E4130
int16 CAEPedSpeechAudioEntity::GetPedType() {
    if (m_IsInitialized)
        return m_PedAudioType;
    else
        return -1;
}

// 0x4E4150
bool CAEPedSpeechAudioEntity::IsPedFemaleForAudio() {
    if (m_IsInitialized)
        return m_IsFemale;
    else
        return false;
}

// 0x4E4F10
CAEPedSpeechAudioEntity* CAEPedSpeechAudioEntity::Constructor() {
    this->CAEPedSpeechAudioEntity::CAEPedSpeechAudioEntity();
    return this;
}

// 0x4E3520// 0x4E4F70// 0x4E5670// 0x4E5CD0// 0x4E4120// 0x4E5800// 0x4E4130// 0x4E4150
