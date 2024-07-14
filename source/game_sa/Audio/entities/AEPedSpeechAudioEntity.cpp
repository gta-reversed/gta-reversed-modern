#include "StdInc.h"
#include <bitset>
#include "AEPedSpeechAudioEntity.h"
#include "AEAudioUtility.h"
#include "PedClothesDesc.h"
#include <AEAudioHardware.h>
#include <Audio/eSoundBankSlot.h>
#include <Tasks/TaskTypes/TaskComplexFacial.h>

#include "./PedSpeechAudioEntityLUTs.inc.h"

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
    RH_ScopedInstall(GetCurrentCJMood, 0x4E53B0);
    RH_ScopedInstall(StaticInitialise, 0x5B98C0);
    RH_ScopedInstall(GetSpecificSpeechContext, 0x4E4470);
    RH_ScopedInstall(Service, 0x4E3710);
    RH_ScopedInstall(Reset, 0x4E37B0);
    RH_ScopedInstall(ReservePedConversationSpeechSlots, 0x4E37F0);
    RH_ScopedInstall(ReservePlayerConversationSpeechSlot, 0x4E3870);
    RH_ScopedInstall(RequestPlayerConversation, 0x4E38C0);
    RH_ScopedInstall(ReleasePlayerConversation, 0x4E3960);
    RH_ScopedInstall(SetUpConversation, 0x4E3A00);
    RH_ScopedInstall(GetAudioPedType, 0x4E3C60);
    RH_ScopedInstall(GetVoice, 0x4E3CD0);
    RH_ScopedInstall(DisableAllPedSpeech, 0x4E3EB0);
    RH_ScopedInstall(IsGlobalContextPain, 0x4E44F0);
    RH_ScopedInstall(SetCJMood, 0x4E3ED0);
    RH_ScopedInstall(EnableAllPedSpeech, 0x4E3EC0);
    RH_ScopedInstall(IsCJDressedInForGangSpeech, 0x4E4270);
    RH_ScopedInstall(GetSexForSpecialPed, 0x4E4260);
    RH_ScopedInstall(IsGlobalContextImportantForWidescreen, 0x4E46B0);
    RH_ScopedInstall(GetRepeatTime, 0x4E47E0);
    RH_ScopedInstall(LoadAndPlaySpeech, 0x4E4840);
    RH_ScopedInstall(GetNumSlotsPlayingContext, 0x4E49B0);
    RH_ScopedInstall(GetNextPlayTime, 0x4E49E0);
    RH_ScopedInstall(SetNextPlayTime, 0x4E4A20);
    RH_ScopedInstall(DisablePedSpeech, 0x4E56D0);
    RH_ScopedInstall(DisablePedSpeechForScriptSpeech, 0x4E5700);
    RH_ScopedInstall(CanPedSayGlobalContext, 0x4E5730);
    RH_ScopedInstall(GetVoiceAndTypeFromModel, 0x4E58C0);
    RH_ScopedInstall(GetSoundAndBankIDs, 0x4E5920);
    RH_ScopedInstall(CanWePlayGlobalSpeechContext, 0x4E5F10);
    RH_ScopedInstall(AddSayEvent, 0x4E6550);
    RH_ScopedInstall(Initialise, 0x4E68D0);
    RH_ScopedInstall(CanPedHoldConversation, 0x4E69E0);
    RH_ScopedInstall(IsGlobalContextImportantForStreaming, 0x4E4510);
    RH_ScopedInstall(EnablePedSpeech, 0x4E3F70);
    RH_ScopedInstall(EnablePedSpeechForScriptSpeech, 0x4E3F90);
    RH_ScopedInstall(StopCurrentSpeech, 0x4E3FB0);
    RH_ScopedInstall(GetSoundAndBankIDsForScriptedSpeech, 0x4E4400);
    RH_ScopedInstall(GetSexFromModel, 0x4E4200);
    RH_ScopedInstall(GetPedTalking, 0x4E3F50);
    RH_ScopedInstall(GetVoiceAndTypeForSpecialPed, 0x4E4170);
    RH_ScopedVMTInstall(UpdateParameters, 0x4E3520);
    RH_ScopedVMTInstall(AddScriptSayEvent, 0x4E4F70);
    RH_ScopedVMTInstall(Terminate, 0x4E5670, { .reversed = false });
    RH_ScopedVMTInstall(PlayLoadedSound, 0x4E5CD0, { .reversed = false });
    RH_ScopedVMTInstall(GetAllocatedVoice, 0x4E4120);
    RH_ScopedVMTInstall(WillPedChatAboutTopic, 0x4E5800);
    RH_ScopedVMTInstall(GetPedType, 0x4E4130);
    RH_ScopedVMTInstall(IsPedFemaleForAudio, 0x4E4150);
}

CAEPedSpeechAudioEntity::CAEPedSpeechAudioEntity() noexcept {
    m_NextTimeCanSayPain.fill(0);
}

CAEPedSpeechAudioEntity::CAEPedSpeechAudioEntity(CPed* ped) noexcept :
    CAEPedSpeechAudioEntity{}
{
    m_pEntity = ped;
    if (ped->GetModelID() != MODEL_INVALID) {
        auto* const mi = ped->GetPedModelInfo();
        if (mi->m_nPedAudioType == PED_TYPE_SPC) {
            if (!GetVoiceAndTypeForSpecialPed(mi->m_nKey)) {
                return;
            }
        } else {
            m_VoiceID = mi->m_nVoiceId;
            if (m_VoiceID == -1) {
                return;
            }
            mi->IncrementVoice();
        }
        VERIFY(GetSexFromModel(ped->GetModelID()));
        m_IsInitialized = true;
    }
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
    return GetFreeSpeechSlot();
}

// 0x4E4AE0
float CAEPedSpeechAudioEntity::GetSpeechContextVolumeOffset(eGlobalSpeechContextS16 gctx) {
    const auto CalculateStrainVolumeOffset = [](float base) {
        const auto t = std::clamp(CStats::GetStatValue(STAT_FAT) - CStats::GetStatValue(STAT_MUSCLE), -1.f, 1.f);
        return (t + 1.f) * 0.5f * base + base;
    };
    switch (gctx) {
    case CTX_GLOBAL_STOMACH_RUMBLE:        return -6.f; // 0x4E4CBB
    case CTX_GLOBAL_BREATHING:             return -12.f; // 0x4E4CC7
    case CTX_GLOBAL_PAIN_CJ_STRAIN:        return CalculateStrainVolumeOffset(-18.f); // 0x4E4B08
    case CTX_GLOBAL_PAIN_CJ_STRAIN_EXHALE: return CalculateStrainVolumeOffset(-21.f); // 0x4E4BE2
    case CTX_GLOBAL_PAIN_CJ_DROWNING:      return 3.f; // 0x4E4CBE
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
        ss       = {}; // Reset slot
        slotID   = -1;
        convoPed = nullptr;
    };
    ReleaseConversationFromSlot(s_pConversationPed1, s_pConversationPedSlot1);
    ReleaseConversationFromSlot(s_pConversationPed2, s_pConversationPedSlot2);

    s_bPedConversationHappening = false;
}

// 0x4E53B0
int16 CAEPedSpeechAudioEntity::GetCurrentCJMood() {
    const auto* const plyr = FindPlayerPed();
    if (!plyr) {
        return MOOD_CR;
    }

    const auto isMoodOverrideActive = s_nCJMoodOverrideTime >= CTimer::GetTimeInMS();
    
    const auto CheckCJIsWellDressed = [&] { // 0x4E53DF
        if (isMoodOverrideActive && s_nCJWellDressed != -1) {
            return s_nCJWellDressed != 0;
        }
        return CStats::GetStatValue(STAT_CLOTHES_RESPECT) >= 650.f
            && CStats::GetStatValue(STAT_FASHION_BUDGET) >= 10'000.f;
    };

    const auto CheckCJIsGangBanging = [&] { // 0x4E5440
        if (isMoodOverrideActive && s_nCJGangBanging != -1) {
            return s_nCJGangBanging != 0;
        }
        if (IsCJDressedInForGangSpeech()) {
            return true;
        }
        auto& plyrGrp = plyr->GetPlayerGroup();
        if (plyrGrp.GetMembership().CountMembersExcludingLeader() <= 1) {
            return true;
        }
        const auto& mem = plyrGrp.GetMembership().GetMembers().front(); // The one-and-only member (This isnt the same as `GetMember(0)`!!!)
        if (mem.m_nPedType == PED_TYPE_GANG2) {
            return true;
        }
        auto& memSpeech = mem.m_pedSpeech;
        return memSpeech.m_PedAudioType == PED_TYPE_GANG
            && notsa::contains({ VOICE_GNG_RYDER, VOICE_GNG_SWEET, VOICE_GNG_SMOKE }, (eGngSpeechVoices)memSpeech.m_VoiceID);
    };

    const auto CheckCJIsFat = [&] { // 0x4E54E0
        if (isMoodOverrideActive && s_nCJFat != -1) {
            return s_nCJFat != 0;
        }
        return CStats::GetStatValue(STAT_FAT) >= 600.f
            && CStats::GetStatValue(STAT_FAT) - 200.f > CStats::GetStatValue(STAT_MUSCLE);
    };

    const auto DeriveMood = [&](eCJMood basicMood) { // 0x4E55CC
        if (isMoodOverrideActive && s_nCJBasicMood != MOOD_UNK) { // 0x4E5592
            basicMood = s_nCJBasicMood;
        }
        switch (basicMood) {
        case MOOD_AR:
            return CheckCJIsFat()
                ? MOOD_AR
                : MOOD_AG;
        case MOOD_CR: {
            if (CheckCJIsGangBanging()) {
                return MOOD_CG;
            }
            if (CheckCJIsFat()) {
                return MOOD_CF;
            }
            return CheckCJIsWellDressed()
                ? MOOD_CD
                : MOOD_CR;
        }
        case MOOD_PR:
            return CheckCJIsGangBanging()
                ? MOOD_PG
                : MOOD_PR;
        case MOOD_WR:
            return CheckCJIsGangBanging()
                ? MOOD_WG
                : MOOD_WR;
        default:
            return MOOD_CR;
        }
    };

    if (FindPlayerWanted()->GetWantedLevel() > 3) { // 0x4E5537
        return DeriveMood(MOOD_PR);
    }

    if (FindPlayerWanted()->GetWantedLevel() > 1) { // 0x4E554B
        return DeriveMood(MOOD_AR);
    }

    if (CTheScripts::LastMissionPassedTime == -1) { // 0x4E555C
        if (CTimer::GetTimeInMS() >= CTheScripts::LastMissionPassedTime) {
            return CTimer::GetTimeInMS() < CTheScripts::LastMissionPassedTime + 180'000
                ? DeriveMood(MOOD_WR)
                : DeriveMood(MOOD_CR);
        } else {
            CTheScripts::LastMissionPassedTime = CTimer::GetTimeInMS();
        }
    }

    return DeriveMood(MOOD_CR); // 0x4E5579
}

