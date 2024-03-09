#pragma once

#include "DebugModule.h"

class AudioZonesDebugModule : public DebugModule {
public:
    void Render3D() override final;
    void RenderMenuEntry() override final;

private:
    bool m_ShowAudioZones{};
    bool m_IsOpen{};

    CMatrix m_transform = CMatrix::GetIdentity();
};
