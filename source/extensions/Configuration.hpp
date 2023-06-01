#pragma once
#include <string>
#include <optional>
#include <unordered_map>
#include <fstream>

#include "app_debug.h"

static inline class {
    using IniContent = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;
    IniContent m_content{};

public:
    template <typename Ret = std::string>
    std::optional<Ret> GetIniValue(const std::string& section, const std::string& key) {
        if (m_content.empty() || !m_content.contains(section) || !m_content[section].contains(key))
            return {};

        const auto& str = m_content[section][key];
        if constexpr (std::is_same_v<Ret, std::string>) {
            return str;
        } else if constexpr (std::is_same_v<Ret, bool>) {
            return str == "true" || str == "TRUE" || str == "1";
        } else if constexpr (notsa::is_standard_integer<Ret> || std::is_floating_point_v<Ret>) {
            Ret rt{};

            auto [_, ec] = std::from_chars(str.data(), str.data() + str.size(), rt);
            if (ec != std::errc{})
                return {};

            return rt;
        } else {
            return {};
        }
    }

    template <typename T>
    void SetIniValue(const std::string& section, const std::string& key, const T& value) {
        auto& ct = m_content[section][key];

        if constexpr (std::is_same_v<T, std::string>) {
            ct = value;
        } else if constexpr (std::is_same_v<T, bool>) {
            ct = value ? "true" : "false";
        } else if constexpr (notsa::is_standard_integer<T> || std::is_floating_point_v<T>) {
            ct = std::to_string(value);
        } else {
            ct = std::string{value}; // not sure about that.
        }
    }

    void Load(const std::string& fileName) {
        ParseIniFile(std::ifstream{fileName}, m_content);
    }

    void Save(const std::string& fileName) {
        std::ofstream out{fileName};
        for (auto&& [section, keys] : m_content) {
            // We consider section == "" as the root.
            if (section != "")
                out << "[" << section << "]" << std::endl;

            for (auto&& [key, value] : keys) {
                out << key << "=" << value << std::endl;
            }
            out << std::endl;
        }
    }

private:
    static void ParseIniFile(std::ifstream file, IniContent& ini) {
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

#define GET_INI_CONFIG_VALUE(section, key_var, _default) \
	key_var = g_ConfigurationMgr.GetIniValue<decltype(key_var)>(section, #key_var).value_or(_default)

#define SAVE_INI_CONFIG_VALUE(section, key_var) \
	g_ConfigurationMgr.SetIniValue<decltype(key_var)>(section, #key_var, key_var);
