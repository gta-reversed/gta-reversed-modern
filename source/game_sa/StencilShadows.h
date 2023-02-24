#pragma once

class CStencilShadowObject;

class CStencilShadows {
public:
    static CStencilShadowObject* m_StencilShadowObjects[64];
    static CStencilShadowObject* pFirstAvailableStencilShadowObject;
    static CStencilShadowObject* pFirstActiveStencilShadowObject;

    static void InjectHooks();

    static void Init();
    static void Process(CVector& cameraPos);
};
