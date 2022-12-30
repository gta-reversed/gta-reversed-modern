#pragma once

/*!
* Various Script commands
*/

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
