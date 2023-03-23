#include "StdInc.h"

#include "Conversations.h"
#include "ConversationForPed.h"
#include "ConversationNode.h"

void CConversations::InjectHooks() {
    RH_ScopedClass(CConversations);
    RH_ScopedCategory("Conversations");

    RH_ScopedInstall(Clear, 0x43A7B0);
    RH_ScopedInstall(RemoveConversationForPed, 0x43A960);
    RH_ScopedInstall(Update, 0x43C590);
    RH_ScopedInstall(IsConversationGoingOn, 0x43AAC0);
    RH_ScopedInstall(IsConversationAtNode, 0x43B000);
    RH_ScopedInstall(EnableConversation, 0x43AA40);
    RH_ScopedInstall(DoneSettingUpConversation, 0x43ADB0);
    RH_ScopedInstall(SetUpConversationNode, 0x43A870);
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
    m_AwkwardSayStatus = AwkwardSayState::NOT_AVAILABLE;
}

// 0x43A870
void CConversations::SetUpConversationNode(
    const char* questionKey,
    const char* answerYesKey,
    const char* answerNoKey,
    int32 questionWAV,
    int32 answerYesWAV,
    int32 answerNoWAV) {
    plugin::Call<0x43A870, const char*, const char*, const char*, int32, int32, int32>(questionKey, answerYesKey, answerNoKey, questionWAV, answerYesWAV, answerNoWAV);
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
    switch (m_AwkwardSayStatus) {
    case AwkwardSayState::AUDIO_PLAYING:
        if (AudioEngine.GetMissionAudioLoadingStatus(0)) {
            AudioEngine.PlayLoadedMissionAudio(0);
            m_AwkwardSayStatus = AwkwardSayState::FINISHING;
        }
        break;
    case AwkwardSayState::FINISHING:
        if (!AudioEngine.IsMissionAudioSampleFinished(0))
            return;

        m_AwkwardSayStatus = AwkwardSayState::NOT_AVAILABLE;
        break;
    case AwkwardSayState::NOT_AVAILABLE:
    default:
        break;
    }

    rng::for_each(m_aConversations, &CConversationForPed::Update);
}

// 0x43AAC0
bool CConversations::IsConversationGoingOn() {
    return rng::any_of(m_aConversations, [](auto& conversation) { return conversation.m_Status != eConversationForPedStatus::NOT_AVAILABLE; });
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
        return !strcmp(MakeUpperCase(nodeName, nodeName), conversation->GetCurrentNode()->m_Name);
    }

    return false;
}

// 0x43AA40
void CConversations::EnableConversation(CPed* ped, bool enable) {
    if (const auto conversation = FindConversationForPed(ped)) {
        conversation->m_bEnabled = enable;
    } else {
        // Originally in this case game would derefecence a nullptr, accessing address `0x18`.
        NOTSA_UNREACHABLE("Couldn't find conversation for ped!");
    }
}

// 0x43ADB0
void CConversations::DoneSettingUpConversation(bool suppressSubtitles) {
    rng::for_each(std::span{m_aTempNodes.data(), (size_t)m_SettingUpConversationNumNodes}, &CTempConversationNode::ClearNodes);
    rng::for_each(std::span{m_aNodes.data(), (size_t)m_SettingUpConversationNumNodes}, &CConversationNode::Clear);

    for (auto i = 0; i < m_SettingUpConversationNumNodes; i++) {
              auto& node = m_aNodes[i];
        const auto& tempNode = m_aTempNodes[i];

        strcpy_s(node.m_Name, tempNode.m_Name);

        if (tempNode.m_NodeYes >= 0) {
            node.m_NodeYes = tempNode.m_NodeYes;
        } /* else: already set to -1 in CConversationNode::Clear. */

        if (tempNode.m_NodeNo >= 0) {
            node.m_NodeNo = tempNode.m_NodeNo;
        } /* else: already set to -1 in CConversationNode::Clear. */

        node.m_Speech = tempNode.m_Speech;
        node.m_SpeechY = tempNode.m_SpeechY;
        node.m_SpeechN = tempNode.m_SpeechN;
    }

    if (const auto conversation = FindFreeConversationSlot()) {
        conversation->m_FirstNode = conversation->m_CurrentNode = m_aTempNodes[0].m_FinalSlot;
        conversation->m_Ped = m_pSettingUpConversationPed;
        CEntity::RegisterReference(conversation->m_Ped);

        conversation->m_LastChange = CTimer::GetTimeInMS();
        conversation->m_LastTimeWeWereCloseEnough = 0;
        conversation->m_bEnabled = true;
        conversation->m_bSuppressSubtitles = suppressSubtitles;
        conversation->m_Status = eConversationForPedStatus::NOT_AVAILABLE; // missing in Android

        m_SettingUpConversationNumNodes = 0;
        m_bSettingUpConversation = false;
    } else {
        // Originally in this case game would derefecence a nullptr, accessing many offsets.
        NOTSA_UNREACHABLE("Couldn't find a free conversation slot!");
    }
}

// 0x43A870
void CConversations::SetUpConversationNode(
    const char* name,
    const char* linkYes,
    const char* linkNo,
    int32 speech,
    int32 speechY,
    int32 speechN) {
    auto& currentTempNode = CConversations::m_aTempNodes[CConversations::m_SettingUpConversationNumNodes];

    const auto CopyUpperCase = [](char* dest, const char* src) {
        strncpy_s((char(&)[8])dest, src, 6u);
        MakeUpperCase(dest, dest);
    };

    CopyUpperCase(currentTempNode.m_Name, name);
    currentTempNode.m_Speech = speech;
    currentTempNode.m_SpeechY = speechY;
    currentTempNode.m_SpeechN = speechN;

    if (linkYes) {
        CopyUpperCase(currentTempNode.m_NameNodeYes, linkYes);
    } else {
        currentTempNode.m_NameNodeYes[0] = '\0';
    }

    if (linkNo) {
        CopyUpperCase(currentTempNode.m_NameNodeNo, linkNo);
    } else {
        currentTempNode.m_NameNodeNo[0] = '\0';
    }

    CConversations::m_SettingUpConversationNumNodes++;
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
    m_AwkwardSayStatus = AwkwardSayState::AUDIO_PLAYING;
}

// 0x43AA10
uint32 CConversations::FindFreeNodeSlot() {
    const auto free = rng::find_if(m_aNodes, [](auto& node) { return node.m_Name[0] == '\0'; });
    if (free == m_aNodes.end()) {
        return 0;
    }

    // Set a temporary name for the node, so it won't be considered free.
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
eConversationForPedStatus CConversations::GetConversationStatus(CPed* ped) {
    if (const auto conversation = FindConversationForPed(ped)) {
        return conversation->m_Status;
    }
    // Originally in this case game would derefecence a nullptr, accessing address `0x14`.
    NOTSA_UNREACHABLE("Couldn't find conversation for ped!");
}
