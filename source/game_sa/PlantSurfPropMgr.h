#pragma once

constexpr auto MAX_SURFACE_PROPERTIES = 178u;

class CPlantSurfPropMgr {
public:
    static int32* (&m_SurfPropPtrTab)[MAX_SURFACE_PROPERTIES];
    static int32& m_countSurfPropsAllocated;
    static int32*& m_SurfPropTab;

public:
    static void InjectHooks();

    CPlantSurfPropMgr() = default;
    ~CPlantSurfPropMgr() = default;

    bool Initialise();
    void Shutdown();

    int32* AllocSurfProperties(uint16 surfaceId, bool clearAllocCount);
    bool LoadPlantsDat(const char* filename);
    int32* GetSurfProperties(uint16 index);
};
