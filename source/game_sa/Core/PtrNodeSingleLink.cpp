#include "StdInc.h"

#include "PtrNodeSingleLink.h"

void CPtrNodeSingleLink::InjectHooks() {
    RH_ScopedClass(CPtrNodeSingleLink);
    RH_ScopedCategory("Core");

    RH_ScopedInstall(AddToList, 0x532960);
}

void CPtrNodeSingleLink::AddToList(CPtrListSingleLink* list) {
    m_next = list->GetNode();
    list->m_node = reinterpret_cast<CPtrNode*>(this);
}

void* CPtrNodeSingleLink::operator new(unsigned size) {
    return GetPtrNodeSingleLinkPool()->New();
}

void CPtrNodeSingleLink::operator delete(void* data) {
    GetPtrNodeSingleLinkPool()->Delete(static_cast<CPtrNodeSingleLink*>(data));
}
