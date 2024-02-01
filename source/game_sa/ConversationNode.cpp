#include "StdInc.h"
#include "ConversationNode.h"
#include "Conversations.h"

void CConversationNode::InjectHooks() {
    RH_ScopedClass(CConversationNode);
    RH_ScopedCategory("Conversations");

    RH_ScopedInstall(Clear, 0x43A6F0);
    RH_ScopedInstall(ClearRecursively, 0x43A710);
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
