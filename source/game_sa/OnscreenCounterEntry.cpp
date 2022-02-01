#include "StdInc.h"
#include "OnscreenCounterEntry.h"

void COnscreenCounterEntry::InjectHooks() {
    RH_ScopedClass(COnscreenCounterEntry);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(ProcessForDisplayCounter, 0x44CA90);
    RH_ScopedInstall(SetColourID, 0x44CB00);
}

void COnscreenCounterEntry::Init() {
    Clear();

    m_szDisplayedText[0]       = '\0';
    m_bFlashWhenFirstDisplayed = false;
    m_nColourId                = HUD_COLOUR_RED;
}

void COnscreenCounterEntry::Clear() {
    m_nVarId                  = 0;
    m_nMaxVarValue            = 0;
    m_szDescriptionTextKey[0] = '\0';
    m_nType                   = eOnscreenCounter::SIMPLE;
    m_bEnabled                = false;
}

// 0x44CA90
void COnscreenCounterEntry::ProcessForDisplayCounter(eOnscreenCounter type) {
    const auto left = std::max<int32>(0, CTheScripts::ScriptSpace[m_nVarId]);

    if (type == eOnscreenCounter::SIMPLE || type == eOnscreenCounter::LINE) {
        sprintf(m_szDisplayedText, "%d", left);
    } else if (type == eOnscreenCounter::DOUBLE) {
        sprintf(m_szDisplayedText, "%d / %d", left, CTheScripts::ScriptSpace[m_nMaxVarValue]);
    }
}

// 0x44CB00
void COnscreenCounterEntry::SetColourID(eHudColours colorId) {
    m_nColourId = colorId;
}
