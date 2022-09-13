#include "StdInc.h"

#include "RunningScript.h"
#include "TheScripts.h"
#include "CarGenerator.h"
#include "Hud.h"
#include "ReversibleHooks/ReversibleHook/ScriptCommand.h"

// Commands stuff
#include "CommandParser/Parser.hpp"

/*!
* Make sure to include the command headers here, otherwise they won't be registered,
* and the default GTA handler will be called.
* 
* Currently we don't include the Commands/CLEO headers at all.
*
* Eventually we'll get rid of this header based approach, and switch to using cpp files instead,
* currently it's not possible because of the way it's set up.
* (Once all old functions are reworked to use the parser)
*/

#include "Commands/Basic.hpp"
#include "Commands/Car.hpp"
#include "Commands/Comparasion.hpp"
#include "Commands/Generic.hpp"
#include "Commands/Mission.hpp"
#include "Commands/Player.hpp"
#include "Commands/Sequence.hpp"
#include "Commands/Utility.hpp"
#include "Commands/Camera.hpp"
#include "Commands/Char.hpp"
#include "Commands/Clock.hpp"
#include "Commands/Game.hpp"
#include "Commands/Math.hpp"
#include "Commands/Pad.hpp"
#include "Commands/Script.hpp"
#include "Commands/Text.hpp"

// Must be included after the commands
#include "CommandParser/LUTGenerator.hpp"

// https://library.sannybuilder.com/#/sa

static auto s_CommandHandlerLUT = notsa::script::GenerateLUT();

void CRunningScript::InjectHooks() {
    RH_ScopedClass(CRunningScript);
    RH_ScopedCategory("Scripts");

    RH_ScopedInstall(Init, 0x4648E0);
    RH_ScopedInstall(GetCorrectPedModelIndexForEmergencyServiceType, 0x464F50);

    // RH_ScopedInstall(PlayAnimScriptCommand, 0x470150);
    // RH_ScopedInstall(LocateCarCommand, 0x487A20);
    // RH_ScopedInstall(LocateCharCommand, 0x486D80);
    // RH_ScopedInstall(LocateObjectCommand, 0x487D10);
    // RH_ScopedInstall(LocateCharCarCommand, 0x487420);
    // RH_ScopedInstall(LocateCharCharCommand, 0x4870F0);
    // RH_ScopedInstall(LocateCharObjectCommand, 0x487720);
    // RH_ScopedInstall(CarInAreaCheckCommand, 0x488EC0);
    // RH_ScopedInstall(CharInAreaCheckCommand, 0x488B50);
    // RH_ScopedInstall(ObjectInAreaCheckCommand, 0x489150);
    // RH_ScopedInstall(CharInAngledAreaCheckCommand, 0x487F60);
    // RH_ScopedInstall(FlameInAngledAreaCheckCommand, 0x488780);
    // RH_ScopedInstall(ObjectInAngledAreaCheckCommand, 0x4883F0);
    RH_ScopedInstall(CollectParameters, 0x464080, { .stackArguments = 1 });
    RH_ScopedInstall(CollectNextParameterWithoutIncreasingPC, 0x464250, { .stackArguments = 0 });
    RH_ScopedInstall(StoreParameters, 0x464370, { .stackArguments = 1 });
    RH_ScopedInstall(ReadArrayInformation, 0x463CF0, { .stackArguments = 3 });
    RH_ScopedInstall(ReadParametersForNewlyStartedScript, 0x464500, { .stackArguments = 1 });
    RH_ScopedInstall(ReadTextLabelFromScript, 0x463D50, { .stackArguments = 2 });
    RH_ScopedInstall(GetIndexOfGlobalVariable, 0x464700, { .stackArguments = 0 });
    RH_ScopedInstall(GetPadState, 0x485B10);
    RH_ScopedInstall(GetPointerToLocalVariable, 0x463CA0, { .stackArguments = 1 });
    RH_ScopedInstall(GetPointerToLocalArrayElement, 0x463CC0, { .stackArguments = 3 });
    RH_ScopedInstall(GetPointerToScriptVariable, 0x464790, { .stackArguments = 1 });
    RH_ScopedInstall(DoDeathArrestCheck, 0x485A50);
    RH_ScopedInstall(SetCharCoordinates, 0x464DC0);
    RH_ScopedInstall(GivePedScriptedTask, 0x465C20);
    RH_ScopedInstall(AddScriptToList, 0x464C00, { .stackArguments = 1 });
    RH_ScopedInstall(RemoveScriptFromList, 0x464BD0, { .stackArguments = 1 });
    // RH_ScopedInstall(ShutdownThisScript, 0x465AA0);
    RH_ScopedInstall(IsPedDead, 0x464D70);
    RH_ScopedInstall(ThisIsAValidRandomPed, 0x489490);
    // RH_ScopedInstall(ScriptTaskPickUpObject, 0x46AF50);
    RH_ScopedInstall(UpdateCompareFlag, 0x4859D0, { .stackArguments = 1 });
    RH_ScopedInstall(UpdatePC, 0x464DA0, { .stackArguments = 1 });
    RH_ScopedInstall(ProcessOneCommand, 0x469EB0);
    RH_ScopedInstall(Process, 0x469F00);

    // Enable in `StdInc.h` if needed (Don't forget to disabled it when committing)
#ifdef ENABLE_SCRIPT_COMMAND_HOOKS
    const auto HookCommand = []<size_t Idx>() {
        using namespace ReversibleHooks::ReversibleHook;
        ReversibleHooks::AddItemToCategory(
            "Scripts/Commands",
            std::make_shared<ScriptCommand<(eScriptCommands)Idx>>()
        );
    };
    notsa::script::IterateCommandIDs(HookCommand);
#endif
}

