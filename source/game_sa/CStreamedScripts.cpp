#include "StdInc.h"

void CStreamedScripts::Initialise() {
    plugin::CallMethodDynGlobal<CStreamedScripts *>(0x470660, this);
}

void CStreamedScripts::LoadStreamedScript(RwStream *stream, int index) {
    plugin::CallMethodDynGlobal<CStreamedScripts *, RwStream *, int>(0x470840, this, stream, index);
}

void CStreamedScripts::ReInitialise()
{
    plugin::CallMethod<0x4706A0, CStreamedScripts*>(this);
}

void CStreamedScripts::RemoveStreamedScriptFromMemory(int index) {
    plugin::CallMethodDynGlobal<CStreamedScripts*, int>(0x4708E0, this, index);
}

int CStreamedScripts::RegisterScript(char const* scriptName) {
    return plugin::CallMethodAndReturnDynGlobal<int, CStreamedScripts*, char const*>(0x4706C0, this, scriptName);
}
