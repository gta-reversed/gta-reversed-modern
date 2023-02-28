#pragma once

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
