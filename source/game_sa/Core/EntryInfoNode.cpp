#include "StdInc.h"

void CEntryInfoNode::InjectHooks()
{
    ReversibleHooks::Install("CEntryInfoNode", "operator new", 0x536DC0, &CEntryInfoNode::operator new);
    ReversibleHooks::Install("CEntryInfoNode", "operator delete", 0x536DD0, &CEntryInfoNode::operator delete);
}

void* CEntryInfoNode::operator new(uint32 size)
{
    return CPools::ms_pEntryInfoNodePool->New();
}

void CEntryInfoNode::operator delete(void* ptr, size_t sz)
{
    CPools::ms_pEntryInfoNodePool->Delete(reinterpret_cast<CEntryInfoNode*>(ptr));
}

void CEntryInfoNode::AddToList(CEntryInfoNode* pNext)
{
    m_pPrevious = nullptr;
    m_pNext = pNext;
    if (pNext) {
        pNext->m_pPrevious = this;
    }
}
