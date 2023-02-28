#include "StdInc.h"

#include "Conversations.h"
#include "ConversationForPed.h"
#include "ConversationNode.h"

void CConversations::InjectHooks() {
    RH_ScopedClass(CConversations);
    RH_ScopedCategory("Conversations");

    RH_ScopedInstall(Clear, 0x43A7B0);
    RH_ScopedInstall(RemoveConversationForPed, 0x43A960);
    RH_ScopedInstall(Update, 0x43C590, {.reversed = false});
    RH_ScopedInstall(IsConversationGoingOn, 0x43AAC0);
    RH_ScopedInstall(IsConversationAtNode, 0x43B000);
    RH_ScopedInstall(EnableConversation, 0x43AA40);
    RH_ScopedInstall(DoneSettingUpConversation, 0x43ADB0, {.reversed = false});
    RH_ScopedInstall(SetUpConversationNode, 0x43A870, {.reversed = false});
    RH_ScopedInstall(StartSettingUpConversation, 0x43A840);
    RH_ScopedInstall(AwkwardSay, 0x43A810);

    // Inlined
    RH_ScopedInstall(FindFreeNodeSlot, 0x43AA10);
    RH_ScopedInstall(FindConversationForPed, 0x43A9E0);
    RH_ScopedInstall(FindFreeConversationSlot, 0x43A9B0);
    RH_ScopedInstall(GetConversationStatus, 0x43AA80);
}

// 0x43A7B0
void CConversations::Clear() {
    rng::for_each(m_aConversations, &CConversationForPed::Clear);
    rng::for_each(m_aNodes, &CConversationNode::Clear);

    m_bSettingUpConversation = false;
    m_AwkwardSayStatus = 0;
}

// 0x43A960
void CConversations::RemoveConversationForPed(CPed* ped) {
    if (const auto conversation = FindConversationForPed(ped)) {
        assert(conversation->GetFirstNode());
        conversation->GetFirstNode()->ClearRecursively();
        conversation->Clear();
    }
}

// 0x43C590
void CConversations::Update() {
    plugin::Call<0x43C590>();
}

// 0x43AAC0
bool CConversations::IsConversationGoingOn() {
    return rng::any_of(m_aConversations, [](auto& conversation) { return conversation.m_Status != 0; });
}

// 0x43B0B0
bool CConversations::IsPlayerInPositionForConversation(CPed* ped, bool isRandomConversation) {    
    if (const auto conversation = FindConversationForPed(ped)) {
        return conversation->IsPlayerInPositionForConversation(isRandomConversation);
    }

    // Originally in this case game would call a THISCALL function with nullptr `this`, so game would crash.
    NOTSA_UNREACHABLE("Couldn't find the specified ped in any conversation.");
}

// 0x43B000
bool CConversations::IsConversationAtNode(char* nodeName, CPed* ped) {
    if (const auto conversation = FindConversationForPed(ped)) {
        assert(conversation->GetCurrentNode());
        return strcmp(MakeUpperCase(nodeName, nodeName), conversation->GetCurrentNode()->m_Name);
    }

    return false;
}

// 0x43AA40
void CConversations::EnableConversation(CPed* ped, bool enable) {
    if (const auto conversation = FindConversationForPed(ped)) {
        conversation->m_bEnabled = enable;
    }
    // Originally in this case game would derefecence a nullptr, accessing address `0x18`.
    NOTSA_UNREACHABLE("Couldn't find conversation for ped!");
}

// 0x43ADB0
void CConversations::DoneSettingUpConversation(bool suppressSubtitles) {}

// 0x43A870
void CConversations::SetUpConversationNode(char*, char*, char*, int32, int32, int32) {}

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

// 0x43AA10
uint32 CConversations::FindFreeNodeSlot() {
    const auto free = rng::find_if(m_aNodes, [](auto& node) { return node.m_Name[0] == '\0'; });
    if (free == m_aNodes.end()) {
        return 0;
    }

    strcpy_s(free->m_Name, "X");
    return rng::distance(m_aNodes.begin(), free);
}

// 0x43A9E0
CConversationForPed* CConversations::FindConversationForPed(CPed* ped) {
    const auto conversation = rng::find_if(m_aConversations, [ped](auto& conv) { return conv.m_Ped == ped; });

    return conversation != m_aConversations.end() ? &(*conversation) : nullptr;
}

// 0x43A9B0
CConversationForPed* CConversations::FindFreeConversationSlot() {
    const auto conversation = rng::find_if(m_aConversations, [](auto& conv) { return conv.m_Ped != nullptr; });

    return conversation != m_aConversations.end() ? &(*conversation) : nullptr;
}

// 0x43AA80
uint32 CConversations::GetConversationStatus(CPed* ped) {
    if (const auto conversation = FindConversationForPed(ped)) {
        return conversation->m_Status;
    }
    // Originally in this case game would derefecence a nullptr, accessing address `0x14`.
    NOTSA_UNREACHABLE("Couldn't find conversation for ped!");
}
