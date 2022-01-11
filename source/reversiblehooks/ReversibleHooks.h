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
    uint8 jumpOpCode = JUMP_OPCODE;
    uint32 jumpLocation = 0;
    uint8 possibleNops[52 - sizeof(jumpOpCode) - sizeof(jumpLocation)] = { 0 };
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
    virtual void Check() = 0;
};

struct SSimpleReversibleHook : SReversibleHook {
    SHookContent m_HookContent;
    uint8        m_OriginalFunctionContent[sizeof(m_HookContent)];
    uint32       m_iHookedBytes;
    uint32       m_iRealHookedAddress;

    SHookContent m_LibHookContent;
    uint8        m_LibOriginalFunctionContent[sizeof(m_LibHookContent)];
    uint32       m_iLibHookedBytes;
    uint32       m_iLibFunctionAddress;

    SSimpleReversibleHook(std::string id, std::string name, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize = 5);
    bool CheckLibFnForChangesAndStore(void* expected);
    void ApplyJumpToGTACode();
    virtual void Switch() override;
    virtual void Check() override;
    virtual ~SSimpleReversibleHook() override = default;
};

struct SVirtualReversibleHook : SReversibleHook {
    std::vector<uint32> m_vecHookedAddresses;
    uint32              m_OriginalFunctionAddress;
    uint32              m_LibFunctionAddress;

    SVirtualReversibleHook(std::string id, std::string name, void* libFuncAddress, const std::vector<uint32>& vecAddressesToHook);
    virtual void Switch() override;
    virtual void Check() override {}
    virtual ~SVirtualReversibleHook() override = default;
};

namespace ReversibleHooks {
    namespace detail {
        void HookInstall(const std::string& sIdentifier, const std::string& sFuncName, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize = 5, bool bDisableByDefault = false);
        void HookInstallVirtual(const std::string& sIdentifier, const std::string& sFuncName, void* libVTableAddress, const std::vector<uint32>& vecAddressesToHook);
        void HookSwitch(std::shared_ptr<SReversibleHook> pHook);
        bool IsFunctionHooked(const std::string& sIdentifier, const std::string& sFuncName);
        std::shared_ptr<SReversibleHook> GetHook(const std::string& sIdentifier, const std::string& sFuncName);
        void VirtualCopy(void* dst, void* src, size_t nbytes);
    };

    template <typename T>
    static void Install(const std::string& sIdentifier, const std::string& sFuncName, DWORD installAddress, T addressToJumpTo, bool bDisableByDefault = false, int iJmpCodeSize = 5) {
        auto ptr = FunctionPointerToVoidP(addressToJumpTo);
        detail::HookInstall(sIdentifier, sFuncName, installAddress, ptr, iJmpCodeSize, bDisableByDefault);
    }

    template <typename T>
    static void InstallVirtual(const std::string& sIdentifier, const std::string& sFuncName, T libVTableAddress, const std::vector<uint32>& vecAddressesToHook) {
        auto ptr = FunctionPointerToVoidP(libVTableAddress);
        detail::HookInstallVirtual(sIdentifier, sFuncName, ptr, vecAddressesToHook);
    }

    static void Switch(std::shared_ptr<SReversibleHook> pHook) {
        detail::HookSwitch(pHook);
    }

    std::map<std::string, std::vector<std::shared_ptr<SReversibleHook>>>& GetAllHooks();

    void UnHook(const std::string& className, const char* functionName = nullptr);

    void CheckAll();

    constexpr uint32 x86JMPSize = 5U;
    constexpr auto GetJMPLocation(uint32 dwFrom, uint32 dwTo) { return dwTo - dwFrom - x86JMPSize; }
    constexpr auto GetFunctionLocationFromJMP(uint32 dwJmpLoc, uint32 dwJmpOffset) { return dwJmpOffset + dwJmpLoc + x86JMPSize; }
};
