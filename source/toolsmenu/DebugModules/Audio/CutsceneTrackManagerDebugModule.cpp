#include "StdInc.h"

#include "CutsceneTrackManagerDebugModule.h"

#include <imgui.h>
#include "AECutsceneTrackManager.h"

namespace CutsceneTrackManagerDebugModule {

void ProcessImgui() {
    ImGui::Text("Play Request %s", AECutsceneTrackManager.m_bPlayRequest ? "true" : "false");
    ImGui::Text("Paused %s", AECutsceneTrackManager.m_bPaused ? "true" : "false");
    ImGui::Text("Audio Channel Id: %d", AECutsceneTrackManager.m_nAudioChannel);
    ImGui::Text("Status: %d", AECutsceneTrackManager.m_nStatus);
    ImGui::Text("Track Id: %d", AECutsceneTrackManager.m_nTrackId);
    // int32  _f10;
    // uint32 _f14;
    // int32  _f18;
    ImGui::Text("Is User Track: %d", AECutsceneTrackManager.m_bIsUserTrack);
    // char   _pad[4];
    ImGui::Text("Playing Track Id: %d", AECutsceneTrackManager.m_nPlayingTrackId);
    ImGui::Text("Track Play Time: %d", AECutsceneTrackManager.m_nTrackPlayTime);
    ImGui::Text("Track Length Ms: %d", AECutsceneTrackManager.m_nTrackLengthMs);
}

void ProcessRender() {}

} // namespace CutsceneTrackManagerDebugModule
