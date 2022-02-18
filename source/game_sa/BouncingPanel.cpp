#include "StdInc.h"
#include "BouncingPanel.h"

// 0x6F4910
void CBouncingPanel::ResetPanel() {
    m_nFrameId = -1;
}

// 0x6F4920
void CBouncingPanel::SetPanel(int16 frameId, int16 axis, float angleLimit) {
    return plugin::CallMethodAndReturn<void, 0x6F4920>(this, frameId, axis, angleLimit);
}

// 0x6F49A0
void CBouncingPanel::ProcessPanel(CVehicle* vehicle, RwFrame* frame, CVector a3, CVector a4, float a5, float a6) {
    plugin::CallMethod<0x6F49A0, CBouncingPanel*, CVehicle*, RwFrame*, CVector, CVector, float, float>(this, vehicle, frame, a3, a4, a5, a6);
}
