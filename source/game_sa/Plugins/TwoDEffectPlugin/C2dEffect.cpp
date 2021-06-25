#include "StdInc.h"

unsigned int& C2dEffect::g2dEffectPluginOffset = *(unsigned int*)0xC3A1E0;
unsigned int& C2dEffect::ms_nTxdSlot = *(unsigned int*)0x8D4948;

void C2dEffect::InjectHooks()
{
// Class methods
    ReversibleHooks::Install("C2dEffect", "Shutdown", 0x4C57D0, &C2dEffect::Shutdown);

// Statics
    ReversibleHooks::Install("C2dEffect", "Roadsign_GetNumLinesFromFlags", 0x6FA640, &C2dEffect::Roadsign_GetNumLinesFromFlags);
    ReversibleHooks::Install("C2dEffect", "Roadsign_GetNumLettersFromFlags", 0x6FA670, &C2dEffect::Roadsign_GetNumLettersFromFlags);
    ReversibleHooks::Install("C2dEffect", "Roadsign_GetPaletteIDFromFlags", 0x6FA6A0, &C2dEffect::Roadsign_GetPaletteIDFromFlags);
    ReversibleHooks::Install("C2dEffect", "PluginAttach", 0x6FA970, &C2dEffect::PluginAttach);
    ReversibleHooks::Install("C2dEffect", "DestroyAtomic", 0x4C54E0, &C2dEffect::DestroyAtomic);

// RW PLUGIN
    ReversibleHooks::Install("C2dEffect", "RpGeometryGet2dFxCount", 0x4C4340, &RpGeometryGet2dFxCount);
    ReversibleHooks::Install("C2dEffect", "RpGeometryGet2dFxAtIndex", 0x4C4A40, &RpGeometryGet2dFxAtIndex);

    ReversibleHooks::Install("C2dEffect", "t2dEffectPluginConstructor", 0x6F9F90, &t2dEffectPluginConstructor);
    ReversibleHooks::Install("C2dEffect", "t2dEffectPluginDestructor", 0x6FA880, &t2dEffectPluginDestructor);
    ReversibleHooks::Install("C2dEffect", "t2dEffectPluginCopyConstructor", 0x6F9FB0, &t2dEffectPluginCopyConstructor);

    //ReversibleHooks::Install("C2dEffect", "Rwt2dEffectPluginDataChunkReadCallBack", 0x6F9FD0, &Rwt2dEffectPluginDataChunkReadCallBack);
    ReversibleHooks::Install("C2dEffect", "Rwt2dEffectPluginDataChunkWriteCallBack", 0x6FA620, &Rwt2dEffectPluginDataChunkWriteCallBack);
    ReversibleHooks::Install("C2dEffect", "Rwt2dEffectPluginDataChunkGetSizeCallBack", 0x6FA630, &Rwt2dEffectPluginDataChunkGetSizeCallBack);
}

void C2dEffect::Shutdown()
{
    if (m_nType == e2dEffectType::EFFECT_ROADSIGN) {
        if (roadsign.m_pText) {
            CMemoryMgr::Free(roadsign.m_pText);
            roadsign.m_pText = nullptr;
        }

        if (roadsign.m_pAtomic) {
            C2dEffect::DestroyAtomic(roadsign.m_pAtomic);
            roadsign.m_pAtomic = nullptr;
        }
    }
    else if (m_nType == e2dEffectType::EFFECT_LIGHT) {
        if (light.m_pCoronaTex) {
            RwTextureDestroy(light.m_pCoronaTex);
            light.m_pCoronaTex = nullptr;
        }

        if (light.m_pShadowTex) {
            RwTextureDestroy(light.m_pShadowTex);
            light.m_pShadowTex = nullptr;
        }
    }
}

int C2dEffect::Roadsign_GetNumLinesFromFlags(CRoadsignAttrFlags flags)
{
    switch (flags.m_nNumOfLines) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    }

    return 4;
}

