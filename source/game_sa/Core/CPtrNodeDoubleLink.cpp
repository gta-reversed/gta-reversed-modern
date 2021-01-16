/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

void CPtrNodeDoubleLink::InjectHooks()
{
    ReversibleHooks::Install("CPtrNodeDoubleLink", "operator new", 0x5523C0, &CPtrNodeDoubleLink::operator new);
    ReversibleHooks::Install("CPtrNodeDoubleLink", "operator delete", 0x5523D0, &CPtrNodeDoubleLink::operator delete);
    ReversibleHooks::Install("CPtrNodeDoubleLink", "AddToList", 0x5329A0, &CPtrNodeDoubleLink::AddToList);
}

void* CPtrNodeDoubleLink::operator new(unsigned int size)
{
    return CPools::ms_pPtrNodeDoubleLinkPool->New();
}

void CPtrNodeDoubleLink::operator delete(void* ptr, size_t sz)
{
    CPools::ms_pPtrNodeDoubleLinkPool->Delete(reinterpret_cast<CPtrNodeDoubleLink*>(ptr));
}

void CPtrNodeDoubleLink::AddToList(CPtrListDoubleLink* list)
{
    pPrev = nullptr;
    auto pNode = list->GetNode();
    pNext = pNode;

    if (pNode)
        pNode->pPrev = this;

    list->pNode = reinterpret_cast<CPtrNode*>(this);
}
