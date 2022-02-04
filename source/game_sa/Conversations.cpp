#include "StdInc.h"

#include "Conversations.h"

void CPedToPlayerConversations::Clear() {
    plugin::Call<0x43AAE0>();
}

void CConversations::Clear() {
    plugin::Call<0x43A7B0>();
}
