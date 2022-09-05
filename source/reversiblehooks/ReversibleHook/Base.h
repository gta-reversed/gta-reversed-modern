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
        Virtual,
        ScriptCommand
    };

    Base(std::string fnName, HookType type, bool locked = false) :
        m_fnName{std::move(fnName)},
        m_type{type},
        m_bIsLocked{locked}
    {
    }

    virtual ~Base() = default;

    virtual void Switch() = 0;
    virtual void Check() = 0;

    /*!
    * @brief Hook/unhook
    * 
    * @param hooked If this hook should be installed/uninstalled (true/false)
    *
    * @returns If state is already the same as `hooked`
    */
    bool State(bool hooked) {
        if (hooked == m_bIsHooked) {
            return true;
        }
        if (m_bIsLocked) {
            return false;
        }
        Switch();
        return true;
    }

    void LockState(bool locked) {
        m_bIsLocked = locked;
    }

    /// Symbol in ImGui (On the left side of the checkbox)
    virtual const char* Symbol() const = 0;

    const auto& Name()   const { return m_fnName; }
    const auto  Type()   const { return m_type; }
    const auto  Hooked() const { return m_bIsHooked; }
    const auto  Locked() const { return m_bIsLocked; }

public:
    // ImGui stuff
    bool m_isVisible{true};

protected:
    bool        m_bIsHooked{};  // Is hook installed
    std::string m_fnName{};     // Name of function, eg.: `Add` (Referring to CEntity::Add)
    HookType    m_type{};
    bool        m_bIsLocked{};  // Is hook locked, i.e.: the hooked state can't be changed.
};
};
};
