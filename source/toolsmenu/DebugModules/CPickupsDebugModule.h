#pragma once

#include "DebugModule.h"

class CPickupsDebugModule final : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "PickupsDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CPickupsDebugModule, m_IsOpen, m_FilterInactive, m_FilterInvisible, m_SelectedPickupIdx);

private:
    void DrawTable();

private:
    bool  m_IsOpen{};
    bool  m_FilterInactive{true};
    bool  m_FilterInvisible{};
    int32 m_SelectedPickupIdx{};
};
