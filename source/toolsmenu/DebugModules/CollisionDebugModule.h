#pragma once

#include "DebugModule.h"


class CollisionDebugModule final : public DebugModule {
public:
    void RenderMenuEntry() override final;
    void Render3D() override final;
    void RenderWindow() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "CollisionDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CollisionDebugModule, m_VisuEnabled, m_DrawBoxes, m_DrawLines, m_DrawSpheres, m_DrawTris, m_DrawBBs, m_DrawShdwTris, m_IsOpen);

private:
    void DrawColModel(const CMatrix& matrix, const CColModel& cm);
    void RenderVisibleColModels();

private:
    // Visualization
    bool m_VisuEnabled{ false };
    bool m_DrawBoxes{ true };
    bool m_DrawLines{ true };
    bool m_DrawSpheres{ true };
    bool m_DrawTris{ true };
    bool m_DrawBBs{ true };
    bool m_DrawShdwTris{ true };

    // Window
    bool m_IsOpen{};
};
