#include "StdInc.h"

#include "RunningScript.h"
#include "CarGenerator.h"
#include "TheCarGenerators.h"

// 0x47C100
OpcodeResult CRunningScript::ProcessCommands300To399(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_CHAR_INVINCIBLE: // 0x12C
        break;
    case COMMAND_SET_PLAYER_INVINCIBLE: // 0x12D
        break;
    case COMMAND_SET_CHAR_GRAPHIC_TYPE: // 0x12E
        break;
    case COMMAND_SET_PLAYER_GRAPHIC_TYPE: // 0x12F
        break;
    case COMMAND_HAS_PLAYER_BEEN_ARRESTED: // 0x130
        break;
    case COMMAND_STOP_CHAR_DRIVING: // 0x131
        break;
    case COMMAND_KILL_CHAR: // 0x132
        break;
    case COMMAND_SET_FAVOURITE_CAR_MODEL_FOR_CHAR: // 0x133
        break;
    case COMMAND_SET_CHAR_OCCUPATION: // 0x134
        break;
    case COMMAND_CHANGE_CAR_LOCK: // 0x135
        break;
    case COMMAND_SHAKE_CAM_WITH_POINT: // 0x136
        break;
    case COMMAND_IS_CAR_MODEL: // 0x137
        break;
    case COMMAND_IS_CAR_REMAP: // 0x138
        break;
    case COMMAND_HAS_CAR_JUST_SUNK: // 0x139
        break;
    case COMMAND_SET_CAR_NO_COLLIDE: // 0x13A
        break;
    case COMMAND_IS_CAR_DEAD_IN_AREA_2D: // 0x13B
        break;
    case COMMAND_IS_CAR_DEAD_IN_AREA_3D: // 0x13C
        break;
    case COMMAND_IS_TRAILER_ATTACHED: // 0x13D
        break;
    case COMMAND_IS_CAR_ON_TRAILER: // 0x13E
        break;
    case COMMAND_HAS_CAR_GOT_WEAPON: // 0x13F
        break;
    case COMMAND_PARK: // 0x140
        break;
    case COMMAND_HAS_PARK_FINISHED: // 0x141
        break;
    case COMMAND_KILL_ALL_PASSENGERS: // 0x142
        break;
    case COMMAND_SET_CAR_BULLETPROOF: // 0x143
        break;
    case COMMAND_SET_CAR_FLAMEPROOF: // 0x144
        break;
    case COMMAND_SET_CAR_ROCKETPROOF: // 0x145
        break;
    case COMMAND_IS_CARBOMB_ACTIVE: // 0x146
        break;
    case COMMAND_GIVE_CAR_ALARM: // 0x147
        break;
    case COMMAND_PUT_CAR_ON_TRAILER: // 0x148
        break;
    case COMMAND_IS_CAR_CRUSHED: // 0x149
        break;
    case COMMAND_CREATE_GANG_CAR: // 0x14A
        break;
    case COMMAND_CREATE_CAR_GENERATOR: // 0x14B
        break;
    case COMMAND_SWITCH_CAR_GENERATOR: // 0x14C
    {
        CollectParameters(2);
        CCarGenerator* generator = CTheCarGenerators::Get(ScriptParams[0].iParam);
        if (ScriptParams[1].iParam) {
            generator->SwitchOn();
            if (ScriptParams[1].iParam <= 100)
                generator->m_nGenerateCount = ScriptParams[1].iParam;
        } else {
            generator->SwitchOff();
        }
        return OR_CONTINUE;
    }
    case COMMAND_ADD_PAGER_MESSAGE: // 0x14D
        break;
    case COMMAND_DISPLAY_ONSCREEN_TIMER: // 0x14E
        break;
    case COMMAND_CLEAR_ONSCREEN_TIMER: // 0x14F
        break;
    case COMMAND_DISPLAY_ONSCREEN_COUNTER: // 0x150
        break;
    case COMMAND_CLEAR_ONSCREEN_COUNTER: // 0x151
        break;
    case COMMAND_SET_ZONE_CAR_INFO: // 0x152
        break;
    case COMMAND_IS_CHAR_IN_GANG_ZONE: // 0x153
        break;
    case COMMAND_IS_CHAR_IN_ZONE: // 0x154
        break;
    case COMMAND_SET_CAR_DENSITY: // 0x155
        break;
    case COMMAND_SET_PED_DENSITY: // 0x156
        break;
    case COMMAND_POINT_CAMERA_AT_PLAYER: // 0x157
        break;
    case COMMAND_POINT_CAMERA_AT_CAR: // 0x158
        break;
    case COMMAND_POINT_CAMERA_AT_CHAR: // 0x159
        break;
    case COMMAND_RESTORE_CAMERA: // 0x15A
        break;
    case COMMAND_SHAKE_PAD: // 0x15B
        break;
    case COMMAND_SET_ZONE_PED_INFO: // 0x15C
        break;
    case COMMAND_SET_TIME_SCALE: // 0x15D
        break;
    case COMMAND_IS_CAR_IN_AIR: // 0x15E
        break;
    case COMMAND_SET_FIXED_CAMERA_POSITION: // 0x15F
        break;
    case COMMAND_POINT_CAMERA_AT_POINT: // 0x160
        break;
    case COMMAND_ADD_BLIP_FOR_CAR_OLD: // 0x161
        break;
    case COMMAND_ADD_BLIP_FOR_CHAR_OLD: // 0x162
        break;
    case COMMAND_ADD_BLIP_FOR_OBJECT_OLD: // 0x163
        break;
    case COMMAND_REMOVE_BLIP: // 0x164
        break;
    case COMMAND_CHANGE_BLIP_COLOUR: // 0x165
        break;
    case COMMAND_DIM_BLIP: // 0x166
        break;
    case COMMAND_ADD_BLIP_FOR_COORD_OLD: // 0x167
        break;
    case COMMAND_CHANGE_BLIP_SCALE: // 0x168
        break;
    case COMMAND_SET_FADING_COLOUR: // 0x169
        break;
    case COMMAND_DO_FADE: // 0x16A
        break;
    case COMMAND_GET_FADING_STATUS: // 0x16B
        break;
    case COMMAND_ADD_HOSPITAL_RESTART: // 0x16C
        break;
    case COMMAND_ADD_POLICE_RESTART: // 0x16D
        break;
    case COMMAND_OVERRIDE_NEXT_RESTART: // 0x16E
        break;
    case COMMAND_DRAW_SHADOW: // 0x16F
        break;
    case COMMAND_GET_PLAYER_HEADING: // 0x170
        break;
    case COMMAND_SET_PLAYER_HEADING: // 0x171
        break;
    case COMMAND_GET_CHAR_HEADING: // 0x172
        break;
    case COMMAND_SET_CHAR_HEADING: // 0x173
        break;
    case COMMAND_GET_CAR_HEADING: // 0x174
        break;
    case COMMAND_SET_CAR_HEADING: // 0x175
        break;
    case COMMAND_GET_OBJECT_HEADING: // 0x176
        break;
    case COMMAND_SET_OBJECT_HEADING: // 0x177
        break;
    case COMMAND_IS_PLAYER_TOUCHING_OBJECT: // 0x178
        break;
    case COMMAND_IS_CHAR_TOUCHING_OBJECT: // 0x179
        break;
    case COMMAND_SET_PLAYER_AMMO: // 0x17A
        break;
    case COMMAND_SET_CHAR_AMMO: // 0x17B
        break;
    case COMMAND_SET_CAR_AMMO: // 0x17C
        break;
    case COMMAND_LOAD_CAMERA_SPLINE: // 0x17D
        break;
    case COMMAND_MOVE_CAMERA_ALONG_SPLINE: // 0x17E
        break;
    case COMMAND_GET_CAMERA_POSITION_ALONG_SPLINE: // 0x17F
        break;
    case COMMAND_DECLARE_MISSION_FLAG: // 0x180
        break;
    case COMMAND_DECLARE_MISSION_FLAG_FOR_CONTACT: // 0x181
        break;
    case COMMAND_DECLARE_BASE_BRIEF_ID_FOR_CONTACT: // 0x182
        break;
    case COMMAND_IS_PLAYER_HEALTH_GREATER: // 0x183
        break;
    case COMMAND_IS_CHAR_HEALTH_GREATER: // 0x184
        break;
    case COMMAND_IS_CAR_HEALTH_GREATER: // 0x185
        break;
    case COMMAND_ADD_BLIP_FOR_CAR: // 0x186
        break;
    case COMMAND_ADD_BLIP_FOR_CHAR: // 0x187
        break;
    case COMMAND_ADD_BLIP_FOR_OBJECT: // 0x188
        break;
    case COMMAND_ADD_BLIP_FOR_CONTACT_POINT: // 0x189
        break;
    case COMMAND_ADD_BLIP_FOR_COORD: // 0x18A
        break;
    case COMMAND_CHANGE_BLIP_DISPLAY: // 0x18B
        break;
    case COMMAND_ADD_ONE_OFF_SOUND: // 0x18C
        break;
    case COMMAND_ADD_CONTINUOUS_SOUND: // 0x18D
        break;
    case COMMAND_REMOVE_SOUND: // 0x18E
        break;
    case COMMAND_IS_CAR_STUCK_ON_ROOF: // 0x18F
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
