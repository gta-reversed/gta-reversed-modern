#include "StdInc.h"
#include "OALBase.h"

#ifdef USE_OPENAL
OALBase::OALBase() {
    m_refCount = 1;
    ++livingCount;
}

OALBase::~OALBase() {
    --livingCount;
}

void OALBase::Release() {
    if (--m_refCount)
        return;

    // OS_MutexObtain(trashMutex);
    trashCan.push_back(this);
    // OS_MutexRelease(trashMutex);
}

void OALBase::AddRef() {
    ++m_refCount;
}
#endif
