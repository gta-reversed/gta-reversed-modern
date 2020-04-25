#include "StdInc.h"

void CMemoryMgr::Free(void* memory)
{
    plugin::Call<0x72F430, void*>(memory);
}

void CMemoryMgr::FreeAlign(void* memory)
{
    plugin::Call<0x72F4F0, void*>(memory);
}
