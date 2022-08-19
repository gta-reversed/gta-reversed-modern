#include "StdInc.h"

#include <extensions/enumerate.hpp>
#include <ReversibleHook/Virtual.h>

namespace ReversibleHooks{
namespace ReversibleHook{
Virtual::Virtual(std::string fnName, void** vtblGTA, void** vtblOur, size_t fnIdx) :
    Base{ std::move(fnName), HookType::Virtual },
    m_vtbls{vtblGTA, vtblOur} // Should be in the same order as the indexers: GTA, OUR
{
    for (const auto [i, vtbl] : notsa::enumerate(m_vtbls)) {
        m_pfns[i] = vtbl[fnIdx];
    }

    Switch();
};

void Virtual::Switch()
{
    m_bIsHooked = !m_bIsHooked;

    // Redirect VTBL entries
    const auto pfn = m_pfns[m_bIsHooked ? OUR : GTA];
    for (const auto vtbl : m_vtbls) {
        detail::ScopedVirtualProtectModify m{ vtbl, sizeof(void*) }; // Make sure we have permissions writing here...
        vtbl[m_fnIdx] = pfn;
    }

    // TODO: Also install trampoline to redirect direct virtual calls (Eg.: `CVehicle::Render` calls `CEntity::Render` directly)
    //       With little modification we could use a Simple hook, but tbh I'd recommend using the Detours lib.
}
};
};
