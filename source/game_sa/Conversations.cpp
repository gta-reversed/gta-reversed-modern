#include "StdInc.h"

#include "Conversations.h"

void CPedToPlayerConversations::Clear() {
    ZoneScoped;

    plugin::Call<0x43AAE0>();
}

void CPedToPlayerConversations::Update() {
    plugin::Call<0x43B0F0>();
}

void CConversations::Clear() {
    ZoneScoped;

    plugin::Call<0x43A7B0>();
}

void CConversations::Update() {
    ZoneScoped;

    plugin::Call<0x43C590>();
}

// 0x43A870
void CConversations::SetUpConversationNode(
    const char* questionKey,
    const char* answerYesKey,
    const char* answerNoKey,
    int32 questionWAV,
    int32 answerYesWAV,
    int32 answerNoWAV) {
    plugin::Call<0x43A870, const char*, const char*, const char*, int32, int32, int32>(questionKey, answerYesKey, answerNoKey, questionWAV, answerYesWAV, answerNoWAV);
}

// 0x43A960
void CConversations::RemoveConversationForPed(CPed* ped) {
    plugin::Call<0x43A960, CPed*>(ped);
}
