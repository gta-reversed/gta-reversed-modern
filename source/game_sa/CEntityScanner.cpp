#include "StdInc.h"

void CEntityScanner::Clear()
{
    plugin::CallMethod<0x5FF9D0, CEntityScanner*>(this);
}