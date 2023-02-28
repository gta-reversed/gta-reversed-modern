#pragma once

class CPed;

class CPedToPlayerConversations {
public:
    enum class State : uint32 {
        NO_CONVERSATION,
        PLAYER_REPLY,
        PLAYER_DISMISSED,
        ENDING
    };

    enum class Topic : int32 {
        CAR,
        CLOTHES,
        HAIR,
        PHYSICS,
        SHOES,
        SMELL,
        TATTOO,
        WEATHER,
        WHERE_ARE_YOU_FROM,
        GANGBANG
    };

    static inline CPed*& m_pPed = *(CPed**)0x9691C0;
    static inline CVehicle*& pLastVehicle = *(CVehicle**)0x969A40;
    static inline State& m_State = *(State*)0x969A20;
    static inline uint32& m_TimeOfLastPlayerConversation = *(uint32*)0x9691B4;
    static inline uint32& m_StartTime = *(uint32*)0x9691B8;
    static inline Topic& m_Topic = *(Topic*)0x9691BC;
    static inline bool& m_bPositiveOpening = *(bool*)0x9691B1;

    static void InjectHooks();

    static void Clear();
    static void Update();
    static void EndConversation();

    // NOTSA
    static Topic GetRandomTopicForPed(CPed* ped) {
        if (ped->IsGangster() && ped->m_nPedType != PED_TYPE_GANG2) { // enemy gangster
            return CGeneral::RandomChoiceFromList({Topic::WHERE_ARE_YOU_FROM, Topic::GANGBANG});
        } else {
            return static_cast<Topic>(CGeneral::GetRandomNumberInRange(0, 7));
        }
    }
};

class CConversationForPed {
public:
    int32  m_FirstNode;
    int32  m_CurrentNode;
    CPed*  m_Ped;
    uint32 m_LastChange;
    uint32 m_LastTimeWeWereCloseEnough;
    uint32 m_Status;
    bool   m_bEnabled;
    bool   m_bSuppressSubtitles;

    void Clear() {
        m_FirstNode = m_CurrentNode = -1;
        m_Ped = nullptr;
        m_LastChange = m_LastTimeWeWereCloseEnough = 0;
    }
};
VALIDATE_SIZE(CConversationForPed, 0x1C);

class CConversationNode {
public:
    char   m_Name[8];
    int16  m_NodeYes;
    int16  m_NodeNo;
    uint32 m_Speech;
    uint32 m_SpeechY;
    uint32 m_SpeechN;

    void Clear() {
        m_Name[0] = '\0';
        m_NodeYes = m_NodeNo = -1;
        m_SpeechY = m_SpeechN = 0;
        m_Speech = 0;
    }
};
VALIDATE_SIZE(CConversationNode, 0x18);

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
    /* Check the signatures before starting work
    static bool IsPlayerInPositionForConversation(CPed* ped, bool);
    
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
