#include "StdInc.h"
#include "CommandLine.h"

#include <span>
#include <Utility.h>
#include <app_debug.h>

namespace CommandLine {
    bool unhookAll{false};
    std::vector<std::string_view> unhookSome{};
    std::vector<std::string_view> unhookExcept{};

    bool waitForDebugger{false};

    void ProcessArgument(const char* arg) {
        const auto str = std::string_view{arg, std::strlen(arg)};

        if (str == "--debug") {
            waitForDebugger = true;
            return;
        }

        if (str == "--unhook-all") {
            if (!unhookExcept.empty()) {
                NOTSA_LOG_WARN("--unhook-except has been called previously, unhook-all will be effective.");
                unhookExcept.clear(); // we aren't gonna use it.
            }
            if (!unhookSome.empty()) {
                NOTSA_LOG_WARN("--unhook-some has been called previously, unhook-all will be effective.");
                unhookSome.clear(); // we aren't gonna use it.
            }
            unhookAll = true;
            return;
        }

        if (str.starts_with("--unhook-except=")) {
            if (unhookAll) {
                NOTSA_LOG_WARN("--unhook-all has been called previously, unhook-all will be effective.");
            } else {
                if (!unhookSome.empty()) {
                    NOTSA_LOG_WARN("--unhook has been called previously, unhook-except will be effective.");
                    unhookSome.clear(); // we aren't gonna use it.
                }

                for (auto hook : SplitStringView(str.substr(str.find('=') + 1), ",")) {
                    unhookExcept.emplace_back(std::move(hook));
                }
            }
            return;
        }

        if (str.starts_with("--unhook=")) {
            if (unhookAll) {
                NOTSA_LOG_WARN("--unhook-all has been called previously, unhook-all will be effective.");
            } else if (!unhookExcept.empty()) {
                NOTSA_LOG_WARN("--unhook-except has been called previously, unhook-except will be effective.");
            } else {
                for (auto hook : SplitStringView(str.substr(str.find('=') + 1), ",")) {
                    unhookSome.emplace_back(std::move(hook));
                }
            }
            return;
        }

        NOTSA_LOG_WARN("Unknown argument '{}'", str);
    }

    void CommandLine::Load(int argc, char** argv) {
        if (--argc <= 0)
            return; // No need to process, there is no argument supplied.
        ++argv;     // Skip first 'argument' which is the exec path.

        for (auto& arg : std::span{argv, (size_t)argc})
            ProcessArgument(arg);
    }
} // namespace CommandLine
