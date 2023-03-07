#pragma once

/*!
* Various text commands
*/


template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_BIG>() { // 0x0BA
    char label[8];
    ReadTextLabelFromScript(label, 8);
    auto text = TheText.Get(label);
    CollectParameters(2);
    CMessages::AddBigMessage(text, ScriptParams[0].iParam, (eMessageStyle)(ScriptParams[1].iParam - 1));
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT>() { // 0x0BB
    char label[8];
    ReadTextLabelFromScript(label, 8);
    auto text = TheText.Get(label);
    CollectParameters(2);
    if (!text || text[0] != '~' || text[1] != 'z' || text[2] != '~' || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessageQ(text, ScriptParams[0].iParam, ScriptParams[1].iParam, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_NOW>() { // 0x0BC
    char label[8];
    ReadTextLabelFromScript(label, 8);
    auto text = TheText.Get(label);
    CollectParameters(2);
    if (!text || text[0] != '~' || text[1] != 'z' || text[2] != '~' || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessageJump(text, ScriptParams[0].iParam, ScriptParams[1].iParam, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CLEAR_PRINTS>() { // 0x0BE
    CMessages::ClearMessages(false);
    return OR_CONTINUE;
}
