#pragma once 

#include "Base.h"
#include "eScriptCommands.h"
#include "Scripts/CommandParser/LUTGenerator.hpp"

#ifdef ENABLE_SCRIPT_COMMAND_HOOKS
namespace ReversibleHooks {
namespace ReversibleHook {
template<eScriptCommands Command>
struct ScriptCommand : Base {
    ScriptCommand(bool locked = false, bool enabledByDefault = true) :
        Base{ std::string{::notsa::script::GetScriptCommandName(Command)}, Base::HookType::ScriptCommand, locked }
    {
        Switch(); // Install hook

        if (!enabledByDefault) {
            Switch(); // Uninstall
        }
    }
    ~ScriptCommand() override = default;

    void Switch() override {
        using namespace ::notsa::script;

        m_bIsHooked = !m_bIsHooked;
        CRunningScript::SetCommandHandler(
            Command,
            m_bIsHooked
                ? GetHandlerOfCommand<Command>() // When hooked use custom handler (Which might still fallback to the GTA handler in case we have no custom handler)
                : &GTAProcessCommand<Command>    // When unhooked use GTA handler
        );
    }

    void        Check() override { /* nop */ }
    const char* Symbol() const override { return "C"; }
};
};
};
#endif
