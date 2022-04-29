/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "PtrNodeDoubleLink.h"

void CPtrNodeDoubleLink::InjectHooks() {
    RH_ScopedClass(CPtrNodeDoubleLink);
    RH_ScopedCategory("Core");

    RH_ScopedInstall(operator new, 0x5523C0);
    RH_ScopedInstall(operator delete, 0x5523D0);
    RH_ScopedInstall(AddToList, 0x5329A0);
}

void* CPtrNodeDoubleLink::operator new(unsigned size) {
    return GetPtrNodeDoubleLinkPool()->New();
}

void CPtrNodeDoubleLink::operator delete(void* ptr, size_t sz) {
    GetPtrNodeDoubleLinkPool()->Delete(static_cast<CPtrNodeDoubleLink*>(ptr));
}

// 0x5329A0
void CPtrNodeDoubleLink::AddToList(CPtrListDoubleLink* list) {
    m_prev = nullptr;
    m_next = list->GetNode();

    if (m_next)
        m_next->m_prev = this;

    list->m_node = reinterpret_cast<CPtrNode*>(this);
}
