#pragma once

#include "DebugModule.h"

namespace notsa {
namespace debugmodules {
class ImGuiDebugModule final : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "ImGuiDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ImGuiDebugModule, m_MetricsOpen, m_AboutOpen, m_DemoOpen);

private:
    bool m_MetricsOpen{};
    bool m_AboutOpen{};
    bool m_DemoOpen{};
    bool m_RequestedRestart{};
};
}; // namespace debugmodules
}; // namespace notsa
