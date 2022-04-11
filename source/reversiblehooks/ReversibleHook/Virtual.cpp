#include "StdInc.h"
#include "Virtual.h"
#include "extensions/enumerate.hpp"

namespace ReversibleHooks{
namespace ReversibleHook{
Virtual::Virtual(std::string fnName, void** pvtblGTA, void** pvtblOur, uint32 vtblIdx) :
    Base{ std::move(fnName), HookType::Virtual },
    m_pvtbls{pvtblGTA, pvtblOur},
    m_vtblIdx{vtblIdx}
{
    // Store original fnptr's
    for (auto [i, vtbl] : notsa::enumerate(m_pvtbls)) {
        // By default we should have read access to these pages, so no need to call `VirtualProtect`
        m_pfns[i] = vtbl[vtblIdx];
    }

    // Attach hook
    Switch();
};

void Virtual::Switch() {
    m_bIsHooked = !m_bIsHooked;
    for (auto [i, vtbl] : notsa::enumerate(m_pvtbls)) {
        detail::ScopedVirtualProtectAutoRollback svpm{ &vtbl[m_vtblIdx], sizeof(void*), PAGE_EXECUTE_READWRITE}; // We really only need write access here
        vtbl[m_vtblIdx] = m_pfns[m_bIsHooked ? OUR : GTA];
    }
}

void Virtual::Check() {
    // Nothing to do
}
};
};
