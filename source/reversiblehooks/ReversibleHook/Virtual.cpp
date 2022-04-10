#include "StdInc.h"

#include "Virtual.h"

namespace ReversibleHooks{
namespace ReversibleHook{
Virtual::Virtual(std::string fnName, void** pvtblGTA, uint32 vtblIdx, void* pfnOur) :
    Base{ std::move(fnName), HookType::Virtual },
    m_pvtblGTA{pvtblGTA},
    m_vtblIdx{vtblIdx},
    m_pfnOur{pfnOur}
{
    // Make sure we have R/W access to the vtbl entry
    detail::ScopedVirtualProtectAutoRollback svpm{ m_pvtblGTA, sizeof(void*), PAGE_EXECUTE_READWRITE };

    // Read original pfn
    m_pfnGTA = m_pvtblGTA[m_vtblIdx];

    // Modify the vtable entry to point to our function
    m_pvtblGTA[m_vtblIdx] = m_pfnOur;


};

void Virtual::Switch() {

}
};
};
