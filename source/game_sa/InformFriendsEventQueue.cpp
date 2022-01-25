#include "StdInc.h"

void CInformFriendsEventQueue::InjectHooks() {
//    Install("CInformFriendsEventQueue", "Constructor", 0x0, &CInformFriendsEventQueue::Constructor);
//    Install("CInformFriendsEventQueue", "Destructor", 0x0, &CInformFriendsEventQueue::Destructor);
//    Install("CInformFriendsEventQueue", "Init", 0x4B2990, &CInformFriendsEventQueue::Init);
//    Install("CInformFriendsEventQueue", "Flush", 0x4AC2A0, &CInformFriendsEventQueue::Flush);
//    Install("CInformFriendsEventQueue", "Add", 0x4AC1E0, &CInformFriendsEventQueue::Add);
//    Install("CInformFriendsEventQueue", "Process", 0x4AC2E0, &CInformFriendsEventQueue::Process);
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