// 0x5B98C0
void CAEPedSpeechAudioEntity::StaticInitialise() {
    rng::fill(s_PedSpeechSlots, CAEPedSpeechSlot{});
    rng::fill(s_PhraseMemory, tPhraseMemory{});

    Reset();

    s_pConversationPed1            = nullptr;
    s_pConversationPed2            = nullptr;
    s_pConversationPedSlot1        = 0;
    s_pConversationPedSlot2        = 0;
    s_pPlayerConversationPed       = nullptr;
    s_bPedConversationHappening    = false;
    s_bPlayerConversationHappening = false;
    rng::fill(s_Conversation, CTX_GLOBAL_UNK);

    s_nCJBasicMood        = MOOD_UNK;
    s_nCJGangBanging      = -1;
    s_nCJFat              = -1;
    s_nCJWellDressed      = -1;
    s_nCJMoodOverrideTime = 0;

    s_NextSpeechSlot     = 0;
    s_bAllSpeechDisabled = false;
    s_bAPlayerSpeaking   = false;
    s_bForceAudible      = false;
}

// 0x4E4470
eSpecificSpeechContext CAEPedSpeechAudioEntity::GetSpecificSpeechContext(eGlobalSpeechContext gCtx, eAudioPedType pedAudioType) {
    // Omitted useless `if`s
    // NOTE: Original code allowed `PED_TYPE_SPC` as a valid ped type too... but that (technically) caused an out-of-bounds read...
    //       We won't assert on that, because there are bounds check for the array (as we use std::array)
    if (const auto* const ctxi = GetGlobalSpeechContextInfo(gCtx)) {
        return ctxi->SpecificSpeechContext[pedAudioType];
    }
    return -1;
}

// 0x4E3710
void CAEPedSpeechAudioEntity::Service() { // static
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
bool CAEPedSpeechAudioEntity::ReservePedConversationSpeechSlots() {
    const auto slotA = GetFreeSpeechSlot();
    const auto slotB = GetFreeSpeechSlot();

    if (slotA == -1 || slotB == -1) {
        return false;
    }

    const auto SetupSlot = [](int32 slot) {
        auto* const ss                   = &s_PedSpeechSlots[slot];
        ss->IsReservedForPedConversation = true;
        ss->Status                       = CAEPedSpeechSlot::eStatus::RESERVED;
    };
    SetupSlot(s_pConversationPedSlot1 = slotA);
    SetupSlot(s_pConversationPedSlot2 = slotB);

    return true;
}

// 0x4E3870
bool CAEPedSpeechAudioEntity::ReservePlayerConversationSpeechSlot() {
    const auto slot = GetFreeSpeechSlot();
    if (slot == -1) {
        return false;
    }
    auto* const ss                      = &s_PedSpeechSlots[slot];
    ss->Status                          = CAEPedSpeechSlot::eStatus::RESERVED;
    ss->IsReservedForPlayerConversation = true;
    s_pConversationPedSlot1             = slot;
    return true;
}

// 0x4E38C0
bool CAEPedSpeechAudioEntity::RequestPlayerConversation(CPed* ped) {
    if (s_bAllSpeechDisabled) {
        return false;
    }

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
        || !ReservePlayerConversationSpeechSlot()
    ) {
        return false;
    }

    s_pPlayerConversationPed       = ped;
    s_bPlayerConversationHappening = true;

    return true;
}

// 0x4E3960
void CAEPedSpeechAudioEntity::ReleasePlayerConversation() {
    if (!s_bPlayerConversationHappening) {
        return;
    }
    s_bPlayerConversationHappening = false;
    if (s_pConversationPedSlot1 < 0) {
        return;
    }
    auto* const ss = &s_PedSpeechSlots[s_pConversationPedSlot1];
    switch (ss->Status) {
    case CAEPedSpeechSlot::eStatus::FREE:
    case CAEPedSpeechSlot::eStatus::RESERVED: {
        *ss = {};
    }
    }
    s_PedSpeechSlots[s_pConversationPedSlot1] = {};
    s_pConversationPedSlot1                   = -1;
    s_pPlayerConversationPed                  = nullptr;
}

// 0x4E3A00
void CAEPedSpeechAudioEntity::SetUpConversation() {
    rng::fill(s_Conversation, CTX_GLOBAL_NO_SPEECH);

    auto PushConvo = [i = 0](eGlobalSpeechContext gctx) mutable {
        s_Conversation[i++] = gctx;
    };

    const auto PushConvoForPeds = [&](eGlobalSpeechContext ifFemale, eGlobalSpeechContext ifMale) {
        const auto PushConvoForPed = [&](const CPed* p) {
            switch (p->m_nPedType) {
            case PED_TYPE_PROSTITUTE:
            case PED_TYPE_CIVFEMALE: PushConvo(ifFemale); break;
            default:                 PushConvo(ifMale);   break;
            }
        };
        PushConvoForPed(s_pConversationPed2); // yes, ped 2, then ped 1
        PushConvoForPed(s_pConversationPed1);
    };

    // Greeting
    PushConvoForPeds(CTX_GLOBAL_PCONV_GREET_FEM, CTX_GLOBAL_PCONV_GREET_MALE);

    // Other stuff
    const auto r = CAEAudioUtility::GetRandomNumberInRange(1, 10);
    if (r <= 8) { // Combined cases 1, -> 4 + 5, -> 8
        const auto hasInitialState = r <= 4;

        s_ConversationLength = hasInitialState ? 3 : 2;

        if (hasInitialState) { // For cases 1 -> 4 only
            const auto isGood = CGeneral::DoCoinFlip();
            PushConvo(isGood ?  CTX_GLOBAL_PCONV_STATE_GOOD :  CTX_GLOBAL_PCONV_STATE_BAD);
            PushConvo(isGood ?  CTX_GLOBAL_PCONV_AGREE_GOOD :  CTX_GLOBAL_PCONV_AGREE_BAD);
        }

        // A question
        PushConvo(CTX_GLOBAL_PCONV_QUESTION);

        // Whenever they agree with the answer (?)
        switch (CAEAudioUtility::GetRandomNumberInRange(0, 2)) {
        case 0: PushConvo(CTX_GLOBAL_PCONV_AGREE_GOOD); break;
        case 1: PushConvo(CTX_GLOBAL_PCONV_AGREE_BAD);  break;
        case 2: PushConvo(CTX_GLOBAL_PCONV_ANS_NO);     break;
        }

        // Part away (?)
        PushConvoForPeds(CTX_GLOBAL_PCONV_PART_FEM, CTX_GLOBAL_PCONV_PART_MALE);
    } else if (r <= 10) { // cases 9, 10
        s_ConversationLength = 1;

        PushConvo(CGeneral::DoCoinFlip() ?  CTX_GLOBAL_PCONV_STATE_GOOD :  CTX_GLOBAL_PCONV_STATE_BAD);
        PushConvo(CTX_GLOBAL_PCONV_DISMISS);
    } else {
        NOTSA_UNREACHABLE();
    }
}

// 0x4E3C60
eAudioPedType CAEPedSpeechAudioEntity::GetAudioPedType(const char* name) {
    static const auto mapping = notsa::make_mapping<std::string_view, eAudioPedType>({
        {"PED_TYPE_GEN",    PED_TYPE_GEN   },
        {"PED_TYPE_EMG",    PED_TYPE_EMG   },
        {"PED_TYPE_PLAYER", PED_TYPE_PLAYER},
        {"PED_TYPE_GANG",   PED_TYPE_GANG  },
        {"PED_TYPE_GFD",    PED_TYPE_GFD   },
        {"PED_TYPE_SPC",    PED_TYPE_SPC   },
    });
    return notsa::find_value_or(mapping, name, PED_TYPE_UNK);
}

