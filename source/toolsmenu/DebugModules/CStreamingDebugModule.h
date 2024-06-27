#pragma once

#include "DebugModule.h"

class CStreamingDebugModule final : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "StreamingDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CStreamingDebugModule, m_IsOpen);

private:
    bool m_IsOpen{ false };
};
