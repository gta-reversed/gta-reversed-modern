#include "StdInc.h"

#include "StdInc.h"

#include "AEPedSpeechAudioEntity.h"

int16& CAEPedSpeechAudioEntity::s_nCJWellDressed = *(int16*)0xB613D0;
int16& CAEPedSpeechAudioEntity::s_nCJFat = *(int16*)0xB613D4;
int16& CAEPedSpeechAudioEntity::s_nCJGangBanging = *(int16*)0xB613D8;
int32& CAEPedSpeechAudioEntity::s_nCJBasicMood = *(int32*)0xB613DC;
int32& CAEPedSpeechAudioEntity::s_nCJMoodOverrideTime = *(int32*)0xB613E0;
bool& CAEPedSpeechAudioEntity::s_bForceAudible = *(bool*)0xB613E4;
bool& CAEPedSpeechAudioEntity::s_bAPlayerSpeaking = *(bool*)0xB613E5;
bool& CAEPedSpeechAudioEntity::s_bAllSpeechDisabled = *(bool*)0xB613E6;
int16& CAEPedSpeechAudioEntity::s_ConversationLength = *(int16*)0xB613E8;
// int16[int8]& CAEPedSpeechAudioEntity::s_Conversation = *(int16[int8]*)0xB613EC;
bool& CAEPedSpeechAudioEntity::s_bPlayerConversationHappening = *(bool*)0xB613FC;
bool& CAEPedSpeechAudioEntity::s_bPedConversationHappening = *(bool*)0xB613FD;
CPed*& CAEPedSpeechAudioEntity::s_pPlayerConversationPed = *(CPed**)0xB61400;
int16& CAEPedSpeechAudioEntity::s_pConversationPedSlot2 = *(int16*)0xB61404;
int16& CAEPedSpeechAudioEntity::s_pConversationPedSlot1 = *(int16*)0xB61408;
CPed*& CAEPedSpeechAudioEntity::s_pConversationPed2 = *(CPed**)0xB6140C;
CPed*& CAEPedSpeechAudioEntity::s_pConversationPed1 = *(CPed**)0xB61410;
int16& CAEPedSpeechAudioEntity::s_NextSpeechSlot = *(int16*)0xB61414;
int16& CAEPedSpeechAudioEntity::s_PhraseMemory = *(int16*)0xB61418;
// CAEPedSpeechAudioEntity::Slot (&CAEPedSpeechAudioEntity::s_PedSpeechSlots)[6] = *(CAEPedSpeechAudioEntity::Slot(*)[6])0xB61C38;

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
int8 CAEPedSpeechAudioEntity::IsGlobalContextImportantForInterupting(int16 a1) {
    return plugin::CallAndReturn<int8, 0x4E4600, int16>(a1);
}

// 0x4E46F0
int8 CAEPedSpeechAudioEntity::IsGlobalContextUberImportant(int16 a1) {
    return plugin::CallAndReturn<int8, 0x4E46F0, int16>(a1);
}

// 0x4E4700
int16 CAEPedSpeechAudioEntity::GetNextMoodToUse(int16 a1) {
    return plugin::CallAndReturn<int16, 0x4E4700, int16>(a1);
}

// 0x4E4760
int32 CAEPedSpeechAudioEntity::GetVoiceForMood(int16 a1) {
    return plugin::CallAndReturn<int32, 0x4E4760, int16>(a1);
}

