#pragma once

namespace notsa {

/*!
* @brief Call the given function on object destruction.
*/
template<typename Fn>
struct AutoCallOnDestruct {
    AutoCallOnDestruct(Fn&& fn) :
        m_fn{std::move(fn)}
    {
    }

    ~AutoCallOnDestruct() {
        m_fn();
    }

private:
    Fn m_fn;
};
};
