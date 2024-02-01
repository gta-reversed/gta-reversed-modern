#pragma once

#include <charconv>
#include <initializer_list>
#include <Vector.h>
#include "Base.h"

namespace notsa {
//template<typename TChar, size_t N>
//struct basic_static_string {
//    template<typename YChar>
//    friend std::strong_ordering operator<=>(const basic_static_string<YChar>& self, std::basic_string_view<YChar> sv) {
//        sv.compare(std::basic_string_view<YChar>{m_chars});
//    }
//    
//private:
//    TChar m_chars[N]{};
//};
namespace rng = std::ranges;

template<rng::input_range R>
ptrdiff_t indexof(R&& r, const rng::range_value_t<R>& v, ptrdiff_t defaultIdx = -1) {
    const auto it = rng::find(r, v);
    return it != rng::end(r)
        ? rng::distance(rng::begin(r), it)
        : defaultIdx;
}

//! [mostly] Works like C#'s `??` (null coalescing operator) or GCC's `?:`
template<typename T>
T coalesce(T a, T b) {
    return a ? a : b;
}

/*!
* Much like std::stoi [and variants] but takes an `std::string_view` + in debug does error checking [unlike the C stuff]
* @param str   The string to convert
* @param radix The radix (base) of the number
* @param end   The end of the the number in the string (points to inside `sv`)
*/
template<std::integral T>
T ston(std::string_view str, int radix = 10, const char** end = nullptr) {
    T out;
    const auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), out, radix);
    assert(ec == std::errc{});
    if (end) {
        *end = ptr;
    }
    return out;
}

/*!
* Much like std::stof [and variants] but takes an `std::string_view` + in debug does error checking [unlike the C stuff]
* @param str   The string to convert
* @param fmt   The formatting mode
* @param end   The end of the the number in the string (points to inside `sv`)
*/
template<typename T>
    requires std::is_floating_point_v<T>
T ston(std::string_view str, std::chars_format fmt = std::chars_format::general, const char** end = nullptr) {
    T out;
    const auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), out, fmt);
    assert(ec != std::errc{});
    if (end) {
        *end = ptr;
    }
    return out;
}

/*
* Parse a string into a 3D vector. The format is `X Y Z` (There might be multiple spaces, they're ignored)
* [On failure asserts in debug]
*/
CVector stov3d(std::string_view str, std::chars_format fmt = std::chars_format::general) {
    CVector v3d;
    for (auto i = 0; i < 3; i++) {
        const char* end;
        v3d[i] = ston<float>(str, fmt, &end);
        if (i < 2) {
            str = str.substr(end - str.data() + 1);
        }
    }
    return v3d;
}

/*
* Want to know something funny?
* `std::initializer_list` is just a proxy object for a stack allocated array.
* So, if you return one from a function you're dommed to be fucked :)
* And best thing, it does allow copying, it has a fucking copy constructor for whatever reason
* Lesson: Don't return `initializer_list`'s from functions
*/

/*!
* @brief Call the given function on object destruction.
*/
template<typename Fn>
struct ScopeGuard {
    ScopeGuard(Fn fn) :
        m_fn{ std::move(fn) }
    {
    }

    ~ScopeGuard() {
        std::invoke(m_fn);
    }

private:
    Fn m_fn;
};

constexpr auto IsFixBugs() {
#ifdef FIX_BUGS
    return true;
#else
    return false;
#endif
}

/// Predicate to check if `value` is null
template<typename T>
    requires(std::is_pointer_v<T>)
bool IsNull(T value) { return value == nullptr; }

/// Negate another predicate function
template<typename T>
auto Not(bool(*fn)(T)) { return [fn](const T& value) { return !fn(value); }; }

struct NotIsNull {
    template<typename T>
    bool operator()(const T* ptr) {
        return ptr != nullptr;
    }
};

//! Find first non-null value in range. If found it's returned, `null` otherwise.
template<rng::input_range R, typename T_Ret = rng::range_value_t<R>>
    requires(std::is_pointer_v<T_Ret>)
T_Ret FirstNonNull(R&& range) {
    const auto it = rng::find_if(range, NotIsNull{});
    return it != rng::end(range)
        ? *it
        : nullptr;
}

// https://stackoverflow.com/a/52667105
template <typename T, std::size_t... Ds>
struct mdarray_impl;

template <typename T, std::size_t D>
struct mdarray_impl<T, D> {
    using type = std::array<T, D>;
};

template <typename T, std::size_t D, std::size_t... Ds>
struct mdarray_impl<T, D, Ds...> {
    using type = std::array<typename mdarray_impl<T, Ds...>::type, D>;
};

//! Multidimensional array - Represents a C array of with dimensions in the same order as specified here
template <typename T, std::size_t... Ds>
using mdarray = typename mdarray_impl<T, Ds...>::type;

/*!
* @arg value The value to search for in the range
*
* @brief Check if a range contains a value, uses `rng::find`. NOTE: If you plan on using the iterator, just use `rng::find` instead..
*/
template<rng::input_range R, class T = rng::range_value_t<R>, class Proj = std::identity>
    requires std::indirect_binary_predicate<rng::equal_to, std::projected<rng::iterator_t<R>, Proj>, const T*>
bool contains(R&& r, const T& value, Proj proj = {}) {
    return rng::find(r, value, proj) != rng::end(r);
}


