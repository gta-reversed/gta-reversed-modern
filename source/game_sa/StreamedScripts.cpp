#include "StdInc.h"

#include "StreamedScripts.h"

void CStreamedScripts::Initialise() {
    plugin::CallMethod<0x470660, CStreamedScripts*>(this);
}

void CStreamedScripts::LoadStreamedScript(RwStream* stream, int32 index) {
    plugin::CallMethod<0x470840, CStreamedScripts*, RwStream*, int32>(this, stream, index);
}

void CStreamedScripts::ReInitialise() {
    plugin::CallMethod<0x4706A0, CStreamedScripts*>(this);
}

void CStreamedScripts::RemoveStreamedScriptFromMemory(int32 index) {
    plugin::CallMethod<0x4708E0, CStreamedScripts*, int32>(this, index);
}

int32 CStreamedScripts::RegisterScript(const char* scriptName) {
    return plugin::CallMethodAndReturn<int32, 0x4706C0, CStreamedScripts*, const char*>(this, scriptName);
}
