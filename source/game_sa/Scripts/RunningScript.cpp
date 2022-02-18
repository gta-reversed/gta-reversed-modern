#include "StdInc.h"

#include "RunningScript.h"

int8(__thiscall** CRunningScript::CommandHandlerTable)(CRunningScript* _this, int32 commandId) = reinterpret_cast<int8(__thiscall**)(CRunningScript*, int32)>(0x8A6168);
int8(CRunningScript::* CRunningScript::reSA_CommandHandlerTable[27])(int32 commandId) = {
    &ProcessCommands0To99,
    &ProcessCommands100To199,
    &ProcessCommands200To299,
    &ProcessCommands300To399,
    &ProcessCommands400To499,
    &ProcessCommands500To599,
    &ProcessCommands600To699,
    &ProcessCommands700To799,
    &ProcessCommands800To899,
    &ProcessCommands900To999,
    &ProcessCommands1000To1099,
    &ProcessCommands1100To1199,
    &ProcessCommands1200To1299,
    &ProcessCommands1300To1399,
    &ProcessCommands1400To1499,
    &ProcessCommands1500To1599,
    &ProcessCommands1600To1699,
    &ProcessCommands1700To1799,
    &ProcessCommands1800To1899,
    &ProcessCommands1900To1999,
    &ProcessCommands2000To2099,
    &ProcessCommands2100To2199,
    &ProcessCommands2200To2299,
    &ProcessCommands2300To2399,
    &ProcessCommands2400To2499,
    &ProcessCommands2500To2599,
    &ProcessCommands2600To2699
};

void CRunningScript::InjectHooks() {
    RH_ScopedClass(CRunningScript);
    RH_ScopedCategory("Scripts");

    RH_ScopedInstall(Init, 0x4648E0);
    RH_ScopedInstall(GetCorrectPedModelIndexForEmergencyServiceType, 0x464F50);
    // RH_ScopedInstall(LocateCarCommand, 0x487A20);
    // RH_ScopedInstall(LocateObjectCommand, 0x487D10);
    // RH_ScopedInstall(PlayAnimScriptCommand, 0x470150);
    // RH_ScopedInstall(LocateCharCommand, 0x486D80);
    // RH_ScopedInstall(LocateCharCarCommand, 0x487420);
    // RH_ScopedInstall(LocateCharCharCommand, 0x4870F0);
    // RH_ScopedInstall(LocateCharObjectCommand, 0x487720);
    // RH_ScopedInstall(CarInAreaCheckCommand, 0x488EC0);
    // RH_ScopedInstall(CharInAreaCheckCommand, 0x488B50);
    // RH_ScopedInstall(ObjectInAreaCheckCommand, 0x489150);
    // RH_ScopedInstall(CharInAngledAreaCheckCommand, 0x487F60);
    // RH_ScopedInstall(FlameInAngledAreaCheckCommand, 0x488780);
    // RH_ScopedInstall(ObjectInAngledAreaCheckCommand, 0x4883F0);
    RH_ScopedInstall(CollectParameters, 0x464080);
    RH_ScopedInstall(CollectNextParameterWithoutIncreasingPC, 0x464250);
    RH_ScopedInstall(StoreParameters, 0x464370);
    RH_ScopedInstall(ReadArrayInformation, 0x463CF0);
    RH_ScopedInstall(ReadParametersForNewlyStartedScript, 0x464500);
    RH_ScopedInstall(ReadTextLabelFromScript, 0x463D50);
    RH_ScopedInstall(GetIndexOfGlobalVariable, 0x464700);
    // RH_ScopedInstall(GetPadState, 0x485B10);
    RH_ScopedInstall(GetPointerToLocalVariable, 0x463CA0);
    RH_ScopedInstall(GetPointerToLocalArrayElement, 0x463CC0);
    RH_ScopedInstall(GetPointerToScriptVariable, 0x464790);
    // RH_ScopedInstall(DoDeathArrestCheck, 0x485A50);
    // RH_ScopedInstall(SetCharCoordinates, 0x464DC0);
    // RH_ScopedInstall(GivePedScriptedTask, 0x465C20);
    RH_ScopedInstall(AddScriptToList, 0x464C00);
    RH_ScopedInstall(RemoveScriptFromList, 0x464BD0);
    // RH_ScopedInstall(ShutdownThisScript, 0x465AA0);
    RH_ScopedInstall(IsPedDead, 0x464D70);
    // RH_ScopedInstall(ThisIsAValidRandomPed, 0x489490);
    // RH_ScopedInstall(ScriptTaskPickUpObject, 0x46AF50);
    RH_ScopedInstall(UpdateCompareFlag, 0x4859D0);
    RH_ScopedInstall(UpdatePC, 0x464DA0);
    RH_ScopedInstall(ProcessOneCommand, 0x469EB0);
    RH_ScopedInstall(Process, 0x469F00);

    // RH_ScopedInstall(ProcessCommands0To99, 0x465E60);
    // RH_ScopedInstall(ProcessCommands100To199, 0x466DE0);
    // RH_ScopedInstall(ProcessCommands200To299, 0x469390);
    // RH_ScopedInstall(ProcessCommands300To399, 0x47C100);
    // RH_ScopedInstall(ProcessCommands400To499, 0x47D210);
    // RH_ScopedInstall(ProcessCommands500To599, 0x47E090);
    // RH_ScopedInstall(ProcessCommands600To699, 0x47F370);
    // RH_ScopedInstall(ProcessCommands700To799, 0x47FA30);
    // RH_ScopedInstall(ProcessCommands800To899, 0x481300);
    // RH_ScopedInstall(ProcessCommands900To999, 0x483BD0);
    // RH_ScopedInstall(ProcessCommands1000To1099, 0x489500);
    // RH_ScopedInstall(ProcessCommands1100To1199, 0x48A320);
    // RH_ScopedInstall(ProcessCommands1200To1299, 0x48B590);
    // RH_ScopedInstall(ProcessCommands1300To1399, 0x48CDD0);
    // RH_ScopedInstall(ProcessCommands1400To1499, 0x48EAA0);
    // RH_ScopedInstall(ProcessCommands1500To1599, 0x490DB0);
    // RH_ScopedInstall(ProcessCommands1600To1699, 0x493FE0);
    // RH_ScopedInstall(ProcessCommands1700To1799, 0x496E00);
    // RH_ScopedInstall(ProcessCommands1800To1899, 0x46D050);
    // RH_ScopedInstall(ProcessCommands1900To1999, 0x46B460);
    // RH_ScopedInstall(ProcessCommands2000To2099, 0x472310);
    // RH_ScopedInstall(ProcessCommands2100To2199, 0x470A90);
    // RH_ScopedInstall(ProcessCommands2200To2299, 0x474900);
    // RH_ScopedInstall(ProcessCommands2300To2399, 0x4762D0);
    // RH_ScopedInstall(ProcessCommands2400To2499, 0x478000);
    // RH_ScopedInstall(ProcessCommands2500To2599, 0x47A760);
    // RH_ScopedInstall(ProcessCommands2600To2699, 0x479DA0);
}

// 0x4648E0
void CRunningScript::Init() {
    strcpy(m_szName, "noname");
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
    m_externalType = -1;
    memset(m_aLocalVars, 0, sizeof(m_aLocalVars));
    m_nLogicalOp = 0;
    m_bNotFlag = false;
    m_bWastedOrBusted = false;
    m_pSceneSkipIP = nullptr;
    m_bIsMission = false;
    m_bWastedBustedCheck = true;
}

// Adds script to list
// 0x464C00
void CRunningScript::AddScriptToList(CRunningScript** queueList) {
    m_pNext = *queueList;
    m_pPrev = nullptr;
    if (*queueList)
        (*queueList)->m_pPrev = this;
    *queueList = this;
}

// 0x463CA0
tScriptParam* CRunningScript::GetPointerToLocalVariable(int32 varIndex) {
    if (m_bIsMission)
        return (tScriptParam*)&CTheScripts::LocalVariablesForCurrentMission[varIndex];
    else
        return (tScriptParam*)&m_aLocalVars[varIndex];
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
    if (m_externalType == 5 || m_externalType == 2 || !m_externalType || m_externalType == 3) {
        int32* pLocalVariable = reinterpret_cast<int32*>(GetPointerToLocalVariable(0));
        otherPed = GetPedPool()->GetAtRef(*pLocalVariable);
    }
    if (ped->bHasAScriptBrain && otherPed != ped) {
        delete task;
    } else if (otherPed && m_externalType == 5) {
        if (CScriptedBrainTaskStore::SetTask(ped, task)) {
            const int32 slot = CPedScriptedTaskRecord::GetVacantSlot();
            CPedScriptedTaskRecord::ms_scriptedTasks[slot].SetAsAttractorScriptTask(ped, opcode, task);
        }
    } else if (!pedGroup || ped->IsPlayer()) {
        CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, task, false);
        CEventScriptCommand* event = static_cast<CEventScriptCommand*>(ped->GetEventGroup().Add(&eventScriptCommand, false));
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

// 0x487A20
void CRunningScript::LocateCarCommand(int32 commandId) {
    plugin::CallMethod<0x487A20, CRunningScript*, int32>(this, commandId);
}

// 0x487420
void CRunningScript::LocateCharCarCommand(int32 commandId) {
    plugin::CallMethod<0x487420, CRunningScript*, int32>(this, commandId);
}

// 0x4870F0
void CRunningScript::LocateCharCharCommand(int32 commandId) {
    plugin::CallMethod<0x4870F0, CRunningScript*, int32>(this, commandId);
}

// 0x486D80
void CRunningScript::LocateCharCommand(int32 commandId) {
    plugin::CallMethod<0x486D80, CRunningScript*, int32>(this, commandId);
}

// 0x487720
void CRunningScript::LocateCharObjectCommand(int32 commandId) {
    plugin::CallMethod<0x487720, CRunningScript*, int32>(this, commandId);
}

// 0x487D10
void CRunningScript::LocateObjectCommand(int32 commandId) {
    plugin::CallMethod<0x487D10, CRunningScript*, int32>(this, commandId);
}

// 0x4883F0
void CRunningScript::ObjectInAngledAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x4883F0, CRunningScript*, int32>(this, commandId);
}

// 0x489150
void CRunningScript::ObjectInAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x489150, CRunningScript*, int32>(this, commandId);
}

// 0x470150
void CRunningScript::PlayAnimScriptCommand(int32 commandId) {
    plugin::CallMethod<0x470150, CRunningScript*, int32>(this, commandId);
}

// 0x464D70
bool CRunningScript::IsPedDead(CPed* ped) {
    ePedState pedState = ped->m_nPedState;
    return pedState == PEDSTATE_DEAD || pedState == PEDSTATE_DIE || pedState == PEDSTATE_DIE_BY_STEALTH;
}

// 0x488EC0
void CRunningScript::CarInAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x488EC0, CRunningScript*, int32>(this, commandId);
}

// 0x487F60
void CRunningScript::CharInAngledAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x487F60, CRunningScript*, int32>(this, commandId);
}

// 0x488B50
void CRunningScript::CharInAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x488B50, CRunningScript*, int32>(this, commandId);
}

// Collects parameter and returns it.
// 0x464250
tScriptParam CRunningScript::CollectNextParameterWithoutIncreasingPC() {
    uint16 arrVarOffset;
    int32 arrElemIdx;
    uint8* pIp = m_pCurrentIP;
    tScriptParam result = {.iParam = -1};

    switch (CTheScripts::Read1ByteFromScript(m_pCurrentIP))
    {
    case SCRIPT_PARAM_STATIC_INT_32BITS:
        result.iParam = CTheScripts::Read4BytesFromScript(m_pCurrentIP);
        break;
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        result.iParam = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[index]);
        break;
    }
    case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        result = *GetPointerToLocalVariable(index);
        break;
    }
    case SCRIPT_PARAM_STATIC_INT_8BITS:
        result.iParam = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
        break;
    case SCRIPT_PARAM_STATIC_INT_16BITS:
        result.iParam = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        break;
    case SCRIPT_PARAM_STATIC_FLOAT:
        result.fParam = CTheScripts::ReadFloatFromScript(m_pCurrentIP);
        break;
    case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
        ReadArrayInformation(0, &arrVarOffset, &arrElemIdx);
        result.iParam = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrVarOffset + 4 * arrElemIdx]);
        break;
    case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
        ReadArrayInformation(0, &arrVarOffset, &arrElemIdx);
        result = *GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 1);
        break;
    }

    m_pCurrentIP = pIp;
    return result;
}

// 0x464080
void CRunningScript::CollectParameters(int16 count) {
    uint16 arrVarOffset;
    int32 arrElemIdx;

    for (int i = 0; i < count; i++)
    {
        switch (CTheScripts::Read1ByteFromScript(m_pCurrentIP))
        {
        case SCRIPT_PARAM_STATIC_INT_32BITS:
            CTheScripts::ScriptParams[i].iParam = CTheScripts::Read4BytesFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            CTheScripts::ScriptParams[i].iParam = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[index]);
            break;
        }
        case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            CTheScripts::ScriptParams[i] = *GetPointerToLocalVariable(index);
            break;
        }
        case SCRIPT_PARAM_STATIC_INT_8BITS:
            CTheScripts::ScriptParams[i].iParam = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_STATIC_INT_16BITS:
            CTheScripts::ScriptParams[i].iParam = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_STATIC_FLOAT:
            CTheScripts::ScriptParams[i].fParam = CTheScripts::ReadFloatFromScript(m_pCurrentIP);
            break;
        case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
            ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
            CTheScripts::ScriptParams[i].iParam = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrVarOffset + 4 * arrElemIdx]);
            break;
        case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
            ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
            CTheScripts::ScriptParams[i] = *GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 1);
            break;
        }
    }
}

// 0x485A50
void CRunningScript::DoDeathArrestCheck() {
    plugin::CallMethod<0x485A50, CRunningScript*>(this);
}

// 0x488780
void CRunningScript::FlameInAngledAreaCheckCommand(int32 commandId) {
    plugin::CallMethod<0x488780, CRunningScript*, int32>(this, commandId);
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

// Returns offset of global variable
// 0x464700
uint16 CRunningScript::GetIndexOfGlobalVariable() {
    uint16 arrVarOffset;
    int32 arrElemIdx;

    switch (CTheScripts::Read1ByteFromScript(m_pCurrentIP))
    {
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        return CTheScripts::Read2BytesFromScript(m_pCurrentIP);
    case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
        ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
        return arrVarOffset + 4 * arrElemIdx;
    default:
        // ???
        return (uint16)(uint32)this;
    }
}

// Returns state of pad button
// 0x485B10
int16 CRunningScript::GetPadState(uint16 playerIndex, eButtonId buttonId) {
    return plugin::CallMethodAndReturn<int16, 0x485B10, CRunningScript*, uint16, eButtonId>(this, playerIndex, buttonId);
}

// Returns pointer to local variable pointed by offset and array index as well as multiplier.
// 0x463CC0
tScriptParam* CRunningScript::GetPointerToLocalArrayElement(int32 arrVarOffset, uint16 arrElemIdx, uint8 arrElemSize) {
    int32 index = arrVarOffset + arrElemSize * arrElemIdx;
    if (m_bIsMission)
        return (tScriptParam*)&CTheScripts::LocalVariablesForCurrentMission[index];
    else
        return (tScriptParam*)&m_aLocalVars[index];
}

// Returns pointer to script variable of any type.
// 0x464790
tScriptParam* CRunningScript::GetPointerToScriptVariable(uint8 variableType) {
    uint8 arrElemSize;
    uint16 arrVarOffset;
    int32 arrElemIdx;

    variableType = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
    switch (variableType)
    {
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_VARIABLE:
    case SCRIPT_PARAM_GLOBAL_LONG_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        return (tScriptParam*)&CTheScripts::LocalVariablesForCurrentMission[index];
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
        ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
        if (variableType == SCRIPT_PARAM_GLOBAL_LONG_STRING_ARRAY)
            return (tScriptParam*)&CTheScripts::ScriptSpace[16 * arrElemIdx + arrVarOffset];
        else if (variableType == SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY)
            return (tScriptParam*)&CTheScripts::ScriptSpace[8 * arrElemIdx + arrVarOffset];
        else
            return (tScriptParam*)&CTheScripts::ScriptSpace[4 * arrElemIdx + arrVarOffset];

    case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
    case SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY:
    case SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY:
        ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
        if (variableType == SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY)
            arrElemSize = 4;
        else if (variableType == SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY)
            arrElemSize = 2;
        else
            arrElemSize = 1;
        return GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, arrElemSize);

    default:
        return nullptr;
    }
}

// Terminates a script
// 0x465AA0
void CRunningScript::ShutdownThisScript() {
    plugin::CallMethod<0x465AA0, CRunningScript*>(this);
}

// Reads array var base offset and element index from index variable.
// 0x463CF0
void CRunningScript::ReadArrayInformation(int32 updateIp, uint16* outArrVarOffset, int32* outArrElemIdx) {
    uint8* pIp = m_pCurrentIP;

    *outArrVarOffset = CTheScripts::Read2BytesFromScript(pIp);
    uint16 arrayIndexVar = CTheScripts::Read2BytesFromScript(pIp);
    bool isGlobalIndexVar = CTheScripts::Read2BytesFromScript(pIp) < 0; // high bit set

    if (isGlobalIndexVar)
        *outArrElemIdx = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrayIndexVar]);
    else
        *outArrElemIdx = GetPointerToLocalVariable(arrayIndexVar)->iParam;

    if (updateIp)
        m_pCurrentIP = pIp;
}

// Collects parameters and puts them to local variables of new script
// 0x464500
void CRunningScript::ReadParametersForNewlyStartedScript(CRunningScript* newScript) {
    uint16 arrVarOffset;
    int32 arrElemIdx;
    int8 type = CTheScripts::Read1ByteFromScript(m_pCurrentIP);

    for (int i = 0; type != SCRIPT_PARAM_END_OF_ARGUMENTS; type = CTheScripts::Read1ByteFromScript(m_pCurrentIP), i++)
    {
        switch (type)
        {
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
            ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
            newScript->m_aLocalVars[i].iParam = *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrVarOffset + 4 * arrElemIdx]);
            break;
        case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
            ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
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
    int32 arrElemIdx;

    int8 type = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
    switch (type)
    {
    case SCRIPT_PARAM_STATIC_SHORT_STRING:
        for (int i = 0; i < 8; ++i)
            buffer[i] = CTheScripts::Read1ByteFromScript(m_pCurrentIP);
        break;

    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        strncpy(buffer, (char*)&CTheScripts::ScriptSpace[index], 8);
        break;
    }

    case SCRIPT_PARAM_LOCAL_SHORT_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        strncpy(buffer, (char*)GetPointerToLocalVariable(index), 8);
        break;
    }

    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY:
    case SCRIPT_PARAM_GLOBAL_LONG_STRING_ARRAY:
        ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
        if (type == SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY)
            strncpy(buffer, (char*)&CTheScripts::ScriptSpace[8 * arrElemIdx + arrVarOffset], 8);
        else
            strncpy(buffer, (char*)&CTheScripts::ScriptSpace[16 * arrElemIdx + arrVarOffset], std::min<uint8>(nBufferLength, 16));
        break;

    case SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY:
    case SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY:
        ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
        if (type == SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY)
            strncpy(buffer, (char*)GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 2), 8);
        else
            strncpy(buffer, (char*)GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 4), std::min<uint8>(nBufferLength, 16));
        break;

    case SCRIPT_PARAM_STATIC_PASCAL_STRING:
    {
        int16 nStringLen = CTheScripts::Read1ByteFromScript(m_pCurrentIP); // sign extension. max size = 127, not 255
        for (uint8 i = 0; i < nStringLen; i++)
            buffer[i] = CTheScripts::Read1ByteFromScript(m_pCurrentIP);

        if (nStringLen < nBufferLength)
            memset(&buffer[(uint8)nStringLen], 0, (uint8)(nBufferLength - nStringLen));
        break;
    }

    case SCRIPT_PARAM_STATIC_LONG_STRING:
        // slightly changed code: original code is a bit messy and calls Read1ByteFromScript
        // in a loop and does some additional checks to ensure that buffer can hold the data
        strncpy(buffer, (char*)m_pCurrentIP, std::min<uint8>(nBufferLength, 16));
        m_pCurrentIP += 16;
        break;

    case SCRIPT_PARAM_GLOBAL_LONG_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        strncpy(buffer, (char*)&CTheScripts::ScriptSpace[index], std::min<uint8>(nBufferLength, 16));
        break;
    }

    case SCRIPT_PARAM_LOCAL_LONG_STRING_VARIABLE:
    {
        uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
        strncpy(buffer, (char*)GetPointerToLocalVariable(index), std::min<uint8>(nBufferLength, 16));
        break;
    }

    default:
        break;
    }
}

// Removes script from list
// 0x464BD0
void CRunningScript::RemoveScriptFromList(CRunningScript** queueList) {
    if (m_pPrev)
        m_pPrev->m_pNext = m_pNext;
    else
        *queueList = m_pNext;

    if (m_pNext)
        m_pNext->m_pPrev = m_pPrev;
}

// 0x46AF50
void CRunningScript::ScriptTaskPickUpObject(int32 commandId) {
    plugin::CallMethod<0x46AF50, CRunningScript*, int32>(this, commandId);
}

// 0x464DC0
void CRunningScript::SetCharCoordinates(CPed* ped, float x, float y, float z, bool bWarpGang, bool bOffset) {
    plugin::CallMethod<0x464DC0, CRunningScript*, CPed*, float, float, float, bool, bool>(this, ped, x, y, z, bWarpGang, bOffset);
}

// 0x464370
void CRunningScript::StoreParameters(int16 count) {
    uint16 arrVarOffset;
    int32 arrElemIdx;

    for (int i = 0; i < count; i++)
    {
        switch (CTheScripts::Read1ByteFromScript(m_pCurrentIP))
        {
        case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[index]) = CTheScripts::ScriptParams[i].iParam;
            break;
        }
        case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
        {
            uint16 index = CTheScripts::Read2BytesFromScript(m_pCurrentIP);
            *GetPointerToLocalVariable(index) = CTheScripts::ScriptParams[i];
            break;
        }
        case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY:
            ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
            *reinterpret_cast<int32*>(&CTheScripts::ScriptSpace[arrVarOffset + 4 * arrElemIdx]) = CTheScripts::ScriptParams[i].iParam;
            break;
        case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY:
            ReadArrayInformation(1, &arrVarOffset, &arrElemIdx);
            *GetPointerToLocalArrayElement(arrVarOffset, arrElemIdx, 1) = CTheScripts::ScriptParams[i];
            break;
        }
    }
}

// 0x489490
bool CRunningScript::ThisIsAValidRandomPed(ePedType pedType, bool civilian, bool gang, bool criminal) {
    return plugin::CallMethodAndReturn<bool, 0x489490, CRunningScript*, ePedType, bool, bool, bool>(this, pedType, civilian, gang, criminal);
}

