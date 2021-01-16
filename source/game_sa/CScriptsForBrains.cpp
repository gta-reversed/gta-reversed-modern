#include "StdInc.h"

void CScriptsForBrains::MarkAttractorScriptBrainWithThisNameAsNoLongerNeeded(char const* name)
{
    plugin::CallMethod<0x46AAE0, CScriptsForBrains*, char const*>(this, name);
}

void CScriptsForBrains::RequestAttractorScriptBrainWithThisName(char const* name)
{
    plugin::CallMethod<0x46AA80, CScriptsForBrains*, char const*>(this, name);
}
