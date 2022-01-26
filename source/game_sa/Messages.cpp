#include "StdInc.h"

void CMessages::InjectHooks() {
    RH_ScopedClass(CMessages);
    RH_ScopedCategoryRoot();

//    RH_ScopedInstall(GetStringLength, 0x69DB50);
//    RH_ScopedInstall(StringCopy, 0x69DB70);
//    RH_ScopedInstall(StringCompare, 0x69DBD0);
//    RH_ScopedInstall(CutString, 0x69DC50);
//    RH_ScopedInstall(ClearMessages, 0x69DCD0);
//    RH_ScopedInstall(ClearSmallMessagesOnly, 0x69DD30);
//    RH_ScopedInstall(AddToPreviousBriefArray, 0x69DD50);
//    RH_ScopedInstall(ClearPreviousBriefArray, 0x69DE70);
//    RH_ScopedInstall(InsertNumberInString, 0x69DE90);
//    RH_ScopedInstall(InsertStringInString, 0x69E040);
//    RH_ScopedInstall(InsertPlayerControlKeysInString, 0x69E160);
//    RH_ScopedInstall(AddMessageWithNumber, 0x69E360);
//    RH_ScopedInstall(AddMessageJumpQWithNumber, 0x69E4E0);
//    RH_ScopedInstall(AddBigMessageWithNumber, 0x69E5F0);
//    RH_ScopedInstall(AddBigMessageWithNumberQ, 0x69E6E0);
//    RH_ScopedInstall(AddMessageWithString, 0x69E800);
//    RH_ScopedInstall(AddMessageJumpQWithString, 0x69E950);
//    RH_ScopedInstall(ClearThisPrint, 0x69EA30);
//    RH_ScopedInstall(ClearThisBigPrint, 0x69EBE0);
//    RH_ScopedInstall(ClearThisPrintBigNow, 0x69ED80);
//    RH_ScopedInstall(Init, 0x69EE00);
//    RH_ScopedInstall(ClearAllMessagesDisplayedByGame, 0x69EDC0);
//    RH_ScopedInstall(Process, 0x69EE60);
//    RH_ScopedInstall(Display, 0x69EFC0);
//    RH_ScopedInstall(AddMessage, 0x69F0B0);
//    RH_ScopedInstall(AddMessageJumpQ, 0x69F1E0);
//    RH_ScopedInstall(AddBigMessage, 0x69F2B0);
//    RH_ScopedInstall(AddBigMessageQ, 0x69F370);
}

// Returns length of a string
// 0x69DB50
uint32 CMessages::GetStringLength(char* string) {
    return plugin::CallAndReturn<uint32, 0x69DB50, char*>(string);
}

// Copies string src to dest
// 0x69DB70
void CMessages::StringCopy(char* dest, char* src, uint16 len) {
    plugin::Call<0x69DB70, char*, char*, uint16>(dest, src, len);
}

// Compares 2 strings
// 0x69DBD0
uint8 CMessages::StringCompare(char* str1, char* str2, uint16 len) {
    return plugin::CallAndReturn<uint8, 0x69DBD0, char*, char*, uint16>(str1, str2, len);
}

// 0x69DC50
void CMessages::CutString(int32 count, char* str, char** dest) {
    plugin::Call<0x69DC50, int32, char*, char**>(count, str, dest);
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
void CMessages::AddToPreviousBriefArray(char* text, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, char* string) {
    plugin::Call<0x69DD50, char*, int32, int32, int32, int32, int32, int32, char*>(text, n1, n2, n3, n4, n5, n6, string);
}

// Removes messages from previous brief
// 0x69DE70
void CMessages::ClearPreviousBriefArray() {
    plugin::Call<0x69DE70>();
}

// Inserts numbers into string
// 0x69DE90
void CMessages::InsertNumberInString(char* src, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, char* dst) {
    plugin::Call<0x69DE90, char*, int32, int32, int32, int32, int32, int32, char*>(src, n1, n2, n3, n4, n5, n6, dst);
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
void CMessages::AddMessageWithNumber(char* text, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, bool bPreviousBrief) {
    plugin::Call<0x69E360, char*, uint32, uint16, int32, int32, int32, int32, int32, int32, bool>(text, time, flag, n1, n2, n3, n4, n5, n6, bPreviousBrief);
}

// Adds message with numbers and shows it instantly
// 0x69E4E0
void CMessages::AddMessageJumpQWithNumber(char* text, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, bool bPreviousBrief) {
    plugin::Call<0x69E4E0, char*, uint32, uint16, int32, int32, int32, int32, int32, int32, bool>(text, time, flag, n1, n2, n3, n4, n5, n6, bPreviousBrief);
}

// Adds big message with numbers and shows it instantly
// 0x69E5F0
void CMessages::AddBigMessageWithNumber(char* text, uint32 time, eMessageStyle style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6) {
    plugin::Call<0x69E5F0, char*, uint32, eMessageStyle, int32, int32, int32, int32, int32, int32>(text, time, style, n1, n2, n3, n4, n5, n6);
}

// Adds big message with numbers to queue
// 0x69E6E0
void CMessages::AddBigMessageWithNumberQ(char* text, uint32 time, eMessageStyle style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6) {
    plugin::Call<0x69E6E0, char*, uint32, eMessageStyle, int32, int32, int32, int32, int32, int32>(text, time, style, n1, n2, n3, n4, n5, n6);
}

// Adds message with string to queue
// 0x69E800
void CMessages::AddMessageWithString(char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief) {
    plugin::Call<0x69E800, char*, uint32, uint16, char*, bool>(text, time, flag, string, bPreviousBrief);
}

// Adds message with string and shows it instantly
// 0x69E950
void CMessages::AddMessageJumpQWithString(char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief) {
    plugin::Call<0x69E950, char*, uint32, uint16, char*, bool>(text, time, flag, string, bPreviousBrief);
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
void CMessages::ClearAllMessagesDisplayedByGame(uint8 unk) {
    plugin::Call<0x69EDC0, uint8>(unk);
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
void CMessages::AddMessage(char* text, uint32 time, uint16 flag, bool bPreviousBrief) {
    plugin::Call<0x69F0B0, char*, uint32, uint16, bool>(text, time, flag, bPreviousBrief);
}

// Adds message and shows it instantly
// 0x69F1E0
void CMessages::AddMessageJumpQ(char* text, uint32 time, uint16 flag, bool bPreviousBrief) {
    plugin::Call<0x69F1E0, char*, uint32, uint16, bool>(text, time, flag, bPreviousBrief);
}

// Adds big message and shows it instantly
// 0x69F2B0
void CMessages::AddBigMessage(char* text, uint32 time, eMessageStyle style) {
    plugin::Call<0x69F2B0, char*, uint32, eMessageStyle>(text, time, style);
}

// Adds big message to queue
// 0x69F370
void CMessages::AddBigMessageQ(char* text, uint32 time, eMessageStyle style) {
    plugin::Call<0x69F370, char*, uint32, eMessageStyle>(text, time, style);
}
