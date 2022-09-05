#pragma once

/*!
* Various clock commands
*/



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
OpcodeResult CRunningScript::ProcessCommand<COMMAND_STORE_CLOCK>() { // 0x253
    CClock::StoreClock();
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_RESTORE_CLOCK>() { // 0x254
    CClock::RestoreClock();
    return OR_CONTINUE;
}

