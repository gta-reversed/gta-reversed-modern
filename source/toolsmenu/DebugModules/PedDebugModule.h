#pragma once

#include "DebugModule.h"

class PedDebugModule final : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "PedDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PedDebugModule, m_CollapseToggleDist, m_DrawDist, m_IsVisible, m_AutoCollapseEnabled, m_IsOpen);

private:
    void ProcessPed(struct PedInfo&);

private:
    float m_CollapseToggleDist{ 20.f };
    float m_DrawDist{ 200.f };
    bool  m_IsVisible{};
    bool  m_AutoCollapseEnabled{};
    bool  m_IsOpen{};
};
