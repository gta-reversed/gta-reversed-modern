#include <StdInc.h>

#include "PoliceScannerAudioEntityDebugModule.h"
#include "AEPoliceScannerAudioEntity.h"

#include <imgui.h>

namespace PoliceScannerAudioEntityDebugModule {

void ProcessImGui() {
    ImGui::Text("Volume Offset %f", CAEPoliceScannerAudioEntity::s_fVolumeOffset);
    ImGui::Text("Stopping Scanner %d", CAEPoliceScannerAudioEntity::s_bStoppingScanner);
    ImGui::Text("Play Request %p", CAEPoliceScannerAudioEntity::s_pSound);
    ImGui::Text("Abort Playback Time %u", CAEPoliceScannerAudioEntity::s_nAbortPlaybackTime);
    ImGui::Text("Playback Start Time %u", CAEPoliceScannerAudioEntity::s_nPlaybackStartTime);
    ImGui::Text("Section Playing %d", CAEPoliceScannerAudioEntity::s_nSectionPlaying);

    ImGui::Text("Slot State");
    for (auto& v : CAEPoliceScannerAudioEntity::s_SlotState) {
        ImGui::SameLine();
        ImGui::Text("%d", v);
    }

    ImGui::Text("Current Slots %p", CAEPoliceScannerAudioEntity::s_pCurrentSlots);

    ImGui::Text("Scanner Slot First");
    for (auto& v : CAEPoliceScannerAudioEntity::s_ScannerSlotFirst) {
        ImGui::SameLine();
        ImGui::Text("%d:%d", v.bankId, v.sfxId);
    }

    ImGui::Text("Scanner Slot Second");
    for (auto& v : CAEPoliceScannerAudioEntity::s_ScannerSlotSecond) {
        ImGui::SameLine();
        ImGui::Text("%d:%d", v.bankId, v.sfxId);
    }

    ImGui::Text("PS Controlling %p", CAEPoliceScannerAudioEntity::s_pPSControlling);
    ImGui::Text("Scanner Playback State %d", CAEPoliceScannerAudioEntity::s_nScannerPlaybackState);
    ImGui::Text("Scanner Disabled %d", CAEPoliceScannerAudioEntity::s_bScannerDisabled);
    ImGui::Text("Next New Scanner DialogueTime %u", CAEPoliceScannerAudioEntity::s_NextNewScannerDialogueTime);
}

} // namespace PoliceScannerAudioEntityDebugModule
