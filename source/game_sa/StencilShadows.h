#pragma once

class CStencilShadowObject;

class CStencilShadows {
public:
    static inline auto& m_StencilShadowObjects = StaticRef<std::array<CStencilShadowObject, 64>>(0xC6A198);

    static CStencilShadowObject* pFirstAvailableStencilShadowObject;
    static CStencilShadowObject* pFirstActiveStencilShadowObject;

    static void InjectHooks();

    static void Init();
    static void Destroy();
    static void Shutdown();
    static void Process(CVector& cameraPos);

    // NOTSA/FIX_BUGS: It was named GraphicsLowQuality for some reason
    static bool GraphicsHighQuality();

    static void UpdateHierarchy(CStencilShadowObject*& firstAvailable, CStencilShadowObject*& firstActive, CStencilShadowObject* newOne);
    static void RegisterStencilShadows(CVector& cameraPos, bool doNotCreateNew);

    static void RenderStencilShadows();
    static void RenderForVehicle(CStencilShadowObject*);
    static void RenderForObject(CStencilShadowObject*);
    static void Render();
};
