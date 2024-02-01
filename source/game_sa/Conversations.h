#pragma once

class CPed;
class CConversationForPed;
class CConversationNode;

enum class eConversationForPedStatus : uint32;

struct CTempConversationNode {
    char m_Name[8];
    char m_NameNodeYes[8];
    char m_NameNodeNo[8];
    int32 m_FinalSlot;
    int16 m_NodeYes;
    int16 m_NodeNo;
    uint32 m_Speech;
    uint32 m_SpeechY;
    uint32 m_SpeechN;

    void ClearNodes() {
        m_NodeYes = m_NodeNo = -1;

        if (!strcmp(m_NameNodeYes, m_Name)) {
            m_NameNodeYes[0] = '\0';
        }

        if (!strcmp(m_NameNodeNo, m_Name)) {
            m_NameNodeNo[0] = '\0';
        }
    }

    void ResolveYesNoNodes();
};
VALIDATE_SIZE(CTempConversationNode, 0x2C);

class CConversations {
public:
    enum class AwkwardSayState : int32 {
        NOT_AVAILABLE,
        AUDIO_PLAYING,
        FINISHING
    };

    static inline bool& m_bSettingUpConversation = *(bool*)0x9691D0;
    static inline AwkwardSayState& m_AwkwardSayStatus = *(AwkwardSayState*)0x9691C4;
    static inline int32& m_SettingUpConversationNumNodes = *(int32*)0x9691C8;
    static inline CPed*& m_pSettingUpConversationPed = *(CPed**)0x9691CC;

    static inline std::array<CConversationForPed, 14>& m_aConversations = *(std::array<CConversationForPed, 14>*)0x9691D8;
    static inline std::array<CTempConversationNode, 12>& m_aTempNodes = *(std::array<CTempConversationNode, 12>*)0x969360;
    static inline std::array<CConversationNode, 50>& m_aNodes = *(std::array<CConversationNode, 50>*)0x969570;

    static void InjectHooks();

    static void Clear();
    static void RemoveConversationForPed(CPed* ped);

    static void Update();
    static bool IsConversationGoingOn();
    static bool IsPlayerInPositionForConversation(CPed* ped, bool isRandomConversation);
    static bool IsConversationAtNode(char* nodeName, CPed* ped);
    static void EnableConversation(CPed* ped, bool enable);
    static void DoneSettingUpConversation(bool suppressSubtitles);
    static void SetUpConversationNode(const char* name, const char* linkYes, const char* linkNo, int32 speech, int32 speechY, int32 speechN);
    static void StartSettingUpConversation(CPed* ped);
    static void AwkwardSay(int32 sampleId, CPed* ped);

    static uint32 FindFreeNodeSlot();
    static CConversationForPed* FindConversationForPed(CPed* ped);
    static CConversationForPed* FindFreeConversationSlot();
    static eConversationForPedStatus GetConversationStatus(CPed* ped);
};
