#pragma once

class CMemoryMgr 
{
public:
    static void Free(void* memory);
    static void FreeAlign(void* memory);
};