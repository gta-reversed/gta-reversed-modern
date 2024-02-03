#include "StdInc.h"

#include "AEPedSpeechAudioEntity.h"
#include "AEAudioUtility.h"
#include "PedClothesDesc.h"
#include <AEAudioHardware.h>

int16& CAEPedSpeechAudioEntity::s_nCJWellDressed = *(int16*)0xB613D0;
int16& CAEPedSpeechAudioEntity::s_nCJFat = *(int16*)0xB613D4;
int16& CAEPedSpeechAudioEntity::s_nCJGangBanging = *(int16*)0xB613D8;
int32& CAEPedSpeechAudioEntity::s_nCJBasicMood = *(int32*)0xB613DC;
int32& CAEPedSpeechAudioEntity::s_nCJMoodOverrideTime = *(int32*)0xB613E0;
bool& CAEPedSpeechAudioEntity::s_bForceAudible = *(bool*)0xB613E4;
bool& CAEPedSpeechAudioEntity::s_bAPlayerSpeaking = *(bool*)0xB613E5;
bool& CAEPedSpeechAudioEntity::s_bAllSpeechDisabled = *(bool*)0xB613E6;
int16& CAEPedSpeechAudioEntity::s_ConversationLength = *(int16*)0xB613E8;
int16 (&CAEPedSpeechAudioEntity::s_Conversation)[8] = *(int16(*)[8])0xB613EC;
bool& CAEPedSpeechAudioEntity::s_bPlayerConversationHappening = *(bool*)0xB613FC;
bool& CAEPedSpeechAudioEntity::s_bPedConversationHappening = *(bool*)0xB613FD;
CPed*& CAEPedSpeechAudioEntity::s_pPlayerConversationPed = *(CPed**)0xB61400;
int16& CAEPedSpeechAudioEntity::s_pConversationPedSlot2 = *(int16*)0xB61404;
int16& CAEPedSpeechAudioEntity::s_pConversationPedSlot1 = *(int16*)0xB61408;
CPed*& CAEPedSpeechAudioEntity::s_pConversationPed2 = *(CPed**)0xB6140C;
CPed*& CAEPedSpeechAudioEntity::s_pConversationPed1 = *(CPed**)0xB61410;
int16& CAEPedSpeechAudioEntity::s_NextSpeechSlot = *(int16*)0xB61414;
static inline auto& gGlobalSpeechContextNextPlayTime = *reinterpret_cast<std::array<uint32, 360>*>(0xB61670);
static inline auto& gSpeechContextLookup = *reinterpret_cast<notsa::mdarray<int16, 8, 360>*>(0x8C6A68);

