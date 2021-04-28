/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

enum eMessageStyle : unsigned short {
    STYLE_MIDDLE,                // InTheMiddle
    STYLE_BOTTOM_RIGHT,          // AtTheBottomRight
    STYLE_WHITE_MIDDLE,          // WhiteText_InTheMiddle
    STYLE_MIDDLE_SMALLER,        // InTheMiddle_Smaller
    STYLE_MIDDLE_SMALLER_HIGHER, // InTheMiddle_Smaller_ABitHigherOnTheScreen
    STYLE_WHITE_MIDDLE_SMALLER,  // SmallWhiteText_InTheMiddleOfTheScreen
    STYLE_LIGHTBLUE_TOP          // LightBlueText_OnTopOfTheScreen
};

struct tMessage {
    char* m_pText;
    unsigned short m_wFlag;
    char _pad1[2];
    unsigned int m_dwTime;
    unsigned int m_dwStartTime;
    int m_dwNumber[6];
    char* m_pString;
    unsigned char m_bPreviousBrief;
    char _pad2[3];
};

struct tBigMessage {
    tMessage m_Current;
    tMessage m_Stack[3];
};

struct tPreviousBrief {
    char* m_pText;
    int m_nNumber[6];
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

    static unsigned int GetStringLength(char* string);
    static void StringCopy(char* dest, char* src, unsigned short len);
    static unsigned char StringCompare(char* str1, char* str2, unsigned short len);
    static void CutString(int count, char* str, char** dest);
    static void ClearMessages(bool flag);
    static void ClearSmallMessagesOnly();
    static void AddToPreviousBriefArray(char* text, int n1, int n2, int n3, int n4, int n5, int n6, char* string);
    static void ClearPreviousBriefArray();
    static void InsertNumberInString(char* src, int n1, int n2, int n3, int n4, int n5, int n6, char* dst);
    static void InsertStringInString(char* src, char* string);
    static void InsertPlayerControlKeysInString(char* string);
    static void AddMessageWithNumber(char* text, unsigned int time, unsigned short flag, int n1, int n2, int n3, int n4, int n5, int n6, bool bPreviousBrief);
    static void AddMessageJumpQWithNumber(char* text, unsigned int time, unsigned short flag, int n1, int n2, int n3, int n4, int n5, int n6, bool bPreviousBrief);
    static void AddBigMessageWithNumber(char* text, unsigned int time, eMessageStyle style, int n1, int n2, int n3, int n4, int n5, int n6);
    static void AddBigMessageWithNumberQ(char* text, unsigned int time, eMessageStyle style, int n1, int n2, int n3, int n4, int n5, int n6);
    static void AddMessageWithString(char* text, unsigned int time, unsigned short flag, char* string, bool bPreviousBrief);
    static void AddMessageJumpQWithString(char* text, unsigned int time, unsigned short flag, char* string, bool bPreviousBrief);
    static void ClearThisPrint(char* text);
    static void ClearThisBigPrint(char* text);
    static void ClearThisPrintBigNow(eMessageStyle style);
    static void Init();
    static void ClearAllMessagesDisplayedByGame(uint8_t unk);
    static void Process();
    static void Display(bool flag);
    static void AddMessage(char* text, unsigned int time, unsigned short flag, bool bPreviousBrief);
    static void AddMessageJumpQ(char* text, unsigned int time, unsigned short flag, bool bPreviousBrief);
    static void AddBigMessage(char* text, unsigned int time, eMessageStyle style);
    static void AddBigMessageQ(char* text, unsigned int time, eMessageStyle style);
};
