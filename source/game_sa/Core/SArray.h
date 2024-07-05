/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

template <typename T>
struct SArray /* : public std::vector<T> */ {
    /* allocator<_Ty>*/ void* allocator{}; // MSVC 6.0 STL vector
    /* iterator      */ T*    _First{};    // ptr to array
    /* iterator      */ T*    _Last{};     // ptr to past the last active element
    /* iterator      */ T*    _End{};      // ptr to end of array
public:
    SArray() = default;
    SArray(SArray const&) {}
    ~SArray() = default;

    void operator=(SArray const&) {}

    auto size() const { return _First ? (size_t)(_Last - _First) : 0u; }
    auto begin() const { return _First; }
    auto end() const { return _Last; }
    auto empty() const { return size() == 0; }
    auto front() const { return *_First; }
    auto back() const { return *(_Last - 1); }

    void erase(T* iter) {
        assert(iter >= _First && iter < _Last);
        std::destroy_at(iter);
        rng::shift_left(iter + 1, _Last, 1);
        _Last--;
    }
};
VALIDATE_SIZE(SArray<int32>, 0x10);
