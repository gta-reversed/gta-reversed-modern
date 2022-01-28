#pragma once

#include <string>

namespace ReversibleHooks{

// TODO: Maybe this should go into `detail`
constexpr uint32 JUMP_OPCODE = 0xE9;
constexpr uint32 NOP_OPCODE  = 0x90;

constexpr uint32 x86JMPSize = 5U;
constexpr auto GetJMPLocation(uint32 dwFrom, uint32 dwTo) { return dwTo - dwFrom - x86JMPSize; }
constexpr auto GetFunctionLocationFromJMP(uint32 dwJmpLoc, uint32 dwJmpOffset) { return dwJmpOffset + dwJmpLoc + x86JMPSize; }

namespace ReversibleHook {
struct Base {
    enum class HookType { // Sadly can't use `Type` alone as it's some function..
        Simple,
        Virtual
    };

    Base(std::string fnName, HookType type) :
        m_fnName{std::move(fnName)},
        m_type{type}
    {
    }

    virtual ~Base() = default;

    virtual void Switch() = 0;
    virtual void Check() = 0;

    void State(bool hooked) {
        if (m_bIsHooked != hooked) {
            Switch();
        }
    }

    const auto& Name()   const { return m_fnName; }
    const auto  Type()   const { return m_type; }
    const auto  Hooked() const { return m_bIsHooked; }
    const char* Symbol() const { return Type() == HookType::Simple ? "S" : "V"; } // Symbol in ImGui
    
    bool m_bImguiHooked = false;   // Workaround for imgui - Maybe somehow get rid of it in the future..
protected:
    bool        m_bIsHooked{};     // Is hook installed
    std::string m_fnName{}; // Name of function, eg.: `Add` (Referring to CEntity::Add)
    HookType    m_type{};
};
};
};
