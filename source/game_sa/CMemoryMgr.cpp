#include "StdInc.h"

std::uint8_t* CMemoryMgr::MallocAlign(std::int32_t size, std::int32_t align)
{
    return plugin::CallAndReturn<std::uint8_t*, 0x72F4C0, std::int32_t, std::int32_t>(size, align);
}

void CMemoryMgr::Free(void* memory)
{
    plugin::Call<0x72F430, void*>(memory);
}

void CMemoryMgr::FreeAlign(void* memory)
{
    plugin::Call<0x72F4F0, void*>(memory);
}