// 0x4648E0
void CRunningScript::Init() {
    SetName("noname");
    m_pBaseIP = nullptr;
    m_pPrev = nullptr;
    m_pNext = nullptr;
    m_pCurrentIP = nullptr;
    memset(m_apStack, 0, sizeof(m_apStack));
    m_nSP = 0;
    m_nWakeTime = 0;
    m_bIsActive = false;
    m_bCondResult = false;
    m_bUseMissionCleanup = false;
    m_bIsExternal = false;
    m_bTextBlockOverride = false;
    m_nExternalType = -1;
    memset(m_aLocalVars, 0, sizeof(m_aLocalVars));
    m_nLogicalOp = 0;
    m_bNotFlag = false;
    m_bDeathArrestExecuted = false;
    m_pSceneSkipIP = nullptr;
    m_bIsMission = false;
    m_bDeathArrestEnabled = true;
}

/*!
 * Adds script to list
 * @addr 0x464C00
 */
void CRunningScript::AddScriptToList(CRunningScript** queueList) {
    m_pNext = *queueList;
    m_pPrev = nullptr;
    if (*queueList)
        (*queueList)->m_pPrev = this;
    *queueList = this;
}

/*!
 * Removes script from list
 * @addr 0x464BD0
 */
void CRunningScript::RemoveScriptFromList(CRunningScript** queueList) {
    if (m_pPrev)
        m_pPrev->m_pNext = m_pNext;
    else
        *queueList = m_pNext;

    if (m_pNext)
        m_pNext->m_pPrev = m_pPrev;
}

/*!
 * Terminates a script
 * @addr 0x465AA0
 */
void CRunningScript::ShutdownThisScript() {
    plugin::CallMethod<0x465AA0, CRunningScript*>(this);
}

