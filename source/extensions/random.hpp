#pragma once

#include <ranges>
#include <random>

namespace notsa {
namespace rng = std::ranges;

// Returns random iterator from range - If empty the end iterator is returned.
template<rng::forward_range R>
auto random_iter(R&& range) {
    if (rng::empty(range)) { // If empty just return end iterator
        return rng::end(range);
    }

    static std::default_random_engine reng{ std::random_device{}() };
    std::uniform_int_distribution<size_t> unidist{ 0, rng::size(range) - 1 };
    return std::next(rng::begin(range), unidist(reng));
}

// Returns random item(value) from range
auto&& random_value(auto&& range) {
    return *random_iter(range);
}

}; // namespace notsa
