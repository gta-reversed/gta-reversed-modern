#pragma once
#include "AudioEngine.h"
#include "FireManager.h"
#include "Timer.h"
#include "Streaming.h"
#include "TheScripts.h"
#include "Conversations.h"
#include "CommandParser/Parser.hpp"

/*!
* Various Script commands
*/

REGISTER_COMMAND_HANDLER(COMMAND_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME, [](const char* name) {
    std::string scriptName{name};
    rng::transform(scriptName, scriptName.begin(), [](char c) { return std::tolower(c); });

    for (auto* script = CTheScripts::pActiveScripts; script; script = script->m_pNext) {
        if (!strcmp(scriptName.c_str(), script->m_szName)) {
            script->RemoveScriptFromList(&CTheScripts::pActiveScripts);
            script->AddScriptToList(&CTheScripts::pIdleScripts);
            script->ShutdownThisScript();
        }
    }
});

REGISTER_COMMAND_HANDLER(COMMAND_REMOVE_ALL_SCRIPT_FIRES, []() { gFireManager.RemoveAllScriptFires(); });

REGISTER_COMMAND_HANDLER(COMMAND_LOAD_SCENE, [](CVector point) {
    CTimer::Stop();
    CStreaming::LoadScene(point);
    CTimer::Update();
});

REGISTER_COMMAND_HANDLER(COMMAND_LOAD_SCENE_IN_DIRECTION, [](CVector point, float heading) {
    CTimer::Stop();
    CRenderer::RequestObjectsInDirection(point, heading, STREAMING_LOADING_SCENE);
    CStreaming::LoadScene(point);
    CTimer::Update();
});

REGISTER_COMMAND_HANDLER(COMMAND_ADD_STUCK_CAR_CHECK, [](int32 carHandle, float distance, uint32 time) {
    CTheScripts::StuckCars.AddCarToCheck(carHandle, distance, time, 0, false, false, false, 0);
});

REGISTER_COMMAND_HANDLER(COMMAND_REMOVE_STUCK_CAR_CHECK, [](int32 carHandle) { CTheScripts::StuckCars.RemoveCarFromCheck(carHandle); });

REGISTER_COMMAND_HANDLER(COMMAND_LOAD_MISSION_AUDIO, [](uint32 slotId, int32 sampleId) { AudioEngine.PreloadMissionAudio(slotId - 1, sampleId); });

REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_MISSION_AUDIO_TO_CAR, [](uint32 slotId, CVehicle& veh) { AudioEngine.AttachMissionAudioToPhysical(slotId - 1, &veh); });

REGISTER_COMMAND_HANDLER(COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_CHAR, [](CPlayerPed& player, int32 eventId) { AudioEngine.ReportMissionAudioEvent(eventId, &player); });

REGISTER_COMMAND_HANDLER(COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_CAR, [](CVehicle& vehicle, int eventId) { AudioEngine.ReportMissionAudioEvent(eventId, &vehicle); });

REGISTER_COMMAND_HANDLER(COMMAND_PLAY_MISSION_AUDIO, [](uint32 slotId) { AudioEngine.PlayLoadedMissionAudio(slotId - 1); });

REGISTER_COMMAND_HANDLER(COMMAND_DISPLAY_NON_MINIGAME_HELP_MESSAGES, [](bool enable) { CTheScripts::bDisplayNonMiniGameHelpMessages = enable; });

REGISTER_COMMAND_HANDLER(COMMAND_SET_PHOTO_CAMERA_EFFECT, [](bool enable) {
    CTheScripts::bDrawCrossHair = enable ? eCrossHairType::FIXED_DRAW_1STPERSON_WEAPON : eCrossHairType::NONE;
});

REGISTER_COMMAND_HANDLER(COMMAND_DRAW_ODDJOB_TITLE_BEFORE_FADE, [](bool enable) { CTheScripts::bDrawOddJobTitleBeforeFade = enable; });

REGISTER_COMMAND_HANDLER(COMMAND_DRAW_SUBTITLES_BEFORE_FADE, [](bool enable) { CTheScripts::bDrawSubtitlesBeforeFade = enable; });

REGISTER_COMMAND_HANDLER(COMMAND_SET_PLAYER_IS_IN_STADIUM, [](bool enable) { CTheScripts::bPlayerIsOffTheMap = enable; });

REGISTER_COMMAND_HANDLER(COMMAND_SET_UP_CONVERSATION_NODE_WITH_SCRIPTED_SPEECH, [](
    const char* questionKey,
    const char* answerYesKey,
    const char* answerNoKey,
    int32 questionWAV,
    int32 answerYesWAV,
    int32 answerNoWAV) {
    CConversations::SetUpConversationNode(questionKey, answerYesKey, answerNoKey, questionWAV, answerYesWAV, answerNoWAV);
});
