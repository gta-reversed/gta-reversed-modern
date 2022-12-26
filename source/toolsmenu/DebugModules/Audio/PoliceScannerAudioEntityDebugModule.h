#pragma once

#include "DebugModule.h"

class PoliceScannerAudioEntityDebugModule : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;

private:
    bool m_IsOpen{};
};