// 0x465C20
void CRunningScript::GivePedScriptedTask(int32 pedHandle, CTask* task, int32 opcode) {
    if (pedHandle == -1) {
        CTaskSequences::AddTaskToActiveSequence(task);
        return;
    }

    CPed* ped = GetPedPool()->GetAtRef(pedHandle);
    CPedGroup* pedGroup = CPedGroups::GetPedsGroup(ped);

    CPed* otherPed = nullptr;
    if (m_nExternalType == 5 || m_nExternalType == 2 || !m_nExternalType || m_nExternalType == 3) {
        auto* localVariable = reinterpret_cast<int32*>(GetPointerToLocalVariable(0));
        otherPed = GetPedPool()->GetAtRef(*localVariable);
    }

    if (ped->bHasAScriptBrain && otherPed != ped) {
        delete task;
    } else if (otherPed && m_nExternalType == 5) {
        if (CScriptedBrainTaskStore::SetTask(ped, task)) {
            const int32 slot = CPedScriptedTaskRecord::GetVacantSlot();
            CPedScriptedTaskRecord::ms_scriptedTasks[slot].SetAsAttractorScriptTask(ped, opcode, task);
        }
    } else if (!pedGroup || ped->IsPlayer()) { // todo: FIXBUGS Warning	C6011 Dereferencing NULL pointer 'ped'
        CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, task, false);
        auto* event = static_cast<CEventScriptCommand*>(ped->GetEventGroup().Add(&eventScriptCommand, false));
        if (event) {
            const int32 slot = CPedScriptedTaskRecord::GetVacantSlot();
            CPedScriptedTaskRecord::ms_scriptedTasks[slot].Set(ped, opcode, event);
        }
    } else {
        pedGroup->GetIntelligence().SetScriptCommandTask(ped, task);
        CTask* scriptedTask = pedGroup->GetIntelligence().GetTaskScriptCommand(ped);
        const int32 slot = CPedScriptedTaskRecord::GetVacantSlot();
        CPedScriptedTaskRecord::ms_scriptedTasks[slot].SetAsGroupTask(ped, opcode, scriptedTask);
        delete task;
    }
}

// 0x470150
void CRunningScript::PlayAnimScriptCommand(int32 commandId) {
    plugin::CallMethod<0x470150, CRunningScript*, int32>(this, commandId);
}

// 0x487A20
void CRunningScript::LocateCarCommand(int32 commandId) {
    plugin::CallMethod<0x487A20, CRunningScript*, int32>(this, commandId);
}

// 0x486D80
void CRunningScript::LocateCharCommand(int32 commandId) {
    plugin::CallMethod<0x486D80, CRunningScript*, int32>(this, commandId);
}

// 0x487D10
void CRunningScript::LocateObjectCommand(int32 commandId) {
    plugin::CallMethod<0x487D10, CRunningScript*, int32>(this, commandId);
}

// 0x487420
void CRunningScript::LocateCharCarCommand(int32 commandId) {
    plugin::CallMethod<0x487420, CRunningScript*, int32>(this, commandId);
}

// 0x4870F0
void CRunningScript::LocateCharCharCommand(int32 commandId) {
    plugin::CallMethod<0x4870F0, CRunningScript*, int32>(this, commandId);
}

// 0x487720
void CRunningScript::LocateCharObjectCommand(int32 commandId) {
    plugin::CallMethod<0x487720, CRunningScript*, int32>(this, commandId);
}

// 0x488EC0
void CRunningScript::CarInAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x488EC0, CRunningScript*, int32>(this, commandId);
}

// 0x488B50
void CRunningScript::CharInAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x488B50, CRunningScript*, int32>(this, commandId);
}

// 0x489150
void CRunningScript::ObjectInAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x489150, CRunningScript*, int32>(this, commandId);
}

// 0x487F60
void CRunningScript::CharInAngledAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x487F60, CRunningScript*, int32>(this, commandId);
}

// 0x488780
void CRunningScript::FlameInAngledAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x488780, CRunningScript*, int32>(this, commandId);
}

// 0x4883F0
void CRunningScript::ObjectInAngledAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x4883F0, CRunningScript*, int32>(this, commandId);
}

// 0x464D70
bool CRunningScript::IsPedDead(CPed* ped) const {
    ePedState pedState = ped->m_nPedState;
    return pedState == PEDSTATE_DEAD || pedState == PEDSTATE_DIE || pedState == PEDSTATE_DIE_BY_STEALTH;
}

