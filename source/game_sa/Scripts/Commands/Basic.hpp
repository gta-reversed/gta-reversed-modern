#pragma once
#include <functional>
#include "CommandParser/Parser.hpp"

/*
* Basic language feature commands (Comparasions, assingments, etc...)
*/


REGISTER_COMMAND_HANDLER(COMMAND_WAIT, [](CRunningScript& S, uint32 duration) {
    S.m_nWakeTime = CTimer::GetTimeInMS() + duration;
    return OR_WAIT;
});

REGISTER_COMMAND_HANDLER(COMMAND_GOTO, [](CRunningScript& S, int32 address) -> void { S.UpdatePC(address); });

//
// GREATER_OR_EQUAL
//
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_VAR, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_VAR, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_NUMBER, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_VAR, [](float lhs, float rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_VAR, [](float lhs, float rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_CONSTANT, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_NUMBER, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_CONSTANT, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_VAR, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR, [](float lhs, float rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR, [](float lhs, float rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_NUMBER, [](float lhs, float rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_VAR, [](int32 lhs, int32 rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_NUMBER, [](float lhs, float rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_LVAR, [](float lhs, float rhs) { return lhs >= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_VAR, [](float lhs, float rhs) { return lhs >= rhs; });


//
// GREATER
//
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_VAR, [](float lhs, float rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_LVAR, [](float lhs, float rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_LVAR_GREATER_THAN_NUMBER, [](float lhs, float rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_NUMBER_GREATER_THAN_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_VAR, [](float lhs, float rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_GREATER_THAN_NUMBER, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_GREATER_THAN_INT_VAR, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_CONSTANT_GREATER_THAN_INT_VAR, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_CONSTANT_GREATER_THAN_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_LVAR, [](float lhs, float rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_GREATER_THAN_INT_VAR, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_GREATER_THAN_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_VAR, [](float lhs, float rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_GREATER_THAN_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_LVAR, [](float lhs, float rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_GREATER_THAN_CONSTANT, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_GREATER_THAN_CONSTANT, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_NUMBER_GREATER_THAN_INT_VAR, [](int32 lhs, int32 rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_VAR_GREATER_THAN_NUMBER, [](float lhs, float rhs) { return lhs > rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER, [](int32 lhs, int32 rhs) { return lhs > rhs; });

//
// EQUAL
//
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_EQUAL_TO_NUMBER, [](int32 lhs, int32 rhs) { return lhs == rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_LVAR_EQUAL_TO_NUMBER, [](float lhs, float rhs) { return lhs == rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_LVAR, [](float lhs, float rhs) { return lhs == rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_LVAR_EQUAL_TO_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs == rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_EQUAL_TO_INT_VAR, [](int32 lhs, int32 rhs) { return lhs == rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_VAR, [](float lhs, float rhs) { return lhs == rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_EQUAL_TO_INT_LVAR, [](int32 lhs, int32 rhs) { return lhs == rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_VAR_EQUAL_TO_NUMBER, [](float lhs, float rhs) { return lhs == rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_INT_VAR_EQUAL_TO_NUMBER, [](int32 lhs, int32 rhs) { return lhs == rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_IS_FLOAT_LVAR_EQUAL_TO_FLOAT_LVAR, [](float lhs, float rhs) { return lhs == rhs; });

//
// SUB
//
REGISTER_COMMAND_HANDLER(COMMAND_SUB_INT_LVAR_FROM_INT_VAR, [](int32& lhs, int32 rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_LVAR, [](float& lhs, float rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_INT_VAR_FROM_INT_VAR, [](int32& lhs, int32 rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_INT_LVAR_FROM_INT_LVAR, [](int32& lhs, int32 rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_VAR, [](float& lhs, float rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_LVAR, [](float& lhs, float rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_INT_VAR_FROM_INT_LVAR, [](int32& lhs, int32 rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_VAL_FROM_FLOAT_LVAR, [](float& lhs, float rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_VAR, [](float& lhs, float rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_VAL_FROM_INT_VAR, [](int32& lhs, int32 rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_VAL_FROM_FLOAT_VAR, [](float& lhs, float rhs) { lhs -= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_VAL_FROM_INT_LVAR, [](int32& lhs, int32 rhs) { lhs -= rhs; });

//
// ADD
//
REGISTER_COMMAND_HANDLER(COMMAND_ADD_INT_VAR_TO_INT_VAR, [](int32& lhs, int32 rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_VAR, [](float& lhs, float rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_INT_LVAR_TO_INT_LVAR, [](int32& lhs, int32 rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_FLOAT_VAR_TO_FLOAT_LVAR, [](float& lhs, float rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_VAL_TO_INT_LVAR, [](int32& lhs, int32 rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_INT_LVAR_TO_INT_VAR, [](int32& lhs, int32 rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_INT_VAR_TO_INT_LVAR, [](int32& lhs, int32 rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_FLOAT_VAR_TO_FLOAT_VAR, [](float& lhs, float rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_VAL_TO_FLOAT_VAR, [](float& lhs, float rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_LVAR, [](float& lhs, float rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_VAL_TO_FLOAT_LVAR, [](float& lhs, float rhs) { lhs += rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_VAL_TO_INT_VAR, [](int32& lhs, int32 rhs) { lhs += rhs; });

//
// MULT
//
REGISTER_COMMAND_HANDLER(COMMAND_MULT_FLOAT_VAR_BY_VAL, [](float& lhs, float rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_INT_LVAR_BY_INT_VAR, [](int32& lhs, int32 rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_INT_LVAR_BY_VAL, [](int32& lhs, int32 rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_VAR, [](float& lhs, float rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_LVAR, [](float& lhs, float rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_FLOAT_VAR_BY_FLOAT_LVAR, [](float& lhs, float rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_INT_VAR_BY_INT_VAR, [](int32& lhs, int32 rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_FLOAT_LVAR_BY_VAL, [](float& lhs, float rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_FLOAT_VAR_BY_FLOAT_VAR, [](float& lhs, float rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_INT_LVAR_BY_INT_LVAR, [](int32& lhs, int32 rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_INT_VAR_BY_INT_LVAR, [](int32& lhs, int32 rhs) { lhs *= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_INT_VAR_BY_VAL, [](int32& lhs, int32 rhs) { lhs *= rhs; });

//
// DIV
//
REGISTER_COMMAND_HANDLER(COMMAND_DIV_INT_VAR_BY_INT_VAR, [](int32& lhs, int32 rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_FLOAT_LVAR_BY_VAL, [](float& lhs, float rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_INT_LVAR_BY_VAL, [](int32& lhs, int32 rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_FLOAT_VAR_BY_FLOAT_LVAR, [](float& lhs, float rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_VAR, [](float& lhs, float rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_FLOAT_VAR_BY_VAL, [](float& lhs, float rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_INT_VAR_BY_VAL, [](int32& lhs, int32 rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_FLOAT_VAR_BY_FLOAT_VAR, [](float& lhs, float rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_LVAR, [](float& lhs, float rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_INT_VAR_BY_INT_LVAR, [](int32& lhs, int32 rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_INT_LVAR_BY_INT_VAR, [](int32& lhs, int32 rhs) { lhs /= rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_INT_LVAR_BY_INT_LVAR, [](int32& lhs, int32 rhs) { lhs /= rhs; });

//
// SET
//
REGISTER_COMMAND_HANDLER(COMMAND_CSET_VAR_INT_TO_LVAR_FLOAT, [](int32& lhs, float rhs) { lhs = (int32)rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_CSET_VAR_FLOAT_TO_LVAR_INT, [](float& lhs, int32 rhs) { lhs = (float)rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_CSET_LVAR_INT_TO_LVAR_FLOAT, [](int32& lhs, float rhs) { lhs = (int32)rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_LVAR_INT_TO_VAR_INT, [](int32& lhs, int32 rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_LVAR_FLOAT_TO_LVAR_FLOAT, [](float& lhs, float rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_VAR_INT_TO_VAR_INT, [](int32& lhs, int32 rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_VAR_FLOAT_TO_LVAR_FLOAT, [](float& lhs, float rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_VAR_INT_TO_LVAR_INT, [](int32& lhs, int32 rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_CSET_LVAR_INT_TO_VAR_FLOAT, [](int32& lhs, float rhs) { lhs = (int32)rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_LVAR_INT_TO_LVAR_INT, [](int32& lhs, int32 rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_CSET_LVAR_FLOAT_TO_VAR_INT, [](float& lhs, int32 rhs) { lhs = (float)rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_CSET_LVAR_FLOAT_TO_LVAR_INT, [](float& lhs, int32 rhs) { lhs = (float)rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_VAR_INT_TO_CONSTANT, [](int32& lhs, int32 rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_LVAR_INT_TO_CONSTANT, [](int32& lhs, int32 rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_VAR_FLOAT_TO_VAR_FLOAT, [](float& lhs, float rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_CSET_VAR_INT_TO_VAR_FLOAT, [](int32& lhs, float rhs) { lhs = (int32)rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_CSET_VAR_FLOAT_TO_VAR_INT, [](float& lhs, int32 rhs) { lhs = (float)rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_LVAR_FLOAT_TO_VAR_FLOAT, [](float& lhs, float rhs) { lhs = rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_VAR_INT, [](int32& lhs, int32 value) { lhs = value; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_VAR_FLOAT, [](float& lhs, float value) { lhs = value; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_LVAR_INT, [](int32& lhs, int32 value) { lhs = value; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_LVAR_FLOAT, [](float& lhs, float value) { lhs = value; });

//
// SUB TIMED
//
REGISTER_COMMAND_HANDLER(COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_LVAR, [](float& lhs, float rhs) { lhs -= CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_LVAR, [](float& lhs, float rhs) { lhs -= CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_VAR, [](float& lhs, float rhs) { lhs -= CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_TIMED_VAL_FROM_FLOAT_VAR, [](float& lhs, float rhs) { lhs -= CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_VAR, [](float& lhs, float rhs) { lhs -= CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_TIMED_VAL_FROM_FLOAT_LVAR, [](float& lhs, float rhs) { lhs -= CTimer::GetTimeStep() * rhs; });

//
// ADD TIMED
//
REGISTER_COMMAND_HANDLER(COMMAND_ADD_TIMED_VAL_TO_FLOAT_VAR, [](float& lhs, float rhs) { lhs += CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_TIMED_VAL_TO_FLOAT_LVAR, [](float& lhs, float rhs) { lhs += CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_VAR, [](float& lhs, float rhs) { lhs += CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_VAR, [](float& lhs, float rhs) { lhs += CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_LVAR, [](float& lhs, float rhs) { lhs += CTimer::GetTimeStep() * rhs; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_LVAR, [](float& lhs, float rhs) { lhs += CTimer::GetTimeStep() * rhs; });

// ABS
REGISTER_COMMAND_HANDLER(COMMAND_ABS_VAR_INT, [](int32& lhs, int32 value) { lhs = std::abs(value); });
REGISTER_COMMAND_HANDLER(COMMAND_ABS_LVAR_INT, [](int32& lhs, int32 value) { lhs = std::abs(value); });
REGISTER_COMMAND_HANDLER(COMMAND_ABS_VAR_FLOAT, [](float& lhs, float value) { lhs = std::abs(value); });
REGISTER_COMMAND_HANDLER(COMMAND_ABS_LVAR_FLOAT, [](float& lhs, float value) { lhs = std::abs(value); });

REGISTER_COMMAND_HANDLER(COMMAND_GOTO_IF_FALSE, [](CRunningScript& S, int32 goToAddress) {
    if (S.m_bCondResult) {
        S.UpdatePC(goToAddress);
    }
});

void DebugOn() {
#ifndef FINAL
    CTheScripts::DbgFlag = true;
#endif
}
REGISTER_COMMAND_HANDLER(COMMAND_DEBUG_ON, DebugOn);

void DebugOff() {
#ifndef FINAL
    CTheScripts::DbgFlag = false;
#endif
}
REGISTER_COMMAND_HANDLER(COMMAND_DEBUG_OFF, DebugOff);

REGISTER_COMMAND_HANDLER(COMMAND_RETURN_TRUE, []() { // 0x0C5
    return true;
});

REGISTER_COMMAND_HANDLER(COMMAND_RETURN_FALSE, []() { // 0x0C6
    return false;
});


REGISTER_COMMAND_HANDLER(COMMAND_TERMINATE_THIS_SCRIPT,  [](CRunningScript& S) { // 0x04E 
    if (S.m_bIsMission) {
        CTheScripts::bAlreadyRunningAMissionScript = false;
    }
    S.RemoveScriptFromList(&CTheScripts::pActiveScripts);
    S.AddScriptToList(&CTheScripts::pIdleScripts);
    S.ShutdownThisScript();
    return OR_WAIT;
});

REGISTER_COMMAND_HANDLER(COMMAND_START_NEW_SCRIPT,  [](CRunningScript& S, int32 offset) { // 0x04F
    if (offset < 0) {// This doesn't make sense
        offset = COMMAND_START_NEW_SCRIPT; // For Mobile, offset is set to 0 here. WD fix perhaps?
    }

    CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[offset]);
    S.ReadParametersForNewlyStartedScript(script);
    return OR_CONTINUE;
});


REGISTER_COMMAND_HANDLER(COMMAND_ANDOR, [](CRunningScript& S, int32 logicalOp) { // 0x0D6
    S.m_nLogicalOp = logicalOp;
    if (S.m_nLogicalOp == CRunningScript::ANDOR_NONE) {
        S.m_bCondResult = false;
    } else if (S.m_nLogicalOp >= CRunningScript::ANDS_1 && S.m_nLogicalOp <= CRunningScript::ANDS_8) { // It's an `AND`
        S.m_nLogicalOp++;
        S.m_bCondResult = true;
    } else if (S.m_nLogicalOp >= CRunningScript::ORS_1 && S.m_nLogicalOp <= CRunningScript::ORS_8) { // It's an `OR`
        S.m_nLogicalOp++;
        S.m_bCondResult = false;
    } else {
        NOTSA_UNREACHABLE("Unknown LogicalOp: {}", logicalOp);
    }
    return OR_CONTINUE;
});

REGISTER_COMMAND_HANDLER(COMMAND_GOSUB,  [](CRunningScript& S, int32 goToAddress) { // 0x050 
    S.m_apStack[S.m_nSP++] = S.m_pCurrentIP;
    S.UpdatePC(goToAddress);
});

REGISTER_COMMAND_HANDLER(COMMAND_RETURN,  [](CRunningScript& S) { // 0x051
    S.m_pCurrentIP = S.m_apStack[--S.m_nSP];
});
