#include "StdInc.h"
#include "RunningScript.h"

OpcodeResult CRunningScript::ProcessExternalCommands(int32 commandId) {
    switch (commandId) {
    case COMMAND_IS_BUTTON_PRESSED: // 0x00E1 (Pad touch, TouchPoints touchPoints)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_WRITE_MEMORY: // 0x0A8C (int32 address, int32 size, any value, bool vp)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_READ_MEMORY: // 0x0A8D (int32 address, int32 size, bool vp)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_INT_ADD: // 0x0A8E (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_INT_SUB: // 0x0A8F (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_INT_MUL: // 0x0A90 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_INT_DIV: // 0x0A91 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_STREAM_CUSTOM_SCRIPT: // 0x0A92 (string scriptFileName, arguments)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_TERMINATE_THIS_CUSTOM_SCRIPT: // 0x0A93
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_LOAD_AND_LAUNCH_CUSTOM_MISSION: // 0x0A94 (string scriptFileName, arguments)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_SAVE_THIS_CUSTOM_SCRIPT: // 0x0A95
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GET_PED_POINTER: // 0x0A96 (Char char)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_VEHICLE_POINTER: // 0x0A97 (Car vehicle)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_OBJECT_POINTER: // 0x0A98 (Object object)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_SET_CURRENT_DIRECTORY: // 0x0A99 (any path)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_OPEN_FILE: // 0x0A9A (string filePathName, FileMode mode)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_CLOSE_FILE: // 0x0A9B (File self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_FILE_SIZE: // 0x0A9C (File self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_READ_FROM_FILE: // 0x0A9D (File self, int32 size)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_WRITE_TO_FILE: // 0x0A9E (File self, int32 size, int32 source)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_GET_THIS_SCRIPT_STRUCT: // 0x0A9F
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GOSUB_IF_FALSE: // 0x0AA0 (label)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_RETURN_IF_FALSE: // 0x0AA1
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_LOAD_DYNAMIC_LIBRARY: // 0x0AA2 (string libraryFileName)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_FREE_DYNAMIC_LIBRARY: // 0x0AA3 (DynamicLibrary self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_DYNAMIC_LIBRARY_PROCEDURE: // 0x0AA4 (string procName, DynamicLibrary self)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_CALL_FUNCTION: // 0x0AA5 (int32 address, int32 numParams, int32 pop, arguments funcParams)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_CALL_METHOD: // 0x0AA6 (int32 address, int32 struct, int32 numParams, int32 pop, arguments funcParams)
    {
        CollectParameters(5);
        return OR_CONTINUE;
    }
    case COMMAND_CALL_FUNCTION_RETURN: // 0x0AA7 (int32 address, int32 numParams, int32 pop, arguments funcParams)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_CALL_METHOD_RETURN: // 0x0AA8 (int32 address, int32 struct, int32 numParams, int32 pop, arguments funcParams)
    {
        CollectParameters(5);
        return OR_CONTINUE;
    }
    case COMMAND_IS_GAME_VERSION_ORIGINAL: // 0x0AA9
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GET_SCRIPT_STRUCT_NAMED: // 0x0AAA (string scriptName)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_DOES_FILE_EXIST: // 0x0AAB (string path)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_LOAD_AUDIO_STREAM: // 0x0AAC (string audioFileName)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_SET_AUDIO_STREAM_STATE: // 0x0AAD (AudioStream self, AudioStreamState state)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_REMOVE_AUDIO_STREAM: // 0x0AAE (AudioStream self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_AUDIO_STREAM_LENGTH: // 0x0AAF (AudioStream self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IS_KEY_PRESSED: // 0x0AB0 (KeyCode keyCode)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_CLEO_CALL: // 0x0AB1 (label , int32 numParams, arguments params)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_CLEO_RETURN: // 0x0AB2 (int32 numRet, arguments retParams)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_SET_CLEO_SHARED_VAR: // 0x0AB3 (int32 varId, any value)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_GET_CLEO_SHARED_VAR: // 0x0AB4 (int32 varId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_STORE_CLOSEST_ENTITIES: // 0x0AB5 (Char self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_TARGET_BLIP_COORDS: // 0x0AB6
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GET_CAR_NUMBER_OF_GEARS: // 0x0AB7 (Car self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_CAR_CURRENT_GEAR: // 0x0AB8 (Car self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_AUDIO_STREAM_STATE: // 0x0AB9 (AudioStream self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_TERMINATE_ALL_CUSTOM_SCRIPTS_WITH_THIS_NAME: // 0x0ABA (string scriptFileName)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_AUDIO_STREAM_VOLUME: // 0x0ABB (AudioStream self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_SET_AUDIO_STREAM_VOLUME: // 0x0ABC (AudioStream self, float volume)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_IS_CAR_SIREN_ON: // 0x0ABD (Car self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IS_CAR_ENGINE_ON: // 0x0ABE (Car self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_CLEO_SET_CAR_ENGINE_ON: // 0x0ABF (Car self, bool state)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_SET_AUDIO_STREAM_LOOPED: // 0x0AC0 (AudioStream self, bool state)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_LOAD_3D_AUDIO_STREAM: // 0x0AC1 (string audioFileName)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_SET_PLAY_3D_AUDIO_STREAM_AT_COORDS: // 0x0AC2 (AudioStream self, float x, float y, float z)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_SET_PLAY_3D_AUDIO_STREAM_AT_OBJECT: // 0x0AC3 (AudioStream self, Object handle)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_SET_PLAY_3D_AUDIO_STREAM_AT_CHAR: // 0x0AC4 (AudioStream self, Char handle)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_SET_PLAY_3D_AUDIO_STREAM_AT_CAR: // 0x0AC5 (AudioStream self, Car handle)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_GET_LABEL_POINTER: // 0x0AC6 (label)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_VAR_POINTER: // 0x0AC7 (any)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_ALLOCATE_MEMORY: // 0x0AC8 (int32 size)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_FREE_MEMORY: // 0x0AC9 (int32 address)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_PRINT_HELP_STRING: // 0x0ACA (string text)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_PRINT_BIG_STRING: // 0x0ACB (string text, int32 time, TextStyle style)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_PRINT_STRING: // 0x0ACC (string text, int32 time)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_PRINT_STRING_NOW: // 0x0ACD (string text, int32 time)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_PRINT_HELP_FORMATTED: // 0x0ACE (string text, arguments args)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_PRINT_BIG_FORMATTED: // 0x0ACF (string text, int32 time, TextStyle style, arguments args)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_PRINT_FORMATTED: // 0x0AD0 (string text, int32 time, arguments arg)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_PRINT_FORMATTED_NOW: // 0x0AD1 (string text, int32 time, arguments arg)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_GET_CHAR_PLAYER_IS_TARGETING: // 0x0AD2 (Player self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_STRING_FORMAT: // 0x0AD3 (string format, arguments args)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_SCAN_STRING: // 0x0AD4 (string str, string format, arguments args)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_FILE_SEEK: // 0x0AD5 (File self, int32 offset, SeekOrigin origin)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IS_END_OF_FILE_REACHED: // 0x0AD6 (File self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_READ_STRING_FROM_FILE: // 0x0AD7 (File self, string buffer, int32 size)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_WRITE_STRING_TO_FILE: // 0x0AD8 (File self, string source)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_WRITE_FORMATTED_STRING_TO_FILE: // 0x0AD9 (File self, string format, arguments args)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_SCAN_FILE: // 0x0ADA (File self, string format, arguments args)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_GET_NAME_OF_VEHICLE_MODEL: // 0x0ADB (model_vehicle modelId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_TEST_CHEAT: // 0x0ADC (string input)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_SPAWN_VEHICLE_BY_CHEATING: // 0x0ADD (model_vehicle modelId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_TEXT_LABEL_STRING: // 0x0ADE (gxt_key key)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_ADD_TEXT_LABEL: // 0x0ADF (gxt_key dynamicKey, string text)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_REMOVE_TEXT_LABEL: // 0x0AE0 (gxt_key dynamicKey)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_RANDOM_CHAR_IN_SPHERE_NO_SAVE_RECURSIVE: // 0x0AE1 (float x, float y, float z, float radius, bool findNext, bool skipDead)
    {
        CollectParameters(6);
        return OR_CONTINUE;
    }
    case COMMAND_GET_RANDOM_CAR_IN_SPHERE_NO_SAVE_RECURSIVE: // 0x0AE2 (float x, float y, float z, float radius, bool findNext, bool skipWrecked)
    {
        CollectParameters(6);
        return OR_CONTINUE;
    }
    case COMMAND_GET_RANDOM_OBJECT_IN_SPHERE_NO_SAVE_RECURSIVE: // 0x0AE3 (float x, float y, float z, float radius, bool findNext)
    {
        CollectParameters(5);
        return OR_CONTINUE;
    }
    case COMMAND_DOES_DIRECTORY_EXIST: // 0x0AE4 (string dirPath)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_CREATE_DIRECTORY: // 0x0AE5 (string dirName)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_FIND_FIRST_FILE: // 0x0AE6 (string searchMask, string fileName)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_FIND_NEXT_FILE: // 0x0AE7 (FindFile self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_FIND_CLOSE: // 0x0AE8 (FindFile self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_POP_FLOAT: // 0x0AE9
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GET_PED_REF: // 0x0AEA (int32 address)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_VEHICLE_REF: // 0x0AEB (int32 address)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_OBJECT_REF: // 0x0AEC (int32 address)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_STRING_FLOAT_FORMAT: // 0x0AED (float number, string format)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_POW: // 0x0AEE (float number, float power)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_LOG: // 0x0AEF (float number, float base)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_READ_STRUCT_OFFSET: // 0x0D4E (int32 address, int32 offset, int32 size)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_GET_CAR_ALARM: // 0x0E00 (Car self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_CREATE_OBJECT_NO_SAVE: // 0x0E01 (model_object modelId, float x, float y, float z, bool useOffset, bool useGround)
    {
        CollectParameters(6);
        return OR_CONTINUE;
    }
    case COMMAND_SET_CAR_GENERATOR_NO_SAVE: // 0x0E02 (CarGenerator self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_PERLIN_NOISE: // 0x0E03 (float x)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_NEXT_WEATHER: // 0x0E04
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_SET_NEXT_WEATHER: // 0x0E05 (WeatherType type)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_RAIN_INTENSITY: // 0x0E06
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_SET_RAIN_INTENSITY: // 0x0E07 (float intensity)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IS_CAR_SCRIPT_CONTROLLED: // 0x0E08 (Car self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_MARK_CAR_AS_NEEDED: // 0x0E09 (Car self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IS_CHAR_SCRIPT_CONTROLLED: // 0x0E0A (Char self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_MARK_CHAR_AS_NEEDED: // 0x0E0B (Char self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IS_OBJECT_SCRIPT_CONTROLLED: // 0x0E0C (Object self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_MARK_OBJECT_AS_NEEDED: // 0x0E0D (Object self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_CURRENT_RESOLUTION: // 0x0E0E
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GET_FIXED_XY_ASPECT_RATIO: // 0x0E0F (float x, float y)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_IS_MOUSE_WHEEL_UP: // 0x0E10
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IS_MOUSE_WHEEL_DOWN: // 0x0E11
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GET_VEHICLE_SUBCLASS: // 0x0E12 (Car self)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_ENTITY_TYPE: // 0x0E13 (int32 address)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IS_ON_MISSION: // 0x0E1D
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IS_ON_SAMP: // 0x0E20
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GET_AUDIO_SFX_VOLUME: // 0x0E21
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GET_AUDIO_RADIO_VOLUME: // 0x0E22
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_GET_MOUSE_SENSIBILITY: // 0x0E23
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_FIX_CHAR_GROUND_BRIGHTNESS_AND_FADE_IN: // 0x0E24 (Char self, bool fixGround, bool fixBrightness, bool fadeIn)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_IS_ON_CUTSCENE: // 0x0E25
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IS_WEAPON_FIRE_TYPE: // 0x0E26 (WeaponType weaponType, WeaponFire weaponFire)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_GET_ANGLE_FROM_TWO_COORDS: // 0x0E27 (float x1, float y1, float x2, float y2)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_WRITE_STRUCT_OFFSET: // 0x0E28 (int32 address, int32 offset, int32 size, any value)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_PERLIN_NOISE_FRACTAL: // 0x0E29 (float x, int32 octaves, float frequency, float amplitude, float lacunarity, float persistence)
    {
        CollectParameters(6);
        return OR_CONTINUE;
    }
    case COMMAND_SET_CAR_ALARM: // 0x0E61 (Car self, CarAlarm status)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_PERLIN_NOISE_FRACTAL_2D: // 0x0EF1 (float x, float y, int32 octaves, float frequency, float amplitude, float lacunarity, float persistence)
    {
        CollectParameters(7);
        return OR_CONTINUE;
    }
    case COMMAND_PERLIN_NOISE_FRACTAL_3D: // 0x0EF2 (float x, float y, float z, int32 octaves, float frequency, float amplitude, float lacunarity, float persistence)
    {
        CollectParameters(8);
        return OR_CONTINUE;
    }
    case COMMAND_BIT_AND: // 0x0B10 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BIT_OR: // 0x0B11 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BIT_XOR: // 0x0B12 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BIT_NOT: // 0x0B13 (int32)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_BIT_MOD: // 0x0B14 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BIT_SHR: // 0x0B15 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BIT_SHL: // 0x0B16 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BITWISE_AND_THING_WITH_THING: // 0x0B17 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BITWISE_OR_THING_WITH_THING: // 0x0B18 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BITWISE_XOR_THING_WITH_THING: // 0x0B19 (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BITWISE_NOT: // 0x0B1A (int32)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_BITWISE_MOD_THING_BY_THING: // 0x0B1B (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BITWISE_SHR_THING_BY_THING: // 0x0B1C (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_BITWISE_SHL_THING_BY_THING: // 0x0B1D (int32, int32)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_READ_CLIPBOARD_DATA: // 0x0B20 (any memory, int32 size)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_WRITE_CLIPBOARD_DATA: // 0x0B21 (any memory, int32 size)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_DELETE_FILE: // 0x0B00 (string fileName)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_DELETE_DIRECTORY: // 0x0B01 (string dirPath, bool recursive)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_MOVE_FILE: // 0x0B02 (string fileName, string newFileName)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_MOVE_DIRECTORY: // 0x0B03 (string dirPath, string newDirPath)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_COPY_FILE: // 0x0B04 (string fileName, string newFileName)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_COPY_DIRECTORY: // 0x0B05 (string dirPath, string newDirPath)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_BEGIN: // 0x0C00 (string windowName, bool state, bool noTitleBar, bool noResize, bool noMove, bool autoResize)
    {
        CollectParameters(6);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_END: // 0x0C01
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_CHECKBOX: // 0x0C02 (string label, bool isChecked)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_BUTTON: // 0x0C03 (string buttonName, float width, float height)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_COLOR_BUTTON: // 0x0C04 (string buttonName, float red, float green, float blue, float alpha, float width, float height)
    {
        CollectParameters(7);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_INVISIBLE_BUTTON: // 0x0C05 (string buttonName, float width, float height)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SET_WINDOW_POS: // 0x0C06 (float x, float y, ImGuiCond imGuiCond)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SET_WINDOW_SIZE: // 0x0C07 (float width, float height, ImGuiCond imGuiCond)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SET_NEXT_WINDOW_POS: // 0x0C08 (float x, float y, ImGuiCond imGuiCond)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SET_NEXT_WINDOW_SIZE: // 0x0C09 (float width, float height, ImGuiCond imGuiCond)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_DUMMY: // 0x0C0A (float width, float height)
    {
        CollectParameters(2);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_TEXT: // 0x0C0B (string text)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_TEXT_DISABLED: // 0x0C0C (string text)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_TEXT_WRAPPED: // 0x0C0D (string text)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_TEXT_COLORED: // 0x0C0E (string text, float red, float green, float blue, float alpha)
    {
        CollectParameters(5);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_BULLET_TEXT: // 0x0C0F (string text)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SET_TOOLTIP: // 0x0C10 (string text)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SAMELINE: // 0x0C11
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_NEWLINE: // 0x0C12
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SPACING: // 0x0C13
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SEPARATOR: // 0x0C14
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_NEXT_COLUMN: // 0x0C15
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_COLUMNS: // 0x0C16 (int32 count)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_GET_FRAMERATE: // 0x0C17
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_GET_VERSION: // 0x0C18
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_GET_PLUGIN_VERSION: // 0x0C19
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SET_CURSOR_VISIBLE: // 0x0C1A (bool show)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_GET_DISPLAY_SIZE: // 0x0C1B
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_GET_FRAME_HEIGHT: // 0x0C1C
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_GET_WINDOW_POS: // 0x0C1D
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_GET_WINDOW_SIZE: // 0x0C1E
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_CALC_TEXT_SIZE: // 0x0C1F (string text)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_GET_WINDOW_CONTENT_REGION_WIDTH: // 0x0C20
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_BEGIN_MAINMENUBAR: // 0x0C21 (string uniqueId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_END_MAINMENUBAR: // 0x0C22
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_MENU_ITEM: // 0x0C23 (string text, bool selected, bool enabled)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SELECTABLE: // 0x0C24 (string text)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_BEGIN_CHILD: // 0x0C25 (string uniqueId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_END_CHILD: // 0x0C26
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_PUSH_ITEM_WIDTH: // 0x0C27 (float width)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_POP_ITEM_WIDTH: // 0x0C28
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_COLLAPSING_HEADER: // 0x0C29 (string label)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SLIDER_INT: // 0x0C2A (string label, int32 initValue, int32 min, int32 max)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SLIDER_FLOAT: // 0x0C2B (string label, float initValue, float min, float max)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_INPUT_FLOAT: // 0x0C2C (string label, float initValue, float min, float max)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_INPUT_INT: // 0x0C2D (string label, int32 initValue, int32 min, int32 max)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_INPUT_TEXT: // 0x0C2E (string label)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_RADIO_BUTTON: // 0x0C2F (string label, int32 selectedBtn, int32 btnNo)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_COLOR_PICKER: // 0x0C30 (string label)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_BEGIN_FRAME: // 0x0C31 (string uniqueId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_END_FRAME: // 0x0C32
    {
        CollectParameters(0);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_IS_ITEM_ACTIVE: // 0x0C33 (string uniqueId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_IS_ITEM_CLICKED: // 0x0C34 (string uniqueId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_IS_ITEM_FOCUSED: // 0x0C35 (string uniqueId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_IS_ITEM_HOVERED: // 0x0C36 (string uniqueId)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_GET_SCALING_SIZE: // 0x0C37 (string uniqueId, int32 count, bool spacing)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_IMGUI_SET_NEXT_WINDOW_TRANSPARENCY: // 0x0C38 (float alpha)
    {
        CollectParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_READ_INT_FROM_INI_FILE: // 0x0AF0 (string path, string section, string key)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_WRITE_INT_TO_INI_FILE: // 0x0AF1 (int32 value, string path, string section, string key)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_READ_FLOAT_FROM_INI_FILE: // 0x0AF2 (string path, string section, string key)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_WRITE_FLOAT_TO_INI_FILE: // 0x0AF3 (float value, string path, string section, string key)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    case COMMAND_READ_STRING_FROM_INI_FILE: // 0x0AF4 (string path, string section, string key)
    {
        CollectParameters(3);
        return OR_CONTINUE;
    }
    case COMMAND_WRITE_STRING_TO_INI_FILE: // 0x0AF5 (string value, string path, string section, string key)
    {
        CollectParameters(4);
        return OR_CONTINUE;
    }
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
