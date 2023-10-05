#include "StdInc.h"

#include "StencilShadowObject.h"

// CStencilShadowObject* CStencilShadows::m_StencilShadowObjects = reinterpret_cast<CStencilShadowObject(*)[64]>(0xC6A198);
CStencilShadowObject* CStencilShadows::pFirstAvailableStencilShadowObject = reinterpret_cast<CStencilShadowObject *>(0xC6A168);
CStencilShadowObject* CStencilShadows::pFirstActiveStencilShadowObject = reinterpret_cast<CStencilShadowObject *>(0xC6A16C);

void CStencilShadows::InjectHooks() {
    RH_ScopedClass(CStencilShadows);
    RH_ScopedCategoryGlobal();

RH_ScopedInstall(Init, 0x70F9E0, { .reversed = false });
RH_ScopedInstall(Process, 0x711D90, { .reversed = false });
}

// 0x70F9E0
void CStencilShadows::Init() {
    ZoneScoped;

    plugin::Call<0x70F9E0>();
}

// 0x711D90
void CStencilShadows::Process(CVector& cameraPos) {
    ZoneScoped;

    plugin::Call<0x711D90, CVector&>(cameraPos);
}
