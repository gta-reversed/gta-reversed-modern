#pragma once
#include "Conversations.h"
#include "ConversationNode.h"

class CConversationForPed {
public:
    int32 m_FirstNode;
    int32 m_CurrentNode;
    CPed* m_Ped;
    uint32 m_LastChange;
    uint32 m_LastTimeWeWereCloseEnough;
    uint32 m_Status;
    bool m_bEnabled;
    bool m_bSuppressSubtitles;

    static void InjectHooks();

    // 0x43A770
    void Clear() {
        m_FirstNode = m_CurrentNode = -1;
        m_Ped = nullptr;
        m_LastChange = m_LastTimeWeWereCloseEnough = 0;
    }

    void Update();
    bool IsPlayerInPositionForConversation(bool isRandomConversation) const;

    // NOTSA
    CConversationNode* GetCurrentNode() const {
        return m_CurrentNode != -1 ? &CConversations::m_aNodes[m_CurrentNode] : nullptr;
    }

    CConversationNode* GetFirstNode() const {
        return m_FirstNode != -1 ? &CConversations::m_aNodes[m_FirstNode] : nullptr;
    }
};
VALIDATE_SIZE(CConversationForPed, 0x1C);