// 0x4E4950
int16 CAEPedSpeechAudioEntity::CanWePlayScriptedSpeech() {
    return plugin::CallAndReturn<int16, 0x4E4950>();
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
    plugin::Call<0x5B98C0>();
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
    plugin::Call<0x4E37B0>();
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

    if (   ped->m_pedSpeech.m_bSpeechForScriptsDisabled
        || ped->m_pedSpeech.m_bSpeechDisabled
        || !FindPlayerPed(-1)
        || FindPlayerPed(-1)->m_pedSpeech.m_bSpeechDisabled
        || FindPlayerPed(-1)->m_pedSpeech.m_bSpeechForScriptsDisabled
        || s_bPedConversationHappening
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

// todo: dev from 2003 and maybe wrong
// 0x4E3C60
int16 CAEPedSpeechAudioEntity::GetAudioPedType(Const char* name) {
    constexpr const char* aAudioPedTypeNames[] = {
        "PED_TYPE_GEN",
        "PED_TYPE_EMG",
        "PED_TYPE_PLAYER",
        "PED_TYPE_GANG",
        "PED_TYPE_GFD",
        "PED_TYPE_SPC"
    };

    auto index = 0;
    for (const auto& pedName : aAudioPedTypeNames) {
        if (strcmp(name, pedName) != 0) {
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
bool CAEPedSpeechAudioEntity::IsGlobalContextPain(int16 a1) {
    return plugin::CallAndReturn<bool, 0x4E44F0, CAEPedSpeechAudioEntity*, int16>(this, a1);
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
    return plugin::CallAndReturn<bool, 0x4E4270>();
}

// 0x4E4260
int8 CAEPedSpeechAudioEntity::GetSexForSpecialPed(uint32 a1) {
    return 1;
}

// Methods
// 0x4E46B0
bool CAEPedSpeechAudioEntity::IsGlobalContextImportantForWidescreen(int16 a1) {
    return plugin::CallMethodAndReturn<bool, 0x4E46B0, CAEPedSpeechAudioEntity*, int16>(this, a1);
}

// 0x4E47E0
int32 CAEPedSpeechAudioEntity::GetRepeatTime(int16 a1) {
    return plugin::CallMethodAndReturn<int32, 0x4E47E0, CAEPedSpeechAudioEntity*, int16>(this, a1);
}

// 0x4E4840
void CAEPedSpeechAudioEntity::LoadAndPlaySpeech(uint32 a2) {
    plugin::CallMethod<0x4E4840, uint32>(a2);
}

// 0x4E49B0
int32 CAEPedSpeechAudioEntity::GetNumSlotsPlayingContext(int16 a2) {
    return plugin::CallMethodAndReturn<int32, 0x4E49B0, CAEPedSpeechAudioEntity*, int16>(this, a2);
}

// 0x4E49E0
int32 CAEPedSpeechAudioEntity::GetNextPlayTime(int16 a2) {
    return plugin::CallMethodAndReturn<int32, 0x4E49E0, int16>(a2);
}

// 0x4E4A20
void CAEPedSpeechAudioEntity::SetNextPlayTime(int16 a2) {
    plugin::CallMethod<0x4E4A20, int16>(a2);
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
    return plugin::CallMethodAndReturn<int8, 0x4E5730, int16>(a2);
}

// 0x4E58C0
int8 CAEPedSpeechAudioEntity::GetVoiceAndTypeFromModel(eModelID modelId) {
    CPedModelInfo* info = CModelInfo::GetModelInfo(modelId)->AsPedModelInfoPtr();
    m_nVoiceType = info->m_nPedAudioType;
    if (m_nVoiceType < 0 || m_nVoiceType >= 6)
        return 0;

    if (info->m_nPedAudioType == 5)
        return GetVoiceAndTypeForSpecialPed(info->m_nKey);

    m_nVoiceId = info->m_nVoiceId;
    if (m_nVoiceId < 0)
        return 0;

    info->IncrementVoice();
    return 1;
}

// 0x4E5920
int16 CAEPedSpeechAudioEntity::GetSoundAndBankIDs(int16 phraseId, int16* a3) {
    return plugin::CallMethodAndReturn<int16, 0x4E5920, int16, int16*>(phraseId, a3);
}

// 0x4E5F10
bool CAEPedSpeechAudioEntity::CanWePlayGlobalSpeechContext(int16 a2) {
    return plugin::CallMethodAndReturn<bool, 0x4E5F10, int16>(a2);
}

// 0x4E6550
int16 CAEPedSpeechAudioEntity::AddSayEvent(int32 a2, int16 phraseId, uint32 a4, float a5, uint8 a6, uint8 a7, uint8 a8) {
    return plugin::CallMethodAndReturn<int16, 0x4E6550, int32, int16, uint32, float, uint8, uint8, uint8>(a2, phraseId, a4, a5, a6, a7, a8);
}

// 0x4E68D0
void CAEPedSpeechAudioEntity::Initialise(CEntity* ped) {
    plugin::CallMethod<0x4E68D0, CEntity*>(ped);
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
    return plugin::CallMethodAndReturn<int8, 0x4E4400, int32>(a2);
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
    return plugin::CallMethodAndReturn<int8, 0x4E4170, uint32>(modelNameHash);
}

// Virtual methods// 0x4E3520
void CAEPedSpeechAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    UpdateParameters_Reversed(sound, curPlayPos);
}

// 0x4E4F70
void CAEPedSpeechAudioEntity::AddScriptSayEvent(int32 a1, int32 a2, uint8 a3, uint8 a4, uint8 a5) {
    AddScriptSayEvent_Reversed(a1, a2, a3, a4, a5);
}

// 0x4E5670
void CAEPedSpeechAudioEntity::Terminate() {
    Terminate_Reversed();
}

// 0x4E5CD0
void CAEPedSpeechAudioEntity::PlayLoadedSound() {
    PlayLoadedSound_Reversed();
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

void CAEPedSpeechAudioEntity::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CAEPedSpeechAudioEntity", "CAEPedSpeechAudioEntity", 0x4E4F10, &CAEPedSpeechAudioEntity::Constructor);
    // Install("CAEPedSpeechAudioEntity", "IsGlobalContextImportantForInterupting", 0x4E4600, &CAEPedSpeechAudioEntity::IsGlobalContextImportantForInterupting);
    // Install("CAEPedSpeechAudioEntity", "IsGlobalContextUberImportant", 0x4E46F0, &CAEPedSpeechAudioEntity::IsGlobalContextUberImportant);
    // Install("CAEPedSpeechAudioEntity", "GetNextMoodToUse", 0x4E4700, &CAEPedSpeechAudioEntity::GetNextMoodToUse);
    // Install("CAEPedSpeechAudioEntity", "GetVoiceForMood", 0x4E4760, &CAEPedSpeechAudioEntity::GetVoiceForMood);
    // Install("CAEPedSpeechAudioEntity", "CanWePlayScriptedSpeech", 0x4E4950, &CAEPedSpeechAudioEntity::CanWePlayScriptedSpeech);
    // Install("CAEPedSpeechAudioEntity", "GetSpeechContextVolumeOffset", 0x4E4AE0, &CAEPedSpeechAudioEntity::GetSpeechContextVolumeOffset);
    // Install("CAEPedSpeechAudioEntity", "RequestPedConversation", 0x4E50E0, &CAEPedSpeechAudioEntity::RequestPedConversation);
    // Install("CAEPedSpeechAudioEntity", "ReleasePedConversation", 0x4E52A0, &CAEPedSpeechAudioEntity::ReleasePedConversation);
    // Install("CAEPedSpeechAudioEntity", "GetCurrentCJMood", 0x4E53B0, &CAEPedSpeechAudioEntity::GetCurrentCJMood);
    // Install("CAEPedSpeechAudioEntity", "StaticInitialise", 0x5B98C0, &CAEPedSpeechAudioEntity::StaticInitialise);
    // Install("CAEPedSpeechAudioEntity", "GetSpecificSpeechContext", 0x4E4470, &CAEPedSpeechAudioEntity::GetSpecificSpeechContext);
    // Install("CAEPedSpeechAudioEntity", "Service", 0x4E3710, &CAEPedSpeechAudioEntity::Service);
    // Install("CAEPedSpeechAudioEntity", "Reset", 0x4E37B0, &CAEPedSpeechAudioEntity::Reset);
    // Install("CAEPedSpeechAudioEntity", "ReservePedConversationSpeechSlots", 0x4E37F0, &CAEPedSpeechAudioEntity::ReservePedConversationSpeechSlots);
    // Install("CAEPedSpeechAudioEntity", "ReservePlayerConversationSpeechSlot", 0x4E3870, &CAEPedSpeechAudioEntity::ReservePlayerConversationSpeechSlot);
    Install("CAEPedSpeechAudioEntity", "RequestPlayerConversation", 0x4E38C0, &CAEPedSpeechAudioEntity::RequestPlayerConversation);
    // Install("CAEPedSpeechAudioEntity", "ReleasePlayerConversation", 0x4E3960, &CAEPedSpeechAudioEntity::ReleasePlayerConversation);
    // Install("CAEPedSpeechAudioEntity", "SetUpConversation", 0x4E3A00, &CAEPedSpeechAudioEntity::SetUpConversation);
    // Install("CAEPedSpeechAudioEntity", "GetAudioPedType", 0x4E3C60, &CAEPedSpeechAudioEntity::GetAudioPedType);
    // Install("CAEPedSpeechAudioEntity", "GetVoice", 0x4E3CD0, &CAEPedSpeechAudioEntity::GetVoice);
    Install("CAEPedSpeechAudioEntity", "DisableAllPedSpeech", 0x4E3EB0, &CAEPedSpeechAudioEntity::DisableAllPedSpeech);
    // Install("CAEPedSpeechAudioEntity", "IsGlobalContextPain", 0x4E44F0, &CAEPedSpeechAudioEntity::IsGlobalContextPain);
    // Install("CAEPedSpeechAudioEntity", "SetCJMood", 0x4E3ED0, &CAEPedSpeechAudioEntity::SetCJMood);
    Install("CAEPedSpeechAudioEntity", "EnableAllPedSpeech", 0x4E3EC0, &CAEPedSpeechAudioEntity::EnableAllPedSpeech);
    // Install("CAEPedSpeechAudioEntity", "IsCJDressedInForGangSpeech", 0x4E4270, &CAEPedSpeechAudioEntity::IsCJDressedInForGangSpeech);
    Install("CAEPedSpeechAudioEntity", "GetSexForSpecialPed", 0x4E4260, &CAEPedSpeechAudioEntity::GetSexForSpecialPed);
    // Install("CAEPedSpeechAudioEntity", "IsGlobalContextImportantForWidescreen", 0x4E46B0, &CAEPedSpeechAudioEntity::IsGlobalContextImportantForWidescreen);
    // Install("CAEPedSpeechAudioEntity", "GetRepeatTime", 0x4E47E0, &CAEPedSpeechAudioEntity::GetRepeatTime);
    // Install("CAEPedSpeechAudioEntity", "LoadAndPlaySpeech", 0x4E4840, &CAEPedSpeechAudioEntity::LoadAndPlaySpeech);
    // Install("CAEPedSpeechAudioEntity", "GetNumSlotsPlayingContext", 0x4E49B0, &CAEPedSpeechAudioEntity::GetNumSlotsPlayingContext);
    // Install("CAEPedSpeechAudioEntity", "GetNextPlayTime", 0x4E49E0, &CAEPedSpeechAudioEntity::GetNextPlayTime);
    // Install("CAEPedSpeechAudioEntity", "SetNextPlayTime", 0x4E4A20, &CAEPedSpeechAudioEntity::SetNextPlayTime);
    Install("CAEPedSpeechAudioEntity", "DisablePedSpeech", 0x4E56D0, &CAEPedSpeechAudioEntity::DisablePedSpeech);
    Install("CAEPedSpeechAudioEntity", "DisablePedSpeechForScriptSpeech", 0x4E5700, &CAEPedSpeechAudioEntity::DisablePedSpeechForScriptSpeech);
    // Install("CAEPedSpeechAudioEntity", "CanPedSayGlobalContext", 0x4E5730, &CAEPedSpeechAudioEntity::CanPedSayGlobalContext);
    Install("CAEPedSpeechAudioEntity", "GetVoiceAndTypeFromModel", 0x4E58C0, &CAEPedSpeechAudioEntity::GetVoiceAndTypeFromModel);
    // Install("CAEPedSpeechAudioEntity", "GetSoundAndBankIDs", 0x4E5920, &CAEPedSpeechAudioEntity::GetSoundAndBankIDs);
    // Install("CAEPedSpeechAudioEntity", "CanWePlayGlobalSpeechContext", 0x4E5F10, &CAEPedSpeechAudioEntity::CanWePlayGlobalSpeechContext);
    // Install("CAEPedSpeechAudioEntity", "AddSayEvent", 0x4E6550, &CAEPedSpeechAudioEntity::AddSayEvent);
    // Install("CAEPedSpeechAudioEntity", "Initialise", 0x4E68D0, &CAEPedSpeechAudioEntity::Initialise);
    // Install("CAEPedSpeechAudioEntity", "CanPedHoldConversation", 0x4E69E0, &CAEPedSpeechAudioEntity::CanPedHoldConversation);
    // Install("CAEPedSpeechAudioEntity", "IsGlobalContextImportantForStreaming", 0x4E4510, &CAEPedSpeechAudioEntity::IsGlobalContextImportantForStreaming);
    // Install("CAEPedSpeechAudioEntity", "EnablePedSpeech", 0x4E3F70, &CAEPedSpeechAudioEntity::EnablePedSpeech);
    // Install("CAEPedSpeechAudioEntity", "EnablePedSpeechForScriptSpeech", 0x4E3F90, &CAEPedSpeechAudioEntity::EnablePedSpeechForScriptSpeech);
    // Install("CAEPedSpeechAudioEntity", "StopCurrentSpeech", 0x4E3FB0, &CAEPedSpeechAudioEntity::StopCurrentSpeech);
    // Install("CAEPedSpeechAudioEntity", "GetSoundAndBankIDsForScriptedSpeech", 0x4E4400, &CAEPedSpeechAudioEntity::GetSoundAndBankIDsForScriptedSpeech);
    // Install("CAEPedSpeechAudioEntity", "GetSexFromModel", 0x4E4200, &CAEPedSpeechAudioEntity::GetSexFromModel);
    // Install("CAEPedSpeechAudioEntity", "GetPedTalking", 0x4E3F50, &CAEPedSpeechAudioEntity::GetPedTalking);
    // Install("CAEPedSpeechAudioEntity", "GetVoiceAndTypeForSpecialPed", 0x4E4170, &CAEPedSpeechAudioEntity::GetVoiceAndTypeForSpecialPed);
    // Install("CAEPedSpeechAudioEntity", "UpdateParameters", 0x4E3520, &CAEPedSpeechAudioEntity::UpdateParameters_Reversed);
    // Install("CAEPedSpeechAudioEntity", "AddScriptSayEvent", 0x4E4F70, &CAEPedSpeechAudioEntity::AddScriptSayEvent_Reversed);
    // Install("CAEPedSpeechAudioEntity", "Terminate", 0x4E5670, &CAEPedSpeechAudioEntity::Terminate_Reversed);
    // Install("CAEPedSpeechAudioEntity", "PlayLoadedSound", 0x4E5CD0, &CAEPedSpeechAudioEntity::PlayLoadedSound_Reversed);
    Install("CAEPedSpeechAudioEntity", "GetAllocatedVoice", 0x4E4120, &CAEPedSpeechAudioEntity::GetAllocatedVoice_Reversed);
    Install("CAEPedSpeechAudioEntity", "WillPedChatAboutTopic", 0x4E5800, &CAEPedSpeechAudioEntity::WillPedChatAboutTopic_Reversed);
    Install("CAEPedSpeechAudioEntity", "GetPedType", 0x4E4130, &CAEPedSpeechAudioEntity::GetPedType_Reversed);
    Install("CAEPedSpeechAudioEntity", "IsPedFemaleForAudio", 0x4E4150, &CAEPedSpeechAudioEntity::IsPedFemaleForAudio_Reversed);
}

// 0x4E4F10
CAEPedSpeechAudioEntity* CAEPedSpeechAudioEntity::Constructor() {
    this->CAEPedSpeechAudioEntity::CAEPedSpeechAudioEntity();
    return this;
}

// 0x4E3520
void CAEPedSpeechAudioEntity::UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos) {
    CAEPedSpeechAudioEntity::UpdateParameters(sound, curPlayPos);
}

// 0x4E4F70
void CAEPedSpeechAudioEntity::AddScriptSayEvent_Reversed(int32 a1, int32 a2, uint8 a3, uint8 a4, uint8 a5) {
    CAEPedSpeechAudioEntity::AddScriptSayEvent(a1, a2, a3, a4, a5);
}

// 0x4E5670
void CAEPedSpeechAudioEntity::Terminate_Reversed() {
    CAEPedSpeechAudioEntity::Terminate();
}

// 0x4E5CD0
void CAEPedSpeechAudioEntity::PlayLoadedSound_Reversed() {
    CAEPedSpeechAudioEntity::PlayLoadedSound();
}

// 0x4E4120
int16 CAEPedSpeechAudioEntity::GetAllocatedVoice_Reversed() {
    return CAEPedSpeechAudioEntity::GetAllocatedVoice();
}

// 0x4E5800
bool CAEPedSpeechAudioEntity::WillPedChatAboutTopic_Reversed(int16 topic) {
    return CAEPedSpeechAudioEntity::WillPedChatAboutTopic(topic);
}

// 0x4E4130
int16 CAEPedSpeechAudioEntity::GetPedType_Reversed() {
    return CAEPedSpeechAudioEntity::GetPedType();
}

// 0x4E4150
bool CAEPedSpeechAudioEntity::IsPedFemaleForAudio_Reversed() {
    return CAEPedSpeechAudioEntity::IsPedFemaleForAudio();
}
