#include "StdInc.h"

#include "StencilShadowObjects.h"

void CStencilShadowObjects::InjectHooks() {
    RH_ScopedClass(CStencilShadowObjects);
    RH_ScopedCategoryGlobal();

RH_ScopedInstall(UpdateHierarchy, 0x710BC0, { .reversed = false });
RH_ScopedInstall(RegisterStencilShadows, 0x711760, { .reversed = false });
RH_ScopedInstall(ScalarConstructor, 0x854B60, { .reversed = false });
RH_ScopedInstall(ScalarDestructor, 0x856AE0, { .reversed = false });
}

// 0x710BC0
void CStencilShadowObjects::UpdateHierarchy(CStencilShadowObject** firstAvailable, CStencilShadowObject** firstActive, CStencilShadowObject* newOne) {
    plugin::Call<0x710BC0, CStencilShadowObject**, CStencilShadowObject**, CStencilShadowObject*>(firstAvailable, firstActive, newOne);
}

// 0x711760
void CStencilShadowObjects::RegisterStencilShadows(RwV3d* cameraPos, int32 flagDoNotCreateNew) {
    plugin::Call<0x711760, RwV3d*, int32>(cameraPos, flagDoNotCreateNew);
}

// 0x854B60
void CStencilShadowObjects::ScalarConstructor() {
    plugin::Call<0x854B60>();
}

// 0x856AE0
void CStencilShadowObjects::ScalarDestructor() {
    plugin::Call<0x856AE0>();
}
