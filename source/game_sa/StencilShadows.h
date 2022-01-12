#pragma once

class CStencilShadows {
public:
    static CStencilShadowObject* m_StencilShadowObjects[64];
    static CStencilShadowObject* pFirstAvailableStencilShadowObject;
    static CStencilShadowObject* pFirstActiveStencilShadowObject;

    static void InjectHooks();

    static void Init();
    static void Process(RwV3d* cameraPos);
};
