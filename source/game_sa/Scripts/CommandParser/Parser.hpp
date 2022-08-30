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
void CollectArgsAndCall(CRunningScript* S, T_FnRet(*CommandFn)(T_FnArgs...), T_CollectedArgs&&... args) {
    if constexpr (sizeof...(T_CollectedArgs) == sizeof...(T_FnArgs)) { // Has it collected enough args?
        const auto CallCommandFn = [&] {
            return std::invoke(CommandFn, std::forward<T_CollectedArgs>(args)...);
        };
        if constexpr (std::is_same_v<T_FnRet, void>) {
            CallCommandFn(); // Returns void, nothing to push
        } else {
            ::notsa::script::StoreArg(S, CallCommandFn()); // Push result to script
        }
    } else {
        using namespace notsa;
        // Not enough args, collect more.
        CollectArgsAndCall(
            S,
            CommandFn,
            std::forward<T_CollectedArgs>(args)..., // Forward read ones
            script::Read<nth_element_t<sizeof...(T_CollectedArgs), T_FnArgs...>>(S) // Read next parameter
        ); 
    }
}
}; // namespace detail

template<eScriptCommands Command, auto* CommandFn>
OpcodeResult CommandParser(CRunningScript* S) {
    detail::CollectArgsAndCall(S, CommandFn);
    return OR_CONTINUE;
}

};
};

/*!
* Use this macro to register a parsed function
*/
#define REGISTER_PARSED_COMMAND(cmd, fn) \
    template<> \
    OpcodeResult CRunningScript::ProcessCommand<cmd>() { \
        return notsa::script::CommandParser<cmd, fn>(this); \
    } \
