#pragma once

#include <extensions/container.hpp>

// Returns a random value from the container
template<Container T>
auto random(const T& container) {
    auto it = container.cbegin();
    unsigned random = rand() % container.size();
    std::advance(it, random);
    return *it;
}
