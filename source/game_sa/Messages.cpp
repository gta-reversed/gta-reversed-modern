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
    RH_ScopedInstall(AddToPreviousBriefArray, 0x69DD50);
    RH_ScopedInstall(ClearPreviousBriefArray, 0x69DE70);
    // RH_ScopedInstall(InsertNumberInString, 0x69DE90, { .reversed = false }); // Weird build error here
    RH_ScopedInstall(InsertStringInString, 0x69E040, { .reversed = false });
    RH_ScopedInstall(InsertPlayerControlKeysInString, 0x69E160, { .reversed = false });
    RH_ScopedInstall(AddMessageWithNumber, 0x69E360);
    RH_ScopedInstall(AddMessageJumpQWithNumber, 0x69E4E0);
    RH_ScopedInstall(AddBigMessageWithNumber, 0x69E5F0);
    RH_ScopedInstall(AddBigMessageWithNumberQ, 0x69E6E0);
    RH_ScopedInstall(AddMessageWithString, 0x69E800);
    RH_ScopedInstall(AddMessageJumpQWithString, 0x69E950);
    RH_ScopedInstall(ClearThisPrint, 0x69EA30);
    RH_ScopedInstall(ClearThisBigPrint, 0x69EBE0);
    RH_ScopedInstall(ClearThisPrintBigNow, 0x69ED80);
    RH_ScopedInstall(Init, 0x69EE00);
    RH_ScopedInstall(ClearAllMessagesDisplayedByGame, 0x69EDC0);
    RH_ScopedInstall(Process, 0x69EE60, { .reversed = false });
    RH_ScopedInstall(Display, 0x69EFC0, { .reversed = false });
    RH_ScopedInstall(AddMessage, 0x69F0B0);
    RH_ScopedInstall(AddMessageJumpQ, 0x69F1E0);
    RH_ScopedInstall(AddBigMessage, 0x69F2B0);
    RH_ScopedInstall(AddBigMessageQ, 0x69F370);
}

// Initialises messages
// 0x69EE00
void CMessages::Init() {
    ClearMessages(true);
    rng::fill(PreviousBriefs, tPreviousBrief{});
}

template<size_t N>
tMessage* FindUnusedMsgInArray(std::array<tMessage, N>& arr) {
    for (auto& msg : arr) {
        if (!msg.m_pText) {
            return &msg;
        }
    }
    DEV_LOG("No free brief message found!");
    return nullptr;
}

// notsa
tMessage* CMessages::FindFreeBriefMessage() {
    return FindUnusedMsgInArray(BriefMessages);
}

/*********************
* BRIEF MESSAGES
**********************/

