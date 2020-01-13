#include "StdInc.h"

SurfaceInfos_c* g_surfaceInfos = reinterpret_cast<SurfaceInfos_c*>(0xB79538);

int SurfaceInfos_c::GetAdhesionGroup(int surfaceId)
{
    return plugin::CallMethodAndReturn<int, 0x55E5C0, SurfaceInfos_c*, int> (this, surfaceId);
}