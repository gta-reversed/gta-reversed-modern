#pragma once

#include <memory>
#include <initializer_list>

namespace notsa {
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
struct AutoCallOnDestruct {
    AutoCallOnDestruct(Fn fn) :
        m_fn{ std::move(fn) }
    {
    }

    ~AutoCallOnDestruct() {
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

template<rng::input_range R, typename T_Ptr = rng::range_value_t<R>>
    requires std::is_pointer_v<T_Ptr> 
auto SpatialQuery(R&& r, CVector distToPos, T_Ptr ignored, T_Ptr closest = nullptr) {
    const auto GetDistSq = [distToPos](T_Ptr e) {
        return (e->GetPosition() - distToPos).SquaredMagnitude();
    };

    float closestDistSq = closest ? GetDistSq(closest) : std::numeric_limits<float>::max();
    for (T_Ptr e : r) {
        if (ignored && e == ignored) {
            continue;
        }
        const auto distSq = GetDistSq(e);
        if (closestDistSq > distSq) {
            closestDistSq = distSq;
            closest       = e;
        }
    }

    struct Ret{ T_Ptr entity; float distSq; };
    return Ret{ closest, closestDistSq };
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

// Find first non-null value in range. If found it's returned, `null` otherwise.
template<rng::input_range R, typename T_Ptr = rng::range_value_t<R>>
    requires(std::is_pointer_v<T_Ptr>)
T_Ptr FirstNonNull(R&& range) {
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
template<rng::input_range R, class T, class Proj = std::identity>
    requires std::indirect_binary_predicate<rng::equal_to, std::projected<rng::iterator_t<R>, Proj>, const T*>
bool contains(R&& r, const T& value, Proj proj = {}) {
    return rng::find(r, value, proj) != rng::end(r);
}

/*!
* Helper (Of your fingers) - Reduces typing needed for Python style `value in {}`
*/
template<typename Y, typename T>
bool contains(std::initializer_list<Y> r, const T& value) {
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
    } else {
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


/*
//! Similar to `std::remove_if`, but only removes the first element found (Unlike the former that removes all)
template<rng::forward_range R, class Proj = std::identity, std::indirect_unary_predicate<std::projected<rng::iterator_t<R>, Proj>> Pr>
    requires std::permutable<rng::iterator_t<R>>
constexpr rng::borrowed_subrange_t<R> remove_first(R&& r, Pr pr, Proj proj = {}) {
    auto end = rng::end(r);
    auto it = rng::find_if(r, pr, proj);
    if (it != rng::end(r)) {
        rng::move_backward(rng::next(it), end, it); // Shift to the left (removing the found element)
    }
    return { std::move(it), std::move(end) }; // Return 
}
*/  

//! `std::ranges` like `accumulate` function => Hopefully to be replaced by an `std` implementation.
template<rng::input_range R, typename T, typename FnOp = std::plus<>, class Proj = std::identity>
T accumulate(R&& r, T init, Proj proj = {}, FnOp op = {}) {
    for (const auto& v : r) {
        init = std::invoke(op, init, std::invoke(proj, v));
    }
    return init;
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
        IterateFunction<Start + ChunkSize, Stop>(functor);
    }
}

//! Simple (not thread safe) singleton class. Instance created on first call to `GetSingleton()`.
template<typename T>
class Singleton {
    static inline std::unique_ptr<T> s_instance{};
public:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    //! Get current singleton instance (Create it if none)
    static T& GetSingleton() {
        if (!s_instance) {
            CreateSingleton();
        }
        return *s_instance;
    }

    //! Destroy current instance and create new
    static void ResetSingleton() {
        DestroySingleton();
        CreateSingleton();
    }

private:
    static void CreateSingleton() {
        assert(!s_instance);
        s_instance = std::make_unique<T>();
    }

    static void DestroySingleton() {
        s_instance.reset();
    }
};

};