// 0x489490
bool CRunningScript::ThisIsAValidRandomPed(ePedType pedType, bool civilian, bool gang, bool criminal) {
    switch (pedType) {
    case PED_TYPE_CIVMALE:
    case PED_TYPE_CIVFEMALE:
        return civilian;
    case PED_TYPE_GANG1:
    case PED_TYPE_GANG2:
    case PED_TYPE_GANG3:
    case PED_TYPE_GANG4:
    case PED_TYPE_GANG5:
    case PED_TYPE_GANG6:
    case PED_TYPE_GANG7:
    case PED_TYPE_GANG8:
    case PED_TYPE_GANG9:
        return gang;
    case PED_TYPE_CRIMINAL:
    case PED_TYPE_PROSTITUTE:
        return criminal;
    default:
        return false;
    }
}

// 0x485A50
void CRunningScript::DoDeathArrestCheck() {
    if (!m_bDeathArrestEnabled)
        return;

    if (!CTheScripts::IsPlayerOnAMission())
        return;

    auto& playerInfo = FindPlayerInfo();
    if (!playerInfo.IsRestartingAfterDeath() && !playerInfo.IsRestartingAfterArrest())
        return;

    if (m_nSP > 1u) { // todo: refactor
        do
            --m_nSP;
        while (m_nSP > 1u);
    }

    m_pCurrentIP = m_apStack[--m_nSP];
    CMessages::ClearSmallMessagesOnly();
    CTheScripts::ScriptSpace[CTheScripts::OnAMissionFlag] = 0;
    m_bDeathArrestExecuted = true;
    m_nWakeTime = 0;
}

// 0x464F50
void CRunningScript::GetCorrectPedModelIndexForEmergencyServiceType(ePedType pedType, int32* outModelId) {
    switch (*outModelId) {
    case MODEL_LAPD1:
    case MODEL_SFPD1:
    case MODEL_LVPD1:
    case MODEL_LAPDM1:
        if (pedType == PED_TYPE_COP) {
            *outModelId = COP_TYPE_CITYCOP;
        }
        break;
    case MODEL_CSHER:
        if (pedType == PED_TYPE_COP) {
            *outModelId = COP_TYPE_CSHER;
        }
        break;
    case MODEL_SWAT:
        if (pedType == PED_TYPE_COP) {
            *outModelId = COP_TYPE_SWAT1;
        }
        break;
    case MODEL_FBI:
        if (pedType == PED_TYPE_COP) {
            *outModelId = COP_TYPE_FBI;
        }
        break;
    case MODEL_ARMY:
        if (pedType == PED_TYPE_COP) {
            *outModelId = COP_TYPE_ARMY;
        }
        break;
    default:
        return;
    }
}

// Returns state of pad button
// 0x485B10
int16 CRunningScript::GetPadState(uint16 playerIndex, eButtonId buttonId) {
    const auto* pad = CPad::GetPad(playerIndex);
    switch (buttonId) {
    case BUTTON_LEFT_STICK_X:    return pad->NewState.LeftStickX;
    case BUTTON_LEFT_STICK_Y:    return pad->NewState.LeftStickY;
    case BUTTON_RIGHT_STICK_X:   return pad->NewState.RightStickX;
    case BUTTON_RIGHT_STICK_Y:   return pad->NewState.RightStickY;
    case BUTTON_LEFT_SHOULDER1:  return pad->NewState.LeftShoulder1;
    case BUTTON_LEFT_SHOULDER2:  return pad->NewState.LeftShoulder2;
    case BUTTON_RIGHT_SHOULDER1: return pad->NewState.RightShoulder1;
    case BUTTON_RIGHT_SHOULDER2: return pad->NewState.RightShoulder2;
    case BUTTON_DPAD_UP:         return pad->NewState.DPadUp;
    case BUTTON_DPAD_DOWN:       return pad->NewState.DPadDown;
    case BUTTON_DPAD_LEFT:       return pad->NewState.DPadLeft;
    case BUTTON_DPAD_RIGHT:      return pad->NewState.DPadRight;
    case BUTTON_START:           return pad->NewState.Start;
    case BUTTON_SELECT:          return pad->NewState.Select;
    case BUTTON_SQUARE:          return pad->NewState.ButtonSquare;
    case BUTTON_TRIANGLE:        return pad->NewState.ButtonTriangle;
    case BUTTON_CROSS:           return pad->NewState.ButtonCross;
    case BUTTON_CIRCLE:          return pad->NewState.ButtonCircle;
    case BUTTON_LEFTSHOCK:       return pad->NewState.ShockButtonL;
    case BUTTON_RIGHTSHOCK:      return pad->NewState.ShockButtonR;
    default:                     return OR_CONTINUE;
    }
}

