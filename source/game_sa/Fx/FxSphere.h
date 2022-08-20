#pragma once

#include "FxPlane.h"

class CVector;

class FxSphere_c /*: public RwSphere*/ {
public:
    CVector m_vecCenter;
    float   m_fRadius;
    uint32  m_nNumPlanesPassed; // m_LastPlaneRejected

public:
    static void InjectHooks();

    static void* operator new(uint32 size, bool32 bUseGlobalHeep);
    static void  operator delete(void* data);
    static void  operator delete(void* data, bool32 bUseGlobalHeep);

    FxSphere_c();

    inline bool  IsCollision(FxSphere_c* sphere) const;
    inline float GetDistToPlane(FxPlane_c* plane) const;
};

VALIDATE_SIZE(FxSphere_c, 0x14);
