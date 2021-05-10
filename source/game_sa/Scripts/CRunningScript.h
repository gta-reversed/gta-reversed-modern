/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eScriptCommands.h"
#include "eWeaponType.h"
#include "CPed.h"

enum ePedType : unsigned int;

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
    unsigned int uParam;
    int iParam;
    float fParam;
    void* pParam;
    char* szParam;
};

VALIDATE_SIZE(tScriptParam, 0x4);

class CRunningScript {
public:
    CRunningScript* m_pNext;
    CRunningScript* m_pPrev;
    char m_szName[8];
    unsigned char* m_pBaseIP;
    unsigned char* m_pCurrentIP;
    unsigned char* m_apStack[8];
    unsigned short m_nSP;
    char _pad3A[2];
    tScriptParam m_aLocalVars[32];
    int m_anTimers[2];
    bool m_bIsActive;
    bool m_bCondResult;
    bool m_bUseMissionCleanup;
    bool m_bIsExternal;
    bool m_bTextBlockOverride;
    std::int8_t m_externalType;
    char field_CA[2];
    int m_nWakeTime;
    unsigned short m_nLogicalOp;
    bool m_bNotFlag;
    bool m_bWastedBustedCheck;
    bool m_bWastedOrBusted;
    char _padD5[3];
    unsigned char* m_pSceneSkipIP;
    bool m_bIsMission;
    char _padDD[3];

public:
    static unsigned char(__thiscall** CommandHandlerTable)(CRunningScript* _this, unsigned short commandId); // static unsigned char(__thiscall *CommandHandlerTable[27])(CRunningScript *,unsigned short )

    static void InjectHooks();

    void Init();

    void LocateCarCommand(int commandId);
    void LocateObjectCommand(int commandId);
    void PlayAnimScriptCommand(int commandId);

    void LocateCharCommand(int commandId);
    void LocateCharCarCommand(int commandId);
    void LocateCharCharCommand(int commandId);
    void LocateCharObjectCommand(int commandId);

    void CarInAreaCheckCommand(int commandId);
    void CharInAreaCheckCommand(int commandId);
    void ObjectInAreaCheckCommand(int commandId);

    void CharInAngledAreaCheckCommand(int commandId);
    void FlameInAngledAreaCheckCommand(int commandId);
    void ObjectInAngledAreaCheckCommand(int commandId);

    void CollectParameters(short count);
    tScriptParam CollectNextParameterWithoutIncreasingPC();

    void StoreParameters(short count);

    void ReadArrayInformation(int move, unsigned short* pOffset, int* pIdx);
    void ReadParametersForNewlyStartedScript(CRunningScript* pNewScript);
    void ReadTextLabelFromScript(char* pBuffer, unsigned char nBufferLength);
    void GetCorrectPedModelIndexForEmergencyServiceType(ePedType pedType, int* pModelId);
    short GetIndexOfGlobalVariable();
    short GetPadState(unsigned short playerIndex, eButtonId buttonId);

    void* GetPointerToLocalVariable(int varId);
    void* GetPointerToLocalArrayElement(int off, unsigned short idx, unsigned char mul);
    tScriptParam* GetPointerToScriptVariable(unsigned char variableType);

    void DoDeathArrestCheck(); // original name DoDeatharrestCheck

    void SetCharCoordinates(CPed* pPed, float x, float y, float z, bool bWarpGang, bool bOffset);
    void GivePedScriptedTask(std::int32_t pedHandle, CTask* task, std::int32_t opcode);

    void AddScriptToList(CRunningScript** queueList);
    void RemoveScriptFromList(CRunningScript** queueList);
    void ShutdownThisScript();

    bool IsPedDead(CPed* pPed);
    bool ThisIsAValidRandomPed(ePedType pedType, bool civilian, bool gang, bool criminal);
    void ScriptTaskPickUpObject(int commandId);

    void UpdateCompareFlag(bool state);
    void UpdatePC(int newIP);

    void ProcessOneCommand();
    void Process();
    void ProcessCommands0To99(int commandId);
    void ProcessCommands100To199(int commandId);
    void ProcessCommands200To299(int commandId);
    void ProcessCommands300To399(int commandId);
    void ProcessCommands400To499(int commandId);
    void ProcessCommands500To599(int commandId);
    void ProcessCommands600To699(int commandId);
    void ProcessCommands700To799(int commandId);
    void ProcessCommands800To899(int commandId);
    void ProcessCommands900To999(int commandId);
    void ProcessCommands1000To1099(int commandId);
    void ProcessCommands1100To1199(int commandId);
    void ProcessCommands1200To1299(int commandId);
    void ProcessCommands1300To1399(int commandId);
    void ProcessCommands1400To1499(int commandId);
    void ProcessCommands1500To1599(int commandId);
    void ProcessCommands1600To1699(int commandId);
    void ProcessCommands1700To1799(int commandId);
    void ProcessCommands1800To1899(int commandId);
    void ProcessCommands1900To1999(int commandId);
    void ProcessCommands2000To2099(int commandId);
    void ProcessCommands2100To2199(int commandId);
    void ProcessCommands2200To2299(int commandId);
    void ProcessCommands2300To2399(int commandId);
    void ProcessCommands2400To2499(int commandId);
    void ProcessCommands2500To2599(int commandId);
    void ProcessCommands2600To2699(int commandId);
};

VALIDATE_SIZE(CRunningScript, 0xE0);
