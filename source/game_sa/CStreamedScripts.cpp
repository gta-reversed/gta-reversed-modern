#include "StdInc.h"

void CStreamedScripts::Initialise() {
    plugin::CallMethod<0x470660, CStreamedScripts*>(this);
}

void CStreamedScripts::LoadStreamedScript(RwStream* stream, int index) {
    plugin::CallMethod<0x470840, CStreamedScripts*, RwStream*, int>(this, stream, index);
}

void CStreamedScripts::ReInitialise() {
    plugin::CallMethod<0x4706A0, CStreamedScripts*>(this);
}

void CStreamedScripts::RemoveStreamedScriptFromMemory(int index) {
    plugin::CallMethod<0x4708E0, CStreamedScripts*, int>(this, index);
}

int CStreamedScripts::RegisterScript(const char* scriptName) {
    return plugin::CallMethodAndReturn<int, 0x4706C0, CStreamedScripts*, char const*>(this, scriptName);
}