// 0x46AF50
void CRunningScript::ScriptTaskPickUpObject(int32 commandId) {
    plugin::CallMethod<0x46AF50, CRunningScript*, int32>(this, commandId);
}

// 0x464DC0
void CRunningScript::SetCharCoordinates(CPed* ped, float x, float y, float z, bool bWarpGang, bool bOffset) {
    if (z <= MAP_Z_LOW_LIMIT)
        z = CWorld::FindGroundZForCoord(x, y);

    CVehicle* vehicle = ped->bInVehicle ? ped->m_pVehicle : nullptr;
    if (vehicle) {
        CVector pos = { x, y, vehicle->GetDistanceFromCentreOfMassToBaseOfModel() + z };
        vehicle->Teleport(pos, false);
        CTheScripts::ClearSpaceForMissionEntity(&pos, vehicle);
    } else {
        CVector pos = { x, y, bOffset ? ped->GetDistanceFromCentreOfMassToBaseOfModel() + z : z };
        CTheScripts::ClearSpaceForMissionEntity(&pos, ped);
        auto* group = CPedGroups::GetPedsGroup(ped);
        if (group && group->GetMembership().IsLeader(ped) && bWarpGang) {
            group->Teleport(&pos);
        } else {
            ped->Teleport(pos, false);
        }
    }
}

// 0x463CA0
tScriptParam* CRunningScript::GetPointerToLocalVariable(int32 varIndex) {
    if (m_bIsMission)
        return reinterpret_cast<tScriptParam*>(&CTheScripts::LocalVariablesForCurrentMission[varIndex]);
    else
        return reinterpret_cast<tScriptParam*>(&m_aLocalVars[varIndex]);
}

/*!
 * Returns pointer to local variable pointed by offset and array index as well as multiplier.
 * @addr 0x463CC0
 */
tScriptParam* CRunningScript::GetPointerToLocalArrayElement(int32 arrVarOffset, uint16 arrElemIdx, uint8 arrElemSize) {
    int32 index = arrVarOffset + arrElemSize * arrElemIdx;
    return GetPointerToLocalVariable(index);
}

/*!
 * Returns pointer to script variable of any type.
 * @addr 0x464790
 */
tScriptParam* CRunningScript::GetPointerToScriptVariable(eScriptVariableType variableType) {
    uint8  arrElemSize;
    uint16 arrVarOffset;
    int32  arrElemIdx;

    int8 type = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
    switch (type) {
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_VARIABLE:
    case SCRIPT_PARAM_GLOBAL_LONG_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        return reinterpret_cast<tScriptParam*>(&CTheScripts::ScriptSpace[index]);
    }
    case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
    case SCRIPT_PARAM_LOCAL_SHORT_STRING_VARIABLE:
    case SCRIPT_PARAM_LOCAL_LONG_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        return GetPointerToLocalVariable(index);
    }

    case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY:
    case SCRIPT_PARAM_GLOBAL_LONG_STRING_ARRAY:
        ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
        if (type == SCRIPT_PARAM_GLOBAL_LONG_STRING_ARRAY)
            return reinterpret_cast<tScriptParam*>(&CTheScripts::ScriptSpace[LONG_STRING_SIZE * arrElemIdx + arrVarOffset]);
        else if (type == SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY)
            return reinterpret_cast<tScriptParam*>(&CTheScripts::ScriptSpace[SHORT_STRING_SIZE * arrElemIdx + arrVarOffset]);
        else
            return reinterpret_cast<tScriptParam*>(&CTheScripts::ScriptSpace[4 * arrElemIdx + arrVarOffset]);

    case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
    case SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY:
    case SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY:
        ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
        if (type == SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY)
            arrElemSize = 4;
        else if (type == SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY)
            arrElemSize = 2;
        else
            arrElemSize = 1;
        return GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, arrElemSize);

    default:
        NOTSA_UNREACHABLE();
    }
}

