/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

void* CPtrNodeDoubleLink::operator new(unsigned int size)
{
    return plugin::CallAndReturn<void*, 0x5523C0, unsigned int>(size);
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
