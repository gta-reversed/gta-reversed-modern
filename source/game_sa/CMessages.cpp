#include "StdInc.h"

void CMessages::InjectHooks() {
//    ReversibleHooks::Install("CMessages", "GetStringLength", 0x69DB50, &CMessages::GetStringLength);
//    ReversibleHooks::Install("CMessages", "StringCopy", 0x69DB70, &CMessages::StringCopy);
//    ReversibleHooks::Install("CMessages", "StringCompare", 0x69DBD0, &CMessages::StringCompare);
//    ReversibleHooks::Install("CMessages", "CutString", 0x69DC50, &CMessages::CutString);
//    ReversibleHooks::Install("CMessages", "ClearMessages", 0x69DCD0, &CMessages::ClearMessages);
//    ReversibleHooks::Install("CMessages", "ClearSmallMessagesOnly", 0x69DD30, &CMessages::ClearSmallMessagesOnly);
//    ReversibleHooks::Install("CMessages", "AddToPreviousBriefArray", 0x69DD50, &CMessages::AddToPreviousBriefArray);
//    ReversibleHooks::Install("CMessages", "ClearPreviousBriefArray", 0x69DE70, &CMessages::ClearPreviousBriefArray);
//    ReversibleHooks::Install("CMessages", "InsertNumberInString", 0x69DE90, &CMessages::InsertNumberInString);
//    ReversibleHooks::Install("CMessages", "InsertStringInString", 0x69E040, &CMessages::InsertStringInString);
//    ReversibleHooks::Install("CMessages", "InsertPlayerControlKeysInString", 0x69E160, &CMessages::InsertPlayerControlKeysInString);
//    ReversibleHooks::Install("CMessages", "AddMessageWithNumber", 0x69E360, &CMessages::AddMessageWithNumber);
//    ReversibleHooks::Install("CMessages", "AddMessageJumpQWithNumber", 0x69E4E0, &CMessages::AddMessageJumpQWithNumber);
//    ReversibleHooks::Install("CMessages", "AddBigMessageWithNumber", 0x69E5F0, &CMessages::AddBigMessageWithNumber);
//    ReversibleHooks::Install("CMessages", "AddBigMessageWithNumberQ", 0x69E6E0, &CMessages::AddBigMessageWithNumberQ);
//    ReversibleHooks::Install("CMessages", "AddMessageWithString", 0x69E800, &CMessages::AddMessageWithString);
//    ReversibleHooks::Install("CMessages", "AddMessageJumpQWithString", 0x69E950, &CMessages::AddMessageJumpQWithString);
//    ReversibleHooks::Install("CMessages", "ClearThisPrint", 0x69EA30, &CMessages::ClearThisPrint);
//    ReversibleHooks::Install("CMessages", "ClearThisBigPrint", 0x69EBE0, &CMessages::ClearThisBigPrint);
//    ReversibleHooks::Install("CMessages", "ClearThisPrintBigNow", 0x69ED80, &CMessages::ClearThisPrintBigNow);
//    ReversibleHooks::Install("CMessages", "Init", 0x69EE00, &CMessages::Init);
//    ReversibleHooks::Install("CMessages", "ClearAllMessagesDisplayedByGame", 0x69EDC0, &CMessages::ClearAllMessagesDisplayedByGame);
//    ReversibleHooks::Install("CMessages", "Process", 0x69EE60, &CMessages::Process);
//    ReversibleHooks::Install("CMessages", "Display", 0x69EFC0, &CMessages::Display);
//    ReversibleHooks::Install("CMessages", "AddMessage", 0x69F0B0, &CMessages::AddMessage);
//    ReversibleHooks::Install("CMessages", "AddMessageJumpQ", 0x69F1E0, &CMessages::AddMessageJumpQ);
//    ReversibleHooks::Install("CMessages", "AddBigMessage", 0x69F2B0, &CMessages::AddBigMessage);
//    ReversibleHooks::Install("CMessages", "AddBigMessageQ", 0x69F370, &CMessages::AddBigMessageQ);
}

// Returns length of a string
// 0x69DB50
unsigned int CMessages::GetStringLength(char* string) {
    return plugin::CallAndReturn<unsigned int, 0x69DB50, char*>(string);
}

// Copies string src to dest
// 0x69DB70
void CMessages::StringCopy(char* dest, char* src, unsigned short len) {
    plugin::Call<0x69DB70, char*, char*, unsigned short>(dest, src, len);
}

// Compares 2 strings
// 0x69DBD0
unsigned char CMessages::StringCompare(char* str1, char* str2, unsigned short len) {
    return plugin::CallAndReturn<unsigned char, 0x69DBD0, char*, char*, unsigned short>(str1, str2, len);
}

// 0x69DC50
void CMessages::CutString(int count, char* str, char** dest) {
    plugin::Call<0x69DC50, int, char*, char**>(count, str, dest);
}

// Removes registered messages
// 0x69DCD0
void CMessages::ClearMessages(bool flag) {
    plugin::Call<0x69DCD0, bool>(flag);
}

// Removes small messages
// 0x69DD30
void CMessages::ClearSmallMessagesOnly() {
    plugin::Call<0x69DD30>();
}

// Adds message to previous brief
// 0x69DD50
void CMessages::AddToPreviousBriefArray(char* text, int n1, int n2, int n3, int n4, int n5, int n6, char* string) {
    plugin::Call<0x69DD50, char*, int, int, int, int, int, int, char*>(text, n1, n2, n3, n4, n5, n6, string);
}

