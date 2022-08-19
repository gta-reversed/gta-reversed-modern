#pragma once

#include "Base.h" 

#include <vector>
#include <string>
#include "Base.h"

namespace ReversibleHooks{
namespace ReversibleHook{
struct Virtual : public Base {
    Virtual(std::string fnName, void** vtblGTA, void** vtblOur, size_t fnIdx);
    ~Virtual() override = default;

    void Switch() override;
    void Check() override {} // Nothing to do 
private:
    // Use these values for indexing below arrays
    constexpr static auto GTA = 0u;
    constexpr static auto OUR = 0u;

    // Original function pointers
    void* m_pfns[2]{};

    // vtables
    void** m_vtbls[2]{};

    // Function index in vtable
    size_t m_fnIdx{};
};

};
};
