#include "StdInc.h"

bool IsDummyPointerValid(CDummy* pDummy)
{
	return plugin::CallAndReturn<bool, 0x532730, CDummy*>(pDummy);
}