/*!
* Add a new brief message.
* @param text           The text (Possibly with format characters, eg.: ~~~~
* @param flag           Flags
* @param bPreviousBrief Whenever to call `AddToPreviousBriefArray`
* @param showInstantly  Whenever to show the message instantly
* @param str            String to insert [May be null]
* @param numbers        Numbers to insert (Use -1 as placeholder)
* @notsa
*/
void CMessages::AddMessage2(const char* text, uint32 time, uint16 flag, bool bPreviousBrief, bool showInstantly, char* str, std::optional<std::array<int32, 6>> numbers) {
    const auto msg = FindFreeBriefMessage();
    if (!msg) {
        return;
    }
    new (msg) tMessage{
        text,
        str,
        flag,
        time,
        bPreviousBrief,
        numbers
    };
    if (bPreviousBrief && (showInstantly || msg == &BriefMessages.front())) {
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

/*!
* Adds message to queue
* @addr 0x69F0B0
*/
void CMessages::AddMessage(const char* text, uint32 time, uint16 flag, bool bPreviousBrief) {
    /* Some string copy code here */
    AddMessage2(text, time, flag, bPreviousBrief);
}

/*!
* Adds message to queue [With string in `text`]
* @addr 0x69E800
*/
void CMessages::AddMessageWithString(const char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief) {
    /* Some string copy code here */
    AddMessage2(text, time, flag, bPreviousBrief, false, string);
}

/*!
* Show a message instantly
* @addr 0x69F1E0
*/
void CMessages::AddMessageJumpQ(const char* text, uint32 time, uint16 flag, bool bPreviousBrief) {
    /* unused string copy here */
    AddMessage2(text, time, flag, bPreviousBrief, true);
}

/*!
* Adds message to queue [With numbers in `text`]
* @addr 0x69E360
*/
void CMessages::AddMessageWithNumber(const char* text, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, bool bPreviousBrief) {
    /* Some string copy code here */
    AddMessage2(text, time, flag, bPreviousBrief, false, nullptr, { { n1, n2, n3, n4, n5, n6 } });
}

/*!
* Show a message instantly [With numbers in `text`]
* @addr 0x69E4E0
*/
void CMessages::AddMessageJumpQWithNumber(const char* text, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, bool bPreviousBrief) {
    AddMessage2(text, time, flag, bPreviousBrief, false, nullptr, { { n1, n2, n3, n4, n5, n6 } });
}

/*!
* Show a message instantly [With a string in `text`]
* @addr 0x69E950
*/
void CMessages::AddMessageJumpQWithString(const char* text, uint32 time, uint16 flag, char* string, bool bPreviousBrief) {
    AddMessage2(text, time, flag, bPreviousBrief, false, string);
}

/*********************
* BIG MESSAGES
**********************/

/*!
* Add a new big message.
* @param text           The text (Possibly with format characters, eg.: ~~~~)
* @param bPreviousBrief Whenever to call `AddToPreviousBriefArray`
* @param showInstantly  Whenever to show the message instantly
* @param str            String to insert [May be null]
* @param numbers        Numbers to insert (Use -1 as placeholder)
* @notsa
*/
void CMessages::AddBigMessage2(const char* text, uint32 time, eMessageStyle style, char* str, std::optional<std::array<int32, 6>> numbers) {
    if (const auto msg = FindUnusedMsgInArray(BIGMessages[style].m_Stack)) {
        new (msg) tMessage{
            text,
            str,
            0,
            time,
            false,
            numbers
        };
    }
}

// Adds big message and shows it instantly
// 0x69F2B0
void CMessages::AddBigMessage(const char* text, uint32 time, eMessageStyle style) {
    AddBigMessage2(text, time, style);
}

// Adds big message to queue
// 0x69F370
void CMessages::AddBigMessageQ(const char* text, uint32 time, eMessageStyle style) {
    AddBigMessage2(text, time, style);
}

// Adds big message with numbers and shows it instantly
// 0x69E5F0
void CMessages::AddBigMessageWithNumber(const char* text, uint32 time, eMessageStyle style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6) {
    AddBigMessage2(text, time, style, nullptr, { { n1, n2, n3, n4, n5, n6 } });
}

// Adds big message with numbers to queue
// 0x69E6E0
void CMessages::AddBigMessageWithNumberQ(const char* text, uint32 time, eMessageStyle style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6) {
    AddBigMessageWithNumber(text, time, style, n1, n2, n3, n4, n5, n6);
}

// Adds message to previous brief
// 0x69DD50
void CMessages::AddToPreviousBriefArray(const char* text, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, char* string) {
    const auto numbers = std::array{ n1, n2, n3, n4, n5, n6 };

    // Find unused entry + duplicate check
    size_t i = 0;
    for (; i < PreviousBriefs.size(); i++) {
        const auto& prev = PreviousBriefs[i];
        if (!prev.m_pText) {
            break; // Found unused
        }
        // Check if it's a duplicate of the one we're about to insert
        if (prev.m_pText != text || prev.m_pString != string) { // I mean that's a pretty naive way, but okay
            continue;
        }
        if (numbers != prev.m_nNumber) {
            continue; 
        }
        return; // Duplicate messages after each other, so skip
    }

    // In case no free entries were found we overwrite the last one
    if (i == PreviousBriefs.size()) {
        i = PreviousBriefs.size() - 1;
    }

    // Move entries so that we overwrite the unused entry at `i` and thus free up the 0th entry
    // if `i == 0` this won't do anything.
    std::shift_right(
        PreviousBriefs.begin(),
        PreviousBriefs.begin() + i,
        1
    );

    // Now construct at the 0th enry (as it's now freed up)
    new (&PreviousBriefs[0]) tPreviousBrief {
        .m_pText   = text,
        .m_nNumber = numbers,
        .m_pString = string,
    };
}

// Removes registered messages
// 0x69DCD0
void CMessages::ClearMessages(bool flag) {
    rng::fill(BIGMessages, tBigMessage{});
    ClearSmallMessagesOnly();
}

// Removes small messages
// 0x69DD30
void CMessages::ClearSmallMessagesOnly() {
    rng::fill(BriefMessages, tMessage{});
}

// Remove messages from previous brief
// 0x69DE70
void CMessages::ClearPreviousBriefArray() {
    rng::fill(PreviousBriefs, tPreviousBrief{});
}

template<size_t N>
void ClearThisPrint_Impl(std::array<tMessage, N>& messages, const char* text, auto&& OnFirstMessageCleared) {
    for (;;) {
        size_t i = 0;
        for (;;) {
            const auto& msg = messages[i];
            if (!msg.m_pText) {
                return; // Reached end of active texts
            }
            if (strcmp(msg.m_pText, text) == 0) {
                break; // Texts match, so clear this
            }
            if (++i >= messages.size()) {
                return; // Reached end
            }
        }
        
        // Overwrite this element
        std::shift_left(
            messages.begin() + i,
            messages.end(),
            1
        );

        // Clear last (As it was left in an unspecified state)
        messages.back() = {};

        if (i == 0) {
            auto& msg = messages[i];
            msg.m_nStartTime = CTimer::GetTimeInMS();
            if (OnFirstMessageCleared) {
                OnFirstMessageCleared(msg);
            }
        }
    }
}

// Removes small message with this text
// 0x69EA30
void CMessages::ClearThisPrint(const char* text) {
    ClearThisPrint_Impl(BriefMessages, text, [](tMessage& msg) {
        if (!msg.m_pText) {
            return;
        }
        AddToPreviousBriefArray(
            msg.m_pText,
            msg.m_nNumber[0],
            msg.m_nNumber[1],
            msg.m_nNumber[2],
            msg.m_nNumber[3],
            msg.m_nNumber[4],
            msg.m_nNumber[5],
            msg.m_pString
        );
    });
}

// Removes big message with this text
// 0x69EBE0
void CMessages::ClearThisBigPrint(const char* text) {
    for (size_t b = 0; b < NUM_MESSAGE_STYLES; b++) {
        ClearThisPrint_Impl(BIGMessages[b].m_Stack, text, [](tMessage&) { /*nop*/ });
    }
}

// Removes first big message in messages stack
// 0x69ED80
void CMessages::ClearThisPrintBigNow(eMessageStyle style) {
    for (auto& msg : BIGMessages[style].m_Stack) {
        ClearThisBigPrint(msg.m_pText);
    }
    CHud::BigMessageX[style] = 0.f;
    CHud::m_BigMessage[style][0] = 0;
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
