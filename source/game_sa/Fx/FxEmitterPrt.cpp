#include "StdInc.h"

#include "FxEmitterPrt.h"
#include "FxManager.h"

// 0x4A18B0
void* FxEmitterPrt_c::operator new[](uint32 size) {
    return g_fxMan.GetMemPool().GetMem(size);
}
