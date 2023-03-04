#include "StdInc.h"

#include "Messages.h"
#include "Hud.h"

void CMessages::InjectHooks() {
    RH_ScopedClass(CMessages);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(GetStringLength, 0x69DB50, { .reversed = false });
    RH_ScopedInstall(StringCopy, 0x69DB70, { .reversed = false });
    RH_ScopedInstall(StringCompare, 0x69DBD0, { .reversed = false });
    RH_ScopedInstall(CutString, 0x69DC50, { .reversed = false });
    RH_ScopedInstall(ClearMessages, 0x69DCD0, { .reversed = false });
    RH_ScopedInstall(ClearSmallMessagesOnly, 0x69DD30);
    RH_ScopedInstall(AddToPreviousBriefArray, 0x69DD50, { .reversed = false });
    RH_ScopedInstall(ClearPreviousBriefArray, 0x69DE70);
    // RH_ScopedInstall(InsertNumberInString, 0x69DE90, { .reversed = false }); // Weird build error here
    RH_ScopedInstall(InsertStringInString, 0x69E040, { .reversed = false });
    RH_ScopedInstall(InsertPlayerControlKeysInString, 0x69E160, { .reversed = false });
    RH_ScopedInstall(AddMessageWithNumber, 0x69E360, { .reversed = false });
    RH_ScopedInstall(AddMessageJumpQWithNumber, 0x69E4E0, { .reversed = false });
    RH_ScopedInstall(AddBigMessageWithNumber, 0x69E5F0, { .reversed = false });
    RH_ScopedInstall(AddBigMessageWithNumberQ, 0x69E6E0, { .reversed = false });
    RH_ScopedInstall(AddMessageWithString, 0x69E800);
    RH_ScopedInstall(AddMessageJumpQWithString, 0x69E950, { .reversed = false });
    RH_ScopedInstall(ClearThisPrint, 0x69EA30, { .reversed = false });
    RH_ScopedInstall(ClearThisBigPrint, 0x69EBE0, { .reversed = false });
    RH_ScopedInstall(ClearThisPrintBigNow, 0x69ED80, { .reversed = false });
    RH_ScopedInstall(Init, 0x69EE00);
    RH_ScopedInstall(ClearAllMessagesDisplayedByGame, 0x69EDC0);
    RH_ScopedInstall(Process, 0x69EE60, { .reversed = false });
    RH_ScopedInstall(Display, 0x69EFC0, { .reversed = false });
    RH_ScopedInstall(AddMessage, 0x69F0B0);
    RH_ScopedInstall(AddMessageJumpQ, 0x69F1E0, { .reversed = false });
    RH_ScopedInstall(AddBigMessage, 0x69F2B0, { .reversed = false });
    RH_ScopedInstall(AddBigMessageQ, 0x69F370, { .reversed = false });
}

// Initialises messages
// 0x69EE00
void CMessages::Init() {
    ClearMessages(true);
    rng::fill(PreviousBriefs, tPreviousBrief{});
}

tMessage* CMessages::FindFreeBriefMessage() {
    for (auto& msg : BriefMessages) {
        if (!msg.m_pText) {
            return &msg;
        }
    }
    DEV_LOG("No free brief message found!");
    return nullptr;
}

// Adds message to queue
// 0x69F0B0
void CMessages::AddMessage(const char* text, uint32 time, uint16 flag, bool bPreviousBrief) {
    AddMessageWithString(text, time, flag, nullptr, bPreviousBrief);
}

// Adds message with string to queue
// 0x69E800
void CMessages::AddMessageWithString(const char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief) {
    /* Some string copy code here */

    const auto msg = FindFreeBriefMessage();
    if (!msg) {
        return;
    }
    new (msg) tMessage{ text, string, flag, time, bPreviousBrief };
    if (msg == &BriefMessages.front() && bPreviousBrief) {
		AddToPreviousBriefArray(
			msg->m_pText,
			msg->m_nNumber[0],
			msg->m_nNumber[1],
			msg->m_nNumber[2],
			msg->m_nNumber[3],
			msg->m_nNumber[4],
			msg->m_nNumber[5],
			msg->m_pString
        );
    }
}

// Adds message and shows it instantly
// 0x69F1E0
void CMessages::AddMessageJumpQ(const char* text, uint32 time, uint16 flag, bool bPreviousBrief) {
    /* unused string copy here */
    BriefMessages.front() = { text, nullptr, flag, time, bPreviousBrief };
    AddToPreviousBriefArray(text, -1, -1, -1, -1, -1, -1, 0);
}


// Adds message with numbers to queue
// 0x69E360
void CMessages::AddMessageWithNumber(const char* text, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, bool bPreviousBrief) {
    plugin::Call<0x69E360, const char*, uint32, uint16, int32, int32, int32, int32, int32, int32, bool>(text, time, flag, n1, n2, n3, n4, n5, n6, bPreviousBrief);
}