// Removes messages from previous brief
// 0x69DE70
void CMessages::ClearPreviousBriefArray() {
    plugin::Call<0x69DE70>();
}

// Inserts numbers into string
// 0x69DE90
void CMessages::InsertNumberInString(char* src, int n1, int n2, int n3, int n4, int n5, int n6, char* dst) {
    plugin::Call<0x69DE90, char*, int, int, int, int, int, int, char*>(src, n1, n2, n3, n4, n5, n6, dst);
}

// Inserts string into src
// 0x69E040
void CMessages::InsertStringInString(char* src, char* string) {
    plugin::Call<0x69E040, char*, char*>(src, string);
}

// Inserts key events into string
// 0x69E160
void CMessages::InsertPlayerControlKeysInString(char* string) {
    plugin::Call<0x69E160, char*>(string);
}

// Adds message with numbers to queue
// 0x69E360
void CMessages::AddMessageWithNumber(char* text, unsigned int time, unsigned short flag, int n1, int n2, int n3, int n4, int n5, int n6, bool bPreviousBrief) {
    plugin::Call<0x69E360, char*, unsigned int, unsigned short, int, int, int, int, int, int, bool>(text, time, flag, n1, n2, n3, n4, n5, n6, bPreviousBrief);
}

// Adds message with numbers and shows it instantly
// 0x69E4E0
void CMessages::AddMessageJumpQWithNumber(char* text, unsigned int time, unsigned short flag, int n1, int n2, int n3, int n4, int n5, int n6, bool bPreviousBrief) {
    plugin::Call<0x69E4E0, char*, unsigned int, unsigned short, int, int, int, int, int, int, bool>(text, time, flag, n1, n2, n3, n4, n5, n6, bPreviousBrief);
}

// Adds big message with numbers and shows it instantly
// 0x69E5F0
void CMessages::AddBigMessageWithNumber(char* text, unsigned int time, eMessageStyle style, int n1, int n2, int n3, int n4, int n5, int n6) {
    plugin::Call<0x69E5F0, char*, unsigned int, eMessageStyle, int, int, int, int, int, int>(text, time, style, n1, n2, n3, n4, n5, n6);
}

// Adds big message with numbers to queue
// 0x69E6E0
void CMessages::AddBigMessageWithNumberQ(char* text, unsigned int time, eMessageStyle style, int n1, int n2, int n3, int n4, int n5, int n6) {
    plugin::Call<0x69E6E0, char*, unsigned int, eMessageStyle, int, int, int, int, int, int>(text, time, style, n1, n2, n3, n4, n5, n6);
}

// Adds message with string to queue
// 0x69E800
void CMessages::AddMessageWithString(char* text, unsigned int time, unsigned short flag, char* string, bool bPreviousBrief) {
    plugin::Call<0x69E800, char*, unsigned int, unsigned short, char*, bool>(text, time, flag, string, bPreviousBrief);
}

// Adds message with string and shows it instantly
// 0x69E950
void CMessages::AddMessageJumpQWithString(char* text, unsigned int time, unsigned short flag, char* string, bool bPreviousBrief) {
    plugin::Call<0x69E950, char*, unsigned int, unsigned short, char*, bool>(text, time, flag, string, bPreviousBrief);
}

// Removes small message with this text
// 0x69EA30
void CMessages::ClearThisPrint(char* text) {
    plugin::Call<0x69EA30, char*>(text);
}

// Removes big message with this text
// 0x69EBE0
void CMessages::ClearThisBigPrint(char* text) {
    plugin::Call<0x69EBE0, char*>(text);
}

// Removes first big message in messages stack
// 0x69ED80
void CMessages::ClearThisPrintBigNow(eMessageStyle style) {
    plugin::Call<0x69ED80, eMessageStyle>(style);
}

// Initialises messages
// 0x69EE00
void CMessages::Init() {
    plugin::Call<0x69EE00>();
}

// Removes all displayed messages
// 0x69EDC0
void CMessages::ClearAllMessagesDisplayedByGame(uint8_t unk) {
    plugin::Call<0x69EDC0, uint8_t>(unk);
}

// Processing messages. This is called from CWorld::Process
// 0x69EE60
void CMessages::Process() {
    plugin::Call<0x69EE60>();
}

// Displays messages
// 0x69EFC0
void CMessages::Display(bool flag) {
    plugin::Call<0x69EFC0, bool>(flag);
}

// Adds message to queue
// 0x69F0B0
void CMessages::AddMessage(char* text, unsigned int time, unsigned short flag, bool bPreviousBrief) {
    plugin::Call<0x69F0B0, char*, unsigned int, unsigned short, bool>(text, time, flag, bPreviousBrief);
}

// Adds message and shows it instantly
// 0x69F1E0
void CMessages::AddMessageJumpQ(char* text, unsigned int time, unsigned short flag, bool bPreviousBrief) {
    plugin::Call<0x69F1E0, char*, unsigned int, unsigned short, bool>(text, time, flag, bPreviousBrief);
}

// Adds big message and shows it instantly
// 0x69F2B0
void CMessages::AddBigMessage(char* text, unsigned int time, eMessageStyle style) {
    plugin::Call<0x69F2B0, char*, unsigned int, eMessageStyle>(text, time, style);
}

// Adds big message to queue
// 0x69F370
void CMessages::AddBigMessageQ(char* text, unsigned int time, eMessageStyle style) {
    plugin::Call<0x69F370, char*, unsigned int, eMessageStyle>(text, time, style);
}
