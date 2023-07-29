#include "StdInc.h"

#include "Zone.h"

// Returns pointer to GXT name string.
// 0x5720C0
const char* CZone::GetTranslatedName() const {
    return TheText.Get(m_TextLabel);
}