// Adds message with numbers and shows it instantly
// 0x69E4E0
void CMessages::AddMessageJumpQWithNumber(const char* text, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, bool bPreviousBrief) {
    plugin::Call<0x69E4E0, const char*, uint32, uint16, int32, int32, int32, int32, int32, int32, bool>(text, time, flag, n1, n2, n3, n4, n5, n6, bPreviousBrief);
}

// Adds message with string and shows it instantly
// 0x69E950
void CMessages::AddMessageJumpQWithString(const char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief) {
    plugin::Call<0x69E950, const char*, uint32, uint16, const char*, bool>(text, time, flag, string, bPreviousBrief);
}

// Adds big message and shows it instantly
// 0x69F2B0
void CMessages::AddBigMessage(const char* text, uint32 time, eMessageStyle style) {
    plugin::Call<0x69F2B0, const char*, uint32, eMessageStyle>(text, time, style);
}

// Adds big message to queue
// 0x69F370
void CMessages::AddBigMessageQ(const char* text, uint32 time, eMessageStyle style) {
    plugin::Call<0x69F370, const char*, uint32, eMessageStyle>(text, time, style);
}

// Adds big message with numbers and shows it instantly
// 0x69E5F0
void CMessages::AddBigMessageWithNumber(const char* text, uint32 time, eMessageStyle style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6) {
    plugin::Call<0x69E5F0, const char*, uint32, eMessageStyle, int32, int32, int32, int32, int32, int32>(text, time, style, n1, n2, n3, n4, n5, n6);
}

// Adds big message with numbers to queue
// 0x69E6E0
void CMessages::AddBigMessageWithNumberQ(const char* text, uint32 time, eMessageStyle style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6) {
    plugin::Call<0x69E6E0, const char*, uint32, eMessageStyle, int32, int32, int32, int32, int32, int32>(text, time, style, n1, n2, n3, n4, n5, n6);
}

// Adds message to previous brief
// 0x69DD50
void CMessages::AddToPreviousBriefArray(const char* text, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, char* string) {
    plugin::Call<0x69DD50, const char*, int32, int32, int32, int32, int32, int32, const char*>(text, n1, n2, n3, n4, n5, n6, string);
}

// Removes registered messages
// 0x69DCD0
void CMessages::ClearMessages(bool flag) {
    plugin::Call<0x69DCD0, bool>(flag);
}

// Removes small messages
// 0x69DD30
void CMessages::ClearSmallMessagesOnly() {
    for (auto& brief : BriefMessages) {
        brief.m_pText = nullptr;
        brief.m_pString = nullptr;
    }
}

// Remove messages from previous brief
// 0x69DE70
void CMessages::ClearPreviousBriefArray() {
    for (auto& brief : PreviousBriefs) {
        brief.m_pText = nullptr;
        brief.m_pString = nullptr;
    }
}

// Removes small message with this text
// 0x69EA30
void CMessages::ClearThisPrint(const char* text) {
    plugin::Call<0x69EA30, const char*>(text);
}

// Removes big message with this text
// 0x69EBE0
void CMessages::ClearThisBigPrint(const char* text) {
    plugin::Call<0x69EBE0, const char*>(text);
}

// Removes first big message in messages stack
// 0x69ED80
void CMessages::ClearThisPrintBigNow(eMessageStyle style) {
    plugin::Call<0x69ED80, eMessageStyle>(style);
}

// Removes all displayed messages
// 0x69EDC0
void CMessages::ClearAllMessagesDisplayedByGame(bool unk) {
    ClearMessages(unk);
    ClearPreviousBriefArray();
    CHud::GetRidOfAllHudMessages(unk);
}

// Returns length of a string
// 0x69DB50
uint32 CMessages::GetStringLength(const char* string) {
    return plugin::CallAndReturn<uint32, 0x69DB50, const char*>(string);
}

// Copies string src to dest
// 0x69DB70
void CMessages::StringCopy(const char* dest, const char* src, uint16 len) {
    plugin::Call<0x69DB70, const char*, const char*, uint16>(dest, src, len);
}

// Compares 2 strings
// 0x69DBD0
uint8 CMessages::StringCompare(const char* str1, const char* str2, uint16 len) {
    return plugin::CallAndReturn<uint8, 0x69DBD0, const char*, const char*, uint16>(str1, str2, len);
}

// 0x69DC50
void CMessages::CutString(int32 count, const char* str, char** dest) {
    plugin::Call<0x69DC50, int32, const char*, char**>(count, str, dest);
}

// Insert numbers into string
// 0x69DE90
void CMessages::InsertNumberInString(const char* src, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, char* dst) {
    plugin::Call<0x69DE90, const char*, int32, int32, int32, int32, int32, int32, char*>(src, n1, n2, n3, n4, n5, n6, dst);
}

// Inserts string into src
// 0x69E040
void CMessages::InsertStringInString(const char* src, char* string) {
    plugin::Call<0x69E040, const char*, char*>(src, string);
}

// Inserts key events into string
// 0x69E160
void CMessages::InsertPlayerControlKeysInString(const char* string) {
    plugin::Call<0x69E160, const char*>(string);
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
