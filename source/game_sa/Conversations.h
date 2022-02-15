#pragma once

class CPed;

class CPedToPlayerConversations {
public:
    static inline CPed*& m_pPed = *(CPed**)0x9691C0;

    static void Clear();
};

class CConversations {
public:
    static void Clear();
    /* Check the signatures before starting work
    static void Update();
    static bool IsPlayerInPositionForConversation(CPed* ped, bool);
    static bool IsConversationGoingOn();
    static bool IsConversationAtNode(char*, CPed* ped);
    static void GetConversationStatus(CPed* ped);
    static void EnableConversation(CPed* ped, bool);
    static void DoneSettingUpConversation(bool);
    static void FindFreeNodeSlot();
    static void FindConversationForPed(CPed* ped);
    static void FindFreeConversationSlot();
    static void RemoveConversationForPed(CPed* ped);
    static void SetUpConversationNode(char*, char*, char*, int32, int32, int32);
    static void StartSettingUpConversation(CPed* ped);
    static void AwkwardSay(int32, CPed* ped);
     */
};
