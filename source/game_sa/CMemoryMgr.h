#pragma once

class CMemoryMgr 
{
public:
    static std::uint8_t* MallocAlign(std::int32_t size, std::int32_t align);
    static void Free(void* memory);
    static void FreeAlign(void* memory);
};
