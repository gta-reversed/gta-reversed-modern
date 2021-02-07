/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "ListItem_c.h"

/**
 * Double linked list base implemantation
 * 
 * NOTE: You should not use this class directly, use TList_c template instead.
 */
class List_c
{
public:
    List_c() : m_pHead(nullptr), m_pTail(nullptr), m_nCount(0) {}
    ~List_c() {}

public:
    ListItem_c* m_pHead;
    ListItem_c* m_pTail;
    uint32_t m_nCount;

public:
    static void InjectHooks();

    // Add new item to the head
    void AddItem(ListItem_c* pItem);

    // Remove given item from the list and decrease counter
    void RemoveItem(ListItem_c* pItem);

    // Remove heading item and return it's pointer
    ListItem_c* RemoveHead();

    // Remove tail item and return it's pointer
    ListItem_c* RemoveTail();

    // Remove all items
    void RemoveAll();

    // Get number of items in the list
    uint32_t GetNumItems();

    // Append item to the list
    void AppendItem(ListItem_c* pItem);

    // Append item to the list
    void InsertAfterItem(ListItem_c* pAddedItem, ListItem_c* pExistingItem);

    // Append item to the list
    void InsertBeforeItem(ListItem_c* pAddedItem, ListItem_c* pExistingItem);

    // Get list head
    ListItem_c* GetHead();

    // Get list head
    ListItem_c* GetTail();

    // Get next item in a list
    ListItem_c* GetNext(ListItem_c* pItem);

    // Get previous item
    ListItem_c* GetPrev(ListItem_c* pItem);

    // Get N-th item from list head/tail
    ListItem_c* GetItemOffset(bool bFromHead, int iOffset);
};


/**
 * Double linked list template wrapper
 * (not an original game class name)
 */
template <
    typename ItemType
>
class TList_c : public List_c
{
public:
    ItemType* GetHead()
    {
        return static_cast<ItemType*>(List_c::GetHead());
    }

    ItemType* GetTail()
    {
        return static_cast<ItemType*>(List_c::GetTail());
    }

    ItemType* RemoveHead()
    {
        return static_cast<ItemType*>(List_c::RemoveHead());
    }

    ItemType* RemoveTail()
    {
        return static_cast<ItemType*>(List_c::RemoveTail());
    }

    ItemType* GetNext(ItemType* pItem)
    {
        return static_cast<ItemType*>(List_c::GetNext(pItem));
    }

    ItemType* GetPrev(ItemType* pItem)
    {
        return static_cast<ItemType*>(List_c::GetPrev(pItem));
    }

    ItemType* GetItemOffset(bool bFromHead, int iOffset)
    {
        return static_cast<ItemType*>(List_c::GetItemOffset(bFromHead, iOffset));
    }
};


VALIDATE_SIZE(List_c, 0xC);
