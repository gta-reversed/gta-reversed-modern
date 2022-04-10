#pragma once

#include "Base.h" 

#include <vector>
#include <string>
#include "Base.h"

namespace ReversibleHooks{
namespace ReversibleHook{

struct Virtual : Base {
    Virtual(std::string fnName, void** pvtblGTA, uint32 vtblIdx, void* pfnOur);
    ~Virtual() override = default;
 
    void Switch() override;
    void Check() override {} // Nothing to do 
private:
    void** m_pvtblGTA{};   // Pointer to GTA vtable
    uint32 m_vtblIdx{};   // Index of this function in the vtable
    void*  m_pfnOur{};  // Our function
    void*  m_pfnGTA{};  // The original GTA function (Extracted from the vtable)

    SHookContent m_LibHookContent{};
    uint8        m_LibOriginalFunctionContent[sizeof(m_LibHookContent)]{};
    uint32       m_iLibHookedBytes{};
    uint32       m_iLibFunctionAddress{};
};
};
};