/*!
 * Returns offset of global variable
 * @addr 0x464700
 */
uint16 CRunningScript::GetIndexOfGlobalVariable() {
    uint16 arrVarOffset;
    int32  arrElemIdx;

    switch (CTheScripts::Read1ByteFromScript(m_pCurrentIP)) {
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        return CTheScripts::Read2BytesFromScript(m_pCurrentIP);
    case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
        ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
        return arrVarOffset + 4 * arrElemIdx;
    default:
        // todo: ???
        return (uint16)(uint32)this;
    }
}

// 0x464080
void CRunningScript::CollectParameters(int16 count) {
    uint16 arrVarOffset;
    int32  arrElemIdx;

    for (auto i = 0; i < count; i++) {
        switch (CTheScripts::Read1ByteFromScript(m_pCurrentIP)) {
        case SCRIPT_PARAM_STATIC_INT_32BITS:
            ScriptParams[i].iParam = CTheScripts::Read4BytesFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            ScriptParams[i].iParam = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[index]);
            break;
        }
        case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            ScriptParams[i] = *GetPointerToLocalVariable(index);
            break;
        }
        case SCRIPT_PARAM_STATIC_INT_8BITS:
            ScriptParams[i].iParam = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_STATIC_INT_16BITS:
            ScriptParams[i].iParam = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_STATIC_FLOAT:
            ScriptParams[i].fParam = CTheScripts::ReadFloatFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
            ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
            ScriptParams[i].iParam = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrVarOffset + 4 * arrElemIdx]);
            break;
        case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
            ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
            ScriptParams[i] = *GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 1);
            break;
        }
    }
}

/*!
 * Collects parameter and returns it.
 * @addr 0x464250
 */
int32 CRunningScript::CollectNextParameterWithoutIncreasingPC() {
    uint16 arrVarOffset;
    int32  arrElemIdx;
    uint8* ip = m_pCurrentIP;
    int32  result = -1;

    switch (CTheScripts::Read1ByteFromScript(m_pCurrentIP)) {
    case SCRIPT_PARAM_STATIC_INT_32BITS:
    case SCRIPT_PARAM_STATIC_FLOAT:
        result = CTheScripts::Read4BytesFromScript(m_pCurrentIP);
        break;
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        result = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[index]);
        break;
    }
    case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        result = GetPointerToLocalVariable(index)->iParam;
        break;
    }
    case SCRIPT_PARAM_STATIC_INT_8BITS:
        result = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
        break;
    case SCRIPT_PARAM_STATIC_INT_16BITS:
        result = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        break;
    case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
        ReadArrayInformation(false, &arrVarOffset, &arrElemIdx);
        result = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrVarOffset + 4 * arrElemIdx]);
        break;
    case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
        ReadArrayInformation(false, &arrVarOffset, &arrElemIdx);
        result = GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 1)->iParam;
        break;
    }

    m_pCurrentIP = ip;
    return result;
}

/*!
 * @addr 0x464370
 */
void CRunningScript::StoreParameters(int16 count) {
    uint16 arrVarOffset;
    int32  arrElemIdx;

    for (auto i = 0; i < count; i++) {
        switch (CTheScripts::Read1ByteFromScript(m_pCurrentIP)) {
        case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[index]) = ScriptParams[i].iParam;
            break;
        }
        case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            *GetPointerToLocalVariable(index) = ScriptParams[i];
            break;
        }
        case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
            ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
            *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrVarOffset + 4 * arrElemIdx]) = ScriptParams[i].iParam;
            break;
        case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
            ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
            *GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 1) = ScriptParams[i];
            break;
        }
    }
}

// Reads array var base offset and element index from index variable.
// 0x463CF0
void CRunningScript::ReadArrayInformation(int32 updateIp, uint16* outArrVarOffset, int32* outArrElemIdx) {
    auto* ip = m_pCurrentIP;

    *outArrVarOffset      = CTheScripts::Read2BytesFromScript(ip);
    uint16 arrayIndexVar  = CTheScripts::Read2BytesFromScript(ip);
    bool isGlobalIndexVar = CTheScripts::Read2BytesFromScript(ip) < 0; // high bit set

    if (isGlobalIndexVar)
        *outArrElemIdx = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrayIndexVar]);
    else
        *outArrElemIdx = GetPointerToLocalVariable(arrayIndexVar)->iParam;

    if (updateIp)
        m_pCurrentIP = ip;
}

