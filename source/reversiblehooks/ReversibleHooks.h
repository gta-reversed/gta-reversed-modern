#pragma once

#include <unordered_map>
#include <vector>
#include <string>

enum class eReversibleHookType {
    Simple,
    Virtual
};

#pragma pack(push, 1)
struct SHookContent {
    unsigned char jumpOpCode = JUMP_OPCODE;
    unsigned int jumpLocation = 0;
    unsigned char possibleNops[52 - sizeof(jumpOpCode) - sizeof(jumpLocation)] = { 0 };
};
#pragma pack(pop)
VALIDATE_SIZE(SHookContent, 0x34);

struct SReversibleHook {
    bool m_bIsHooked = false;
    bool m_bImguiHooked = false;
    std::string m_sIdentifier;
    std::string m_sFunctionName;
    eReversibleHookType m_eHookType;

    SReversibleHook(std::string id, std::string name, eReversibleHookType type);
    virtual ~SReversibleHook() = default;
    virtual void Switch() = 0;
};

struct SSimpleReversibleHook : SReversibleHook {
    SHookContent m_HookContent;
    unsigned char m_OriginalFunctionContent[sizeof(m_HookContent)];
    unsigned int m_iHookedBytes;
    unsigned int m_iRealHookedAddress;

    SHookContent m_LibHookContent;
    unsigned char m_LibOriginalFunctionContent[sizeof(m_LibHookContent)];
    unsigned int m_iLibHookedBytes;
    unsigned int m_iLibFunctionAddress;

    SSimpleReversibleHook(std::string id, std::string name, uint32_t installAddress, void* addressToJumpTo, int iJmpCodeSize = 5);
    virtual void Switch() override;
    virtual ~SSimpleReversibleHook() override = default;
};

struct SVirtualReversibleHook : SReversibleHook {
    std::vector<uint32_t> m_vecHookedAddresses;
    uint32_t m_OriginalFunctionAddress;
    uint32_t m_LibFunctionAddress;

    SVirtualReversibleHook(std::string id, std::string name, void* libFuncAddress, const std::vector<uint32_t>& vecAddressesToHook);
    virtual void Switch() override;
    virtual ~SVirtualReversibleHook() override = default;
};

namespace ReversibleHooks {
    namespace detail {
        void HookInstall(const std::string& sIdentifier, const std::string& sFuncName, unsigned int installAddress, void* addressToJumpTo, int iJmpCodeSize = 5, bool bDisableByDefault = false);
        void HookInstallVirtual(const std::string& sIdentifier, const std::string& sFuncName, void* libVTableAddress, const std::vector<uint32_t>& vecAddressesToHook);
        void HookSwitch(std::shared_ptr<SReversibleHook> pHook);
        bool IsFunctionHooked(const std::string& sIdentifier, const std::string& sFuncName);
        std::shared_ptr<SReversibleHook> GetHook(const std::string& sIdentifier, const std::string& sFuncName);
    };

    template <typename T>
    static void Install(const std::string& sIdentifier, const std::string& sFuncName, DWORD installAddress, T addressToJumpTo, bool bDisableByDefault = false, int iJmpCodeSize = 5) {
        auto ptr = FunctionPointerToVoidP(addressToJumpTo);
        detail::HookInstall(sIdentifier, sFuncName, installAddress, ptr, iJmpCodeSize, bDisableByDefault);
    }

    template <typename T>
    static void InstallVirtual(const std::string& sIdentifier, const std::string& sFuncName, T libVTableAddress, const std::vector<uint32_t>& vecAddressesToHook) {
        auto ptr = FunctionPointerToVoidP(libVTableAddress);
        detail::HookInstallVirtual(sIdentifier, sFuncName, ptr, vecAddressesToHook);
    }

    static void Switch(std::shared_ptr<SReversibleHook> pHook) {
        detail::HookSwitch(pHook);
    }

    std::map<std::string, std::vector<std::shared_ptr<SReversibleHook>>>& GetAllHooks();

    void UnHook(const std::string& className, const char* functionName = nullptr);

    constexpr unsigned int x86JMPSize = 5U;
    unsigned int GetJMPLocation(unsigned int dwFrom, unsigned int dwTo);
    unsigned int GetFunctionLocationFromJMP(unsigned int dwJmpLoc, unsigned int dwJmpOffset);
};
