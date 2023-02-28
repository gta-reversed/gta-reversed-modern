#pragma once

class CConversationNode {
public:
    char m_Name[8];
    int16 m_NodeYes;
    int16 m_NodeNo;
    uint32 m_Speech;
    uint32 m_SpeechY;
    uint32 m_SpeechN;

    static void InjectHooks();

    // 0x43A6F0
    void Clear() {
        m_Name[0] = '\0';
        m_NodeYes = m_NodeNo = -1;
        m_SpeechY = m_SpeechN = 0;
        m_Speech = 0;
    }

    void ClearRecursively();
    void SetUpConversationNode(const char* name, uint8* linkYes, uint8* linkNo, int32 speech, int32 speechY, int32 speechN);
};
VALIDATE_SIZE(CConversationNode, 0x18);
