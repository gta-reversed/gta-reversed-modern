#include "StdInc.h"

#include "List_c.h"

void List_c::InjectHooks() {
    RH_ScopedClass(List_c);
    RH_ScopedCategory("Core");

    RH_ScopedInstall(AddItem, 0x4A8DF0);
    RH_ScopedInstall(RemoveItem, 0x4A8E30);
    RH_ScopedInstall(RemoveHead, 0x4A8E70);
    RH_ScopedInstall(RemoveTail, 0x4A8FD0);
    RH_ScopedInstall(RemoveAll, 0x4A8EB0);
    RH_ScopedInstall(InsertAfterItem, 0x4A8F10);
    RH_ScopedInstall(InsertBeforeItem, 0x4A8F70);
    RH_ScopedInstall(GetNext, 0x4A8FF0);
    RH_ScopedInstall(GetPrev, 0x4A9000);
    RH_ScopedInstall(GetNumItems, 0x4A8EC0);
    RH_ScopedInstall(GetItemOffset, 0x4A9010);
}

// 0x4A8DF0
void List_c::AddItem(ListItem_c* item) {
    assert(item);
    auto* pOldHead = m_pHead;
    m_pHead = item;
    item->m_pPrev = nullptr;
    item->m_pNext = pOldHead;

    if (pOldHead)
        pOldHead->m_pPrev = item;
    else
        m_pTail = item;

    ++m_nCount;
}

// 0x4A8E30
void List_c::RemoveItem(ListItem_c* item) {
    assert(item);

    if (item->m_pNext)
        item->m_pNext->m_pPrev = item->m_pPrev;
    else
        m_pTail = item->m_pPrev;

    if (item->m_pPrev)
        item->m_pPrev->m_pNext = item->m_pNext;
    else
        m_pHead = item->m_pNext;

    --m_nCount;
}

ListItem_c* List_c::GetHead() {
    return m_pHead;
}

ListItem_c* List_c::GetTail() {
    return m_pTail;
}

// 0x4A8E70
ListItem_c* List_c::RemoveHead() {
    // return plugin::CallMethodAndReturn<ListItem_c *, 0x004A8E70, List_c *>(this);
    if (!m_pHead)
        return nullptr;

    --m_nCount;
    auto* pOldHead = m_pHead;
    if (m_pHead == m_pTail) {
        m_pTail = nullptr;
        m_pHead = nullptr;
        return pOldHead;
    }

    if (m_pHead->m_pNext)
        m_pHead->m_pNext->m_pPrev = nullptr;

    m_pHead = m_pHead->m_pNext;
    return pOldHead;
}

ListItem_c* List_c::RemoveTail() {
    if (!m_pTail)
        return nullptr;

    --m_nCount;
    auto* pOldTail = m_pTail;
    m_pTail->m_pPrev->m_pNext = nullptr;
    m_pTail = m_pTail->m_pPrev;
    return pOldTail;
}

void List_c::RemoveAll() {
    m_pHead = nullptr;
    m_pTail = nullptr;
    m_nCount = 0;
}

uint32 List_c::GetNumItems() const {
    return m_nCount;
}

void List_c::AppendItem(ListItem_c* item) {
    auto* pOldTail = m_pTail;
    m_pTail = item;
    item->m_pPrev = pOldTail;
    item->m_pNext = nullptr;

    if (pOldTail)
        pOldTail->m_pNext = item;
    else
        m_pHead = item;

    ++m_nCount;
}

void List_c::InsertAfterItem(ListItem_c* addedItem, ListItem_c* pExistingItem) {
    ++m_nCount; // BUG: We increment count even though the item wasn't added to table, and there's no certainity that it will
    if (!m_pHead)
        return;

    auto curItem = GetHead();
    while (curItem && curItem != pExistingItem)
        curItem = GetNext(curItem);

    if (!curItem)
        return;

    addedItem->m_pPrev = curItem;
    addedItem->m_pNext = curItem->m_pNext;
    auto* pOldNext = curItem->m_pNext;
    curItem->m_pNext = addedItem;
    if (pOldNext)
        pOldNext->m_pPrev = addedItem;
    else
        m_pTail = addedItem;
}

void List_c::InsertBeforeItem(ListItem_c* addedItem, ListItem_c* pExistingItem) {
    ++m_nCount; // BUG: We increment count even though the item wasn't added to table, and there's no certainity that it will
    if (!m_pHead)
        return;

    auto curItem = GetHead();
    while (curItem && curItem != pExistingItem)
        curItem = GetNext(curItem);

    if (!curItem)
        return;

    addedItem->m_pPrev = curItem->m_pPrev;
    addedItem->m_pNext = curItem;
    auto* oldPrev = curItem->m_pPrev;
    curItem->m_pPrev = addedItem;
    if (oldPrev)
        oldPrev->m_pNext = addedItem;
    else
        m_pHead = addedItem;
}

ListItem_c* List_c::GetNext(ListItem_c* item) {
    assert(item);
    return item->m_pNext;
}

// 0x4A9000
ListItem_c* List_c::GetPrev(ListItem_c* item) {
    assert(item);
    return item->m_pPrev;
}

// 0x4A9010
ListItem_c* List_c::GetItemOffset(bool bFromHead, int32 iOffset) {
    if (bFromHead) {
        auto* result = GetHead();
        if (iOffset > 0 && result) {
            int32 iCounter = 0;
            while (iCounter < iOffset && result) {
                ++iCounter;
                result = GetNext(result);
            }
        }
        return result;
    } else {
        auto* result = GetTail();
        if (iOffset > 0 && result) {
            int32 iCounter = 0;
            while (iCounter < iOffset && result) {
                ++iCounter;
                result = GetPrev(result);
            }
        }
        return result;
    }
}
