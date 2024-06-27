#pragma once

#include "DebugModule.h"

class COcclusionDebugModule final : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;
    void Render3D() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "COcclusionDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(COcclusionDebugModule, m_IsOpen, m_DrawActiveOcclusions);

private:
    bool m_IsOpen{};
    bool m_DrawActiveOcclusions;
};
