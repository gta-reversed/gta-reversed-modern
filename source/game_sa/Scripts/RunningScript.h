/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eScriptCommands.h"
#include "OpcodeResult.h"
#include "eWeaponType.h"
#include "Ped.h"

enum ePedType : uint32;

enum eScriptParameterType : int8 {
    SCRIPT_PARAM_END_OF_ARGUMENTS, //< Special type used for vararg stuff

    SCRIPT_PARAM_STATIC_INT_32BITS,
    SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE, //< Global int32 variable
    SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE, //< Local int32 variable
    SCRIPT_PARAM_STATIC_INT_8BITS,
    SCRIPT_PARAM_STATIC_INT_16BITS,
    SCRIPT_PARAM_STATIC_FLOAT,

    // Types below are only available in GTA SA

    // Number arrays
    SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY, //< Global array of numbers (always int32)
    SCRIPT_PARAM_LOCAL_NUMBER_ARRAY, //< Local array of numbers (always int32)

    SCRIPT_PARAM_STATIC_SHORT_STRING, //< Static 8 byte string

    SCRIPT_PARAM_GLOBAL_SHORT_STRING_VARIABLE, //< Local 8 byte string
    SCRIPT_PARAM_LOCAL_SHORT_STRING_VARIABLE, //< Local 8 byte string

    SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY, //< Global 8 byte string array
    SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY,  //< Local 8 byte string array

    SCRIPT_PARAM_STATIC_PASCAL_STRING, //< Pascal string is a sequence of characters with optional size specification. (So says Google)
    SCRIPT_PARAM_STATIC_LONG_STRING,    //< 16 byte string

    SCRIPT_PARAM_GLOBAL_LONG_STRING_VARIABLE, //< Global 16 byte string
    SCRIPT_PARAM_LOCAL_LONG_STRING_VARIABLE, //< Local 16 byte string

    SCRIPT_PARAM_GLOBAL_LONG_STRING_ARRAY, //< Global array of 16 byte strings
    SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY, //< Local array of 16 byte strings
};

enum eScriptVariableType : uint8 {
    VAR_LOCAL  = 1,
    VAR_GLOBAL = 2
};

enum eButtonId : uint16 {
    BUTTON_LEFT_STICK_X,
    BUTTON_LEFT_STICK_Y,
    BUTTON_RIGHT_STICK_X,
    BUTTON_RIGHT_STICK_Y,
    BUTTON_LEFT_SHOULDER1,
    BUTTON_LEFT_SHOULDER2,
    BUTTON_RIGHT_SHOULDER1,
    BUTTON_RIGHT_SHOULDER2,
    BUTTON_DPAD_UP,
    BUTTON_DPAD_DOWN,
    BUTTON_DPAD_LEFT,
    BUTTON_DPAD_RIGHT,
    BUTTON_START,
    BUTTON_SELECT,
    BUTTON_SQUARE,
    BUTTON_TRIANGLE,
    BUTTON_CROSS,
    BUTTON_CIRCLE,
    BUTTON_LEFTSHOCK,
    BUTTON_RIGHTSHOCK,
};

// *** 🤝 UNION 🤝 ***
union tScriptParam {
    uint8  u8Param;
    int8   i8Param;

    uint16 u16Param;
    int16  i16Param;

    uint32 uParam;
    int32  iParam;

    float  fParam;
    void*  pParam;
    char*  szParam;
    bool   bParam;
};
VALIDATE_SIZE(tScriptParam, 0x4);

static inline std::array<tScriptParam, 32>& ScriptParams = *(std::array<tScriptParam, 32>*)0xA43C78;

enum {
    MAX_STACK_DEPTH = 8,
    NUM_LOCAL_VARS  = 32,
    NUM_TIMERS      = 2
};

constexpr auto SHORT_STRING_SIZE = 8;
constexpr auto LONG_STRING_SIZE = 16;

class CRunningScript {
    /*!
     * Needed for compound if statements.
     * Basically, an `if` translates to:
     * - `COMMAND_ANDOR` followed by a parameter that encodes:
     *   1. the number of conditions = `n` (max 8)
     *   2. logical operation between conditions (AND/OR, hence the command name)
     * - `n` commands that update the conditional flag
     *
     * For instance `if ($A > 0 && $B > 0 && $C > 0)` would generate:
     *
     * ```
     * COMMAND_ANDOR                          ANDS_2 // (three conditions joined by AND)
     * COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER $A 0
     * COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER $B 0
     * COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER $C 0
     * ```
     *
     * Each time a condition is tested, the result is AND/OR'd with the previous
     * result and the ANDOR state is decremented until it reaches the lower bound,
     * meaning that all conditions were tested.
     */
    enum {
        ANDOR_NONE = 0,
        ANDS_1 = 1,
        ANDS_2,
        ANDS_3,
        ANDS_4,
        ANDS_5,
        ANDS_6,
        ANDS_7,
        ANDS_8,
        ORS_1 = 21,
        ORS_2,
        ORS_3,
        ORS_4,
        ORS_5,
        ORS_6,
        ORS_7,
        ORS_8
    };

public:
    CRunningScript* m_pNext;
    CRunningScript* m_pPrev;
    char            m_szName[8];
    uint8*          m_pBaseIP;    // base instruction pointer
    uint8*          m_pCurrentIP; // current instruction pointer
    uint8*          m_apStack[MAX_STACK_DEPTH];
    uint16          m_nSP;        // Stack Pointer
    tScriptParam    m_aLocalVars[NUM_LOCAL_VARS];
    int32           m_anTimers[NUM_TIMERS];
    bool            m_bIsActive;
    bool            m_bCondResult; ///< Used for `COMMAND_GOTO_IF_FALSE`
    bool            m_bUseMissionCleanup;
    bool            m_bIsExternal;
    bool            m_bTextBlockOverride;
    int8            m_nExternalType;
    int32           m_nWakeTime;
    uint16          m_nLogicalOp;
    bool            m_bNotFlag;
    bool            m_bDeathArrestEnabled;
    bool            m_bDeathArrestExecuted;
    uint8*          m_pSceneSkipIP; // scene skip instruction pointer
    bool            m_bIsMission;

