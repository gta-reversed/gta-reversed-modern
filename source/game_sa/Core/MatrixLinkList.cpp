#include "StdInc.h"

CMatrixLinkList& gMatrixList = *(CMatrixLinkList*)0xB74288;

void CMatrixLinkList::InjectHooks()
{
    Install("CMatrixLinkList", "Init", 0x54F0D0, &CMatrixLinkList::Init);
    Install("CMatrixLinkList", "Shutdown", 0x54E990, &CMatrixLinkList::Shutdown);
    Install("CMatrixLinkList", "AddToList1", 0x54E9D0, &CMatrixLinkList::AddToList1);
    Install("CMatrixLinkList", "AddToList2", 0x54EA10, &CMatrixLinkList::AddToList2);
    Install("CMatrixLinkList", "MoveToList1", 0x54EA60, &CMatrixLinkList::MoveToList1);
    Install("CMatrixLinkList", "MoveToList2", 0x54EA90, &CMatrixLinkList::MoveToList2);
    Install("CMatrixLinkList", "MoveToFreeList", 0x54EAD0, &CMatrixLinkList::MoveToFreeList);
    Install("CMatrixLinkList", "GetNumFree", 0x54EB10, &CMatrixLinkList::GetNumFree);
    Install("CMatrixLinkList", "GetNumUsed1", 0x54EB30, &CMatrixLinkList::GetNumUsed1);
    Install("CMatrixLinkList", "GetNumUsed2", 0x54EB50, &CMatrixLinkList::GetNumUsed2);
}

CMatrixLinkList::CMatrixLinkList() : m_head(), m_tail(), m_allocatedListHead(), m_allocatedListTail(), m_freeListHead(), m_freeListTail()
{
    m_pObjects = nullptr;
}

void CMatrixLinkList::Init(int32 count)
{
    m_pObjects = new CMatrixLink[count];

    m_head.m_pNext = &m_tail;
    m_tail.m_pPrev = &m_head;

    m_freeListHead.m_pNext = &m_freeListTail;
    m_freeListTail.m_pPrev = &m_freeListHead;

    m_allocatedListHead.m_pNext = &m_allocatedListTail;
    m_allocatedListTail.m_pPrev = &m_allocatedListHead;

    for (int32 i = count - 1; i >= 0; --i) {
        auto& pMat = m_pObjects[i];
        m_freeListHead.Insert(&pMat);
    }
}

void CMatrixLinkList::Shutdown()
{
    delete[] m_pObjects;
    m_pObjects = nullptr;
}

CMatrixLink* CMatrixLinkList::AddToList1()
{
    if (IsFull())
        return nullptr;

    auto pNextFree = m_freeListHead.m_pNext;
    CMatrixLinkList::MoveToList1(pNextFree);
    return pNextFree;
}

CMatrixLink* CMatrixLinkList::AddToList2()
{
    if (IsFull())
        return nullptr;

    auto pNextFree = m_freeListHead.m_pNext;
    CMatrixLinkList::MoveToList2(pNextFree);
    return pNextFree;
}

void CMatrixLinkList::MoveToList1(CMatrixLink* pMat)
{
    pMat->Remove();
    m_head.Insert(pMat);
}

void CMatrixLinkList::MoveToList2(CMatrixLink* pMat)
{
    pMat->Remove();
    m_allocatedListHead.Insert(pMat);
}

void CMatrixLinkList::MoveToFreeList(CMatrixLink* pMat)
{
    pMat->Remove();
    m_freeListHead.Insert(pMat);
}

int32 CMatrixLinkList::GetNumFree()
{
    int32 result = 0;
    auto pCur = m_freeListHead.m_pNext;
    while (pCur != &m_freeListTail) {
        pCur = pCur->m_pNext;
        ++result;
    }

    return result;
}

int32 CMatrixLinkList::GetNumUsed1()
{
    int32 result = 0;
    auto pCur = m_head.m_pNext;
    while (pCur != &m_tail) {
        pCur = pCur->m_pNext;
        ++result;
    }

    return result;
}

int32 CMatrixLinkList::GetNumUsed2()
{
    int32 result = 0;
    auto pCur = m_allocatedListHead.m_pNext;
    while (pCur != &m_allocatedListTail) {
        pCur = pCur->m_pNext;
        ++result;
    }

    return result;
}
