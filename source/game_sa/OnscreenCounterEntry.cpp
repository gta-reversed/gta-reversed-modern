#include "StdInc.h"
#include "OnscreenCounterEntry.h"

void COnscreenCounterEntry::InjectHooks() {
    RH_ScopedClass(COnscreenCounterEntry);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(ProcessForDisplayCounter, 0x44CA90);
    RH_ScopedInstall(SetColourID, 0x44CB00);
}

// 0x44CA90
void COnscreenCounterEntry::ProcessForDisplayCounter(uint16 type) {
    const int32 value = std::max(0, *(int32*)CTheScripts::ScriptSpace[m_nVarId]);
    if (type <= 1) {
        sprintf(m_szDisplayedText, "%d", value);
    } else if (type == 2) {
        sprintf(m_szDisplayedText, "%d / %d", value, *(int32*)CTheScripts::ScriptSpace[m_nMaxVarValue]);
    }
}

// 0x44CB00
void COnscreenCounterEntry::SetColourID(uint8 colorId) {
    m_nColourId = colorId;
}
