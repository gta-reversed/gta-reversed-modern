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

/**
 * Double linked list template wrapper
 * (not an original game class name)
 */
template <typename ItemType> class TList_c : public List_c {
public:
    ItemType* GetHead() {
        return static_cast<ItemType*>(List_c::GetHead());
    }

    ItemType* GetTail() {
        return static_cast<ItemType*>(List_c::GetTail());
    }

    ItemType* RemoveHead() {
        return static_cast<ItemType*>(List_c::RemoveHead());
    }

    ItemType* RemoveTail() {
        return static_cast<ItemType*>(List_c::RemoveTail());
    }

    ItemType* GetNext(ItemType* item) {
        return static_cast<ItemType*>(List_c::GetNext(item));
    }

    ItemType* GetPrev(ItemType* item) {
        return static_cast<ItemType*>(List_c::GetPrev(item));
    }

    ItemType* GetItemOffset(bool bFromHead, int32 iOffset) {
        return static_cast<ItemType*>(List_c::GetItemOffset(bFromHead, iOffset));
    }
};

VALIDATE_SIZE(List_c, 0xC);
