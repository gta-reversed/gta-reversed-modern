#include "StdInc.h"

#include "AttractorScanner.h"

void CAttractorScanner::Clear()
{
    plugin::CallMethod<0x5FFF90, CAttractorScanner*>(this);
}
