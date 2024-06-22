#pragma once

#include "DebugModule.h"

namespace notsa { 
namespace debugmodules {
class CheckpointsDebugModule final : public DebugModule {
public:
    void RenderWindow() override;
    void RenderMenuEntry() override; 

private:
    bool       m_IsOpen{};
    int        m_SelectedTypeIdx{};
    int        m_CurrentID{1};
    CVector    m_Pos{};
    bool       m_UsePlayersPosition{true};
    CVector    m_Dir{};
    bool       m_UsePlayersDir{true};
    float      m_Size{1.f};
    RwRGBAReal m_Color{ 1.f, 0.f, 0.f, 1.f };
    int        m_PulsePeriod{1'024};
    float      m_PulseFraction{0.25f};
    int        m_RotateRate{5};
    bool       m_PlaceOneRandom{};
};
}; // namespace debugmodules
}; // namespace notsa

