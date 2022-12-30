#pragma once

#include <utility>
#include "StoreArg.hpp"
#include "ReadArg.hpp"
#include "RunningScript.h"

class CRunningScript;

namespace notsa {
namespace script {
namespace detail {
template<typename T_FnRet, typename... T_FnArgs, typename... T_CollectedArgs>
inline OpcodeResult CollectArgsAndCall(CRunningScript* S, eScriptCommands command, T_FnRet(*CommandFn)(T_FnArgs...), T_CollectedArgs&&... args) {
    if constexpr (sizeof...(T_CollectedArgs) == sizeof...(T_FnArgs)) { // Has it collected enough args?
        const auto CallCommandFn = [&]() -> T_FnRet {
            return std::invoke(CommandFn, std::forward<T_CollectedArgs>(args)...);
        };

        if constexpr (std::is_same_v<T_FnRet, void>) {
            CallCommandFn(); // Returns void, nothing to push
        } else {
            T_FnRet ret = CallCommandFn();
            if constexpr (std::is_same_v<T_FnRet, OpcodeResult>) { 
                return ret;
            } else {
                StoreArg(S, std::forward<T_FnRet>(ret)); // Store result to script
            }
        }

        return OR_CONTINUE;
    } else { // Not enough args, read more
        using T_ToRead = nth_element_t<sizeof...(T_CollectedArgs), T_FnArgs...>;
        const auto ContinueWithArg = [&]<typename T>(T&& arg) {
            return CollectArgsAndCall(
                S,
                command,
                CommandFn,
                std::forward<T_CollectedArgs>(args)...,
                std::forward<T>(arg)
            );
        };

        if constexpr (std::is_same_v<T_ToRead, eScriptCommands>) { // Special case for reading the current script comamnd
            return ContinueWithArg(command);
        } else {
            return ContinueWithArg(notsa::script::Read<T_ToRead>(S)); // Read next parameter and continue
        }
    
        // Don't remove this, we might need it!
        //try {
        //} catch (const std::exception&) {
            // In cases the argument parser has errored out we still
            // have to read all values before returning.
            // Reason: The IP has to be increased
            //((void)(notsa::script::Read<T_FnArgs>(S)), ...);
            //return OR_CONTINUE;
        //}
    }
}

//! Called from unimplemented commands
//! This originally returned `OR_INTERRUPT`, but it isn't handled specially at all, so I'd just pass our debug checks
inline auto NotImplemented() { NOTSA_UNREACHABLE(); return OR_INTERRUPT; }
template<eScriptCommands Command, auto* CommandFn>
inline OpcodeResult CommandParser(CRunningScript* S) {
    return detail::CollectArgsAndCall(S, Command, CommandFn);
}

template<eScriptCommands Command, auto* CommandFn>
inline void AddCommandHandler() {
    auto& entry = CRunningScript::CustomCommandHandlerOf(Command);
    assert(!entry); // Make sure it doesn't already have a handler
    entry = &CommandParser<Command, CommandFn>; // Register handler
}
}; // namespace detail
}; // namespace script
}; // namespace notsa

template<eScriptCommands Command>
struct CommandHandler : std::false_type {};

namespace notsa {
namespace detail {
//! Returns raw function pointer of a function or lambda.
//! The `+` operator is a hack to get lambda's function pointer.
//! The `+` is a no-op in this case (As in, it won't increment the value, or anything like that, is just merely forces a decay to a pointer [from a lambda object instance])
//! See: https://stackoverflow.com/questions/18889028
template<typename T>
constexpr inline auto AddressOfFunction(T fn) {
    return +(fn);
}
};
};

//! Register a custom command handler
#define REGISTER_COMMAND_HANDLER(cmd, fn) \
    ::notsa::script::detail::AddCommandHandler<cmd, ::notsa::detail::AddressOfFunction(fn)>()

//! Register a command handler for an unimplemented command (That is, a command that wasn't implemented in the game either)
#define REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(cmd) \
    REGISTER_COMMAND_HANDLER(cmd, ::notsa::script::detail::NotImplemented)
