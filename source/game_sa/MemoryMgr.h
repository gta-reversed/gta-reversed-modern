#pragma once

#include <cstddef>

static inline char(&s_MemoryHeapBuffer)[16384] = *(char(*)[16384])0xC8E0C8;

class CMemoryMgr {
public:
    static void   Init(){}; // NOP
    static void*  Malloc(size_t size);
    static void   Free(void* memory);
    static void*  Realloc(void* memory, size_t size);
    static void*  Calloc(size_t elemsize, size_t nelems);
    static void*  InitScratchPad();
    static void   LockScratchPad();
    static void   ReleaseScratchPad();
    static uint8* MallocAlign(size_t size, uintptr_t align);
    static void   FreeAlign(void* memory);
};
