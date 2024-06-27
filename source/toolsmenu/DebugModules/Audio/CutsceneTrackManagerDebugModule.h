#pragma once

#include "../DebugModule.h"

class CutsceneTrackManagerDebugModule : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "CutsceneTrackManagerDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CutsceneTrackManagerDebugModule, m_IsOpen);

private:
    bool m_IsOpen{};
};