void CAEPedSpeechAudioEntity::InjectHooks() {
    RH_ScopedVirtualClass(CAEPedSpeechAudioEntity, 0x85F310, 8);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Constructor, 0x4E4F10);
    RH_ScopedInstall(IsGlobalContextImportantForInterupting, 0x4E4600);
    RH_ScopedInstall(IsGlobalContextUberImportant, 0x4E46F0);
    RH_ScopedInstall(GetNextMoodToUse, 0x4E4700);
    RH_ScopedInstall(GetVoiceForMood, 0x4E4760);
    RH_ScopedInstall(CanWePlayScriptedSpeech, 0x4E4950);
    RH_ScopedInstall(GetSpeechContextVolumeOffset, 0x4E4AE0, { .reversed = false });
    RH_ScopedInstall(RequestPedConversation, 0x4E50E0, { .reversed = false });
    RH_ScopedInstall(ReleasePedConversation, 0x4E52A0, { .reversed = false });
    RH_ScopedInstall(GetCurrentCJMood, 0x4E53B0, { .reversed = false });
    RH_ScopedInstall(StaticInitialise, 0x5B98C0, { .reversed = true });
    RH_ScopedInstall(GetSpecificSpeechContext, 0x4E4470, { .reversed = false });
    RH_ScopedInstall(Service, 0x4E3710, { .reversed = false });
    RH_ScopedInstall(Reset, 0x4E37B0);
    RH_ScopedInstall(ReservePedConversationSpeechSlots, 0x4E37F0, { .reversed = false });
    RH_ScopedInstall(ReservePlayerConversationSpeechSlot, 0x4E3870, { .reversed = false });
    RH_ScopedInstall(RequestPlayerConversation, 0x4E38C0);
    RH_ScopedInstall(ReleasePlayerConversation, 0x4E3960, { .reversed = false });
    RH_ScopedInstall(SetUpConversation, 0x4E3A00, { .reversed = false });
    RH_ScopedInstall(GetAudioPedType, 0x4E3C60);
    RH_ScopedInstall(GetVoice, 0x4E3CD0, { .reversed = false });
    RH_ScopedInstall(DisableAllPedSpeech, 0x4E3EB0);
    RH_ScopedInstall(IsGlobalContextPain, 0x4E44F0, { .reversed = true });
    RH_ScopedInstall(SetCJMood, 0x4E3ED0, { .reversed = false });
    RH_ScopedInstall(EnableAllPedSpeech, 0x4E3EC0);
    RH_ScopedInstall(IsCJDressedInForGangSpeech, 0x4E4270, { .reversed = true });
    RH_ScopedInstall(GetSexForSpecialPed, 0x4E4260);
    RH_ScopedInstall(IsGlobalContextImportantForWidescreen, 0x4E46B0, { .reversed = true });
    RH_ScopedInstall(GetRepeatTime, 0x4E47E0, { .reversed = false });
    RH_ScopedInstall(LoadAndPlaySpeech, 0x4E4840, { .reversed = false });
    RH_ScopedInstall(GetNumSlotsPlayingContext, 0x4E49B0, { .reversed = true });
    RH_ScopedInstall(GetNextPlayTime, 0x4E49E0, { .reversed = true });
    RH_ScopedInstall(SetNextPlayTime, 0x4E4A20, { .reversed = true });
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
    RH_ScopedInstall(EnablePedSpeech, 0x4E3F70, { .reversed = false });
    RH_ScopedInstall(EnablePedSpeechForScriptSpeech, 0x4E3F90, { .reversed = false });
    RH_ScopedInstall(StopCurrentSpeech, 0x4E3FB0, { .reversed = false });
    RH_ScopedInstall(GetSoundAndBankIDsForScriptedSpeech, 0x4E4400, { .reversed = false });
    RH_ScopedInstall(GetSexFromModel, 0x4E4200, { .reversed = false });
    RH_ScopedInstall(GetPedTalking, 0x4E3F50, { .reversed = false });
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

// 0x4E4F10
CAEPedSpeechAudioEntity::CAEPedSpeechAudioEntity() : CAEAudioEntity() {
    f90                         = false;
    m_nVoiceType                = 0;
    m_bTalking                  = false;
    m_bSpeechDisabled           = false;
    m_bSpeechForScriptsDisabled = false;
    m_pSound                    = nullptr;
    m_nSoundId                  = -1;
    m_nBankId                   = -1;
    m_nPedSpeechSlotIndex       = -1;
    m_fVoiceVolume              = -100.0f;
    m_nCurrentPhraseId          = -1;
}

