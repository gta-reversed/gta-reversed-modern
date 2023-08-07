#pragma once
#include <memory>
#include <vector>

// Dynamic array that frees all pointers on destruction.
// 
// TODO: Make sure all instances of this to use new/delete
// allocators and remove the `UseCFree` flag.
template<typename T, bool UseCFree = false>
class HeapPtrArray {
    std::vector<T*> m_elements;
public:
    HeapPtrArray() = default;
    ~HeapPtrArray() {
        for (auto& ptr : m_elements) {
            if constexpr (!UseCFree) {
                delete ptr;
            } else {
                free(ptr);
            }
        }
    }

    auto& vector() { return m_elements; }
    const auto& vector() const { return m_elements; }

    // std::vector-like member funcs
    size_t size() const noexcept {
        return m_elements.size();
    }

    void push_back(T* ptr) {
        m_elements.push_back(ptr);
    }

    auto begin() { return m_elements.begin(); }
    const auto begin() const { return m_elements.begin(); }

    auto end() { return m_elements.end(); }
    const auto end() const { return m_elements.end(); }
};
