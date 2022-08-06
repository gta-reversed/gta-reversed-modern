#pragma once

#include <ranges>
#include <random>
#include <algorithm>

namespace notsa {
namespace rng = std::ranges;

/*!
* @arg value The value to search for in the range
* 
* @brief Check if a range contains a value, uses `rng::find`. NOTE: If you plan on using the iterator, just use `rng::find` instead..
*/
template<rng::input_range R, class T, class Proj = std::identity>
    requires std::indirect_binary_predicate<rng::equal_to, std::projected<rng::iterator_t<R>, Proj>, const T*>
bool contains(R&& r, const T& value, Proj proj = {}) {
    return rng::find(r, value, proj) != r.end();
}

}; // namespace notsa
