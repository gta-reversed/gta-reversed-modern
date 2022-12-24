#pragma once

#include <DebugModule.h>


class CollisionDebugModule : public DebugModuleSingleWindow {
public:
    CollisionDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
    void Render3D() override final;

private:
    void DrawColModel(const CMatrix& matrix, const CColModel& cm);
    void RenderVisibleColModels();
private:
    bool m_visualizationEnabled{ false };
    bool m_drawBoxes{ true };
    bool m_drawLines{ true };
    bool m_drawSpheres{ true };
    bool m_drawTris{ true };
    bool m_drawBBs{ true };
    bool m_drawShdwTris{ true };
};
