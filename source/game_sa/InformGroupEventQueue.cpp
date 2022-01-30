#include "StdInc.h"

void CInformGroupEventQueue::InjectHooks() {
    RH_ScopedClass(CInformGroupEventQueue);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x4B2AD0);
//    RH_ScopedInstall(Add, 0x4B7CD0);
//    RH_ScopedInstall(Flush, 0x4AC410);
//    RH_ScopedInstall(Process, 0x4B2AE0);
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