/*!
* Helper (Of your fingers) - Reduces typing needed for Python style `value in {}`
*/
template<typename Y>
bool contains(std::initializer_list<Y> r, const Y& value) {
    return contains(r, value, {});
}

/*!
* @brief Similar to `std::remove_if`, but only removes the first element found (Unlike the former that removes all)
*
* @return Whenever an element was removed. If it was, you have to pop the last element from your container
*/
template <std::permutable I, std::sentinel_for<I> S, class T, class Proj = std::identity>
    requires std::indirect_binary_predicate<rng::equal_to, std::projected<I, Proj>, const T*>
constexpr bool remove_first(I first, S last, const T& value, Proj proj = {}) {
    first = rng::find(std::move(first), last, value, proj);
    if (first == last) {
        return false;
    }
    else {
        rng::move_backward(rng::next(first), last, std::prev(last)); // Shift to the left (removing the found element)
        return true;
    }
}

// We require `bidirectional_range`, because we have to use `std::prev`.
// if for any reason we want to use `forward_range` only, I guess we gotta figure
// out a different way of getting the pre-end iteartor

//! @copydoc `remove_first`
template <rng::bidirectional_range R, class T, class Proj = std::identity>
    requires std::permutable<rng::iterator_t<R>>&& std::indirect_binary_predicate<rng::equal_to, std::projected<rng::iterator_t<R>, Proj>, const T*>
constexpr bool remove_first(R&& r, const T& value, Proj proj = {}) {
    return remove_first(rng::begin(r), rng::end(r), value, std::move(proj));
}

//! `std::ranges` like `accumulate` function => Hopefully to be replaced by an `std` implementation.
template<rng::input_range R, typename T, typename FnOp = std::plus<>, class Proj = std::identity>
T accumulate(R&& r, T init, Proj proj = {}, FnOp op = {}) {
    for (const auto& v : r) {
        init = std::invoke(op, init, std::invoke(proj, v));
    }
    return init;
}

//! Same as rng::min, but accepts a default value that is returned in case the range is empty (Which would result be UB for `rng::min`)
template<rng::forward_range R, typename Pr = std::less<>, class Proj = std::identity>
constexpr rng::range_value_t<R> min_default(R&& r, rng::range_value_t<R> defaultValue, Pr pr = {}, Proj proj = {}) {
    if (rng::empty(r)) {
        return std::move(defaultValue);
    }
    return rng::min(r, pr, proj);
}

/*!
* @brief Helper functor - to be used as projection to `ranges` functions - to cast a value into another type.
*
* @tparam O - Type to cast to
*/
template<typename O>
struct cast_to {
    template<typename I>
    O operator()(I&& input) {
        return static_cast<O>(input);
    }
};


/*!
* @tparam Start     The number at which to start the iteration
* @tparam Stop      The number at which to stop the iteration
* @tparam ChunkSize The chunk size, see function description.
*
* @arg functor The functor instance that has a `operator()` with matching `template<size_t>`. Templated lambdas can be used.
*
* This function will iterate thru the sequence of numbers in range [Base, Stop), and
* call the functor's templated `operator()` with the index being the first template argument.
*
* @code{.cpp}
*   constexpr auto Bar = []<size_t Idx>(){
*       std::cout << Idx << ", ";
*   };
*   IterateFunction<0, 5>(Bar); // Prints: 0, 1, 2, 3, 4
* @endcode
*
* About the `ChunkSize` template parameter:
* We have to balance between recursion and index seq. size, because:
* - Fold op. by default maxes out at ~256 arguments (MSVC)
* - contexpr recursion is limited to ~1000 (MSVC)
* So we can't rely on using only 1 method, gotta use both at the same time
* In case you ever run into one of the limits:
* - Fold op. => Decrease `ChunkSize`
* - Recursion => Increase `ChunkSize`
*/
template<int Start, int Stop, int ChunkSize = 128>
static constexpr void IterateFunction(auto&& functor) {
    // Invoke function with current sequence
    [&] <std::size_t... Idx>(std::index_sequence<Idx...>) {
        (functor.template operator()<Start + Idx>(), ...);
    }(std::make_index_sequence<std::min(ChunkSize, Stop - Start)>{});

    // Continue recursing if there's anything left
    if constexpr (Stop - Start > ChunkSize) {
        IterateFunction<Start + ChunkSize, Stop, ChunkSize>(functor);
    }
}

template<typename T, typename... Ts>
concept is_any_of_type_v = (std::same_as<T, Ts> || ...);

//! Check if the type is an integer type excluding bool and character types.
template<typename T>
inline constexpr bool is_standard_integer = std::is_integral_v<T> && !is_any_of_type_v<T, bool, char, wchar_t, char8_t, char16_t, char32_t>;

// Find value in a range then return a pointer of it.
template<rng::input_range R, class T, class Proj = std::identity>
constexpr T* find_or_nullptr(R&& r, const T& value, Proj proj = {}) {
    const auto fnd = rng::find(r, value, proj);
    return fnd != r.end() ? &(*fnd) : nullptr;
}


// Find with a predicate in a range then return a pointer of it.
template<typename T, rng::input_range R, class Proj = std::identity,
    std::indirect_unary_predicate<std::projected<rng::iterator_t<R>, Proj>> Pred>
constexpr T* find_if_or_nullptr(R&& r, Pred pred, Proj proj = {}) {
    const auto fnd = rng::find_if(r, pred, proj);
    return fnd != r.end() ? (T*)&(*fnd) : nullptr;
}
};
