#pragma once 

#include "ReversibleHook/Base.h"

#include <Base.h>

namespace ReversibleHooks{
namespace ReversibleHook {

#pragma pack(push, 1)
struct SHookContent {
    uint8  jumpOpCode{(uint8)JUMP_OPCODE};
    uint32 jumpLocation{};
    uint8  possibleNops[52 - sizeof(jumpOpCode) - sizeof(jumpLocation)]{};
};
#pragma pack(pop)
VALIDATE_SIZE(SHookContent, 0x34);

struct Simple : Base {
    // TODO: Refactor this copy-pate and document it

    SHookContent m_HookContent{};
    uint8        m_OriginalFunctionContent[sizeof(m_HookContent)]{};
    uint32       m_iHookedBytes{};
    uint32       m_iRealHookedAddress{};

    SHookContent m_LibHookContent{};
    uint8        m_LibOriginalFunctionContent[sizeof(m_LibHookContent)]{};
    uint32       m_iLibHookedBytes{};
    uint32       m_iLibFunctionAddress{};

    Simple(std::string fnName, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize = 5);

    virtual ~Simple() override = default;

    bool CheckLibFnForChangesAndStore(void* expected);
    void ApplyJumpToGTACode();
    virtual void Switch() override;
    virtual void Check() override;
};

};
};
