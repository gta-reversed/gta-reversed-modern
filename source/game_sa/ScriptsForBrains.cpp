#include "StdInc.h"

#include "ScriptsForBrains.h"

void CScriptsForBrains::CheckIfNewEntityNeedsScript(CEntity* pEntity, int8 attachType, void* unused)
{
    plugin::CallMethod<0x46FF20, CScriptsForBrains*, CEntity*, int8, void*>(this, pEntity, attachType, unused);
}

void CScriptsForBrains::MarkAttractorScriptBrainWithThisNameAsNoLongerNeeded(char const* name)
{
    plugin::CallMethod<0x46AAE0, CScriptsForBrains*, char const*>(this, name);
}

void CScriptsForBrains::RequestAttractorScriptBrainWithThisName(char const* name)
{
    plugin::CallMethod<0x46AA80, CScriptsForBrains*, char const*>(this, name);
}
