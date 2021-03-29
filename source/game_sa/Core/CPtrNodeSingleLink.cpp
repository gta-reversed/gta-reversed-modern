#include "StdInc.h"

void CPtrNodeSingleLink::InjectHooks()
{
    ReversibleHooks::Install("CPtrNodeSingleLink", "AddToList", 0x532960, &CPtrNodeSingleLink::AddToList);
}

void CPtrNodeSingleLink::AddToList(CPtrListSingleLink* list)
{
    pNext = list->GetNode();
    list->pNode = reinterpret_cast<CPtrNode*>(this);
}

void* CPtrNodeSingleLink::operator new(unsigned int size)
{
    return CPools::ms_pPtrNodeSingleLinkPool->New();
}

void CPtrNodeSingleLink::operator delete(void* data)
{
    CPools::ms_pPtrNodeSingleLinkPool->Delete(static_cast<CPtrNodeSingleLink*>(data));
}
