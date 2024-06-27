#pragma once

#include "DebugModule.h"

class AudioZonesDebugModule final : public DebugModule {
public:
    void Render3D() override final;
    void RenderMenuEntry() override final;
    json Serialize() const override { return *this; }
    void Deserialize(const json& j) override { from_json(j, *this); }
    std::string_view GetID() const { return "AudioZonesDebugModule"; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(AudioZonesDebugModule, m_IsOpen, m_ShowAudioZones);

private:
    bool m_IsOpen{};
    bool m_ShowAudioZones{};

    CMatrix m_Transform = CMatrix::GetIdentity();
};
