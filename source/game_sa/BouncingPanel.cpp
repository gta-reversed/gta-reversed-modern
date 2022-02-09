#include "StdInc.h"

void CBouncingPanel::ResetPanel() {
    m_nFrameId = -1;
}

void CBouncingPanel::SetPanel(int16 frameId, int16 axis, float angleLimit) {
    return plugin::CallMethodAndReturn<void, 0x6F4920>(this, frameId, axis, angleLimit);
}