    using CommandHandlerFn_t    = OpcodeResult(__thiscall CRunningScript::*)(int32);
    using CommandHandlerTable_t = std::array<CommandHandlerFn_t, 27>;

    static inline CommandHandlerTable_t& CommandHandlerTable = *(CommandHandlerTable_t*)0x8A6168;

public:
    static void InjectHooks();

    void Init();

    void PlayAnimScriptCommand(int32 commandId);

    void LocateCarCommand(int32 commandId);
    void LocateCharCommand(int32 commandId);
    void LocateObjectCommand(int32 commandId);
    void LocateCharCarCommand(int32 commandId);
    void LocateCharCharCommand(int32 commandId);
    void LocateCharObjectCommand(int32 commandId);

    void CarInAreaCheckCommand(int32 commandId);
    void CharInAreaCheckCommand(int32 commandId);
    void ObjectInAreaCheckCommand(int32 commandId);

    void CharInAngledAreaCheckCommand(int32 commandId);
    void FlameInAngledAreaCheckCommand(int32 commandId);
    void ObjectInAngledAreaCheckCommand(int32 commandId);

    void  CollectParameters(int16 count);
    int32 CollectNextParameterWithoutIncreasingPC();
    void  StoreParameters(int16 count);

    void ReadArrayInformation(int32 updateIp, uint16* outArrVarOffset, int32* outArrElemIdx);
    void ReadParametersForNewlyStartedScript(CRunningScript* newScript);
    void ReadTextLabelFromScript(char* buffer, uint8 nBufferLength);
    void GetCorrectPedModelIndexForEmergencyServiceType(ePedType pedType, int32* outModelId);
    int16 GetPadState(uint16 playerIndex, eButtonId buttonId);

    tScriptParam* GetPointerToLocalVariable(int32 varId);
    tScriptParam* GetPointerToLocalArrayElement(int32 arrVarOffset, uint16 arrElemIdx, uint8 arrElemSize);
    tScriptParam* GetPointerToScriptVariable(eScriptVariableType variableType);
    uint16        GetIndexOfGlobalVariable();

    void DoDeathArrestCheck(); // original name DoDeatharrestCheck

    void SetCharCoordinates(CPed* ped, float x, float y, float z, bool bWarpGang, bool bOffset);
    void GivePedScriptedTask(int32 pedHandle, CTask* task, int32 opcode);

    void AddScriptToList(CRunningScript** queueList);
    void RemoveScriptFromList(CRunningScript** queueList);
    void ShutdownThisScript();

    bool IsPedDead(CPed* ped) const;
    bool ThisIsAValidRandomPed(ePedType pedType, bool civilian, bool gang, bool criminal);
    void ScriptTaskPickUpObject(int32 commandId);

    void UpdateCompareFlag(bool state);
    void UpdatePC(int32 newIP);

    OpcodeResult ProcessOneCommand();
    OpcodeResult Process();

    void SetName(const char* name)      { strcpy_s(m_szName, name); }
    void SetName(std::string_view name) { assert(name.size() < sizeof(m_szName)); strncpy(m_szName, name.data(), name.size()); }
    void SetBaseIp(uint8* ip)           { m_pBaseIP = ip; }
    void SetCurrentIp(uint8* ip)        { m_pCurrentIP = ip; }
    void SetActive(bool active)         { m_bIsActive = active; }
    void SetExternal(bool external)     { m_bIsExternal = external; }

    //! Read a value from at the current IP then increase IP by the number of bytes read.
    template<typename T>
    T ReadAtIPAs() {
        const auto ret = *reinterpret_cast<T*>(m_pCurrentIP);
        m_pCurrentIP += sizeof(T);
        return ret;
    }

    template<eScriptCommands Command>
    OpcodeResult ProcessCommand() {
        // By default call original GTA handler
        return std::invoke(CommandHandlerTable[(size_t)Command / 100], this, Command);
    }

    static void SetCommandHandler(eScriptCommands cmd, OpcodeResult(*handler)(CRunningScript*));
};

VALIDATE_SIZE(CRunningScript, 0xE0);
