#pragma once

#include <string_view>
#include <ranges>

static bool findStringCaseInsensitive(std::string_view haystack, std::string_view needle) {
    return !std::ranges::search(haystack, needle, {}, std::toupper, std::toupper).empty();
}

// https://stackoverflow.com/a/48403210
// Maybe get rid of this in C++23 :D
static auto SplitStringView(std::string_view str, std::string_view delim) {
    return str
        | std::ranges::views::split(delim)
        | std::ranges::views::transform([](auto&& rng) {
            return std::string_view(&*rng.begin(), std::ranges::distance(rng));
        });
}

