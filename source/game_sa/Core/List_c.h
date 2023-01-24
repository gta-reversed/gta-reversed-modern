/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "ListItem_c.h"

/**
 * Double linked list base implementation
 *
 * NOTE: You should not use this class directly, use TList_c template instead.
 */
class List_c {
public:
    List_c() : m_pHead(nullptr), m_pTail(nullptr), m_nCount(0) {}
    ~List_c() = default;

public:
    ListItem_c* m_pHead;
    ListItem_c* m_pTail;
    uint32      m_nCount;

public:
    static void InjectHooks();

    // Add new item to the head
    void AddItem(ListItem_c* item);

    // Remove given item from the list and decrease counter
    void RemoveItem(ListItem_c* item);

    // Remove heading item and return it's pointer
    ListItem_c* RemoveHead();

    // Remove tail item and return it's pointer
    ListItem_c* RemoveTail();

    // Remove all items
    void RemoveAll();

    // Get number of items in the list
    uint32 GetNumItems() const;

    // Append item to the list
    void AppendItem(ListItem_c* item);

    // Append item to the list
    void InsertAfterItem(ListItem_c* addedItem, ListItem_c* pExistingItem);

    // Append item to the list
    void InsertBeforeItem(ListItem_c* addedItem, ListItem_c* pExistingItem);

    // Get list head
    ListItem_c* GetHead();

    // Get list head
    ListItem_c* GetTail();

    // Get next item in a list
    ListItem_c* GetNext(ListItem_c* item);

    // Get previous item
    ListItem_c* GetPrev(ListItem_c* item);

    // Get N-th item from list head/tail
    ListItem_c* GetItemOffset(bool bFromHead, int32 iOffset);
};

namespace notsa {
namespace detail {
template<typename Y>
struct TList_Iterator {
    using self_type = TList_Iterator<Y>;

    using value_type        = Y;
    using reference         = Y&;
    using pointer           = Y*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = ptrdiff_t;

    TList_Iterator(ListItem_c* curr) :
        m_curr{ curr }
    {
    }

    self_type& operator++()    { m_curr = m_curr->m_pNext; return *this; } // ++i
    self_type  operator++(int) { self_type pre = *this; operator++(); return pre; } // i++

    self_type& operator--()    { m_curr = m_curr->m_pPrev; return *this; } // --i
    self_type  operator--(int) { self_type pre = *this; operator--(); return pre; } // i--

    reference operator*()  { return static_cast<reference>(*m_curr); }
    pointer   operator->() { return static_cast<pointer>(m_curr); }

    template<typename I1, typename I2>
    friend bool operator==(TList_Iterator<I1> lhs, TList_Iterator<I2> rhs) { return lhs.m_curr == rhs.m_curr; }

    //template<typename I1, typename I2>
    //friend bool operator!=(Iterator<I1> lhs, Iterator<I2> rhs) { return !(lhs == rhs); }
private:
    ListItem_c* m_curr;
};
};
};

/**
 * Double linked list template wrapper
 * (not an original game class name)
 */
template <typename T>
class TList_c : public List_c {
public:
    auto begin() { return IterAt(List_c::GetHead()); }
    auto end()   { return IterAt(nullptr); }

    // TODO: const iter

    T* GetHead() {
        return static_cast<T*>(List_c::GetHead());
    }

    T* GetTail() {
        return static_cast<T*>(List_c::GetTail());
    }

    T* RemoveHead() {
        return static_cast<T*>(List_c::RemoveHead());
    }

    T* RemoveTail() {
        return static_cast<T*>(List_c::RemoveTail());
    }

    T* GetNext(T* item) {
        return static_cast<T*>(List_c::GetNext(item));
    }

    T* GetPrev(T* item) {
        return static_cast<T*>(List_c::GetPrev(item));
    }

    T* GetItemOffset(bool bFromHead, int32 iOffset) {
        return static_cast<T*>(List_c::GetItemOffset(bFromHead, iOffset));
    }

private:
    auto IterAt(ListItem_c* at) { return notsa::detail::TList_Iterator<T>{ at }; }
};

VALIDATE_SIZE(List_c, 0xC);
