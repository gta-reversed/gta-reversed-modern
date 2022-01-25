#include "StdInc.h"

void CInformGroupEventQueue::InjectHooks() {
    Install("CInformGroupEventQueue", "Init", 0x4B2AD0, &CInformGroupEventQueue::Init);
//    Install("CInformGroupEventQueue", "Add", 0x4B7CD0, &CInformGroupEventQueue::Add);
//    Install("CInformGroupEventQueue", "Flush", 0x4AC410, &CInformGroupEventQueue::Flush);
//    Install("CInformGroupEventQueue", "Process", 0x4B2AE0, &CInformGroupEventQueue::Process);
}

// 0x4B2AD0
void CInformGroupEventQueue::Init() {
    CInformGroupEventQueue::Flush();
}

// 0x4B7CD0
bool CInformGroupEventQueue::Add(CEntity* pEntity, CPedGroup* pPedGroup, CEvent* pEvent) {
    return plugin::CallAndReturn<bool, 0x4B7CD0, CEntity*, CPedGroup*, CEvent*>(pEntity, pPedGroup, pEvent);
}

// 0x4AC410
void CInformGroupEventQueue::Flush() {
    plugin::Call<0x4AC410>();
}

// 0x4B2AE0
void CInformGroupEventQueue::Process() {
    plugin::Call<0x4B2AE0>();
}

