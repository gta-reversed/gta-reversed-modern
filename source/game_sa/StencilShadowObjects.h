#pragma once

class CStencilShadowObject;

class CStencilShadowObjects {
public:
    static void InjectHooks();

    static void UpdateHierarchy(CStencilShadowObject **firstAvailable, CStencilShadowObject **firstActive, CStencilShadowObject* newOne);
    static void RegisterStencilShadows(RwV3d *cameraPos, int32 flagDoNotCreateNew);
    static void ScalarConstructor();
    static void ScalarDestructor();
};
