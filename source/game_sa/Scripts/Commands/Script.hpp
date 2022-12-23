#pragma once
#include "AudioEngine.h"
#include "FireManager.h"
#include "Timer.h"
#include "Streaming.h"
#include "TheScripts.h"
#include "CommandParser/Parser.hpp"

/*!
* Various Script commands
*/

void TerminateAllScriptsWithThisName(const char* name) {
    std::string scriptName{name};
    rng::transform(scriptName, scriptName.begin(), [](char c) { return std::tolower(c); });

    for (auto* script = CTheScripts::pActiveScripts; script; script = script->m_pNext) {
        if (!strcmp(scriptName.c_str(), script->m_szName)) {
            script->RemoveScriptFromList(&CTheScripts::pActiveScripts);
            script->AddScriptToList(&CTheScripts::pIdleScripts);
            script->ShutdownThisScript();
        }
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME, TerminateAllScriptsWithThisName);

void RemoveAllScriptFires() {
    gFireManager.RemoveAllScriptFires();
}
REGISTER_COMMAND_HANDLER(COMMAND_REMOVE_ALL_SCRIPT_FIRES, RemoveAllScriptFires);

void LoadScene(CVector point) {
    CTimer::Stop();
    CStreaming::LoadScene(point);
    CTimer::Update();
}
REGISTER_COMMAND_HANDLER(COMMAND_LOAD_SCENE, LoadScene);

void LoadSceneInDirection(CVector point, float heading) {
    CTimer::Stop();
    CRenderer::RequestObjectsInDirection(point, heading, STREAMING_LOADING_SCENE);
    CStreaming::LoadScene(point);
    CTimer::Update();
}
REGISTER_COMMAND_HANDLER(COMMAND_LOAD_SCENE_IN_DIRECTION, LoadSceneInDirection);

void AddStuckCarCheck(int32 carHandle, float distance, uint32 time) {
    CTheScripts::StuckCars.AddCarToCheck(carHandle, distance, time, 0, false, false, false, 0);
}
REGISTER_COMMAND_HANDLER(COMMAND_ADD_STUCK_CAR_CHECK, AddStuckCarCheck);

void RemoveStuckCarCheck(int32 carHandle) {
    CTheScripts::StuckCars.RemoveCarFromCheck(carHandle);
}
REGISTER_COMMAND_HANDLER(COMMAND_REMOVE_STUCK_CAR_CHECK, RemoveStuckCarCheck);

void LoadMissionAudio(uint32 slotId, int32 sampleId) {
    AudioEngine.PreloadMissionAudio(slotId - 1, sampleId);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOAD_MISSION_AUDIO, LoadMissionAudio);

void AttachMissionAudioToCar(uint32 slotId, CVehicle& veh) {
    AudioEngine.AttachMissionAudioToPhysical(slotId - 1, &veh);
}
REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_MISSION_AUDIO_TO_CAR, AttachMissionAudioToCar);

void PlayMissionAudio(uint32 slotId) {
    AudioEngine.PlayLoadedMissionAudio(slotId - 1);
}
REGISTER_COMMAND_HANDLER(COMMAND_PLAY_MISSION_AUDIO, PlayMissionAudio);

void DisplayNonMinigameHelpMessages(bool enable) {
    CTheScripts::bDisplayNonMiniGameHelpMessages = enable;
}
REGISTER_COMMAND_HANDLER(COMMAND_DISPLAY_NON_MINIGAME_HELP_MESSAGES, DisplayNonMinigameHelpMessages);

void SetPhotoCameraEffect(bool enable) {
    CTheScripts::bDrawCrossHair = enable ? eCrossHairType::FIXED_DRAW_1STPERSON_WEAPON : eCrossHairType::NONE;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_PHOTO_CAMERA_EFFECT, SetPhotoCameraEffect);

void DrawOddJobTitleBeforeFade(bool enable) {
    CTheScripts::bDrawOddJobTitleBeforeFade = enable;
}
REGISTER_COMMAND_HANDLER(COMMAND_DRAW_ODDJOB_TITLE_BEFORE_FADE, DrawOddJobTitleBeforeFade);

void DrawSubtitlesBeforeFade(bool enable) {
    CTheScripts::bDrawSubtitlesBeforeFade = enable;
}
REGISTER_COMMAND_HANDLER(COMMAND_DRAW_SUBTITLES_BEFORE_FADE, DrawSubtitlesBeforeFade);
