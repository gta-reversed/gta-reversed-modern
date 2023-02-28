#pragma once

class CPed;
class CConversationForPed;
class CConversationNode;

class CConversations {
public:
    static inline bool& m_bSettingUpConversation = *(bool*)0x9691D0;
    static inline int32& m_AwkwardSayStatus = *(int32*)0x9691C4;
    static inline int32& m_SettingUpConversationNumNodes = *(int32*)0x9691C8;
    static inline CPed*& m_pSettingUpConversationPed = *(CPed**)0x9691CC;

    static inline std::array<CConversationForPed, 14>& m_aConversations = *(std::array<CConversationForPed, 14>*)0x9691D8;
    static inline std::array<CConversationNode, 50>& m_aNodes = *(std::array<CConversationNode, 50>*)0x969570;

    static void InjectHooks();

    static void Clear();
    static void RemoveConversationForPed(CPed* ped);

    static void Update();
    static bool IsConversationGoingOn();
    static bool IsPlayerInPositionForConversation(CPed* ped, bool isRandomConversation);
    /* Check the signatures before starting work
    
    static bool IsConversationAtNode(char*, CPed* ped);
    static void GetConversationStatus(CPed* ped);
    static void EnableConversation(CPed* ped, bool);
    static void DoneSettingUpConversation(bool);
    static void FindFreeNodeSlot();
    static void FindConversationForPed(CPed* ped);
    static void FindFreeConversationSlot();
    static void SetUpConversationNode(char*, char*, char*, int32, int32, int32);
     */
    static void StartSettingUpConversation(CPed* ped);
    static void AwkwardSay(int32 sampleId, CPed* ped);
};
