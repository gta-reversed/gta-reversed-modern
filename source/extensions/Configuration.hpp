#pragma once
#include <string>
#include <optional>
#include <unordered_map>
#include <fstream>
#include <filesystem>

#include "app_debug.h"

static inline class {
    using IniContent = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;
    IniContent m_content{};

    struct NewConfigFile {
        std::ofstream out;
        std::string lastSection;
    };
    std::optional<NewConfigFile> m_createdIniFile{};

public:
    template <typename Ret = std::string>
    Ret GetIniValue(const std::string& section, const std::string& key, Ret&& _default) {
        if (m_content.empty() || !m_content.contains(section) || !m_content[section].contains(key)) {
            if (m_createdIniFile.has_value()) {
                if (std::exchange(m_createdIniFile->lastSection, section) != section)
                    m_createdIniFile->out << "\n[" << section << "]\n";

               if constexpr (std::is_same_v<Ret, bool>)
                    m_createdIniFile->out << key << " = " << std::boolalpha << _default << "\n";
               else
                    m_createdIniFile->out << key << " = " << _default << "\n";
            }
            return _default;
        }

        const auto& str = m_content[section][key];
        if constexpr (std::is_same_v<Ret, std::string>) {
            return str;
        } else if constexpr (std::is_same_v<Ret, bool>) {
            return str == "true" || str == "TRUE" || str == "1";
        } else if constexpr (notsa::is_standard_integer<Ret> || std::is_floating_point_v<Ret>) {
            Ret rt{};

            auto [_, ec] = std::from_chars(str.data(), str.data() + str.size(), rt);
            if (ec != std::errc{})
                return _default;

            return rt;
        } else {
            return _default;
        }
    }

    void Load(const std::filesystem::path& fileName) {
        if (!std::filesystem::exists(fileName)) {
            DEV_LOG("Configuration file {} doesn't exist! A new one will be generated.", fileName.string());
            DEV_LOG("Using the provided config file with comments is recommended.");

            auto out = std::ofstream{fileName};
            out << "; GTA-Reversed configuration file generated at " << std::chrono::system_clock::now();
            m_createdIniFile = {std::move(out), ""};
            return;
        }

        std::ifstream in(fileName);
        assert(!in.bad());

        ParseIniFile(in, m_content);
    }

private:
    static void ParseIniFile(std::ifstream& file, IniContent& ini) {
        std::string sectionName{""};
        std::string line;
        while (std::getline(file, line)) {
            const auto StripText = [](std::string& s) {
                s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
                s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
            };

            if (const auto cf = line.find(';'); cf != std::string::npos) {
                line.erase(cf);
            }

            StripText(line);

            if (line.empty())
                continue;

            if (line.front() == '[' && line.back() == ']') {
                sectionName = line.substr(1, line.size() - 2);
                continue;
            }

            if (const auto ef = line.find('='); ef != std::string::npos) {
                auto key = line.substr(0, ef);
                auto value = line.substr(ef + 1);

                StripText(key);
                StripText(value);

                DEV_LOG("key: {} value: {}", key, value);
                ini[sectionName][std::move(key)] = std::move(value);
                continue;
            }

            DEV_LOG("err: something wrong!");
            break;
        }
    }
} g_ConfigurationMgr;

#define INI_CONFIG_SECTION(name) \
    static constexpr auto IniSectionName = name

#define GET_INI_CONFIG_VALUE(key, _default) \
	g_ConfigurationMgr.GetIniValue<decltype(_default)>(IniSectionName, key, _default)

#define STORE_INI_CONFIG_VALUE(key_var, _default) \
	key_var = g_ConfigurationMgr.GetIniValue<decltype(key_var)>(IniSectionName, #key_var, _default)
