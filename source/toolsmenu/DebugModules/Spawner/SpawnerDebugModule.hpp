#pragma once

#include "../DebugModule.h"

class SpawnerDebugModule final : public DebugModule {
public:
    SpawnerDebugModule();

    void RenderWindow() override final;
    void RenderMenuEntry() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "SpawnerDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SpawnerDebugModule, m_IsOpen); // Good enough for now (Would need a refactor for other stuff....)

private:
    bool m_IsOpen{};
};
