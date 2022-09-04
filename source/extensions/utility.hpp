#pragma once

namespace notsa {

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


/// Predicate to check if `value` is null
template<typename T>
    requires(std::is_pointer_v<T>)
bool IsNull(T value) { return value == nullptr; }

/// Negate another predicate function
template<typename T>
auto Not(bool(*fn)(T)) { return [fn](const T& value) { return !fn(value); }; }

};
