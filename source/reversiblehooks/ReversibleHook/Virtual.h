#pragma once

#include "Base.h" 

#include <vector>
#include <string>
#include "Base.h"

namespace ReversibleHooks{
namespace ReversibleHook{

struct Virtual : Base {
    Virtual(std::string fnName, void** pvtblGTA, void** pvtblOur, uint32 vtblIdx);
    ~Virtual() override = default;
 
    void Switch() override;
    void Check() override; 
private:
    enum {
        GTA,
        OUR
    };

    // These 2 arrays are indexed using the above enum
    void** m_pvtbl[2]{};        // vtbl pointers
    void*  m_pfn[2]{};          // Original function pointers
    //uint8  m_originalByte[2]{}; // We replace the beginning of both functions with a hardware break (`int3`). This here stores the original beginning.
    uint32 m_vtblIdx{};         // Index of this function in the vtable
};
};
};
