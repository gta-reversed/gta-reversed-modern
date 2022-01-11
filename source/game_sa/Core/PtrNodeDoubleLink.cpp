/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "PtrNodeDoubleLink.h"

void CPtrNodeDoubleLink::InjectHooks() {
    ReversibleHooks::Install("CPtrNodeDoubleLink", "operator new", 0x5523C0, &CPtrNodeDoubleLink::operator new);
    ReversibleHooks::Install("CPtrNodeDoubleLink", "operator delete", 0x5523D0, &CPtrNodeDoubleLink::operator delete);
    ReversibleHooks::Install("CPtrNodeDoubleLink", "AddToList", 0x5329A0, &CPtrNodeDoubleLink::AddToList);
}

void* CPtrNodeDoubleLink::operator new(uint32 size) {
    return CPools::ms_pPtrNodeDoubleLinkPool->New();
}

void CPtrNodeDoubleLink::operator delete(void* ptr, size_t sz) {
    CPools::ms_pPtrNodeDoubleLinkPool->Delete(static_cast<CPtrNodeDoubleLink*>(ptr));
}

// 0x5329A0
void CPtrNodeDoubleLink::AddToList(CPtrListDoubleLink* list) {
    m_prev = nullptr;
    m_next = list->GetNode();

    if (m_next)
        m_next->m_prev = this;

    list->m_node = reinterpret_cast<CPtrNode*>(this);
}
