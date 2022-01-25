#include "StdInc.h"

void CStencilShadowObjects::InjectHooks() {
//    Install("CStencilShadowObjects", "UpdateHierarchy", 0x710BC0, &CStencilShadowObjects::UpdateHierarchy);
//    Install("CStencilShadowObjects", "RegisterStencilShadows", 0x711760, &CStencilShadowObjects::RegisterStencilShadows);
//    Install("CStencilShadowObjects", "ScalarConstructor", 0x854B60, &CStencilShadowObjects::ScalarConstructor);
//    Install("CStencilShadowObjects", "ScalarDestructor", 0x856AE0, &CStencilShadowObjects::ScalarDestructor);
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