// Collects parameters and puts them to local variables of new script
// 0x464500
void CRunningScript::ReadParametersForNewlyStartedScript(CRunningScript* newScript) {
    uint16 arrVarOffset;
    int32  arrElemIdx;
    int8   type = CTheScripts::Read1ByteFromScript(m_pCurrentIP);

    for (int i = 0; type != SCRIPT_PARAM_END_OF_ARGUMENTS; type = CTheScripts::Read1ByteFromScript(m_pCurrentIP), i++) {
        switch (type) {
        case SCRIPT_PARAM_STATIC_INT_32BITS:
            newScript->m_aLocalVars[i].iParam = CTheScripts::Read4BytesFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            newScript->m_aLocalVars[i].iParam = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[index]);
            break;
        }
        case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            newScript->m_aLocalVars[i] = *GetPointerToLocalVariable(index);
            break;
        }
        case SCRIPT_PARAM_STATIC_INT_8BITS:
            newScript->m_aLocalVars[i].iParam = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_STATIC_INT_16BITS:
            newScript->m_aLocalVars[i].iParam = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_STATIC_FLOAT:
            newScript->m_aLocalVars[i].fParam = CTheScripts::ReadFloatFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
            ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
            newScript->m_aLocalVars[i].iParam = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrVarOffset + 4 * arrElemIdx]);
            break;
        case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
            ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
            newScript->m_aLocalVars[i] = *GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 1);
            break;
        default:
            break;
        }
    }
}

// Collects string parameter
// 0x463D50
void CRunningScript::ReadTextLabelFromScript(char* buffer, uint8 nBufferLength) {
    uint16 arrVarOffset;
    int32  arrElemIdx;

    int8 type = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
    switch (type) {
    case SCRIPT_PARAM_STATIC_SHORT_STRING:
        for (auto i = 0; i < SHORT_STRING_SIZE; i++)
            buffer[i] = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
        break;

    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        strncpy(buffer, (char*)&CTheScripts::ScriptSpace[index], SHORT_STRING_SIZE);
        break;
    }

    case SCRIPT_PARAM_LOCAL_SHORT_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        strncpy(buffer, (char*)GetPointerToLocalVariable(index), SHORT_STRING_SIZE);
        break;
    }

    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY:
    case SCRIPT_PARAM_GLOBAL_LONG_STRING_ARRAY:
        ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
        if (type == SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY)
            strncpy(buffer, (char*)&CTheScripts::ScriptSpace[SHORT_STRING_SIZE * arrElemIdx + arrVarOffset], SHORT_STRING_SIZE);
        else
            strncpy(buffer, (char*)&CTheScripts::ScriptSpace[LONG_STRING_SIZE * arrElemIdx + arrVarOffset], std::min<uint8>(nBufferLength, LONG_STRING_SIZE));
        break;

    case SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY:
    case SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY:
        ReadArrayInformation(true, &arrVarOffset, &arrElemIdx);
        if (type == SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY)
            strncpy(buffer, (char*)GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 2), SHORT_STRING_SIZE);
        else
            strncpy(buffer, (char*)GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 4), std::min<uint8>(nBufferLength, LONG_STRING_SIZE));
        break;

    case SCRIPT_PARAM_STATIC_PASCAL_STRING:
    {
        int16 nStringLen = CTheScripts::Read1ByteFromScript(m_pCurrentIP); // sign extension. max size = 127, not 255
        for (auto i = 0; i < nStringLen; i++)
            buffer[i] = CTheScripts::Read1ByteFromScript(m_pCurrentIP);

        if (nStringLen < nBufferLength)
            memset(&buffer[(uint8)nStringLen], 0, (uint8)(nBufferLength - nStringLen));
        break;
    }

    case SCRIPT_PARAM_STATIC_LONG_STRING:
        // slightly changed code: original code is a bit messy and calls Read1ByteFromScript
        // in a loop and does some additional checks to ensure that buffer can hold the data
        strncpy(buffer, (char*)m_pCurrentIP, std::min<uint8>(nBufferLength, LONG_STRING_SIZE));
        m_pCurrentIP += LONG_STRING_SIZE;
        break;

    case SCRIPT_PARAM_GLOBAL_LONG_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        strncpy(buffer, (char*)&CTheScripts::ScriptSpace[index], std::min<uint8>(nBufferLength, LONG_STRING_SIZE));
        break;
    }

    case SCRIPT_PARAM_LOCAL_LONG_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        strncpy(buffer, (char*)GetPointerToLocalVariable(index), std::min<uint8>(nBufferLength, LONG_STRING_SIZE));
        break;
    }

    default:
        break;
    }
}

