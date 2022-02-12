#pragma once

#include <string_view>
#include <ranges>

// Always returns `true` if either strings are empty (This matches the behaviour of `haystack.find(needle) != npos`)
static bool StringContainsString(std::string_view haystack, std::string_view needle, bool caseSensitive = true) {
    if (caseSensitive) {
        return haystack.find(needle) != std::string_view::npos;
    }
    if (haystack.empty() || needle.empty()) {
        return true;
    }
    return !std::ranges::search(haystack, needle, {}, std::toupper, std::toupper).empty();
}

// https://stackoverflow.com/a/48403210
// Maybe get rid of this in C++23 :D
static auto SplitStringView(std::string_view str, std::string_view delim) {
    return str
        | std::ranges::views::split(delim)
        | std::ranges::views::transform([](auto&& rng) {
            return std::string_view(rng.begin(), rng.end());
        });
}

