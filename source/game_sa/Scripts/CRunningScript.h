/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "ePedType.h"
#include "eScriptCommands.h"
#include "eWeaponType.h"
#include "CPed.h"

enum eScriptParameterType {
    SCRIPTPARAM_END_OF_ARGUMENTS,
    SCRIPTPARAM_STATIC_INT_32BITS,
    SCRIPTPARAM_GLOBAL_NUMBER_VARIABLE,
    SCRIPTPARAM_LOCAL_NUMBER_VARIABLE,
    SCRIPTPARAM_STATIC_INT_8BITS,
    SCRIPTPARAM_STATIC_INT_16BITS,
    SCRIPTPARAM_STATIC_FLOAT,

    // Types below are only available in GTA SA

    // Number arrays
    SCRIPTPARAM_GLOBAL_NUMBER_ARRAY,
    SCRIPTPARAM_LOCAL_NUMBER_ARRAY,
    SCRIPTPARAM_STATIC_SHORT_STRING,
    SCRIPTPARAM_GLOBAL_SHORT_STRING_VARIABLE,
    SCRIPTPARAM_LOCAL_SHORT_STRING_VARIABLE,
    SCRIPTPARAM_GLOBAL_SHORT_STRING_ARRAY,
    SCRIPTPARAM_LOCAL_SHORT_STRING_ARRAY,
    SCRIPTPARAM_STATIC_PASCAL_STRING,
    SCRIPTPARAM_STATIC_LONG_STRING,
    SCRIPTPARAM_GLOBAL_LONG_STRING_VARIABLE,
    SCRIPTPARAM_LOCAL_LONG_STRING_VARIABLE,
    SCRIPTPARAM_GLOBAL_LONG_STRING_ARRAY,
    SCRIPTPARAM_LOCAL_LONG_STRING_ARRAY,
};

enum eButtonID
{
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
    void *pParam;
    char *szParam;
};

VALIDATE_SIZE(tScriptParam, 0x4);

class  CRunningScript {
public:
    CRunningScript *m_pNext;
    CRunningScript *m_pPrev;
    char            m_szName[8];
    unsigned char  *m_pBaseIP;
    unsigned char  *m_pCurrentIP;
    unsigned char  *m_apStack[8];
    unsigned short  m_nSP;
private:
    char _pad3A[2];
public:
    tScriptParam	m_aLocalVars[32];
    int             m_anTimers[2];
    bool            m_bIsActive;
    bool            m_bCondResult;
    bool            m_bUseMissionCleanup;
    bool            m_bIsExternal;
    bool            m_bTextBlockOverride;
    std::int8_t     m_externalType;
private:
    char field_CA[2];
public:
    int             m_nWakeTime;
    unsigned short  m_nLogicalOp;
    bool            m_bNotFlag;
    bool            m_bWastedBustedCheck;
    bool            m_bWastedOrBusted;
private:
    char _padD5[3];
public:
    unsigned char  *m_pSceneSkipIP;
    bool            m_bIsMission;
private:
    char _padDD[3];
public:

     static unsigned char(__thiscall **CommandHandlerTable)(CRunningScript *_this,unsigned short commandID); // static unsigned char(__thiscall *CommandHandlerTable[27])(CRunningScript *,unsigned short )

     static void InjectHooks();

    //! Adds script to list
     void AddScriptToList(CRunningScript **queuelist);
     void CarInAreaCheckCommand(int commandID);
     void CharInAngledAreaCheckCommand(int commandID);
     void CharInAreaCheckCommand(int commandID);
    //! Collects parameter and returns it.
     tScriptParam CollectNextParameterWithoutIncreasingPC();
     void CollectParameters(short count);
     void DoDeatharrestCheck();
     void FlameInAngledAreaCheckCommand(int commandID);
     void GetCorrectPedModelIndexForEmergencyServiceType(ePedType pedType, int *pModelId);
    //! Returns offset of global variable
     short GetIndexOfGlobalVariable();
    //! Returns state of pad button , see eButtonID.
     short GetPadState(unsigned short playerIndex, unsigned short buttonID);   
    //! Returns pointer to local variable pointed by offset and array index as well as multiplier.
     void *GetPointerToLocalArrayElement(int off, unsigned short idx, unsigned char mul);
     void *GetPointerToLocalVariable(int varId);
    //! Returns pointer to script variable of any type.
     tScriptParam *GetPointerToScriptVariable(unsigned char variableType);
     void GivePedScriptedTask(std::int32_t pedHandle, CTask* task, std::int32_t opcode);
     void Init();
     bool IsPedDead(CPed *pPed);
     void LocateCarCommand(int commandID);
     void LocateCharCarCommand(int commandID);
     void LocateCharCharCommand(int commandID);
     void LocateCharCommand(int commandID);
     void LocateCharObjectCommand(int commandID);
     void LocateObjectCommand(int commandID);
     void ObjectInAngledAreaCheckCommand(int commandID);
     void ObjectInAreaCheckCommand(int commandID);
     void PlayAnimScriptCommand(int commandID);
     void Process();
     char ProcessCommands0To99(int commandID);
     char ProcessCommands1000To1099(int commandID);
     char ProcessCommands100To199(int commandID);
     char ProcessCommands1100To1199(int commandID);
     char ProcessCommands1200To1299(int commandID);
     char ProcessCommands1300To1399(int commandID);
     char ProcessCommands1400To1499(int commandID);
     char ProcessCommands1500To1599(int commandID);
     char ProcessCommands1600To1699(int commandID);
     char ProcessCommands1700To1799(int commandID);
     char ProcessCommands1800To1899(int commandID);
     char ProcessCommands1900To1999(int commandID);
     char ProcessCommands2000To2099(int commandID);
     char ProcessCommands200To299(int commandID);
     char ProcessCommands2100To2199(int commandID);
     char ProcessCommands2200To2299(int commandID);
     char ProcessCommands2300To2399(int commandID);
     char ProcessCommands2400To2499(int commandID);
     char ProcessCommands2500To2599(int commandID);
     char ProcessCommands2600To2699(int commandID);
     char ProcessCommands300To399(int commandID);
     char ProcessCommands400To499(int commandID);
     char ProcessCommands500To599(int commandID);
     char ProcessCommands600To699(int commandID);
     char ProcessCommands700To799(int commandID);
     char ProcessCommands800To899(int commandID);
     char ProcessCommands900To999(int commandID);
     void ProcessOneCommand();
    //! Reads array offset and value from array index variable.
     void ReadArrayInformation(int move, unsigned short *pOffset, int *pIdx);
    //! Collects parameters and puts them to local variables of new script
     void ReadParametersForNewlyStartedScript(CRunningScript *pNewScript);
    //! Collects string parameter
     void ReadTextLabelFromScript(char *pBuffer, unsigned char nBufferLength);
    //! Removes script from list
     void RemoveScriptFromList(CRunningScript **queuelist);
     void ScriptTaskPickUpObject(int commandID);
     void SetCharCoordinates(CPed *pPed, float x_coord, float y_coord, float z_coord, bool bWarpGang, bool bOffset);
    //! Terminates a script
     void ShutdownThisScript();
     void StoreParameters(short count);
     bool ThisIsAValidRandomPed(ePedType pedType, bool civilian, bool gang, bool criminal);
    //! Updates comparement flag, used in conditional commands
     void UpdateCompareFlag(bool state);
    //! Sets instruction pointer, used in GOTO-like commands
     void UpdatePC(int newIP);
};

//#include "meta/meta.CRunningScript.h"

VALIDATE_SIZE(CRunningScript, 0xE0);
