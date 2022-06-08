#include "StdInc.h"

#include "RunningScript.h"
#include "TaskSimpleSwim.h"
#include "TaskComplexProstituteSolicit.h"

// 0x479DA0
OpcodeResult CRunningScript::ProcessCommands2600To2699(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_SWIM_SPEED: // 0xA28
    {
        CollectParameters(2);
        auto* ped = GetPedPool()->GetAt(ScriptParams[0].iParam);
        if (!ped) return OR_CONTINUE;

        auto* task = ped->GetIntelligence()->GetTaskSwim();
        if (!task) return OR_CONTINUE;

        task->m_fAnimSpeed = ScriptParams[1].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_IS_PLAYER_CLIMBING: // 0xA29
    {
        const auto* player = FindPlayerPed(ScriptParams[0].iParam);
        const auto* task   = player->GetIntelligence()->GetTaskClimb();
        UpdateCompareFlag(task != nullptr);
        return OR_CONTINUE;
    }
    case COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED: // 0xA2A
        break;
    case COMMAND_IS_WIDESCREEN_ON_IN_OPTIONS: // 0xA2B
    {
        UpdateCompareFlag(FrontEndMenuManager.m_bWidescreenOn);
        return OR_CONTINUE;
    }
    case COMMAND_DRAW_SUBTITLES_BEFORE_FADE: // 0xA2C
        CollectParameters(1);
        CTheScripts::bDrawSubtitlesBeforeFade = ScriptParams[0].u8Param;
        return OR_CONTINUE;
    case COMMAND_DRAW_ODDJOB_TITLE_BEFORE_FADE: // 0xA2D
        CollectParameters(1);
        CTheScripts::bDrawOddJobTitleBeforeFade = ScriptParams[0].u8Param;
        return OR_CONTINUE;
    case COMMAND_TASK_FOLLOW_PATH_NODES_TO_COORD_WITH_RADIUS: // 0xA2E
        break;
    case COMMAND_SET_PHOTO_CAMERA_EFFECT: // 0xA2F
        CollectParameters(1);
        CTheScripts::bDrawCrossHair = ScriptParams[0].uParam != 0 ? 2 : 0;
        return OR_CONTINUE;
    case COMMAND_FIX_CAR: // 0xA30
    {
        CollectParameters(1);
        auto vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam);
        vehicle->Fix();
        vehicle->m_fHealth = 1000.0f;
        return OR_CONTINUE;
    }
    case COMMAND_SET_PLAYER_GROUP_TO_FOLLOW_NEVER: // 0xA31
        break;
    case COMMAND_IS_CHAR_ATTACHED_TO_ANY_CAR: // 0xA32
        break;
    case COMMAND_STORE_CAR_CHAR_IS_ATTACHED_TO_NO_SAVE: // 0xA33
        break;
    case COMMAND_SET_UP_SKIP_TO_BE_FINISHED_BY_SCRIPT: // 0xA34
        break;
    case COMMAND_SET_UP_SKIP_FOR_VEHICLE_FINISHED_BY_SCRIPT: // 0xA35
        break;
    case COMMAND_IS_SKIP_WAITING_FOR_SCRIPT_TO_FADE_IN: // 0xA36
        break;
    case COMMAND_FORCE_ALL_VEHICLE_LIGHTS_OFF: // 0xA37
        break;
    case COMMAND_SET_RENDER_PLAYER_WEAPON: // 0xA38
        break;
    case COMMAND_GET_PLAYER_IN_CAR_CAMERA_MODE: // 0xA39
        break;
    case COMMAND_IS_LAST_BUILDING_MODEL_SHOT_BY_PLAYER: // 0xA3A
        break;
    case COMMAND_CLEAR_LAST_BUILDING_MODEL_SHOT_BY_PLAYER: // 0xA3B
        break;
    case COMMAND_SET_UP_CONVERSATION_END_NODE_WITH_SCRIPTED_SPEECH: // 0xA3C
        break;
    case COMMAND_ACTIVATE_PIMP_CHEAT: // 0xA3D
        CollectParameters(1);
        if (ScriptParams[0].iParam) {
            CCheat::ApplyCheat(CHEAT_PROSTITUTES_PAY_YOU);
        } else {
            CCheat::Disable(CHEAT_PROSTITUTES_PAY_YOU);
        }
        return OR_CONTINUE;
    case COMMAND_GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE: // 0xA3E
        break;
    case COMMAND_SET_SCRIPT_COOP_GAME: // 0xA3F
        break;
    case COMMAND_CREATE_USER_3D_MARKER: // 0xA40
        CollectParameters(4);
        ScriptParams[0].uParam = C3dMarkers::User3dMarkerSet(ScriptParams[0].fParam, ScriptParams[1].fParam, ScriptParams[2].fParam, ScriptParams[3].iParam);
        StoreParameters(1);
        return OR_CONTINUE;
    case COMMAND_REMOVE_USER_3D_MARKER: // 0xA41
        CollectParameters(1);
        C3dMarkers::User3dMarkerDelete(ScriptParams[0].iParam);
        return OR_CONTINUE;
    case COMMAND_REMOVE_ALLUSER_3D_MARKERS: // 0xA42 NOTSA
        break;
    case COMMAND_GET_RID_OF_PLAYER_PROSTITUTE: // 0xA43
        CTaskComplexProstituteSolicit::GetRidOfPlayerProstitute();
        return OR_CONTINUE;
    case COMMAND_DISPLAY_NON_MINIGAME_HELP_MESSAGES: // 0xA44
        CollectParameters(1);
        CTheScripts::bDisplayNonMiniGameHelpMessages = ScriptParams[0].uParam != 0;
        return OR_CONTINUE;
    case COMMAND_SET_RAILTRACK_RESISTANCE_MULT: // 0xA45
        CollectParameters(1);
        if (ScriptParams[0].fParam <= 0.0f) {
            CVehicle::ms_fRailTrackResistance = CVehicle::ms_fRailTrackResistanceDefault;
        } else {
            CVehicle::ms_fRailTrackResistance = CVehicle::ms_fRailTrackResistanceDefault * ScriptParams[0].fParam;
        }
        return OR_CONTINUE;
    case COMMAND_SWITCH_OBJECT_BRAINS: // 0xA46
        CollectParameters(2);
        if (ScriptParams[1].uParam) {
            CTheScripts::ScriptsForBrains.SwitchAllObjectBrainsWithThisID(ScriptParams[0].i8Param, true);
        } else {
            CTheScripts::ScriptsForBrains.SwitchAllObjectBrainsWithThisID(ScriptParams[0].i8Param, false);
        }
        return OR_CONTINUE;
    case COMMAND_FINISH_SETTING_UP_CONVERSATION_NO_SUBTITLES: // 0xA47
        break;
        // todo: CConversations::DoneSettingUpConversation(1);
        return OR_CONTINUE;
    case COMMAND_ALLOW_PAUSE_IN_WIDESCREEN: // 0xA48
        CollectParameters(1);
        FrontEndMenuManager.m_bMenuAccessWidescreen = ScriptParams[0].uParam != 0;
        return OR_CONTINUE;
    case COMMAND_IS_XBOX_VERSION: // 0xA49
    case COMMAND_IS_JAPANESE_VERSION: // 0xA4D
        UpdateCompareFlag(0);
        return OR_CONTINUE;
    case COMMAND_GET_PC_MOUSE_MOVEMENT: // 0xA4A
        ScriptParams[0].fParam = CPad::NewMouseControllerState.X; // todo: check ASM
        ScriptParams[1].fParam = CPad::NewMouseControllerState.Y;
        StoreParameters(2);
        return OR_CONTINUE;
    case COMMAND_IS_PC_USING_JOYPAD: // 0xA4B
        UpdateCompareFlag(FrontEndMenuManager.m_nController != 0);
        return OR_CONTINUE;
    case COMMAND_IS_MOUSE_USING_VERTICAL_INVERSION: // 0xA4C
        UpdateCompareFlag(CMenuManager::bInvertMouseY != 0);
        return OR_CONTINUE;
    case COMMAND_IS_XBOX_PLAYER2_PRESSING_START: // 0xA4E
        break;
    case COMMAND_FINISHED_WITH_XBOX_PLAYER2: // 0xA4F
        break;
    case COMMAND_DO_DEBUG_STUFF: // 0xA50
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
