#pragma once

#include "DebugModule.h"

class COcclusionDebugModule : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;
    void Render3D() override final;

private:
    bool m_IsOpen{};
    bool m_DrawActiveOcclusions;
};