// Updates comparement flag, used in conditional commands
// 0x4859D0
void CRunningScript::UpdateCompareFlag(bool state) {
    if (m_bNotFlag)
        state = !state;

    if (m_nLogicalOp == ANDOR_NONE)
    {
        m_bCondResult = state;
        return;
    }

    if (m_nLogicalOp >= ANDS_1 && m_nLogicalOp <= ANDS_8)
    {
        m_bCondResult &= state;
        if (m_nLogicalOp == ANDS_1)
            m_nLogicalOp = ANDOR_NONE;
        else
            m_nLogicalOp--;

        return;
    }

    if (m_nLogicalOp >= ORS_1 && m_nLogicalOp <= ORS_8)
    {
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

// unused
// 0x469EB0
int8 CRunningScript::ProcessOneCommand() {
    ++CTheScripts::CommandsExecuted;

    int32 command = CTheScripts::Read2BytesFromScript(m_pCurrentIP);

    m_bNotFlag = (command & 0x8000) != 0;
    command &= 0x7FFF;

    // CUSTOM CODE: First we try to call our (reversed) implementation for the current command
    int8 ret = (this->*reSA_CommandHandlerTable[command / 100])(command);
    if (ret == COMMAND_NOT_IMPLEMENTED_YET)
    {
        // Not implemented -> invoke the original opcode
        ret = CommandHandlerTable[command / 100](this, command);
    }
    // TODO: Inspect whether CommandHandlerTable is a design decision or it's a modernish MSVC&GCC optimisation

    return ret;
}

// 0x469F00
int8 CRunningScript::Process() {
    if (m_pSceneSkipIP && CCutsceneMgr::IsCutsceneSkipButtonBeingPressed())
    {
        CHud::m_BigMessage[1][0] = 0;
        UpdatePC(*(int32*)&m_pSceneSkipIP);
        m_pSceneSkipIP = 0;
        m_nWakeTime = 0;
    }
    if (m_bUseMissionCleanup)
        DoDeathArrestCheck();

    if (m_bIsMission && CTheScripts::FailCurrentMission == 1)
    {
        while (m_nSP > 1) // inline(?): while (stack.size > 1) { stack.pop() }
            --m_nSP;

        if (m_nSP == 1)
        {
            m_nSP = 0;
            m_pCurrentIP = m_apStack[0];
        }
    }
    CTheScripts::ReinitialiseSwitchStatementData();
    if (CTimer::m_snTimeInMilliseconds >= m_nWakeTime) // m_nWakeTime might be unsigned, while m_snTimeInMillis is 100% SIGNED
    {
        while (!ProcessOneCommand())
            ;
    }

    return 0;
}

// 0x465E60
int8 CRunningScript::ProcessCommands0To99(int32 commandId) {
    switch (commandId) {
    case COMMAND_NOP: // 0x000
        break;
    case COMMAND_WAIT: // 0x001
        // CollectParameters(1);
        break;
    case COMMAND_GOTO: // 0x002
        break;
    case COMMAND_SHAKE_CAM: // 0x003
        break;
    case COMMAND_SET_VAR_INT: // 0x004
        break;
    case COMMAND_SET_VAR_FLOAT: // 0x005
        break;
    case COMMAND_SET_LVAR_INT: // 0x006
        break;
    case COMMAND_SET_LVAR_FLOAT: // 0x007
        break;
    case COMMAND_ADD_VAL_TO_INT_VAR: // 0x008
        break;
    case COMMAND_ADD_VAL_TO_FLOAT_VAR: // 0x009
        break;
    case COMMAND_ADD_VAL_TO_INT_LVAR: // 0x00A
        break;
    case COMMAND_ADD_VAL_TO_FLOAT_LVAR: // 0x00B
        break;
    case COMMAND_SUB_VAL_FROM_INT_VAR: // 0x00C
        break;
    case COMMAND_SUB_VAL_FROM_FLOAT_VAR: // 0x00D
        break;
    case COMMAND_SUB_VAL_FROM_INT_LVAR: // 0x00E
        break;
    case COMMAND_SUB_VAL_FROM_FLOAT_LVAR: // 0x00F
        break;
    case COMMAND_MULT_INT_VAR_BY_VAL: // 0x010
        break;
    case COMMAND_MULT_FLOAT_VAR_BY_VAL: // 0x011
        break;
    case COMMAND_MULT_INT_LVAR_BY_VAL: // 0x012
        break;
    case COMMAND_MULT_FLOAT_LVAR_BY_VAL: // 0x013
        break;
    case COMMAND_DIV_INT_VAR_BY_VAL: // 0x014
        break;
    case COMMAND_DIV_FLOAT_VAR_BY_VAL: // 0x015
        break;
    case COMMAND_DIV_INT_LVAR_BY_VAL: // 0x016
        break;
    case COMMAND_DIV_FLOAT_LVAR_BY_VAL: // 0x017
        break;
    case COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER: // 0x018
        break;
    case COMMAND_IS_INT_LVAR_GREATER_THAN_NUMBER: // 0x019
        break;
    case COMMAND_IS_NUMBER_GREATER_THAN_INT_VAR: // 0x01A
        break;
    case COMMAND_IS_NUMBER_GREATER_THAN_INT_LVAR: // 0x01B
        break;
    case COMMAND_IS_INT_VAR_GREATER_THAN_INT_VAR: // 0x01C
        break;
    case COMMAND_IS_INT_LVAR_GREATER_THAN_INT_LVAR: // 0x01D
        break;
    case COMMAND_IS_INT_VAR_GREATER_THAN_INT_LVAR: // 0x01E
        break;
    case COMMAND_IS_INT_LVAR_GREATER_THAN_INT_VAR: // 0x01F
        break;
    case COMMAND_IS_FLOAT_VAR_GREATER_THAN_NUMBER: // 0x020
        break;
    case COMMAND_IS_FLOAT_LVAR_GREATER_THAN_NUMBER: // 0x021
        break;
    case COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_VAR: // 0x022
        break;
    case COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_LVAR: // 0x023
        break;
    case COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_VAR: // 0x024
        break;
    case COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_LVAR: // 0x025
        break;
    case COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_LVAR: // 0x026
        break;
    case COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_VAR: // 0x027
        break;
    case COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_NUMBER: // 0x028
        break;
    case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_NUMBER: // 0x029
        break;
    case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_VAR: // 0x02A
        break;
    case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_LVAR: // 0x02B
        break;
    case COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_VAR: // 0x02C
        break;
    case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_LVAR: // 0x02D
        break;
    case COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_LVAR: // 0x02E
        break;
    case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_VAR: // 0x02F
        break;
    case COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_NUMBER: // 0x030
        break;
    case COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_NUMBER: // 0x031
        break;
    case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_VAR: // 0x032
        break;
    case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_LVAR: // 0x033
        break;
    case COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_VAR: // 0x034
        break;
    case COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR: // 0x035
        break;
    case COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR: // 0x036
        break;
    case COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_VAR: // 0x037
        break;
    case COMMAND_IS_INT_VAR_EQUAL_TO_NUMBER: // 0x038
        break;
    case COMMAND_IS_INT_LVAR_EQUAL_TO_NUMBER: // 0x039
        break;
    case COMMAND_IS_INT_VAR_EQUAL_TO_INT_VAR: // 0x03A
        break;
    case COMMAND_IS_INT_LVAR_EQUAL_TO_INT_LVAR: // 0x03B
        break;
    case COMMAND_IS_INT_VAR_EQUAL_TO_INT_LVAR: // 0x03C
        break;
    case COMMAND_IS_INT_VAR_NOT_EQUAL_TO_NUMBER: // 0x03D
        break;
    case COMMAND_IS_INT_LVAR_NOT_EQUAL_TO_NUMBER: // 0x03E
        break;
    case COMMAND_IS_INT_VAR_NOT_EQUAL_TO_INT_VAR: // 0x03F
        break;
    case COMMAND_IS_INT_LVAR_NOT_EQUAL_TO_INT_LVAR: // 0x040
        break;
    case COMMAND_IS_INT_VAR_NOT_EQUAL_TO_INT_LVAR: // 0x041
        break;
    case COMMAND_IS_FLOAT_VAR_EQUAL_TO_NUMBER: // 0x042
        break;
    case COMMAND_IS_FLOAT_LVAR_EQUAL_TO_NUMBER: // 0x043
        break;
    case COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_VAR: // 0x044
        break;
    case COMMAND_IS_FLOAT_LVAR_EQUAL_TO_FLOAT_LVAR: // 0x045
        break;
    case COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_LVAR: // 0x046
        break;
    case COMMAND_IS_FLOAT_VAR_NOT_EQUAL_TO_NUMBER: // 0x047
        break;
    case COMMAND_IS_FLOAT_LVAR_NOT_EQUAL_TO_NUMBER: // 0x048
        break;
    case COMMAND_IS_FLOAT_VAR_NOT_EQUAL_TO_FLOAT_VAR: // 0x049
        break;
    case COMMAND_IS_FLOAT_LVAR_NOT_EQUAL_TO_FLOAT_LVAR: // 0x04A
        break;
    case COMMAND_IS_FLOAT_VAR_NOT_EQUAL_TO_FLOAT_LVAR: // 0x04B
        break;
    case COMMAND_GOTO_IF_TRUE: // 0x04C
        break;
    case COMMAND_GOTO_IF_FALSE: // 0x04D
        break;
    case COMMAND_TERMINATE_THIS_SCRIPT: // 0x04E
        break;
    case COMMAND_START_NEW_SCRIPT: // 0x04F
    {
        CollectParameters(1);

        int32 offset = CTheScripts::ScriptParams[0].iParam; // Btw ScriptParams should be in the global scope(?)
        if (offset < 0) // This doesn't make sense
            offset = commandId; // For Mobile, offset is set to 0 here. WD fix perhaps?

        CRunningScript* pNew = CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[offset]);
        ReadParametersForNewlyStartedScript(pNew);
        return 0;
    }
    case COMMAND_GOSUB: // 0x050
        break;
    case COMMAND_RETURN: // 0x051
        break;
    case COMMAND_LINE: // 0x052
        break;
    case COMMAND_CREATE_PLAYER: // 0x053
        break;
    case COMMAND_GET_PLAYER_COORDINATES: // 0x054
        break;
    case COMMAND_SET_PLAYER_COORDINATES: // 0x055
        break;
    case COMMAND_IS_PLAYER_IN_AREA_2D: // 0x056
        break;
    case COMMAND_IS_PLAYER_IN_AREA_3D: // 0x057
        break;
    case COMMAND_ADD_INT_VAR_TO_INT_VAR: // 0x058
        break;
    case COMMAND_ADD_FLOAT_VAR_TO_FLOAT_VAR: // 0x059
        break;
    case COMMAND_ADD_INT_LVAR_TO_INT_LVAR: // 0x05A
        break;
    case COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_LVAR: // 0x05B
        break;
    case COMMAND_ADD_INT_VAR_TO_INT_LVAR: // 0x05C
        break;
    case COMMAND_ADD_FLOAT_VAR_TO_FLOAT_LVAR: // 0x05D
        break;
    case COMMAND_ADD_INT_LVAR_TO_INT_VAR: // 0x05E
        break;
    case COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_VAR: // 0x05F
        break;
    case COMMAND_SUB_INT_VAR_FROM_INT_VAR: // 0x060
        break;
    case COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_VAR: // 0x061
        break;
    case COMMAND_SUB_INT_LVAR_FROM_INT_LVAR: // 0x062
        break;
    case COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_LVAR: // 0x063
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x466DE0
int8 CRunningScript::ProcessCommands100To199(int32 commandId) {
    switch (commandId) {
    case COMMAND_SUB_INT_VAR_FROM_INT_LVAR: // 0x064
        break;
    case COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_LVAR: // 0x065
        break;
    case COMMAND_SUB_INT_LVAR_FROM_INT_VAR: // 0x066
        break;
    case COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_VAR: // 0x067
        break;
    case COMMAND_MULT_INT_VAR_BY_INT_VAR: // 0x068
        break;
    case COMMAND_MULT_FLOAT_VAR_BY_FLOAT_VAR: // 0x069
        break;
    case COMMAND_MULT_INT_LVAR_BY_INT_LVAR: // 0x06A
        break;
    case COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_LVAR: // 0x06B
        break;
    case COMMAND_MULT_INT_VAR_BY_INT_LVAR: // 0x06C
        break;
    case COMMAND_MULT_FLOAT_VAR_BY_FLOAT_LVAR: // 0x06D
        break;
    case COMMAND_MULT_INT_LVAR_BY_INT_VAR: // 0x06E
        break;
    case COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_VAR: // 0x06F
        break;
    case COMMAND_DIV_INT_VAR_BY_INT_VAR: // 0x070
        break;
    case COMMAND_DIV_FLOAT_VAR_BY_FLOAT_VAR: // 0x071
        break;
    case COMMAND_DIV_INT_LVAR_BY_INT_LVAR: // 0x072
        break;
    case COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_LVAR: // 0x073
        break;
    case COMMAND_DIV_INT_VAR_BY_INT_LVAR: // 0x074
        break;
    case COMMAND_DIV_FLOAT_VAR_BY_FLOAT_LVAR: // 0x075
        break;
    case COMMAND_DIV_INT_LVAR_BY_INT_VAR: // 0x076
        break;
    case COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_VAR: // 0x077
        break;
    case COMMAND_ADD_TIMED_VAL_TO_FLOAT_VAR: // 0x078
        break;
    case COMMAND_ADD_TIMED_VAL_TO_FLOAT_LVAR: // 0x079
        break;
    case COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_VAR: // 0x07A
        break;
    case COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_LVAR: // 0x07B
        break;
    case COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_LVAR: // 0x07C
        break;
    case COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_VAR: // 0x07D
        break;
    case COMMAND_SUB_TIMED_VAL_FROM_FLOAT_VAR: // 0x07E
        break;
    case COMMAND_SUB_TIMED_VAL_FROM_FLOAT_LVAR: // 0x07F
        break;
    case COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_VAR: // 0x080
        break;
    case COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_LVAR: // 0x081
        break;
    case COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_LVAR: // 0x082
        break;
    case COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_VAR: // 0x083
        break;
    case COMMAND_SET_VAR_INT_TO_VAR_INT: // 0x084
        break;
    case COMMAND_SET_LVAR_INT_TO_LVAR_INT: // 0x085
        break;
    case COMMAND_SET_VAR_FLOAT_TO_VAR_FLOAT: // 0x086
        break;
    case COMMAND_SET_LVAR_FLOAT_TO_LVAR_FLOAT: // 0x087
        break;
    case COMMAND_SET_VAR_FLOAT_TO_LVAR_FLOAT: // 0x088
        break;
    case COMMAND_SET_LVAR_FLOAT_TO_VAR_FLOAT: // 0x089
        break;
    case COMMAND_SET_VAR_INT_TO_LVAR_INT: // 0x08A
        break;
    case COMMAND_SET_LVAR_INT_TO_VAR_INT: // 0x08B
        break;
    case COMMAND_CSET_VAR_INT_TO_VAR_FLOAT: // 0x08C
        break;
    case COMMAND_CSET_VAR_FLOAT_TO_VAR_INT: // 0x08D
        break;
    case COMMAND_CSET_LVAR_INT_TO_VAR_FLOAT: // 0x08E
        break;
    case COMMAND_CSET_LVAR_FLOAT_TO_VAR_INT: // 0x08F
        break;
    case COMMAND_CSET_VAR_INT_TO_LVAR_FLOAT: // 0x090
        break;
    case COMMAND_CSET_VAR_FLOAT_TO_LVAR_INT: // 0x091
        break;
    case COMMAND_CSET_LVAR_INT_TO_LVAR_FLOAT: // 0x092
        break;
    case COMMAND_CSET_LVAR_FLOAT_TO_LVAR_INT: // 0x093
        break;
    case COMMAND_ABS_VAR_INT: // 0x094
        break;
    case COMMAND_ABS_LVAR_INT: // 0x095
        break;
    case COMMAND_ABS_VAR_FLOAT: // 0x096
        break;
    case COMMAND_ABS_LVAR_FLOAT: // 0x097
        break;
    case COMMAND_GENERATE_RANDOM_FLOAT: // 0x098
        break;
    case COMMAND_GENERATE_RANDOM_INT: // 0x099
        break;
    case COMMAND_CREATE_CHAR: // 0x09A
        break;
    case COMMAND_DELETE_CHAR: // 0x09B
        break;
    case COMMAND_CHAR_WANDER_DIR: // 0x09C
        break;
    case COMMAND_CHAR_WANDER_RANGE: // 0x09D
        break;
    case COMMAND_CHAR_FOLLOW_PATH: // 0x09E
        break;
    case COMMAND_CHAR_SET_IDLE: // 0x09F
        break;
    case COMMAND_GET_CHAR_COORDINATES: // 0x0A0
        break;
    case COMMAND_SET_CHAR_COORDINATES: // 0x0A1
        break;
    case COMMAND_IS_CHAR_STILL_ALIVE: // 0x0A2
        break;
    case COMMAND_IS_CHAR_IN_AREA_2D: // 0x0A3
        break;
    case COMMAND_IS_CHAR_IN_AREA_3D: // 0x0A4
        break;
    case COMMAND_CREATE_CAR: // 0x0A5
        break;
    case COMMAND_DELETE_CAR: // 0x0A6
        break;
    case COMMAND_CAR_GOTO_COORDINATES: // 0x0A7
        break;
    case COMMAND_CAR_WANDER_RANDOMLY: // 0x0A8
        break;
    case COMMAND_CAR_SET_IDLE: // 0x0A9
        break;
    case COMMAND_GET_CAR_COORDINATES: // 0x0AA
        break;
    case COMMAND_SET_CAR_COORDINATES: // 0x0AB
        break;
    case COMMAND_IS_CAR_STILL_ALIVE: // 0x0AC
        break;
    case COMMAND_SET_CAR_CRUISE_SPEED: // 0x0AD
        break;
    case COMMAND_SET_CAR_DRIVING_STYLE: // 0x0AE
        break;
    case COMMAND_SET_CAR_MISSION: // 0x0AF
        break;
    case COMMAND_IS_CAR_IN_AREA_2D: // 0x0B0
        break;
    case COMMAND_IS_CAR_IN_AREA_3D: // 0x0B1
        break;
    case COMMAND_SPECIAL_0: // 0x0B2
        break;
    case COMMAND_SPECIAL_1: // 0x0B3
        break;
    case COMMAND_SPECIAL_2: // 0x0B4
        break;
    case COMMAND_SPECIAL_3: // 0x0B5
        break;
    case COMMAND_SPECIAL_4: // 0x0B6
        break;
    case COMMAND_SPECIAL_5: // 0x0B7
        break;
    case COMMAND_SPECIAL_6: // 0x0B8
        break;
    case COMMAND_SPECIAL_7: // 0x0B9
        break;
    case COMMAND_PRINT_BIG: // 0x0BA
        break;
    case COMMAND_PRINT: // 0x0BB
        break;
    case COMMAND_PRINT_NOW: // 0x0BC
        break;
    case COMMAND_PRINT_SOON: // 0x0BD
        break;
    case COMMAND_CLEAR_PRINTS: // 0x0BE
        break;
    case COMMAND_GET_TIME_OF_DAY: // 0x0BF
        break;
    case COMMAND_SET_TIME_OF_DAY: // 0x0C0
        break;
    case COMMAND_GET_MINUTES_TO_TIME_OF_DAY: // 0x0C1
        break;
    case COMMAND_IS_POINT_ON_SCREEN: // 0x0C2
        break;
    case COMMAND_DEBUG_ON: // 0x0C3
        break;
    case COMMAND_DEBUG_OFF: // 0x0C4
        break;
    case COMMAND_RETURN_TRUE: // 0x0C5
        break;
    case COMMAND_RETURN_FALSE: // 0x0C6
        break;
    case COMMAND_VAR_INT: // 0x0C7
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x469390
int8 CRunningScript::ProcessCommands200To299(int32 commandId) {
    switch (commandId) {
    case COMMAND_VAR_FLOAT: // 0x0C8
        break;
    case COMMAND_LVAR_INT: // 0x0C9
        break;
    case COMMAND_LVAR_FLOAT: // 0x0CA
        break;
    case COMMAND_START_SCOPE: // 0x0CB
        break;
    case COMMAND_END_SCOPE: // 0x0CC
        break;
    case COMMAND_REPEAT: // 0x0CD
        break;
    case COMMAND_ENDREPEAT: // 0x0CE
        break;
    case COMMAND_IF: // 0x0CF
        break;
    case COMMAND_IFNOT: // 0x0D0
        break;
    case COMMAND_ELSE: // 0x0D1
        break;
    case COMMAND_ENDIF: // 0x0D2
        break;
    case COMMAND_WHILE: // 0x0D3
        break;
    case COMMAND_WHILENOT: // 0x0D4
        break;
    case COMMAND_ENDWHILE: // 0x0D5
        break;
    case COMMAND_ANDOR: // 0x0D6
        break;
    case COMMAND_LAUNCH_MISSION: // 0x0D7
    {
        CollectParameters(1);
        auto* pNew = CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[CTheScripts::ScriptParams[0].iParam]);
        return 0;
    }
    case COMMAND_MISSION_HAS_FINISHED: // 0x0D8
        break;
    case COMMAND_STORE_CAR_CHAR_IS_IN: // 0x0D9
        break;
    case COMMAND_STORE_CAR_PLAYER_IS_IN: // 0x0DA
        break;
    case COMMAND_IS_CHAR_IN_CAR: // 0x0DB
        break;
    case COMMAND_IS_PLAYER_IN_CAR: // 0x0DC
        break;
    case COMMAND_IS_CHAR_IN_MODEL: // 0x0DD
        break;
    case COMMAND_IS_PLAYER_IN_MODEL: // 0x0DE
        break;
    case COMMAND_IS_CHAR_IN_ANY_CAR: // 0x0DF
        break;
    case COMMAND_IS_PLAYER_IN_ANY_CAR: // 0x0E0
        break;
    case COMMAND_IS_BUTTON_PRESSED: // 0x0E1
        break;
    case COMMAND_GET_PAD_STATE: // 0x0E2
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_2D: // 0x0E3
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_2D: // 0x0E4
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_2D: // 0x0E5
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_ANY_MEANS_2D: // 0x0E6
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_ON_FOOT_2D: // 0x0E7
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_IN_CAR_2D: // 0x0E8
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_CHAR_2D: // 0x0E9
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_CHAR_2D: // 0x0EA
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_CHAR_2D: // 0x0EB
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_2D: // 0x0EC
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_2D: // 0x0ED
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_2D: // 0x0EE
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_2D: // 0x0EF
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_2D: // 0x0F0
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_2D: // 0x0F1
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_2D: // 0x0F2
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_2D: // 0x0F3
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_CHAR_2D: // 0x0F4
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_3D: // 0x0F5
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_3D: // 0x0F6
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_3D: // 0x0F7
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_ANY_MEANS_3D: // 0x0F8
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_ON_FOOT_3D: // 0x0F9
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_IN_CAR_3D: // 0x0FA
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_CHAR_3D: // 0x0FB
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_CHAR_3D: // 0x0FC
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_CHAR_3D: // 0x0FD
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_3D: // 0x0FE
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_3D: // 0x0FF
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_3D: // 0x100
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_3D: // 0x101
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_3D: // 0x102
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_3D: // 0x103
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_3D: // 0x104
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_3D: // 0x105
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_CHAR_3D: // 0x106
        break;
    case COMMAND_CREATE_OBJECT: // 0x107
        break;
    case COMMAND_DELETE_OBJECT: // 0x108
        break;
    case COMMAND_ADD_SCORE: // 0x109
        break;
    case COMMAND_IS_SCORE_GREATER: // 0x10A
        break;
    case COMMAND_STORE_SCORE: // 0x10B
        break;
    case COMMAND_GIVE_REMOTE_CONTROLLED_CAR_TO_PLAYER: // 0x10C
        break;
    case COMMAND_ALTER_WANTED_LEVEL: // 0x10D
        break;
    case COMMAND_ALTER_WANTED_LEVEL_NO_DROP: // 0x10E
        break;
    case COMMAND_IS_WANTED_LEVEL_GREATER: // 0x10F
        break;
    case COMMAND_CLEAR_WANTED_LEVEL: // 0x110
        break;
    case COMMAND_SET_DEATHARREST_STATE: // 0x111
        break;
    case COMMAND_HAS_DEATHARREST_BEEN_EXECUTED: // 0x112
        break;
    case COMMAND_ADD_AMMO_TO_PLAYER: // 0x113
        break;
    case COMMAND_ADD_AMMO_TO_CHAR: // 0x114
        break;
    case COMMAND_ADD_AMMO_TO_CAR: // 0x115
        break;
    case COMMAND_IS_PLAYER_STILL_ALIVE: // 0x116
        break;
    case COMMAND_IS_PLAYER_DEAD: // 0x117
        break;
    case COMMAND_IS_CHAR_DEAD: // 0x118
        break;
    case COMMAND_IS_CAR_DEAD: // 0x119
        break;
    case COMMAND_SET_CHAR_THREAT_SEARCH: // 0x11A
        break;
    case COMMAND_SET_CHAR_THREAT_REACTION: // 0x11B
        break;
    case COMMAND_SET_CHAR_OBJ_NO_OBJ: // 0x11C
        break;
    case COMMAND_ORDER_DRIVER_OUT_OF_CAR: // 0x11D
        break;
    case COMMAND_ORDER_CHAR_TO_DRIVE_CAR: // 0x11E
        break;
    case COMMAND_ADD_PATROL_POINT: // 0x11F
        break;
    case COMMAND_IS_PLAYER_IN_GANGZONE: // 0x120
        break;
    case COMMAND_IS_PLAYER_IN_ZONE: // 0x121
        break;
    case COMMAND_IS_PLAYER_PRESSING_HORN: // 0x122
        break;
    case COMMAND_HAS_CHAR_SPOTTED_PLAYER: // 0x123
        break;
    case COMMAND_ORDER_CHAR_TO_BACKDOOR: // 0x124
        break;
    case COMMAND_ADD_CHAR_TO_GANG: // 0x125
        break;
    case COMMAND_IS_CHAR_OBJECTIVE_PASSED: // 0x126
        break;
    case COMMAND_SET_CHAR_DRIVE_AGGRESSION: // 0x127
        break;
    case COMMAND_SET_CHAR_MAX_DRIVESPEED: // 0x128
        break;
    case COMMAND_CREATE_CHAR_INSIDE_CAR: // 0x129
        break;
    case COMMAND_WARP_PLAYER_FROM_CAR_TO_COORD: // 0x12A
        break;
    case COMMAND_MAKE_CHAR_DO_NOTHING: // 0x12B
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x47C100
int8 CRunningScript::ProcessCommands300To399(int32 commandId) {
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
        break;
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
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x47D210
int8 CRunningScript::ProcessCommands400To499(int32 commandId) {
    switch (commandId) {
    case COMMAND_ADD_UPSIDEDOWN_CAR_CHECK: // 0x190
        break;
    case COMMAND_REMOVE_UPSIDEDOWN_CAR_CHECK: // 0x191
        break;
    case COMMAND_SET_CHAR_OBJ_WAIT_ON_FOOT: // 0x192
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_ON_FOOT_TILL_SAFE: // 0x193
        break;
    case COMMAND_SET_CHAR_OBJ_GUARD_SPOT: // 0x194
        break;
    case COMMAND_SET_CHAR_OBJ_GUARD_AREA: // 0x195
        break;
    case COMMAND_SET_CHAR_OBJ_WAIT_IN_CAR: // 0x196
        break;
    case COMMAND_IS_PLAYER_IN_AREA_ON_FOOT_2D: // 0x197
        break;
    case COMMAND_IS_PLAYER_IN_AREA_IN_CAR_2D: // 0x198
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_2D: // 0x199
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_ON_FOOT_2D: // 0x19A
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_IN_CAR_2D: // 0x19B
        break;
    case COMMAND_IS_PLAYER_IN_AREA_ON_FOOT_3D: // 0x19C
        break;
    case COMMAND_IS_PLAYER_IN_AREA_IN_CAR_3D: // 0x19D
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_3D: // 0x19E
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_ON_FOOT_3D: // 0x19F
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_IN_CAR_3D: // 0x1A0
        break;
    case COMMAND_IS_CHAR_IN_AREA_ON_FOOT_2D: // 0x1A1
        break;
    case COMMAND_IS_CHAR_IN_AREA_IN_CAR_2D: // 0x1A2
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_2D: // 0x1A3
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_2D: // 0x1A4
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_2D: // 0x1A5
        break;
    case COMMAND_IS_CHAR_IN_AREA_ON_FOOT_3D: // 0x1A6
        break;
    case COMMAND_IS_CHAR_IN_AREA_IN_CAR_3D: // 0x1A7
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_3D: // 0x1A8
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_3D: // 0x1A9
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_3D: // 0x1AA
        break;
    case COMMAND_IS_CAR_STOPPED_IN_AREA_2D: // 0x1AB
        break;
    case COMMAND_IS_CAR_STOPPED_IN_AREA_3D: // 0x1AC
        break;
    case COMMAND_LOCATE_CAR_2D: // 0x1AD
        break;
    case COMMAND_LOCATE_STOPPED_CAR_2D: // 0x1AE
        break;
    case COMMAND_LOCATE_CAR_3D: // 0x1AF
        break;
    case COMMAND_LOCATE_STOPPED_CAR_3D: // 0x1B0
        break;
    case COMMAND_GIVE_WEAPON_TO_PLAYER: // 0x1B1
        break;
    case COMMAND_GIVE_WEAPON_TO_CHAR: // 0x1B2
        break;
    case COMMAND_GIVE_WEAPON_TO_CAR: // 0x1B3
        break;
    case COMMAND_SET_PLAYER_CONTROL: // 0x1B4
        break;
    case COMMAND_FORCE_WEATHER: // 0x1B5
        break;
    case COMMAND_FORCE_WEATHER_NOW: // 0x1B6
        break;
    case COMMAND_RELEASE_WEATHER: // 0x1B7
        break;
    case COMMAND_SET_CURRENT_PLAYER_WEAPON: // 0x1B8
        break;
    case COMMAND_SET_CURRENT_CHAR_WEAPON: // 0x1B9
        break;
    case COMMAND_SET_CURRENT_CAR_WEAPON: // 0x1BA
        break;
    case COMMAND_GET_OBJECT_COORDINATES: // 0x1BB
        break;
    case COMMAND_SET_OBJECT_COORDINATES: // 0x1BC
        break;
    case COMMAND_GET_GAME_TIMER: // 0x1BD
        break;
    case COMMAND_TURN_CHAR_TO_FACE_COORD: // 0x1BE
        break;
    case COMMAND_TURN_PLAYER_TO_FACE_COORD: // 0x1BF
        break;
    case COMMAND_STORE_WANTED_LEVEL: // 0x1C0
        break;
    case COMMAND_IS_CAR_STOPPED: // 0x1C1
        break;
    case COMMAND_MARK_CHAR_AS_NO_LONGER_NEEDED: // 0x1C2
        break;
    case COMMAND_MARK_CAR_AS_NO_LONGER_NEEDED: // 0x1C3
        break;
    case COMMAND_MARK_OBJECT_AS_NO_LONGER_NEEDED: // 0x1C4
        break;
    case COMMAND_DONT_REMOVE_CHAR: // 0x1C5
        break;
    case COMMAND_DONT_REMOVE_CAR: // 0x1C6
        break;
    case COMMAND_DONT_REMOVE_OBJECT: // 0x1C7
        break;
    case COMMAND_CREATE_CHAR_AS_PASSENGER: // 0x1C8
        break;
    case COMMAND_SET_CHAR_OBJ_KILL_CHAR_ON_FOOT: // 0x1C9
        break;
    case COMMAND_SET_CHAR_OBJ_KILL_PLAYER_ON_FOOT: // 0x1CA
        break;
    case COMMAND_SET_CHAR_OBJ_KILL_CHAR_ANY_MEANS: // 0x1CB
        break;
    case COMMAND_SET_CHAR_OBJ_KILL_PLAYER_ANY_MEANS: // 0x1CC
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_CHAR_ON_FOOT_TILL_SAFE: // 0x1CD
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_PLAYER_ON_FOOT_TILL_SAFE: // 0x1CE
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS: // 0x1CF
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_PLAYER_ON_FOOT_ALWAYS: // 0x1D0
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_CHAR_ON_FOOT: // 0x1D1
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_PLAYER_ON_FOOT: // 0x1D2
        break;
    case COMMAND_SET_CHAR_OBJ_LEAVE_CAR: // 0x1D3
        break;
    case COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_PASSENGER: // 0x1D4
        break;
    case COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_DRIVER: // 0x1D5
        break;
    case COMMAND_SET_CHAR_OBJ_FOLLOW_CAR_IN_CAR: // 0x1D6
        break;
    case COMMAND_SET_CHAR_OBJ_FIRE_AT_OBJECT_FROM_VEHICLE: // 0x1D7
        break;
    case COMMAND_SET_CHAR_OBJ_DESTROY_OBJECT: // 0x1D8
        break;
    case COMMAND_SET_CHAR_OBJ_DESTROY_CAR: // 0x1D9
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_AREA_ON_FOOT: // 0x1DA
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_AREA_IN_CAR: // 0x1DB
        break;
    case COMMAND_SET_CHAR_OBJ_FOLLOW_CAR_ON_FOOT_WITH_OFFSET: // 0x1DC
        break;
    case COMMAND_SET_CHAR_OBJ_GUARD_ATTACK: // 0x1DD
        break;
    case COMMAND_SET_CHAR_AS_LEADER: // 0x1DE
        break;
    case COMMAND_SET_PLAYER_AS_LEADER: // 0x1DF
        break;
    case COMMAND_LEAVE_GROUP: // 0x1E0
        break;
    case COMMAND_SET_CHAR_OBJ_FOLLOW_ROUTE: // 0x1E1
        break;
    case COMMAND_ADD_ROUTE_POINT: // 0x1E2
        break;
    case COMMAND_PRINT_WITH_NUMBER_BIG: // 0x1E3
        break;
    case COMMAND_PRINT_WITH_NUMBER: // 0x1E4
        break;
    case COMMAND_PRINT_WITH_NUMBER_NOW: // 0x1E5
        break;
    case COMMAND_PRINT_WITH_NUMBER_SOON: // 0x1E6
        break;
    case COMMAND_SWITCH_ROADS_ON: // 0x1E7
        break;
    case COMMAND_SWITCH_ROADS_OFF: // 0x1E8
        break;
    case COMMAND_GET_NUMBER_OF_PASSENGERS: // 0x1E9
        break;
    case COMMAND_GET_MAXIMUM_NUMBER_OF_PASSENGERS: // 0x1EA
        break;
    case COMMAND_SET_CAR_DENSITY_MULTIPLIER: // 0x1EB
        break;
    case COMMAND_SET_CAR_HEAVY: // 0x1EC
        break;
    case COMMAND_CLEAR_CHAR_THREAT_SEARCH: // 0x1ED
        break;
    case COMMAND_ACTIVATE_CRANE: // 0x1EE
        break;
    case COMMAND_DEACTIVATE_CRANE: // 0x1EF
        break;
    case COMMAND_SET_MAX_WANTED_LEVEL: // 0x1F0
        break;
    case COMMAND_SAVE_VAR_INT: // 0x1F1
        break;
    case COMMAND_SAVE_VAR_FLOAT: // 0x1F2
        break;
    case COMMAND_IS_CAR_IN_AIR_PROPER: // 0x1F3
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x47E090
int8 CRunningScript::ProcessCommands500To599(int32 commandId) {
    switch (commandId) {
    case COMMAND_IS_CAR_UPSIDEDOWN: // 0x1F4
        break;
    case COMMAND_GET_PLAYER_CHAR: // 0x1F5
        break;
    case COMMAND_CANCEL_OVERRIDE_RESTART: // 0x1F6
        break;
    case COMMAND_SET_POLICE_IGNORE_PLAYER: // 0x1F7
        break;
    case COMMAND_ADD_PAGER_MESSAGE_WITH_NUMBER: // 0x1F8
        break;
    case COMMAND_START_KILL_FRENZY: // 0x1F9
        break;
    case COMMAND_READ_KILL_FRENZY_STATUS: // 0x1FA
        break;
    case COMMAND_SQRT: // 0x1FB
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_CAR_2D: // 0x1FC
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_CAR_2D: // 0x1FD
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_CAR_2D: // 0x1FE
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_CAR_3D: // 0x1FF
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_CAR_3D: // 0x200
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_CAR_3D: // 0x201
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_2D: // 0x202
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_CAR_2D: // 0x203
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_CAR_2D: // 0x204
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_3D: // 0x205
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_CAR_3D: // 0x206
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_CAR_3D: // 0x207
        break;
    case COMMAND_GENERATE_RANDOM_FLOAT_IN_RANGE: // 0x208
        break;
    case COMMAND_GENERATE_RANDOM_INT_IN_RANGE: // 0x209
        break;
    case COMMAND_LOCK_CAR_DOORS: // 0x20A
        break;
    case COMMAND_EXPLODE_CAR: // 0x20B
        break;
    case COMMAND_ADD_EXPLOSION: // 0x20C
        break;
    case COMMAND_IS_CAR_UPRIGHT: // 0x20D
        break;
    case COMMAND_TURN_CHAR_TO_FACE_CHAR: // 0x20E
        break;
    case COMMAND_TURN_CHAR_TO_FACE_PLAYER: // 0x20F
        break;
    case COMMAND_TURN_PLAYER_TO_FACE_CHAR: // 0x210
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_COORD_ON_FOOT: // 0x211
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_COORD_IN_CAR: // 0x212
        break;
    case COMMAND_CREATE_PICKUP: // 0x213
        break;
    case COMMAND_HAS_PICKUP_BEEN_COLLECTED: // 0x214
        break;
    case COMMAND_REMOVE_PICKUP: // 0x215
        break;
    case COMMAND_SET_TAXI_LIGHTS: // 0x216
        break;
    case COMMAND_PRINT_BIG_Q: // 0x217
        break;
    case COMMAND_PRINT_WITH_NUMBER_BIG_Q: // 0x218
        break;
    case COMMAND_SET_GARAGE: // 0x219
        break;
    case COMMAND_SET_GARAGE_WITH_CAR_MODEL: // 0x21A
        break;
    case COMMAND_SET_TARGET_CAR_FOR_MISSION_GARAGE: // 0x21B
        break;
    case COMMAND_IS_CAR_IN_MISSION_GARAGE: // 0x21C
        break;
    case COMMAND_SET_FREE_BOMBS: // 0x21D
        break;
    case COMMAND_SET_POWERPOINT: // 0x21E
        break;
    case COMMAND_SET_ALL_TAXI_LIGHTS: // 0x21F
        break;
    case COMMAND_IS_CAR_ARMED_WITH_ANY_BOMB: // 0x220
        break;
    case COMMAND_APPLY_BRAKES_TO_PLAYERS_CAR: // 0x221
        break;
    case COMMAND_SET_PLAYER_HEALTH: // 0x222
        break;
    case COMMAND_SET_CHAR_HEALTH: // 0x223
        break;
    case COMMAND_SET_CAR_HEALTH: // 0x224
        break;
    case COMMAND_GET_PLAYER_HEALTH: // 0x225
        break;
    case COMMAND_GET_CHAR_HEALTH: // 0x226
        break;
    case COMMAND_GET_CAR_HEALTH: // 0x227
        break;
    case COMMAND_IS_CAR_ARMED_WITH_BOMB: // 0x228
        break;
    case COMMAND_CHANGE_CAR_COLOUR: // 0x229
        break;
    case COMMAND_SWITCH_PED_ROADS_ON: // 0x22A
        break;
    case COMMAND_SWITCH_PED_ROADS_OFF: // 0x22B
        break;
    case COMMAND_CHAR_LOOK_AT_CHAR_ALWAYS: // 0x22C
        break;
    case COMMAND_CHAR_LOOK_AT_PLAYER_ALWAYS: // 0x22D
        break;
    case COMMAND_PLAYER_LOOK_AT_CHAR_ALWAYS: // 0x22E
        break;
    case COMMAND_STOP_CHAR_LOOKING: // 0x22F
        break;
    case COMMAND_STOP_PLAYER_LOOKING: // 0x230
        break;
    case COMMAND_SET_SCRIPT_POLICE_HELI_TO_CHASE_CHAR: // 0x231
        break;
    case COMMAND_SET_GANG_ATTITUDE: // 0x232
        break;
    case COMMAND_SET_GANG_GANG_ATTITUDE: // 0x233
        break;
    case COMMAND_SET_GANG_PLAYER_ATTITUDE: // 0x234
        break;
    case COMMAND_SET_GANG_PED_MODELS: // 0x235
        break;
    case COMMAND_SET_GANG_CAR_MODEL: // 0x236
        break;
    case COMMAND_SET_GANG_WEAPONS: // 0x237
        break;
    case COMMAND_SET_CHAR_OBJ_RUN_TO_AREA: // 0x238
        break;
    case COMMAND_SET_CHAR_OBJ_RUN_TO_COORD: // 0x239
        break;
    case COMMAND_IS_PLAYER_TOUCHING_OBJECT_ON_FOOT: // 0x23A
        break;
    case COMMAND_IS_CHAR_TOUCHING_OBJECT_ON_FOOT: // 0x23B
        break;
    case COMMAND_LOAD_SPECIAL_CHARACTER: // 0x23C
        break;
    case COMMAND_HAS_SPECIAL_CHARACTER_LOADED: // 0x23D
        break;
    case COMMAND_FLASH_CAR: // 0x23E
        break;
    case COMMAND_FLASH_CHAR: // 0x23F
        break;
    case COMMAND_FLASH_OBJECT: // 0x240
        break;
    case COMMAND_IS_PLAYER_IN_REMOTE_MODE: // 0x241
        break;
    case COMMAND_ARM_CAR_WITH_BOMB: // 0x242
        break;
    case COMMAND_SET_CHAR_PERSONALITY: // 0x243
        break;
    case COMMAND_SET_CUTSCENE_OFFSET: // 0x244
        break;
    case COMMAND_SET_ANIM_GROUP_FOR_CHAR: // 0x245
        break;
    case COMMAND_SET_ANIM_GROUP_FOR_PLAYER: // 0x246
        break;
    case COMMAND_REQUEST_MODEL: // 0x247
        break;
    case COMMAND_HAS_MODEL_LOADED: // 0x248
        break;
    case COMMAND_MARK_MODEL_AS_NO_LONGER_NEEDED: // 0x249
        break;
    case COMMAND_GRAB_PHONE: // 0x24A
        break;
    case COMMAND_SET_REPEATED_PHONE_MESSAGE: // 0x24B
        break;
    case COMMAND_SET_PHONE_MESSAGE: // 0x24C
        break;
    case COMMAND_HAS_PHONE_DISPLAYED_MESSAGE: // 0x24D
        break;
    case COMMAND_TURN_PHONE_OFF: // 0x24E
        break;
    case COMMAND_DRAW_CORONA: // 0x24F
        break;
    case COMMAND_DRAW_LIGHT: // 0x250
        break;
    case COMMAND_STORE_WEATHER: // 0x251
        break;
    case COMMAND_RESTORE_WEATHER: // 0x252
        break;
    case COMMAND_STORE_CLOCK: // 0x253
        // CClock::StoreClock();
        break;
    case COMMAND_RESTORE_CLOCK: // 0x254
        // CClock::RestoreClock();
        break;
    case COMMAND_RESTART_CRITICAL_MISSION: // 0x255
        break;
    case COMMAND_IS_PLAYER_PLAYING: // 0x256
        CollectParameters(1);
        UpdateCompareFlag(CWorld::Players[CTheScripts::ScriptParams[0].iParam].m_nPlayerState == PLAYERSTATE_PLAYING);
        return 0;
    case COMMAND_SET_COLL_OBJ_NO_OBJ: // 0x257
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x47F370
int8 CRunningScript::ProcessCommands600To699(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_COLL_OBJ_WAIT_ON_FOOT: // 0x258
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_ON_FOOT_TILL_SAFE: // 0x259
        break;
    case COMMAND_SET_COLL_OBJ_GUARD_SPOT: // 0x25A
        break;
    case COMMAND_SET_COLL_OBJ_GUARD_AREA: // 0x25B
        break;
    case COMMAND_SET_COLL_OBJ_WAIT_IN_CAR: // 0x25C
        break;
    case COMMAND_SET_COLL_OBJ_KILL_CHAR_ON_FOOT: // 0x25D
        break;
    case COMMAND_SET_COLL_OBJ_KILL_PLAYER_ON_FOOT: // 0x25E
        break;
    case COMMAND_SET_COLL_OBJ_KILL_CHAR_ANY_MEANS: // 0x25F
        break;
    case COMMAND_SET_COLL_OBJ_KILL_PLAYER_ANY_MEANS: // 0x260
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_TILL_SAFE: // 0x261
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_PLAYER_ON_FOOT_TILL_SAFE: // 0x262
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS: // 0x263
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_PLAYER_ON_FOOT_ALWAYS: // 0x264
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_CHAR_ON_FOOT: // 0x265
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_PLAYER_ON_FOOT: // 0x266
        break;
    case COMMAND_SET_COLL_OBJ_LEAVE_CAR: // 0x267
        break;
    case COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_PASSENGER: // 0x268
        break;
    case COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_DRIVER: // 0x269
        break;
    case COMMAND_SET_COLL_OBJ_FOLLOW_CAR_IN_CAR: // 0x26A
        break;
    case COMMAND_SET_COLL_OBJ_FIRE_AT_OBJECT_FROM_VEHICLE: // 0x26B
        break;
    case COMMAND_SET_COLL_OBJ_DESTROY_OBJECT: // 0x26C
        break;
    case COMMAND_SET_COLL_OBJ_DESTROY_CAR: // 0x26D
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_AREA_ON_FOOT: // 0x26E
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_AREA_IN_CAR: // 0x26F
        break;
    case COMMAND_SET_COLL_OBJ_FOLLOW_CAR_ON_FOOT_WITH_OFFSET: // 0x270
        break;
    case COMMAND_SET_COLL_OBJ_GUARD_ATTACK: // 0x271
        break;
    case COMMAND_SET_COLL_OBJ_FOLLOW_ROUTE: // 0x272
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_COORD_ON_FOOT: // 0x273
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_COORD_IN_CAR: // 0x274
        break;
    case COMMAND_SET_COLL_OBJ_RUN_TO_AREA: // 0x275
        break;
    case COMMAND_SET_COLL_OBJ_RUN_TO_COORD: // 0x276
        break;
    case COMMAND_ADD_PEDS_IN_AREA_TO_COLL: // 0x277
        break;
    case COMMAND_ADD_PEDS_IN_VEHICLE_TO_COLL: // 0x278
        break;
    case COMMAND_CLEAR_COLL: // 0x279
        break;
    case COMMAND_IS_COLL_IN_CARS: // 0x27A
        break;
    case COMMAND_LOCATE_COLL_ANY_MEANS_2D: // 0x27B
        break;
    case COMMAND_LOCATE_COLL_ON_FOOT_2D: // 0x27C
        break;
    case COMMAND_LOCATE_COLL_IN_CAR_2D: // 0x27D
        break;
    case COMMAND_LOCATE_STOPPED_COLL_ANY_MEANS_2D: // 0x27E
        break;
    case COMMAND_LOCATE_STOPPED_COLL_ON_FOOT_2D: // 0x27F
        break;
    case COMMAND_LOCATE_STOPPED_COLL_IN_CAR_2D: // 0x280
        break;
    case COMMAND_LOCATE_COLL_ANY_MEANS_CHAR_2D: // 0x281
        break;
    case COMMAND_LOCATE_COLL_ON_FOOT_CHAR_2D: // 0x282
        break;
    case COMMAND_LOCATE_COLL_IN_CAR_CHAR_2D: // 0x283
        break;
    case COMMAND_LOCATE_COLL_ANY_MEANS_CAR_2D: // 0x284
        break;
    case COMMAND_LOCATE_COLL_ON_FOOT_CAR_2D: // 0x285
        break;
    case COMMAND_LOCATE_COLL_IN_CAR_CAR_2D: // 0x286
        break;
    case COMMAND_LOCATE_COLL_ANY_MEANS_PLAYER_2D: // 0x287
        break;
    case COMMAND_LOCATE_COLL_ON_FOOT_PLAYER_2D: // 0x288
        break;
    case COMMAND_LOCATE_COLL_IN_CAR_PLAYER_2D: // 0x289
        break;
    case COMMAND_IS_COLL_IN_AREA_2D: // 0x28A
        break;
    case COMMAND_IS_COLL_IN_AREA_ON_FOOT_2D: // 0x28B
        break;
    case COMMAND_IS_COLL_IN_AREA_IN_CAR_2D: // 0x28C
        break;
    case COMMAND_IS_COLL_STOPPED_IN_AREA_2D: // 0x28D
        break;
    case COMMAND_IS_COLL_STOPPED_IN_AREA_ON_FOOT_2D: // 0x28E
        break;
    case COMMAND_IS_COLL_STOPPED_IN_AREA_IN_CAR_2D: // 0x28F
        break;
    case COMMAND_GET_NUMBER_OF_PEDS_IN_COLL: // 0x290
        break;
    case COMMAND_SET_CHAR_HEED_THREATS: // 0x291
        break;
    case COMMAND_SET_PLAYER_HEED_THREATS: // 0x292
        break;
    case COMMAND_GET_CONTROLLER_MODE: // 0x293
        break;
    case COMMAND_SET_CAN_RESPRAY_CAR: // 0x294
        break;
    case COMMAND_IS_TAXI: // 0x295
        break;
    case COMMAND_UNLOAD_SPECIAL_CHARACTER: // 0x296
        break;
    case COMMAND_RESET_NUM_OF_MODELS_KILLED_BY_PLAYER: // 0x297
        break;
    case COMMAND_GET_NUM_OF_MODELS_KILLED_BY_PLAYER: // 0x298
        break;
    case COMMAND_ACTIVATE_GARAGE: // 0x299
        break;
    case COMMAND_SWITCH_TAXI_TIMER: // 0x29A
        break;
    case COMMAND_CREATE_OBJECT_NO_OFFSET: // 0x29B
        break;
    case COMMAND_IS_BOAT: // 0x29C
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_AREA_ANY_MEANS: // 0x29D
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_AREA_ANY_MEANS: // 0x29E
        break;
    case COMMAND_IS_PLAYER_STOPPED: // 0x29F
        break;
    case COMMAND_IS_CHAR_STOPPED: // 0x2A0
        break;
    case COMMAND_MESSAGE_WAIT: // 0x2A1
        break;
    case COMMAND_ADD_PARTICLE_EFFECT: // 0x2A2
        break;
    case COMMAND_SWITCH_WIDESCREEN: // 0x2A3
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_CAR: // 0x2A4
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_CHAR: // 0x2A5
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_OBJECT: // 0x2A6
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_CONTACT_POINT: // 0x2A7
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_COORD: // 0x2A8
        break;
    case COMMAND_SET_CHAR_ONLY_DAMAGED_BY_PLAYER: // 0x2A9
        break;
    case COMMAND_SET_CAR_ONLY_DAMAGED_BY_PLAYER: // 0x2AA
        break;
    case COMMAND_SET_CHAR_PROOFS: // 0x2AB
        break;
    case COMMAND_SET_CAR_PROOFS: // 0x2AC
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_2D: // 0x2AD
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_ON_FOOT_2D: // 0x2AE
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_IN_CAR_2D: // 0x2AF
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_2D: // 0x2B0
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_ON_FOOT_2D: // 0x2B1
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_IN_CAR_2D: // 0x2B2
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_3D: // 0x2B3
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_ON_FOOT_3D: // 0x2B4
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_IN_CAR_3D: // 0x2B5
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_3D: // 0x2B6
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_ON_FOOT_3D: // 0x2B7
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_IN_CAR_3D: // 0x2B8
        break;
    case COMMAND_DEACTIVATE_GARAGE: // 0x2B9
        break;
    case COMMAND_GET_NUMBER_OF_CARS_COLLECTED_BY_GARAGE: // 0x2BA
        break;
    case COMMAND_HAS_CAR_BEEN_TAKEN_TO_GARAGE: // 0x2BB
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x47FA30
int8 CRunningScript::ProcessCommands700To799(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_SWAT_REQUIRED: // 0x2BC
        break;
    case COMMAND_SET_FBI_REQUIRED: // 0x2BD
        break;
    case COMMAND_SET_ARMY_REQUIRED: // 0x2BE
        break;
    case COMMAND_IS_CAR_IN_WATER: // 0x2BF
        break;
    case COMMAND_GET_CLOSEST_CHAR_NODE: // 0x2C0
        break;
    case COMMAND_GET_CLOSEST_CAR_NODE: // 0x2C1
        break;
    case COMMAND_CAR_GOTO_COORDINATES_ACCURATE: // 0x2C2
        break;
    case COMMAND_START_PACMAN_RACE: // 0x2C3
        break;
    case COMMAND_START_PACMAN_RECORD: // 0x2C4
        break;
    case COMMAND_GET_NUMBER_OF_POWER_PILLS_EATEN: // 0x2C5
        break;
    case COMMAND_CLEAR_PACMAN: // 0x2C6
        break;
    case COMMAND_START_PACMAN_SCRAMBLE: // 0x2C7
        break;
    case COMMAND_GET_NUMBER_OF_POWER_PILLS_CARRIED: // 0x2C8
        break;
    case COMMAND_CLEAR_NUMBER_OF_POWER_PILLS_CARRIED: // 0x2C9
        break;
    case COMMAND_IS_CAR_ON_SCREEN: // 0x2CA
        break;
    case COMMAND_IS_CHAR_ON_SCREEN: // 0x2CB
        break;
    case COMMAND_IS_OBJECT_ON_SCREEN: // 0x2CC
        break;
    case COMMAND_GOSUB_FILE: // 0x2CD
        break;
    case COMMAND_GET_GROUND_Z_FOR_3D_COORD: // 0x2CE
        break;
    case COMMAND_START_SCRIPT_FIRE: // 0x2CF
        break;
    case COMMAND_IS_SCRIPT_FIRE_EXTINGUISHED: // 0x2D0
        break;
    case COMMAND_REMOVE_SCRIPT_FIRE: // 0x2D1
        break;
    case COMMAND_SET_COMEDY_CONTROLS: // 0x2D2
        break;
    case COMMAND_BOAT_GOTO_COORDS: // 0x2D3
        break;
    case COMMAND_BOAT_STOP: // 0x2D4
        break;
    case COMMAND_IS_PLAYER_SHOOTING_IN_AREA: // 0x2D5
        break;
    case COMMAND_IS_CHAR_SHOOTING_IN_AREA: // 0x2D6
        break;
    case COMMAND_IS_CURRENT_PLAYER_WEAPON: // 0x2D7
        break;
    case COMMAND_IS_CURRENT_CHAR_WEAPON: // 0x2D8
        break;
    case COMMAND_CLEAR_NUMBER_OF_POWER_PILLS_EATEN: // 0x2D9
        break;
    case COMMAND_ADD_POWER_PILL: // 0x2DA
        break;
    case COMMAND_SET_BOAT_CRUISE_SPEED: // 0x2DB
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_AREA: // 0x2DC
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_ZONE: // 0x2DD
        break;
    case COMMAND_IS_PLAYER_IN_TAXI: // 0x2DE
        break;
    case COMMAND_IS_PLAYER_SHOOTING: // 0x2DF
        break;
    case COMMAND_IS_CHAR_SHOOTING: // 0x2E0
        break;
    case COMMAND_CREATE_MONEY_PICKUP: // 0x2E1
        break;
    case COMMAND_SET_CHAR_ACCURACY: // 0x2E2
        break;
    case COMMAND_GET_CAR_SPEED: // 0x2E3
        break;
    case COMMAND_LOAD_CUTSCENE: // 0x2E4
        break;
    case COMMAND_CREATE_CUTSCENE_OBJECT: // 0x2E5
        break;
    case COMMAND_SET_CUTSCENE_ANIM: // 0x2E6
        break;
    case COMMAND_START_CUTSCENE: // 0x2E7
        break;
    case COMMAND_GET_CUTSCENE_TIME: // 0x2E8
        break;
    case COMMAND_HAS_CUTSCENE_FINISHED: // 0x2E9
        break;
    case COMMAND_CLEAR_CUTSCENE: // 0x2EA
        break;
    case COMMAND_RESTORE_CAMERA_JUMPCUT: // 0x2EB
        break;
    case COMMAND_CREATE_COLLECTABLE1: // 0x2EC
        break;
    case COMMAND_SET_COLLECTABLE1_TOTAL: // 0x2ED
        break;
    case COMMAND_IS_PROJECTILE_IN_AREA: // 0x2EE
        break;
    case COMMAND_DESTROY_PROJECTILES_IN_AREA: // 0x2EF
        break;
    case COMMAND_DROP_MINE: // 0x2F0
        break;
    case COMMAND_DROP_NAUTICAL_MINE: // 0x2F1
        break;
    case COMMAND_IS_CHAR_MODEL: // 0x2F2
        break;
    case COMMAND_LOAD_SPECIAL_MODEL: // 0x2F3
        break;
    case COMMAND_CREATE_CUTSCENE_HEAD: // 0x2F4
        break;
    case COMMAND_SET_CUTSCENE_HEAD_ANIM: // 0x2F5
        break;
    case COMMAND_SIN: // 0x2F6
        break;
    case COMMAND_COS: // 0x2F7
        break;
    case COMMAND_GET_CAR_FORWARD_X: // 0x2F8
        break;
    case COMMAND_GET_CAR_FORWARD_Y: // 0x2F9
        break;
    case COMMAND_CHANGE_GARAGE_TYPE: // 0x2FA
        break;
    case COMMAND_ACTIVATE_CRUSHER_CRANE: // 0x2FB
        break;
    case COMMAND_PRINT_WITH_2_NUMBERS: // 0x2FC
        break;
    case COMMAND_PRINT_WITH_2_NUMBERS_NOW: // 0x2FD
        break;
    case COMMAND_PRINT_WITH_2_NUMBERS_SOON: // 0x2FE
        break;
    case COMMAND_PRINT_WITH_3_NUMBERS: // 0x2FF
        break;
    case COMMAND_PRINT_WITH_3_NUMBERS_NOW: // 0x300
        break;
    case COMMAND_PRINT_WITH_3_NUMBERS_SOON: // 0x301
        break;
    case COMMAND_PRINT_WITH_4_NUMBERS: // 0x302
        break;
    case COMMAND_PRINT_WITH_4_NUMBERS_NOW: // 0x303
        break;
    case COMMAND_PRINT_WITH_4_NUMBERS_SOON: // 0x304
        break;
    case COMMAND_PRINT_WITH_5_NUMBERS: // 0x305
        break;
    case COMMAND_PRINT_WITH_5_NUMBERS_NOW: // 0x306
        break;
    case COMMAND_PRINT_WITH_5_NUMBERS_SOON: // 0x307
        break;
    case COMMAND_PRINT_WITH_6_NUMBERS: // 0x308
        break;
    case COMMAND_PRINT_WITH_6_NUMBERS_NOW: // 0x309
        break;
    case COMMAND_PRINT_WITH_6_NUMBERS_SOON: // 0x30A
        break;
    case COMMAND_SET_CHAR_OBJ_FOLLOW_CHAR_IN_FORMATION: // 0x30B
        break;
    case COMMAND_PLAYER_MADE_PROGRESS: // 0x30C
        break;
    case COMMAND_SET_PROGRESS_TOTAL: // 0x30D
        break;
    case COMMAND_REGISTER_JUMP_DISTANCE: // 0x30E
        break;
    case COMMAND_REGISTER_JUMP_HEIGHT: // 0x30F
        break;
    case COMMAND_REGISTER_JUMP_FLIPS: // 0x310
        break;
    case COMMAND_REGISTER_JUMP_SPINS: // 0x311
        break;
    case COMMAND_REGISTER_JUMP_STUNT: // 0x312
        break;
    case COMMAND_REGISTER_UNIQUE_JUMP_FOUND: // 0x313
        break;
    case COMMAND_SET_UNIQUE_JUMPS_TOTAL: // 0x314
        break;
    case COMMAND_REGISTER_PASSENGER_DROPPED_OFF_TAXI: // 0x315
        break;
    case COMMAND_REGISTER_MONEY_MADE_TAXI: // 0x316
        break;
    case COMMAND_REGISTER_MISSION_GIVEN: // 0x317
        break;
    case COMMAND_REGISTER_MISSION_PASSED: // 0x318
        break;
    case COMMAND_SET_CHAR_RUNNING: // 0x319
        break;
    case COMMAND_REMOVE_ALL_SCRIPT_FIRES: // 0x31A
        break;
    case COMMAND_IS_FIRST_CAR_COLOUR: // 0x31B
        break;
    case COMMAND_IS_SECOND_CAR_COLOUR: // 0x31C
        break;
    case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_WEAPON: // 0x31D
        break;
    case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_WEAPON: // 0x31E
        break;
    case COMMAND_IS_CHAR_IN_CHARS_GROUP: // 0x31F
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x481300
int8 CRunningScript::ProcessCommands800To899(int32 commandId) {
    switch (commandId) {
    case COMMAND_IS_CHAR_IN_PLAYERS_GROUP: // 0x320
        break;
    case COMMAND_EXPLODE_CHAR_HEAD: // 0x321
        break;
    case COMMAND_EXPLODE_PLAYER_HEAD: // 0x322
        break;
    case COMMAND_ANCHOR_BOAT: // 0x323
        break;
    case COMMAND_SET_ZONE_GROUP: // 0x324
        break;
    case COMMAND_START_CAR_FIRE: // 0x325
        break;
    case COMMAND_START_CHAR_FIRE: // 0x326
        break;
    case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_AREA: // 0x327
        break;
    case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_ZONE: // 0x328
        break;
    case COMMAND_HAS_RESPRAY_HAPPENED: // 0x329
        break;
    case COMMAND_SET_CAMERA_ZOOM: // 0x32A
        break;
    case COMMAND_CREATE_PICKUP_WITH_AMMO: // 0x32B
        break;
    case COMMAND_SET_CAR_RAM_CAR: // 0x32C
        break;
    case COMMAND_SET_CAR_BLOCK_CAR: // 0x32D
        break;
    case COMMAND_SET_CHAR_OBJ_CATCH_TRAIN: // 0x32E
        break;
    case COMMAND_SET_COLL_OBJ_CATCH_TRAIN: // 0x32F
        break;
    case COMMAND_SET_PLAYER_NEVER_GETS_TIRED: // 0x330
        break;
    case COMMAND_SET_PLAYER_FAST_RELOAD: // 0x331
        break;
    case COMMAND_SET_CHAR_BLEEDING: // 0x332
        break;
    case COMMAND_SET_CAR_FUNNY_SUSPENSION: // 0x333
        break;
    case COMMAND_SET_CAR_BIG_WHEELS: // 0x334
        break;
    case COMMAND_SET_FREE_RESPRAYS: // 0x335
        break;
    case COMMAND_SET_PLAYER_VISIBLE: // 0x336
        break;
    case COMMAND_SET_CHAR_VISIBLE: // 0x337
        break;
    case COMMAND_SET_CAR_VISIBLE: // 0x338
        break;
    case COMMAND_IS_AREA_OCCUPIED: // 0x339
        break;
    case COMMAND_START_DRUG_RUN: // 0x33A
        break;
    case COMMAND_HAS_DRUG_RUN_BEEN_COMPLETED: // 0x33B
        break;
    case COMMAND_HAS_DRUG_PLANE_BEEN_SHOT_DOWN: // 0x33C
        break;
    case COMMAND_SAVE_PLAYER_FROM_FIRES: // 0x33D
        break;
    case COMMAND_DISPLAY_TEXT: // 0x33E
        break;
    case COMMAND_SET_TEXT_SCALE: // 0x33F
        break;
    case COMMAND_SET_TEXT_COLOUR: // 0x340
        break;
    case COMMAND_SET_TEXT_JUSTIFY: // 0x341
        break;
    case COMMAND_SET_TEXT_CENTRE: // 0x342
        break;
    case COMMAND_SET_TEXT_WRAPX: // 0x343
        break;
    case COMMAND_SET_TEXT_CENTRE_SIZE: // 0x344
        break;
    case COMMAND_SET_TEXT_BACKGROUND: // 0x345
        break;
    case COMMAND_SET_TEXT_BACKGROUND_COLOUR: // 0x346
        break;
    case COMMAND_SET_TEXT_BACKGROUND_ONLY_TEXT: // 0x347
        break;
    case COMMAND_SET_TEXT_PROPORTIONAL: // 0x348
        break;
    case COMMAND_SET_TEXT_FONT: // 0x349
        break;
    case COMMAND_INDUSTRIAL_PASSED: // 0x34A
        break;
    case COMMAND_COMMERCIAL_PASSED: // 0x34B
        break;
    case COMMAND_SUBURBAN_PASSED: // 0x34C
        break;
    case COMMAND_ROTATE_OBJECT: // 0x34D
        break;
    case COMMAND_SLIDE_OBJECT: // 0x34E
        break;
    case COMMAND_REMOVE_CHAR_ELEGANTLY: // 0x34F
        break;
    case COMMAND_SET_CHAR_STAY_IN_SAME_PLACE: // 0x350
        break;
    case COMMAND_IS_NASTY_GAME: // 0x351
        break;
    case COMMAND_UNDRESS_CHAR: // 0x352
        break;
    case COMMAND_DRESS_CHAR: // 0x353
        break;
    case COMMAND_START_CHASE_SCENE: // 0x354
        break;
    case COMMAND_STOP_CHASE_SCENE: // 0x355
        break;
    case COMMAND_IS_EXPLOSION_IN_AREA: // 0x356
        break;
    case COMMAND_IS_EXPLOSION_IN_ZONE: // 0x357
        break;
    case COMMAND_START_DRUG_DROP_OFF: // 0x358
        break;
    case COMMAND_HAS_DROP_OFF_PLANE_BEEN_SHOT_DOWN: // 0x359
        break;
    case COMMAND_FIND_DROP_OFF_PLANE_COORDINATES: // 0x35A
        break;
    case COMMAND_CREATE_FLOATING_PACKAGE: // 0x35B
        break;
    case COMMAND_PLACE_OBJECT_RELATIVE_TO_CAR: // 0x35C
        break;
    case COMMAND_MAKE_OBJECT_TARGETTABLE: // 0x35D
        break;
    case COMMAND_ADD_ARMOUR_TO_PLAYER: // 0x35E
        break;
    case COMMAND_ADD_ARMOUR_TO_CHAR: // 0x35F
        break;
    case COMMAND_OPEN_GARAGE: // 0x360
        break;
    case COMMAND_CLOSE_GARAGE: // 0x361
        break;
    case COMMAND_WARP_CHAR_FROM_CAR_TO_COORD: // 0x362
        break;
    case COMMAND_SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE: // 0x363
        break;
    case COMMAND_HAS_CHAR_SPOTTED_CHAR: // 0x364
        break;
    case COMMAND_SET_CHAR_OBJ_HAIL_TAXI: // 0x365
        break;
    case COMMAND_HAS_OBJECT_BEEN_DAMAGED: // 0x366
        break;
    case COMMAND_START_KILL_FRENZY_HEADSHOT: // 0x367
        break;
    case COMMAND_ACTIVATE_MILITARY_CRANE: // 0x368
        break;
    case COMMAND_WARP_PLAYER_INTO_CAR: // 0x369
        break;
    case COMMAND_WARP_CHAR_INTO_CAR: // 0x36A
        break;
    case COMMAND_SWITCH_CAR_RADIO: // 0x36B
        break;
    case COMMAND_SET_AUDIO_STREAM: // 0x36C
        break;
    case COMMAND_PRINT_WITH_2_NUMBERS_BIG: // 0x36D
        break;
    case COMMAND_PRINT_WITH_3_NUMBERS_BIG: // 0x36E
        break;
    case COMMAND_PRINT_WITH_4_NUMBERS_BIG: // 0x36F
        break;
    case COMMAND_PRINT_WITH_5_NUMBERS_BIG: // 0x370
        break;
    case COMMAND_PRINT_WITH_6_NUMBERS_BIG: // 0x371
        break;
    case COMMAND_SET_CHAR_WAIT_STATE: // 0x372
        break;
    case COMMAND_SET_CAMERA_BEHIND_PLAYER: // 0x373
        break;
    case COMMAND_SET_MOTION_BLUR: // 0x374
        break;
    case COMMAND_PRINT_STRING_IN_STRING: // 0x375
        break;
    case COMMAND_CREATE_RANDOM_CHAR: // 0x376
        break;
    case COMMAND_SET_CHAR_OBJ_STEAL_ANY_CAR: // 0x377
        break;
    case COMMAND_SET_2_REPEATED_PHONE_MESSAGES: // 0x378
        break;
    case COMMAND_SET_2_PHONE_MESSAGES: // 0x379
        break;
    case COMMAND_SET_3_REPEATED_PHONE_MESSAGES: // 0x37A
        break;
    case COMMAND_SET_3_PHONE_MESSAGES: // 0x37B
        break;
    case COMMAND_SET_4_REPEATED_PHONE_MESSAGES: // 0x37C
        break;
    case COMMAND_SET_4_PHONE_MESSAGES: // 0x37D
        break;
    case COMMAND_IS_SNIPER_BULLET_IN_AREA: // 0x37E
        break;
    case COMMAND_GIVE_PLAYER_DETONATOR: // 0x37F
        break;
    case COMMAND_SET_COLL_OBJ_STEAL_ANY_CAR: // 0x380
        break;
    case COMMAND_SET_OBJECT_VELOCITY: // 0x381
        break;
    case COMMAND_SET_OBJECT_COLLISION: // 0x382
        break;
    case COMMAND_IS_ICECREAM_JINGLE_ON: // 0x383
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x483BD0
int8 CRunningScript::ProcessCommands900To999(int32 commandId) {
    char str[52];

    switch (commandId) {
    case COMMAND_PRINT_STRING_IN_STRING_NOW: // 0x384
        break;
    case COMMAND_PRINT_STRING_IN_STRING_SOON: // 0x385
        break;
    case COMMAND_SET_5_REPEATED_PHONE_MESSAGES: // 0x386
        break;
    case COMMAND_SET_5_PHONE_MESSAGES: // 0x387
        break;
    case COMMAND_SET_6_REPEATED_PHONE_MESSAGES: // 0x388
        break;
    case COMMAND_SET_6_PHONE_MESSAGES: // 0x389
        break;
    case COMMAND_IS_POINT_OBSCURED_BY_A_MISSION_ENTITY: // 0x38A
        break;
    case COMMAND_LOAD_ALL_MODELS_NOW: // 0x38B
        break;
    case COMMAND_ADD_TO_OBJECT_VELOCITY: // 0x38C
        break;
    case COMMAND_DRAW_SPRITE: // 0x38D
        break;
    case COMMAND_DRAW_RECT: // 0x38E
        break;
    case COMMAND_LOAD_SPRITE: // 0x38F
        break;
    case COMMAND_LOAD_TEXTURE_DICTIONARY: // 0x390
        break;
    case COMMAND_REMOVE_TEXTURE_DICTIONARY: // 0x391
        break;
    case COMMAND_SET_OBJECT_DYNAMIC: // 0x392
        break;
    case COMMAND_SET_CHAR_ANIM_SPEED: // 0x393
        break;
    case COMMAND_PLAY_MISSION_PASSED_TUNE: // 0x394
        break;
    case COMMAND_CLEAR_AREA: // 0x395
        break;
    case COMMAND_FREEZE_ONSCREEN_TIMER: // 0x396
        break;
    case COMMAND_SWITCH_CAR_SIREN: // 0x397
        break;
    case COMMAND_SWITCH_PED_ROADS_ON_ANGLED: // 0x398
        break;
    case COMMAND_SWITCH_PED_ROADS_OFF_ANGLED: // 0x399
        break;
    case COMMAND_SWITCH_ROADS_ON_ANGLED: // 0x39A
        break;
    case COMMAND_SWITCH_ROADS_OFF_ANGLED: // 0x39B
        break;
    case COMMAND_SET_CAR_WATERTIGHT: // 0x39C
        break;
    case COMMAND_ADD_MOVING_PARTICLE_EFFECT: // 0x39D
        break;
    case COMMAND_SET_CHAR_CANT_BE_DRAGGED_OUT: // 0x39E
        break;
    case COMMAND_TURN_CAR_TO_FACE_COORD: // 0x39F
        break;
    case COMMAND_IS_CRANE_LIFTING_CAR: // 0x3A0
        break;
    case COMMAND_DRAW_SPHERE: // 0x3A1
        break;
    case COMMAND_SET_CAR_STATUS: // 0x3A2
        break;
    case COMMAND_IS_CHAR_MALE: // 0x3A3
        break;
    case COMMAND_SCRIPT_NAME: // 0x3A4
        ReadTextLabelFromScript(str, 8);

        for (int i = 0; i < 8; i++)
            str[i] = tolower(str[i]);

        strncpy(m_szName, str, 8);
        return 0;
    case COMMAND_CHANGE_GARAGE_TYPE_WITH_CAR_MODEL: // 0x3A5
        break;
    case COMMAND_FIND_DRUG_PLANE_COORDINATES: // 0x3A6
        break;
    case COMMAND_SAVE_INT_TO_DEBUG_FILE: // 0x3A7
        break;
    case COMMAND_SAVE_FLOAT_TO_DEBUG_FILE: // 0x3A8
        break;
    case COMMAND_SAVE_NEWLINE_TO_DEBUG_FILE: // 0x3A9
        break;
    case COMMAND_POLICE_RADIO_MESSAGE: // 0x3AA
        break;
    case COMMAND_SET_CAR_STRONG: // 0x3AB
        break;
    case COMMAND_REMOVE_ROUTE: // 0x3AC
        break;
    case COMMAND_SWITCH_RUBBISH: // 0x3AD
        break;
    case COMMAND_REMOVE_PARTICLE_EFFECTS_IN_AREA: // 0x3AE
        break;
    case COMMAND_SWITCH_STREAMING: // 0x3AF
        break;
    case COMMAND_IS_GARAGE_OPEN: // 0x3B0
        break;
    case COMMAND_IS_GARAGE_CLOSED: // 0x3B1
        break;
    case COMMAND_START_CATALINA_HELI: // 0x3B2
        break;
    case COMMAND_CATALINA_HELI_TAKE_OFF: // 0x3B3
        break;
    case COMMAND_REMOVE_CATALINA_HELI: // 0x3B4
        break;
    case COMMAND_HAS_CATALINA_HELI_BEEN_SHOT_DOWN: // 0x3B5
        break;
    case COMMAND_SWAP_NEAREST_BUILDING_MODEL: // 0x3B6
        break;
    case COMMAND_SWITCH_WORLD_PROCESSING: // 0x3B7
        break;
    case COMMAND_REMOVE_ALL_PLAYER_WEAPONS: // 0x3B8
        break;
    case COMMAND_GRAB_CATALINA_HELI: // 0x3B9
        break;
    case COMMAND_CLEAR_AREA_OF_CARS: // 0x3BA
        break;
    case COMMAND_SET_ROTATING_GARAGE_DOOR: // 0x3BB
        break;
    case COMMAND_ADD_SPHERE: // 0x3BC
        break;
    case COMMAND_REMOVE_SPHERE: // 0x3BD
        break;
    case COMMAND_CATALINA_HELI_FLY_AWAY: // 0x3BE
        break;
    case COMMAND_SET_EVERYONE_IGNORE_PLAYER: // 0x3BF
        break;
    case COMMAND_STORE_CAR_CHAR_IS_IN_NO_SAVE: // 0x3C0
        break;
    case COMMAND_STORE_CAR_PLAYER_IS_IN_NO_SAVE: // 0x3C1
        break;
    case COMMAND_IS_PHONE_DISPLAYING_MESSAGE: // 0x3C2
        break;
    case COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_STRING: // 0x3C3
        break;
    case COMMAND_DISPLAY_ONSCREEN_COUNTER_WITH_STRING: // 0x3C4
        break;
    case COMMAND_CREATE_RANDOM_CAR_FOR_CAR_PARK: // 0x3C5
        break;
    case COMMAND_IS_COLLISION_IN_MEMORY: // 0x3C6
        break;
    case COMMAND_SET_WANTED_MULTIPLIER: // 0x3C7
        break;
    case COMMAND_SET_CAMERA_IN_FRONT_OF_PLAYER: // 0x3C8
        break;
    case COMMAND_IS_CAR_VISIBLY_DAMAGED: // 0x3C9
        break;
    case COMMAND_DOES_OBJECT_EXIST: // 0x3CA
        break;
    case COMMAND_LOAD_SCENE: // 0x3CB
        break;
    case COMMAND_ADD_STUCK_CAR_CHECK: // 0x3CC
        break;
    case COMMAND_REMOVE_STUCK_CAR_CHECK: // 0x3CD
        break;
    case COMMAND_IS_CAR_STUCK: // 0x3CE
        break;
    case COMMAND_LOAD_MISSION_AUDIO: // 0x3CF
        break;
    case COMMAND_HAS_MISSION_AUDIO_LOADED: // 0x3D0
        break;
    case COMMAND_PLAY_MISSION_AUDIO: // 0x3D1
        break;
    case COMMAND_HAS_MISSION_AUDIO_FINISHED: // 0x3D2
        break;
    case COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING: // 0x3D3
        break;
    case COMMAND_HAS_IMPORT_GARAGE_SLOT_BEEN_FILLED: // 0x3D4
        break;
    case COMMAND_CLEAR_THIS_PRINT: // 0x3D5
        break;
    case COMMAND_CLEAR_THIS_BIG_PRINT: // 0x3D6
        break;
    case COMMAND_SET_MISSION_AUDIO_POSITION: // 0x3D7
        break;
    case COMMAND_ACTIVATE_SAVE_MENU: // 0x3D8
        break;
    case COMMAND_HAS_SAVE_GAME_FINISHED: // 0x3D9
        break;
    case COMMAND_NO_SPECIAL_CAMERA_FOR_THIS_GARAGE: // 0x3DA
        break;
    case COMMAND_ADD_BLIP_FOR_PICKUP_OLD: // 0x3DB
        break;
    case COMMAND_ADD_BLIP_FOR_PICKUP: // 0x3DC
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_PICKUP: // 0x3DD
        break;
    case COMMAND_SET_PED_DENSITY_MULTIPLIER: // 0x3DE
        break;
    case COMMAND_FORCE_RANDOM_PED_TYPE: // 0x3DF
        break;
    case COMMAND_SET_TEXT_DRAW_BEFORE_FADE: // 0x3E0
        break;
    case COMMAND_GET_COLLECTABLE1S_COLLECTED: // 0x3E1
        break;
    case COMMAND_SET_CHAR_OBJ_LEAVE_ANY_CAR: // 0x3E2
        break;
    case COMMAND_SET_SPRITES_DRAW_BEFORE_FADE: // 0x3E3
        break;
    case COMMAND_SET_TEXT_RIGHT_JUSTIFY: // 0x3E4
        break;
    case COMMAND_PRINT_HELP: // 0x3E5
        break;
    case COMMAND_CLEAR_HELP: // 0x3E6
        break;
    case COMMAND_FLASH_HUD_OBJECT: // 0x3E7
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x489500
int8 CRunningScript::ProcessCommands1000To1099(int32 commandId) {
    switch (commandId) {
    case COMMAND_FLASH_RADAR_BLIP: // 0x3E8
        break;
    case COMMAND_IS_CHAR_IN_CONTROL: // 0x3E9
        break;
    case COMMAND_SET_GENERATE_CARS_AROUND_CAMERA: // 0x3EA
        break;
    case COMMAND_CLEAR_SMALL_PRINTS: // 0x3EB
        break;
    case COMMAND_HAS_MILITARY_CRANE_COLLECTED_ALL_CARS: // 0x3EC
        break;
    case COMMAND_SET_UPSIDEDOWN_CAR_NOT_DAMAGED: // 0x3ED
        break;
    case COMMAND_CAN_PLAYER_START_MISSION: // 0x3EE
        break;
    case COMMAND_MAKE_PLAYER_SAFE_FOR_CUTSCENE: // 0x3EF
        break;
    case COMMAND_USE_TEXT_COMMANDS: // 0x3F0
        break;
    case COMMAND_SET_THREAT_FOR_PED_TYPE: // 0x3F1
        break;
    case COMMAND_CLEAR_THREAT_FOR_PED_TYPE: // 0x3F2
        break;
    case COMMAND_GET_CAR_COLOURS: // 0x3F3
        break;
    case COMMAND_SET_ALL_CARS_CAN_BE_DAMAGED: // 0x3F4
        break;
    case COMMAND_SET_CAR_CAN_BE_DAMAGED: // 0x3F5
        break;
    case COMMAND_MAKE_PLAYER_UNSAFE: // 0x3F6
        break;
    case COMMAND_LOAD_COLLISION: // 0x3F7
        break;
    case COMMAND_GET_BODY_CAST_HEALTH: // 0x3F8
        break;
    case COMMAND_SET_CHARS_CHATTING: // 0x3F9
        break;
    case COMMAND_MAKE_PLAYER_SAFE: // 0x3FA
        break;
    case COMMAND_SET_CAR_STAYS_IN_CURRENT_LEVEL: // 0x3FB
        break;
    case COMMAND_SET_CHAR_STAYS_IN_CURRENT_LEVEL: // 0x3FC
        break;
    case COMMAND_SET_DRUNK_INPUT_DELAY: // 0x3FD
        break;
    case COMMAND_SET_CHAR_MONEY: // 0x3FE
        break;
    case COMMAND_INCREASE_CHAR_MONEY: // 0x3FF
        break;
    case COMMAND_GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS: // 0x400
        break;
    case COMMAND_REGISTER_LIFE_SAVED: // 0x401
        break;
    case COMMAND_REGISTER_CRIMINAL_CAUGHT: // 0x402
        break;
    case COMMAND_REGISTER_AMBULANCE_LEVEL: // 0x403
        break;
    case COMMAND_REGISTER_FIRE_EXTINGUISHED: // 0x404
        break;
    case COMMAND_TURN_PHONE_ON: // 0x405
        break;
    case COMMAND_REGISTER_LONGEST_DODO_FLIGHT: // 0x406
        break;
    case COMMAND_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS: // 0x407
        break;
    case COMMAND_SET_TOTAL_NUMBER_OF_KILL_FRENZIES: // 0x408
        break;
    case COMMAND_BLOW_UP_RC_BUGGY: // 0x409
        break;
    case COMMAND_REMOVE_CAR_FROM_CHASE: // 0x40A
        break;
    case COMMAND_IS_FRENCH_GAME: // 0x40B
        break;
    case COMMAND_IS_GERMAN_GAME: // 0x40C
        break;
    case COMMAND_CLEAR_MISSION_AUDIO: // 0x40D
        break;
    case COMMAND_SET_FADE_IN_AFTER_NEXT_ARREST: // 0x40E
        break;
    case COMMAND_SET_FADE_IN_AFTER_NEXT_DEATH: // 0x40F
        break;
    case COMMAND_SET_GANG_PED_MODEL_PREFERENCE: // 0x410
        break;
    case COMMAND_SET_CHAR_USE_PEDNODE_SEEK: // 0x411
        break;
    case COMMAND_SWITCH_VEHICLE_WEAPONS: // 0x412
        break;
    case COMMAND_SET_GET_OUT_OF_JAIL_FREE: // 0x413
        break;
    case COMMAND_SET_FREE_HEALTH_CARE: // 0x414
        break;
    case COMMAND_IS_CAR_DOOR_CLOSED: // 0x415
        break;
    case COMMAND_LOAD_AND_LAUNCH_MISSION: // 0x416
        return 0;
    case COMMAND_LOAD_AND_LAUNCH_MISSION_INTERNAL: // 0x417
    {
        CollectParameters(1);
        int32 missionId = CTheScripts::ScriptParams[0].iParam;

        // Mostly CP from StartMission @ MissionDebugModule
        if (CTheScripts::NumberOfExclusiveMissionScripts > 0) {
            if (missionId <= 65532)
                return 0;
            missionId = 0xFFFF - missionId;
        }
        CTimer::Suspend();
        int offsetToMission = CTheScripts::MultiScriptArray[missionId];
        CFileMgr::ChangeDir("\\");
        if (CGame::bMissionPackGame) {
            size_t bytesRead = 0;
            while (FrontEndMenuManager.CheckMissionPackValidMenu()) {
                CFileMgr::SetDirMyDocuments();
                sprintf(gString, "MPACK//MPACK%d//SCR.SCM", CGame::bMissionPackGame);
                FILE* file = CFileMgr::OpenFile(gString, "rb");
                if (file) {
                    CFileMgr::Seek(file, offsetToMission, 0);
                    bytesRead = CFileMgr::Read(file, &CTheScripts::ScriptSpace[200000], 69000);
                    CFileMgr::CloseFile(file);
                    if (bytesRead >= 1) {
                        CTheScripts::WipeLocalVariableMemoryForMissionScript();
                        CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[200000]);
                        script->m_bUseMissionCleanup = true;
                        script->m_bIsMission = true;
                        script->m_pBaseIP = &CTheScripts::ScriptSpace[200000];
                        CTheScripts::bAlreadyRunningAMissionScript = true;
                        CGameLogic::ClearSkip(false);
                    }
                }
                if (bytesRead >= 1) {
                    break;
                }
            }
        }
        CFileMgr::SetDir(gta_empty_string);
        if (!CGame::bMissionPackGame) {
            FILE* file = CFileMgr::OpenFile("data\\script\\main.scm", "rb");
            CFileMgr::Seek(file, offsetToMission, 0);
            CFileMgr::Read(file, &CTheScripts::ScriptSpace[200000], 69000);
            CFileMgr::CloseFile(file);

            CTheScripts::WipeLocalVariableMemoryForMissionScript();
            CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[200000]);
            script->m_bUseMissionCleanup = true;
            script->m_bIsMission = true;
            script->m_pBaseIP = &CTheScripts::ScriptSpace[200000];
            CTheScripts::bAlreadyRunningAMissionScript = true;
            CGameLogic::ClearSkip(false);
        }
        CTimer::Resume();
        return 0;
    }
    case COMMAND_SET_OBJECT_DRAW_LAST: // 0x418
        break;
    case COMMAND_GET_AMMO_IN_PLAYER_WEAPON: // 0x419
        break;
    case COMMAND_GET_AMMO_IN_CHAR_WEAPON: // 0x41A
        break;
    case COMMAND_REGISTER_KILL_FRENZY_PASSED: // 0x41B
        break;
    case COMMAND_SET_CHAR_SAY: // 0x41C
        break;
    case COMMAND_SET_NEAR_CLIP: // 0x41D
        break;
    case COMMAND_SET_RADIO_CHANNEL: // 0x41E
        break;
    case COMMAND_OVERRIDE_HOSPITAL_LEVEL: // 0x41F
        break;
    case COMMAND_OVERRIDE_POLICE_STATION_LEVEL: // 0x420
        break;
    case COMMAND_FORCE_RAIN: // 0x421
        break;
    case COMMAND_DOES_GARAGE_CONTAIN_CAR: // 0x422
        break;
    case COMMAND_SET_CAR_TRACTION: // 0x423
        break;
    case COMMAND_ARE_MEASUREMENTS_IN_METRES: // 0x424
        break;
    case COMMAND_CONVERT_METRES_TO_FEET: // 0x425
        break;
    case COMMAND_MARK_ROADS_BETWEEN_LEVELS: // 0x426
        break;
    case COMMAND_MARK_PED_ROADS_BETWEEN_LEVELS: // 0x427
        break;
    case COMMAND_SET_CAR_AVOID_LEVEL_TRANSITIONS: // 0x428
        break;
    case COMMAND_SET_CHAR_AVOID_LEVEL_TRANSITIONS: // 0x429
        break;
    case COMMAND_IS_THREAT_FOR_PED_TYPE: // 0x42A
        break;
    case COMMAND_CLEAR_AREA_OF_CHARS: // 0x42B
        break;
    case COMMAND_SET_TOTAL_NUMBER_OF_MISSIONS: // 0x42C
        break;
    case COMMAND_CONVERT_METRES_TO_FEET_INT: // 0x42D
        break;
    case COMMAND_REGISTER_FASTEST_TIME: // 0x42E
        break;
    case COMMAND_REGISTER_HIGHEST_SCORE: // 0x42F
        break;
    case COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER: // 0x430
        break;
    case COMMAND_IS_CAR_PASSENGER_SEAT_FREE: // 0x431
        break;
    case COMMAND_GET_CHAR_IN_CAR_PASSENGER_SEAT: // 0x432
        break;
    case COMMAND_SET_CHAR_IS_CHRIS_CRIMINAL: // 0x433
        break;
    case COMMAND_START_CREDITS: // 0x434
        break;
    case COMMAND_STOP_CREDITS: // 0x435
        break;
    case COMMAND_ARE_CREDITS_FINISHED: // 0x436
        break;
    case COMMAND_CREATE_SINGLE_PARTICLE: // 0x437
        break;
    case COMMAND_SET_CHAR_IGNORE_LEVEL_TRANSITIONS: // 0x438
        break;
    case COMMAND_GET_CHASE_CAR: // 0x439
        break;
    case COMMAND_START_BOAT_FOAM_ANIMATION: // 0x43A
        break;
    case COMMAND_UPDATE_BOAT_FOAM_ANIMATION: // 0x43B
        break;
    case COMMAND_SET_MUSIC_DOES_FADE: // 0x43C
        break;
    case COMMAND_SET_INTRO_IS_PLAYING: // 0x43D
        break;
    case COMMAND_SET_PLAYER_HOOKER: // 0x43E
        break;
    case COMMAND_PLAY_END_OF_GAME_TUNE: // 0x43F
        break;
    case COMMAND_STOP_END_OF_GAME_TUNE: // 0x440
        break;
    case COMMAND_GET_CAR_MODEL: // 0x441
        break;
    case COMMAND_IS_PLAYER_SITTING_IN_CAR: // 0x442
        break;
    case COMMAND_IS_PLAYER_SITTING_IN_ANY_CAR: // 0x443
        break;
    case COMMAND_SET_SCRIPT_FIRE_AUDIO: // 0x444
        break;
    case COMMAND_ARE_ANY_CAR_CHEATS_ACTIVATED: // 0x445
        break;
    case COMMAND_SET_CHAR_SUFFERS_CRITICAL_HITS: // 0x446
        break;
    case COMMAND_IS_PLAYER_LIFTING_A_PHONE: // 0x447
        break;
    case COMMAND_IS_CHAR_SITTING_IN_CAR: // 0x448
        break;
    case COMMAND_IS_CHAR_SITTING_IN_ANY_CAR: // 0x449
        break;
    case COMMAND_IS_PLAYER_ON_FOOT: // 0x44A
        break;
    case COMMAND_IS_CHAR_ON_FOOT: // 0x44B
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x48A320
int8 CRunningScript::ProcessCommands1100To1199(int32 commandId) {
    switch (commandId) {
    case COMMAND_LOAD_COLLISION_WITH_SCREEN: // 0x44C
        break;
    case COMMAND_LOAD_SPLASH_SCREEN: // 0x44D
        break;
    case COMMAND_SET_CAR_IGNORE_LEVEL_TRANSITIONS: // 0x44E
        break;
    case COMMAND_MAKE_CRAIGS_CAR_A_BIT_STRONGER: // 0x44F
        break;
    case COMMAND_SET_JAMES_CAR_ON_PATH_TO_PLAYER: // 0x450
        break;
    case COMMAND_LOAD_END_OF_GAME_TUNE: // 0x451
        break;
    case COMMAND_ENABLE_PLAYER_CONTROL_CAMERA: // 0x452
        break;
    case COMMAND_SET_OBJECT_ROTATION: // 0x453
        break;
    case COMMAND_GET_DEBUG_CAMERA_COORDINATES: // 0x454
        break;
    case COMMAND_GET_DEBUG_CAMERA_FRONT_VECTOR: // 0x455
        break;
    case COMMAND_IS_PLAYER_TARGETTING_ANY_CHAR: // 0x456
        break;
    case COMMAND_IS_PLAYER_TARGETTING_CHAR: // 0x457
        break;
    case COMMAND_IS_PLAYER_TARGETTING_OBJECT: // 0x458
        break;
    case COMMAND_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME: // 0x459
        break;
    case COMMAND_DISPLAY_TEXT_WITH_NUMBER: // 0x45A
        break;
    case COMMAND_DISPLAY_TEXT_WITH_2_NUMBERS: // 0x45B
        break;
    case COMMAND_FAIL_CURRENT_MISSION: // 0x45C
        break;
    case COMMAND_GET_CLOSEST_OBJECT_OF_TYPE: // 0x45D
        break;
    case COMMAND_PLACE_OBJECT_RELATIVE_TO_OBJECT: // 0x45E
        break;
    case COMMAND_SET_ALL_OCCUPANTS_OF_CAR_LEAVE_CAR: // 0x45F
        break;
    case COMMAND_SET_INTERPOLATION_PARAMETERS: // 0x460
        break;
    case COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING_TOWARDS_POINT: // 0x461
        break;
    case COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING_AWAY_POINT: // 0x462
        break;
    case COMMAND_GET_DEBUG_CAMERA_POINT_AT: // 0x463
        break;
    case COMMAND_ATTACH_CHAR_TO_CAR: // 0x464
        break;
    case COMMAND_DETACH_CHAR_FROM_CAR: // 0x465
        break;
    case COMMAND_SET_CAR_STAY_IN_FAST_LANE: // 0x466
        break;
    case COMMAND_CLEAR_CHAR_LAST_WEAPON_DAMAGE: // 0x467
        break;
    case COMMAND_CLEAR_CAR_LAST_WEAPON_DAMAGE: // 0x468
        break;
    case COMMAND_GET_RANDOM_COP_IN_AREA: // 0x469
        break;
    case COMMAND_GET_RANDOM_COP_IN_ZONE: // 0x46A
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_CAR: // 0x46B
        break;
    case COMMAND_GET_DRIVER_OF_CAR: // 0x46C
        break;
    case COMMAND_GET_NUMBER_OF_FOLLOWERS: // 0x46D
        break;
    case COMMAND_GIVE_REMOTE_CONTROLLED_MODEL_TO_PLAYER: // 0x46E
        break;
    case COMMAND_GET_CURRENT_PLAYER_WEAPON: // 0x46F
        break;
    case COMMAND_GET_CURRENT_CHAR_WEAPON: // 0x470
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_2D: // 0x471
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_2D: // 0x472
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_2D: // 0x473
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_3D: // 0x474
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_3D: // 0x475
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_3D: // 0x476
        break;
    case COMMAND_SET_CAR_TEMP_ACTION: // 0x477
        break;
    case COMMAND_SET_CAR_HANDBRAKE_TURN_RIGHT: // 0x478
        break;
    case COMMAND_SET_CAR_HANDBRAKE_STOP: // 0x479
        break;
    case COMMAND_IS_CHAR_ON_ANY_BIKE: // 0x47A
        break;
    case COMMAND_LOCATE_SNIPER_BULLET_2D: // 0x47B
        break;
    case COMMAND_LOCATE_SNIPER_BULLET_3D: // 0x47C
        break;
    case COMMAND_GET_NUMBER_OF_SEATS_IN_MODEL: // 0x47D
        break;
    case COMMAND_IS_PLAYER_ON_ANY_BIKE: // 0x47E
        break;
    case COMMAND_IS_CHAR_LYING_DOWN: // 0x47F
        break;
    case COMMAND_CAN_CHAR_SEE_DEAD_CHAR: // 0x480
        break;
    case COMMAND_SET_ENTER_CAR_RANGE_MULTIPLIER: // 0x481
        break;
    case COMMAND_SET_THREAT_REACTION_RANGE_MULTIPLIER: // 0x482
        break;
    case COMMAND_SET_CHAR_CEASE_ATTACK_TIMER: // 0x483
        break;
    case COMMAND_GET_REMOTE_CONTROLLED_CAR: // 0x484
        break;
    case COMMAND_IS_PC_VERSION: // 0x485
        break;
    case COMMAND_REPLAY: // 0x486
        break;
    case COMMAND_IS_REPLAY_PLAYING: // 0x487
        break;
    case COMMAND_IS_MODEL_AVAILABLE: // 0x488
        break;
    case COMMAND_SHUT_CHAR_UP: // 0x489
        break;
    case COMMAND_SET_ENABLE_RC_DETONATE: // 0x48A
        break;
    case COMMAND_SET_CAR_RANDOM_ROUTE_SEED: // 0x48B
        break;
    case COMMAND_IS_ANY_PICKUP_AT_COORDS: // 0x48C
        break;
    case COMMAND_GET_FIRST_PICKUP_COORDS: // 0x48D
        break;
    case COMMAND_GET_NEXT_PICKUP_COORDS: // 0x48E
        break;
    case COMMAND_REMOVE_ALL_CHAR_WEAPONS: // 0x48F
        break;
    case COMMAND_HAS_PLAYER_GOT_WEAPON: // 0x490
        break;
    case COMMAND_HAS_CHAR_GOT_WEAPON: // 0x491
        break;
    case COMMAND_IS_PLAYER_FACING_CHAR: // 0x492
        break;
    case COMMAND_SET_TANK_DETONATE_CARS: // 0x493
        break;
    case COMMAND_GET_POSITION_OF_ANALOGUE_STICKS: // 0x494
        break;
    case COMMAND_IS_CAR_ON_FIRE: // 0x495
        break;
    case COMMAND_IS_CAR_TYRE_BURST: // 0x496
        break;
    case COMMAND_SET_CAR_DRIVE_STRAIGHT_AHEAD: // 0x497
        break;
    case COMMAND_SET_CAR_WAIT: // 0x498
        break;
    case COMMAND_IS_PLAYER_STANDING_ON_A_VEHICLE: // 0x499
        break;
    case COMMAND_IS_PLAYER_FOOT_DOWN: // 0x49A
        break;
    case COMMAND_IS_CHAR_FOOT_DOWN: // 0x49B
        break;
    case COMMAND_INITIALISE_OBJECT_PATH: // 0x49C
        break;
    case COMMAND_START_OBJECT_ON_PATH: // 0x49D
        break;
    case COMMAND_SET_OBJECT_PATH_SPEED: // 0x49E
        break;
    case COMMAND_SET_OBJECT_PATH_POSITION: // 0x49F
        break;
    case COMMAND_GET_OBJECT_DISTANCE_ALONG_PATH: // 0x4A0
        break;
    case COMMAND_CLEAR_OBJECT_PATH: // 0x4A1
        break;
    case COMMAND_HELI_GOTO_COORDS: // 0x4A2
        break;
    case COMMAND_IS_INT_VAR_EQUAL_TO_CONSTANT: // 0x4A3
        break;
    case COMMAND_IS_INT_LVAR_EQUAL_TO_CONSTANT: // 0x4A4
        break;
    case COMMAND_GET_DEAD_CHAR_PICKUP_COORDS: // 0x4A5
        break;
    case COMMAND_CREATE_PROTECTION_PICKUP: // 0x4A6
        break;
    case COMMAND_IS_CHAR_IN_ANY_BOAT: // 0x4A7
        break;
    case COMMAND_IS_PLAYER_IN_ANY_BOAT: // 0x4A8
        break;
    case COMMAND_IS_CHAR_IN_ANY_HELI: // 0x4A9
        break;
    case COMMAND_IS_PLAYER_IN_ANY_HELI: // 0x4AA
        break;
    case COMMAND_IS_CHAR_IN_ANY_PLANE: // 0x4AB
        break;
    case COMMAND_IS_PLAYER_IN_ANY_PLANE: // 0x4AC
        break;
    case COMMAND_IS_CHAR_IN_WATER: // 0x4AD
        break;
    case COMMAND_SET_VAR_INT_TO_CONSTANT: // 0x4AE
        break;
    case COMMAND_SET_LVAR_INT_TO_CONSTANT: // 0x4AF
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x48B590
int8 CRunningScript::ProcessCommands1200To1299(int32 commandId) {
    switch (commandId) {
    case COMMAND_IS_INT_VAR_GREATER_THAN_CONSTANT: // 0x4B0
        break;
    case COMMAND_IS_INT_LVAR_GREATER_THAN_CONSTANT: // 0x4B1
        break;
    case COMMAND_IS_CONSTANT_GREATER_THAN_INT_VAR: // 0x4B2
        break;
    case COMMAND_IS_CONSTANT_GREATER_THAN_INT_LVAR: // 0x4B3
        break;
    case COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_CONSTANT: // 0x4B4
        break;
    case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_CONSTANT: // 0x4B5
        break;
    case COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_VAR: // 0x4B6
        break;
    case COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_LVAR: // 0x4B7
        break;
    case COMMAND_GET_CHAR_WEAPON_IN_SLOT: // 0x4B8
        break;
    case COMMAND_GET_CLOSEST_STRAIGHT_ROAD: // 0x4B9
        break;
    case COMMAND_SET_CAR_FORWARD_SPEED: // 0x4BA
        break;
    case COMMAND_SET_AREA_VISIBLE: // 0x4BB
        break;
    case COMMAND_SET_CUTSCENE_ANIM_TO_LOOP: // 0x4BC
        break;
    case COMMAND_MARK_CAR_AS_CONVOY_CAR: // 0x4BD
        break;
    case COMMAND_RESET_HAVOC_CAUSED_BY_PLAYER: // 0x4BE
        break;
    case COMMAND_GET_HAVOC_CAUSED_BY_PLAYER: // 0x4BF
        break;
    case COMMAND_CREATE_SCRIPT_ROADBLOCK: // 0x4C0
        break;
    case COMMAND_CLEAR_ALL_SCRIPT_ROADBLOCKS: // 0x4C1
        break;
    case COMMAND_SET_CHAR_OBJ_WALK_TO_CHAR: // 0x4C2
        break;
    case COMMAND_IS_PICKUP_IN_ZONE: // 0x4C3
        break;
    case COMMAND_GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS: // 0x4C4
        break;
    case COMMAND_HAS_CHAR_BEEN_PHOTOGRAPHED: // 0x4C5
        break;
    case COMMAND_SET_CHAR_OBJ_AIM_GUN_AT_CHAR: // 0x4C6
        break;
    case COMMAND_SWITCH_SECURITY_CAMERA: // 0x4C7
        break;
    case COMMAND_IS_CHAR_IN_FLYING_VEHICLE: // 0x4C8
        break;
    case COMMAND_IS_PLAYER_IN_FLYING_VEHICLE: // 0x4C9
        break;
    case COMMAND_HAS_SONY_CD_BEEN_READ: // 0x4CA
        break;
    case COMMAND_GET_NUMBER_OF_SONY_CDS_READ: // 0x4CB
        break;
    case COMMAND_ADD_SHORT_RANGE_BLIP_FOR_COORD_OLD: // 0x4CC
        break;
    case COMMAND_ADD_SHORT_RANGE_BLIP_FOR_COORD: // 0x4CD
        break;
    case COMMAND_ADD_SHORT_RANGE_SPRITE_BLIP_FOR_COORD: // 0x4CE
        break;
    case COMMAND_ADD_MONEY_SPENT_ON_CLOTHES: // 0x4CF
        break;
    case COMMAND_SET_HELI_ORIENTATION: // 0x4D0
        break;
    case COMMAND_CLEAR_HELI_ORIENTATION: // 0x4D1
        break;
    case COMMAND_PLANE_GOTO_COORDS: // 0x4D2
        break;
    case COMMAND_GET_NTH_CLOSEST_CAR_NODE: // 0x4D3
        break;
    case COMMAND_GET_NTH_CLOSEST_CHAR_NODE: // 0x4D4
        break;
    case COMMAND_DRAW_WEAPONSHOP_CORONA: // 0x4D5
        break;
    case COMMAND_SET_ENABLE_RC_DETONATE_ON_CONTACT: // 0x4D6
        break;
    case COMMAND_FREEZE_CHAR_POSITION: // 0x4D7
        break;
    case COMMAND_SET_CHAR_DROWNS_IN_WATER: // 0x4D8
        break;
    case COMMAND_SET_OBJECT_RECORDS_COLLISIONS: // 0x4D9
        break;
    case COMMAND_HAS_OBJECT_COLLIDED_WITH_ANYTHING: // 0x4DA
        break;
    case COMMAND_REMOVE_RC_BUGGY: // 0x4DB
        break;
    case COMMAND_HAS_PHOTOGRAPH_BEEN_TAKEN: // 0x4DC
        break;
    case COMMAND_GET_CHAR_ARMOUR: // 0x4DD
        break;
    case COMMAND_SET_CHAR_ARMOUR: // 0x4DE
        break;
    case COMMAND_SET_HELI_STABILISER: // 0x4DF
        break;
    case COMMAND_SET_CAR_STRAIGHT_LINE_DISTANCE: // 0x4E0
        break;
    case COMMAND_POP_CAR_BOOT: // 0x4E1
        break;
    case COMMAND_SHUT_PLAYER_UP: // 0x4E2
        break;
    case COMMAND_SET_PLAYER_MOOD: // 0x4E3
        break;
    case COMMAND_REQUEST_COLLISION: // 0x4E4
        break;
    case COMMAND_LOCATE_OBJECT_2D: // 0x4E5
        break;
    case COMMAND_LOCATE_OBJECT_3D: // 0x4E6
        break;
    case COMMAND_IS_OBJECT_IN_WATER: // 0x4E7
        break;
    case COMMAND_SET_CHAR_OBJ_STEAL_ANY_CAR_EVEN_MISSION_CAR: // 0x4E8
        break;
    case COMMAND_IS_OBJECT_IN_AREA_2D: // 0x4E9
        break;
    case COMMAND_IS_OBJECT_IN_AREA_3D: // 0x4EA
        break;
    case COMMAND_TASK_TOGGLE_DUCK: // 0x4EB
        break;
    case COMMAND_SET_ZONE_CIVILIAN_CAR_INFO: // 0x4EC
        break;
    case COMMAND_REQUEST_ANIMATION: // 0x4ED
        break;
    case COMMAND_HAS_ANIMATION_LOADED: // 0x4EE
        break;
    case COMMAND_REMOVE_ANIMATION: // 0x4EF
        break;
    case COMMAND_IS_CHAR_WAITING_FOR_WORLD_COLLISION: // 0x4F0
        break;
    case COMMAND_IS_CAR_WAITING_FOR_WORLD_COLLISION: // 0x4F1
        break;
    case COMMAND_IS_OBJECT_WAITING_FOR_WORLD_COLLISION: // 0x4F2
        break;
    case COMMAND_SET_CHAR_SHUFFLE_INTO_DRIVERS_SEAT: // 0x4F3
        break;
    case COMMAND_ATTACH_CHAR_TO_OBJECT: // 0x4F4
        break;
    case COMMAND_SET_CHAR_AS_PLAYER_FRIEND: // 0x4F5
        break;
    case COMMAND_DISPLAY_NTH_ONSCREEN_COUNTER: // 0x4F6
        break;
    case COMMAND_DISPLAY_NTH_ONSCREEN_COUNTER_WITH_STRING: // 0x4F7
        break;
    case COMMAND_ADD_SET_PIECE: // 0x4F8
        break;
    case COMMAND_SET_EXTRA_COLOURS: // 0x4F9
        break;
    case COMMAND_CLEAR_EXTRA_COLOURS: // 0x4FA
        break;
    case COMMAND_CLOSE_CAR_BOOT: // 0x4FB
        break;
    case COMMAND_GET_WHEELIE_STATS: // 0x4FC
        break;
    case COMMAND_DISARM_CHAR: // 0x4FD
        break;
    case COMMAND_BURST_CAR_TYRE: // 0x4FE
        break;
    case COMMAND_IS_CHAR_OBJ_NO_OBJ: // 0x4FF
        break;
    case COMMAND_IS_PLAYER_WEARING: // 0x500
        break;
    case COMMAND_SET_PLAYER_CAN_DO_DRIVE_BY: // 0x501
        break;
    case COMMAND_SET_CHAR_OBJ_SPRINT_TO_COORD: // 0x502
        break;
    case COMMAND_CREATE_SWAT_ROPE: // 0x503
        break;
    case COMMAND_SET_FIRST_PERSON_CONTROL_CAMERA: // 0x504
        break;
    case COMMAND_GET_NEAREST_TYRE_TO_POINT: // 0x505
        break;
    case COMMAND_SET_CAR_MODEL_COMPONENTS: // 0x506
        break;
    case COMMAND_SWITCH_LIFT_CAMERA: // 0x507
        break;
    case COMMAND_CLOSE_ALL_CAR_DOORS: // 0x508
        break;
    case COMMAND_GET_DISTANCE_BETWEEN_COORDS_2D: // 0x509
        break;
    case COMMAND_GET_DISTANCE_BETWEEN_COORDS_3D: // 0x50A
        break;
    case COMMAND_POP_CAR_BOOT_USING_PHYSICS: // 0x50B
        break;
    case COMMAND_SET_FIRST_PERSON_WEAPON_CAMERA: // 0x50C
        break;
    case COMMAND_IS_CHAR_LEAVING_VEHICLE_TO_DIE: // 0x50D
        break;
    case COMMAND_SORT_OUT_OBJECT_COLLISION_WITH_CAR: // 0x50E
        break;
    case COMMAND_GET_MAX_WANTED_LEVEL: // 0x50F
        break;
    case COMMAND_IS_CHAR_WANDER_PATH_CLEAR: // 0x510
        break;
    case COMMAND_PRINT_HELP_WITH_NUMBER: // 0x511
        break;
    case COMMAND_PRINT_HELP_FOREVER: // 0x512
        break;
    case COMMAND_PRINT_HELP_FOREVER_WITH_NUMBER: // 0x513
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x48CDD0
int8 CRunningScript::ProcessCommands1300To1399(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_CHAR_CAN_BE_DAMAGED_BY_MEMBERS_OF_GANG: // 0x514
        break;
    case COMMAND_LOAD_AND_LAUNCH_MISSION_EXCLUSIVE: // 0x515
        break;
    case COMMAND_IS_MISSION_AUDIO_PLAYING: // 0x516
        break;
    case COMMAND_CREATE_LOCKED_PROPERTY_PICKUP: // 0x517
        break;
    case COMMAND_CREATE_FORSALE_PROPERTY_PICKUP: // 0x518
        break;
    case COMMAND_FREEZE_CAR_POSITION: // 0x519
        break;
    case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CHAR: // 0x51A
        break;
    case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CAR: // 0x51B
        break;
    case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_CHAR: // 0x51C
        break;
    case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_CAR: // 0x51D
        break;
    case COMMAND_GET_RADIO_CHANNEL: // 0x51E
        break;
    case COMMAND_DISPLAY_TEXT_WITH_3_NUMBERS: // 0x51F
        break;
    case COMMAND_IS_CAR_DROWNING_IN_WATER: // 0x520
        break;
    case COMMAND_IS_CHAR_DROWNING_IN_WATER: // 0x521
        break;
    case COMMAND_DISABLE_CUTSCENE_SHADOWS: // 0x522
        break;
    case COMMAND_HAS_GLASS_BEEN_SHATTERED_NEARBY: // 0x523
        break;
    case COMMAND_ATTACH_CUTSCENE_OBJECT_TO_BONE: // 0x524
        break;
    case COMMAND_ATTACH_CUTSCENE_OBJECT_TO_COMPONENT: // 0x525
        break;
    case COMMAND_SET_CHAR_STAY_IN_CAR_WHEN_JACKED: // 0x526
        break;
    case COMMAND_IS_MISSION_AUDIO_LOADING: // 0x527
        break;
    case COMMAND_ADD_MONEY_SPENT_ON_WEAPONS: // 0x528
        break;
    case COMMAND_ADD_MONEY_SPENT_ON_PROPERTY: // 0x529
        break;
    case COMMAND_ADD_MONEY_SPENT_ON_AUTO_PAINTING: // 0x52A
        break;
    case COMMAND_SET_CHAR_ANSWERING_MOBILE: // 0x52B
        break;
    case COMMAND_SET_PLAYER_DRUNKENNESS: // 0x52C
        break;
    case COMMAND_GET_PLAYER_DRUNKENNESS: // 0x52D
        break;
    case COMMAND_SET_PLAYER_DRUG_LEVEL: // 0x52E
        break;
    case COMMAND_GET_PLAYER_DRUG_LEVEL: // 0x52F
        break;
    case COMMAND_ADD_LOAN_SHARK_VISITS: // 0x530
        break;
    case COMMAND_ADD_STORES_KNOCKED_OFF: // 0x531
        break;
    case COMMAND_ADD_MOVIE_STUNTS: // 0x532
        break;
    case COMMAND_ADD_NUMBER_OF_ASSASSINATIONS: // 0x533
        break;
    case COMMAND_ADD_PIZZAS_DELIVERED: // 0x534
        break;
    case COMMAND_ADD_GARBAGE_PICKUPS: // 0x535
        break;
    case COMMAND_ADD_ICE_CREAMS_SOLD: // 0x536
        break;
    case COMMAND_SET_TOP_SHOOTING_RANGE_SCORE: // 0x537
        break;
    case COMMAND_ADD_SHOOTING_RANGE_RANK: // 0x538
        break;
    case COMMAND_ADD_MONEY_SPENT_ON_GAMBLING: // 0x539
        break;
    case COMMAND_ADD_MONEY_WON_ON_GAMBLING: // 0x53A
        break;
    case COMMAND_SET_LARGEST_GAMBLING_WIN: // 0x53B
        break;
    case COMMAND_SET_CHAR_IN_PLAYERS_GROUP_CAN_FIGHT: // 0x53C
        break;
    case COMMAND_CLEAR_CHAR_WAIT_STATE: // 0x53D
        break;
    case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_AREA_NO_SAVE: // 0x53E
        break;
    case COMMAND_SET_CAN_BURST_CAR_TYRES: // 0x53F
        break;
    case COMMAND_SET_PLAYER_AUTO_AIM: // 0x540
        break;
    case COMMAND_FIRE_HUNTER_GUN: // 0x541
        break;
    case COMMAND_SET_PROPERTY_AS_OWNED: // 0x542
        break;
    case COMMAND_ADD_BLOOD_RING_KILLS: // 0x543
        break;
    case COMMAND_SET_LONGEST_TIME_IN_BLOOD_RING: // 0x544
        break;
    case COMMAND_REMOVE_EVERYTHING_FOR_HUGE_CUTSCENE: // 0x545
        break;
    case COMMAND_IS_PLAYER_TOUCHING_VEHICLE: // 0x546
        break;
    case COMMAND_IS_CHAR_TOUCHING_VEHICLE: // 0x547
        break;
    case COMMAND_CHECK_FOR_PED_MODEL_AROUND_PLAYER: // 0x548
        break;
    case COMMAND_CLEAR_CHAR_FOLLOW_PATH: // 0x549
        break;
    case COMMAND_SET_CHAR_CAN_BE_SHOT_IN_VEHICLE: // 0x54A
        break;
    case COMMAND_ATTACH_CUTSCENE_OBJECT_TO_VEHICLE: // 0x54B
        break;
    case COMMAND_LOAD_MISSION_TEXT: // 0x54C
        break;
    case COMMAND_SET_TONIGHTS_EVENT: // 0x54D
        break;
    case COMMAND_CLEAR_CHAR_LAST_DAMAGE_ENTITY: // 0x54E
        break;
    case COMMAND_CLEAR_CAR_LAST_DAMAGE_ENTITY: // 0x54F
        break;
    case COMMAND_FREEZE_OBJECT_POSITION: // 0x550
        break;
    case COMMAND_SET_PLAYER_HAS_MET_DEBBIE_HARRY: // 0x551
        break;
    case COMMAND_SET_RIOT_INTENSITY: // 0x552
        break;
    case COMMAND_IS_CAR_IN_ANGLED_AREA_2D: // 0x553
        break;
    case COMMAND_IS_CAR_IN_ANGLED_AREA_3D: // 0x554
        break;
    case COMMAND_REMOVE_WEAPON_FROM_CHAR: // 0x555
        break;
    case COMMAND_SET_UP_TAXI_SHORTCUT: // 0x556
        break;
    case COMMAND_CLEAR_TAXI_SHORTCUT: // 0x557
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_CAR_ON_FOOT: // 0x558
        break;
    case COMMAND_GET_CLOSEST_WATER_NODE: // 0x559
        break;
    case COMMAND_ADD_PORN_LEAFLET_TO_RUBBISH: // 0x55A
        break;
    case COMMAND_CREATE_CLOTHES_PICKUP: // 0x55B
        break;
    case COMMAND_CHANGE_BLIP_THRESHOLD: // 0x55C
        break;
    case COMMAND_MAKE_PLAYER_FIRE_PROOF: // 0x55D
        break;
    case COMMAND_INCREASE_PLAYER_MAX_HEALTH: // 0x55E
        break;
    case COMMAND_INCREASE_PLAYER_MAX_ARMOUR: // 0x55F
        break;
    case COMMAND_CREATE_RANDOM_CHAR_AS_DRIVER: // 0x560
        break;
    case COMMAND_CREATE_RANDOM_CHAR_AS_PASSENGER: // 0x561
        break;
    case COMMAND_SET_CHAR_IGNORE_THREATS_BEHIND_OBJECTS: // 0x562
        break;
    case COMMAND_ENSURE_PLAYER_HAS_DRIVE_BY_WEAPON: // 0x563
        break;
    case COMMAND_MAKE_HELI_COME_CRASHING_DOWN: // 0x564
        break;
    case COMMAND_ADD_EXPLOSION_NO_SOUND: // 0x565
        break;
    case COMMAND_SET_OBJECT_AREA_VISIBLE: // 0x566
        break;
    case COMMAND_WAS_VEHICLE_EVER_POLICE: // 0x567
        break;
    case COMMAND_SET_CHAR_NEVER_TARGETTED: // 0x568
        break;
    case COMMAND_LOAD_UNCOMPRESSED_ANIM: // 0x569
        break;
    case COMMAND_WAS_CUTSCENE_SKIPPED: // 0x56A
        break;
    case COMMAND_SET_CHAR_CROUCH_WHEN_THREATENED: // 0x56B
        break;
    case COMMAND_IS_CHAR_IN_ANY_POLICE_VEHICLE: // 0x56C
        break;
    case COMMAND_DOES_CHAR_EXIST: // 0x56D
        break;
    case COMMAND_DOES_VEHICLE_EXIST: // 0x56E
        break;
    case COMMAND_ADD_SHORT_RANGE_BLIP_FOR_CONTACT_POINT: // 0x56F
        break;
    case COMMAND_ADD_SHORT_RANGE_SPRITE_BLIP_FOR_CONTACT_POINT: // 0x570
        break;
    case COMMAND_IS_CHAR_STUCK: // 0x571
        break;
    case COMMAND_SET_ALL_TAXIS_HAVE_NITRO: // 0x572
    {
        /*
        CollectParameters(1);
        if (ScriptParams[0])
            CCheat::EnableLegitimateCheat(CHEAT_ALL_TAXIS_NITRO);
        else
            CCheat::IsActive(CHEAT_ALL_TAXIS_NITRO) = false;
        */
        break;
    }
    case COMMAND_SET_CHAR_STOP_SHOOT_DONT_SEEK_ENTITY: // 0x573
        break;
    case COMMAND_FREEZE_CAR_POSITION_AND_DONT_LOAD_COLLISION: // 0x574
        break;
    case COMMAND_FREEZE_CHAR_POSITION_AND_DONT_LOAD_COLLISION: // 0x575
        break;
    case COMMAND_FREEZE_OBJECT_POSITION_AND_DONT_LOAD_COLLISION: // 0x576
        break;
    case COMMAND_SET_FADE_AND_JUMPCUT_AFTER_RC_EXPLOSION: // 0x577
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x48EAA0
int8 CRunningScript::ProcessCommands1400To1499(int32 commandId) {
    switch (commandId) {
    case COMMAND_REGISTER_VIGILANTE_LEVEL: // 0x578
        break;
    case COMMAND_CLEAR_ALL_CHAR_ANIMS: // 0x579
        break;
    case COMMAND_SET_MAXIMUM_NUMBER_OF_CARS_IN_GARAGE: // 0x57A
        break;
    case COMMAND_WANTED_STARS_ARE_FLASHING: // 0x57B
        break;
    case COMMAND_SET_ALLOW_HURRICANES: // 0x57C
        break;
    case COMMAND_PLAY_ANNOUNCEMENT: // 0x57D
        break;
    case COMMAND_SET_PLAYER_IS_IN_STADIUM: // 0x57E
        break;
    case COMMAND_GET_BUS_FARES_COLLECTED_BY_PLAYER: // 0x57F
        break;
    case COMMAND_SET_CHAR_OBJ_BUY_ICE_CREAM: // 0x580
        break;
    case COMMAND_DISPLAY_RADAR: // 0x581
        break;
    case COMMAND_REGISTER_BEST_POSITION: // 0x582
        break;
    case COMMAND_IS_PLAYER_IN_INFO_ZONE: // 0x583
        break;
    case COMMAND_CLEAR_CHAR_ICE_CREAM_PURCHASE: // 0x584
        break;
    case COMMAND_IS_IN_CAR_FIRE_BUTTON_PRESSED: // 0x585
        break;
    case COMMAND_HAS_CHAR_ATTEMPTED_ATTRACTOR: // 0x586
        break;
    case COMMAND_SET_LOAD_COLLISION_FOR_CAR_FLAG: // 0x587
        break;
    case COMMAND_SET_LOAD_COLLISION_FOR_CHAR_FLAG: // 0x588
        break;
    case COMMAND_SET_LOAD_COLLISION_FOR_OBJECT_FLAG: // 0x589
        break;
    case COMMAND_ADD_BIG_GUN_FLASH: // 0x58A
        break;
    case COMMAND_HAS_CHAR_BOUGHT_ICE_CREAM: // 0x58B
        break;
    case COMMAND_GET_PROGRESS_PERCENTAGE: // 0x58C
        break;
    case COMMAND_SET_SHORTCUT_PICKUP_POINT: // 0x58D
        break;
    case COMMAND_SET_SHORTCUT_DROPOFF_POINT_FOR_MISSION: // 0x58E
        break;
    case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_AREA: // 0x58F
        break;
    case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_ZONE: // 0x590
        break;
    case COMMAND_UNLOCK_ALL_CAR_DOORS_IN_AREA: // 0x591
        break;
    case COMMAND_SET_GANG_ATTACK_PLAYER_WITH_COPS: // 0x592
        break;
    case COMMAND_SET_CHAR_FRIGHTENED_IN_JACKED_CAR: // 0x593
        break;
    case COMMAND_SET_VEHICLE_TO_FADE_IN: // 0x594
        break;
    case COMMAND_REGISTER_ODDJOB_MISSION_PASSED: // 0x595
        break;
    case COMMAND_IS_PLAYER_IN_SHORTCUT_TAXI: // 0x596
        break;
    case COMMAND_IS_CHAR_DUCKING: // 0x597
        break;
    case COMMAND_CREATE_DUST_EFFECT_FOR_CUTSCENE_HELI: // 0x598
        break;
    case COMMAND_REGISTER_FIRE_LEVEL: // 0x599
        break;
    case COMMAND_IS_AUSTRALIAN_GAME: // 0x59A
        break;
    case COMMAND_DISARM_CAR_BOMB: // 0x59B
        break;
    case COMMAND_SET_ONSCREEN_COUNTER_FLASH_WHEN_FIRST_DISPLAYED: // 0x59C
        break;
    case COMMAND_SHUFFLE_CARD_DECKS: // 0x59D
        break;
    case COMMAND_FETCH_NEXT_CARD: // 0x59E
        break;
    case COMMAND_GET_OBJECT_VELOCITY: // 0x59F
        break;
    case COMMAND_IS_DEBUG_CAMERA_ON: // 0x5A0
        break;
    case COMMAND_ADD_TO_OBJECT_ROTATION_VELOCITY: // 0x5A1
        break;
    case COMMAND_SET_OBJECT_ROTATION_VELOCITY: // 0x5A2
        break;
    case COMMAND_IS_OBJECT_STATIC: // 0x5A3
        break;
    case COMMAND_GET_ANGLE_BETWEEN_2D_VECTORS: // 0x5A4
        break;
    case COMMAND_DO_2D_RECTANGLES_COLLIDE: // 0x5A5
        break;
    case COMMAND_GET_OBJECT_ROTATION_VELOCITY: // 0x5A6
        break;
    case COMMAND_ADD_VELOCITY_RELATIVE_TO_OBJECT_VELOCITY: // 0x5A7
        break;
    case COMMAND_GET_OBJECT_SPEED: // 0x5A8
        break;
    case COMMAND_SET_VAR_TEXT_LABEL: // 0x5A9
        break;
    case COMMAND_SET_LVAR_TEXT_LABEL: // 0x5AA
        break;
    case COMMAND_VAR_TEXT_LABEL: // 0x5AB
        break;
    case COMMAND_LVAR_TEXT_LABEL: // 0x5AC
        break;
    case COMMAND_IS_VAR_TEXT_LABEL_EQUAL_TO_TEXT_LABEL: // 0x5AD
        break;
    case COMMAND_IS_LVAR_TEXT_LABEL_EQUAL_TO_TEXT_LABEL: // 0x5AE
        break;
    case COMMAND_DO_2D_LINES_INTERSECT: // 0x5AF
        break;
    case COMMAND_GET_2D_LINES_INTERSECT_POINT: // 0x5B0
        break;
    case COMMAND_IS_2D_POINT_IN_TRIANGLE: // 0x5B1
        break;
    case COMMAND_IS_2D_POINT_IN_RECTANGLE_ON_LEFT_SIDE_OF_LINE: // 0x5B2
        break;
    case COMMAND_IS_2D_POINT_ON_LEFT_SIDE_OF_2D_LINE: // 0x5B3
        break;
    case COMMAND_CHAR_LOOK_AT_OBJECT_ALWAYS: // 0x5B4
        break;
    case COMMAND_APPLY_COLLISION_ON_OBJECT: // 0x5B5
        break;
    case COMMAND_SAVE_STRING_TO_DEBUG_FILE: // 0x5B6
        break;
    case COMMAND_TASK_PLAYER_ON_FOOT: // 0x5B7
        break;
    case COMMAND_TASK_PLAYER_IN_CAR: // 0x5B8
        break;
    case COMMAND_TASK_PAUSE: // 0x5B9
        break;
    case COMMAND_TASK_STAND_STILL: // 0x5BA
        break;
    case COMMAND_TASK_FALL_AND_GET_UP: // 0x5BB
        break;
    case COMMAND_TASK_JUMP: // 0x5BC
        break;
    case COMMAND_TASK_TIRED: // 0x5BD
        break;
    case COMMAND_TASK_DIE: // 0x5BE
        break;
    case COMMAND_TASK_LOOK_AT_CHAR: // 0x5BF
        break;
    case COMMAND_TASK_LOOK_AT_VEHICLE: // 0x5C0
        break;
    case COMMAND_TASK_SAY: // 0x5C1
        break;
    case COMMAND_TASK_SHAKE_FIST: // 0x5C2
        break;
    case COMMAND_TASK_COWER: // 0x5C3
        break;
    case COMMAND_TASK_HANDS_UP: // 0x5C4
        break;
    case COMMAND_TASK_DUCK: // 0x5C5
        break;
    case COMMAND_TASK_DETONATE: // 0x5C6
        break;
    case COMMAND_TASK_USE_ATM: // 0x5C7
        break;
    case COMMAND_TASK_SCRATCH_HEAD: // 0x5C8
        break;
    case COMMAND_TASK_LOOK_ABOUT: // 0x5C9
        break;
    case COMMAND_TASK_ENTER_CAR_AS_PASSENGER: // 0x5CA
        break;
    case COMMAND_TASK_ENTER_CAR_AS_DRIVER: // 0x5CB
        break;
    case COMMAND_TASK_STEAL_CAR: // 0x5CC
        break;
    case COMMAND_TASK_LEAVE_CAR: // 0x5CD
        break;
    case COMMAND_TASK_LEAVE_CAR_AND_DIE: // 0x5CE
        break;
    case COMMAND_TASK_LEAVE_CAR_AND_FLEE: // 0x5CF
        break;
    case COMMAND_TASK_CAR_DRIVE: // 0x5D0
        break;
    case COMMAND_TASK_CAR_DRIVE_TO_COORD: // 0x5D1
        break;
    case COMMAND_TASK_CAR_DRIVE_WANDER: // 0x5D2
        break;
    case COMMAND_TASK_GO_STRAIGHT_TO_COORD: // 0x5D3
        break;
    case COMMAND_TASK_ACHIEVE_HEADING: // 0x5D4
        break;
    case COMMAND_SET_CHAR_IN_DISGUISE: // 0x5D5
        break;
    case COMMAND_FLUSH_ROUTE: // 0x5D6
        break;
    case COMMAND_EXTEND_ROUTE: // 0x5D7
        break;
    case COMMAND_TASK_FOLLOW_POINT_ROUTE: // 0x5D8
        break;
    case COMMAND_TASK_GOTO_CHAR: // 0x5D9
        break;
    case COMMAND_TASK_FLEE_POINT: // 0x5DA
        break;
    case COMMAND_TASK_FLEE_CHAR: // 0x5DB
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x490DB0
int8 CRunningScript::ProcessCommands1500To1599(int32 commandId) {
    switch (commandId) {
    case COMMAND_TASK_SMART_FLEE_POINT: // 0x5DC
        break;
    case COMMAND_TASK_SMART_FLEE_CHAR: // 0x5DD
        break;
    case COMMAND_TASK_WANDER_STANDARD: // 0x5DE
        break;
    case COMMAND_TASK_WANDER_COP: // 0x5DF
        break;
    case COMMAND_TASK_WANDER_CRIMINAL: // 0x5E0
        break;
    case COMMAND_TASK_FOLLOW_LEADER_IN_FORMATION: // 0x5E1
        break;
    case COMMAND_TASK_KILL_CHAR_ON_FOOT: // 0x5E2
        break;
    case COMMAND_START_ADDING_STUNT_POINTS: // 0x5E3
        break;
    case COMMAND_ADD_STUNT_POINT: // 0x5E4
        break;
    case COMMAND_START_PLAYING_STUNT: // 0x5E5
        break;
    case COMMAND_HAS_STUNT_ENDED: // 0x5E6
        break;
    case COMMAND_HAS_STUNT_FAILED: // 0x5E7
        break;
    case COMMAND_START_RECORDING_STUNT: // 0x5E8
        break;
    case COMMAND_START_RECORDING_CAR: // 0x5E9
        break;
    case COMMAND_STOP_RECORDING_CARS: // 0x5EA
        break;
    case COMMAND_START_PLAYBACK_RECORDED_CAR: // 0x5EB
        break;
    case COMMAND_STOP_PLAYBACK_RECORDED_CAR: // 0x5EC
        break;
    case COMMAND_PAUSE_PLAYBACK_RECORDED_CAR: // 0x5ED
        break;
    case COMMAND_UNPAUSE_PLAYBACK_RECORDED_CAR: // 0x5EE
        break;
    case COMMAND_SET_CAR_PROTECT_CAR_REAR: // 0x5EF
        break;
    case COMMAND_SET_CAR_PROTECT_CAR_FRONT: // 0x5F0
        break;
    case COMMAND_SET_CAR_ESCORT_CAR_LEFT: // 0x5F1
        break;
    case COMMAND_SET_CAR_ESCORT_CAR_RIGHT: // 0x5F2
        break;
    case COMMAND_SET_CAR_ESCORT_CAR_REAR: // 0x5F3
        break;
    case COMMAND_SET_CAR_ESCORT_CAR_FRONT: // 0x5F4
        break;
    case COMMAND_TASK_FOLLOW_PATH_NODES_TO_COORD: // 0x5F5
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_2D: // 0x5F6
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_ON_FOOT_2D: // 0x5F7
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_IN_CAR_2D: // 0x5F8
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_2D: // 0x5F9
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_ON_FOOT_2D: // 0x5FA
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_IN_CAR_2D: // 0x5FB
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_3D: // 0x5FC
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_ON_FOOT_3D: // 0x5FD
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_IN_CAR_3D: // 0x5FE
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_3D: // 0x5FF
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_ON_FOOT_3D: // 0x600
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_IN_CAR_3D: // 0x601
        break;
    case COMMAND_IS_CHAR_IN_TAXI: // 0x602
        break;
    case COMMAND_TASK_GO_TO_COORD_ANY_MEANS: // 0x603
        break;
    case COMMAND_GET_HEADING_FROM_VECTOR_2D: // 0x604
        break;
    case COMMAND_TASK_PLAY_ANIM: // 0x605
        break;
    case COMMAND_LOAD_PATH_NODES_IN_AREA: // 0x606
        break;
    case COMMAND_RELEASE_PATH_NODES: // 0x607
        break;
    case COMMAND_HAVE_PATH_NODES_BEEN_LOADED: // 0x608
        break;
    case COMMAND_LOAD_ALL_PATH_NODES_FOR_DEBUG: // 0x609
        break;
    case COMMAND_LOAD_CHAR_DECISION_MAKER: // 0x60A
        break;
    case COMMAND_SET_CHAR_DECISION_MAKER: // 0x60B
        break;
    case COMMAND_CLEAR_ALL_DECISION_MAKERS: // 0x60C
        break;
    case COMMAND_SET_TEXT_DROPSHADOW: // 0x60D
        break;
    case COMMAND_IS_PLAYBACK_GOING_ON_FOR_CAR: // 0x60E
        break;
    case COMMAND_SET_SENSE_RANGE: // 0x60F
        break;
    case COMMAND_SET_HEARING_RANGE: // 0x610
        break;
    case COMMAND_IS_CHAR_PLAYING_ANIM: // 0x611
        break;
    case COMMAND_SET_CHAR_ANIM_PLAYING_FLAG: // 0x612
        break;
    case COMMAND_GET_CHAR_ANIM_CURRENT_TIME: // 0x613
        break;
    case COMMAND_SET_CHAR_ANIM_CURRENT_TIME: // 0x614
        break;
    case COMMAND_OPEN_SEQUENCE_TASK: // 0x615
        break;
    case COMMAND_CLOSE_SEQUENCE_TASK: // 0x616
        break;
    case COMMAND_SCRIPT_EVENT: // 0x617
        break;
    case COMMAND_PERFORM_SEQUENCE_TASK: // 0x618
        break;
    case COMMAND_SET_CHAR_COLLISION: // 0x619
        break;
    case COMMAND_GET_CHAR_ANIM_TOTAL_TIME: // 0x61A
        break;
    case COMMAND_CLEAR_SEQUENCE_TASK: // 0x61B
        break;
    case COMMAND_CLEAR_ALL_SEQUENCE_TASKS: // 0x61C
        break;
    case COMMAND_ADD_ATTRACTOR: // 0x61D
        break;
    case COMMAND_CLEAR_ATTRACTOR: // 0x61E
        break;
    case COMMAND_CLEAR_ALL_ATTRACTORS: // 0x61F
        break;
    case COMMAND_TASK_PLAY_ANIM_FOR_TIME: // 0x620
        break;
    case COMMAND_CREATE_CHAR_AT_ATTRACTOR: // 0x621
        break;
    case COMMAND_TASK_LEAVE_CAR_IMMEDIATELY: // 0x622
        break;
    case COMMAND_INCREMENT_INT_STAT: // 0x623
        break;
    case COMMAND_INCREMENT_FLOAT_STAT: // 0x624
        break;
    case COMMAND_DECREMENT_INT_STAT: // 0x625
        break;
    case COMMAND_DECREMENT_FLOAT_STAT: // 0x626
        break;
    case COMMAND_REGISTER_INT_STAT: // 0x627
        break;
    case COMMAND_REGISTER_FLOAT_STAT: // 0x628
        break;
    case COMMAND_SET_INT_STAT: // 0x629
        break;
    case COMMAND_SET_FLOAT_STAT: // 0x62A
        break;
    case COMMAND_GET_ATTEMPTS_FOR_THIS_MISSION: // 0x62B
        break;
    case COMMAND_REGISTER_THIS_MISSION_HAS_BEEN_ATTEMPTED: // 0x62C
        break;
    case COMMAND_REGISTER_THIS_MISSION_HAS_BEEN_PASSED: // 0x62D
        break;
    case COMMAND_GET_SCRIPT_TASK_STATUS: // 0x62E
        break;
    case COMMAND_CREATE_GROUP: // 0x62F
        break;
    case COMMAND_SET_GROUP_LEADER: // 0x630
        break;
    case COMMAND_SET_GROUP_MEMBER: // 0x631
        break;
    case COMMAND_REMOVE_GROUP: // 0x632
        break;
    case COMMAND_TASK_LEAVE_ANY_CAR: // 0x633
        break;
    case COMMAND_TASK_KILL_CHAR_ON_FOOT_WHILE_DUCKING: // 0x634
        break;
    case COMMAND_TASK_AIM_GUN_AT_CHAR: // 0x635
        break;
    case COMMAND_TASK_SIDE_STEP_AND_SHOOT: // 0x636
        break;
    case COMMAND_TASK_GO_TO_COORD_WHILE_SHOOTING: // 0x637
        break;
    case COMMAND_TASK_STAY_IN_SAME_PLACE: // 0x638
        break;
    case COMMAND_TASK_TURN_CHAR_TO_FACE_CHAR: // 0x639
        break;
    case COMMAND_OPEN_THREAT_LIST: // 0x63A
        break;
    case COMMAND_CLOSE_THREAT_LIST: // 0x63B
        break;
    case COMMAND_SET_PEDMODEL_AS_THREAT: // 0x63C
        break;
    case COMMAND_SET_CHAR_THREAT_LIST: // 0x63D
        break;
    case COMMAND_REMOVE_THREAT_LIST: // 0x63E
        break;
    case COMMAND_PERFORM_SEQUENCE_TASK_REPEATEDLY: // 0x63F
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x493FE0
int8 CRunningScript::ProcessCommands1600To1699(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_PEDTYPE_AS_THREAT: // 0x640
        break;
    case COMMAND_CLEAR_CHAR_THREATS: // 0x641
        break;
    case COMMAND_IS_CHAR_AT_SCRIPTED_ATTRACTOR: // 0x642
        break;
    case COMMAND_SET_SEQUENCE_TO_REPEAT: // 0x643
        break;
    case COMMAND_CREATE_PED_GENERATOR: // 0x644
        break;
    case COMMAND_SWITCH_PED_GENERATOR: // 0x645
        break;
    case COMMAND_GET_SEQUENCE_PROGRESS: // 0x646
        break;
    case COMMAND_CLEAR_LOOK_AT: // 0x647
        break;
    case COMMAND_SET_FOLLOW_NODE_THRESHOLD_DISTANCE: // 0x648
        break;
    case COMMAND_SET_CHAR_ZONE_DISTANCE: // 0x649
        break;
    case COMMAND_ADD_PEDMODEL_AS_ATTRACTOR_USER: // 0x64A
        break;
    case COMMAND_CREATE_FX_SYSTEM: // 0x64B
        break;
    case COMMAND_PLAY_FX_SYSTEM: // 0x64C
        break;
    case COMMAND_PAUSE_FX_SYSTEM: // 0x64D
        break;
    case COMMAND_STOP_FX_SYSTEM: // 0x64E
        break;
    case COMMAND_PLAY_AND_KILL_FX_SYSTEM: // 0x64F
        break;
    case COMMAND_KILL_FX_SYSTEM: // 0x650
        break;
    case COMMAND_CREATE_FX_SYSTEM_WITH_DIRECTION: // 0x651
        break;
    case COMMAND_GET_INT_STAT: // 0x652
        break;
    case COMMAND_GET_FLOAT_STAT: // 0x653
        break;
    case COMMAND_SET_OBJECT_RENDER_SCORCHED: // 0x654
        break;
    case COMMAND_TASK_LOOK_AT_OBJECT: // 0x655
        break;
    case COMMAND_LIMIT_ANGLE: // 0x656
        break;
    case COMMAND_OPEN_CAR_DOOR: // 0x657
        break;
    case COMMAND_SET_GROUP_DEFAULT_LEADER_TASK: // 0x658
        break;
    case COMMAND_SET_ATTRACTOR_PAIR: // 0x659
        break;
    case COMMAND_PLACE_CHAR_AT_ATTRACTOR: // 0x65A
        break;
    case COMMAND_GET_PICKUP_COORDINATES: // 0x65B
        break;
    case COMMAND_REMOVE_DECISION_MAKER: // 0x65C
        break;
    case COMMAND_VIEW_INTEGER_VARIABLE: // 0x65D
        break;
    case COMMAND_VIEW_FLOAT_VARIABLE: // 0x65E
        break;
    case COMMAND_WATCH_INTEGER_VARIABLE: // 0x65F
        break;
    case COMMAND_WATCH_FLOAT_VARIABLE: // 0x660
        break;
    case COMMAND_BREAKPOINT: // 0x661
        break;
    case COMMAND_WRITE_DEBUG: // 0x662
        break;
    case COMMAND_WRITE_DEBUG_WITH_INT: // 0x663
        break;
    case COMMAND_WRITE_DEBUG_WITH_FLOAT: // 0x664
        break;
    case COMMAND_GET_CHAR_MODEL: // 0x665
        break;
    case COMMAND_IS_CHAR_TOUCHING_ANY_OBJECT: // 0x666
        break;
    case COMMAND_TASK_AIM_GUN_AT_COORD: // 0x667
        break;
    case COMMAND_TASK_SHOOT_AT_COORD: // 0x668
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_CHAR: // 0x669
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_CHAR_WITH_DIRECTION: // 0x66A
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_CAR: // 0x66B
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_CAR_WITH_DIRECTION: // 0x66C
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_OBJECT: // 0x66D
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_OBJECT_WITH_DIRECTION: // 0x66E
        break;
    case COMMAND_ADD_QUEUED_DIALOGUE: // 0x66F
        break;
    case COMMAND_IS_DIALOGUE_FINISHED: // 0x670
        break;
    case COMMAND_IS_DIALOGUE_PLAYING: // 0x671
        break;
    case COMMAND_TASK_DESTROY_CAR: // 0x672
        break;
    case COMMAND_TASK_DIVE_AND_GET_UP: // 0x673
        break;
    case COMMAND_CUSTOM_PLATE_FOR_NEXT_CAR: // 0x674
        break;
    case COMMAND_CREATE_PED_GENERATOR_AT_ATTRACTOR: // 0x675
        break;
    case COMMAND_TASK_SHUFFLE_TO_NEXT_CAR_SEAT: // 0x676
        break;
    case COMMAND_TASK_CHAT_WITH_CHAR: // 0x677
        break;
    case COMMAND_GET_CHAR_AT_SCRIPTED_ATTRACTOR: // 0x678
        break;
    case COMMAND_ATTACH_CAMERA_TO_VEHICLE: // 0x679
        break;
    case COMMAND_ATTACH_CAMERA_TO_VEHICLE_LOOK_AT_VEHICLE: // 0x67A
        break;
    case COMMAND_ATTACH_CAMERA_TO_VEHICLE_LOOK_AT_CHAR: // 0x67B
        break;
    case COMMAND_ATTACH_CAMERA_TO_CHAR: // 0x67C
        break;
    case COMMAND_ATTACH_CAMERA_TO_CHAR_LOOK_AT_VEHICLE: // 0x67D
        break;
    case COMMAND_ATTACH_CAMERA_TO_CHAR_LOOK_AT_CHAR: // 0x67E
        break;
    case COMMAND_FORCE_CAR_LIGHTS: // 0x67F
        break;
    case COMMAND_ADD_PEDTYPE_AS_ATTRACTOR_USER: // 0x680
        break;
    case COMMAND_ATTACH_OBJECT_TO_CAR: // 0x681
        break;
    case COMMAND_DETACH_OBJECT: // 0x682
        break;
    case COMMAND_ATTACH_CAR_TO_CAR: // 0x683
        break;
    case COMMAND_DETACH_CAR: // 0x684
        break;
    case COMMAND_IS_OBJECT_ATTACHED: // 0x685
        break;
    case COMMAND_IS_VEHICLE_ATTACHED: // 0x686
        break;
    case COMMAND_CLEAR_CHAR_TASKS: // 0x687
        break;
    case COMMAND_TASK_TOGGLE_PED_THREAT_SCANNER: // 0x688
        break;
    case COMMAND_POP_CAR_DOOR: // 0x689
        break;
    case COMMAND_FIX_CAR_DOOR: // 0x68A
        break;
    case COMMAND_TASK_EVERYONE_LEAVE_CAR: // 0x68B
        break;
    case COMMAND_IS_PLAYER_TARGETTING_ANYTHING: // 0x68C
        break;
    case COMMAND_GET_ACTIVE_CAMERA_COORDINATES: // 0x68D
        break;
    case COMMAND_GET_ACTIVE_CAMERA_POINT_AT: // 0x68E
        break;
    case COMMAND_GET_CLOSEST_BUYABLE_OBJECT_TO_PLAYER: // 0x68F
        break;
    case COMMAND_OPEN_FRIEND_LIST: // 0x690
        break;
    case COMMAND_CLOSE_FRIEND_LIST: // 0x691
        break;
    case COMMAND_REMOVE_FRIEND_LIST: // 0x692
        break;
    case COMMAND_SET_PEDMODEL_AS_FRIEND: // 0x693
        break;
    case COMMAND_SET_PEDTYPE_AS_FRIEND: // 0x694
        break;
    case COMMAND_CLEAR_CHAR_FRIENDS: // 0x695
        break;
    case COMMAND_SET_CHAR_FRIEND_LIST: // 0x696
        break;
    case COMMAND_POP_CAR_PANEL: // 0x697
        break;
    case COMMAND_FIX_CAR_PANEL: // 0x698
        break;
    case COMMAND_FIX_CAR_TYRE: // 0x699
        break;
    case COMMAND_ATTACH_OBJECT_TO_OBJECT: // 0x69A
        break;
    case COMMAND_ATTACH_OBJECT_TO_CHAR: // 0x69B
        break;
    case COMMAND_ATTACH_CAMERA_TO_OBJECT: // 0x69C
        break;
    case COMMAND_ATTACH_CAMERA_TO_OBJECT_LOOK_AT_VEHICLE: // 0x69D
        break;
    case COMMAND_ATTACH_CAMERA_TO_OBJECT_LOOK_AT_CHAR: // 0x69E
        break;
    case COMMAND_ATTACH_CAMERA_TO_OBJECT_LOOK_AT_OBJECT: // 0x69F
        break;
    case COMMAND_ATTACH_CAMERA_TO_CHAR_LOOK_AT_OBJECT: // 0x6A0
        break;
    case COMMAND_ATTACH_CAMERA_TO_VEHICLE_LOOK_AT_OBJECT: // 0x6A1
        break;
    case COMMAND_GET_CAR_SPEED_VECTOR: // 0x6A2
        break;
    case COMMAND_GET_CAR_MASS: // 0x6A3
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x496E00
int8 CRunningScript::ProcessCommands1700To1799(int32 commandId) {
    switch (commandId) {
    case COMMAND_TASK_KILL_THREATS_ON_FOOT_WHILE_DUCKING: // 0x6A4
        break;
    case COMMAND_TASK_DIVE_FROM_ATTACHMENT_AND_GET_UP: // 0x6A5
        break;
    case COMMAND_TASK_PLAY_ANIM_WITH_VELOCITY_EXTRACTION: // 0x6A6
        break;
    case COMMAND_ATTACH_CHAR_TO_BIKE: // 0x6A7
        break;
    case COMMAND_TASK_GOTO_CHAR_OFFSET: // 0x6A8
        break;
    case COMMAND_TASK_LOOK_AT_COORD: // 0x6A9
        break;
    case COMMAND_IS_RECORDING_GOING_ON_FOR_CAR: // 0x6AA
        break;
    case COMMAND_HIDE_CHAR_WEAPON_FOR_SCRIPTED_CUTSCENE: // 0x6AB
        break;
    case COMMAND_GET_CHAR_SPEED: // 0x6AC
        break;
    case COMMAND_SET_GROUP_DECISION_MAKER: // 0x6AD
        break;
    case COMMAND_LOAD_GROUP_DECISION_MAKER: // 0x6AE
        break;
    case COMMAND_DISABLE_PLAYER_SPRINT: // 0x6AF
        break;
    case COMMAND_TASK_SIT_DOWN: // 0x6B0
        break;
    case COMMAND_CREATE_SEARCHLIGHT: // 0x6B1
        break;
    case COMMAND_DELETE_SEARCHLIGHT: // 0x6B2
        break;
    case COMMAND_DOES_SEARCHLIGHT_EXIST: // 0x6B3
        break;
    case COMMAND_MOVE_SEARCHLIGHT_BETWEEN_COORDS: // 0x6B4
        break;
    case COMMAND_POINT_SEARCHLIGHT_AT_COORD: // 0x6B5
        break;
    case COMMAND_POINT_SEARCHLIGHT_AT_CHAR: // 0x6B6
        break;
    case COMMAND_IS_CHAR_IN_SEARCHLIGHT: // 0x6B7
        break;
    case COMMAND_SET_GROUP_DEFAULT_TASK: // 0x6B8
        break;
    case COMMAND_HAS_CUTSCENE_LOADED: // 0x6B9
        break;
    case COMMAND_TASK_TURN_CHAR_TO_FACE_COORD: // 0x6BA
        break;
    case COMMAND_TASK_DRIVE_POINT_ROUTE: // 0x6BB
        break;
    case COMMAND_FIRE_SINGLE_BULLET: // 0x6BC
        break;
    case COMMAND_IS_LINE_OF_SIGHT_CLEAR: // 0x6BD
        break;
    case COMMAND_GET_CAR_ROLL: // 0x6BE
        break;
    case COMMAND_POINT_SEARCHLIGHT_AT_VEHICLE: // 0x6BF
        break;
    case COMMAND_IS_VEHICLE_IN_SEARCHLIGHT: // 0x6C0
        break;
    case COMMAND_CREATE_SEARCHLIGHT_ON_VEHICLE: // 0x6C1
        break;
    case COMMAND_TASK_GO_TO_COORD_WHILE_AIMING: // 0x6C2
        break;
    case COMMAND_GET_NUMBER_OF_FIRES_IN_RANGE: // 0x6C3
        break;
    case COMMAND_ADD_BLIP_FOR_SEARCHLIGHT: // 0x6C4
        break;
    case COMMAND_SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_CAR: // 0x6C5
        break;
    case COMMAND_TASK_OPEN_DRIVER_DOOR: // 0x6C6
        break;
    case COMMAND_TASK_CAR_TEMP_ACTION: // 0x6C7
        break;
    case COMMAND_SET_LA_RIOTS: // 0x6C8
        break;
    case COMMAND_REMOVE_CHAR_FROM_GROUP: // 0x6C9
        break;
    case COMMAND_ATTACH_SEARCHLIGHT_TO_SEARCHLIGHT_OBJECT: // 0x6CA
        break;
    case COMMAND_SET_VEHICLE_RECORDS_COLLISIONS: // 0x6CB
        break;
    case COMMAND_DRAW_CROSS_IN_FRONT_OF_DEBUG_CAMERA: // 0x6CC
        break;
    case COMMAND_DRAW_DEBUG_CUBE: // 0x6CD
        break;
    case COMMAND_GET_CAR_LAST_ROUTE_COORDS: // 0x6CE
        break;
    case COMMAND_DISPLAY_TIMER_BARS: // 0x6CF
        break;
    case COMMAND_SWITCH_EMERGENCY_SERVICES: // 0x6D0
        break;
    case COMMAND_SET_VAR_TEXT_LABEL16: // 0x6D1
        break;
    case COMMAND_SET_LVAR_TEXT_LABEL16: // 0x6D2
        break;
    case COMMAND_VAR_TEXT_LABEL16: // 0x6D3
        break;
    case COMMAND_LVAR_TEXT_LABEL16: // 0x6D4
        break;
    case COMMAND_CREATE_CHECKPOINT: // 0x6D5
        break;
    case COMMAND_DELETE_CHECKPOINT: // 0x6D6
        break;
    case COMMAND_SWITCH_RANDOM_TRAINS: // 0x6D7
        break;
    case COMMAND_CREATE_MISSION_TRAIN: // 0x6D8
        break;
    case COMMAND_DELETE_MISSION_TRAINS: // 0x6D9
        break;
    case COMMAND_MARK_MISSION_TRAINS_AS_NO_LONGER_NEEDED: // 0x6DA
        break;
    case COMMAND_DELETE_ALL_TRAINS: // 0x6DB
        break;
    case COMMAND_SET_TRAIN_SPEED: // 0x6DC
        break;
    case COMMAND_SET_TRAIN_CRUISE_SPEED: // 0x6DD
        break;
    case COMMAND_GET_TRAIN_CABOOSE: // 0x6DE
        break;
    case COMMAND_DELETE_PLAYER: // 0x6DF
        break;
    case COMMAND_SET_TWO_PLAYER_CAMERA_MODE: // 0x6E0
        break;
    case COMMAND_TASK_CAR_MISSION: // 0x6E1
        break;
    case COMMAND_TASK_GO_TO_OBJECT: // 0x6E2
        break;
    case COMMAND_TASK_WEAPON_ROLL: // 0x6E3
        break;
    case COMMAND_TASK_CHAR_ARREST_CHAR: // 0x6E4
        break;
    case COMMAND_GET_AVAILABLE_VEHICLE_MOD: // 0x6E5
        break;
    case COMMAND_GET_VEHICLE_MOD_TYPE: // 0x6E6
        break;
    case COMMAND_ADD_VEHICLE_MOD: // 0x6E7
        break;
    case COMMAND_REMOVE_VEHICLE_MOD: // 0x6E8
        break;
    case COMMAND_REQUEST_VEHICLE_MOD: // 0x6E9
        break;
    case COMMAND_HAS_VEHICLE_MOD_LOADED: // 0x6EA
        break;
    case COMMAND_MARK_VEHICLE_MOD_AS_NO_LONGER_NEEDED: // 0x6EB
        break;
    case COMMAND_GET_NUM_AVAILABLE_PAINTJOBS: // 0x6EC
        break;
    case COMMAND_GIVE_VEHICLE_PAINTJOB: // 0x6ED
        break;
    case COMMAND_IS_GROUP_MEMBER: // 0x6EE
        break;
    case COMMAND_IS_GROUP_LEADER: // 0x6EF
        break;
    case COMMAND_SET_GROUP_SEPARATION_RANGE: // 0x6F0
        break;
    case COMMAND_LIMIT_TWO_PLAYER_DISTANCE: // 0x6F1
        break;
    case COMMAND_RELEASE_TWO_PLAYER_DISTANCE: // 0x6F2
        break;
    case COMMAND_SET_PLAYER_PLAYER_TARGETTING: // 0x6F3
        break;
    case COMMAND_CREATE_SCRIPT_GANG_ROADBLOCK: // 0x6F4
        break;
    case COMMAND_GET_SCRIPT_FIRE_COORDS: // 0x6F5
        break;
    case COMMAND_CLEAR_TWO_PLAYER_CAMERA_MODE: // 0x6F6
        break;
    case COMMAND_SET_PLAYER_PASSENGER_CAN_SHOOT: // 0x6F7
        break;
    case COMMAND_GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING: // 0x6F8
        break;
    case COMMAND_GET_HEIGHT_OF_CAR_WHEELS_FROM_GROUND: // 0x6F9
        break;
    case COMMAND_SET_PLAYERS_CAN_BE_IN_SEPARATE_CARS: // 0x6FA
        break;
    case COMMAND_SWITCH_PLAYER_CROSSHAIR: // 0x6FB
        break;
    case COMMAND_DOES_CAR_HAVE_STUCK_CAR_CHECK: // 0x6FC
        break;
    case COMMAND_SET_PLAYBACK_SPEED: // 0x6FD
        break;
    case COMMAND_GET_CAR_VALUE: // 0x6FE
        break;
    case COMMAND_ARE_ANY_CHARS_NEAR_CHAR: // 0x6FF
        break;
    case COMMAND_SKIP_CUTSCENE_START: // 0x700
        break;
    case COMMAND_SKIP_CUTSCENE_END: // 0x701
        break;
    case COMMAND_GET_PERCENTAGE_TAGGED_IN_AREA: // 0x702
        break;
    case COMMAND_SET_TAG_STATUS_IN_AREA: // 0x703
        break;
    case COMMAND_CAR_GOTO_COORDINATES_RACING: // 0x704
        break;
    case COMMAND_START_PLAYBACK_RECORDED_CAR_USING_AI: // 0x705
        break;
    case COMMAND_SKIP_IN_PLAYBACK_RECORDED_CAR: // 0x706
        break;
    case COMMAND_SKIP_CUTSCENE_START_INTERNAL: // 0x707
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x46D050
int8 CRunningScript::ProcessCommands1800To1899(int32 commandId) {
    switch (commandId) {
    case COMMAND_CLEAR_CHAR_DECISION_MAKER_EVENT_RESPONSE: // 0x708
        break;
    case COMMAND_ADD_CHAR_DECISION_MAKER_EVENT_RESPONSE: // 0x709
        break;
    case COMMAND_TASK_PICK_UP_OBJECT: // 0x70A
        break;
    case COMMAND_DROP_OBJECT: // 0x70B
        break;
    case COMMAND_EXPLODE_CAR_IN_CUTSCENE: // 0x70C
        break;
    case COMMAND_BUILD_PLAYER_MODEL: // 0x70D
        break;
    case COMMAND_PLANE_ATTACK_PLAYER: // 0x70E
        break;
    case COMMAND_PLANE_FLY_IN_DIRECTION: // 0x70F
        break;
    case COMMAND_PLANE_FOLLOW_ENTITY: // 0x710
        break;
    case COMMAND_ALLOCATE_SCRIPT_TO_PED_GENERATOR: // 0x711
        break;
    case COMMAND_ALLOCATE_SCRIPT_TO_RANDOM_PED: // 0x712
        break;
    case COMMAND_TASK_DRIVE_BY: // 0x713
        break;
    case COMMAND_SET_CAR_STAY_IN_SLOW_LANE: // 0x714
        break;
    case COMMAND_TAKE_REMOTE_CONTROL_OF_CAR: // 0x715
        break;
    case COMMAND_IS_CLOSEST_OBJECT_OF_TYPE_SMASHED_OR_DAMAGED: // 0x716
        break;
    case COMMAND_START_SETTING_UP_CONVERSATION: // 0x717
        break;
    case COMMAND_SET_UP_CONVERSATION_NODE: // 0x718
        break;
    case COMMAND_FINISH_SETTING_UP_CONVERSATION: // 0x719
        break;
    case COMMAND_IS_CONVERSATION_AT_NODE: // 0x71A
        break;
    case COMMAND_CLEAR_ALL_CONVERSATIONS: // 0x71B
        break;
    case COMMAND_GET_CHAR_LIGHTING: // 0x71C
        break;
    case COMMAND_SET_CLOSEST_OBJECT_OF_TYPE_RENDER_SCORCHED: // 0x71D
        break;
    case COMMAND_GET_OBJECT_HEALTH: // 0x71E
        break;
    case COMMAND_SET_OBJECT_HEALTH: // 0x71F
        break;
    case COMMAND_GET_VEHICLE_WHEEL_UPGRADE_CLASS: // 0x720
        break;
    case COMMAND_GET_NUM_WHEELS_IN_UPGRADE_CLASS: // 0x721
        break;
    case COMMAND_GET_WHEEL_IN_UPGRADE_CLASS: // 0x722
        break;
    case COMMAND_BREAK_OBJECT: // 0x723
        break;
    case COMMAND_HELI_ATTACK_PLAYER: // 0x724
        break;
    case COMMAND_HELI_FLY_IN_DIRECTION: // 0x725
        break;
    case COMMAND_HELI_FOLLOW_ENTITY: // 0x726
        break;
    case COMMAND_POLICE_HELI_CHASE_ENTITY: // 0x727
        break;
    case COMMAND_SET_UP_CONVERSATION_END_NODE: // 0x728
        break;
    case COMMAND_TASK_USE_MOBILE_PHONE: // 0x729
        break;
    case COMMAND_TASK_WARP_CHAR_INTO_CAR_AS_DRIVER: // 0x72A
        break;
    case COMMAND_TASK_WARP_CHAR_INTO_CAR_AS_PASSENGER: // 0x72B
        break;
    case COMMAND_SWITCH_COPS_ON_BIKES: // 0x72C
        break;
    case COMMAND_IS_FLAME_IN_ANGLED_AREA_2D: // 0x72D
        break;
    case COMMAND_IS_FLAME_IN_ANGLED_AREA_3D: // 0x72E
        break;
    case COMMAND_ADD_STUCK_CAR_CHECK_WITH_WARP: // 0x72F
        break;
    case COMMAND_DAMAGE_CAR_PANEL: // 0x730
        break;
    case COMMAND_SET_CAR_ROLL: // 0x731
        break;
    case COMMAND_SUPPRESS_CAR_MODEL: // 0x732
        break;
    case COMMAND_DONT_SUPPRESS_CAR_MODEL: // 0x733
        break;
    case COMMAND_DONT_SUPPRESS_ANY_CAR_MODELS: // 0x734
        break;
    case COMMAND_IS_PS2_KEYBOARD_KEY_PRESSED: // 0x735
        break;
    case COMMAND_IS_PS2_KEYBOARD_KEY_JUST_PRESSED: // 0x736
        break;
    case COMMAND_IS_CHAR_HOLDING_OBJECT: // 0x737
        break;
    case COMMAND_SET_ZONE_RADAR_COLOURS: // 0x738
        break;
    case COMMAND_GIVE_LOWRIDER_SUSPENSION_TO_CAR: // 0x739
        break;
    case COMMAND_DOES_CAR_HAVE_LOWRIDER_SUSPENSION: // 0x73A
        break;
    case COMMAND_SET_CAR_CAN_GO_AGAINST_TRAFFIC: // 0x73B
        break;
    case COMMAND_DAMAGE_CAR_DOOR: // 0x73C
        break;
    case COMMAND_GET_RANDOM_CAR_IN_SPHERE: // 0x73D
        break;
    case COMMAND_GET_RANDOM_CAR_IN_SPHERE_NO_SAVE: // 0x73E
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_SPHERE: // 0x73F
        break;
    case COMMAND_GET_COORDS_OF_CLOSEST_COLLECTABLE1: // 0x740
        break;
    case COMMAND_HAS_CHAR_BEEN_ARRESTED: // 0x741
        break;
    case COMMAND_SET_PLANE_THROTTLE: // 0x742
        break;
    case COMMAND_HELI_LAND_AT_COORDS: // 0x743
        break;
    case COMMAND_GET_STAT_CHANGE_AMOUNT: // 0x744
        break;
    case COMMAND_PLANE_STARTS_IN_AIR: // 0x745
        break;
    case COMMAND_SET_RELATIONSHIP: // 0x746
        break;
    case COMMAND_CLEAR_RELATIONSHIP: // 0x747
        break;
    case COMMAND_CLEAR_ALL_RELATIONSHIPS: // 0x748
        break;
    case COMMAND_CLEAR_GROUP_DECISION_MAKER_EVENT_RESPONSE: // 0x749
        break;
    case COMMAND_ADD_GROUP_DECISION_MAKER_EVENT_RESPONSE: // 0x74A
        break;
    case COMMAND_DRAW_SPRITE_WITH_ROTATION: // 0x74B
        break;
    case COMMAND_TASK_USE_ATTRACTOR: // 0x74C
        break;
    case COMMAND_TASK_SHOOT_AT_CHAR: // 0x74D
        break;
    case COMMAND_SET_INFORM_RESPECTED_FRIENDS: // 0x74E
        break;
    case COMMAND_IS_CHAR_RESPONDING_TO_EVENT: // 0x74F
        break;
    case COMMAND_SET_OBJECT_VISIBLE: // 0x750
        break;
    case COMMAND_TASK_FLEE_CHAR_ANY_MEANS: // 0x751
        break;
    case COMMAND_STOP_RECORDING_CAR: // 0x752
        break;
    case COMMAND_SET_ALERTNESS: // 0x753
        break;
    case COMMAND_FLUSH_PATROL_ROUTE: // 0x754
        break;
    case COMMAND_EXTEND_PATROL_ROUTE: // 0x755
        break;
    case COMMAND_TASK_GO_ON_PATROL: // 0x756
        break;
    case COMMAND_GET_PATROL_ALERTNESS: // 0x757
        break;
    case COMMAND_SET_CHAR_SPECIAL_EVENT: // 0x758
        break;
    case COMMAND_SET_ATTRACTOR_AS_COVER_NODE: // 0x759
        break;
    case COMMAND_PLAY_OBJECT_ANIM: // 0x75A
        break;
    case COMMAND_SET_RADAR_ZOOM: // 0x75B
        break;
    case COMMAND_DOES_BLIP_EXIST: // 0x75C
        break;
    case COMMAND_LOAD_PRICES: // 0x75D
        break;
    case COMMAND_LOAD_SHOP: // 0x75E
        break;
    case COMMAND_GET_NUMBER_OF_ITEMS_IN_SHOP: // 0x75F
        break;
    case COMMAND_GET_ITEM_IN_SHOP: // 0x760
        break;
    case COMMAND_GET_PRICE_OF_ITEM: // 0x761
        break;
    case COMMAND_TASK_DEAD: // 0x762
        break;
    case COMMAND_SET_CAR_AS_MISSION_CAR: // 0x763
        break;
    case COMMAND_IS_SEARCHLIGHT_IN_ANGLED_AREA_2D: // 0x764
        break;
    case COMMAND_IS_SEARCHLIGHT_IN_ANGLED_AREA_3D: // 0x765
        break;
    case COMMAND_SWITCH_SEARCHLIGHT_BULB: // 0x766
        break;
    case COMMAND_SET_ZONE_POPULATION_TYPE: // 0x767
        break;
    case COMMAND_SET_ZONE_GANG_CAP: // 0x768
        break;
    case COMMAND_GET_ZONE_GANG_CAP: // 0x769
        break;
    case COMMAND_SET_ZONE_DEALER_STRENGTH: // 0x76A
        break;
    case COMMAND_GET_ZONE_DEALER_STRENGTH: // 0x76B
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x46B460
int8 CRunningScript::ProcessCommands1900To1999(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_ZONE_GANG_STRENGTH: // 0x76C
        break;
    case COMMAND_GET_ZONE_GANG_STRENGTH: // 0x76D
        break;
    case COMMAND_SET_NO_POLICE_DURING_LA_RIOTS: // 0x76E
        break;
    case COMMAND_IS_MESSAGE_BEING_DISPLAYED: // 0x76F
        break;
    case COMMAND_SET_CHAR_IS_TARGET_PRIORITY: // 0x770
        break;
    case COMMAND_CUSTOM_PLATE_DESIGN_FOR_NEXT_CAR: // 0x771
        break;
    case COMMAND_TASK_GOTO_CAR: // 0x772
        break;
    case COMMAND_CLEAR_HELP_WITH_THIS_LABEL: // 0x773
        break;
    case COMMAND_IS_SEARCHLIGHT_BULB_ON: // 0x774
        break;
    case COMMAND_CREATE_OIL_PUDDLE: // 0x775
        break;
    case COMMAND_REQUEST_IPL: // 0x776
        break;
    case COMMAND_REMOVE_IPL: // 0x777
        break;
    case COMMAND_REMOVE_IPL_DISCREETLY: // 0x778
        break;
    case COMMAND_TASK_OPEN_PASSENGER_DOOR: // 0x779
        break;
    case COMMAND_SET_CHAR_RELATIONSHIP: // 0x77A
        break;
    case COMMAND_CLEAR_CHAR_RELATIONSHIP: // 0x77B
        break;
    case COMMAND_CLEAR_ALL_CHAR_RELATIONSHIPS: // 0x77C
        break;
    case COMMAND_GET_CAR_PITCH: // 0x77D
        break;
    case COMMAND_GET_AREA_VISIBLE: // 0x77E
        break;
    case COMMAND_ADD_INT_TO_VAR_CONSOLE: // 0x77F
        break;
    case COMMAND_HELI_KEEP_ENTITY_IN_VIEW: // 0x780
        break;
    case COMMAND_GET_WEAPONTYPE_MODEL: // 0x781
        break;
    case COMMAND_GET_WEAPONTYPE_SLOT: // 0x782
        break;
    case COMMAND_GET_SHOPPING_EXTRA_INFO: // 0x783
        break;
    case COMMAND_GIVE_PLAYER_CLOTHES: // 0x784
        break;
    case COMMAND_GIVE_PLAYER_TATTOO: // 0x785
        break;
    case COMMAND_GET_NUMBER_OF_FIRES_IN_AREA: // 0x786
        break;
    case COMMAND_SET_CHAR_TYRES_CAN_BE_BURST: // 0x787
        break;
    case COMMAND_ATTACH_WINCH_TO_HELI: // 0x788
        break;
    case COMMAND_RELEASE_ENTITY_FROM_WINCH: // 0x789
        break;
    case COMMAND_GET_TRAIN_CARRIAGE: // 0x78A
        break;
    case COMMAND_GRAB_ENTITY_ON_WINCH: // 0x78B
        break;
    case COMMAND_GET_NAME_OF_ITEM: // 0x78C
        break;
    case COMMAND_ADD_FLOAT_TO_VAR_CONSOLE: // 0x78D
        break;
    case COMMAND_TASK_DRAG_CHAR_FROM_CAR: // 0x78E
        break;
    case COMMAND_TASK_CLIMB: // 0x78F
        break;
    case COMMAND_BUY_ITEM: // 0x790
        break;
    case COMMAND_BUY_TATTOO: // 0x791
        break;
    case COMMAND_CLEAR_CHAR_TASKS_IMMEDIATELY: // 0x792
        break;
    case COMMAND_STORE_CLOTHES_STATE: // 0x793
        break;
    case COMMAND_RESTORE_CLOTHES_STATE: // 0x794
        break;
    case COMMAND_DELETE_WINCH_FOR_HELI: // 0x795
        break;
    case COMMAND_GET_ROPE_HEIGHT_FOR_OBJECT: // 0x796
        break;
    case COMMAND_SET_ROPE_HEIGHT_FOR_OBJECT: // 0x797
        break;
    case COMMAND_GRAB_ENTITY_ON_ROPE_FOR_OBJECT: // 0x798
        break;
    case COMMAND_RELEASE_ENTITY_FROM_ROPE_FOR_OBJECT: // 0x799
        break;
    case COMMAND_ATTACH_CAR_TO_ROPE_FOR_OBJECT: // 0x79A
        break;
    case COMMAND_ATTACH_CHAR_TO_ROPE_FOR_OBJECT: // 0x79B
        break;
    case COMMAND_ATTACH_OBJECT_TO_ROPE_FOR_OBJECT: // 0x79C
        break;
    case COMMAND_PLAYER_ENTERED_DOCK_CRANE: // 0x79D
        break;
    case COMMAND_PLAYER_ENTERED_BUILDINGSITE_CRANE: // 0x79E
        break;
    case COMMAND_PLAYER_LEFT_CRANE: // 0x79F
        break;
    case COMMAND_PERFORM_SEQUENCE_TASK_FROM_PROGRESS: // 0x7A0
        break;
    case COMMAND_SET_NEXT_DESIRED_MOVE_STATE: // 0x7A1
        break;
    case COMMAND_SET_NEXT_EVENT_RESPONSE_SEQUENCE: // 0x7A2
        break;
    case COMMAND_TASK_GOTO_CHAR_AIMING: // 0x7A3
        break;
    case COMMAND_GET_SEQUENCE_PROGRESS_RECURSIVE: // 0x7A4
        break;
    case COMMAND_TASK_KILL_CHAR_ON_FOOT_TIMED: // 0x7A5
        break;
    case COMMAND_GET_NEAREST_TAG_POSITION: // 0x7A6
        break;
    case COMMAND_TASK_JETPACK: // 0x7A7
        break;
    case COMMAND_SET_AREA51_SAM_SITE: // 0x7A8
        break;
    case COMMAND_IS_CHAR_IN_ANY_SEARCHLIGHT: // 0x7A9
        break;
    case COMMAND_GET_SEARCHLIGHT_COORDS: // 0x7AA
        break;
    case COMMAND_IS_TRAILER_ATTACHED_TO_CAB: // 0x7AB
        break;
    case COMMAND_DETACH_TRAILER_FROM_CAB: // 0x7AC
        break;
    case COMMAND_GET_TRAILER_ATTACHED_TO_CAB: // 0x7AD
        break;
    case COMMAND_GET_CAB_ATTACHED_TO_TRAILER: // 0x7AE
        break;
    case COMMAND_GET_PLAYER_GROUP: // 0x7AF
        break;
    case COMMAND_GET_LOADED_SHOP: // 0x7B0
        break;
    case COMMAND_GET_BEAT_PROXIMITY: // 0x7B1
        break;
    case COMMAND_SET_BEAT_ZONE_SIZE: // 0x7B2
        break;
    case COMMAND_SET_GROUP_DEFAULT_TASK_ALLOCATOR: // 0x7B3
        break;
    case COMMAND_SET_PLAYER_GROUP_RECRUITMENT: // 0x7B4
        break;
    case COMMAND_DISPLAY_TWO_ONSCREEN_COUNTERS: // 0x7B5
        break;
    case COMMAND_DISPLAY_TWO_ONSCREEN_COUNTERS_WITH_STRING: // 0x7B6
        break;
    case COMMAND_DISPLAY_NTH_TWO_ONSCREEN_COUNTERS: // 0x7B7
        break;
    case COMMAND_DISPLAY_NTH_TWO_ONSCREEN_COUNTERS_WITH_STRING: // 0x7B8
        break;
    case COMMAND_TASK_KILL_CHAR_ON_FOOT_PATROL: // 0x7B9
        break;
    case COMMAND_HELI_AIM_AHEAD_OF_TARGET_ENTITY: // 0x7BA
        break;
    case COMMAND_ACTIVATE_HELI_SPEED_CHEAT: // 0x7BB
        break;
    case COMMAND_TASK_SET_CHAR_DECISION_MAKER: // 0x7BC
        break;
    case COMMAND_DELETE_MISSION_TRAIN: // 0x7BD
        break;
    case COMMAND_MARK_MISSION_TRAIN_AS_NO_LONGER_NEEDED: // 0x7BE
        break;
    case COMMAND_SET_BLIP_ALWAYS_DISPLAY_ON_ZOOMED_RADAR: // 0x7BF
        break;
    case COMMAND_REQUEST_CAR_RECORDING: // 0x7C0
        break;
    case COMMAND_HAS_CAR_RECORDING_BEEN_LOADED: // 0x7C1
        break;
    case COMMAND_DISPLAY_PLAYBACK_RECORDED_CAR: // 0x7C2
        break;
    case COMMAND_GET_OBJECT_QUATERNION: // 0x7C3
        break;
    case COMMAND_SET_OBJECT_QUATERNION: // 0x7C4
        break;
    case COMMAND_GET_VEHICLE_QUATERNION: // 0x7C5
        break;
    case COMMAND_SET_VEHICLE_QUATERNION: // 0x7C6
        break;
    case COMMAND_SET_MISSION_TRAIN_COORDINATES: // 0x7C7
        break;
    case COMMAND_DISPLAY_DEBUG_MESSAGE: // 0x7C8
        break;
    case COMMAND_TASK_COMPLEX_PICKUP_OBJECT: // 0x7C9
        break;
    case COMMAND_TASK_SIMPLE_PUTDOWN_OBJECT: // 0x7CA
        break;
    case COMMAND_LISTEN_TO_PLAYER_GROUP_COMMANDS: // 0x7CB
        break;
    case COMMAND_SET_PLAYER_ENTER_CAR_BUTTON: // 0x7CC
        break;
    case COMMAND_TASK_CHAR_SLIDE_TO_COORD: // 0x7CD
        break;
    case COMMAND_SET_BULLET_WHIZZ_BY_DISTANCE: // 0x7CE
        break;
    case COMMAND_SET_TWO_PLAYER_CAM_MODE_SEPARATE_CARS: // 0x7CF
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x472310
int8 CRunningScript::ProcessCommands2000To2099(int32 commandId) {
    switch (commandId) {
    case COMMAND_GET_CURRENT_DAY_OF_WEEK: // 0x7D0
        break;
    case COMMAND_SET_CURRENT_DAY_OF_WEEK: // 0x7D1
        break;
    case COMMAND_ACTIVATE_INTERIORS: // 0x7D2
        break;
    case COMMAND_REGISTER_SCRIPT_BRAIN_FOR_CODE_USE: // 0x7D3
        break;
    case COMMAND_REGISTER_OBJECT_SCRIPT_BRAIN_FOR_CODE_USE: // 0x7D4
        break;
    case COMMAND_APPLY_FORCE_TO_CAR: // 0x7D5
        break;
    case COMMAND_IS_INT_LVAR_EQUAL_TO_INT_VAR: // 0x7D6
        break;
    case COMMAND_IS_FLOAT_LVAR_EQUAL_TO_FLOAT_VAR: // 0x7D7
        break;
    case COMMAND_IS_INT_LVAR_NOT_EQUAL_TO_INT_VAR: // 0x7D8
        break;
    case COMMAND_IS_FLOAT_LVAR_NOT_EQUAL_TO_FLOAT_VAR: // 0x7D9
        break;
    case COMMAND_ADD_TO_CAR_ROTATION_VELOCITY: // 0x7DA
        break;
    case COMMAND_SET_CAR_ROTATION_VELOCITY: // 0x7DB
        break;
    case COMMAND_GET_CAR_ROTATION_VELOCITY: // 0x7DC
        break;
    case COMMAND_SET_CHAR_SHOOT_RATE: // 0x7DD
        break;
    case COMMAND_IS_MODEL_IN_CDIMAGE: // 0x7DE
        break;
    case COMMAND_REMOVE_OIL_PUDDLES_IN_AREA: // 0x7DF
        break;
    case COMMAND_SET_BLIP_AS_FRIENDLY: // 0x7E0
        break;
    case COMMAND_TASK_SWIM_TO_COORD: // 0x7E1
        break;
    case COMMAND_TASK_GO_STRAIGHT_TO_COORD_WITHOUT_STOPPING: // 0x7E2
        break;
    case COMMAND_GET_BEAT_INFO_FOR_CURRENT_TRACK: // 0x7E3
        break;
    case COMMAND_GET_MODEL_DIMENSIONS: // 0x7E4
        break;
    case COMMAND_COPY_CHAR_DECISION_MAKER: // 0x7E5
        break;
    case COMMAND_COPY_GROUP_DECISION_MAKER: // 0x7E6
        break;
    case COMMAND_TASK_DRIVE_POINT_ROUTE_ADVANCED: // 0x7E7
        break;
    case COMMAND_IS_RELATIONSHIP_SET: // 0x7E8
        break;
    case COMMAND_HAS_CHAR_SPOTTED_CAR: // 0x7E9
        break;
    case COMMAND_SET_ROPE_HEIGHT_FOR_HELI: // 0x7EA
        break;
    case COMMAND_GET_ROPE_HEIGHT_FOR_HELI: // 0x7EB
        break;
    case COMMAND_IS_CAR_LOWRIDER: // 0x7EC
        break;
    case COMMAND_IS_PERFORMANCE_CAR: // 0x7ED
        break;
    case COMMAND_SET_CAR_ALWAYS_CREATE_SKIDS: // 0x7EE
        break;
    case COMMAND_GET_CITY_FROM_COORDS: // 0x7EF
        break;
    case COMMAND_HAS_OBJECT_OF_TYPE_BEEN_SMASHED: // 0x7F0
        break;
    case COMMAND_IS_PLAYER_PERFORMING_WHEELIE: // 0x7F1
        break;
    case COMMAND_IS_PLAYER_PERFORMING_STOPPIE: // 0x7F2
        break;
    case COMMAND_SET_CHECKPOINT_COORDS: // 0x7F3
        break;
    case COMMAND_SET_ONSCREEN_TIMER_DISPLAY: // 0x7F4
        break;
    case COMMAND_CONTROL_CAR_HYDRAULICS: // 0x7F5
        break;
    case COMMAND_GET_GROUP_SIZE: // 0x7F6
        break;
    case COMMAND_SET_OBJECT_COLLISION_DAMAGE_EFFECT: // 0x7F7
        break;
    case COMMAND_SET_CAR_FOLLOW_CAR: // 0x7F8
        break;
    case COMMAND_PLAYER_ENTERED_QUARRY_CRANE: // 0x7F9
        break;
    case COMMAND_PLAYER_ENTERED_LAS_VEGAS_CRANE: // 0x7FA
        break;
    case COMMAND_SWITCH_ENTRY_EXIT: // 0x7FB
        break;
    case COMMAND_DISPLAY_TEXT_WITH_FLOAT: // 0x7FC
        break;
    case COMMAND_DOES_GROUP_EXIST: // 0x7FD
        break;
    case COMMAND_GIVE_MELEE_ATTACK_TO_CHAR: // 0x7FE
        break;
    case COMMAND_SET_CAR_HYDRAULICS: // 0x7FF
        break;
    case COMMAND_IS_2PLAYER_GAME_GOING_ON: // 0x800
        break;
    case COMMAND_GET_CAMERA_FOV: // 0x801
        break;
    case COMMAND_SET_GLOBAL_PED_SEARCH_PARAMS: // 0x802
        break;
    case COMMAND_DOES_CAR_HAVE_HYDRAULICS: // 0x803
        break;
    case COMMAND_TASK_CHAR_SLIDE_TO_COORD_AND_PLAY_ANIM: // 0x804
        break;
    case COMMAND_ALLOCATE_SCRIPT_TO_OBJECT: // 0x805
        break;
    case COMMAND_GET_TOTAL_NUMBER_OF_PEDS_KILLED_BY_PLAYER: // 0x806
        break;
    case COMMAND_SET_TWO_PLAYER_CAM_MODE_SAME_CAR_SHOOTING: // 0x807
        break;
    case COMMAND_SET_TWO_PLAYER_CAM_MODE_SAME_CAR_NO_SHOOTING: // 0x808
        break;
    case COMMAND_SET_TWO_PLAYER_CAM_MODE_NOT_BOTH_IN_CAR: // 0x809
        break;
    case COMMAND_GET_LEVEL_DESIGN_COORDS_FOR_OBJECT: // 0x80A
        break;
    case COMMAND_SAVE_TEXT_LABEL_TO_DEBUG_FILE: // 0x80B
        break;
    case COMMAND_GET_CHAR_BREATH: // 0x80C
        break;
    case COMMAND_SET_CHAR_BREATH: // 0x80D
        break;
    case COMMAND_GET_CHAR_HIGHEST_PRIORITY_EVENT: // 0x80E
        break;
    case COMMAND_ARE_PATHS_LOADED_FOR_CAR: // 0x80F
        break;
    case COMMAND_GET_PARKING_NODE_IN_AREA: // 0x810
        break;
    case COMMAND_GET_CAR_CHAR_IS_USING: // 0x811
        break;
    case COMMAND_TASK_PLAY_ANIM_NON_INTERRUPTABLE: // 0x812
        break;
    case COMMAND_FORCE_NEXT_DIE_ANIM: // 0x813
        break;
    case COMMAND_ADD_STUNT_JUMP: // 0x814
        break;
    case COMMAND_SET_OBJECT_COORDINATES_AND_VELOCITY: // 0x815
        break;
    case COMMAND_SET_CHAR_KINDA_STAY_IN_SAME_PLACE: // 0x816
        break;
    case COMMAND_TASK_FOLLOW_PATROL_ROUTE: // 0x817
        break;
    case COMMAND_IS_CHAR_IN_AIR: // 0x818
        break;
    case COMMAND_GET_CHAR_HEIGHT_ABOVE_GROUND: // 0x819
        break;
    case COMMAND_SET_CHAR_WEAPON_SKILL: // 0x81A
        break;
    case COMMAND_ARE_PATHS_LOADED_IN_AREA: // 0x81B
        break;
    case COMMAND_SET_TEXT_EDGE: // 0x81C
        break;
    case COMMAND_SET_CAR_ENGINE_BROKEN: // 0x81D
        break;
    case COMMAND_IS_THIS_MODEL_A_BOAT: // 0x81E
        break;
    case COMMAND_IS_THIS_MODEL_A_PLANE: // 0x81F
        break;
    case COMMAND_IS_THIS_MODEL_A_HELI: // 0x820
        break;
    case COMMAND_IS_3D_COORD_IN_ZONE: // 0x821
        break;
    case COMMAND_SET_FIRST_PERSON_IN_CAR_CAMERA_MODE: // 0x822
        break;
    case COMMAND_TASK_GREET_PARTNER: // 0x823
        break;
    case COMMAND_GET_CLOSEST_PICKUP_COORDS_TO_COORD: // 0x824
        break;
    case COMMAND_SET_HELI_BLADES_FULL_SPEED: // 0x825
        break;
    case COMMAND_DISPLAY_HUD: // 0x826
        break;
    case COMMAND_CONNECT_LODS: // 0x827
        break;
    case COMMAND_SET_MAX_FIRE_GENERATIONS: // 0x828
        break;
    case COMMAND_TASK_DIE_NAMED_ANIM: // 0x829
        break;
    case COMMAND_SET_PLAYER_DUCK_BUTTON: // 0x82A
        break;
    case COMMAND_FIND_NEAREST_MULTIBUILDING: // 0x82B
        break;
    case COMMAND_SET_MULTIBUILDING_MODEL: // 0x82C
        break;
    case COMMAND_GET_NUMBER_MULTIBUILDING_MODELS: // 0x82D
        break;
    case COMMAND_GET_MULTIBUILDING_MODEL_INDEX: // 0x82E
        break;
    case COMMAND_SET_CURRENT_BUYABLE_PROPERTY: // 0x82F
        break;
    case COMMAND_SET_POOL_TABLE_COORDS: // 0x830
        break;
    case COMMAND_IS_AUDIO_BUILD: // 0x831
        break;
    case COMMAND_CLEAR_QUEUED_DIALOGUE: // 0x832
        break;
    case COMMAND_HAS_OBJECT_BEEN_PHOTOGRAPHED: // 0x833
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x470A90
int8 CRunningScript::ProcessCommands2100To2199(int32 commandId) {
    switch (commandId) {
    case COMMAND_DO_CAMERA_BUMP: // 0x834
        break;
    case COMMAND_GET_CURRENT_DATE: // 0x835
        break;
    case COMMAND_SET_OBJECT_ANIM_SPEED: // 0x836
        break;
    case COMMAND_IS_OBJECT_PLAYING_ANIM: // 0x837
        break;
    case COMMAND_SET_OBJECT_ANIM_PLAYING_FLAG: // 0x838
        break;
    case COMMAND_GET_OBJECT_ANIM_CURRENT_TIME: // 0x839
        break;
    case COMMAND_SET_OBJECT_ANIM_CURRENT_TIME: // 0x83A
        break;
    case COMMAND_GET_OBJECT_ANIM_TOTAL_TIME: // 0x83B
        break;
    case COMMAND_SET_CHAR_VELOCITY: // 0x83C
        break;
    case COMMAND_GET_CHAR_VELOCITY: // 0x83D
        break;
    case COMMAND_SET_CHAR_ROTATION: // 0x83E
        break;
    case COMMAND_GET_CAR_UPRIGHT_VALUE: // 0x83F
        break;
    case COMMAND_SET_VEHICLE_AREA_VISIBLE: // 0x840
        break;
    case COMMAND_SELECT_WEAPONS_FOR_VEHICLE: // 0x841
        break;
    case COMMAND_GET_CITY_PLAYER_IS_IN: // 0x842
        break;
    case COMMAND_GET_NAME_OF_ZONE: // 0x843
        break;
    case COMMAND_IS_VAR_TEXT_LABEL_EMPTY: // 0x844
        break;
    case COMMAND_IS_LVAR_TEXT_LABEL_EMPTY: // 0x845
        break;
    case COMMAND_IS_VAR_TEXT_LABEL16_EMPTY: // 0x846
        break;
    case COMMAND_IS_LVAR_TEXT_LABEL16_EMPTY: // 0x847
        break;
    case COMMAND_SWITCH: // 0x848
        break;
    case COMMAND_ENDSWITCH: // 0x849
        break;
    case COMMAND_CASE: // 0x84A
        break;
    case COMMAND_DEFAULT: // 0x84B
        break;
    case COMMAND_BREAK: // 0x84C
        break;
    case COMMAND_ACTIVATE_INTERIOR_PEDS: // 0x84D
        break;
    case COMMAND_SET_VEHICLE_CAN_BE_TARGETTED: // 0x84E
        break;
    case COMMAND_GET_GROUP_LEADER: // 0x84F
        break;
    case COMMAND_TASK_FOLLOW_FOOTSTEPS: // 0x850
        break;
    case COMMAND_DAMAGE_CHAR: // 0x851
        break;
    case COMMAND_SET_CAR_CAN_BE_VISIBLY_DAMAGED: // 0x852
        break;
    case COMMAND_SET_HELI_REACHED_TARGET_DISTANCE: // 0x853
        break;
    case COMMAND_BLOCK_NODES_IN_AREA: // 0x854
        break;
    case COMMAND_GET_SOUND_LEVEL_AT_COORDS: // 0x855
        break;
    case COMMAND_SET_CHAR_ALLOWED_TO_DUCK: // 0x856
        break;
    case COMMAND_SET_WATER_CONFIGURATION: // 0x857
        break;
    case COMMAND_SET_HEADING_FOR_ATTACHED_PLAYER: // 0x858
        break;
    case COMMAND_TASK_WALK_ALONGSIDE_CHAR: // 0x859
        break;
    case COMMAND_CREATE_EMERGENCY_SERVICES_CAR: // 0x85A
        break;
    case COMMAND_TASK_KINDA_STAY_IN_SAME_PLACE: // 0x85B
        break;
    case COMMAND_TASK_USE_ATTRACTOR_ADVANCED: // 0x85C
        break;
    case COMMAND_TASK_FOLLOW_PATH_NODES_TO_COORD_SHOOTING: // 0x85D
        break;
    case COMMAND_START_PLAYBACK_RECORDED_CAR_LOOPED: // 0x85E
        break;
    case COMMAND_START_PLAYBACK_RECORDED_CAR_USING_AI_LOOPED: // 0x85F
        break;
    case COMMAND_SET_CHAR_AREA_VISIBLE: // 0x860
        break;
    case COMMAND_IS_ATTACHED_PLAYER_HEADING_ACHIEVED: // 0x861
        break;
    case COMMAND_GET_MODEL_NAME_FOR_DEBUG_ONLY: // 0x862
        break;
    case COMMAND_TASK_USE_NEARBY_ENTRY_EXIT: // 0x863
        break;
    case COMMAND_ENABLE_ENTRY_EXIT_PLAYER_GROUP_WARPING: // 0x864
        break;
    case COMMAND_FREEZE_STATE_OF_INTERIORS: // 0x865
        break;
    case COMMAND_GET_CLOSEST_STEALABLE_OBJECT: // 0x866
        break;
    case COMMAND_IS_PROCEDURAL_INTERIOR_ACTIVE: // 0x867
        break;
    case COMMAND_CLEAR_THIS_VIEW_INTEGER_VARIABLE: // 0x868
        break;
    case COMMAND_CLEAR_THIS_VIEW_FLOAT_VARIABLE: // 0x869
        break;
    case COMMAND_CLEAR_ALL_VIEW_VARIABLES: // 0x86A
        break;
    case COMMAND_CLEAR_THIS_INTEGER_WATCHPOINT: // 0x86B
        break;
    case COMMAND_CLEAR_THIS_FLOAT_WATCHPOINT: // 0x86C
        break;
    case COMMAND_CLEAR_ALL_BREAKPOINTS: // 0x86D
        break;
    case COMMAND_CLEAR_ALL_WATCHPOINTS: // 0x86E
        break;
    case COMMAND_IS_THIS_MODEL_A_TRAIN: // 0x86F
        break;
    case COMMAND_GET_VEHICLE_CHAR_IS_STANDING_ON: // 0x870
        break;
    case COMMAND_SWITCH_START: // 0x871
        break;
    case COMMAND_SWITCH_CONTINUED: // 0x872
        break;
    case COMMAND_REMOVE_CAR_RECORDING: // 0x873
        break;
    case COMMAND_SET_ZONE_POPULATION_RACE: // 0x874
        break;
    case COMMAND_SET_OBJECT_ONLY_DAMAGED_BY_PLAYER: // 0x875
        break;
    case COMMAND_CREATE_BIRDS: // 0x876
        break;
    case COMMAND_GET_VEHICLE_DIRT_LEVEL: // 0x877
        break;
    case COMMAND_SET_VEHICLE_DIRT_LEVEL: // 0x878
        break;
    case COMMAND_SET_GANG_WARS_ACTIVE: // 0x879
        break;
    case COMMAND_IS_GANG_WAR_GOING_ON: // 0x87A
        break;
    case COMMAND_GIVE_PLAYER_CLOTHES_OUTSIDE_SHOP: // 0x87B
        break;
    case COMMAND_CLEAR_LOADED_SHOP: // 0x87C
        break;
    case COMMAND_SET_GROUP_SEQUENCE: // 0x87D
        break;
    case COMMAND_SET_CHAR_DROPS_WEAPONS_WHEN_DEAD: // 0x87E
        break;
    case COMMAND_SET_CHAR_NEVER_LEAVES_GROUP: // 0x87F
        break;
    case COMMAND_DRAW_RECT_WITH_TITLE: // 0x880
        break;
    case COMMAND_SET_PLAYER_FIRE_BUTTON: // 0x881
        break;
    case COMMAND_SET_ATTRACTOR_RADIUS: // 0x882
        break;
    case COMMAND_ATTACH_FX_SYSTEM_TO_CHAR_BONE: // 0x883
        break;
    case COMMAND_REGISTER_ATTRACTOR_SCRIPT_BRAIN_FOR_CODE_USE: // 0x884
        break;
    case COMMAND_CONST_INT: // 0x885
        break;
    case COMMAND_CONST_FLOAT: // 0x886
        break;
    case COMMAND_SET_HEADING_LIMIT_FOR_ATTACHED_CHAR: // 0x887
        break;
    case COMMAND_ADD_BLIP_FOR_DEAD_CHAR: // 0x888
        break;
    case COMMAND_GET_DEAD_CHAR_COORDINATES: // 0x889
        break;
    case COMMAND_TASK_PLAY_ANIM_WITH_FLAGS: // 0x88A
        break;
    case COMMAND_SET_VEHICLE_AIR_RESISTANCE_MULTIPLIER: // 0x88B
        break;
    case COMMAND_SET_CAR_COORDINATES_NO_OFFSET: // 0x88C
        break;
    case COMMAND_SET_USES_COLLISION_OF_CLOSEST_OBJECT_OF_TYPE: // 0x88D
        break;
    case COMMAND_SET_TIME_ONE_DAY_FORWARD: // 0x88E
        break;
    case COMMAND_SET_TIME_ONE_DAY_BACK: // 0x88F
        break;
    case COMMAND_SET_TIMER_BEEP_COUNTDOWN_TIME: // 0x890
        break;
    case COMMAND_TASK_SIT_IN_RESTAURANT: // 0x891
        break;
    case COMMAND_GET_RANDOM_ATTRACTOR_ON_CLOSEST_OBJECT_OF_TYPE: // 0x892
        break;
    case COMMAND_ATTACH_TRAILER_TO_CAB: // 0x893
        break;
    case COMMAND_ADD_INTERESTING_ENTITY_FOR_CHAR: // 0x894
        break;
    case COMMAND_CLEAR_INTERESTING_ENTITIES_FOR_CHAR: // 0x895
        break;
    case COMMAND_GET_CLOSEST_ATTRACTOR: // 0x896
        break;
    case COMMAND_IS_VEHICLE_TOUCHING_OBJECT: // 0x897
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x474900
int8 CRunningScript::ProcessCommands2200To2299(int32 commandId) {
    switch (commandId) {
    case COMMAND_ENABLE_CRANE_CONTROLS: // 0x898
        break;
    case COMMAND_ALLOCATE_SCRIPT_TO_ATTRACTOR: // 0x899
        break;
    case COMMAND_GET_CLOSEST_ATTRACTOR_WITH_THIS_SCRIPT: // 0x89A
        break;
    case COMMAND_IS_PLAYER_IN_POSITION_FOR_CONVERSATION: // 0x89B
        break;
    case COMMAND_ENABLE_CONVERSATION: // 0x89C
        break;
    case COMMAND_GET_CONVERSATION_STATUS: // 0x89D
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_SPHERE_ONLY_DRUGS_BUYERS: // 0x89E
        break;
    case COMMAND_GET_PED_TYPE: // 0x89F
        break;
    case COMMAND_TASK_USE_CLOSEST_MAP_ATTRACTOR: // 0x8A0
        break;
    case COMMAND_GET_CHAR_MAP_ATTRACTOR_STATUS: // 0x8A1
        break;
    case COMMAND_PLANE_ATTACK_PLAYER_USING_DOG_FIGHT: // 0x8A2
        break;
    case COMMAND_CAN_TRIGGER_GANG_WAR_WHEN_ON_A_MISSION: // 0x8A3
        break;
    case COMMAND_CONTROL_MOVABLE_VEHICLE_PART: // 0x8A4
        break;
    case COMMAND_WINCH_CAN_PICK_VEHICLE_UP: // 0x8A5
        break;
    case COMMAND_OPEN_CAR_DOOR_A_BIT: // 0x8A6
        break;
    case COMMAND_IS_CAR_DOOR_FULLY_OPEN: // 0x8A7
        break;
    case COMMAND_SET_ALWAYS_DRAW_3D_MARKERS: // 0x8A8
        break;
    case COMMAND_STREAM_SCRIPT: // 0x8A9
        break;
    case COMMAND_STREAM_SCRIPT_INTERNAL: // 0x8AA
        break;
    case COMMAND_HAS_STREAMED_SCRIPT_LOADED: // 0x8AB
        break;
    case COMMAND_SET_GANG_WARS_TRAINING_MISSION: // 0x8AC
        break;
    case COMMAND_SET_CHAR_HAS_USED_ENTRY_EXIT: // 0x8AD
        break;
    case COMMAND_DRAW_WINDOW_TEXT: // 0x8AE
        break;
    case COMMAND_SET_CHAR_MAX_HEALTH: // 0x8AF
        break;
    case COMMAND_SET_CAR_PITCH: // 0x8B0
        break;
    case COMMAND_SET_NIGHT_VISION: // 0x8B1
        break;
    case COMMAND_SET_INFRARED_VISION: // 0x8B2
        break;
    case COMMAND_SET_ZONE_FOR_GANG_WARS_TRAINING: // 0x8B3
        break;
    case COMMAND_IS_GLOBAL_VAR_BIT_SET_CONST: // 0x8B4
        break;
    case COMMAND_IS_GLOBAL_VAR_BIT_SET_VAR: // 0x8B5
        break;
    case COMMAND_IS_GLOBAL_VAR_BIT_SET_LVAR: // 0x8B6
        break;
    case COMMAND_IS_LOCAL_VAR_BIT_SET_CONST: // 0x8B7
        break;
    case COMMAND_IS_LOCAL_VAR_BIT_SET_VAR: // 0x8B8
        break;
    case COMMAND_IS_LOCAL_VAR_BIT_SET_LVAR: // 0x8B9
        break;
    case COMMAND_SET_GLOBAL_VAR_BIT_CONST: // 0x8BA
        break;
    case COMMAND_SET_GLOBAL_VAR_BIT_VAR: // 0x8BB
        break;
    case COMMAND_SET_GLOBAL_VAR_BIT_LVAR: // 0x8BC
        break;
    case COMMAND_SET_LOCAL_VAR_BIT_CONST: // 0x8BD
        break;
    case COMMAND_SET_LOCAL_VAR_BIT_VAR: // 0x8BE
        break;
    case COMMAND_SET_LOCAL_VAR_BIT_LVAR: // 0x8BF
        break;
    case COMMAND_CLEAR_GLOBAL_VAR_BIT_CONST: // 0x8C0
        break;
    case COMMAND_CLEAR_GLOBAL_VAR_BIT_VAR: // 0x8C1
        break;
    case COMMAND_CLEAR_GLOBAL_VAR_BIT_LVAR: // 0x8C2
        break;
    case COMMAND_CLEAR_LOCAL_VAR_BIT_CONST: // 0x8C3
        break;
    case COMMAND_CLEAR_LOCAL_VAR_BIT_VAR: // 0x8C4
        break;
    case COMMAND_CLEAR_LOCAL_VAR_BIT_LVAR: // 0x8C5
        break;
    case COMMAND_SET_CHAR_CAN_BE_KNOCKED_OFF_BIKE: // 0x8C6
        break;
    case COMMAND_SET_CHAR_COORDINATES_DONT_WARP_GANG: // 0x8C7
        break;
    case COMMAND_ADD_PRICE_MODIFIER: // 0x8C8
        break;
    case COMMAND_REMOVE_PRICE_MODIFIER: // 0x8C9
        break;
    case COMMAND_INIT_ZONE_POPULATION_SETTINGS: // 0x8CA
        break;
    case COMMAND_EXPLODE_CAR_IN_CUTSCENE_SHAKE_AND_BITS: // 0x8CB
        break;
    case COMMAND_PICK_UP_OBJECT_WITH_WINCH: // 0x8CC
        break;
    case COMMAND_PICK_UP_VEHICLE_WITH_WINCH: // 0x8CD
        break;
    case COMMAND_PICK_UP_CHAR_WITH_WINCH: // 0x8CE
        break;
    case COMMAND_STORE_CAR_IN_NEAREST_IMPOUNDING_GARAGE: // 0x8CF
        break;
    case COMMAND_IS_SKIP_CUTSCENE_BUTTON_PRESSED: // 0x8D0
        break;
    case COMMAND_GET_CUTSCENE_OFFSET: // 0x8D1
        break;
    case COMMAND_SET_OBJECT_SCALE: // 0x8D2
        break;
    case COMMAND_GET_CURRENT_POPULATION_ZONE_TYPE: // 0x8D3
        break;
    case COMMAND_CREATE_MENU: // 0x8D4
        break;
    case COMMAND_CONSTANT_INT: // 0x8D5
        break;
    case COMMAND_SET_MENU_COLUMN_ORIENTATION: // 0x8D6
        break;
    case COMMAND_GET_MENU_ITEM_SELECTED: // 0x8D7
        break;
    case COMMAND_GET_MENU_ITEM_ACCEPTED: // 0x8D8
        break;
    case COMMAND_ACTIVATE_MENU_ITEM: // 0x8D9
        break;
    case COMMAND_DELETE_MENU: // 0x8DA
        break;
    case COMMAND_SET_MENU_COLUMN: // 0x8DB
        break;
    case COMMAND_SET_BLIP_ENTRY_EXIT: // 0x8DC
        break;
    case COMMAND_SWITCH_DEATH_PENALTIES: // 0x8DD
        break;
    case COMMAND_SWITCH_ARREST_PENALTIES: // 0x8DE
        break;
    case COMMAND_SET_EXTRA_HOSPITAL_RESTART_POINT: // 0x8DF
        break;
    case COMMAND_SET_EXTRA_POLICE_STATION_RESTART_POINT: // 0x8E0
        break;
    case COMMAND_FIND_NUMBER_TAGS_TAGGED: // 0x8E1
        break;
    case COMMAND_GET_TERRITORY_UNDER_CONTROL_PERCENTAGE: // 0x8E2
        break;
    case COMMAND_IS_OBJECT_IN_ANGLED_AREA_2D: // 0x8E3
        break;
    case COMMAND_IS_OBJECT_IN_ANGLED_AREA_3D: // 0x8E4
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_SPHERE_NO_BRAIN: // 0x8E5
        break;
    case COMMAND_SET_PLANE_UNDERCARRIAGE_UP: // 0x8E6
        break;
    case COMMAND_DISABLE_ALL_ENTRY_EXITS: // 0x8E7
        break;
    case COMMAND_ATTACH_ANIMS_TO_MODEL: // 0x8E8
        break;
    case COMMAND_SET_OBJECT_AS_STEALABLE: // 0x8E9
        break;
    case COMMAND_SET_CREATE_RANDOM_GANG_MEMBERS: // 0x8EA
        break;
    case COMMAND_ADD_SPARKS: // 0x8EB
        break;
    case COMMAND_GET_VEHICLE_CLASS: // 0x8EC
        break;
    case COMMAND_CLEAR_CONVERSATION_FOR_CHAR: // 0x8ED
        break;
    case COMMAND_SET_MENU_ITEM_WITH_NUMBER: // 0x8EE
        break;
    case COMMAND_SET_MENU_ITEM_WITH_2_NUMBERS: // 0x8EF
        break;
    case COMMAND_APPEND_TO_NEXT_CUTSCENE: // 0x8F0
        break;
    case COMMAND_GET_NAME_OF_INFO_ZONE: // 0x8F1
        break;
    case COMMAND_VEHICLE_CAN_BE_TARGETTED_BY_HS_MISSILE: // 0x8F2
        break;
    case COMMAND_SET_FREEBIES_IN_VEHICLE: // 0x8F3
        break;
    case COMMAND_SET_SCRIPT_LIMIT_TO_GANG_SIZE: // 0x8F4
        break;
    case COMMAND_MAKE_PLAYER_GANG_DISAPPEAR: // 0x8F5
        break;
    case COMMAND_MAKE_PLAYER_GANG_REAPPEAR: // 0x8F6
        break;
    case COMMAND_GET_CLOTHES_ITEM: // 0x8F7
        break;
    case COMMAND_SHOW_UPDATE_STATS: // 0x8F8
        break;
    case COMMAND_IS_VAR_TEXT_LABEL16_EQUAL_TO_TEXT_LABEL: // 0x8F9
        break;
    case COMMAND_IS_LVAR_TEXT_LABEL16_EQUAL_TO_TEXT_LABEL: // 0x8FA
        break;
    case COMMAND_SET_COORD_BLIP_APPEARANCE: // 0x8FB
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x4762D0
int8 CRunningScript::ProcessCommands2300To2399(int32 commandId) {
    switch (commandId) {
    case COMMAND_GET_MENU_POSITION: // 0x8FC
        break;
    case COMMAND_SET_HEATHAZE_EFFECT: // 0x8FD
        break;
    case COMMAND_IS_HELP_MESSAGE_BEING_DISPLAYED: // 0x8FE
        break;
    case COMMAND_HAS_OBJECT_BEEN_DAMAGED_BY_WEAPON: // 0x8FF
        break;
    case COMMAND_CLEAR_OBJECT_LAST_WEAPON_DAMAGE: // 0x900
        break;
    case COMMAND_SET_PLAYER_JUMP_BUTTON: // 0x901
        break;
    case COMMAND_SET_OBJECT_BEEN_PHOTOGRAPHED_FLAG: // 0x902
        break;
    case COMMAND_SET_CHAR_BEEN_PHOTOGRAPHED_FLAG: // 0x903
        break;
    case COMMAND_GET_HUD_COLOUR: // 0x904
        break;
    case COMMAND_LOCK_DOOR: // 0x905
        break;
    case COMMAND_SET_OBJECT_MASS: // 0x906
        break;
    case COMMAND_GET_OBJECT_MASS: // 0x907
        break;
    case COMMAND_SET_OBJECT_TURN_MASS: // 0x908
        break;
    case COMMAND_GET_OBJECT_TURN_MASS: // 0x909
        break;
    case COMMAND_IS_PLAYBACK_FOR_CAR_PAUSED: // 0x90A
        break;
    case COMMAND_TRIGGER_PED_BOUNCE: // 0x90B
        break;
    case COMMAND_SET_SPECIFIC_ZONE_TO_TRIGGER_GANG_WAR: // 0x90C
        break;
    case COMMAND_CLEAR_SPECIFIC_ZONES_TO_TRIGGER_GANG_WAR: // 0x90D
        break;
    case COMMAND_SET_ACTIVE_MENU_ITEM: // 0x90E
        break;
    case COMMAND_MARK_STREAMED_SCRIPT_AS_NO_LONGER_NEEDED: // 0x90F
        break;
    case COMMAND_REMOVE_STREAMED_SCRIPT: // 0x910
        break;
    case COMMAND_REGISTER_STREAMED_SCRIPT: // 0x911
        break;
    case COMMAND_SET_MESSAGE_FORMATTING: // 0x912
        break;
    case COMMAND_START_NEW_STREAMED_SCRIPT: // 0x913
        break;
    case COMMAND_REGISTER_STREAMED_SCRIPT_INTERNAL: // 0x914
        break;
    case COMMAND_SET_WEATHER_TO_APPROPRIATE_TYPE_NOW: // 0x915
        break;
    case COMMAND_WINCH_CAN_PICK_OBJECT_UP: // 0x916
        break;
    case COMMAND_SWITCH_AUDIO_ZONE: // 0x917
        break;
    case COMMAND_SET_CAR_ENGINE_ON: // 0x918
        break;
    case COMMAND_SET_CAR_LIGHTS_ON: // 0x919
        break;
    case COMMAND_GET_LATEST_CONSOLE_COMMAND: // 0x91A
        break;
    case COMMAND_RESET_LATEST_CONSOLE_COMMAND: // 0x91B
        break;
    case COMMAND_GET_USER_OF_CLOSEST_MAP_ATTRACTOR: // 0x91C
        break;
    case COMMAND_SWITCH_ROADS_BACK_TO_ORIGINAL: // 0x91D
        break;
    case COMMAND_SWITCH_PED_ROADS_BACK_TO_ORIGINAL: // 0x91E
        break;
    case COMMAND_GET_PLANE_UNDERCARRIAGE_POSITION: // 0x91F
        break;
    case COMMAND_CAMERA_SET_VECTOR_TRACK: // 0x920
        break;
    case COMMAND_CAMERA_SET_SHAKE_SIMULATION: // 0x921
        break;
    case COMMAND_CAMERA_SET_LERP_FOV: // 0x922
        break;
    case COMMAND_SWITCH_AMBIENT_PLANES: // 0x923
        break;
    case COMMAND_SET_DARKNESS_EFFECT: // 0x924
        break;
    case COMMAND_CAMERA_RESET_NEW_SCRIPTABLES: // 0x925
        break;
    case COMMAND_GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT: // 0x926
        break;
    case COMMAND_ALLOCATE_STREAMED_SCRIPT_TO_PED_GENERATOR: // 0x927
        break;
    case COMMAND_ALLOCATE_STREAMED_SCRIPT_TO_RANDOM_PED: // 0x928
        break;
    case COMMAND_ALLOCATE_STREAMED_SCRIPT_TO_OBJECT: // 0x929
        break;
    case COMMAND_SET_PLAYER_CAN_BE_DAMAGED: // 0x92A
        break;
    case COMMAND_GET_GROUP_MEMBER: // 0x92B
        break;
    case COMMAND_GET_PLAYERS_GANG_IN_CAR_ACTIVE: // 0x92C
        break;
    case COMMAND_SET_PLAYERS_GANG_IN_CAR_ACTIVE: // 0x92D
        break;
    case COMMAND_GET_WATER_HEIGHT_AT_COORDS: // 0x92E
        break;
    case COMMAND_CAMERA_PERSIST_TRACK: // 0x92F
        break;
    case COMMAND_CAMERA_PERSIST_POS: // 0x930
        break;
    case COMMAND_CAMERA_PERSIST_FOV: // 0x931
        break;
    case COMMAND_CAMERA_IS_FOV_RUNNING: // 0x932
        break;
    case COMMAND_CAMERA_IS_VECTOR_MOVE_RUNNING: // 0x933
        break;
    case COMMAND_CAMERA_IS_VECTOR_TRACK_RUNNING: // 0x934
        break;
    case COMMAND_CAMERA_IS_SHAKE_RUNNING: // 0x935
        break;
    case COMMAND_CAMERA_SET_VECTOR_MOVE: // 0x936
        break;
    case COMMAND_DRAW_WINDOW: // 0x937
        break;
    case COMMAND_CLEAR_ALL_QUEUED_DIALOGUE: // 0x938
        break;
    case COMMAND_ATTACH_CAR_TO_OBJECT: // 0x939
        break;
    case COMMAND_SET_GARAGE_RESPRAY_FREE: // 0x93A
        break;
    case COMMAND_SET_CHAR_BULLETPROOF_VEST: // 0x93B
        break;
    case COMMAND_SET_ONSCREEN_COUNTER_COLOUR: // 0x93C
        break;
    case COMMAND_SET_CINEMA_CAMERA: // 0x93D
        break;
    case COMMAND_SET_CHAR_FIRE_DAMAGE_MULTIPLIER: // 0x93E
        break;
    case COMMAND_IS_FIRE_BUTTON_PRESSED: // 0x93F
        break;
    case COMMAND_SET_GROUP_FOLLOW_STATUS: // 0x940
        break;
    case COMMAND_SET_SEARCHLIGHT_CLIP_IF_COLLIDING: // 0x941
        break;
    case COMMAND_HAS_PLAYER_BOUGHT_ITEM: // 0x942
        break;
    case COMMAND_SET_CAMERA_BEHIND_CHAR: // 0x943
        break;
    case COMMAND_SET_CAMERA_IN_FRONT_OF_CHAR: // 0x944
        break;
    case COMMAND_GET_PLAYER_MAX_ARMOUR: // 0x945
        break;
    case COMMAND_SET_CHAR_USES_UPPERBODY_DAMAGE_ANIMS_ONLY: // 0x946
        break;
    case COMMAND_SET_CHAR_SAY_CONTEXT: // 0x947
        break;
    case COMMAND_ADD_EXPLOSION_VARIABLE_SHAKE: // 0x948
        break;
    case COMMAND_ATTACH_MISSION_AUDIO_TO_CHAR: // 0x949
        break;
    case COMMAND_UPDATE_PICKUP_MONEY_PER_DAY: // 0x94A
        break;
    case COMMAND_GET_NAME_OF_ENTRY_EXIT_CHAR_USED: // 0x94B
        break;
    case COMMAND_GET_POSITION_OF_ENTRY_EXIT_CHAR_USED: // 0x94C
        break;
    case COMMAND_IS_CHAR_TALKING: // 0x94D
        break;
    case COMMAND_DISABLE_CHAR_SPEECH: // 0x94E
        break;
    case COMMAND_ENABLE_CHAR_SPEECH: // 0x94F
        break;
    case COMMAND_SET_UP_SKIP: // 0x950
        break;
    case COMMAND_CLEAR_SKIP: // 0x951
        break;
    case COMMAND_PRELOAD_BEAT_TRACK: // 0x952
        break;
    case COMMAND_GET_BEAT_TRACK_STATUS: // 0x953
        break;
    case COMMAND_PLAY_BEAT_TRACK: // 0x954
        break;
    case COMMAND_STOP_BEAT_TRACK: // 0x955
        break;
    case COMMAND_FIND_MAX_NUMBER_OF_GROUP_MEMBERS: // 0x956
        break;
    case COMMAND_VEHICLE_DOES_PROVIDE_COVER: // 0x957
        break;
    case COMMAND_CREATE_SNAPSHOT_PICKUP: // 0x958
        break;
    case COMMAND_CREATE_HORSESHOE_PICKUP: // 0x959
        break;
    case COMMAND_CREATE_OYSTER_PICKUP: // 0x95A
        break;
    case COMMAND_HAS_OBJECT_BEEN_UPROOTED: // 0x95B
        break;
    case COMMAND_ADD_SMOKE_PARTICLE: // 0x95C
        break;
    case COMMAND_IS_CHAR_STUCK_UNDER_CAR: // 0x95D
        break;
    case COMMAND_CONTROL_CAR_DOOR: // 0x95E
        break;
    case COMMAND_GET_DOOR_ANGLE_RATIO: // 0x95F
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x478000
int8 CRunningScript::ProcessCommands2400To2499(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_PLAYER_DISPLAY_VITAL_STATS_BUTTON: // 0x960
        break;
    case COMMAND_SET_CHAR_KEEP_TASK: // 0x961
        break;
    case COMMAND_DOES_CAR_HAVE_ROOF: // 0x962
        break;
    case COMMAND_SET_BLIP_FADE: // 0x963
        break;
    case COMMAND_CREATE_MENU_GRID: // 0x964
        break;
    case COMMAND_IS_CHAR_SWIMMING: // 0x965
        break;
    case COMMAND_GET_CHAR_SWIM_STATE: // 0x966
        break;
    case COMMAND_START_CHAR_FACIAL_TALK: // 0x967
        break;
    case COMMAND_STOP_CHAR_FACIAL_TALK: // 0x968
        break;
    case COMMAND_IS_BIG_VEHICLE: // 0x969
        break;
    case COMMAND_SWITCH_POLICE_HELIS: // 0x96A
        break;
    case COMMAND_STORE_CAR_MOD_STATE: // 0x96B
        break;
    case COMMAND_RESTORE_CAR_MOD_STATE: // 0x96C
        break;
    case COMMAND_GET_CURRENT_CAR_MOD: // 0x96D
        break;
    case COMMAND_IS_CAR_LOW_RIDER: // 0x96E
        break;
    case COMMAND_IS_CAR_STREET_RACER: // 0x96F
        break;
    case COMMAND_FORCE_DEATH_RESTART: // 0x970
        break;
    case COMMAND_SYNC_WATER: // 0x971
        break;
    case COMMAND_SET_CHAR_COORDINATES_NO_OFFSET: // 0x972
        break;
    case COMMAND_DOES_SCRIPT_FIRE_EXIST: // 0x973
        break;
    case COMMAND_RESET_STUFF_UPON_RESURRECTION: // 0x974
        break;
    case COMMAND_IS_EMERGENCY_SERVICES_VEHICLE: // 0x975
        break;
    case COMMAND_KILL_FX_SYSTEM_NOW: // 0x976
        break;
    case COMMAND_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE: // 0x977
        break;
    case COMMAND_COPY_SHARED_CHAR_DECISION_MAKER: // 0x978
        break;
    case COMMAND_LOAD_SHARED_CHAR_DECISION_MAKER: // 0x979
        break;
    case COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_POSITION: // 0x97A
        break;
    case COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_OBJECT: // 0x97B
        break;
    case COMMAND_ATTACH_MISSION_AUDIO_TO_OBJECT: // 0x97C
        break;
    case COMMAND_GET_NUM_CAR_COLOURS: // 0x97D
        break;
    case COMMAND_IS_POLICE_VEHICLE_IN_PURSUIT: // 0x97E
        break;
    case COMMAND_GET_CAR_COLOUR_FROM_MENU_INDEX: // 0x97F
        break;
    case COMMAND_EXTINGUISH_FIRE_AT_POINT: // 0x980
        break;
    case COMMAND_HAS_TRAIN_DERAILED: // 0x981
        break;
    case COMMAND_SET_CHAR_FORCE_DIE_IN_CAR: // 0x982
        break;
    case COMMAND_SET_ONLY_CREATE_GANG_MEMBERS: // 0x983
        break;
    case COMMAND_GET_OBJECT_MODEL: // 0x984
        break;
    case COMMAND_SET_CHAR_USES_COLLISION_CLOSEST_OBJECT_OF_TYPE: // 0x985
        break;
    case COMMAND_CLEAR_ALL_SCRIPT_FIRE_FLAGS: // 0x986
        break;
    case COMMAND_GET_CAR_BLOCKING_CAR: // 0x987
        break;
    case COMMAND_GET_CURRENT_VEHICLE_PAINTJOB: // 0x988
        break;
    case COMMAND_SET_HELP_MESSAGE_BOX_SIZE: // 0x989
        break;
    case COMMAND_SET_GUNSHOT_SENSE_RANGE_FOR_RIOT2: // 0x98A
        break;
    case COMMAND_STRING_CAT16: // 0x98B
        break;
    case COMMAND_STRING_CAT8: // 0x98C
        break;
    case COMMAND_GET_CAR_MOVING_COMPONENT_OFFSET: // 0x98D
        break;
    case COMMAND_SET_NAMED_ENTRY_EXIT_FLAG: // 0x98E
        break;
    case COMMAND_RADIANS_TO_DEGREES: // 0x98F
        break;
    case COMMAND_DEGREES_TO_RADIANS: // 0x990
        break;
    case COMMAND_PAUSE_CURRENT_BEAT_TRACK: // 0x991
        break;
    case COMMAND_SET_PLAYER_CYCLE_WEAPON_BUTTON: // 0x992
        break;
    case COMMAND_SET_CHAR_AIR_RESISTANCE_MULTIPLIER: // 0x993
        break;
    case COMMAND_MARK_ROAD_NODE_AS_DONT_WANDER: // 0x994
        break;
    case COMMAND_UNMARK_ALL_ROAD_NODES_AS_DONT_WANDER: // 0x995
        break;
    case COMMAND_SET_CHECKPOINT_HEADING: // 0x996
        break;
    case COMMAND_SET_MISSION_RESPECT_TOTAL: // 0x997
        break;
    case COMMAND_AWARD_PLAYER_MISSION_RESPECT: // 0x998
        break;
    case COMMAND_SET_PLAYER_FIRE_WITH_SHOULDER_BUTTON: // 0x999
        break;
    case COMMAND_SET_CAR_COLLISION: // 0x99A
        break;
    case COMMAND_CHANGE_PLAYBACK_TO_USE_AI: // 0x99B
        break;
    case COMMAND_CAMERA_SET_SHAKE_SIMULATION_SIMPLE: // 0x99C
        break;
    case COMMAND_IS_NIGHT_VISION_ACTIVE: // 0x99D
        break;
    case COMMAND_SET_CREATE_RANDOM_COPS: // 0x99E
        break;
    case COMMAND_TASK_SET_IGNORE_WEAPON_RANGE_FLAG: // 0x99F
        break;
    case COMMAND_TASK_PICK_UP_SECOND_OBJECT: // 0x9A0
        break;
    case COMMAND_DROP_SECOND_OBJECT: // 0x9A1
        break;
    case COMMAND_REMOVE_OBJECT_ELEGANTLY: // 0x9A2
        break;
    case COMMAND_DRAW_CROSSHAIR: // 0x9A3
        break;
    case COMMAND_SET_UP_CONVERSATION_NODE_WITH_SPEECH: // 0x9A4
        break;
    case COMMAND_SET_CCTV_EFFECT: // 0x9A5
        break;
    case COMMAND_SHOW_BLIPS_ON_ALL_LEVELS: // 0x9A6
        break;
    case COMMAND_SET_CHAR_DRUGGED_UP: // 0x9A7
        break;
    case COMMAND_IS_CHAR_HEAD_MISSING: // 0x9A8
        break;
    case COMMAND_GET_HASH_KEY: // 0x9A9
        break;
    case COMMAND_SET_UP_CONVERSATION_END_NODE_WITH_SPEECH: // 0x9AA
        break;
    case COMMAND_RANDOM_PASSENGER_SAY: // 0x9AB
        break;
    case COMMAND_HIDE_ALL_FRONTEND_BLIPS: // 0x9AC
        break;
    case COMMAND_SET_PLAYER_IN_CAR_CAMERA_MODE: // 0x9AD
        break;
    case COMMAND_IS_CHAR_IN_ANY_TRAIN: // 0x9AE
        break;
    case COMMAND_SET_UP_SKIP_AFTER_MISSION: // 0x9AF
        break;
    case COMMAND_SET_VEHICLE_IS_CONSIDERED_BY_PLAYER: // 0x9B0
        break;
    case COMMAND_GET_CPU_LEVEL: // 0x9B1
        break;
    case COMMAND_GET_RANDOM_CAR_MODEL_IN_MEMORY: // 0x9B2
        break;
    case COMMAND_GET_CAR_DOOR_LOCK_STATUS: // 0x9B3
        break;
    case COMMAND_SET_CLOSEST_ENTRY_EXIT_FLAG: // 0x9B4
        break;
    case COMMAND_SET_CHAR_SIGNAL_AFTER_KILL: // 0x9B5
        break;
    case COMMAND_SET_CHAR_WANTED_BY_POLICE: // 0x9B6
        break;
    case COMMAND_SET_ZONE_NO_COPS: // 0x9B7
        break;
    case COMMAND_ADD_BLOOD: // 0x9B8
        break;
    case COMMAND_DISPLAY_CAR_NAMES: // 0x9B9
        break;
    case COMMAND_DISPLAY_ZONE_NAMES: // 0x9BA
        break;
    case COMMAND_IS_CAR_DOOR_DAMAGED: // 0x9BB
        break;
    case COMMAND_SET_CHAR_COORDINATES_DONT_WARP_GANG_NO_OFFSET: // 0x9BC
        break;
    case COMMAND_SET_MINIGAME_IN_PROGRESS: // 0x9BD
        break;
    case COMMAND_IS_MINIGAME_IN_PROGRESS: // 0x9BE
        break;
    case COMMAND_SET_FORCE_RANDOM_CAR_MODEL: // 0x9BF
        break;
    case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_ANGLED_AREA_NO_SAVE: // 0x9C0
        break;
    case COMMAND_ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS: // 0x9C1
        break;
    case COMMAND_FAIL_KILL_FRENZY: // 0x9C2
        break;
    case COMMAND_IS_COP_VEHICLE_IN_AREA_3D_NO_SAVE: // 0x9C3
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x47A760
int8 CRunningScript::ProcessCommands2500To2599(int32 commandId) {
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
        break;
    case COMMAND_DOES_DECISION_MAKER_EXIST: // 0x9F2
        break;
    case COMMAND_GET_RANDOM_TRAIN_IN_SPHERE_NO_SAVE: // 0x9F3
        break;
    case COMMAND_IGNORE_HEIGHT_DIFFERENCE_FOLLOWING_NODES: // 0x9F4
        break;
    case COMMAND_SHUT_ALL_CHARS_UP: // 0x9F5
        break;
    case COMMAND_SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR: // 0x9F6
        break;
    case COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_CAR: // 0x9F7
        break;
    case COMMAND_DO_WEAPON_STUFF_AT_START_OF_2P_GAME: // 0x9F8
        break;
    case COMMAND_SET_MENU_HEADER_ORIENTATION: // 0x9F9
        break;
    case COMMAND_HAS_GAME_JUST_RETURNED_FROM_FRONTEND: // 0x9FA
        break;
    case COMMAND_GET_CURRENT_LANGUAGE: // 0x9FB
        break;
    case COMMAND_IS_OBJECT_INTERSECTING_WORLD: // 0x9FC
        break;
    case COMMAND_GET_STRING_WIDTH: // 0x9FD
        break;
    case COMMAND_RESET_VEHICLE_HYDRAULICS: // 0x9FE
        break;
    case COMMAND_SET_RESPAWN_POINT_FOR_DURATION_OF_MISSION: // 0x9FF
        break;
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
        break;
    case COMMAND_GET_STRING_WIDTH_WITH_NUMBER: // 0xA08
        break;
    case COMMAND_SHUT_CHAR_UP_FOR_SCRIPTED_SPEECH: // 0xA09
        break;
    case COMMAND_ENABLE_DISABLED_ATTRACTORS_ON_OBJECT: // 0xA0A
        break;
    case COMMAND_LOAD_SCENE_IN_DIRECTION: // 0xA0B
        break;
    case COMMAND_IS_PLAYER_USING_JETPACK: // 0xA0C
        break;
    case COMMAND_BLOCK_VEHICLE_MODEL: // 0xA0D
        break;
    case COMMAND_CLEAR_THIS_PRINT_BIG_NOW: // 0xA0E
        break;
    case COMMAND_HAS_LANGUAGE_CHANGED: // 0xA0F
        break;
    case COMMAND_INCREMENT_INT_STAT_NO_MESSAGE: // 0xA10
        break;
    case COMMAND_SET_EXTRA_CAR_COLOURS: // 0xA11
        break;
    case COMMAND_GET_EXTRA_CAR_COLOURS: // 0xA12
        break;
    case COMMAND_MANAGE_ALL_POPULATION: // 0xA13
        break;
    case COMMAND_SET_NO_RESPRAYS: // 0xA14
        break;
    case COMMAND_HAS_CAR_BEEN_RESPRAYED: // 0xA15
        break;
    case COMMAND_ATTACH_MISSION_AUDIO_TO_CAR: // 0xA16
        break;
    case COMMAND_SET_HAS_BEEN_OWNED_FOR_CAR_GENERATOR: // 0xA17
        break;
    case COMMAND_SET_UP_CONVERSATION_NODE_WITH_SCRIPTED_SPEECH: // 0xA18
        break;
    case COMMAND_SET_AREA_NAME: // 0xA19
        break;
    case COMMAND_TASK_PLAY_ANIM_SECONDARY: // 0xA1A
        break;
    case COMMAND_IS_CHAR_TOUCHING_CHAR: // 0xA1B
        break;
    case COMMAND_DISABLE_HELI_AUDIO: // 0xA1C
        break;
    case COMMAND_TASK_HAND_GESTURE: // 0xA1D
        break;
    case COMMAND_TAKE_PHOTO: // 0xA1E
        break;
    case COMMAND_INCREMENT_FLOAT_STAT_NO_MESSAGE: // 0xA1F
        break;
    case COMMAND_SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS: // 0xA20
        break;
    case COMMAND_IMPROVE_CAR_BY_CHEATING: // 0xA21
        break;
    case COMMAND_CHANGE_CAR_COLOUR_FROM_MENU: // 0xA22
        break;
    case COMMAND_HIGHLIGHT_MENU_ITEM: // 0xA23
        break;
    case COMMAND_SET_DISABLE_MILITARY_ZONES: // 0xA24
        break;
    case COMMAND_SET_CAMERA_POSITION_UNFIXED: // 0xA25
        break;
    case COMMAND_SET_RADIO_TO_PLAYERS_FAVOURITE_STATION: // 0xA26
        break;
    case COMMAND_SET_DEATH_WEAPONS_PERSIST: // 0xA27
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}

// 0x479DA0
int8 CRunningScript::ProcessCommands2600To2699(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_SWIM_SPEED: // 0xA28
        break;
    case COMMAND_IS_PLAYER_CLIMBING: // 0xA29
        break;
    case COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED: // 0xA2A
        break;
    case COMMAND_IS_WIDESCREEN_ON_IN_OPTIONS: // 0xA2B
        break;
    case COMMAND_DRAW_SUBTITLES_BEFORE_FADE: // 0xA2C
        break;
    case COMMAND_DRAW_ODDJOB_TITLE_BEFORE_FADE: // 0xA2D
        break;
    case COMMAND_TASK_FOLLOW_PATH_NODES_TO_COORD_WITH_RADIUS: // 0xA2E
        break;
    case COMMAND_SET_PHOTO_CAMERA_EFFECT: // 0xA2F
        break;
    case COMMAND_FIX_CAR: // 0xA30
        break;
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
    {
        /*
        CollectParameters(1);
        if (ScriptParams[0])
            CCheat::EnableLegitimateCheat(CHEAT_PROSTITUTES_PAY_YOU);
        else
            CCheat::IsActive(CHEAT_PROSTITUTES_PAY_YOU) = false;
        */
        break;
    }
    case COMMAND_GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE: // 0xA3E
        break;
    case COMMAND_SET_SCRIPT_COOP_GAME: // 0xA3F
        break;
    case COMMAND_CREATE_USER_3D_MARKER: // 0xA40
        break;
    case COMMAND_REMOVE_USER_3D_MARKER: // 0xA41
        break;
    case COMMAND_REMOVE_ALLUSER_3D_MARKERS: // 0xA42
        break;
    case COMMAND_GET_RID_OF_PLAYER_PROSTITUTE: // 0xA43
        break;
    case COMMAND_DISPLAY_NON_MINIGAME_HELP_MESSAGES: // 0xA44
        break;
    case COMMAND_SET_RAILTRACK_RESISTANCE_MULT: // 0xA45
        break;
    case COMMAND_SWITCH_OBJECT_BRAINS: // 0xA46
        break;
    case COMMAND_FINISH_SETTING_UP_CONVERSATION_NO_SUBTITLES: // 0xA47
        break;
    case COMMAND_ALLOW_PAUSE_IN_WIDESCREEN: // 0xA48
        break;
    case COMMAND_IS_XBOX_VERSION: // 0xA49
        break;
    case COMMAND_GET_PC_MOUSE_MOVEMENT: // 0xA4A
        break;
    case COMMAND_IS_PC_USING_JOYPAD: // 0xA4B
        break;
    case COMMAND_IS_MOUSE_USING_VERTICAL_INVERSION: // 0xA4C
        break;
    case COMMAND_IS_JAPANESE_VERSION: // 0xA4D
        break;
    case COMMAND_IS_XBOX_PLAYER2_PRESSING_START: // 0xA4E
        break;
    case COMMAND_FINISHED_WITH_XBOX_PLAYER2: // 0xA4F
        break;
    case COMMAND_DO_DEBUG_STUFF: // 0xA50
        break;
    default:
        break;
    }

    return COMMAND_NOT_IMPLEMENTED_YET;
}
