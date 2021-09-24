#include "StdInc.h"

void CDummy::InjectHooks()
{
    ReversibleHooks::Install("CDummy", "IsDummyPointerValid", 0x532730, &IsDummyPointerValid);
}

void* CDummy::operator new(unsigned size)
{
    return CPools::ms_pDummyPool->New();
}

void CDummy::operator delete(void* pObj)
{
    CPools::ms_pDummyPool->Delete(static_cast<CDummy*>(pObj));
}

bool IsDummyPointerValid(CDummy* pDummy)
{
    return CPools::ms_pDummyPool->IsObjectValid(pDummy);
}
