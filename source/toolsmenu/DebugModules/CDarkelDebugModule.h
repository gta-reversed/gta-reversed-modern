#pragma once

#include <DebugModule.h>

class DarkelDebugModule : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;

private:
    bool m_IsOpen{};

    int32 m_WeaponType{ 30 };
    int32 m_TimeLimit{ 120 };
    int32 m_NumKillsNeeded{ 10 };
    int32 m_ModelsToKill[4]{ -1, -1, -1, -1 };
    bool  m_StandardSoundAndMsg{ true };
    bool  m_IsHeadshotRequired{ false };
};
