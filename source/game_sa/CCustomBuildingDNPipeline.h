#pragma once
#include "PluginBase.h"
#include "RenderWare.h"

class CCustomBuildingDNPipeline {
public:
    static bool& m_bCameraChange;
    static RwUInt32& m_AtmDNWorkingIndex;
    static RxPipeline*& ObjPipeline;
    static RwUInt32& ms_extraVertColourPluginOffset;
    static float& m_fDNBalanceParam;

public:
    static void PreRenderUpdate(RpAtomic* pAtomic, bool ignoreDNBalanceParam);
    static RpAtomic* PreRenderUpdateRpAtomicCB(RpAtomic* pAtomic, void* data);
};
