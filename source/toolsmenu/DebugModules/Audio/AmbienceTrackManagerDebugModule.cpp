#include "StdInc.h"

#include "AmbienceTrackManagerDebugModule.h"

#include <imgui.h>
#include "AEAmbienceTrackManager.h"

namespace AmbienceTrackManagerDebugModule {

void ProcessImgui() {
    ImGui::Text("Stop %s",                           AEAmbienceTrackManager.m_bStop ? "true" : "false");
    ImGui::Text("Stop Prev %s",                      AEAmbienceTrackManager.m_bStopPrev ? "true" : "false");
    ImGui::Text("b3 %s",                             AEAmbienceTrackManager.m_b3 ? "true" : "false");
    ImGui::Text("Is Ambience Radio Active %d",       AEAmbienceTrackManager.m_IsAmbienceRadioActive);
    ImGui::Text("Channel Id %d",                     AEAmbienceTrackManager.m_nChannel);
    ImGui::Text("Special Mission Ambience Track %d", AEAmbienceTrackManager.m_nSpecialMissionAmbienceTrack);
    ImGui::Text("Track Play Time %d",                AEAmbienceTrackManager.m_nTrackPlayTime);
    ImGui::Text("Time In Ms %d",                     AEAmbienceTrackManager.m_nTimeInMs);
    ImGui::InputFloat("Volume %f",                  &AEAmbienceTrackManager.m_nVolume);
    ImGui::InputFloat("Frequency %f",               &AEAmbienceTrackManager.m_fFreqFactor);
    ImGui::InputInt("Track Id %d",                  &AEAmbienceTrackManager.m_nTrackId);
    ImGui::Text("dword24 %d",                        AEAmbienceTrackManager.dword24);
    ImGui::Text("byte28 %d",                         AEAmbienceTrackManager.byte28);
}

void ProcessRender() {}

} // namespace AmbienceTrackManagerDebugModule
