#pragma once

#include "DebugModule.h"

class ParticleDebugModule final : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "ParticleDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ParticleDebugModule, m_IsOpen);

private:
    bool m_IsOpen{};
};
