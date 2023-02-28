#include "StdInc.h"
#include "ConversationNode.h"
#include "Conversations.h"

void CConversationNode::InjectHooks() {
    RH_ScopedClass(CConversationNode);
    RH_ScopedCategory("Conversations");

    RH_ScopedInstall(Clear, 0x43A6F0);
    RH_ScopedInstall(ClearRecursively, 0x43A710);
    RH_ScopedInstall(SetUpConversationNode, 0x43A870);
}

// 0x43A710
void CConversationNode::ClearRecursively() {
    if (m_NodeYes >= 0) {
        CConversations::m_aNodes[m_NodeYes].ClearRecursively();
    }

    if (m_NodeNo >= 0) {
        CConversations::m_aNodes[m_NodeNo].ClearRecursively();
    }

    Clear();
}

// 0x43A870
void CConversationNode::SetUpConversationNode(
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
