#include "StdInc.h"

#include "Dummy.h"

void CDummy::InjectHooks() {
    RH_ScopedClass(CDummy);
    RH_ScopedCategory("Entity/Dummy");

    RH_ScopedGlobalInstall(IsDummyPointerValid, 0x532730);
}

void* CDummy::operator new(unsigned size) {
    return GetDummyPool()->New();
}

void CDummy::operator delete(void* obj) {
    GetDummyPool()->Delete(static_cast<CDummy*>(obj));
}

bool IsDummyPointerValid(CDummy* pDummy) {
    return GetDummyPool()->IsObjectValid(pDummy);
}
