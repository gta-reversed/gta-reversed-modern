#include "StdInc.h"

#include "Conversations.h"

void CPedToPlayerConversations::Clear() {
    plugin::Call<0x43AAE0>();
}

void CPedToPlayerConversations::Update() {
    plugin::Call<0x43B0F0>();
}

void CConversations::Clear() {
    plugin::Call<0x43A7B0>();
}

void CConversations::Update() {
    plugin::Call<0x43C590>();
}

// 0x43A960
void CConversations::RemoveConversationForPed(CPed* ped) {
    plugin::Call<0x43A960, CPed*>(ped);
}
