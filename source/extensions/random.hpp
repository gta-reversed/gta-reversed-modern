#pragma once

#include <ranges>
#include <random>

namespace notsa {
namespace rng = std::ranges;

// Returns random iterator from range
template<rng::forward_range R>
auto random_iter(R&& range) {
    static std::default_random_engine reng{ std::random_device{}() };
    std::uniform_int_distribution<size_t> unidist{ 0, rng::size(range) };
    return std::next(range.begin(), unidist(reng));
}

// Returns random item(value) from range
auto&& random_value(auto&& range) {
    return *random_iter(range);
}

}; // namespace notsa
