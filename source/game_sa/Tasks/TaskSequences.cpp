#include "StdInc.h"

int32& CTaskSequences::ms_iActiveSequence = *(int32*)0x8D2E98; // -1
CTaskComplexSequence (&CTaskSequences::ms_taskSequence)[NUM_SEQUENCES] = *(CTaskComplexSequence(*)[NUM_SEQUENCES])0xC178F0;
bool (&CTaskSequences::ms_bIsOpened)[NUM_SEQUENCES] = *(bool(*)[64])0xC17898;

void CTaskSequences::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CTaskSequences", "Init", 0x632D90, &CTaskSequences::Init);
    Install("CTaskSequences", "CleanUpForShutdown", 0x632DD0, &CTaskSequences::CleanUpForShutdown);
}

// 0x632D90
void CTaskSequences::Init() {
    ms_iActiveSequence = -1;
    CleanUpForShutdown();
}

// 0x632DD0
void CTaskSequences::CleanUpForShutdown() {
    for (auto i = 0; i < NUM_SEQUENCES; i++) {
        ms_bIsOpened[i] = false;
        auto taskSequence = &ms_taskSequence[i];
        taskSequence->Flush();
    }
}

// 0x632E00
int32 CTaskSequences::GetAvailableSlot(uint8 slot) {
    assert(false);
    return -1;
}
