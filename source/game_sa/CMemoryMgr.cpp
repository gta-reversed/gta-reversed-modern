#include "StdInc.h"

#include <cstdlib>

void *CMemoryMgr::Malloc(size_t size)
{
#if defined(USE_GTASA_ALLOCATOR) || defined(USE_DEFAULT_FUNCTIONS)
    return plugin::CallAndReturn<void*, 0x72F420, size_t>(size);
#else
    return malloc(size);
#endif
}

void CMemoryMgr::Free(void* memory)
{
#if defined(USE_GTASA_ALLOCATOR) || defined(USE_DEFAULT_FUNCTIONS)
    plugin::Call<0x72F430, void*>(memory);
#else
    free(memory);
#endif
}

void *CMemoryMgr::Realloc(void *memory, size_t size)
{
#if defined(USE_GTASA_ALLOCATOR) || defined(USE_DEFAULT_FUNCTIONS)
    return plugin::CallAndReturn<void*, 0x72F440, void*, size_t>(memory, size);
#else
    return realloc(memory, size);
#endif
}

void *CMemoryMgr::Calloc(size_t elemsize, size_t nelems)
{
#if defined(USE_GTASA_ALLOCATOR) || defined(USE_DEFAULT_FUNCTIONS)
    return plugin::CallAndReturn<void*, 0x72F460, size_t, size_t>(elemsize, nelems);
#else
    return calloc(elemsize, nelems);
#endif
}

void *CMemoryMgr::InitScratchPad()
{
    // TODO: Please reverse this later
    return plugin::CallAndReturn<void*, 0x72F480>();
}

void CMemoryMgr::LockScratchPad()
{
    // Empty body
}

void CMemoryMgr::ReleaseScratchPad()
{
    // Empty body
}

std::uint8_t *CMemoryMgr::MallocAlign(size_t size, uintptr_t align)
{
#if defined(USE_GTASA_ALLOCATOR) || defined(USE_DEFAULT_FUNCTIONS)
    return plugin::CallAndReturn<std::uint8_t*, 0x72F4C0, size_t, uintptr_t>(size, align);
#else
    std::uint8_t *ptr = (std::uint8_t *) malloc(size + align)
    if (ptr == nullptr)
        return nullptr;

    std::uintptr_t *ptr2 = (std::uintptr_t *) ((uintptr_t) ptr + align & ~(align - 1));
    ptr2[-1] = (uintptr_t) ptr;
    return ptr2;
#endif
}

void CMemoryMgr::FreeAlign(void* memory)
{
#if defined(USE_GTASA_ALLOCATOR) || defined(USE_DEFAULT_FUNCTIONS)
    plugin::Call<0x72F4F0, void*>(memory);
#else
    free(((uintptr_t **) memory)[-1]);
#endif
}

#ifdef USE_GTASA_ALLOCATOR
void *operator new(size_t size)
{
    return plugin::CallAndReturn<void*, 0x82119A, size_t>(size);
}

void *operator new[](size_t size)
{
    return plugin::CallAndReturn<void*, 0x821195, size_t>(size);
}

void operator delete(void *p)
{
    plugin::Call<0x8214BD, void*>(p);
}

void operator delete[](void *p)
{
    plugin::Call<0x8213AE, void*>(p);
}
#endif
