#pragma once

#include <DebugModule.h>
#include "CDebugMenuToolInput.h"

class MissionDebugModule : public DebugModule {
public:
    MissionDebugModule();

    void RenderWindow() override final;
    void RenderMenuEntry() override final;

private:
    bool StartMission(int32 missionId, bool bDoMissionCleanUp);

private:
    bool                m_IsOpen{};

    bool                m_bStartMission{};
    int32               m_missionToStartId{};

    int32               m_SelectedMissionIdx{-1};

    CDebugMenuToolInput m_missionToolInput{};
};

