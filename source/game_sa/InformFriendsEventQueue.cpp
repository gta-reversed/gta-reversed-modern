#include "StdInc.h"

#include "InformFriendsEventQueue.h"

void CInformFriendsEventQueue::InjectHooks() {
    RH_ScopedClass(CInformFriendsEventQueue);
    RH_ScopedCategoryGlobal();

    //RH_ScopedInstall(Constructor, 0x0, { .reversed = false });
    //RH_ScopedInstall(Destructor, 0x0, { .reversed = false });
    RH_ScopedInstall(Init, 0x4B2990, { .reversed = false });
    RH_ScopedInstall(Flush, 0x4AC2A0, { .reversed = false });
    RH_ScopedInstall(Add, 0x4AC1E0, { .reversed = false });
    RH_ScopedInstall(Process, 0x4AC2E0, { .reversed = false });
}

// 0x4B2990
void CInformFriendsEventQueue::Init() {
    CInformFriendsEventQueue::Flush();
}

// 0x4AC2A0
void CInformFriendsEventQueue::Flush() {
    plugin::Call<0x4AC2A0>();
}

// 0x4AC1E0
bool CInformFriendsEventQueue::Add(CEntity* entity, CEvent* event) {
    return plugin::CallAndReturn<bool, 0x4AC1E0, CEntity*, CEvent*>(entity, event);
}

// 0x4AC2E0
void CInformFriendsEventQueue::Process() {
    plugin::Call<0x4AC2E0>();
}
