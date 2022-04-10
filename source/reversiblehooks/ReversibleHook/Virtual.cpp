#include "StdInc.h"
#include "Virtual.h"
#include "extensions/enumerate.hpp"

namespace ReversibleHooks{
namespace ReversibleHook{
Virtual::Virtual(std::string fnName, void** pvtblGTA, void** pvtblOur, uint32 vtblIdx) :
    Base{ std::move(fnName), HookType::Virtual },
    m_pvtbl{pvtblGTA, pvtblOur},
    m_vtblIdx{vtblIdx}
{
    // Make sure we have R/W access to the vtbl entry
    detail::ScopedVirtualProtectAutoRollback svpm{ m_pvtbl[GTA][m_vtblIdx], sizeof(void*), PAGE_EXECUTE_READWRITE};

    // Store original fnptr's
    for (auto [i, vtbl] : notsa::enumerate(m_pvtbl)) {
        m_pfn[i] = vtbl[vtblIdx];
    }

    // Attach hook
    Switch();
};

void Virtual::Switch() {
    detail::ScopedVirtualProtectAutoRollback svpm{ &m_pvtbl[GTA][m_vtblIdx], sizeof(void*), PAGE_EXECUTE_READWRITE};

    m_bIsHooked = !m_bIsHooked;
    for (auto [i, vtbl] : notsa::enumerate(m_pvtbl)) {
        vtbl[m_vtblIdx] = m_pfn[m_bIsHooked ? OUR : GTA];
    }
}

void Virtual::Check() {
    // Nothing to do
}
};
};
