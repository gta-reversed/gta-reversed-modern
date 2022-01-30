#pragma once

#include <string_view>
#include <ranges>

static bool findStringCaseInsensitive(std::string_view haystack, std::string_view needle) {
    return !std::ranges::search(haystack, needle, {}, std::toupper, std::toupper).empty();
}
