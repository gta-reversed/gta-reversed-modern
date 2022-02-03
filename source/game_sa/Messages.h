/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

enum eMessageStyle : uint16 {
    STYLE_MIDDLE,                // InTheMiddle
    STYLE_BOTTOM_RIGHT,          // AtTheBottomRight
    STYLE_WHITE_MIDDLE,          // WhiteText_InTheMiddle
    STYLE_MIDDLE_SMALLER,        // InTheMiddle_Smaller
    STYLE_MIDDLE_SMALLER_HIGHER, // InTheMiddle_Smaller_ABitHigherOnTheScreen
    STYLE_WHITE_MIDDLE_SMALLER,  // SmallWhiteText_InTheMiddleOfTheScreen
    STYLE_LIGHTBLUE_TOP          // LightBlueText_OnTopOfTheScreen
};

struct tMessage {
    char*  m_pText;
    uint16 m_wFlag;
    char   _pad1[2];
    uint32 m_dwTime;
    uint32 m_dwStartTime;
    int32  m_dwNumber[6];
    char*  m_pString;
    uint8  m_bPreviousBrief;
    char   _pad2[3];
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
    // count: 20
    static tPreviousBrief* PreviousBriefs;
    // count: 8
    static tMessage* BriefMessages;
    // count: 7 (for each text style)
    static tBigMessage* BIGMessages;

public:
    static void InjectHooks();

    static uint32 GetStringLength(char* string);
    static void StringCopy(char* dest, char* src, uint16 len);
    static uint8 StringCompare(char* str1, char* str2, uint16 len);
    static void CutString(int32 count, char* str, char** dest);
    static void ClearMessages(bool flag);
    static void ClearSmallMessagesOnly();
    static void AddToPreviousBriefArray(char* text, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, char* string);
    static void ClearPreviousBriefArray();
    static void InsertNumberInString(char* src, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, char* dst);
    static void InsertStringInString(char* src, char* string);
    static void InsertPlayerControlKeysInString(char* string);
    static void AddMessageWithNumber(char* text, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, bool bPreviousBrief);
    static void AddMessageJumpQWithNumber(char* text, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, bool bPreviousBrief);
    static void AddBigMessageWithNumber(char* text, uint32 time, eMessageStyle style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6);
    static void AddBigMessageWithNumberQ(char* text, uint32 time, eMessageStyle style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6);
    static void AddMessageWithString(char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief);
    static void AddMessageJumpQWithString(char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief);
    static void ClearThisPrint(char* text);
    static void ClearThisBigPrint(char* text);
    static void ClearThisPrintBigNow(eMessageStyle style);
    static void Init();
    static void ClearAllMessagesDisplayedByGame(uint8 unk);
    static void Process();
    static void Display(bool flag);
    static void AddMessage(char* text, uint32 time, uint16 flag, bool bPreviousBrief);
    static void AddMessageJumpQ(char* text, uint32 time, uint16 flag, bool bPreviousBrief);
    static void AddBigMessage(char* text, uint32 time, eMessageStyle style);
    static void AddBigMessageQ(char* text, uint32 time, eMessageStyle style);
};
