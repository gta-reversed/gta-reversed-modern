#pragma once

#include <utility>
#include <array>

#include "eScriptCommands.h"
#include "RunningScript.h"

namespace notsa {
namespace detail {
namespace script {
// We have to balance between recursion and index seq. size, because:
// - Fold op. by default has maxes out at 256 arg
// - contexpr recursion is limited to ~1000
// So we can't rely on using only 1 method, gotta use both at the same time
// In case we'd ever run into either the fold or recursion limit, this value can be changed.
constexpr auto FILL_LUT_CHUNK_SIZE = 128;

template<size_t base = 0, bool end = false, size_t lut_size, typename FnT, size_t... idx>
constexpr void FillLUT(std::array<FnT, lut_size>& lut, std::index_sequence<idx...>) {
    constexpr auto rem = lut_size - base;
    if constexpr (sizeof...(idx) > rem) {
        FillLUT<base, true>(lut, std::make_index_sequence<rem>{});
    }
    else {
        ((lut[base + idx] = &CRunningScript::ProcessCommand<(eScriptCommands)(base + idx)>), ...);

        if constexpr (!end) {
            FillLUT<base + FILL_LUT_CHUNK_SIZE>(lut, std::make_index_sequence<FILL_LUT_CHUNK_SIZE>{});
        }
    }
}

constexpr auto GenerateLUT() {
    //constexpr auto lut
    std::array<OpcodeResult(CRunningScript::*)(), (size_t)COMMAND_HIGHEST_ID> lut{};
    FillLUT(lut, std::make_index_sequence<FILL_LUT_CHUNK_SIZE>{});
    return lut;
}
}; // namespace notsa 
}; // namespace detail 
}; // namespace script
