#pragma once

#include "DebugModule.h"

namespace notsa { 
namespace debugmodules {
class ScriptDebugModule final : public DebugModule {
public:
    void RenderWindow() override;
    void RenderMenuEntry() override;
    void Render3D() override;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "ScriptDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ScriptDebugModule, m_IsOpen);

private:
    bool m_IsOpen{};
};
}; // namespace debugmodules
}; // namespace notsa

