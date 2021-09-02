#include "StdInc.h"

void List_c::InjectHooks()
{
    ReversibleHooks::Install("List_c", "AddItem", 0x4A8DF0, &List_c::AddItem);
    ReversibleHooks::Install("List_c", "RemoveItem", 0x4A8E30, &List_c::RemoveItem);
    ReversibleHooks::Install("List_c", "RemoveHead", 0x4A8E70, &List_c::RemoveHead);
    ReversibleHooks::Install("List_c", "RemoveTail", 0x4A8FD0, &List_c::RemoveTail);
    ReversibleHooks::Install("List_c", "RemoveAll", 0x4A8EB0, &List_c::RemoveAll);
    ReversibleHooks::Install("List_c", "InsertAfterItem", 0x4A8F10, &List_c::InsertAfterItem);
    ReversibleHooks::Install("List_c", "InsertBeforeItem", 0x4A8F70, &List_c::InsertBeforeItem);
    ReversibleHooks::Install("List_c", "GetNext", 0x4A8FF0, &List_c::GetNext);
    ReversibleHooks::Install("List_c", "GetPrev", 0x4A9000, &List_c::GetPrev);
    ReversibleHooks::Install("List_c", "GetNumItems", 0x4A8EC0, &List_c::GetNumItems);
    ReversibleHooks::Install("List_c", "GetItemOffset", 0x4A9010, &List_c::GetItemOffset);
}

// US-1.00 @ 0x004A8DF0
// EU-1.00 @ 0x004A8DF0
void List_c::AddItem(ListItem_c * pItem) {
    assert(pItem);
    auto* pOldHead = m_pHead;
    m_pHead = pItem;
    pItem->m_pPrev = nullptr;
    pItem->m_pNext = pOldHead;

    if (pOldHead)
        pOldHead->m_pPrev = pItem;
    else
        m_pTail = pItem;

    ++m_nCount;
}

// US-1.00 @ 0x004A8E30
// EU-1.00 @ 0x004A8E30
void List_c::RemoveItem(ListItem_c * pItem) {
    assert(pItem);

    if (pItem->m_pNext)
        pItem->m_pNext->m_pPrev = pItem->m_pPrev;
    else
        m_pTail = pItem->m_pPrev;

    if (pItem->m_pPrev)
        pItem->m_pPrev->m_pNext = pItem->m_pNext;
    else
        m_pHead = pItem->m_pNext;

    --m_nCount;
}

ListItem_c * List_c::GetHead() {
    return m_pHead;
}

ListItem_c* List_c::GetTail()
{
    return m_pTail;
}


// EU-1.00 @ 0x004A8E70
ListItem_c * List_c::RemoveHead(void) {
    //return plugin::CallMethodAndReturn<ListItem_c *, 0x004A8E70, List_c *>(this);
    if (!m_pHead)
        return nullptr;

    --m_nCount;
    auto* pOldHead = m_pHead;
    if (m_pHead == m_pTail)
    {
        m_pTail = nullptr;
        m_pHead = nullptr;
        return pOldHead;
    }

    if (m_pHead->m_pNext)
        m_pHead->m_pNext->m_pPrev = nullptr;

    m_pHead = m_pHead->m_pNext;
    return pOldHead;
}

ListItem_c* List_c::RemoveTail()
{
    if (!m_pTail)
        return nullptr;

    --m_nCount;
    auto* pOldTail = m_pTail;
    m_pTail->m_pPrev->m_pNext = nullptr;
    m_pTail = m_pTail->m_pPrev;
    return pOldTail;
}

void List_c::RemoveAll()
{
    m_pHead = nullptr;
    m_pTail = nullptr;
    m_nCount = 0;
}

uint32 List_c::GetNumItems()
{
    return m_nCount;
}

void List_c::AppendItem(ListItem_c* pItem)
{
    auto* pOldTail = m_pTail;
    m_pTail = pItem;
    pItem->m_pPrev = pOldTail;
    pItem->m_pNext = nullptr;

    if (pOldTail)
        pOldTail->m_pNext = pItem;
    else
        m_pHead = pItem;

    ++m_nCount;
}

void List_c::InsertAfterItem(ListItem_c* pAddedItem, ListItem_c* pExistingItem)
{
    ++m_nCount; //BUG: We increment count even though the item wasn't added to table, and there's no certainity that it will
    if (!m_pHead)
        return;

    auto pCurItem = GetHead();
    while (pCurItem && pCurItem != pExistingItem)
        pCurItem = GetNext(pCurItem);

    if (!pCurItem)
        return;

    pAddedItem->m_pPrev = pCurItem;
    pAddedItem->m_pNext = pCurItem->m_pNext;
    auto* pOldNext = pCurItem->m_pNext;
    pCurItem->m_pNext = pAddedItem;
    if (pOldNext)
        pOldNext->m_pPrev = pAddedItem;
    else
        m_pTail = pAddedItem;
}

void List_c::InsertBeforeItem(ListItem_c* pAddedItem, ListItem_c* pExistingItem)
{
    ++m_nCount; //BUG: We increment count even though the item wasn't added to table, and there's no certainity that it will
    if (!m_pHead)
        return;

    auto pCurItem = GetHead();
    while (pCurItem && pCurItem != pExistingItem)
        pCurItem = GetNext(pCurItem);

    if (!pCurItem)
        return;

    pAddedItem->m_pPrev = pCurItem->m_pPrev;
    pAddedItem->m_pNext = pCurItem;
    auto* pOldPrev = pCurItem->m_pPrev;
    pCurItem->m_pPrev = pAddedItem;
    if (pOldPrev)
        pOldPrev->m_pNext = pAddedItem;
    else
        m_pHead = pAddedItem;
}

ListItem_c * List_c::GetNext(ListItem_c * pItem) {
    assert(pItem);
    return pItem->m_pNext;
}

// US-1.00 @ 0x004A9000
// EU-1.00 @ 0x004A9000
ListItem_c * List_c::GetPrev(ListItem_c * pItem) {
    assert(pItem);
    return pItem->m_pPrev;
}

// US-1.00 @ 0x004A9010
// EU-1.00 @ 0x004A9010
ListItem_c * List_c::GetItemOffset(bool bFromHead, int32 iOffset) {
    if (bFromHead)
    {
        auto* result = GetHead();
        if (iOffset > 0 && result)
        {
            int32_t iCounter = 0;
            while (iCounter < iOffset && result)
            {
                ++iCounter;
                result = GetNext(result);
            }
        }
        return result;
    }
    else
    {
        auto* result = GetTail();
        if (iOffset > 0 && result)
        {
            int32_t iCounter = 0;
            while (iCounter < iOffset && result)
            {
                ++iCounter;
                result = GetPrev(result);
            }
        }
        return result;
    }
}