// Updates comparement flag, used in conditional commands
// 0x4859D0
void CRunningScript::UpdateCompareFlag(bool state) {
    if (m_bNotFlag)
        state = !state;

    if (m_nLogicalOp == ANDOR_NONE) {
        m_bCondResult = state;
        return;
    }

    if (m_nLogicalOp >= ANDS_1 && m_nLogicalOp <= ANDS_8) {
        m_bCondResult &= state;
        if (m_nLogicalOp == ANDS_1)
            m_nLogicalOp = ANDOR_NONE;
        else
            m_nLogicalOp--;

        return;
    }

    if (m_nLogicalOp >= ORS_1 && m_nLogicalOp <= ORS_8) {
        m_bCondResult |= state;
        if (m_nLogicalOp == ORS_1)
            m_nLogicalOp = ANDOR_NONE;
        else
            m_nLogicalOp--;

        return;
    }
}

// Sets instruction pointer, used in GOTO-like commands
// 0x464DA0
void CRunningScript::UpdatePC(int32 newIP) {
    if (newIP >= 0)
        m_pCurrentIP = &CTheScripts::ScriptSpace[newIP];
    else
        m_pCurrentIP = &m_pBaseIP[-newIP];
}
static std::array<size_t, COMMAND_HIGHEST_ID> counter{};

// 0x469EB0, inlined
OpcodeResult CRunningScript::ProcessOneCommand() {
    ++CTheScripts::CommandsExecuted;

    union {
        int16 op;
        struct {
            uint16 command : 15;
            uint16 notFlag : 1;
        };
    } op = { CTheScripts::Read2BytesFromScript(m_pCurrentIP) };

    counter[op.command]++;

    m_bNotFlag = op.notFlag;

    //return std::invoke(CommandHandlerTable[(size_t)op.command / 100], this, (eScriptCommands)op.command);

    return std::invoke(s_CommandHandlerLUT[(size_t)op.command], this);
}

// 0x469F00
OpcodeResult CRunningScript::Process() {
    if (m_pSceneSkipIP && CCutsceneMgr::IsCutsceneSkipButtonBeingPressed()) {
        CHud::m_BigMessage[1][0] = 0;
        UpdatePC(reinterpret_cast<int32>(m_pSceneSkipIP));
        m_pSceneSkipIP = nullptr;
        m_nWakeTime = 0;
    }

    if (m_bUseMissionCleanup)
        DoDeathArrestCheck();

    if (m_bIsMission && CTheScripts::FailCurrentMission == 1) {
        while (m_nSP > 1) // // todo: refactor | inline(?): while (stack.size > 1) { stack.pop() }
            --m_nSP;

        if (m_nSP == 1) {
            m_nSP = 0;
            m_pCurrentIP = m_apStack[0];
        }
    }
    CTheScripts::ReinitialiseSwitchStatementData();
    if (CTimer::GetTimeInMS() >= (uint32)m_nWakeTime) {
        while (!ProcessOneCommand()); // Process commands
    }

    return OR_CONTINUE;
}

void CRunningScript::SetCommandHandler(eScriptCommands cmd, OpcodeResult(*handler)(CRunningScript*)) {
    s_CommandHandlerLUT[(size_t)cmd] = handler;
}
