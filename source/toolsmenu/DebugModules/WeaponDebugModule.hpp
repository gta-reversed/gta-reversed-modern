#pragma once

#include "DebugModule.h"

namespace notsa { 
namespace debugmodules {
class WeaponDebugModule final : public DebugModule {
public:
    void RenderWindow() override;
    void RenderMenuEntry() override; 
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "WeaponDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(WeaponDebugModule, m_IsOpen);

private:
    bool m_IsOpen{};
};
}; // namespace debugmodules
}; // namespace notsa