int C2dEffect::Roadsign_GetNumLettersFromFlags(CRoadsignAttrFlags flags)
{
    switch (flags.m_nSymbolsPerLine) {
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 8;
    }

    return 16;
}

int C2dEffect::Roadsign_GetPaletteIDFromFlags(CRoadsignAttrFlags flags)
{

    switch (flags.m_nTextColor) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    }

    return 0;
}

bool C2dEffect::PluginAttach()
{
    C2dEffect::g2dEffectPluginOffset = RpGeometryRegisterPlugin(
        sizeof(t2dEffectPlugin),
        MAKECHUNKID(rwVENDORID_ROCKSTAR, 0xF8),
        t2dEffectPluginConstructor,
        t2dEffectPluginDestructor,
        t2dEffectPluginCopyConstructor
    );

    RpGeometryRegisterPluginStream(
        MAKECHUNKID(rwVENDORID_ROCKSTAR, 0xF8),
        Rwt2dEffectPluginDataChunkReadCallBack,
        Rwt2dEffectPluginDataChunkWriteCallBack,
        Rwt2dEffectPluginDataChunkGetSizeCallBack
    );

    return C2dEffect::g2dEffectPluginOffset != -1;
}

void C2dEffect::DestroyAtomic(RpAtomic* pAtomic)
{
    if (!pAtomic)
        return;

    auto pFrame = RpAtomicGetFrame(pAtomic);
    if (pFrame) {
        RpAtomicSetFrame(pAtomic, nullptr);
        RwFrameDestroy(pFrame);
    }
    RpAtomicDestroy(pAtomic);
}

unsigned int RpGeometryGet2dFxCount(RpGeometry* pGeometry)
{
    auto plugin = C2DEFFECTPLG(pGeometry, m_pEffectEntries);
    if (!plugin)
        return 0;

    return plugin->m_nObjCount;
}

C2dEffect* RpGeometryGet2dFxAtIndex(RpGeometry* pGeometry, int iEffectInd)
{
    auto plugin = C2DEFFECTPLG(pGeometry, m_pEffectEntries);
    return &plugin->m_pObjects[iEffectInd];
}

void* t2dEffectPluginConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject)
{
    C2DEFFECTPLG(object, m_pEffectEntries) = nullptr;
    return object;
}

void* t2dEffectPluginDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject)
{
    auto plugin = C2DEFFECTPLG(object, m_pEffectEntries);
    if (!plugin)
        return object;

    // It's the same as CModelInfo::ms_2dFXInfoStore cleaning, maybe the plugin has CStore inside too?
    // Dunno how that would work, as the size is decided at runtime, easy with some manual memory tricks tho.
    for (uint32_t i = 0; i < plugin->m_nObjCount; ++i) {
        auto& pEffect = plugin->m_pObjects[i];
        pEffect.Shutdown();
    }

    if (C2DEFFECTPLG(object, m_pEffectEntries))
        CMemoryMgr::Free(C2DEFFECTPLG(object, m_pEffectEntries));

    return object;
}

void* t2dEffectPluginCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject)
{
    C2DEFFECTPLG(dstObject, m_pEffectEntries) = nullptr;
    return dstObject;
}

RwStream* Rwt2dEffectPluginDataChunkReadCallBack(RwStream* stream, RwInt32 binaryLength, void* object, RwInt32 offsetInObject, RwInt32 sizeInObject)
{
    return plugin::CallAndReturn<RwStream*, 0x6F9FD0, RwStream*, RwInt32, const void*, RwInt32, RwInt32>
        (stream, binaryLength, object, offsetInObject, sizeInObject);
}

RwStream* Rwt2dEffectPluginDataChunkWriteCallBack(RwStream* stream, RwInt32 binaryLength, const void* object, RwInt32 offsetInObject, RwInt32 sizeInObject)
{
    return stream;
}

RwInt32 Rwt2dEffectPluginDataChunkGetSizeCallBack(const void* object, RwInt32 offsetInObject, RwInt32 sizeInObject)
{
    return -1;
}
