/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

struct tMessage {
    tMessage() = default;

    tMessage(
        const char* text,
        const char* strToInsert = {},
        uint16 flags = {},
        uint32 time = {},
        bool previousBrief = {},
        std::optional<std::array<int32, 6>> numbers = {}
    ) :
        Text{ text },
        StringToInsert{ strToInsert},
        Flags{ flags },
        VisibleTime{ time },
        CreatedAtMS{ CTimer::GetTimeInMS() },
        PreviousBrief{ previousBrief }
    {
        if (numbers) {
            rng::copy(*numbers, rng::begin(NumbersToInsert));
        } else {
            rng::fill(NumbersToInsert, -1);
        }
    }

    ~tMessage() {
        Text = nullptr; // This marks that this object is destroyed
    }

    //! If this object is in use
    bool IsValid() const { return Text != nullptr; }

    //! Ticks to disappear at
    auto GetTimeToDisappearAtMS() const { return CreatedAtMS + VisibleTime; }


    const char*          Text{};
    uint16               Flags{};
    uint32               VisibleTime{};
    uint32               CreatedAtMS{};
    std::array<int32, 6> NumbersToInsert{};
    const char*          StringToInsert{};
    uint8                PreviousBrief{};
};

struct tBigMessage {
    std::array<tMessage, 4> Stack{};
};

struct tPreviousBrief {
    const char*          Text{};
    std::array<int32, 6> NumbersToInsert{};
    const char*          StringToInsert{};
};

class CMessages {
public:
    static inline std::array<tPreviousBrief, 20>& PreviousBriefs = *(std::array<tPreviousBrief, 20>*)0xC1A570;
    static inline std::array<tMessage, 8>& BriefMessages = *(std::array<tMessage, 8>*)0xC1A7F0;
    static inline std::array<tBigMessage, 7>& BIGMessages = *(std::array<tBigMessage, 7>*)0xC1A970; // (for each text style)

public:
    static void InjectHooks();

    static void Init();
    static void AddMessage2(const char* text, uint32 time, uint16 flag, bool bPreviousBrief, bool showInstantly = false, char* str = nullptr, std::optional<std::array<int32, 6>> numbers = {});
    static void AddMessageQ(const char* text, uint32 time, uint16 flag, bool bPreviousBrief); // Renamed from AddMessage
    static void AddMessageWithStringQ(const char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief);
    static void AddMessageWithNumberQ(const char* text, uint32 time, uint16 flag, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1, bool bPreviousBrief = false);
    static void AddMessageJump(const char* text, uint32 time, uint16 flag, bool bPreviousBrief); // Renamed from AddMessageJumpQ
    static void AddMessageJumpQWithNumber(const char* text, uint32 time, uint16 flag, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1, bool bPreviousBrief = false);
    static void AddMessageJumpQWithString(const char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief);

    static void AddBigMessage2(const char* text, uint32 time, eMessageStyle style, bool showInstantly, char* str = nullptr, std::optional<std::array<int32, 6>> numbers = {});
    static void AddBigMessageWithNumberQ(const char* text, uint32 time, eMessageStyle style, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1);
    static void AddBigMessageQ(const char* text, uint32 time, eMessageStyle style);
    static void AddBigMessageWithNumber(const char* text, uint32 time, eMessageStyle style, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1);
    static void AddBigMessage(const char* text, uint32 time, eMessageStyle style);

    static void AddToPreviousBriefArray(const char* text, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1, const char* string = nullptr);

    static void ClearMessages(bool flag);
    static void ClearSmallMessagesOnly();
    static void ClearPreviousBriefArray();
    static void ClearThisPrint(const char* text);
    static void ClearThisBigPrint(const char* text);
    static void ClearThisPrintBigNow(eMessageStyle style);
    static void ClearAllMessagesDisplayedByGame(bool unk);

    static uint32 GetStringLength(const char* string);

    static void StringCopy(char* dest, const char* src, uint16 len);
    static bool StringCompare(const char* str1, const char* str2, uint16 len);
    static void CutString(int32 count, const char* str, char** dest);

    static void InsertNumberInString(const char* src, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1, char* dst = nullptr);
    static void InsertStringInString(char* into, const char* str);
    static void InsertPlayerControlKeysInString(char* str);

    static void Process();
    static void Display(bool flag);

    // NOTSA helpers
    static void InsertNumberInString2(const char* text, auto&& n, char* dst) {
        InsertNumberInString(text, n[0], n[1], n[2], n[3], n[4], n[5], dst);
    }
};
