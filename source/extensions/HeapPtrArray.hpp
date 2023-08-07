#pragma once
#include <memory>
#include <vector>

// Dynamic array that frees all pointers on destruction.
//
// TODO: Make sure all instances of this to use new/delete
// allocators and remove the `UseCFree` flag.
template<typename T, bool UseCFree = false>
class HeapPtrArray : public std::vector<T*> {
    HeapPtrArray() = default;
    ~HeapPtrArray() {
        for (auto& ptr : *this) {
            if constexpr (!UseCFree) {
                delete ptr;
            } else {
                free(ptr);
            }
        }
    }
};
