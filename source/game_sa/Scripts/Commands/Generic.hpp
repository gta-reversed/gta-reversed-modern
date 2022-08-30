#include "StdInc.h"
#include "TaskSimplePlayerOnFoot.h"
#include "eScriptCommands.h"
#include "RunningScript.h"
#include "OpcodeResult.h"
#include "RunningScript.h"
#include "Cheat.h"
#include "CarGenerator.h"
#include "TheCarGenerators.h"
#include "FireManager.h"
#include "CommandParser/Parser.hpp"

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_ALL_TAXIS_HAVE_NITRO>() {
    CollectParameters(1);
    if (ScriptParams[0].iParam) {
        CCheat::ApplyCheat(CHEAT_ALL_TAXIS_NITRO);
    }
    else {
        CCheat::Disable(CHEAT_ALL_TAXIS_NITRO);
    }
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_THAN_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_THAN_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CONSTANT_GREATER_THAN_INT_VAR>() {
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CONSTANT_GREATER_THAN_INT_LVAR>() {
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_VAR>() {
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_LVAR>() {
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_SHORT_RANGE_SPRITE_BLIP_FOR_COORD>() {
    CollectParameters(4);
    CVector pos = CTheScripts::ReadCVectorFromScript(0);
    if (pos.z <= MAP_Z_LOW_LIMIT) {
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
    }

    int32 index = CollectNextParameterWithoutIncreasingPC(); // pointless
    CRadar::GetActualBlipArrayIndex(index);                  // pointless

    int32 blip = CRadar::SetShortRangeCoordBlip(BLIP_COORD, pos, 5, BLIP_DISPLAY_BOTH, m_szName);
    CRadar::SetBlipSprite(blip, ScriptParams[3].iParam);
    ScriptParams[0].iParam = blip;
    StoreParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME>() {
    char str[8];
    ReadTextLabelFromScript(str, 8);

    for (int i = 0; i < 8; i++)
        str[i] = tolower(str[i]);

    CRunningScript* script = CTheScripts::pActiveScripts;
    while (script) {
        CRunningScript* next = script->m_pNext;
        if (!strcmp(script->m_szName, str)) {
            script->RemoveScriptFromList(&CTheScripts::pActiveScripts);
            script->AddScriptToList(&CTheScripts::pIdleScripts);
            script->ShutdownThisScript();
        }
        script = next;
    }
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_INT_TO_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->iParam = ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_INT_TO_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->iParam = ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_LOAD_AND_LAUNCH_MISSION_INTERNAL>() {
    CollectParameters(1);
    int32 missionId = ScriptParams[0].iParam;

    // Mostly CP from StartMission @ MissionDebugModule
    if (CTheScripts::NumberOfExclusiveMissionScripts > 0) {
        if (missionId <= 65532)
            return OR_CONTINUE;
        missionId = 0xFFFF - missionId;
    }
    CTimer::Suspend();
    int32 offsetToMission = CTheScripts::MultiScriptArray[missionId];
    CFileMgr::ChangeDir("\\");
    if (CGame::bMissionPackGame) {
        size_t bytesRead = 0;
        while (FrontEndMenuManager.CheckMissionPackValidMenu()) {
            CFileMgr::SetDirMyDocuments();
            sprintf(gString, "MPACK//MPACK%d//SCR.SCM", CGame::bMissionPackGame);
            auto* file = CFileMgr::OpenFile(gString, "rb");
            if (file) {
                CFileMgr::Seek(file, offsetToMission, 0);
                bytesRead = CFileMgr::Read(file, &CTheScripts::MissionBlock[0], MISSION_SCRIPT_SIZE);
                CFileMgr::CloseFile(file);
                if (bytesRead >= 1) {
                    CTheScripts::WipeLocalVariableMemoryForMissionScript();
                    CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::MissionBlock[0]);
                    script->m_bUseMissionCleanup = true;
                    script->m_bIsMission = true;
                    script->m_pBaseIP = &CTheScripts::MissionBlock[0];
                    CTheScripts::bAlreadyRunningAMissionScript = true;
                    CGameLogic::ClearSkip(false);
                }
            }
            if (bytesRead >= 1) {
                break;
            }
        }
    }
    CFileMgr::SetDir("");
    if (!CGame::bMissionPackGame) {
        auto* file = CFileMgr::OpenFile("data\\script\\main.scm", "rb");
        CFileMgr::Seek(file, offsetToMission, 0);
        CFileMgr::Read(file, &CTheScripts::MissionBlock[0], MISSION_SCRIPT_SIZE);
        CFileMgr::CloseFile(file);

        CTheScripts::WipeLocalVariableMemoryForMissionScript();
        CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::MissionBlock[0]);
        script->m_bUseMissionCleanup = true;
        script->m_bIsMission = true;
        script->m_pBaseIP = &CTheScripts::MissionBlock[0];
        CTheScripts::bAlreadyRunningAMissionScript = true;
        CGameLogic::ClearSkip(false);
    }
    CTimer::Resume();
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SCRIPT_NAME>() {
    char str[8];
    ReadTextLabelFromScript(str, 8);

    for (int i = 0; i < 8; i++)
        str[i] = tolower(str[i]);

    strncpy(m_szName, str, 8);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_INT_VAR_FROM_INT_LVAR>() {
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam -= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_LVAR>() { // 0x065
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam -= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_INT_LVAR_FROM_INT_VAR>() { // 0x066
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam -= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_VAR>() { // 0x067
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam -= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_VAR_BY_INT_VAR>() { // 0x068
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam *= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_VAR_BY_FLOAT_VAR>() { // 0x069
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam *= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_LVAR_BY_INT_LVAR>() { // 0x06A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam *= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_LVAR>() { // 0x06B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam *= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_VAR_BY_INT_LVAR>() { // 0x06C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam *= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_VAR_BY_FLOAT_LVAR>() { // 0x06D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam *= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_LVAR_BY_INT_VAR>() { // 0x06E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam *= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_VAR>() { // 0x06F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam *= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_VAR_BY_INT_VAR>() { // 0x070
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam /= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_VAR_BY_FLOAT_VAR>() { // 0x071
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam /= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_LVAR_BY_INT_LVAR>() { // 0x072
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam /= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_LVAR>() { // 0x073
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam /= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_VAR_BY_INT_LVAR>() { // 0x074
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam /= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_VAR_BY_FLOAT_LVAR>() { // 0x075
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam /= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_LVAR_BY_INT_VAR>() { // 0x076
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam /= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_VAR>() { // 0x077
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam /= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_VAL_TO_FLOAT_VAR>() { // 0x078
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->fParam += CTimer::GetTimeStep() * ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_VAL_TO_FLOAT_LVAR>() { // 0x079
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->fParam += CTimer::GetTimeStep() * ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_VAR>() { // 0x07A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam += CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_LVAR>() { // 0x07B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam += CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_LVAR>() { // 0x07C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam += CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_VAR>() { // 0x07D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam += CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_VAL_FROM_FLOAT_VAR>() { // 0x07E
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->fParam -= CTimer::GetTimeStep() * ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_VAL_FROM_FLOAT_LVAR>() { // 0x07F
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->fParam -= CTimer::GetTimeStep() * ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_VAR>() { // 0x080
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_LVAR>() { // 0x081
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_LVAR>() { // 0x082
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_VAR>() { // 0x083
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_INT_TO_VAR_INT>() { // 0x084
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_INT_TO_LVAR_INT>() { // 0x085
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_FLOAT_TO_VAR_FLOAT>() { // 0x086
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_FLOAT_TO_LVAR_FLOAT>() { // 0x087
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_FLOAT_TO_LVAR_FLOAT>() { // 0x088
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_FLOAT_TO_VAR_FLOAT>() { // 0x089
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_INT_TO_LVAR_INT>() { // 0x08A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_INT_TO_VAR_INT>() { // 0x08B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_VAR_INT_TO_VAR_FLOAT>() { // 0x08C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam = static_cast<int32>(var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_VAR_FLOAT_TO_VAR_INT>() { // 0x08D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam = static_cast<float>(var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_LVAR_INT_TO_VAR_FLOAT>() { // 0x08E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam = static_cast<int32>(var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_LVAR_FLOAT_TO_VAR_INT>() { // 0x08F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam = static_cast<float>(var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_VAR_INT_TO_LVAR_FLOAT>() { // 0x090
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam = static_cast<int32>(var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_VAR_FLOAT_TO_LVAR_INT>() { // 0x091
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam = static_cast<float>(var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_LVAR_INT_TO_LVAR_FLOAT>() { // 0x092
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam = static_cast<int32>(var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_LVAR_FLOAT_TO_LVAR_INT>() { // 0x093
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam = static_cast<float>(var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ABS_VAR_INT>() { // 0x094
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    var->iParam = std::abs(var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ABS_LVAR_INT>() { // 0x095
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    var->iParam = std::abs(var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ABS_VAR_FLOAT>() { // 0x096
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    var->fParam = std::abs(var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ABS_LVAR_FLOAT>() { // 0x097
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    var->fParam = std::abs(var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GENERATE_RANDOM_FLOAT>() { // 0x098 todo: Check "Bling-bling Scramble" case
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CGeneral::GetRandomNumber(); // For
    CGeneral::GetRandomNumber(); // Better
    CGeneral::GetRandomNumber(); // Randomness
    var->fParam = CGeneral::GetRandomNumber() / (32768.0f * 2); // 100% NOT GetRandomNumberInRange(0, 0.5f) [0.000106812, 32768]
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GENERATE_RANDOM_INT>() { // 0x099
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    var->iParam = CGeneral::GetRandomNumber();
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_CAR_DRIVING_STYLE>() { // 0x0AE
    CollectParameters(2);
    auto* vehicle = GetVehiclePool()->GetAtRef(ScriptParams[0].iParam);
    assert(vehicle);
    vehicle->m_autoPilot.m_nCarDrivingStyle = static_cast<eCarDrivingStyle>(ScriptParams[1].u8Param);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_BIG>() { // 0x0BA
    char label[8];
    ReadTextLabelFromScript(label, 8);
    char* text = TheText.Get(label);
    CollectParameters(2);
    CMessages::AddBigMessage(text, ScriptParams[0].iParam, (eMessageStyle)(ScriptParams[1].iParam - 1));
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT>() { // 0x0BB
    char label[8];
    ReadTextLabelFromScript(label, 8);
    char* text = TheText.Get(label);
    CollectParameters(2);
    if (!text || text[0] != '~' || text[1] != 'z' || text[2] != '~' || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessage(text, ScriptParams[0].iParam, ScriptParams[1].iParam, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_NOW>() { // 0x0BC
    char label[8];
    ReadTextLabelFromScript(label, 8);
    char* text = TheText.Get(label);
    CollectParameters(2);
    if (!text || text[0] != '~' || text[1] != 'z' || text[2] != '~' || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessageJumpQ(text, ScriptParams[0].iParam, ScriptParams[1].iParam, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CLEAR_PRINTS>() { // 0x0BE
    CMessages::ClearMessages(false);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_TIME_OF_DAY>() { // 0x0BF
    ScriptParams[0].iParam = CClock::ms_nGameClockHours;
    ScriptParams[1].iParam = CClock::ms_nGameClockMinutes;
    StoreParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_TIME_OF_DAY>() { // 0x0C0
    CollectParameters(2);
    CClock::SetGameClock(ScriptParams[0].iParam, ScriptParams[1].iParam, 0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_MINUTES_TO_TIME_OF_DAY>() { // 0x0C1
    CollectParameters(2);
    ScriptParams[0].iParam = CClock::GetGameClockMinutesUntil(ScriptParams[0].iParam, ScriptParams[1].iParam);
    StoreParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_POINT_ON_SCREEN>() { // 0x0C2
    CollectParameters(4);
    CVector pos = CTheScripts::ReadCVectorFromScript(0);
    if (pos.z <= MAP_Z_LOW_LIMIT)
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

    UpdateCompareFlag(TheCamera.IsSphereVisible(&pos, ScriptParams[3].fParam));
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DEBUG_ON>() { // 0x0C3
#ifndef FINAL
    CTheScripts::DbgFlag = true;
#endif
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DEBUG_OFF>() { // 0x0C4
#ifndef FINAL
    CTheScripts::DbgFlag = false;
#endif
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_RETURN_TRUE>() { // 0x0C5
    UpdateCompareFlag(true);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_RETURN_FALSE>() { // 0x0C6
    UpdateCompareFlag(false);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_0>() { // 0x0B2 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_1>() { // 0x0B3 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_2>() { // 0x0B4 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_3>() { // 0x0B5 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_4>() { // 0x0B6 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_5>() { // 0x0B7 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_6>() { // 0x0B8 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_7>() { // 0x0B9 | NOTSA
    NOTSA_UNREACHABLE();
}


template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WAIT>() { // 0x001 
    CollectParameters(1);
    m_nWakeTime = ScriptParams[0].uParam + CTimer::GetTimeInMS();
    return OR_WAIT;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GOTO>() { // 0x002 
    CollectParameters(1);
    UpdatePC(ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SHAKE_CAM>() { // 0x003 
    CollectParameters(1);
    CamShakeNoPos(&TheCamera, ScriptParams[0].fParam / 1000.0f);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_INT>() { // 0x004
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    *var = ScriptParams[0];
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_FLOAT>() { // 0x005
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    *var = ScriptParams[0];
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_INT>() { // 0x006
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    *var = ScriptParams[0];
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_FLOAT>() { // 0x007
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    *var = ScriptParams[0];
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_VAL_TO_INT_VAR>() { // 0x008
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->iParam += ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_VAL_TO_FLOAT_VAR>() { // 0x009
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->fParam += ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_VAL_TO_INT_LVAR>() { // 0x00A
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->iParam += ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_VAL_TO_FLOAT_LVAR>() { // 0x00B
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->fParam += ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_VAL_FROM_INT_VAR>() { // 0x00C
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->iParam -= ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_VAL_FROM_FLOAT_VAR>() { // 0x00D
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->fParam -= ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_VAL_FROM_INT_LVAR>() { // 0x00E
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->iParam -= ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_VAL_FROM_FLOAT_LVAR>() { // 0x00F
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->fParam -= ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_VAR_BY_VAL>() { // 0x010
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->iParam *= ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_VAR_BY_VAL>() { // 0x011
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->fParam *= ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_LVAR_BY_VAL>() { // 0x012
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->iParam *= ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_LVAR_BY_VAL>() { // 0x013
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->fParam *= ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_VAR_BY_VAL>() { // 0x014
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->iParam /= ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_VAR_BY_VAL>() { // 0x015
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->fParam /= ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_LVAR_BY_VAL>() { // 0x016
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->iParam /= ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_LVAR_BY_VAL>() { // 0x017
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->fParam /= ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER>() { // 0x018
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_THAN_NUMBER>() { // 0x019
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_THAN_INT_VAR>() { // 0x01A
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_THAN_INT_LVAR>() { // 0x01B
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_THAN_INT_VAR>() { // 0x01C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam > var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_THAN_INT_LVAR>() { // 0x01D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam > var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_THAN_INT_LVAR>() { // 0x01E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam > var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_THAN_INT_VAR>() { // 0x01F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam > var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_THAN_NUMBER>() { // 0x020
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam > ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_THAN_NUMBER>() { // 0x021
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam > ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_VAR>() { // 0x022
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].fParam > var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_LVAR>() { // 0x023
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].fParam > var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_VAR>() { // 0x024
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam > var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_LVAR>() { // 0x025
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam > var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_LVAR>() { // 0x026
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam > var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_VAR>() { // 0x027
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam > var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_NUMBER>() { // 0x028
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_NUMBER>() { // 0x029
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_VAR>() { // 0x02A
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_LVAR>() { // 0x02B
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_VAR>() { // 0x02C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam >= var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_LVAR>() { // 0x02D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam >= var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_LVAR>() { // 0x02E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam >= var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_VAR>() { // 0x02F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam >= var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_NUMBER>() { // 0x030
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam >= ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_NUMBER>() { // 0x031
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam >= ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_VAR>() { // 0x032
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].fParam >= var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_LVAR>() { // 0x033
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].fParam >= var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_VAR>() { // 0x034
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam >= var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR>() { // 0x035
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam >= var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR>() { // 0x036
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam >= var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_VAR>() { // 0x037
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam >= var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_EQUAL_TO_NUMBER>() { // 0x038
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam == ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_EQUAL_TO_NUMBER>() { // 0x039
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam == ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_EQUAL_TO_INT_VAR>() { // 0x03A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam == var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_EQUAL_TO_INT_LVAR>() { // 0x03B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam == var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_EQUAL_TO_INT_LVAR>() { // 0x03C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam == var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_EQUAL_TO_NUMBER>() { // 0x042
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam == ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_EQUAL_TO_NUMBER>() { // 0x043
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam == ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_VAR>() { // 0x044
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam == var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_EQUAL_TO_FLOAT_LVAR>() { // 0x045
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam == var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_LVAR>() { // 0x046
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam == var2->fParam);
    return OR_CONTINUE;
}

void GoToIfFalse(CRunningScript& S, int32 label) { // COMMAND_GOTO_IF_FALSE
    if (S.m_bCondResult) {
        S.UpdatePC(label);
    }
}
REGISTER_PARSED_COMMAND(COMMAND_GOTO_IF_FALSE, GoToIfFalse)

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_TERMINATE_THIS_SCRIPT>() { // 0x04E 
    if (m_bIsMission)
        CTheScripts::bAlreadyRunningAMissionScript = false;
    RemoveScriptFromList(&CTheScripts::pActiveScripts);
    AddScriptToList(&CTheScripts::pIdleScripts);
    ShutdownThisScript();
    return OR_WAIT;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_START_NEW_SCRIPT>() { // 0x04F
    CollectParameters(1);

    int32 offset = ScriptParams[0].iParam;
    if (offset < 0) // This doesn't make sense
        offset = COMMAND_START_NEW_SCRIPT; // For Mobile, offset is set to 0 here. WD fix perhaps?

    CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[offset]);
    ReadParametersForNewlyStartedScript(script);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GOSUB>() { // 0x050 
    CollectParameters(1);
    m_apStack[m_nSP++] = m_pCurrentIP;
    UpdatePC(ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_RETURN>() { // 0x051
    m_pCurrentIP = m_apStack[--m_nSP];
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_LINE>() { // 0x052
    CollectParameters(6);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CREATE_PLAYER>() { // 0x053
    CollectParameters(4);
    int32 index = ScriptParams[0].iParam;
    if (!CStreaming::IsModelLoaded(0 /*MI_PLAYER*/)) // todo (Izzotop): rename MODEL_NULL -> MI_PLAYER
    {
        CStreaming::RequestSpecialModel(0, "player", STREAMING_GAME_REQUIRED | STREAMING_KEEP_IN_MEMORY | STREAMING_PRIORITY_REQUEST);
        CStreaming::LoadAllRequestedModels(true);
    }

    CPlayerPed::SetupPlayerPed(index);
    CPlayerInfo* playerInfo = &CWorld::Players[index];
    CPlayerPed* player = playerInfo->m_pPed;
    player->SetCharCreatedBy(PED_MISSION);
    CPlayerPed::DeactivatePlayerPed(index);

    CVector pos = CTheScripts::ReadCVectorFromScript(1);
    if (pos.z <= MAP_Z_LOW_LIMIT)
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

    pos.z += player->GetDistanceFromCentreOfMassToBaseOfModel();
    player->SetPosn(pos);
    CTheScripts::ClearSpaceForMissionEntity(pos, player);
    CPlayerPed::ReactivatePlayerPed(index);
    ScriptParams[0].iParam = index;
    StoreParameters(1);

    CTask* task = new CTaskSimplePlayerOnFoot();
    player->GetTaskManager().SetTask(task, TASK_PRIMARY_DEFAULT);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_PLAYER_COORDINATES>() { // 0x054 | NOTSA
    CollectParameters(1);
    auto& playerInfo = FindPlayerInfo(ScriptParams[0].iParam);
    *(CVector*)&ScriptParams[0] = playerInfo.GetPos();
    StoreParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_PLAYER_IN_AREA_2D>() { // 0x056 | NOTSA
    CollectParameters(6);
    CPlayerPed* player = FindPlayerPed(ScriptParams[0].iParam);
    float x1 = ScriptParams[1].fParam;
    float y1 = ScriptParams[2].fParam;
    float x2 = ScriptParams[3].fParam;
    float y2 = ScriptParams[4].fParam;

    if (player->bInVehicle)
        UpdateCompareFlag(player->m_pVehicle->IsWithinArea(x1, y1, x2, y2));
    else
        UpdateCompareFlag(player->IsWithinArea(x1, y1, x2, y2));

    if (ScriptParams[5].bParam)
        CTheScripts::HighlightImportantArea(reinterpret_cast<uint32>((uint32)this + m_pCurrentIP), x1, y1, x2, y2, MAP_Z_LOW_LIMIT);

    if (CTheScripts::DbgFlag)
        CTheScripts::DrawDebugSquare(x1, y1, x2, y2);

    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_PLAYER_IN_AREA_3D>() { // 0x057 | NOTSA
    CollectParameters(8);
    CPlayerPed* player = FindPlayerPed(ScriptParams[0].iParam);
    const CVector p1 = CTheScripts::ReadCVectorFromScript(1);
    const CVector p2 = CTheScripts::ReadCVectorFromScript(4);

    if (player->bInVehicle)
        UpdateCompareFlag(player->m_pVehicle->IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z));
    else
        UpdateCompareFlag(player->IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z));

    if (ScriptParams[7].bParam)
        CTheScripts::HighlightImportantArea(reinterpret_cast<uint32>((uint32)this + m_pCurrentIP), p1.x, p1.y, p2.x, p2.y, (p1.z + p2.z) / 2.0f);

    if (CTheScripts::DbgFlag)
        CTheScripts::DrawDebugCube(p1, p2);

    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_INT_VAR_TO_INT_VAR>() { // 0x058
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam += var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_FLOAT_VAR_TO_FLOAT_VAR>() { // 0x059
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam += var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_INT_LVAR_TO_INT_LVAR>() { // 0x05A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam += var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_LVAR>() { // 0x05B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam += var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_INT_VAR_TO_INT_LVAR>() { // 0x05C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam += var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_FLOAT_VAR_TO_FLOAT_LVAR>() { // 0x05D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam += var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_INT_LVAR_TO_INT_VAR>() { // 0x05E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam += var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_VAR>() { // 0x05F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam += var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_INT_VAR_FROM_INT_VAR>() { // 0x060
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam -= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_VAR>() { // 0x061
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam -= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_INT_LVAR_FROM_INT_LVAR>() { // 0x062
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam -= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_LVAR>() { // 0x063
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam -= var2->fParam;
    return OR_CONTINUE;
}


template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_BUTTON_PRESSED>() { // 0x00E1 (Pad touch, TouchPoints touchPoints)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_MEMORY>() { // 0x0A8C (int32 address, int32 size, any value, bool vp)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_READ_MEMORY>() { // 0x0A8D (int32 address, int32 size, bool vp)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_INT_ADD>() { // 0x0A8E (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_INT_SUB>() { // 0x0A8F (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_INT_MUL>() { // 0x0A90 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_INT_DIV>() { // 0x0A91 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_STREAM_CUSTOM_SCRIPT>() { // 0x0A92 (string scriptFileName, arguments)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_TERMINATE_THIS_CUSTOM_SCRIPT>() { // 0x0A93
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_LOAD_AND_LAUNCH_CUSTOM_MISSION>() { // 0x0A94 (string scriptFileName, arguments)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SAVE_THIS_CUSTOM_SCRIPT>() { // 0x0A95
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_PED_POINTER>() { // 0x0A96 (Char char)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_VEHICLE_POINTER>() { // 0x0A97 (Car vehicle)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_OBJECT_POINTER>() { // 0x0A98 (Object object)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_CURRENT_DIRECTORY>() { // 0x0A99 (any path)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_OPEN_FILE>() { // 0x0A9A (string filePathName, FileMode mode)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CLOSE_FILE>() { // 0x0A9B (File self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_FILE_SIZE>() { // 0x0A9C (File self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_READ_FROM_FILE>() { // 0x0A9D (File self, int32 size)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_TO_FILE>() { // 0x0A9E (File self, int32 size, int32 source)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_THIS_SCRIPT_STRUCT>() { // 0x0A9F
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GOSUB_IF_FALSE>() { // 0x0AA0 (label)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_RETURN_IF_FALSE>() { // 0x0AA1
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_LOAD_DYNAMIC_LIBRARY>() { // 0x0AA2 (string libraryFileName)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_FREE_DYNAMIC_LIBRARY>() { // 0x0AA3 (DynamicLibrary self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_DYNAMIC_LIBRARY_PROCEDURE>() { // 0x0AA4 (string procName, DynamicLibrary self)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_FUNCTION>() { // 0x0AA5 (int32 address, int32 numParams, int32 pop, arguments funcParams)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_METHOD>() { // 0x0AA6 (int32 address, int32 struct, int32 numParams, int32 pop, arguments funcParams)
    CollectParameters(5);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_FUNCTION_RETURN>() { // 0x0AA7 (int32 address, int32 numParams, int32 pop, arguments funcParams)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_METHOD_RETURN>() { // 0x0AA8 (int32 address, int32 struct, int32 numParams, int32 pop, arguments funcParams)
    CollectParameters(5);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_GAME_VERSION_ORIGINAL>() { // 0x0AA9
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_SCRIPT_STRUCT_NAMED>() { // 0x0AAA (string scriptName)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DOES_FILE_EXIST>() { // 0x0AAB (string path)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_LOAD_AUDIO_STREAM>() { // 0x0AAC (string audioFileName)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_AUDIO_STREAM_STATE>() { // 0x0AAD (AudioStream self, AudioStreamState state)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_REMOVE_AUDIO_STREAM>() { // 0x0AAE (AudioStream self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_AUDIO_STREAM_LENGTH>() { // 0x0AAF (AudioStream self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_KEY_PRESSED>() { // 0x0AB0 (KeyCode keyCode)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CLEO_CALL>() { // 0x0AB1 (label , int32 numParams, arguments params)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CLEO_RETURN>() { // 0x0AB2 (int32 numRet, arguments retParams)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_CLEO_SHARED_VAR>() { // 0x0AB3 (int32 varId, any value)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_CLEO_SHARED_VAR>() { // 0x0AB4 (int32 varId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_STORE_CLOSEST_ENTITIES>() { // 0x0AB5 (Char self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_TARGET_BLIP_COORDS>() { // 0x0AB6
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_CAR_NUMBER_OF_GEARS>() { // 0x0AB7 (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_CAR_CURRENT_GEAR>() { // 0x0AB8 (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_AUDIO_STREAM_STATE>() { // 0x0AB9 (AudioStream self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_TERMINATE_ALL_CUSTOM_SCRIPTS_WITH_THIS_NAME>() { // 0x0ABA (string scriptFileName)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_AUDIO_STREAM_VOLUME>() { // 0x0ABB (AudioStream self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_AUDIO_STREAM_VOLUME>() { // 0x0ABC (AudioStream self, float volume)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CAR_SIREN_ON>() { // 0x0ABD (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CAR_ENGINE_ON>() { // 0x0ABE (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CLEO_SET_CAR_ENGINE_ON>() { // 0x0ABF (Car self, bool state)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_AUDIO_STREAM_LOOPED>() { // 0x0AC0 (AudioStream self, bool state)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_LOAD_3D_AUDIO_STREAM>() { // 0x0AC1 (string audioFileName)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_PLAY_3D_AUDIO_STREAM_AT_COORDS>() { // 0x0AC2 (AudioStream self, float x, float y, float z)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_PLAY_3D_AUDIO_STREAM_AT_OBJECT>() { // 0x0AC3 (AudioStream self, Object handle)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_PLAY_3D_AUDIO_STREAM_AT_CHAR>() { // 0x0AC4 (AudioStream self, Char handle)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_PLAY_3D_AUDIO_STREAM_AT_CAR>() { // 0x0AC5 (AudioStream self, Car handle)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_LABEL_POINTER>() { // 0x0AC6 (label)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_VAR_POINTER>() { // 0x0AC7 (any)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ALLOCATE_MEMORY>() { // 0x0AC8 (int32 size)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_FREE_MEMORY>() { // 0x0AC9 (int32 address)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_HELP_STRING>() { // 0x0ACA (string text)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_BIG_STRING>() { // 0x0ACB (string text, int32 time, TextStyle style)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_STRING>() { // 0x0ACC (string text, int32 time)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_STRING_NOW>() { // 0x0ACD (string text, int32 time)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_HELP_FORMATTED>() { // 0x0ACE (string text, arguments args)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_BIG_FORMATTED>() { // 0x0ACF (string text, int32 time, TextStyle style, arguments args)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_FORMATTED>() { // 0x0AD0 (string text, int32 time, arguments arg)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_FORMATTED_NOW>() { // 0x0AD1 (string text, int32 time, arguments arg)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_CHAR_PLAYER_IS_TARGETING>() { // 0x0AD2 (Player self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_STRING_FORMAT>() { // 0x0AD3 (string format, arguments args)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SCAN_STRING>() { // 0x0AD4 (string str, string format, arguments args)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_FILE_SEEK>() { // 0x0AD5 (File self, int32 offset, SeekOrigin origin)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_END_OF_FILE_REACHED>() { // 0x0AD6 (File self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_READ_STRING_FROM_FILE>() { // 0x0AD7 (File self, string buffer, int32 size)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_STRING_TO_FILE>() { // 0x0AD8 (File self, string source)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_FORMATTED_STRING_TO_FILE>() { // 0x0AD9 (File self, string format, arguments args)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SCAN_FILE>() { // 0x0ADA (File self, string format, arguments args)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_NAME_OF_VEHICLE_MODEL>() { // 0x0ADB (model_vehicle modelId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_TEST_CHEAT>() { // 0x0ADC (string input)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPAWN_VEHICLE_BY_CHEATING>() { // 0x0ADD (model_vehicle modelId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_TEXT_LABEL_STRING>() { // 0x0ADE (gxt_key key)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TEXT_LABEL>() { // 0x0ADF (gxt_key dynamicKey, string text)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_REMOVE_TEXT_LABEL>() { // 0x0AE0 (gxt_key dynamicKey)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_RANDOM_CHAR_IN_SPHERE_NO_SAVE_RECURSIVE>() { // 0x0AE1 (float x, float y, float z, float radius, bool findNext, bool skipDead)
    CollectParameters(6);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_RANDOM_CAR_IN_SPHERE_NO_SAVE_RECURSIVE>() { // 0x0AE2 (float x, float y, float z, float radius, bool findNext, bool skipWrecked)
    CollectParameters(6);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_RANDOM_OBJECT_IN_SPHERE_NO_SAVE_RECURSIVE>() { // 0x0AE3 (float x, float y, float z, float radius, bool findNext)
    CollectParameters(5);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DOES_DIRECTORY_EXIST>() { // 0x0AE4 (string dirPath)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CREATE_DIRECTORY>() { // 0x0AE5 (string dirName)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_FIND_FIRST_FILE>() { // 0x0AE6 (string searchMask, string fileName)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_FIND_NEXT_FILE>() { // 0x0AE7 (FindFile self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_FIND_CLOSE>() { // 0x0AE8 (FindFile self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_POP_FLOAT>() { // 0x0AE9
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_PED_REF>() { // 0x0AEA (int32 address)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_VEHICLE_REF>() { // 0x0AEB (int32 address)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_OBJECT_REF>() { // 0x0AEC (int32 address)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_STRING_FLOAT_FORMAT>() { // 0x0AED (float number, string format)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_POW>() { // 0x0AEE (float number, float power)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_LOG>() { // 0x0AEF (float number, float base)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_READ_STRUCT_OFFSET>() { // 0x0D4E (int32 address, int32 offset, int32 size)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_CAR_ALARM>() { // 0x0E00 (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CREATE_OBJECT_NO_SAVE>() { // 0x0E01 (model_object modelId, float x, float y, float z, bool useOffset, bool useGround)
    CollectParameters(6);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_CAR_GENERATOR_NO_SAVE>() { // 0x0E02 (CarGenerator self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PERLIN_NOISE>() { // 0x0E03 (float x)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_NEXT_WEATHER>() { // 0x0E04
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_NEXT_WEATHER>() { // 0x0E05 (WeatherType type)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_RAIN_INTENSITY>() { // 0x0E06
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_RAIN_INTENSITY>() { // 0x0E07 (float intensity)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CAR_SCRIPT_CONTROLLED>() { // 0x0E08 (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MARK_CAR_AS_NEEDED>() { // 0x0E09 (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CHAR_SCRIPT_CONTROLLED>() { // 0x0E0A (Char self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MARK_CHAR_AS_NEEDED>() { // 0x0E0B (Char self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_OBJECT_SCRIPT_CONTROLLED>() { // 0x0E0C (Object self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MARK_OBJECT_AS_NEEDED>() { // 0x0E0D (Object self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_CURRENT_RESOLUTION>() { // 0x0E0E
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_FIXED_XY_ASPECT_RATIO>() { // 0x0E0F (float x, float y)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_MOUSE_WHEEL_UP>() { // 0x0E10
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_MOUSE_WHEEL_DOWN>() { // 0x0E11
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_VEHICLE_SUBCLASS>() { // 0x0E12 (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_ENTITY_TYPE>() { // 0x0E13 (int32 address)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_ON_MISSION>() { // 0x0E1D
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_ON_SAMP>() { // 0x0E20
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_AUDIO_SFX_VOLUME>() { // 0x0E21
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_AUDIO_RADIO_VOLUME>() { // 0x0E22
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_MOUSE_SENSIBILITY>() { // 0x0E23
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_FIX_CHAR_GROUND_BRIGHTNESS_AND_FADE_IN>() { // 0x0E24 (Char self, bool fixGround, bool fixBrightness, bool fadeIn)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_ON_CUTSCENE>() { // 0x0E25
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_WEAPON_FIRE_TYPE>() { // 0x0E26 (WeaponType weaponType, WeaponFire weaponFire)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_ANGLE_FROM_TWO_COORDS>() { // 0x0E27 (float x1, float y1, float x2, float y2)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_STRUCT_OFFSET>() { // 0x0E28 (int32 address, int32 offset, int32 size, any value)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PERLIN_NOISE_FRACTAL>() { // 0x0E29 (float x, int32 octaves, float frequency, float amplitude, float lacunarity, float persistence)
    CollectParameters(6);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_CAR_ALARM>() { // 0x0E61 (Car self, CarAlarm status)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PERLIN_NOISE_FRACTAL_2D>() { // 0x0EF1 (float x, float y, int32 octaves, float frequency, float amplitude, float lacunarity, float persistence)
    CollectParameters(7);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PERLIN_NOISE_FRACTAL_3D>() { // 0x0EF2 (float x, float y, float z, int32 octaves, float frequency, float amplitude, float lacunarity, float persistence)
    CollectParameters(8);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BIT_AND>() { // 0x0B10 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BIT_OR>() { // 0x0B11 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BIT_XOR>() { // 0x0B12 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BIT_NOT>() { // 0x0B13 (int32)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BIT_MOD>() { // 0x0B14 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BIT_SHR>() { // 0x0B15 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BIT_SHL>() { // 0x0B16 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BITWISE_AND_THING_WITH_THING>() { // 0x0B17 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BITWISE_OR_THING_WITH_THING>() { // 0x0B18 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BITWISE_XOR_THING_WITH_THING>() { // 0x0B19 (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BITWISE_NOT>() { // 0x0B1A (int32)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BITWISE_MOD_THING_BY_THING>() { // 0x0B1B (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BITWISE_SHR_THING_BY_THING>() { // 0x0B1C (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_BITWISE_SHL_THING_BY_THING>() { // 0x0B1D (int32, int32)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_READ_CLIPBOARD_DATA>() { // 0x0B20 (any memory, int32 size)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_CLIPBOARD_DATA>() { // 0x0B21 (any memory, int32 size)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DELETE_FILE>() { // 0x0B00 (string fileName)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DELETE_DIRECTORY>() { // 0x0B01 (string dirPath, bool recursive)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MOVE_FILE>() { // 0x0B02 (string fileName, string newFileName)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MOVE_DIRECTORY>() { // 0x0B03 (string dirPath, string newDirPath)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_COPY_FILE>() { // 0x0B04 (string fileName, string newFileName)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_COPY_DIRECTORY>() { // 0x0B05 (string dirPath, string newDirPath)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_BEGIN>() { // 0x0C00 (string windowName, bool state, bool noTitleBar, bool noResize, bool noMove, bool autoResize)
    CollectParameters(6);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_END>() { // 0x0C01
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_CHECKBOX>() { // 0x0C02 (string label, bool isChecked)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_BUTTON>() { // 0x0C03 (string buttonName, float width, float height)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_COLOR_BUTTON>() { // 0x0C04 (string buttonName, float red, float green, float blue, float alpha, float width, float height)
    CollectParameters(7);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_INVISIBLE_BUTTON>() { // 0x0C05 (string buttonName, float width, float height)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SET_WINDOW_POS>() { // 0x0C06 (float x, float y, ImGuiCond imGuiCond)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SET_WINDOW_SIZE>() { // 0x0C07 (float width, float height, ImGuiCond imGuiCond)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SET_NEXT_WINDOW_POS>() { // 0x0C08 (float x, float y, ImGuiCond imGuiCond)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SET_NEXT_WINDOW_SIZE>() { // 0x0C09 (float width, float height, ImGuiCond imGuiCond)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_DUMMY>() { // 0x0C0A (float width, float height)
    CollectParameters(2);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_TEXT>() { // 0x0C0B (string text)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_TEXT_DISABLED>() { // 0x0C0C (string text)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_TEXT_WRAPPED>() { // 0x0C0D (string text)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_TEXT_COLORED>() { // 0x0C0E (string text, float red, float green, float blue, float alpha)
    CollectParameters(5);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_BULLET_TEXT>() { // 0x0C0F (string text)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SET_TOOLTIP>() { // 0x0C10 (string text)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SAMELINE>() { // 0x0C11
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_NEWLINE>() { // 0x0C12
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SPACING>() { // 0x0C13
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SEPARATOR>() { // 0x0C14
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_NEXT_COLUMN>() { // 0x0C15
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_COLUMNS>() { // 0x0C16 (int32 count)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_GET_FRAMERATE>() { // 0x0C17
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_GET_VERSION>() { // 0x0C18
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_GET_PLUGIN_VERSION>() { // 0x0C19
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SET_CURSOR_VISIBLE>() { // 0x0C1A (bool show)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_GET_DISPLAY_SIZE>() { // 0x0C1B
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_GET_FRAME_HEIGHT>() { // 0x0C1C
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_GET_WINDOW_POS>() { // 0x0C1D
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_GET_WINDOW_SIZE>() { // 0x0C1E
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_CALC_TEXT_SIZE>() { // 0x0C1F (string text)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_GET_WINDOW_CONTENT_REGION_WIDTH>() { // 0x0C20
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_BEGIN_MAINMENUBAR>() { // 0x0C21 (string uniqueId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_END_MAINMENUBAR>() { // 0x0C22
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_MENU_ITEM>() { // 0x0C23 (string text, bool selected, bool enabled)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SELECTABLE>() { // 0x0C24 (string text)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_BEGIN_CHILD>() { // 0x0C25 (string uniqueId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_END_CHILD>() { // 0x0C26
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_PUSH_ITEM_WIDTH>() { // 0x0C27 (float width)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_POP_ITEM_WIDTH>() { // 0x0C28
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_COLLAPSING_HEADER>() { // 0x0C29 (string label)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SLIDER_INT>() { // 0x0C2A (string label, int32 initValue, int32 min, int32 max)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SLIDER_FLOAT>() { // 0x0C2B (string label, float initValue, float min, float max)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_INPUT_FLOAT>() { // 0x0C2C (string label, float initValue, float min, float max)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_INPUT_INT>() { // 0x0C2D (string label, int32 initValue, int32 min, int32 max)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_INPUT_TEXT>() { // 0x0C2E (string label)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_RADIO_BUTTON>() { // 0x0C2F (string label, int32 selectedBtn, int32 btnNo)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_COLOR_PICKER>() { // 0x0C30 (string label)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_BEGIN_FRAME>() { // 0x0C31 (string uniqueId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_END_FRAME>() { // 0x0C32
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_IS_ITEM_ACTIVE>() { // 0x0C33 (string uniqueId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_IS_ITEM_CLICKED>() { // 0x0C34 (string uniqueId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_IS_ITEM_FOCUSED>() { // 0x0C35 (string uniqueId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_IS_ITEM_HOVERED>() { // 0x0C36 (string uniqueId)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_GET_SCALING_SIZE>() { // 0x0C37 (string uniqueId, int32 count, bool spacing)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IMGUI_SET_NEXT_WINDOW_TRANSPARENCY>() { // 0x0C38 (float alpha)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_READ_INT_FROM_INI_FILE>() { // 0x0AF0 (string path, string section, string key)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_INT_TO_INI_FILE>() { // 0x0AF1 (int32 value, string path, string section, string key)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_READ_FLOAT_FROM_INI_FILE>() { // 0x0AF2 (string path, string section, string key)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_FLOAT_TO_INI_FILE>() { // 0x0AF3 (float value, string path, string section, string key)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_READ_STRING_FROM_INI_FILE>() { // 0x0AF4 (string path, string section, string key)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_STRING_TO_INI_FILE>() { // 0x0AF5 (string value, string path, string section, string key)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ACTIVATE_PIMP_CHEAT>() { // 0xA3D
    CollectParameters(1);
    if (ScriptParams[0].iParam)
        CCheat::ApplyCheat(CHEAT_PROSTITUTES_PAY_YOU);
    else
        CCheat::Disable(CHEAT_PROSTITUTES_PAY_YOU);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_SEQUENCE_TO_REPEAT>() { // 0x643
    CollectParameters(2);
    auto index = CTheScripts::GetActualScriptThingIndex(ScriptParams[0].iParam, SCRIPT_THING_SEQUENCE_TASK);
    if (index < 0 || index >= 64) {
        DEV_LOG("COMMAND_SET_SEQUENCE_TO_REPEAT: Index should be in [0, 64]");
        return OR_CONTINUE;
    }
    CTaskSequences::GetActiveSequence().m_bRepeatSequence = ScriptParams[1].bParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_START_SCRIPT_FIRE>() { // 0x2CF
    CollectParameters(5);
    CVector pos = CTheScripts::ReadCVectorFromScript(0);
    if (pos.z <= MAP_Z_LOW_LIMIT)
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

    ScriptParams[0].iParam = gFireManager.StartScriptFire(pos, nullptr, 0.8f, 1, ScriptParams[3].iParam, ScriptParams[4].iParam);
    StoreParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_CHAR_PROOFS>() { // 0x2AB
    CollectParameters(6);
    auto* ped = GetPedPool()->GetAt(ScriptParams[0].iParam >> 8);
    assert(ped);
    ped->physicalFlags.bBulletProof = ScriptParams[1].uParam;
    ped->physicalFlags.bFireProof = ScriptParams[2].uParam;
    ped->physicalFlags.bExplosionProof = ScriptParams[3].uParam;
    ped->physicalFlags.bCollisionProof = ScriptParams[4].uParam;
    ped->physicalFlags.bMeleeProof = ScriptParams[5].uParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_CAR_PROOFS>() { // 0x2AC
    CollectParameters(6);
    auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam >> 8);
    assert(vehicle);
    vehicle->physicalFlags.bBulletProof = ScriptParams[1].uParam;
    vehicle->physicalFlags.bFireProof = ScriptParams[2].uParam;
    vehicle->physicalFlags.bExplosionProof = ScriptParams[3].uParam;
    vehicle->physicalFlags.bCollisionProof = ScriptParams[4].uParam;
    vehicle->physicalFlags.bMeleeProof = ScriptParams[5].uParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_STORE_CLOCK>() { // 0x253
    CClock::StoreClock();
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_RESTORE_CLOCK>() { // 0x254
    CClock::RestoreClock();
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_PLAYER_PLAYING>() { // 0x256
    CollectParameters(1);
    UpdateCompareFlag(FindPlayerInfo(ScriptParams[0].iParam).m_nPlayerState == PLAYERSTATE_PLAYING);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SWITCH_CAR_GENERATOR>() { // 0x14C
    CollectParameters(2);
    CCarGenerator* generator = CTheCarGenerators::Get(ScriptParams[0].iParam);
    if (ScriptParams[1].iParam) {
        generator->SwitchOn();
        if (ScriptParams[1].iParam <= 100)
            generator->m_nGenerateCount = ScriptParams[1].iParam;
    }
    else {
        generator->SwitchOff();
    }
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ANDOR>() { // 0x0D6
    CollectParameters(1);
    m_nLogicalOp = ScriptParams[0].iParam;
    if (m_nLogicalOp == ANDOR_NONE)
    {
        m_bCondResult = false;
    }
    else if (m_nLogicalOp >= ANDS_1 && m_nLogicalOp <= ANDS_8)
    {
        m_nLogicalOp++;
        m_bCondResult = true;
    }
    else if (m_nLogicalOp >= ORS_1 && m_nLogicalOp <= ORS_8)
    {
        m_nLogicalOp++;
        m_bCondResult = false;
    }
    return OR_CONTINUE;
}

void LaunchMission(uint32 label) {
    CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[label]);
}
REGISTER_PARSED_COMMAND(COMMAND_LAUNCH_MISSION, LaunchMission)

void AttachCameraToVehicleLookAtVehicle(CVehicle& attachTo, CVector offset, CVehicle& lookAt, float tilt, eSwitchType switchType) {
    CVector zero{};
    TheCamera.TakeControlAttachToEntity(
        &lookAt,
        &attachTo,
        &offset,
        &zero,
        tilt,
        switchType,
        1
    );
}
REGISTER_PARSED_COMMAND(COMMAND_ATTACH_CAMERA_TO_VEHICLE_LOOK_AT_VEHICLE, AttachCameraToVehicleLookAtVehicle)

float GetCarSpeed(CVehicle& veh) {
    return veh.m_vecMoveSpeed.Magnitude() * 50.f;
}
REGISTER_PARSED_COMMAND(COMMAND_GET_CAR_SPEED, GetCarSpeed)

notsa::script::CompareFlagUpdate IsCharInArea2D(CRunningScript& S, CPed& ped, CVector2D a, CVector2D b, bool drawSphere) {
    const auto Check = [&](const auto& e) { return e.IsWithinArea(a.x, a.y, b.x, b.y); };

    if (drawSphere) {
        CTheScripts::HighlightImportantArea(reinterpret_cast<int32>(&S) + reinterpret_cast<int32>(S.m_pCurrentIP), a.x, a.y, b.x, b.y, -100.f);
    }

    return { ped.IsInVehicle() ? Check(*ped.m_pVehicle) : Check(ped) };
}
REGISTER_PARSED_COMMAND(COMMAND_IS_CHAR_IN_AREA_2D, IsCharInArea2D)
