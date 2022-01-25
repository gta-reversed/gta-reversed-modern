#include "StdInc.h"

#include "BreakManager_c.h"

BreakManager_c& g_breakMan = *(BreakManager_c*)0xBB4240;

void BreakManager_c::InjectHooks() {
    using namespace ReversibleHooks;
    Install("BreakManager_c", "Init", 0x59E650, &BreakManager_c::Init);
    Install("BreakManager_c", "Exit", 0x59E660, &BreakManager_c::Exit);
    Install("BreakManager_c", "ResetAll", 0x59E720, &BreakManager_c::ResetAll);
    Install("BreakManager_c", "Add", 0x59E9B0, &BreakManager_c::Add);
    Install("BreakManager_c", "Update", 0x59E670, &BreakManager_c::Update);
    Install("BreakManager_c", "Render", 0x59E6A0, &BreakManager_c::Render);
}

// 0x59E650
bool BreakManager_c::Init() {
    return true;
}

// 0x59E660
void BreakManager_c::Exit() {
    // NOP
}

// 0x59E720
void BreakManager_c::ResetAll() {
    for (BreakObject_c& object : m_aObjects) {
        if (object.m_bActive) {
            object.Exit();
        }
    }
}

// 0x59E9B0
bool BreakManager_c::Add(CObject* object, CVector* vecPos, float fVelocityRand, bool bSmash) {
    BreakObject_c* slot = GetFirstFreeSlot();
    return slot && slot->Init(object, vecPos, fVelocityRand, bSmash);
}

// 0x59E700
BreakObject_c* BreakManager_c::GetFirstFreeSlot() {
    for (BreakObject_c& object : m_aObjects) {
        if (!object.m_bActive) {
            return &object;
        }
    }
    return nullptr;
}

// 0x59E670
void BreakManager_c::Update(float timeStep) {
    for (BreakObject_c& object : m_aObjects) {
        if (object.m_bActive) {
            object.Update(timeStep);
        }
    }
}

// 0x59E6A0
void BreakManager_c::Render(uint8 state) {
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(TRUE));

    for (BreakObject_c& object : m_aObjects) {
        if (object.m_bActive) {
            object.Render(state);
        }
    }
}