// 0x4E4600
bool __stdcall CAEPedSpeechAudioEntity::IsGlobalContextImportantForInterupting(int16 globalCtx) {
    // return plugin::CallAndReturn<int8, 0x4E4600, int16>(a1);
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
int16 __stdcall CAEPedSpeechAudioEntity::GetNextMoodToUse(int16 lastMood) {
    switch (lastMood) {
    case 0:
    case 7:
        return 1;
    case 6:
        return 0;
    case 8:
        return 4;
    default:
        return 5;
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
    for (auto i = 0; i < 5; i++) {
        const auto slot = (s_NextSpeechSlot + i) % 5;
        if (s_PedSpeechSlots[slot].m_nState)
            continue;

        s_NextSpeechSlot = slot;
        return slot;
    }
    return -1;
}

// 0x4E4AE0
float CAEPedSpeechAudioEntity::GetSpeechContextVolumeOffset(int16 a1) {
    return plugin::CallAndReturn<float, 0x4E4AE0, int16>(a1);
}

// 0x4E50E0
int8 CAEPedSpeechAudioEntity::RequestPedConversation(CPed* ped1, CPed* ped2) {
    return plugin::CallAndReturn<int8, 0x4E50E0, CPed*, CPed*>(ped1, ped2);
}

// 0x4E52A0
void CAEPedSpeechAudioEntity::ReleasePedConversation() {
    plugin::Call<0x4E52A0>();
}

// 0x4E53B0
int16 CAEPedSpeechAudioEntity::GetCurrentCJMood() {
    return plugin::CallAndReturn<int16, 0x4E53B0>();
}

// 0x5B98C0
void CAEPedSpeechAudioEntity::StaticInitialise() {
    rng::for_each(s_PedSpeechSlots, &tSpeechSlot::Reset);
    rng::for_each(s_PhraseMemory, &tPhraseMemory::Reset);
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
int16 CAEPedSpeechAudioEntity::GetSpecificSpeechContext(int16 a1, int16 voiceType) {
    return plugin::CallAndReturn<int16, 0x4E4470, int16, int16>(a1, voiceType);
}

// 0x4E3710
void CAEPedSpeechAudioEntity::Service() {
    plugin::Call<0x4E3710>();
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

    if (ped->m_pedSpeech.m_bSpeechForScriptsDisabled || ped->m_pedSpeech.m_bSpeechDisabled) {
        return false;
    }

    const auto player = FindPlayerPed();
    if (!player || player->m_pedSpeech.m_bSpeechDisabled || player->m_pedSpeech.m_bSpeechForScriptsDisabled) {
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
    return globalCtx > 339 && globalCtx < 359;
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
        eClothesTexturePart clothesPart;
        const char* textureName;
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

    if (!FindPlayerPed(PED_TYPE_PLAYER1))
        return false;

    if (CGameLogic::FindCityClosestToPoint(FindPlayerCoors()) != LEVEL_NAME_LOS_SANTOS)
        return false;

    return rng::any_of(GANG_SPEECH_CLOTHES, [pcd = FindPlayerPed()->GetClothesDesc()](auto& gc) {
        return pcd->m_anTextureKeys[gc.clothesPart] == CKeyGen::GetUppercaseKey(gc.textureName);
    });
}

// 0x4E4260
int8 CAEPedSpeechAudioEntity::GetSexForSpecialPed(uint32 a1) {
    return 1;
}

// Methods
// 0x4E46B0
bool CAEPedSpeechAudioEntity::IsGlobalContextImportantForWidescreen(int16 globalCtx) {
    return notsa::contains<int>({4, 2}, m_nVoiceType) || notsa::contains<int>({13, 15, 116}, globalCtx);
}

// 0x4E47E0
int32 CAEPedSpeechAudioEntity::GetRepeatTime(int16 a1) {
    return plugin::CallMethodAndReturn<int32, 0x4E47E0, CAEPedSpeechAudioEntity*, int16>(this, a1);
}

// 0x4E4840
void CAEPedSpeechAudioEntity::LoadAndPlaySpeech(uint32 offset) {
    //plugin::CallMethod<0x4E4840>(this, offset);
    auto& currSpeech = GetCurrentPedSpeech();
    if (currSpeech.m_nState != 0 && currSpeech.m_nState != 4)
        return;

    AEAudioHardware.LoadSound(m_nBankId, m_nSoundId, m_nPedSpeechSlotIndex + 20); // TODO: Helper
    currSpeech.m_nState = 1;
    currSpeech.m_nBankId = m_nBankId;
    currSpeech.m_nSoundId = m_nSoundId;
    currSpeech.m_PedSpeechAE = this;
    currSpeech.m_nTime = CTimer::GetTimeInMS() + offset;
    currSpeech.m_nVoiceType = m_nVoiceType;
    currSpeech.m_nPhraseId = m_nCurrentPhraseId;
    // byte_B61C50[28 * m_nPedSpeechSlotIndex] = field_9C;
}

// 0x4E49B0
int32 CAEPedSpeechAudioEntity::GetNumSlotsPlayingContext(int16 context) {
    return rng::count_if(s_PedSpeechSlots, [&](tSpeechSlot& speech) {
        return speech.m_nState && speech.m_nPhraseId == context;
    });
}

// 0x4E49E0
uint32 CAEPedSpeechAudioEntity::GetNextPlayTime(int16 globalCtx) {
    if (globalCtx > 359) // todo: const
        return 0;

    if (IsGlobalContextPain(globalCtx))
        return field_B4[globalCtx - 340];

    return gGlobalSpeechContextNextPlayTime[globalCtx];
}

// 0x4E4A20
void CAEPedSpeechAudioEntity::SetNextPlayTime(int16 globalCtx) {
    // plugin::CallMethod<0x4E4A20>(this, globalCtx);

    if (globalCtx > 359)
        return;

    for (auto& lookup : gSpeechContextLookup) {
        if (lookup[0] == -1)
            break;

        if (lookup[0] != globalCtx)
            continue;

        const auto playTime = lookup[6] + CAEAudioUtility::GetRandomNumberInRange(1, 1000);
        auto& ctxNextPlayTime = [&]() -> uint32& {
            if (IsGlobalContextPain(globalCtx))
                return field_B4[globalCtx - 340];
            else
                return gGlobalSpeechContextNextPlayTime[globalCtx];
        }() = CTimer::GetTimeInMS() + playTime;
        return;
    }
}

// 0x4E56D0
void CAEPedSpeechAudioEntity::DisablePedSpeech(int16 a1) {
    if (f90) {
        m_bSpeechDisabled = true;
        if (a1)
            StopCurrentSpeech();
    }
}

// 0x4E5700
void CAEPedSpeechAudioEntity::DisablePedSpeechForScriptSpeech(int16 a1) {
    if (f90) {
        m_bSpeechForScriptsDisabled = true;
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
    CPedModelInfo* info = CModelInfo::GetModelInfo(modelId)->AsPedModelInfoPtr();
    if (info->m_nPedAudioType < 0 || info->m_nPedAudioType >= 6)
        return 0;

    if (info->m_nPedAudioType == 5) // PED_TYPE_SPC, see GetAudioPedType
        return GetVoiceAndTypeForSpecialPed(info->m_nKey);

    m_nVoiceId = info->m_nVoiceId;
    if (m_nVoiceId < 0)
        return 0;

    info->IncrementVoice();
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
    if (f90)
        m_bSpeechDisabled = false;
}

// 0x4E3F90
void CAEPedSpeechAudioEntity::EnablePedSpeechForScriptSpeech() {
    if (f90)
        m_bSpeechForScriptsDisabled = false;
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
    return f90 && m_bTalking;
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
    return m_nVoiceId;
}

// 0x4E5800
bool CAEPedSpeechAudioEntity::WillPedChatAboutTopic(int16 topic) {
    switch (topic) {
    case 0:
        return CanPedSayGlobalContext(48);
    case 1:
        return CanPedSayGlobalContext(49);
    case 2:
        return CanPedSayGlobalContext(50);
    case 3:
        return CanPedSayGlobalContext(51);
    case 4:
        return CanPedSayGlobalContext(52);
    case 5:
        return CanPedSayGlobalContext(53);
    case 6:
        return CanPedSayGlobalContext(54);
    case 7:
        return CanPedSayGlobalContext(55);
    case 8:
    case 9:
        return true;
    default:
        return false;
    }
}

// 0x4E4130
int16 CAEPedSpeechAudioEntity::GetPedType() {
    if (f90)
        return m_nVoiceType;
    else
        return -1;
}

// 0x4E4150
bool CAEPedSpeechAudioEntity::IsPedFemaleForAudio() {
    if (f90)
        return m_nVoiceGender;
    else
        return false;
}

// 0x4E4F10
CAEPedSpeechAudioEntity* CAEPedSpeechAudioEntity::Constructor() {
    this->CAEPedSpeechAudioEntity::CAEPedSpeechAudioEntity();
    return this;
}

// 0x4E3520// 0x4E4F70// 0x4E5670// 0x4E5CD0// 0x4E4120// 0x4E5800// 0x4E4130// 0x4E4150