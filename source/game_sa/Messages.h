/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

struct tMessage {
    char*  m_pText;
    uint16 m_nFlags;
    uint32 m_nTime;
    uint32 m_nStartTime;
    int32  m_nNumber[6];
    char*  m_pString;
    uint8  m_bPreviousBrief;
};

struct tBigMessage {
    tMessage m_Current;
    tMessage m_Stack[3];
};

struct tPreviousBrief {
    char* m_pText;
    int32 m_nNumber[6];
    char* m_pString;
};

class CMessages {
public:
    static inline std::array<tPreviousBrief, 20>& PreviousBriefs = *(std::array<tPreviousBrief, 20>*)0xC1A570;
    static inline std::array<tMessage, 8>& BriefMessages = *(std::array<tMessage, 8>*)0xC1A7F0;
    static inline std::array<tBigMessage, 7>& BIGMessages = *(std::array<tBigMessage, 7>*)0xC1A970; // (for each text style)

public:
    static void InjectHooks();

    static void Init();
    static void AddMessage(const char* text, uint32 time, uint16 flag, bool bPreviousBrief);
    static void AddMessageJumpQ(const char* text, uint32 time, uint16 flag, bool bPreviousBrief);
    static void AddMessageWithString(const char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief);
    static void AddMessageWithNumber(const char* text, uint32 time, uint16 flag, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1, bool bPreviousBrief = false);
    static void AddMessageJumpQWithNumber(const char* text, uint32 time, uint16 flag, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1, bool bPreviousBrief = false);
    static void AddMessageJumpQWithString(const char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief);

    static void AddBigMessage(const char* text, uint32 time, eMessageStyle style);
    static void AddBigMessageQ(const char* text, uint32 time, eMessageStyle style);
    static void AddBigMessageWithNumber(const char* text, uint32 time, eMessageStyle style, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1);
    static void AddBigMessageWithNumberQ(const char* text, uint32 time, eMessageStyle style, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1);

    static void AddToPreviousBriefArray(const char* text, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1, char* string = nullptr);

    static void ClearMessages(bool flag);
    static void ClearSmallMessagesOnly();
    static void ClearPreviousBriefArray();
    static void ClearThisPrint(const char* text);
    static void ClearThisBigPrint(const char* text);
    static void ClearThisPrintBigNow(eMessageStyle style);
    static void ClearAllMessagesDisplayedByGame(bool unk);

    static uint32 GetStringLength(const char* string);

    static void StringCopy(const char* dest, const char* src, uint16 len);
    static uint8 StringCompare(const char* str1, const char* str2, uint16 len);
    static void CutString(int32 count, const char* str, char** dest);

    static void InsertNumberInString(const char* src, int32 n1 = -1, int32 n2 = -1, int32 n3 = -1, int32 n4 = -1, int32 n5 = -1, int32 n6 = -1, char* dst = nullptr);
    static void InsertStringInString(const char* src, char* string);
    static void InsertPlayerControlKeysInString(const char* string);

    static void Process();
    static void Display(bool flag);

    // NOTSA helpers
    static void InsertNumberInString(char* text, int32* n, char* dst) {
        InsertNumberInString(text, n[0], n[1], n[2], n[3], n[4], n[5], dst);
    }
};
