#include "StdInc.h"

CEventScriptCommand* CEventScriptCommand::Constructor(int command, CTask* pTask, char a3)
{
    return plugin::CallMethodAndReturn< CEventScriptCommand*, 0x4B0A00, CEventScriptCommand*, int, CTask*, char>(this, command, pTask, a3);
}

void CEventScriptCommand::Destructor()
{
    plugin::CallMethod<0x4B0A50, CEventScriptCommand*>(this);
}