#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#pragma pack(push, 1)
struct SHookContent {
    unsigned char jumpOpCode = JUMP_OPCODE;
    unsigned int jumpLocation = 0;
    unsigned char possibleNops[52 - sizeof(jumpOpCode) - sizeof(jumpLocation)] = { 0 };
};
#pragma pack(pop)
static_assert(sizeof(SHookContent) == 0x34, "Incorrect struct size: SHookContent");

struct SReversibleHook {
    SHookContent m_HookContent;
    unsigned char m_OriginalFunctionContent[sizeof(m_HookContent)];
    unsigned int m_iHookedBytes;
    unsigned int m_iRealHookedAddress;

    SHookContent m_LibHookContent;
    unsigned char m_LibOriginalFunctionContent[sizeof(m_LibHookContent)];
    unsigned int m_iLibHookedBytes;
    unsigned int m_iLibFunctionAddress;

    bool m_bIsHooked = false;
    bool m_bImguiHooked = false;
    std::string m_sIdentifier;
    std::string m_sFunctionName;
};

class ReversibleHooks {
public:
    static ReversibleHooks& GetInstance() {
        static ReversibleHooks instance;
        return instance;
    }

    template <typename T>
    static void Install(const std::string& sIdentifier, const std::string& sFuncName, DWORD installAddress, T addressToJumpTo, int iJmpCodeSize = 5) {
        auto ptr = FunctionPointerToVoidP(addressToJumpTo);
        ReversibleHooks::GetInstance().HookInstall(sIdentifier, sFuncName, installAddress, ptr, iJmpCodeSize);
    }
    static void Switch(SReversibleHook& sHook) {
        ReversibleHooks::GetInstance().HookSwitch(sHook);
    }
    static std::unordered_map<std::string, std::vector<SReversibleHook>>& GetAllHooks() {
        return ReversibleHooks::GetInstance().m_HooksMap;
    }

private:
    void HookInstall(const std::string& sIdentifier, const std::string& sFuncName, unsigned int installAddress, void* addressToJumpTo, int iJmpCodeSize = 5);
    void HookSwitch(SReversibleHook& sHook);
    bool IsFunctionHooked(const std::string& sIdentifier, const std::string& sFuncName);
    SReversibleHook* GetHook(const std::string& sIdentifier, const std::string& sFuncName);

    static constexpr unsigned int x86JMPSize = 5U;
    static unsigned int GetJMPLocation(unsigned int dwFrom, unsigned int dwTo);

private:
    std::unordered_map<std::string, std::vector<SReversibleHook>> m_HooksMap;
    ReversibleHooks() = default;
    ReversibleHooks(ReversibleHooks const&) = delete;
    void operator=(ReversibleHooks const&) = delete;
};
