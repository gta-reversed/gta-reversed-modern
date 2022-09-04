#pragma once

/*!
* Various Sequence commands
*/

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
