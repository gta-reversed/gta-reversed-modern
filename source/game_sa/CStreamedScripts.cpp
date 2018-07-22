#include "StdInc.h"

void CStreamedScripts::Initialise() {
    plugin::CallMethodDynGlobal<CStreamedScripts *>(0x470660, this);
}

void CStreamedScripts::LoadStreamedScript(RwStream *stream, int index) {
    plugin::CallMethodDynGlobal<CStreamedScripts *, RwStream *, int>(0x470840, this, stream, index);
}