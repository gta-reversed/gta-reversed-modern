#include "StdInc.h"
#include "COnscreenCounterEntry.h"

void COnscreenCounterEntry::InjectHooks() {
    ReversibleHooks::Install("COnscreenCounterEntry", "ProcessForDisplayCounter", 0x44CA90, &COnscreenCounterEntry::ProcessForDisplayCounter);
    ReversibleHooks::Install("COnscreenCounterEntry", "SetColourID", 0x44CB00, &COnscreenCounterEntry::SetColourID);
}

// 0x44CA90
void COnscreenCounterEntry::ProcessForDisplayCounter(uint16_t type) {
    const int value = std::max(0, *(int*)CTheScripts::ScriptSpace[m_nVarId]);
    if (type <= 1) {
        sprintf(m_szDisplayedText, "%d", value);
    } else if (type == 2) {
        sprintf(m_szDisplayedText, "%d / %d", value, *(int*)CTheScripts::ScriptSpace[m_nMaxVarValue]);
    }
}

// 0x44CB00
void COnscreenCounterEntry::SetColourID(uint8_t colorId) {
    m_nColourId = colorId;
}
