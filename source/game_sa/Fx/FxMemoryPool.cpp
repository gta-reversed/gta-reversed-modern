#include "StdInc.h"

#include "FxMemoryPool.h"

void FxMemoryPool_c::InjectHooks() {
    RH_ScopedClass(FxMemoryPool_c);
    RH_ScopedCategory("Fx");

    RH_ScopedInstall(Init, 0x4A9C30);
    RH_ScopedInstall(Exit, 0x4A9C80);
    RH_ScopedInstall(Reset, 0x4A9C90);
    RH_ScopedInstall(GetMem, 0x4A9CA0);
    RH_ScopedInstall(Optimise, 0x4A9CD0);
}

// 0x4A9C30
void FxMemoryPool_c::Init() {
    m_nSize     = 1024 * 1024; // 1 megabyte
    m_nPosition = 0;
    m_pData     = static_cast<uint8*>(CMemoryMgr::Malloc(m_nSize));

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
    m_pData = static_cast<uint8*>(CMemoryMgr::Realloc(m_pData, m_nPosition));
    m_nSize = m_nPosition;
}
