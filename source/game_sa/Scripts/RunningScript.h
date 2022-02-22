/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eScriptCommands.h"
#include "eWeaponType.h"
#include "Ped.h"

enum ePedType : uint32;

enum eScriptParameterType {
    SCRIPT_PARAM_END_OF_ARGUMENTS,
    SCRIPT_PARAM_STATIC_INT_32BITS,
    SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE,
    SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE,
    SCRIPT_PARAM_STATIC_INT_8BITS,
    SCRIPT_PARAM_STATIC_INT_16BITS,
    SCRIPT_PARAM_STATIC_FLOAT,

    // Types below are only available in GTA SA

    // Number arrays
    SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY,
    SCRIPT_PARAM_LOCAL_NUMBER_ARRAY,
    SCRIPT_PARAM_STATIC_SHORT_STRING,
    SCRIPT_PARAM_GLOBAL_SHORT_STRING_VARIABLE,
    SCRIPT_PARAM_LOCAL_SHORT_STRING_VARIABLE,
    SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY,
    SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY,
    SCRIPT_PARAM_STATIC_PASCAL_STRING,
    SCRIPT_PARAM_STATIC_LONG_STRING,
    SCRIPT_PARAM_GLOBAL_LONG_STRING_VARIABLE,
    SCRIPT_PARAM_LOCAL_LONG_STRING_VARIABLE,
    SCRIPT_PARAM_GLOBAL_LONG_STRING_ARRAY,
    SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY,
};

enum eScriptVariableType : uint8 {
    VAR_LOCAL = 1,
    VAR_GLOBAL = 2
};

enum eButtonId {
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

union tScriptParam {
    uint32 uParam;
    int32 iParam;
    float fParam;
    void* pParam;
    char* szParam;
};

VALIDATE_SIZE(tScriptParam, 0x4);

class CRunningScript {
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
    uint8*          m_pBaseIP;
    uint8*          m_pCurrentIP;
    uint8*          m_apStack[8];
    uint16          m_nSP;
    char            _pad3A[2];
    tScriptParam    m_aLocalVars[32];
    int32           m_anTimers[2];
    bool            m_bIsActive;
    bool            m_bCondResult;
    bool            m_bUseMissionCleanup;
    bool            m_bIsExternal;
    bool            m_bTextBlockOverride;
    int8            m_externalType;
    char            field_CA[2];
    int32           m_nWakeTime;
    uint16          m_nLogicalOp;
    bool            m_bNotFlag;
    bool            m_bWastedBustedCheck;
    bool            m_bWastedOrBusted;
    char            _padD5[3];
    uint8*          m_pSceneSkipIP;
    bool            m_bIsMission;
    char            _padDD[3];

    static constexpr int8 COMMAND_NOT_IMPLEMENTED_YET = -2;

public:
    using CommandHandlerFn_t = int8(__thiscall CRunningScript::*)(int32);
    using CommandHandlerTable_t = std::array<CommandHandlerFn_t, 27>;
    static inline std::array<CommandHandlerFn_t, 27>& CommandHandlerTable = *(CommandHandlerTable_t*)0x8A6168;
    static CommandHandlerTable_t reSA_CommandHandlerTable;

    static void InjectHooks();

    void Init();

    void LocateCarCommand(int32 commandId);
    void LocateObjectCommand(int32 commandId);
    void PlayAnimScriptCommand(int32 commandId);

    void LocateCharCommand(int32 commandId);
    void LocateCharCarCommand(int32 commandId);
    void LocateCharCharCommand(int32 commandId);
    void LocateCharObjectCommand(int32 commandId);

    void CarInAreaCheckCommand(int32 commandId);
    void CharInAreaCheckCommand(int32 commandId);
    void ObjectInAreaCheckCommand(int32 commandId);

    void CharInAngledAreaCheckCommand(int32 commandId);
    void FlameInAngledAreaCheckCommand(int32 commandId);
    void ObjectInAngledAreaCheckCommand(int32 commandId);

    void CollectParameters(int16 count);
    int32 CollectNextParameterWithoutIncreasingPC();

    void StoreParameters(int16 count);

    void ReadArrayInformation(int32 updateIp, uint16* outArrVarOffset, int32* outArrElemIdx);
    void ReadParametersForNewlyStartedScript(CRunningScript* newScript);
    void ReadTextLabelFromScript(char* buffer, uint8 nBufferLength);
    void GetCorrectPedModelIndexForEmergencyServiceType(ePedType pedType, int32* outModelId);
    uint16 GetIndexOfGlobalVariable();
    int16 GetPadState(uint16 playerIndex, eButtonId buttonId);

    tScriptParam* GetPointerToLocalVariable(int32 varId);
    tScriptParam* GetPointerToLocalArrayElement(int32 arrVarOffset, uint16 arrElemIdx, uint8 arrElemSize);
    tScriptParam* GetPointerToScriptVariable(eScriptVariableType variableType);

    void DoDeathArrestCheck(); // original name DoDeatharrestCheck

    void SetCharCoordinates(CPed* ped, float x, float y, float z, bool bWarpGang, bool bOffset);
    void GivePedScriptedTask(int32 pedHandle, CTask* task, int32 opcode);

    void AddScriptToList(CRunningScript** queueList);
    void RemoveScriptFromList(CRunningScript** queueList);
    void ShutdownThisScript();

    bool IsPedDead(CPed* ped);
    bool ThisIsAValidRandomPed(ePedType pedType, bool civilian, bool gang, bool criminal);
    void ScriptTaskPickUpObject(int32 commandId);

    void UpdateCompareFlag(bool state);
    void UpdatePC(int32 newIP);

    int8 ProcessOneCommand();
    int8 Process();
    int8 ProcessCommands0To99(int32 commandId);
    int8 ProcessCommands100To199(int32 commandId);
    int8 ProcessCommands200To299(int32 commandId);
    int8 ProcessCommands300To399(int32 commandId);
    int8 ProcessCommands400To499(int32 commandId);
    int8 ProcessCommands500To599(int32 commandId);
    int8 ProcessCommands600To699(int32 commandId);
    int8 ProcessCommands700To799(int32 commandId);
    int8 ProcessCommands800To899(int32 commandId);
    int8 ProcessCommands900To999(int32 commandId);
    int8 ProcessCommands1000To1099(int32 commandId);
    int8 ProcessCommands1100To1199(int32 commandId);
    int8 ProcessCommands1200To1299(int32 commandId);
    int8 ProcessCommands1300To1399(int32 commandId);
    int8 ProcessCommands1400To1499(int32 commandId);
    int8 ProcessCommands1500To1599(int32 commandId);
    int8 ProcessCommands1600To1699(int32 commandId);
    int8 ProcessCommands1700To1799(int32 commandId);
    int8 ProcessCommands1800To1899(int32 commandId);
    int8 ProcessCommands1900To1999(int32 commandId);
    int8 ProcessCommands2000To2099(int32 commandId);
    int8 ProcessCommands2100To2199(int32 commandId);
    int8 ProcessCommands2200To2299(int32 commandId);
    int8 ProcessCommands2300To2399(int32 commandId);
    int8 ProcessCommands2400To2499(int32 commandId);
    int8 ProcessCommands2500To2599(int32 commandId);
    int8 ProcessCommands2600To2699(int32 commandId);

    void SetBaseIp(uint8* ip) { m_pBaseIP = ip; }
    void SetCurrentIp(uint8* ip) { m_pCurrentIP = ip; }
    void SetActive(bool active) { m_bIsActive = active; }
    void SetExternal(bool external) { m_bIsExternal = external; }
};

VALIDATE_SIZE(CRunningScript, 0xE0);
