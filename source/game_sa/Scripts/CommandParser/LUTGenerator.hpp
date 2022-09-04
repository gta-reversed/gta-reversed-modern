#pragma once

#include <utility>
#include <array>

#include "Parser.hpp"
#include "eScriptCommands.h"
#include "RunningScript.h"

namespace notsa {
namespace script {
namespace detail {
// We have to balance between recursion and index seq. size, because:
// - Fold op. by default has maxes out at 256 arg
// - contexpr recursion is limited to ~1000
// So we can't rely on using only 1 method, gotta use both at the same time
// In case we'd ever run into either the fold or recursion limit, this value can be changed.
constexpr auto FILL_LUT_CHUNK_SIZE = 128;

/*!
* Wrap CRunningScript::ProcessCommand into a static function, instead of a member one.
*/
template<eScriptCommands Command>
static auto ProcessCommandMemFnWrapper(CRunningScript* S) {
    return std::invoke(&CRunningScript::ProcessCommand<Command>, S);
}

/*!
* Get the function for the command that is to the `CommandParser`
*/
template<eScriptCommands Command>
static constexpr auto GetFunctionForCommand() {
    // Check if there's a registered command handler
    using RegisteredCommandHandler = CommandHandler<Command>;
    if constexpr (RegisteredCommandHandler::value) {
        return &CommandParser<Command, RegisteredCommandHandler::Function>;
    } else { // Otherwise use base ProcessCommand, eventually (ideally) we'll get rid of these commands (by converting them to parsed commands instead)
        return &CommandParser<Command, ProcessCommandMemFnWrapper<Command>>;
    }
}

/*!
* Process one command to be inserted into the LUT
*/
template<eScriptCommands Command>
static constexpr void InsertCommandIntoLUT(auto& lut) {
    lut[(size_t)Command] = GetFunctionForCommand<Command>();
}

/*!
* Fill the LUT with command functions
*/
template<size_t Base = 0, bool StopRecursing = false, size_t LUTSize, typename T_Fn, size_t... Idx>
static constexpr void FillLUT(std::array<T_Fn, LUTSize>& lut, std::index_sequence<Idx...>) {
    constexpr auto rem = LUTSize - Base;
    if constexpr (sizeof...(Idx) > rem) {
        FillLUT<Base, true>(lut, std::make_index_sequence<rem>{});
    } else {
        (InsertCommandIntoLUT<(eScriptCommands)(Base + Idx)>(lut), ...);

        if constexpr (!StopRecursing) {
            FillLUT<Base + FILL_LUT_CHUNK_SIZE>(lut, std::make_index_sequence<FILL_LUT_CHUNK_SIZE>{});
        }
    }
}

static constexpr auto GenerateLUT() {
    // NOTE: Signature here has to be the same as `CommandParser`
    std::array<OpcodeResult(*)(CRunningScript*), (size_t)COMMAND_HIGHEST_ID> lut{};
    FillLUT(lut, std::make_index_sequence<FILL_LUT_CHUNK_SIZE>{});
    return lut;
}

}; // namespace detail 
}; // namespace script
}; // namespace notsa 
