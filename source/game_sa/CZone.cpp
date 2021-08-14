#include "StdInc.h"

const char* CZone::GetTranslatedName() const {
    return TheText.Get(m_szTextKey);
}
