#include "StdInc.h"

void CInformFriendsEventQueue::InjectHooks() {
    RH_ScopedClass(CInformFriendsEventQueue);
    RH_ScopedCategoryRoot();

//    RH_ScopedInstall(Constructor, 0x0);
//    RH_ScopedInstall(Destructor, 0x0);
//    RH_ScopedInstall(Init, 0x4B2990);
//    RH_ScopedInstall(Flush, 0x4AC2A0);
//    RH_ScopedInstall(Add, 0x4AC1E0);
//    RH_ScopedInstall(Process, 0x4AC2E0);
}

// 0x
CInformFriendsEventQueue::CInformFriendsEventQueue() {

}

CInformFriendsEventQueue* CInformFriendsEventQueue::Constructor() {
    this->CInformFriendsEventQueue::CInformFriendsEventQueue();
    return this;
}

// 0x
CInformFriendsEventQueue::~CInformFriendsEventQueue() {

}

CInformFriendsEventQueue* CInformFriendsEventQueue::Destructor() {
    this->CInformFriendsEventQueue::~CInformFriendsEventQueue();
    return this;
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
bool CInformFriendsEventQueue::Add(CEntity* pEntity, CEvent* pEvent) {
    return plugin::CallAndReturn<bool, 0x4AC1E0, CEntity*, CEvent*>(pEntity, pEvent);
}

// 0x4AC2E0
void CInformFriendsEventQueue::Process() {
    plugin::Call<0x4AC2E0>();
}