// 0x4E3CD0
ePedSpeechVoiceS16 CAEPedSpeechAudioEntity::GetVoice(const char* name, eAudioPedTypeS16 type) {
    switch (type) {
    case PED_TYPE_GEN: {
        static const auto mapping = notsa::make_mapping<std::string_view, eGenSpeechVoices>({
            {"VOICE_GEN_BBDYG1", VOICE_GEN_BBDYG1}, {"VOICE_GEN_BBDYG2", VOICE_GEN_BBDYG2}, {"VOICE_GEN_BFORI", VOICE_GEN_BFORI}, {"VOICE_GEN_BFOST", VOICE_GEN_BFOST}, {"VOICE_GEN_BFYBE", VOICE_GEN_BFYBE}, {"VOICE_GEN_BFYBU", VOICE_GEN_BFYBU}, {"VOICE_GEN_BFYCRP", VOICE_GEN_BFYCRP}, {"VOICE_GEN_BFYPRO", VOICE_GEN_BFYPRO}, {"VOICE_GEN_BFYRI", VOICE_GEN_BFYRI}, {"VOICE_GEN_BFYST", VOICE_GEN_BFYST}, {"VOICE_GEN_BIKDRUG", VOICE_GEN_BIKDRUG}, {"VOICE_GEN_BIKERA", VOICE_GEN_BIKERA}, {"VOICE_GEN_BIKERB", VOICE_GEN_BIKERB}, {"VOICE_GEN_BMOCD", VOICE_GEN_BMOCD}, {"VOICE_GEN_BMORI", VOICE_GEN_BMORI}, {"VOICE_GEN_BMOSEC", VOICE_GEN_BMOSEC}, {"VOICE_GEN_BMOST", VOICE_GEN_BMOST}, {"VOICE_GEN_BMOTR1", VOICE_GEN_BMOTR1}, {"VOICE_GEN_BMYAP", VOICE_GEN_BMYAP}, {"VOICE_GEN_BMYBE", VOICE_GEN_BMYBE}, {"VOICE_GEN_BMYBOUN", VOICE_GEN_BMYBOUN}, {"VOICE_GEN_BMYBOX", VOICE_GEN_BMYBOX}, {"VOICE_GEN_BMYBU", VOICE_GEN_BMYBU}, {"VOICE_GEN_BMYCG", VOICE_GEN_BMYCG}, {"VOICE_GEN_BMYCON", VOICE_GEN_BMYCON}, {"VOICE_GEN_BMYCR", VOICE_GEN_BMYCR}, {"VOICE_GEN_BMYDJ", VOICE_GEN_BMYDJ}, {"VOICE_GEN_BMYDRUG", VOICE_GEN_BMYDRUG}, {"VOICE_GEN_BMYMOUN", VOICE_GEN_BMYMOUN}, {"VOICE_GEN_BMYPOL1", VOICE_GEN_BMYPOL1}, {"VOICE_GEN_BMYPOL2", VOICE_GEN_BMYPOL2}, {"VOICE_GEN_BMYRI", VOICE_GEN_BMYRI}, {"VOICE_GEN_BMYST", VOICE_GEN_BMYST}, {"VOICE_GEN_BYMPI", VOICE_GEN_BYMPI}, {"VOICE_GEN_CWFOFR", VOICE_GEN_CWFOFR}, {"VOICE_GEN_CWFOHB", VOICE_GEN_CWFOHB}, {"VOICE_GEN_CWFYFR1", VOICE_GEN_CWFYFR1}, {"VOICE_GEN_CWFYFR2", VOICE_GEN_CWFYFR2}, {"VOICE_GEN_CWFYHB1", VOICE_GEN_CWFYHB1}, {"VOICE_GEN_CWMOFR1", VOICE_GEN_CWMOFR1}, {"VOICE_GEN_CWMOHB1", VOICE_GEN_CWMOHB1}, {"VOICE_GEN_CWMOHB2", VOICE_GEN_CWMOHB2}, {"VOICE_GEN_CWMYFR", VOICE_GEN_CWMYFR}, {"VOICE_GEN_CWMYHB1", VOICE_GEN_CWMYHB1}, {"VOICE_GEN_CWMYHB2", VOICE_GEN_CWMYHB2}, {"VOICE_GEN_DNFOLC1", VOICE_GEN_DNFOLC1}, {"VOICE_GEN_DNFOLC2", VOICE_GEN_DNFOLC2}, {"VOICE_GEN_DNFYLC", VOICE_GEN_DNFYLC}, {"VOICE_GEN_DNMOLC1", VOICE_GEN_DNMOLC1}, {"VOICE_GEN_DNMOLC2", VOICE_GEN_DNMOLC2}, {"VOICE_GEN_DNMYLC", VOICE_GEN_DNMYLC}, {"VOICE_GEN_DWFOLC", VOICE_GEN_DWFOLC}, {"VOICE_GEN_DWFYLC1", VOICE_GEN_DWFYLC1}, {"VOICE_GEN_DWFYLC2", VOICE_GEN_DWFYLC2}, {"VOICE_GEN_DWMOLC1", VOICE_GEN_DWMOLC1}, {"VOICE_GEN_DWMOLC2", VOICE_GEN_DWMOLC2}, {"VOICE_GEN_DWMYLC1", VOICE_GEN_DWMYLC1}, {"VOICE_GEN_DWMYLC2", VOICE_GEN_DWMYLC2}, {"VOICE_GEN_HFORI", VOICE_GEN_HFORI}, {"VOICE_GEN_HFOST", VOICE_GEN_HFOST}, {"VOICE_GEN_HFYBE", VOICE_GEN_HFYBE}, {"VOICE_GEN_HFYPRO", VOICE_GEN_HFYPRO}, {"VOICE_GEN_HFYRI", VOICE_GEN_HFYRI}, {"VOICE_GEN_HFYST", VOICE_GEN_HFYST}, {"VOICE_GEN_HMORI", VOICE_GEN_HMORI}, {"VOICE_GEN_HMOST", VOICE_GEN_HMOST}, {"VOICE_GEN_HMYBE", VOICE_GEN_HMYBE}, {"VOICE_GEN_HMYCM", VOICE_GEN_HMYCM}, {"VOICE_GEN_HMYCR", VOICE_GEN_HMYCR}, {"VOICE_GEN_HMYDRUG", VOICE_GEN_HMYDRUG}, {"VOICE_GEN_HMYRI", VOICE_GEN_HMYRI}, {"VOICE_GEN_HMYST", VOICE_GEN_HMYST}, {"VOICE_GEN_IMYST", VOICE_GEN_IMYST}, {"VOICE_GEN_IRFYST", VOICE_GEN_IRFYST}, {"VOICE_GEN_IRMYST", VOICE_GEN_IRMYST}, {"VOICE_GEN_MAFFA", VOICE_GEN_MAFFA}, {"VOICE_GEN_MAFFB", VOICE_GEN_MAFFB}, {"VOICE_GEN_MALE01", VOICE_GEN_MALE01}, {"VOICE_GEN_NOVOICE", VOICE_GEN_NOVOICE}, {"VOICE_GEN_OFORI", VOICE_GEN_OFORI}, {"VOICE_GEN_OFOST", VOICE_GEN_OFOST}, {"VOICE_GEN_OFYRI", VOICE_GEN_OFYRI}, {"VOICE_GEN_OFYST", VOICE_GEN_OFYST}, {"VOICE_GEN_OMOBOAT", VOICE_GEN_OMOBOAT}, {"VOICE_GEN_OMOKUNG", VOICE_GEN_OMOKUNG}, {"VOICE_GEN_OMORI", VOICE_GEN_OMORI}, {"VOICE_GEN_OMOST", VOICE_GEN_OMOST}, {"VOICE_GEN_OMYRI", VOICE_GEN_OMYRI}, {"VOICE_GEN_OMYST", VOICE_GEN_OMYST}, {"VOICE_GEN_SBFORI", VOICE_GEN_SBFORI}, {"VOICE_GEN_SBFOST", VOICE_GEN_SBFOST}, {"VOICE_GEN_SBFYPRO", VOICE_GEN_SBFYPRO}, {"VOICE_GEN_SBFYRI", VOICE_GEN_SBFYRI}, {"VOICE_GEN_SBFYST", VOICE_GEN_SBFYST}, {"VOICE_GEN_SBFYSTR", VOICE_GEN_SBFYSTR}, {"VOICE_GEN_SBMOCD", VOICE_GEN_SBMOCD}, {"VOICE_GEN_SBMORI", VOICE_GEN_SBMORI}, {"VOICE_GEN_SBMOST", VOICE_GEN_SBMOST}, {"VOICE_GEN_SBMOTR1", VOICE_GEN_SBMOTR1}, {"VOICE_GEN_SBMOTR2", VOICE_GEN_SBMOTR2}, {"VOICE_GEN_SBMYCR", VOICE_GEN_SBMYCR}, {"VOICE_GEN_SBMYRI", VOICE_GEN_SBMYRI}, {"VOICE_GEN_SBMYST", VOICE_GEN_SBMYST}, {"VOICE_GEN_SBMYTR3", VOICE_GEN_SBMYTR3}, {"VOICE_GEN_SFYPRO", VOICE_GEN_SFYPRO}, {"VOICE_GEN_SHFYPRO", VOICE_GEN_SHFYPRO}, {"VOICE_GEN_SHMYCR", VOICE_GEN_SHMYCR}, {"VOICE_GEN_SMYST", VOICE_GEN_SMYST}, {"VOICE_GEN_SMYST2", VOICE_GEN_SMYST2}, {"VOICE_GEN_SOFORI", VOICE_GEN_SOFORI}, {"VOICE_GEN_SOFOST", VOICE_GEN_SOFOST}, {"VOICE_GEN_SOFYBU", VOICE_GEN_SOFYBU}, {"VOICE_GEN_SOFYRI", VOICE_GEN_SOFYRI}, {"VOICE_GEN_SOFYST", VOICE_GEN_SOFYST}, {"VOICE_GEN_SOMOBU", VOICE_GEN_SOMOBU}, {"VOICE_GEN_SOMORI", VOICE_GEN_SOMORI}, {"VOICE_GEN_SOMOST", VOICE_GEN_SOMOST}, {"VOICE_GEN_SOMYAP", VOICE_GEN_SOMYAP}, {"VOICE_GEN_SOMYBU", VOICE_GEN_SOMYBU}, {"VOICE_GEN_SOMYRI", VOICE_GEN_SOMYRI}, {"VOICE_GEN_SOMYST", VOICE_GEN_SOMYST}, {"VOICE_GEN_SWFOPRO", VOICE_GEN_SWFOPRO}, {"VOICE_GEN_SWFORI", VOICE_GEN_SWFORI}, {"VOICE_GEN_SWFOST", VOICE_GEN_SWFOST}, {"VOICE_GEN_SWFYRI", VOICE_GEN_SWFYRI}, {"VOICE_GEN_SWFYST", VOICE_GEN_SWFYST}, {"VOICE_GEN_SWFYSTR", VOICE_GEN_SWFYSTR}, {"VOICE_GEN_SWMOCD", VOICE_GEN_SWMOCD}, {"VOICE_GEN_SWMORI", VOICE_GEN_SWMORI}, {"VOICE_GEN_SWMOST", VOICE_GEN_SWMOST}, {"VOICE_GEN_SWMOTR1", VOICE_GEN_SWMOTR1}, {"VOICE_GEN_SWMOTR2", VOICE_GEN_SWMOTR2}, {"VOICE_GEN_SWMOTR3", VOICE_GEN_SWMOTR3}, {"VOICE_GEN_SWMOTR4", VOICE_GEN_SWMOTR4}, {"VOICE_GEN_SWMOTR5", VOICE_GEN_SWMOTR5}, {"VOICE_GEN_SWMYCR", VOICE_GEN_SWMYCR}, {"VOICE_GEN_SWMYHP1", VOICE_GEN_SWMYHP1}, {"VOICE_GEN_SWMYHP2", VOICE_GEN_SWMYHP2}, {"VOICE_GEN_SWMYRI", VOICE_GEN_SWMYRI}, {"VOICE_GEN_SWMYST", VOICE_GEN_SWMYST}, {"VOICE_GEN_VBFYPRO", VOICE_GEN_VBFYPRO}, {"VOICE_GEN_VBFYST2", VOICE_GEN_VBFYST2}, {"VOICE_GEN_VBMOCD", VOICE_GEN_VBMOCD}, {"VOICE_GEN_VBMYCR", VOICE_GEN_VBMYCR}, {"VOICE_GEN_VBMYELV", VOICE_GEN_VBMYELV}, {"VOICE_GEN_VHFYPRO", VOICE_GEN_VHFYPRO}, {"VOICE_GEN_VHFYST3", VOICE_GEN_VHFYST3}, {"VOICE_GEN_VHMYCR", VOICE_GEN_VHMYCR}, {"VOICE_GEN_VHMYELV", VOICE_GEN_VHMYELV}, {"VOICE_GEN_VIMYELV", VOICE_GEN_VIMYELV}, {"VOICE_GEN_VWFYPRO", VOICE_GEN_VWFYPRO}, {"VOICE_GEN_VWFYST1", VOICE_GEN_VWFYST1}, {"VOICE_GEN_VWFYWAI", VOICE_GEN_VWFYWAI}, {"VOICE_GEN_VWMOTR1", VOICE_GEN_VWMOTR1}, {"VOICE_GEN_VWMOTR2", VOICE_GEN_VWMOTR2}, {"VOICE_GEN_VWMYAP", VOICE_GEN_VWMYAP}, {"VOICE_GEN_VWMYBJD", VOICE_GEN_VWMYBJD}, {"VOICE_GEN_VWMYCD", VOICE_GEN_VWMYCD}, {"VOICE_GEN_VWMYCR", VOICE_GEN_VWMYCR}, {"VOICE_GEN_WFOPJ", VOICE_GEN_WFOPJ}, {"VOICE_GEN_WFORI", VOICE_GEN_WFORI}, {"VOICE_GEN_WFOST", VOICE_GEN_WFOST}, {"VOICE_GEN_WFYBE", VOICE_GEN_WFYBE}, {"VOICE_GEN_WFYBU", VOICE_GEN_WFYBU}, {"VOICE_GEN_WFYCRK", VOICE_GEN_WFYCRK}, {"VOICE_GEN_WFYCRP", VOICE_GEN_WFYCRP}, {"VOICE_GEN_WFYJG", VOICE_GEN_WFYJG}, {"VOICE_GEN_WFYLG", VOICE_GEN_WFYLG}, {"VOICE_GEN_WFYPRO", VOICE_GEN_WFYPRO}, {"VOICE_GEN_WFYRI", VOICE_GEN_WFYRI}, {"VOICE_GEN_WFYRO", VOICE_GEN_WFYRO}, {"VOICE_GEN_WFYST", VOICE_GEN_WFYST}, {"VOICE_GEN_WFYSTEW", VOICE_GEN_WFYSTEW}, {"VOICE_GEN_WMOMIB", VOICE_GEN_WMOMIB}, {"VOICE_GEN_WMOPJ", VOICE_GEN_WMOPJ}, {"VOICE_GEN_WMOPREA", VOICE_GEN_WMOPREA}, {"VOICE_GEN_WMORI", VOICE_GEN_WMORI}, {"VOICE_GEN_WMOSCI", VOICE_GEN_WMOSCI}, {"VOICE_GEN_WMOST", VOICE_GEN_WMOST}, {"VOICE_GEN_WMOTR1", VOICE_GEN_WMOTR1}, {"VOICE_GEN_WMYBE", VOICE_GEN_WMYBE}, {"VOICE_GEN_WMYBMX", VOICE_GEN_WMYBMX}, {"VOICE_GEN_WMYBOUN", VOICE_GEN_WMYBOUN}, {"VOICE_GEN_WMYBOX", VOICE_GEN_WMYBOX}, {"VOICE_GEN_WMYBP", VOICE_GEN_WMYBP}, {"VOICE_GEN_WMYBU", VOICE_GEN_WMYBU}, {"VOICE_GEN_WMYCD1", VOICE_GEN_WMYCD1}, {"VOICE_GEN_WMYCD2", VOICE_GEN_WMYCD2}, {"VOICE_GEN_WMYCH", VOICE_GEN_WMYCH}, {"VOICE_GEN_WMYCON", VOICE_GEN_WMYCON}, {"VOICE_GEN_WMYCONB", VOICE_GEN_WMYCONB}, {"VOICE_GEN_WMYCR", VOICE_GEN_WMYCR}, {"VOICE_GEN_WMYDRUG", VOICE_GEN_WMYDRUG}, {"VOICE_GEN_WMYGAR", VOICE_GEN_WMYGAR}, {"VOICE_GEN_WMYGOL1", VOICE_GEN_WMYGOL1}, {"VOICE_GEN_WMYGOL2", VOICE_GEN_WMYGOL2}, {"VOICE_GEN_WMYJG", VOICE_GEN_WMYJG}, {"VOICE_GEN_WMYLG", VOICE_GEN_WMYLG}, {"VOICE_GEN_WMYMECH", VOICE_GEN_WMYMECH}, {"VOICE_GEN_WMYMOUN", VOICE_GEN_WMYMOUN}, {"VOICE_GEN_WMYPLT", VOICE_GEN_WMYPLT}, {"VOICE_GEN_WMYRI", VOICE_GEN_WMYRI}, {"VOICE_GEN_WMYRO", VOICE_GEN_WMYRO}, {"VOICE_GEN_WMYSGRD", VOICE_GEN_WMYSGRD}, {"VOICE_GEN_WMYSKAT", VOICE_GEN_WMYSKAT}, {"VOICE_GEN_WMYST", VOICE_GEN_WMYST}, {"VOICE_GEN_WMYTX1", VOICE_GEN_WMYTX1}, {"VOICE_GEN_WMYTX2", VOICE_GEN_WMYTX2}, {"VOICE_GEN_WMYVA", VOICE_GEN_WMYVA}
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    case PED_TYPE_EMG: {
        static const auto mapping = notsa::make_mapping<std::string_view, eEmgSpeechVoices>({
            {"VOICE_EMG_ARMY1", VOICE_EMG_ARMY1}, {"VOICE_EMG_ARMY2", VOICE_EMG_ARMY2}, {"VOICE_EMG_ARMY3", VOICE_EMG_ARMY3}, {"VOICE_EMG_EMT1", VOICE_EMG_EMT1}, {"VOICE_EMG_EMT2", VOICE_EMG_EMT2}, {"VOICE_EMG_EMT3", VOICE_EMG_EMT3}, {"VOICE_EMG_EMT4", VOICE_EMG_EMT4}, {"VOICE_EMG_EMT5", VOICE_EMG_EMT5}, {"VOICE_EMG_FBI2", VOICE_EMG_FBI2}, {"VOICE_EMG_FBI3", VOICE_EMG_FBI3}, {"VOICE_EMG_FBI4", VOICE_EMG_FBI4}, {"VOICE_EMG_FBI5", VOICE_EMG_FBI5}, {"VOICE_EMG_FBI6", VOICE_EMG_FBI6}, {"VOICE_EMG_LAPD1", VOICE_EMG_LAPD1}, {"VOICE_EMG_LAPD2", VOICE_EMG_LAPD2}, {"VOICE_EMG_LAPD3", VOICE_EMG_LAPD3}, {"VOICE_EMG_LAPD4", VOICE_EMG_LAPD4}, {"VOICE_EMG_LAPD5", VOICE_EMG_LAPD5}, {"VOICE_EMG_LAPD6", VOICE_EMG_LAPD6}, {"VOICE_EMG_LAPD7", VOICE_EMG_LAPD7}, {"VOICE_EMG_LAPD8", VOICE_EMG_LAPD8}, {"VOICE_EMG_LVPD1", VOICE_EMG_LVPD1}, {"VOICE_EMG_LVPD2", VOICE_EMG_LVPD2}, {"VOICE_EMG_LVPD3", VOICE_EMG_LVPD3}, {"VOICE_EMG_LVPD4", VOICE_EMG_LVPD4}, {"VOICE_EMG_LVPD5", VOICE_EMG_LVPD5}, {"VOICE_EMG_MCOP1", VOICE_EMG_MCOP1}, {"VOICE_EMG_MCOP2", VOICE_EMG_MCOP2}, {"VOICE_EMG_MCOP3", VOICE_EMG_MCOP3}, {"VOICE_EMG_MCOP4", VOICE_EMG_MCOP4}, {"VOICE_EMG_MCOP5", VOICE_EMG_MCOP5}, {"VOICE_EMG_MCOP6", VOICE_EMG_MCOP6}, {"VOICE_EMG_PULASKI", VOICE_EMG_PULASKI}, {"VOICE_EMG_RCOP1", VOICE_EMG_RCOP1}, {"VOICE_EMG_RCOP2", VOICE_EMG_RCOP2}, {"VOICE_EMG_RCOP3", VOICE_EMG_RCOP3}, {"VOICE_EMG_RCOP4", VOICE_EMG_RCOP4}, {"VOICE_EMG_SFPD1", VOICE_EMG_SFPD1}, {"VOICE_EMG_SFPD2", VOICE_EMG_SFPD2}, {"VOICE_EMG_SFPD3", VOICE_EMG_SFPD3}, {"VOICE_EMG_SFPD4", VOICE_EMG_SFPD4}, {"VOICE_EMG_SFPD5", VOICE_EMG_SFPD5}, {"VOICE_EMG_SWAT1", VOICE_EMG_SWAT1}, {"VOICE_EMG_SWAT2", VOICE_EMG_SWAT2}, {"VOICE_EMG_SWAT4", VOICE_EMG_SWAT4}, {"VOICE_EMG_SWAT6", VOICE_EMG_SWAT6},
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    case PED_TYPE_PLAYER: {
        static const auto mapping = notsa::make_mapping<std::string_view, ePlySpeechVoices>({
            {"VOICE_PLY_AG", VOICE_PLY_AG}, {"VOICE_PLY_AG2", VOICE_PLY_AG2}, {"VOICE_PLY_AR", VOICE_PLY_AR}, {"VOICE_PLY_AR2", VOICE_PLY_AR2}, {"VOICE_PLY_CD", VOICE_PLY_CD}, {"VOICE_PLY_CD2", VOICE_PLY_CD2}, {"VOICE_PLY_CF", VOICE_PLY_CF}, {"VOICE_PLY_CF2", VOICE_PLY_CF2}, {"VOICE_PLY_CG", VOICE_PLY_CG}, {"VOICE_PLY_CG2", VOICE_PLY_CG2}, {"VOICE_PLY_CR", VOICE_PLY_CR}, {"VOICE_PLY_CR2", VOICE_PLY_CR2}, {"VOICE_PLY_PG", VOICE_PLY_PG}, {"VOICE_PLY_PG2", VOICE_PLY_PG2}, {"VOICE_PLY_PR", VOICE_PLY_PR}, {"VOICE_PLY_PR2", VOICE_PLY_PR2}, {"VOICE_PLY_WG", VOICE_PLY_WG}, {"VOICE_PLY_WG2", VOICE_PLY_WG2}, {"VOICE_PLY_WR", VOICE_PLY_WR}, {"VOICE_PLY_WR2", VOICE_PLY_WR2},
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    case PED_TYPE_GANG: {
        static const auto mapping = notsa::make_mapping<std::string_view, eGngSpeechVoices>({
            {"VOICE_GNG_BALLAS1", VOICE_GNG_BALLAS1}, {"VOICE_GNG_BALLAS2", VOICE_GNG_BALLAS2}, {"VOICE_GNG_BALLAS3", VOICE_GNG_BALLAS3}, {"VOICE_GNG_BALLAS4", VOICE_GNG_BALLAS4}, {"VOICE_GNG_BALLAS5", VOICE_GNG_BALLAS5}, {"VOICE_GNG_BIG_BEAR", VOICE_GNG_BIG_BEAR}, {"VOICE_GNG_CESAR", VOICE_GNG_CESAR}, {"VOICE_GNG_DNB1", VOICE_GNG_DNB1}, {"VOICE_GNG_DNB2", VOICE_GNG_DNB2}, {"VOICE_GNG_DNB3", VOICE_GNG_DNB3}, {"VOICE_GNG_DNB5", VOICE_GNG_DNB5}, {"VOICE_GNG_DWAINE", VOICE_GNG_DWAINE}, {"VOICE_GNG_FAM1", VOICE_GNG_FAM1}, {"VOICE_GNG_FAM2", VOICE_GNG_FAM2}, {"VOICE_GNG_FAM3", VOICE_GNG_FAM3}, {"VOICE_GNG_FAM4", VOICE_GNG_FAM4}, {"VOICE_GNG_FAM5", VOICE_GNG_FAM5}, {"VOICE_GNG_JIZZY", VOICE_GNG_JIZZY}, {"VOICE_GNG_LSV1", VOICE_GNG_LSV1}, {"VOICE_GNG_LSV2", VOICE_GNG_LSV2}, {"VOICE_GNG_LSV3", VOICE_GNG_LSV3}, {"VOICE_GNG_LSV4", VOICE_GNG_LSV4}, {"VOICE_GNG_LSV5", VOICE_GNG_LSV5}, {"VOICE_GNG_MACCER", VOICE_GNG_MACCER}, {"VOICE_GNG_MAFBOSS", VOICE_GNG_MAFBOSS}, {"VOICE_GNG_OGLOC", VOICE_GNG_OGLOC}, {"VOICE_GNG_RYDER", VOICE_GNG_RYDER}, {"VOICE_GNG_SFR1", VOICE_GNG_SFR1}, {"VOICE_GNG_SFR2", VOICE_GNG_SFR2}, {"VOICE_GNG_SFR3", VOICE_GNG_SFR3}, {"VOICE_GNG_SFR4", VOICE_GNG_SFR4}, {"VOICE_GNG_SFR5", VOICE_GNG_SFR5}, {"VOICE_GNG_SMOKE", VOICE_GNG_SMOKE}, {"VOICE_GNG_STRI1", VOICE_GNG_STRI1}, {"VOICE_GNG_STRI2", VOICE_GNG_STRI2}, {"VOICE_GNG_STRI4", VOICE_GNG_STRI4}, {"VOICE_GNG_STRI5", VOICE_GNG_STRI5}, {"VOICE_GNG_SWEET", VOICE_GNG_SWEET}, {"VOICE_GNG_TBONE", VOICE_GNG_TBONE}, {"VOICE_GNG_TORENO", VOICE_GNG_TORENO}, {"VOICE_GNG_TRUTH", VOICE_GNG_TRUTH}, {"VOICE_GNG_VLA1", VOICE_GNG_VLA1}, {"VOICE_GNG_VLA2", VOICE_GNG_VLA2}, {"VOICE_GNG_VLA3", VOICE_GNG_VLA3}, {"VOICE_GNG_VLA4", VOICE_GNG_VLA4}, {"VOICE_GNG_VLA5", VOICE_GNG_VLA5}, {"VOICE_GNG_VMAFF1", VOICE_GNG_VMAFF1}, {"VOICE_GNG_VMAFF2", VOICE_GNG_VMAFF2}, {"VOICE_GNG_VMAFF3", VOICE_GNG_VMAFF3}, {"VOICE_GNG_VMAFF4", VOICE_GNG_VMAFF4}, {"VOICE_GNG_VMAFF5", VOICE_GNG_VMAFF5}, {"VOICE_GNG_WOOZIE", VOICE_GNG_WOOZIE},
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    case PED_TYPE_GFD: {
        static const auto mapping = notsa::make_mapping<std::string_view, eGfdSpeechVoices>({
            {"VOICE_GFD_BARBARA", VOICE_GFD_BARBARA}, {"VOICE_GFD_BMOBAR", VOICE_GFD_BMOBAR}, {"VOICE_GFD_BMYBARB", VOICE_GFD_BMYBARB}, {"VOICE_GFD_BMYTATT", VOICE_GFD_BMYTATT}, {"VOICE_GFD_CATALINA", VOICE_GFD_CATALINA}, {"VOICE_GFD_DENISE", VOICE_GFD_DENISE}, {"VOICE_GFD_HELENA", VOICE_GFD_HELENA}, {"VOICE_GFD_KATIE", VOICE_GFD_KATIE}, {"VOICE_GFD_MICHELLE", VOICE_GFD_MICHELLE}, {"VOICE_GFD_MILLIE", VOICE_GFD_MILLIE}, {"VOICE_GFD_POL_ANN", VOICE_GFD_POL_ANN}, {"VOICE_GFD_WFYBURG", VOICE_GFD_WFYBURG}, {"VOICE_GFD_WFYCLOT", VOICE_GFD_WFYCLOT}, {"VOICE_GFD_WMYAMMO", VOICE_GFD_WMYAMMO}, {"VOICE_GFD_WMYBARB", VOICE_GFD_WMYBARB}, {"VOICE_GFD_WMYBELL", VOICE_GFD_WMYBELL}, {"VOICE_GFD_WMYCLOT", VOICE_GFD_WMYCLOT}, {"VOICE_GFD_WMYPIZZ", VOICE_GFD_WMYPIZZ},
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x4E3EB0
void CAEPedSpeechAudioEntity::DisableAllPedSpeech() {
    s_bAllSpeechDisabled = true;
}

// 0x4E44F0
bool __stdcall CAEPedSpeechAudioEntity::IsGlobalContextPain(eGlobalSpeechContext gCtx) {
    return CTX_GLOBAL_PAIN_START < gCtx && gCtx < CTX_GLOBAL_PAIN_END;
}

// 0x4E3ED0
void CAEPedSpeechAudioEntity::SetCJMood(eCJMood basicMood, uint32 overrideTimeMS, int16 isGangBanging, int16 isFat, int16 isWellDressed) {
    s_nCJMoodOverrideTime = CTimer::GetTimeInMS() + overrideTimeMS;
    s_nCJBasicMood  = [=]{
        switch (basicMood) {
        case MOOD_AR:
        case MOOD_CR:
        case MOOD_PR:
        case MOOD_WR: return basicMood;
        default:      return MOOD_UNK;
        }
    }();
    s_nCJGangBanging = isGangBanging;
    s_nCJFat         = isFat;
    s_nCJWellDressed = isWellDressed;
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

// 0x4E4600
bool __stdcall CAEPedSpeechAudioEntity::IsGlobalContextImportantForInterupting(eGlobalSpeechContext gCtx) {
    return GetGlobalSpeechContextInfo(gCtx)->IsImportantForInterrupting; // NOTSA: Use context info lookup instead of static switch
    /*
    switch (gCtx) {
    case CTX_GLOBAL_ARREST:
    case CTX_GLOBAL_ARRESTED:
    case CTX_GLOBAL_JOIN_GANG_NO:
    case CTX_GLOBAL_JOIN_GANG_YES:
    case CTX_GLOBAL_JOIN_ME_ASK:
    return true;
    default:
    return false;
    }
    */
}

// 0x4E46F0 - unused
bool CAEPedSpeechAudioEntity::IsGlobalContextUberImportant(int16 gCtx) {
    return false;
}

// 0x4E46B0
bool CAEPedSpeechAudioEntity::IsGlobalContextImportantForWidescreen(eGlobalSpeechContext gCtx) {
    switch (m_PedAudioType) {
    case PED_TYPE_GFD:
    case PED_TYPE_PLAYER:
        return true;
    }
    return GetGlobalSpeechContextInfo(gCtx)->IsImportantForWidescreen; // NOTSA: Use context info lookup instead of static switch
    /*
    switch (gCtx) {
    case CTX_GLOBAL_ARREST:
    case CTX_GLOBAL_ARRESTED:
    case CTX_GLOBAL_HAVING_SEX:
        return true;
    }
    return false;
    */
}

// 0x4E4260
int8 CAEPedSpeechAudioEntity::GetSexForSpecialPed(uint32 a1) {
    return 1;
}

// 0x4E47E0
int16 CAEPedSpeechAudioEntity::GetRepeatTime(eGlobalSpeechContext gCtx) {
    assert(gCtx < CTX_GLOBAL_NUM); // OG: return 0

    if (const auto* const ctxi = GetGlobalSpeechContextInfo(gCtx)) {
        return ctxi->RepeatTime;
    }
    return 0;
}

// 0x4E4840
void CAEPedSpeechAudioEntity::LoadAndPlaySpeech(uint32 playbackTimeOffsetMS) {
    auto* const speech = GetCurrentSpeech();
    switch (speech->Status) {
    case CAEPedSpeechSlot::eStatus::FREE:
    case CAEPedSpeechSlot::eStatus::RESERVED:
        break;
    default:
        return;
    }

    AEAudioHardware.LoadSound(m_BankID, m_SoundID, SND_BANK_SLOT_SPEECH1 + m_PedSpeechSlotID);
    *speech = CAEPedSpeechSlot{
        .Status            = CAEPedSpeechSlot::eStatus::LOADING,
        .AudioEntity       = this,
        .SoundID           = m_SoundID,
        .SoundBankID       = m_BankID,
        .StartPlaybackTime = CTimer::GetTimeInMS() + playbackTimeOffsetMS,
        .GCtx              = m_LastGCtx,
        .PedAudioType      = m_PedAudioType,
        .ForceAudible      = m_IsForcedAudible,
    };
}

// 0x4E49B0
int32 CAEPedSpeechAudioEntity::GetNumSlotsPlayingContext(int16 context) {
    return rng::count_if(s_PedSpeechSlots, [&](CAEPedSpeechSlot& speech) {
        return speech.Status != CAEPedSpeechSlot::eStatus::FREE && speech.GCtx == context;
    });
}

// 0x4E49E0
uint32 CAEPedSpeechAudioEntity::GetNextPlayTime(eGlobalSpeechContext gCtx) {
    assert(gCtx < CTX_GLOBAL_NUM); // OG: `return 0;`

    return GetNextPlayTimeRef(gCtx);
}

// 0x4E4A20
void CAEPedSpeechAudioEntity::SetNextPlayTime(eGlobalSpeechContext gCtx) {
    assert(gCtx < CTX_GLOBAL_NUM); // OG: `return;`

    if (const auto* const ctxi = GetGlobalSpeechContextInfo(gCtx)) {
        GetNextPlayTimeRef(gCtx) = CTimer::GetTimeInMS() + ctxi->RepeatTime + CAEAudioUtility::GetRandomNumberInRange(1, 1000);
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
bool CAEPedSpeechAudioEntity::CanPedSayGlobalContext(eGlobalSpeechContext gCtx) const {
    if (!m_IsInitialized) {
        return false;
    }
    const auto sCtx = GetSpecificSpeechContext(gCtx, m_PedAudioType);
    if (sCtx == -1) {
        return false;
    }
    if (const auto* const ctxi = GetSpecificSpeechContextInfo(sCtx, gCtx, m_PedAudioType, m_VoiceID)) {
        return ctxi->FirstSoundID != -1;
    }
    return false;
}

// 0x4E58C0
int8 CAEPedSpeechAudioEntity::GetVoiceAndTypeFromModel(eModelID modelId) {
    auto* const mi = CModelInfo::GetModelInfo(modelId)->AsPedModelInfoPtr();
    if (mi->m_nPedAudioType == -1 || mi->m_nPedAudioType >= PED_TYPE_NUM) {
        return 0;
    }

    if (mi->m_nPedAudioType == PED_TYPE_SPC) {
        return GetVoiceAndTypeForSpecialPed(mi->m_nKey);
    }

    m_VoiceID = mi->m_nVoiceId;
    if (m_VoiceID == -1) {
        return 0;
    }

    mi->IncrementVoice();

    return 1;
}

// 0x4E5920
int16 CAEPedSpeechAudioEntity::GetSoundAndBankIDs(eGlobalSpeechContext gCtx, eSpecificSpeechContext& outSpecificSpeechContext) {
    // Left out some ifs error checking ifs as they aren't necessary (They're gonna get caught in debug anyways)

    const auto sCtx = GetSpecificSpeechContext(gCtx, m_PedAudioType);
    if (sCtx == -1) {
        return -1;
    }
    outSpecificSpeechContext = sCtx;

    const auto* const ctx = GetSpecificSpeechContextInfo(sCtx, gCtx, m_PedAudioType, m_VoiceID);
    if (!ctx) {
        return -1;
    }

    m_BankID = GetVoiceSoundBank(gCtx, m_PedAudioType, m_VoiceID);

    if (ctx->FirstSoundID == -1) {
        return -1;
    }
    assert(ctx->FirstSoundID <= ctx->LastSoundID);

    const size_t numSounds = ctx->LastSoundID - ctx->FirstSoundID;
    assert(numSounds > 0);

    // Find sound ID to use
    // If all possible sounds are in the PhraseMemory,
    // the least recently used one will be picked
    // NOTE: Below is a better version of what they did (without using an intermediary array)

    const auto GetPhraseIndexInMemory = [this](int32 soundID) -> int16 {
        for (auto&& [i, p] : notsa::enumerate(s_PhraseMemory)) {
            if (p.SoundID == soundID && p.BankID == m_BankID) {
                return i;
            }
        }
        return -1;
    };

    int16      soundIDToUse    = -1;
    int16      maxPhraseIMemdx = -1;
    const auto rndOffset    = CAEAudioUtility::GetRandomNumberInRange(0u, numSounds);
    for (size_t i = 0; i < std::min(20u, numSounds); i++) { // NOTE: Here you can tune the maximum tries (Default: 20)
        const auto soundIDCurr  = ctx->FirstSoundID + (int16)((rndOffset + i) % (numSounds + 1));
        const auto phraseMemIdx = GetPhraseIndexInMemory(soundIDCurr);

        // Not in memory at all? Good, pick this!
        if (phraseMemIdx == -1) {
            soundIDToUse = soundIDCurr;
            break;
        }

        // Maybe this was used a longer time ago than the previous one?
        if (maxPhraseIMemdx < phraseMemIdx) {
            soundIDToUse = soundIDCurr;
            maxPhraseIMemdx = phraseMemIdx;
        }
    }
    assert(soundIDToUse != -1);

    // Insert into front of `s_PhraseMemory`
    rng::shift_right(s_PhraseMemory, 1);
    s_PhraseMemory[0] = {soundIDToUse, m_BankID};

    return soundIDToUse - ctx->FirstSoundID;
}

// 0x4E5F10
int16 CAEPedSpeechAudioEntity::CanWePlayGlobalSpeechContext(eGlobalSpeechContext gCtx) {
    if (!IsGlobalContextImportantForInterupting(gCtx) && !IsGlobalContextPain(gCtx)) {
        const auto CheckSlot = [](auto slot) {
            return s_PedSpeechSlots[slot].Status == CAEPedSpeechSlot::eStatus::RESERVED
                ? slot
                : -1;
        };
        if (s_bPedConversationHappening) {
            if (this == &s_pConversationPed1->m_pedSpeech) {
                return CheckSlot(s_pConversationPedSlot1);
            }
            if (this == &s_pConversationPed2->m_pedSpeech) {
                return CheckSlot(s_pConversationPedSlot2);
            }
        } else if (s_bPlayerConversationHappening) {
            if (this == &s_pPlayerConversationPed->m_pedSpeech) {
                return CheckSlot(s_pConversationPedSlot1);
            }    
        }
    }
    return GetNextPlayTime(gCtx) < CTimer::GetTimeInMS()
        ? GetFreeSpeechSlot() // s_NextSpeechSlot is set in `GetFreeSpeechSlot`
        : -1;
}

// 0x4E6550
int16 CAEPedSpeechAudioEntity::AddSayEvent(eAudioEvents audioEvent, eGlobalSpeechContext gCtx, uint32 startTimeDelayMs, float probability, bool overrideSilence, bool isForceAudible, bool isFrontEnd) {
    // tempTimeOffset == 0, so ignore it

    if (!m_IsInitialized || s_bAllSpeechDisabled || m_IsSpeechForScriptsDisabled) {
        return -1;
    }

    if (TheCamera.m_bWideScreenOn && !IsGlobalContextImportantForWidescreen(gCtx)) {
        return -1;
    }

    if (CGameLogic::GameState == eGameState::GAME_STATE_PLAYING_LOGO) {
        return -1;
    }

    if (gCtx == CTX_GLOBAL_CHAT) {
        if (CTimer::GetFrameCounter() % 64 || s_bPedConversationHappening || s_bPlayerConversationHappening) {
            return -1;
        }
    } else if (gCtx == CTX_GLOBAL_PAIN_CJ_DROWNING && CWeather::UnderWaterness < 0.5f)  {
        return -1;
    }

    if (!CAEAudioUtility::ResolveProbability(probability) || audioEvent != AE_SPEECH_PED) {
        return -1;
    }

    if (m_IsSpeechDisabled && !overrideSilence) {
        return -1;
    }

    const auto IsContextImportant = [](eGlobalSpeechContext c) {
        return IsGlobalContextPain(c) || IsGlobalContextImportantForInterupting(c);
    };
    if (IsContextImportant(gCtx)) {
        if (const auto* const speech = GetCurrentSpeech()) {
            if (IsContextImportant(speech->GCtx)) {
                return -1;
            }
        }
        StopCurrentSpeech();
    }

    if (!m_pEntity->AsPed()->IsAlive() && !IsGlobalContextPain(gCtx)) {
        return -1;
    }

    if (IsGlobalContextImportantForStreaming(gCtx) || isForceAudible || isFrontEnd) {
        if (CStreaming::ms_numModelsRequested > 15 && CAEVehicleAudioEntity::s_pVehicleAudioSettingsForRadio) {
            return -1;
        }
    } else if (CStreaming::IsVeryBusy()) {
        return -1;
    }

    if (m_PedAudioType == PED_TYPE_PLAYER) {
        if (FindPlayerPed() != m_pEntity || s_bAPlayerSpeaking && !m_IsPlayingSpeech) {
            return -1;
        }
    }

    if (CVector::DistSqr(TheCamera.GetPosition(), m_pEntity->GetPosition()) >= sq(40.f)) {
        return -1;
    }

    eSpecificSpeechContext sCtx;
    const auto soundID = CAEPedSpeechAudioEntity::GetSoundAndBankIDs(gCtx, sCtx);
    if (soundID == -1) {
        return -1;
    }

    const auto speechSlotID = m_PedAudioType == PED_TYPE_PLAYER
        ? CTimer::GetTimeInMS() >= GetNextPlayTime(gCtx)
            ? PLAYER_SPEECH_SLOT
            : -1
        : CanWePlayGlobalSpeechContext(gCtx);
    if (speechSlotID == -1) {
        return -1;
    }

    SetNextPlayTime(gCtx);
    m_IsFrontend = isFrontEnd;
    m_IsForcedAudible = isForceAudible;
    if (const auto veh = m_pEntity->AsPed()->GetVehicleIfInOne()) {
        m_IsForcedAudible |= veh == FindPlayerVehicle() && gCtx != CTX_GLOBAL_STOMACH_RUMBLE;
    }
    
    m_EventVolume = GetDefaultVolume(AE_SPEECH_PED);
    if (m_PedAudioType == PED_TYPE_PLAYER) {
        m_EventVolume += 3.f;
    }
    m_EventVolume += GetSpeechContextVolumeOffset(gCtx);

    m_IsPlayingSpeech = true;
    if (m_PedAudioType == PED_TYPE_PLAYER) {
        s_bAPlayerSpeaking = true;
    }

    m_LastGCtx        = gCtx;
    m_PedSpeechSlotID = speechSlotID;
    LoadAndPlaySpeech(startTimeDelayMs);

    return soundID;
}

// 0x4E68D0
void CAEPedSpeechAudioEntity::Initialise(CEntity* ped) {
    *this = CAEPedSpeechAudioEntity{ped->AsPed()};
}

// 0x4E69E0
bool CAEPedSpeechAudioEntity::CanPedHoldConversation() {
    return CanPedSayGlobalContext(CTX_GLOBAL_PCONV_QUESTION);
}

// 0x4E4510
bool CAEPedSpeechAudioEntity::IsGlobalContextImportantForStreaming(eGlobalSpeechContext gCtx) {
    switch (m_PedAudioType) {
    case PED_TYPE_GFD:
    case PED_TYPE_PLAYER:
        return true;
    }
    return GetGlobalSpeechContextInfo(gCtx)->IsImportantForStreaming; // NOTSA: Use context info lookup instead of static switch
    /*
    switch (gCtx) {
    case CTX_GLOBAL_ARREST:
    case CTX_GLOBAL_ARRESTED:
    case CTX_GLOBAL_CONV_DISL_CAR:
    case CTX_GLOBAL_CONV_DISL_CLOTHES:
    case CTX_GLOBAL_CONV_DISL_HAIR:
    case CTX_GLOBAL_CONV_DISL_PHYS:
    case CTX_GLOBAL_CONV_DISL_SHOES:
    case CTX_GLOBAL_CONV_DISL_SMELL:
    case CTX_GLOBAL_CONV_DISL_TATTOO:
    case CTX_GLOBAL_CONV_DISL_WEATHER:
    case CTX_GLOBAL_CONV_IGNORED:
    case CTX_GLOBAL_CONV_LIKE_CAR:
    case CTX_GLOBAL_CONV_LIKE_CLOTHES:
    case CTX_GLOBAL_CONV_LIKE_HAIR:
    case CTX_GLOBAL_CONV_LIKE_PHYS:
    case CTX_GLOBAL_CONV_LIKE_SHOES:
    case CTX_GLOBAL_CONV_LIKE_SMELL:
    case CTX_GLOBAL_CONV_LIKE_TATTOO:
    case CTX_GLOBAL_CONV_LIKE_WEATHER:
    case CTX_GLOBAL_JOIN_GANG_NO:
    case CTX_GLOBAL_JOIN_GANG_YES:
    case CTX_GLOBAL_JOIN_ME_ASK:
    case CTX_GLOBAL_PCONV_AGREE_BAD:
    case CTX_GLOBAL_PCONV_AGREE_GOOD:
    case CTX_GLOBAL_PCONV_ANS_NO:
    case CTX_GLOBAL_PCONV_DISMISS:
    case CTX_GLOBAL_PCONV_GREET_FEM:
    case CTX_GLOBAL_PCONV_GREET_MALE:
    case CTX_GLOBAL_PCONV_PART_FEM:
    case CTX_GLOBAL_PCONV_PART_MALE:
    case CTX_GLOBAL_PCONV_QUESTION:
    case CTX_GLOBAL_PCONV_STATE_BAD:
    case CTX_GLOBAL_PCONV_STATE_GOOD:
        return true;
    }
    return false;
    */
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
    if (!m_IsInitialized || !m_IsPlayingSpeech) {
        return;
    }

    if (auto* const tFacial = CTask::Cast<CTaskComplexFacial>(m_pEntity->AsPed()->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_FACIAL_COMPLEX))) {
        tFacial->StopAll();
    }

    auto* const speech = GetCurrentSpeech();

    if (speech->Status == CAEPedSpeechSlot::eStatus::PLAYING) {
        if (auto* const s = std::exchange(m_Sound, nullptr)) {
            s->StopSoundAndForget();
        }
    }

    *speech = CAEPedSpeechSlot{
        .Status = speech->IsReservedForPedConversation || speech->IsReservedForPlayerConversation
            ? CAEPedSpeechSlot::eStatus::RESERVED
            : CAEPedSpeechSlot::eStatus::FREE,
        .IsReservedForPedConversation    = speech->IsReservedForPedConversation,
        .IsReservedForPlayerConversation = speech->IsReservedForPlayerConversation,
    };

    m_IsPlayingSpeech = false;
    if (m_PedAudioType == PED_TYPE_PLAYER) {
        s_bAPlayerSpeaking = false;
    }
    m_PedSpeechSlotID = -1;
}

// 0x4E4400
bool CAEPedSpeechAudioEntity::GetSoundAndBankIDsForScriptedSpeech(eAudioEvents scriptID) {
    int32         soundID;
    eSoundBankS32 bankID;
    CAEAudioUtility::GetBankAndSoundFromScriptSlotAudioEvent(scriptID, bankID, soundID, -1);
    if (soundID < 0 || bankID < 0) {
        m_BankID  = SND_BANK_UNK;
        m_SoundID = -1;
        return false;
    } else {
        m_BankID  = bankID;
        m_SoundID = soundID;
        return true;
    }
}

// 0x4E4200
bool CAEPedSpeechAudioEntity::GetSexFromModel(eModelID model) {
    const auto* const mi = CModelInfo::GetModelInfo(model)->AsPedModelInfoPtr();
    assert(mi->m_nPedAudioType < PED_TYPE_NUM);
    if (mi->m_nPedAudioType == PED_TYPE_SPC) {
        return true;
    }
    m_IsFemale = notsa::contains({PED_TYPE_CIVFEMALE, PED_TYPE_PROSTITUTE}, mi->GetPedType());
    return true;
}

// 0x4E3F50
bool CAEPedSpeechAudioEntity::GetPedTalking() const {
    return m_IsInitialized && m_IsPlayingSpeech;
}

// 0x4E4170
bool CAEPedSpeechAudioEntity::GetVoiceAndTypeForSpecialPed(uint32 modelNameHash) {
    const auto idx = notsa::indexof(gSpecialPedVoiceNameLookup, modelNameHash);
    if (idx == -1) {
        return false;
    }
    std::tie(m_VoiceID, m_PedAudioType, m_IsFemale) = gSpecialPedVoiceLookup[idx];
    return true;
}

// notsa
ePainSpeechVoices CAEPedSpeechAudioEntity::GetPainVoice() const {
    if (m_PedAudioType == PED_TYPE_PLAYER) {
        return VOICE_PAIN_CARL;
    }
    return m_IsFemale
        ? VOICE_PAIN_FEMALE
        : VOICE_PAIN_MALE;
}

// 0x4E3520
void CAEPedSpeechAudioEntity::UpdateParameters(CAESound* sound, int16 playTime) {
    auto* const ped = m_pEntity->AsPed();
    auto* const speech = GetCurrentSpeech();
    if (playTime == -1) { // Sound has finished?
        if (m_PedAudioType == PED_TYPE_PLAYER) {
            s_bAPlayerSpeaking = false;
        }

        *speech = {
            .Status = CAEPedSpeechSlot::eStatus::FREE
        };

        m_Sound           = nullptr;
        m_SoundID         = -1;
        m_BankID          = SND_BANK_UNK;
        m_PedSpeechSlotID = -1;
        m_IsForcedAudible = false;

        if (s_bPedConversationHappening) {
            if (   this == &s_pConversationPed1->m_pedSpeech && m_PedSpeechSlotID == s_pConversationPedSlot1
                || this == &s_pConversationPed2->m_pedSpeech && m_PedSpeechSlotID == s_pConversationPedSlot2
            ) {
                speech->Status = CAEPedSpeechSlot::eStatus::RESERVED;
            }
        } else if (s_bPlayerConversationHappening) {
            if (this == &s_pPlayerConversationPed->m_pedSpeech && m_PedSpeechSlotID == s_pConversationPedSlot1) {
                speech->Status = CAEPedSpeechSlot::eStatus::RESERVED;
            }
        }
        if (auto* const tFacial = CTask::Cast<CTaskComplexFacial>(m_pEntity->AsPed()->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_FACIAL_COMPLEX))) {
            tFacial->StopAll();
        }
    } else { // Update sound
        speech->Status = CAEPedSpeechSlot::eStatus::PLAYING;
        if (ped->bIsTalking && ped->m_nBodypartToRemove == PED_NODE_HEAD) {
            sound->StopSound();
        } else if (!m_IsFrontend) {
            sound->SetPosition(ped->GetPosition());
        }
    }
}

// 0x4E4F70
void CAEPedSpeechAudioEntity::AddScriptSayEvent(eAudioEvents audioEvent, eAudioEvents scriptID, bool overrideSilence, bool isForceAudible, bool isFrontEnd) {
    if (audioEvent != AE_SCRIPT_SPEECH_PED) {
        return;
    }
    if (!m_IsInitialized || s_bAllSpeechDisabled) {
        return;
    }
    if (TheCamera.m_bWideScreenOn) {
        return;
    }
    if (m_IsSpeechDisabled && !overrideSilence) {
        return;
    }
    if (m_IsPlayingSpeech) {
        return;
    }
    if (CStreaming::IsVeryBusy()) {
        return;
    }
    const auto speechSlotID = m_PedAudioType == PED_TYPE_PLAYER
        ? !CAEPedSpeechAudioEntity::s_bAPlayerSpeaking || this->m_IsPlayingSpeech
            ? PLAYER_SPEECH_SLOT
            : -1
        : CanWePlayScriptedSpeech();
    if (speechSlotID == -1) {
        return;
    }
    if (!GetSoundAndBankIDsForScriptedSpeech(scriptID)) {
        return;
    }

    m_LastGCtx        = CTX_GLOBAL_UNK;
    m_PedSpeechSlotID = speechSlotID;
    m_IsFrontend      = isFrontEnd;

    m_IsForcedAudible = isForceAudible;
    if (const auto veh = m_pEntity->AsPed()->GetVehicleIfInOne()) {
        if (veh == FindPlayerVehicle()) {
            m_IsForcedAudible = true;
        }
    }

    m_EventVolume = GetDefaultVolume(AE_SPEECH_PED);
    if (m_PedAudioType == PED_TYPE_PLAYER) {
        m_EventVolume += 3.f;
    }

    m_IsPlayingSpeech = true;
    if (m_PedAudioType == PED_TYPE_PLAYER) {
        s_bAPlayerSpeaking = true;
    }

    LoadAndPlaySpeech();
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
    case 0:  return CanPedSayGlobalContext(CTX_GLOBAL_CONV_DISL_CAR);
    case 1:  return CanPedSayGlobalContext(CTX_GLOBAL_CONV_DISL_CLOTHES);
    case 2:  return CanPedSayGlobalContext(CTX_GLOBAL_CONV_DISL_HAIR);
    case 3:  return CanPedSayGlobalContext(CTX_GLOBAL_CONV_DISL_PHYS);
    case 4:  return CanPedSayGlobalContext(CTX_GLOBAL_CONV_DISL_SHOES);
    case 5:  return CanPedSayGlobalContext(CTX_GLOBAL_CONV_DISL_SMELL);
    case 6:  return CanPedSayGlobalContext(CTX_GLOBAL_CONV_DISL_TATTOO);
    case 7:  return CanPedSayGlobalContext(CTX_GLOBAL_CONV_DISL_WEATHER);
    case 8:
    case 9:  return true;
    default: return false;
    }
}

// 0x4E4130
int16 CAEPedSpeechAudioEntity::GetPedType() {
    return m_IsInitialized
        ? m_PedAudioType
        : PED_TYPE_UNK;
}

// 0x4E4150
bool CAEPedSpeechAudioEntity::IsPedFemaleForAudio() {
    return m_IsInitialized
        ? m_IsFemale
        : false;
}

// notsa
int32 CAEPedSpeechAudioEntity::GetFreeSpeechSlot() {
    const auto size = s_PedSpeechSlots.size() - 1; // Last one always reserved for the player
    for (size_t n = 0; n < size; n++) {
        const auto i = (s_NextSpeechSlot + n) % size;
        if (s_PedSpeechSlots[i].Status == CAEPedSpeechSlot::eStatus::FREE) {
            s_NextSpeechSlot = (uint16)((i + 1u) % size);
            return (int32)i;
        }
    }
    return -1;
}

uint32& CAEPedSpeechAudioEntity::GetNextPlayTimeRef(eGlobalSpeechContext gCtx) {
    return IsGlobalContextPain(gCtx)
        ? m_NextTimeCanSayPain[gCtx - CTX_GLOBAL_PAIN_START + 1]
        : gGlobalSpeechContextNextPlayTime[gCtx];
}

// notsa
const tGlobalSpeechContextInfo* CAEPedSpeechAudioEntity::GetGlobalSpeechContextInfo(eGlobalSpeechContext gCtx) {
    // Must use a loop because there are a few skipped values (TODO: Though I guess we could fix this?)
    for (const auto& e : gSpeechContextLookup) {
        if (e.GCtx == gCtx) {
            return &e;
        }
    }
    return nullptr;
}

// notsa
const tSpecificSpeechContextInfo* CAEPedSpeechAudioEntity::GetSpecificSpeechContextInfo(eSpecificSpeechContext sCtx, eGlobalSpeechContext gCtx, eAudioPedType pt, ePedSpeechVoiceS16 voice) {
    if (IsGlobalContextPain(gCtx)) {
        return &gPainSpeechLookup[sCtx][voice];
    }
    switch (pt) {
    case PED_TYPE_GEN:    return &gGenSpeechLookup[sCtx][voice];
    case PED_TYPE_EMG:    return &gEmgSpeechLookup[sCtx][voice];
    case PED_TYPE_PLAYER: return &gPlySpeechLookup[sCtx][voice];
    case PED_TYPE_GANG:   return &gGngSpeechLookup[sCtx][voice];
    case PED_TYPE_GFD:    return &gGfdSpeechLookup[sCtx][voice];
    default:              return nullptr;
    }
}

eSoundBank CAEPedSpeechAudioEntity::GetVoiceSoundBank(eGlobalSpeechContext gCtx, eAudioPedType pt, ePedSpeechVoiceS16 voice) {
    if (IsGlobalContextPain(gCtx)) {
        return gPainVoiceToBankLookup[voice];
    }
    switch (pt) {
    case PED_TYPE_GEN:    return gGenSpeechVoiceToBankLookup[voice];
    case PED_TYPE_EMG:    return gEmgSpeechVoiceToBankLookup[voice];
    case PED_TYPE_PLAYER: return gPlySpeechVoiceToBankLookup[voice];
    case PED_TYPE_GANG:   return gGngSpeechVoiceToBankLookup[voice];
    case PED_TYPE_GFD:    return gGfdSpeechVoiceToBankLookup[voice];
    default:              NOTSA_UNREACHABLE();
    }
}
