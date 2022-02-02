#pragma once

#include "Base.h" 

#include <vector>
#include <string>
#include "Base.h"

namespace ReversibleHooks{
namespace ReversibleHook{

struct Virtual : Base {
    Virtual(std::string fnName, void* libFuncAddress, std::vector<uint32> vecAddressesToHook);
    virtual ~Virtual() override = default;

    virtual void Switch() override;
    virtual void Check() override {} // Nothing to do 
private:
    std::vector<uint32> m_vecHookedAddresses;
    uint32              m_OriginalFunctionAddress;
    uint32              m_LibFunctionAddress;
};

};
};
