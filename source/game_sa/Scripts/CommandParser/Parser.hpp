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
OpcodeResult CollectArgsAndCall(CRunningScript* S, T_FnRet(*CommandFn)(T_FnArgs...), T_CollectedArgs&&... args) {
    if constexpr (sizeof...(T_CollectedArgs) == sizeof...(T_FnArgs)) { // Has it collected enough args?
        const auto CallCommandFn = [&] {
            return std::invoke(CommandFn, std::forward<T_CollectedArgs>(args)...);
        };
        if constexpr (std::is_same_v<T_FnRet, void>) {
            CallCommandFn(); // Returns void, nothing to push
        } else {
            const auto ret = CallCommandFn(); 
            if constexpr (std::is_same_v<T_FnRet, OpcodeResult>) { // Special handling for OpcodeResult's, hopefully soon to be removed (once all commands start using the parser)
                return ret;
            } else {
                StoreArg(S, ret); // Store result to script
            }
        }
        return OR_CONTINUE;
    } else {
        // Not enough args, collect more.
        return CollectArgsAndCall(
            S,
            CommandFn,
            std::forward<T_CollectedArgs>(args)..., // Forward read ones
            notsa::script::Read<nth_element_t<sizeof...(T_CollectedArgs), T_FnArgs...>>(S) // Read next parameter
        ); 
    }
}
}; // namespace detail

template<eScriptCommands Command, auto* CommandFn>
OpcodeResult CommandParser(CRunningScript* S) {
    return detail::CollectArgsAndCall(S, CommandFn);
}

};
};

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

/*!
* Use this macro to register a parsed function
*/
#define REGISTER_COMMAND_HANDLER(cmd, fn) \
    template<> \
    struct CommandHandler<cmd> : std::true_type { \
        constexpr static auto Command  = cmd; \
        constexpr static auto Function = notsa::detail::AddressOfFunction(fn); \
    } \
