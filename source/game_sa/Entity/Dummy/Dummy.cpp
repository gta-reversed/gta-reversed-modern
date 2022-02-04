#include "StdInc.h"

#include "Dummy.h"

void CDummy::InjectHooks() {
    RH_ScopedClass(CDummy);
    RH_ScopedCategory("Entity/Dummy");

    RH_ScopedGlobalInstall(IsDummyPointerValid, 0x532730);
}

void* CDummy::operator new(unsigned size) {
    return CPools::ms_pDummyPool->New();
}

void CDummy::operator delete(void* obj) {
    CPools::ms_pDummyPool->Delete(static_cast<CDummy*>(obj));
}

bool IsDummyPointerValid(CDummy* pDummy) {
    return CPools::ms_pDummyPool->IsObjectValid(pDummy);
}
