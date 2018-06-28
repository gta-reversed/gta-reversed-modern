/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

enum eMessageStyle : unsigned short
{
    STYLE_MIDDLE,                 // InTheMiddle
    STYLE_BOTTOM_RIGHT,           // AtTheBottomRight
    STYLE_WHITE_MIDDLE,           // WhiteText_InTheMiddle
    STYLE_MIDDLE_SMALLER,         // InTheMiddle_Smaller
    STYLE_MIDDLE_SMALLER_HIGHER,  // InTheMiddle_Smaller_ABitHigherOnTheScreen
    STYLE_WHITE_MIDDLE_SMALLER,   // SmallWhiteText_InTheMiddleOfTheScreen
    STYLE_LIGHTBLUE_TOP           // LightBlueText_OnTopOfTheScreen
};

struct tMessage {
	char *          m_pText;
	unsigned short  m_wFlag;
	char _pad1[2];
	unsigned int    m_dwTime;
	unsigned int    m_dwStartTime;
	int             m_dwNumber[6];
	char           *m_pString;
	unsigned char   m_bPreviousBrief;
	char _pad2[3];
};

struct tBigMessage {
	tMessage m_Current;
	tMessage m_Stack[3];
};

struct tPreviousBrief {
	char * m_pText;
	int    m_nNumber[6];
	char * m_pString;
};

class  CMessages {
public:
	// count: 20
	static tPreviousBrief *PreviousBriefs;
	// count: 8
	static tMessage *BriefMessages;
	// count: 7 (for each text style)
	static tBigMessage *BIGMessages;
	// Returns length of a string
	static unsigned int GetStringLength(char *string);
	// Copies string src to dest
	static void StringCopy(char *dest, char *src, unsigned short len);
	// Compares 2 strings
	static unsigned char StringCompare(char *str1, char *str2, unsigned short len);
	static void CutString(int count, char *str, char **dest);
	// Removes registered messages
	static void ClearMessages(bool flag);
	// Removes small messages
	static void ClearSmallMessagesOnly();
	// Adds message to previous brief
	static void AddToPreviousBriefArray(char *text, int n1, int n2, int n3, int n4, int n5, int n6, char *string);
	// Removes messages from previous brief
	static void ClearPreviousBriefArray();
	// Inserts numbers into string
	static void InsertNumberInString(char *src, int n1, int n2, int n3, int n4, int n5, int n6, char *dst);
	// Inserts string into src
	static void InsertStringInString(char *src, char *string);
	// Inserts key events into string
	static void InsertPlayerControlKeysInString(char *string);
	// Adds message with numbers to queue
	static void AddMessageWithNumber(char *text, unsigned int time, unsigned short flag, int n1, int n2, int n3, int n4, int n5, int n6, bool bPreviousBrief);
	// Adds message with numbers and shows it instantly
	static void AddMessageJumpQWithNumber(char *text, unsigned int time, unsigned short flag, int n1, int n2, int n3, int n4, int n5, int n6, bool bPreviousBrief);
	// Adds big message with numbers and shows it instantly , see eMessageStyle
	static void AddBigMessageWithNumber(char *text, unsigned int time, unsigned short style, int n1, int n2, int n3, int n4, int n5, int n6);
	// Adds big message with numbers to queue , see eMessageStyle
	static void AddBigMessageWithNumberQ(char *text, unsigned int time, unsigned short style, int n1, int n2, int n3, int n4, int n5, int n6);
	// Adds message with string to queue
	static void AddMessageWithString(char *text, unsigned int time, unsigned short flag, char *string, char bPreviousBrief);
	// Adds message with string and shows it instantly
	static void AddMessageJumpQWithString(char *text, unsigned int time, unsigned short flag, char *string, char bPreviousBrief);
	// Removes small message with this text
	static void ClearThisPrint(char *text);
	// Removes big message with this text
	static void ClearThisBigPrint(char *text);
	// Removes first big message in messages stack , see eMessageStyle
	static void ClearThisPrintBigNow(unsigned short style);
	// Initialises messages
	static void Init(bool flag);
	// Removes all displayed messages
	static void ClearAllMessagesDisplayedByGame();
	// Processing messages. This is called from CWorld::Process
	static void Process();
	// Displays messages
	static void Display(bool flag);
	// Adds message to queue
	static void AddMessage(char *text, unsigned int time, unsigned short flag, bool bPreviousBrief);
	// Adds message and shows it instantly
	static void AddMessageJumpQ(char *text, unsigned int time, unsigned short flag, bool bPreviousBrief);
	// Adds big message and shows it instantly , see eMessageStyle
	static void AddBigMessage(char *text, unsigned int time, unsigned short style);
	// Adds big message to queue , see eMessageStyle
	static void AddBigMessageQ(char *text, unsigned int time, unsigned short style);
};
