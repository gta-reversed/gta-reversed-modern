#include "StdInc.h"

CSurfaceTable* g_surfaceInfos = reinterpret_cast<CSurfaceTable*>(0xB79538);

bool CSurfaceTable::IsSprint(int surfaceNumber)
{
    return plugin::CallMethodAndReturn<bool, 0x55E870, CSurfaceTable*, int>(this, surfaceNumber);
}

float CSurfaceTable::GetFriction(CColPoint* pColPoint)
{
    return plugin::CallMethodAndReturn<float, 0x55EB50, CSurfaceTable*, CColPoint*>(this, pColPoint);
}