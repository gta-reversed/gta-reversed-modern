#include "StdInc.h"

#include "RunningScript.h"
#include "TaskSimplePlayerOnFoot.h"
#include "PlayerInfo.h"

// 0x465E60
OpcodeResult CRunningScript::ProcessCommands0To99(int32 commandId) {
    switch (commandId) {
    case COMMAND_NOP: // 0x000
        return OR_CONTINUE;
    case COMMAND_WAIT: // 0x001
        CollectParameters(1);
        m_nWakeTime = ScriptParams[0].uParam + CTimer::GetTimeInMS();
        return OR_WAIT;
    case COMMAND_GOTO: // 0x002
        CollectParameters(1);
        UpdatePC(ScriptParams[0].iParam);
        return OR_CONTINUE;
    case COMMAND_SHAKE_CAM: // 0x003
        CollectParameters(1);
        CamShakeNoPos(&TheCamera, ScriptParams[0].fParam / 1000.0f);
        return OR_CONTINUE;
    case COMMAND_SET_VAR_INT: // 0x004
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        *var = ScriptParams[0];
        return OR_CONTINUE;
    }
    case COMMAND_SET_VAR_FLOAT: // 0x005
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        *var = ScriptParams[0];
        return OR_CONTINUE;
    }
    case COMMAND_SET_LVAR_INT: // 0x006
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        *var = ScriptParams[0];
        return OR_CONTINUE;
    }
    case COMMAND_SET_LVAR_FLOAT: // 0x007
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        *var = ScriptParams[0];
        return OR_CONTINUE;
    }
    case COMMAND_ADD_VAL_TO_INT_VAR: // 0x008
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->iParam += ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_VAL_TO_FLOAT_VAR: // 0x009
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->fParam += ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_VAL_TO_INT_LVAR: // 0x00A
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->iParam += ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_VAL_TO_FLOAT_LVAR: // 0x00B
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->fParam += ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_VAL_FROM_INT_VAR: // 0x00C
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->iParam -= ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_VAL_FROM_FLOAT_VAR: // 0x00D
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->fParam -= ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_VAL_FROM_INT_LVAR: // 0x00E
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->iParam -= ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_VAL_FROM_FLOAT_LVAR: // 0x00F
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->fParam -= ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_INT_VAR_BY_VAL: // 0x010
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->iParam *= ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_FLOAT_VAR_BY_VAL: // 0x011
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->fParam *= ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_INT_LVAR_BY_VAL: // 0x012
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->iParam *= ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_FLOAT_LVAR_BY_VAL: // 0x013
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->fParam *= ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_INT_VAR_BY_VAL: // 0x014
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->iParam /= ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_FLOAT_VAR_BY_VAL: // 0x015
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->fParam /= ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_INT_LVAR_BY_VAL: // 0x016
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->iParam /= ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_FLOAT_LVAR_BY_VAL: // 0x017
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->fParam /= ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER: // 0x018
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_GREATER_THAN_NUMBER: // 0x019
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_NUMBER_GREATER_THAN_INT_VAR: // 0x01A
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_NUMBER_GREATER_THAN_INT_LVAR: // 0x01B
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_GREATER_THAN_INT_VAR: // 0x01C
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->iParam > var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_GREATER_THAN_INT_LVAR: // 0x01D
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->iParam > var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_GREATER_THAN_INT_LVAR: // 0x01E
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->iParam > var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_GREATER_THAN_INT_VAR: // 0x01F
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->iParam > var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_VAR_GREATER_THAN_NUMBER: // 0x020
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        UpdateCompareFlag(var->fParam > ScriptParams[0].fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_LVAR_GREATER_THAN_NUMBER: // 0x021
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        UpdateCompareFlag(var->fParam > ScriptParams[0].fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_VAR: // 0x022
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(ScriptParams[0].fParam > var->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_LVAR: // 0x023
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(ScriptParams[0].fParam > var->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_VAR: // 0x024
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->fParam > var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_LVAR: // 0x025
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->fParam > var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_LVAR: // 0x026
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->fParam > var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_VAR: // 0x027
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->fParam > var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_NUMBER: // 0x028
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_NUMBER: // 0x029
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_VAR: // 0x02A
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_LVAR: // 0x02B
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_VAR: // 0x02C
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->iParam >= var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_LVAR: // 0x02D
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->iParam >= var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_LVAR: // 0x02E
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->iParam >= var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_VAR: // 0x02F
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->iParam >= var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_NUMBER: // 0x030
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        UpdateCompareFlag(var->fParam >= ScriptParams[0].fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_NUMBER: // 0x031
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        UpdateCompareFlag(var->fParam >= ScriptParams[0].fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_VAR: // 0x032
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(ScriptParams[0].fParam >= var->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_LVAR: // 0x033
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(ScriptParams[0].fParam >= var->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_VAR: // 0x034
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->fParam >= var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR: // 0x035
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->fParam >= var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR: // 0x036
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->fParam >= var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_VAR: // 0x037
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->fParam >= var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_EQUAL_TO_NUMBER: // 0x038
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam == ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_EQUAL_TO_NUMBER: // 0x039
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam == ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_EQUAL_TO_INT_VAR: // 0x03A
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->iParam == var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_EQUAL_TO_INT_LVAR: // 0x03B
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->iParam == var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_EQUAL_TO_INT_LVAR: // 0x03C
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->iParam == var2->iParam);
        return OR_CONTINUE;
    }

    // Not implemented:
    // case COMMAND_IS_INT_VAR_NOT_EQUAL_TO_NUMBER: // 0x03D
    // case COMMAND_IS_INT_LVAR_NOT_EQUAL_TO_NUMBER: // 0x03E
    // case COMMAND_IS_INT_VAR_NOT_EQUAL_TO_INT_VAR: // 0x03F
    // case COMMAND_IS_INT_LVAR_NOT_EQUAL_TO_INT_LVAR: // 0x040
    // case COMMAND_IS_INT_VAR_NOT_EQUAL_TO_INT_LVAR: // 0x041

    case COMMAND_IS_FLOAT_VAR_EQUAL_TO_NUMBER: // 0x042
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        UpdateCompareFlag(var->fParam == ScriptParams[0].fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_LVAR_EQUAL_TO_NUMBER: // 0x043
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        UpdateCompareFlag(var->fParam == ScriptParams[0].fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_VAR: // 0x044
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(var1->fParam == var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_LVAR_EQUAL_TO_FLOAT_LVAR: // 0x045
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->fParam == var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_LVAR: // 0x046
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(var1->fParam == var2->fParam);
        return OR_CONTINUE;
    }

    // Not implemented:
    // case COMMAND_IS_FLOAT_VAR_NOT_EQUAL_TO_NUMBER: // 0x047
    // case COMMAND_IS_FLOAT_LVAR_NOT_EQUAL_TO_NUMBER: // 0x048
    // case COMMAND_IS_FLOAT_VAR_NOT_EQUAL_TO_FLOAT_VAR: // 0x049
    // case COMMAND_IS_FLOAT_LVAR_NOT_EQUAL_TO_FLOAT_LVAR: // 0x04A
    // case COMMAND_IS_FLOAT_VAR_NOT_EQUAL_TO_FLOAT_LVAR: // 0x04B
    // case COMMAND_GOTO_IF_TRUE: // 0x04C

    case COMMAND_GOTO_IF_FALSE: // 0x04D
        CollectParameters(1);
        if (m_bCondResult)
            return OR_CONTINUE;
        UpdatePC(ScriptParams[0].iParam);
        return OR_CONTINUE;
    case COMMAND_TERMINATE_THIS_SCRIPT: // 0x04E
        if (m_bIsMission)
            CTheScripts::bAlreadyRunningAMissionScript = false;
        RemoveScriptFromList(&CTheScripts::pActiveScripts);
        AddScriptToList(&CTheScripts::pIdleScripts);
        ShutdownThisScript();
        return OR_WAIT;
    case COMMAND_START_NEW_SCRIPT: // 0x04F
    {
        CollectParameters(1);

        int32 offset = ScriptParams[0].iParam;
        if (offset < 0) // This doesn't make sense
            offset = commandId; // For Mobile, offset is set to 0 here. WD fix perhaps?

        CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[offset]);
        ReadParametersForNewlyStartedScript(script);
        return OR_CONTINUE;
    }
    case COMMAND_GOSUB: // 0x050
        CollectParameters(1);
        m_apStack[m_nSP++] = m_pCurrentIP;
        UpdatePC(ScriptParams[0].iParam);
        return OR_CONTINUE;
    case COMMAND_RETURN: // 0x051
        m_pCurrentIP = m_apStack[--m_nSP];
        return OR_CONTINUE;
    case COMMAND_LINE: // 0x052
        CollectParameters(6);
        return OR_CONTINUE;
    case COMMAND_CREATE_PLAYER: // 0x053
    {
        CollectParameters(4);
        int32 index = ScriptParams[0].iParam;
        if (!CStreaming::IsModelLoaded(0 /*MI_PLAYER*/)) // todo (Izzotop): rename MODEL_NULL -> MI_PLAYER
        {
            CStreaming::RequestSpecialModel(0, "player", STREAMING_GAME_REQUIRED | STREAMING_KEEP_IN_MEMORY | STREAMING_PRIORITY_REQUEST);
            CStreaming::LoadAllRequestedModels(true);
        }

        CPlayerPed::SetupPlayerPed(index);
        CPlayerInfo* playerInfo = &CWorld::Players[index];
        CPlayerPed*  player      = playerInfo->m_pPed;
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

    case COMMAND_GET_PLAYER_COORDINATES: // 0x054 | NOTSA
    {
        CollectParameters(1);
        auto& playerInfo = FindPlayerInfo(ScriptParams[0].iParam);
        *(CVector*)&ScriptParams[0] = playerInfo.GetPos();
        StoreParameters(3);
        return OR_CONTINUE;
    }
    // case COMMAND_SET_PLAYER_COORDINATES: // 0x055
    case COMMAND_IS_PLAYER_IN_AREA_2D: // 0x056 | NOTSA
    {
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
    case COMMAND_IS_PLAYER_IN_AREA_3D: // 0x057 | NOTSA
    {
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
    case COMMAND_ADD_INT_VAR_TO_INT_VAR: // 0x058
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam += var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_FLOAT_VAR_TO_FLOAT_VAR: // 0x059
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam += var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_INT_LVAR_TO_INT_LVAR: // 0x05A
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam += var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_LVAR: // 0x05B
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam += var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_INT_VAR_TO_INT_LVAR: // 0x05C
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam += var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_FLOAT_VAR_TO_FLOAT_LVAR: // 0x05D
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam += var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_INT_LVAR_TO_INT_VAR: // 0x05E
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam += var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_VAR: // 0x05F
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam += var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_INT_VAR_FROM_INT_VAR: // 0x060
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam -= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_VAR: // 0x061
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam -= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_INT_LVAR_FROM_INT_LVAR: // 0x062
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam -= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_LVAR: // 0x063
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam -= var2->fParam;
        return OR_CONTINUE;
    }
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
