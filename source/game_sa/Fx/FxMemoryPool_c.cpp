#include "StdInc.h"

#include "FxMemoryPool_c.h"

void FxMemoryPool_c::InjectHooks() {
    using namespace ReversibleHooks;
    Install("FxMemoryPool_c", "Init", 0x4A9C30, &FxMemoryPool_c::Init);
    Install("FxMemoryPool_c", "Exit", 0x4A9C80, &FxMemoryPool_c::Exit);
    Install("FxMemoryPool_c", "Reset", 0x4A9C90, &FxMemoryPool_c::Reset);
    Install("FxMemoryPool_c", "GetMem", 0x4A9CA0, &FxMemoryPool_c::GetMem);
    Install("FxMemoryPool_c", "Optimise", 0x4A9CD0, &FxMemoryPool_c::Optimise);
}

// 0x4A9C30
void FxMemoryPool_c::Init() {
    m_nSize     = 1024 * 1024; // 1 megabyte
    m_nPosition = 0;
    m_pData     = static_cast<char*>(CMemoryMgr::Malloc(m_nSize));

    if (m_pData)
        memset(m_pData, 0, m_nSize);
}

// 0x4A9C80
void FxMemoryPool_c::Exit() {
    CMemoryMgr::Free(this);
}

// 0x4A9C90
void FxMemoryPool_c::Reset() {
    m_nPosition = 0;
}

// 0x4A9CA0
void* FxMemoryPool_c::GetMem(int32 size, int32 align) {
    if (m_nPosition % align > 0)
        m_nPosition = align + m_nPosition - m_nPosition % align;

    auto result = m_pData + m_nPosition;
    m_nPosition = size + m_nPosition;
    return result;
}

// 0x4A9CD0
void FxMemoryPool_c::Optimise() {
    m_pData = static_cast<char*>(CMemoryMgr::Realloc(m_pData, m_nPosition));
    m_nSize = m_nPosition;
}
