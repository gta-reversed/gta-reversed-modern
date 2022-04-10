#include "StdInc.h"

#include "RunningScript.h"
#include "PostEffects.h"
#include "CarGenerator.h"
#include "TheCarGenerators.h"

// 0x47A760
OpcodeResult CRunningScript::ProcessCommands2500To2599(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_PETROL_TANK_WEAKPOINT: // 0x9C4
        break;
    case COMMAND_IS_CHAR_USING_MAP_ATTRACTOR: // 0x9C5
        break;
    case COMMAND_SET_ALL_CARS_IN_AREA_VISIBLE: // 0x9C6
        break;
    case COMMAND_SET_PLAYER_MODEL: // 0x9C7
        break;
    case COMMAND_ARE_SUBTITLES_SWITCHED_ON: // 0x9C8
        break;
    case COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION: // 0x9C9
        break;
    case COMMAND_SET_OBJECT_PROOFS: // 0x9CA
        break;
    case COMMAND_IS_CAR_TOUCHING_CAR: // 0x9CB
        break;
    case COMMAND_DOES_OBJECT_HAVE_THIS_MODEL: // 0x9CC
        break;
    case COMMAND_IS_ITALIAN_GAME: // 0x9CD
        break;
    case COMMAND_IS_SPANISH_GAME: // 0x9CE
        break;
    case COMMAND_SET_TRAIN_FORCED_TO_SLOW_DOWN: // 0x9CF
        break;
    case COMMAND_IS_VEHICLE_ON_ALL_WHEELS: // 0x9D0
        break;
    case COMMAND_DOES_PICKUP_EXIST: // 0x9D1
        break;
    case COMMAND_ENABLE_AMBIENT_CRIME: // 0x9D2
        break;
    case COMMAND_IS_AMBIENT_CRIME_ENABLED: // 0x9D3
        break;
    case COMMAND_CLEAR_WANTED_LEVEL_IN_GARAGE: // 0x9D4
        break;
    case COMMAND_SET_CHAR_SAY_CONTEXT_IMPORTANT: // 0x9D5
        break;
    case COMMAND_SET_CHAR_SAY_SCRIPT: // 0x9D6
        break;
    case COMMAND_FORCE_INTERIOR_LIGHTING_FOR_PLAYER: // 0x9D7
        break;
    case COMMAND_DISABLE_2ND_PAD_FOR_DEBUG: // 0x9D8
        break;
    case COMMAND_USE_DETONATOR: // 0x9D9
        break;
    case COMMAND_IS_MONEY_PICKUP_AT_COORDS: // 0x9DA
        break;
    case COMMAND_SET_MENU_COLUMN_WIDTH: // 0x9DB
        break;
    case COMMAND_SET_CHAR_CAN_CLIMB_OUT_WATER: // 0x9DC
        break;
    case COMMAND_MAKE_ROOM_IN_PLAYER_GANG_FOR_MISSION_PEDS: // 0x9DD
        break;
    case COMMAND_IS_CHAR_GETTING_IN_TO_A_CAR: // 0x9DE
        break;
    case COMMAND_RESTORE_PLAYER_AFTER_2P_GAME: // 0x9DF
        break;
    case COMMAND_SET_UP_SKIP_FOR_SPECIFIC_VEHICLE: // 0x9E0
        break;
    case COMMAND_GET_CAR_MODEL_VALUE: // 0x9E1
        break;
    case COMMAND_CREATE_CAR_GENERATOR_WITH_PLATE: // 0x9E2
        break;
    case COMMAND_FIND_TRAIN_DIRECTION: // 0x9E3
        break;
    case COMMAND_SET_AIRCRAFT_CARRIER_SAM_SITE: // 0x9E4
        break;
    case COMMAND_DRAW_LIGHT_WITH_RANGE: // 0x9E5
        break;
    case COMMAND_ENABLE_BURGLARY_HOUSES: // 0x9E6
        break;
    case COMMAND_IS_PLAYER_CONTROL_ON: // 0x9E7
        break;
    case COMMAND_GET_CHAR_AREA_VISIBLE: // 0x9E8
        break;
    case COMMAND_GIVE_NON_PLAYER_CAR_NITRO: // 0x9E9
        break;
    case COMMAND_PLAYER_PUT_ON_GOGGLES: // 0x9EA
        break;
    case COMMAND_PLAYER_TAKE_OFF_GOGGLES: // 0x9EB
        break;
    case COMMAND_ALLOW_FIXED_CAMERA_COLLISION: // 0x9EC
        break;
    case COMMAND_HAS_CHAR_SPOTTED_CHAR_IN_FRONT: // 0x9ED
        break;
    case COMMAND_FORCE_BIG_MESSAGE_AND_COUNTER: // 0x9EE
        break;
    case COMMAND_SET_VEHICLE_CAMERA_TWEAK: // 0x9EF
        break;
    case COMMAND_RESET_VEHICLE_CAMERA_TWEAK: // 0x9F0
        break;
    case COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_CHAR: // 0x9F1
    {
        CollectParameters(2);
        auto* ped = GetPedPool()->GetAt(ScriptParams[0].iParam);
        assert(ped);
        AudioEngine.ReportMissionAudioEvent(ScriptParams[1].u16Param, ped);
        return OR_CONTINUE;
    }
    case COMMAND_DOES_DECISION_MAKER_EXIST: // 0x9F2
        break;
    case COMMAND_GET_RANDOM_TRAIN_IN_SPHERE_NO_SAVE: // 0x9F3
        break;
    case COMMAND_IGNORE_HEIGHT_DIFFERENCE_FOLLOWING_NODES: // 0x9F4
    {
        CollectParameters(2);
        auto* ped = GetPedPool()->GetAt(ScriptParams[0].iParam);
        assert(ped);
        ped->bIgnoreHeightDifferenceFollowingNodes = ScriptParams[1].bParam; // 0x8000
        return OR_CONTINUE;
    }
    case COMMAND_SHUT_ALL_CHARS_UP: // 0x9F5
        CollectParameters(1);
        if (ScriptParams[0].bParam) {
            CAEPedSpeechAudioEntity::DisableAllPedSpeech();
        } else {
            CAEPedSpeechAudioEntity::EnableAllPedSpeech();
        }
        return OR_CONTINUE;
    case COMMAND_SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR: // 0x9F6
    {
        CollectParameters(2);
        auto* ped = GetPedPool()->GetAt(ScriptParams[0].iParam);
        assert(ped);
        ped->bGetOutUpsideDownCar = ScriptParams[1].bParam;
        return OR_CONTINUE;
    }
    case COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_CAR: // 0x9F7
    {
        CollectParameters(2);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam);
        assert(vehicle);
        AudioEngine.ReportMissionAudioEvent(ScriptParams[1].u16Param, vehicle);
        return OR_CONTINUE;
    }
    case COMMAND_DO_WEAPON_STUFF_AT_START_OF_2P_GAME: // 0x9F8
        CGameLogic::DoWeaponStuffAtStartOf2PlayerGame(1);
        return OR_CONTINUE;
    case COMMAND_SET_MENU_HEADER_ORIENTATION: // 0x9F9 | NOTSA
        // CMenuSystem::SetHeaderOrientation
        break;
    case COMMAND_HAS_GAME_JUST_RETURNED_FROM_FRONTEND: // 0x9FA
        UpdateCompareFlag(CPad::GetPad(0)->JustOutOfFrontEnd == 1);
        return OR_CONTINUE;
    case COMMAND_GET_CURRENT_LANGUAGE: // 0x9FB
        ScriptParams[0].uParam = static_cast<uint8>(FrontEndMenuManager.m_nLanguage);
        StoreParameters(1);
        return OR_CONTINUE;
    case COMMAND_IS_OBJECT_INTERSECTING_WORLD: // 0x9FC
        break;
    case COMMAND_GET_STRING_WIDTH: // 0x9FD
        break;
    case COMMAND_RESET_VEHICLE_HYDRAULICS: // 0x9FE
        break;
    case COMMAND_SET_RESPAWN_POINT_FOR_DURATION_OF_MISSION: // 0x9FF
        CollectParameters(3);
        CRestart::SetRespawnPointForDurationOfMission(CTheScripts::ReadCVectorFromScript(0));
        return OR_CONTINUE;
    case COMMAND_IS_THIS_MODEL_A_BIKE: // 0xA00
        break;
    case COMMAND_IS_THIS_MODEL_A_CAR: // 0xA01
        break;
    case COMMAND_SWITCH_ON_GROUND_SEARCHLIGHT: // 0xA02
        break;
    case COMMAND_IS_GANG_WAR_FIGHTING_GOING_ON: // 0xA03
        break;
    case COMMAND_SET_VEHICLE_FIRING_RATE_MULTIPLIER: // 0xA04
        break;
    case COMMAND_GET_VEHICLE_FIRING_RATE_MULTIPLIER: // 0xA05
        break;
    case COMMAND_IS_NEXT_STATION_ALLOWED: // 0xA06
        break;
    case COMMAND_SKIP_TO_NEXT_ALLOWED_STATION: // 0xA07
    {
        CollectParameters(1);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam);
        assert(vehicle && vehicle->IsTrain());
        CTrain::SkipToNextAllowedStation(vehicle->AsTrain());
        return OR_CONTINUE;
    }
    case COMMAND_GET_STRING_WIDTH_WITH_NUMBER: // 0xA08
        break;
    case COMMAND_SHUT_CHAR_UP_FOR_SCRIPTED_SPEECH: // 0xA09
        break;
    case COMMAND_ENABLE_DISABLED_ATTRACTORS_ON_OBJECT: // 0xA0A
    {
        CollectParameters(2);
        auto* obj = GetObjectPool()->GetAt(ScriptParams[0].iParam);
        assert(obj);
        obj->objectFlags.b0x1000000 = ScriptParams[1].bParam; // todo: rename obj->objectFlags.b0x1000000
        return OR_CONTINUE;
    }
    case COMMAND_LOAD_SCENE_IN_DIRECTION: // 0xA0B
    {
        CollectParameters(4);
        auto pos     = CTheScripts::ReadCVectorFromScript(0);
        auto heading = DegreesToRadians(ScriptParams[3].fParam);

        CTimer::Stop();
        CRenderer::RequestObjectsInDirection(pos, heading, STREAMING_LOADING_SCENE);
        CStreaming::LoadScene(pos);
        CTimer::Update();
        return OR_CONTINUE;
    }
    case COMMAND_IS_PLAYER_USING_JETPACK: // 0xA0C
        break;
    case COMMAND_BLOCK_VEHICLE_MODEL: // 0xA0D
        break;
    case COMMAND_CLEAR_THIS_PRINT_BIG_NOW: // 0xA0E
    {
        CollectParameters(1);
        CMessages::ClearThisPrintBigNow(static_cast<eMessageStyle>(ScriptParams[0].u16Param - 1));
        return OR_CONTINUE;
    }
    case COMMAND_HAS_LANGUAGE_CHANGED: // 0xA0F
        break;
    case COMMAND_INCREMENT_INT_STAT_NO_MESSAGE: // 0xA10
    {
        CollectParameters(2);
        CStats::IncrementStat(static_cast<eStats>(ScriptParams[0].iParam), ScriptParams[1].fParam);
        return OR_CONTINUE;
    }
    case COMMAND_SET_EXTRA_CAR_COLOURS: // 0xA11
    {
        CollectParameters(3);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam);
        assert(vehicle);
        vehicle->m_nTertiaryColor   = ScriptParams[1].u8Param;
        vehicle->m_nQuaternaryColor = ScriptParams[2].u8Param;
        return OR_CONTINUE;
    }
    case COMMAND_GET_EXTRA_CAR_COLOURS: // 0xA12
    {
        CollectParameters(1);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam);
        assert(vehicle);
        ScriptParams[0].u8Param = vehicle->m_nTertiaryColor;  // todo: u8 or u32 output?
        ScriptParams[1].u8Param = vehicle->m_nQuaternaryColor;
        StoreParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_MANAGE_ALL_POPULATION: // 0xA13
        CPopulation::ManageAllPopulation();
        return OR_CONTINUE;
    case COMMAND_SET_NO_RESPRAYS: // 0xA14
    {
        break;
        CollectParameters(1);
        CGarages::NoResprays = ScriptParams[0].bParam;
        //todo: CGarages::AllRespraysCloseOrOpen(ScriptParams[0].bParam);
        return OR_CONTINUE;
    }
    case COMMAND_HAS_CAR_BEEN_RESPRAYED: // 0xA15
        break;
    case COMMAND_ATTACH_MISSION_AUDIO_TO_CAR: // 0xA16
    {
        CollectParameters(2);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[1].iParam);
        assert(vehicle);
        AudioEngine.AttachMissionAudioToPhysical(ScriptParams[0].u8Param - 1, vehicle);
        return OR_CONTINUE;
    }
    case COMMAND_SET_HAS_BEEN_OWNED_FOR_CAR_GENERATOR: // 0xA17
    {
        CollectParameters(2);
        auto* generator = CTheCarGenerators::Get(ScriptParams[0].iParam);
        generator->bPlayerHasAlreadyOwnedCar = ScriptParams[1].bParam;
        return OR_CONTINUE;
    }
    case COMMAND_SET_UP_CONVERSATION_NODE_WITH_SCRIPTED_SPEECH: // 0xA18 0x47BA77
    {
        break; // todo:
        char a[8], b[8], c[8];
        ReadTextLabelFromScript(a, 8);
        ReadTextLabelFromScript(b, 8);
        ReadTextLabelFromScript(c, 8);
        CollectParameters(3);
        // CConversations::SetUpConversationNode(a, b, c, -ScriptParams[0], -ScriptParams[1], -ScriptParams[2]);
        return OR_CONTINUE;
    }
    case COMMAND_SET_AREA_NAME: // 0xA19
        char key[8];
        ReadTextLabelFromScript(key, 8);
        CHud::SetZoneName(TheText.Get(key), 1);
        return OR_CONTINUE;
    case COMMAND_TASK_PLAY_ANIM_SECONDARY: // 0xA1A
        PlayAnimScriptCommand(commandId);
        return OR_CONTINUE;
    case COMMAND_IS_CHAR_TOUCHING_CHAR: // 0xA1B
        break;
    case COMMAND_DISABLE_HELI_AUDIO: // 0xA1C
    {
        break;
        CollectParameters(2);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam);
        assert(vehicle);
        if (ScriptParams[1].bParam) {
            // todo: vehicle->m_vehicleAudio.EnableHelicoptor();
        } else {
            // todo: vehicle->m_vehicleAudio.DisableHelicoptor();
        }
        return OR_CONTINUE;
    }
    case COMMAND_TASK_HAND_GESTURE: // 0xA1D
        break;
    case COMMAND_TAKE_PHOTO: // 0xA1E
        CollectParameters(1);
        CWeapon::ms_bTakePhoto = true;
        CPostEffects::m_bSavePhotoFromScript = ScriptParams[0].bParam;
        return OR_CONTINUE;
    case COMMAND_INCREMENT_FLOAT_STAT_NO_MESSAGE: // 0xA1F
        CollectParameters(2);
        CStats::IncrementStat(static_cast<eStats>(ScriptParams[0].iParam), ScriptParams[1].fParam);
        return OR_CONTINUE;
    case COMMAND_SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS: // 0xA20
        CollectParameters(2);
        FindPlayerPed(ScriptParams[0].iParam)->ForceGroupToAlwaysFollow(ScriptParams[1].bParam);
        return OR_CONTINUE;
    case COMMAND_IMPROVE_CAR_BY_CHEATING: // 0xA21
    {
        CollectParameters(2);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam);
        assert(vehicle);
        vehicle->vehicleFlags.bUseCarCheats = ScriptParams[1].bParam;
        return OR_CONTINUE;
    }
    case COMMAND_CHANGE_CAR_COLOUR_FROM_MENU: // 0xA22
    {
        break; // todo: GetCarColourFromGrid
        CollectParameters(4);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[1].iParam);
        assert(vehicle);
        auto color = 0;//CMenuSystem::GetCarColourFromGrid(ScriptParams[0].u8param, ScriptParams[3].u8param);
        if (ScriptParams[2].bParam) {
            vehicle->m_nPrimaryColor = color;
        } else {
            vehicle->m_nSecondaryColor = color;
        }
        return OR_CONTINUE;
    }
    case COMMAND_HIGHLIGHT_MENU_ITEM: // 0xA23
        break;
        //CollectParameters(3);
        //CMenuSystem::HighlightOneItem(ScriptParams[0].uParam, ScriptParams[1].uParam, ScriptParams[2].bParam);
    case COMMAND_SET_DISABLE_MILITARY_ZONES: // 0xA24
        CollectParameters(1);
        CCullZones::bMilitaryZonesDisabled = ScriptParams[0].bParam;
        return OR_CONTINUE;
    case COMMAND_SET_CAMERA_POSITION_UNFIXED: // 0xA25
        break;
    case COMMAND_SET_RADIO_TO_PLAYERS_FAVOURITE_STATION: // 0xA26
        AudioEngine.RetuneRadio(CStats::FindMostFavoriteRadioStation());
        return OR_CONTINUE;
    case COMMAND_SET_DEATH_WEAPONS_PERSIST: // 0xA27
    {
        CollectParameters(2);
        auto* ped = GetPedPool()->GetAt(ScriptParams[0].iParam);
        assert(ped);
        ped->bDeathPickupsPersist = ScriptParams[1].bParam;
        return OR_CONTINUE;
    }
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
