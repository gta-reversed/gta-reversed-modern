#pragma once

class CPed;

class CPedToPlayerConversations {
public:
    static inline CPed*& m_pPed = *(CPed**)0x9691C0;

    static void Clear();
    static void Update();
};

class CConversations {
public:
    static void Clear();
    static void RemoveConversationForPed(CPed* ped);

    static void Update();
    static void SetUpConversationNode(const char*, const char*, const char*, int32, int32, int32);
    /* Check the signatures before starting work
    static bool IsPlayerInPositionForConversation(CPed* ped, bool);
    static bool IsConversationGoingOn();
    static bool IsConversationAtNode(char*, CPed* ped);
    static void GetConversationStatus(CPed* ped);
    static void EnableConversation(CPed* ped, bool);
    static void DoneSettingUpConversation(bool);
    static void FindFreeNodeSlot();
    static void FindConversationForPed(CPed* ped);
    static void FindFreeConversationSlot();
    static void StartSettingUpConversation(CPed* ped);
    static void AwkwardSay(int32, CPed* ped);
     */
};
