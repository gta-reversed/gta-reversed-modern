#include "StdInc.h"

#include "CutsceneTrackManagerDebugModule.h"

#include <imgui.h>
#include "AECutsceneTrackManager.h"

namespace CutsceneTrackManagerDebugModule {

void ProcessImgui() {
    ImGui::Text("Play Request %s",      AECutsceneTrackManager.m_bPlayRequest ? "true" : "false");
    ImGui::Text("Paused %s",            AECutsceneTrackManager.m_bPaused ? "true" : "false");
    ImGui::Text("Audio Channel Id: %d", AECutsceneTrackManager.m_nAudioChannel);
    ImGui::Text("Status: %d",           AECutsceneTrackManager.m_nStatus);
    ImGui::Text("Track Id: %d",         AECutsceneTrackManager.m_nTrackId);
    ImGui::Text("f10: %d",              AECutsceneTrackManager._f10);
    ImGui::Text("f14: %d",              AECutsceneTrackManager._f14);
    ImGui::Text("f18: %d",              AECutsceneTrackManager._f18);
    ImGui::Text("Is User Track: %d",    AECutsceneTrackManager.m_bIsUserTrack);
    ImGui::Text("pad: %d",              AECutsceneTrackManager._pad);
    ImGui::Text("Playing Track Id: %d", AECutsceneTrackManager.m_nPlayingTrackId);
    ImGui::Text("Track Play Time: %d",  AECutsceneTrackManager.m_nTrackPlayTime);
    ImGui::Text("Track Length Ms: %d",  AECutsceneTrackManager.m_nTrackLengthMs);
}

void ProcessRender() {}

} // namespace CutsceneTrackManagerDebugModule
