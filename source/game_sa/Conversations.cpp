#include "StdInc.h"

#include "Conversations.h"
#include "ConversationForPed.h"
#include "ConversationNode.h"

void CConversations::InjectHooks() {
    RH_ScopedClass(CConversations);
    RH_ScopedCategory("Conversations");

    RH_ScopedInstall(Clear, 0x43A7B0);
    RH_ScopedInstall(IsConversationGoingOn, 0x43AAC0);
    RH_ScopedInstall(StartSettingUpConversation, 0x43A840);
    RH_ScopedInstall(AwkwardSay, 0x43A810);
}

// 0x43A7B0
void CConversations::Clear() {
    rng::for_each(m_aConversations, &CConversationForPed::Clear);
    rng::for_each(m_aNodes, &CConversationNode::Clear);

    m_bSettingUpConversation = false;
    m_AwkwardSayStatus = 0;
}

// 0x0x43C590
void CConversations::Update() {
    plugin::Call<0x43C590>();
}

// 0x43AAC0
bool CConversations::IsConversationGoingOn() {
    return rng::any_of(m_aConversations, [](auto& conversation) { return conversation.m_Status; });
}

// 0x43B0B0
bool CConversations::IsPlayerInPositionForConversation(CPed* ped, bool isRandomConversation) {
    const auto conversation = rng::find_if(m_aConversations, [ped](auto& conv) { return conv.m_Ped == ped; });
    if (conversation == m_aConversations.end()) {
        // Originally in this case game would call a THISCALL function with nullptr `this`, so game would crash.
        NOTSA_UNREACHABLE("Couldn't find the specified ped in any conversation.");
    }

    conversation->IsPlayerInPositionForConversation(isRandomConversation);
}

// 0x43A840
void CConversations::StartSettingUpConversation(CPed* ped) {
    m_pSettingUpConversationPed = ped;
    CEntity::RegisterReference(m_pSettingUpConversationPed);

    m_SettingUpConversationNumNodes = 0;
    m_bSettingUpConversation = true;
}

// 0x43A810
void CConversations::AwkwardSay(int32 sampleId, CPed* ped) {
    AudioEngine.PreloadMissionAudio(0u, sampleId);
    AudioEngine.AttachMissionAudioToPed(0u, ped);
    m_AwkwardSayStatus = 1;
}

// 0x43A960
void CConversations::RemoveConversationForPed(CPed* ped) {
    plugin::Call<0x43A960, CPed*>(ped);
}
