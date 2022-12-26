#pragma once

#include <DebugModule.h>


class CollisionDebugModule : public DebugModule {
public:
    void RenderMenuEntry() override final;
    void Render3D() override final;

private:
    void DrawColModel(const CMatrix& matrix, const CColModel& cm);
    void RenderVisibleColModels();

private:
    bool m_Enabled{ false };
    bool m_DrawBoxes{ true };
    bool m_DrawLines{ true };
    bool m_DrawSpheres{ true };
    bool m_DrawTris{ true };
    bool m_DrawBBs{ true };
    bool m_DrawShdwTris{ true };
};
