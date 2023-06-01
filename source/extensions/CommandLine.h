#pragma once
#include <vector>
#include <string_view>

namespace CommandLine {
    // Hook features
    extern bool unhookAll;
    extern std::vector<std::string_view> unhookSome;
    extern std::vector<std::string_view> unhookExcept;

    // Debug features
    extern bool waitForDebugger;

    void Load(int argc, char** argv);
} // namespace CommandLine;
