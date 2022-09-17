#include "StdInc.h"

#include "InformGroupEventQueue.h"

void CInformGroupEventQueue::InjectHooks() {
    RH_ScopedClass(CInformGroupEventQueue);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x4B2AD0);
RH_ScopedInstall(Add, 0x4B7CD0, { .reversed = false });
RH_ScopedInstall(Flush, 0x4AC410, { .reversed = false });
RH_ScopedInstall(Process, 0x4B2AE0, { .reversed = false });
}

// 0x4B2AD0
void CInformGroupEventQueue::Init() {
    CInformGroupEventQueue::Flush();
}

// 0x4B7CD0
bool CInformGroupEventQueue::Add(CEntity* entity, CPedGroup* pedGroup, CEvent* event) {
    return plugin::CallAndReturn<bool, 0x4B7CD0, CEntity*, CPedGroup*, CEvent*>(entity, pedGroup, event);
}

// 0x4AC410
void CInformGroupEventQueue::Flush() {
    plugin::Call<0x4AC410>();
}

// 0x4B2AE0
void CInformGroupEventQueue::Process() {
    plugin::Call<0x4B2AE0>();
}

