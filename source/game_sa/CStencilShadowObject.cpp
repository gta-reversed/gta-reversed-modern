#include "StdInc.h"

void CStencilShadowObject::InjectHooks() {
//    ReversibleHooks::Install("CStencilShadowObject", "Render", 0x710D50, &CStencilShadowObject::Render);
//    ReversibleHooks::Install("CStencilShadowObject", "RenderForVehicle", 0x70FAE0, &CStencilShadowObject::RenderForVehicle);
//    ReversibleHooks::Install("CStencilShadowObject", "RenderForObject", 0x710310, &CStencilShadowObject::RenderForObject);
}

// 0x711280
CStencilShadowObject::CStencilShadowObject() {

}

// 0x711310
CStencilShadowObject::~CStencilShadowObject() {

}

// 0x710D50
void CStencilShadowObject::Render(CRGBA* color) {
    plugin::Call<0x710D50, CRGBA*>(color);
}

// 0x7113B0
void gRenderStencil() {
    plugin::Call<0x7113B0>();
}

// 0x70FAE0
void CStencilShadowObject::RenderForVehicle(CDummy* dummy) {
    plugin::Call<0x70FAE0, CDummy* >(dummy);
}

// 0x710310
void CStencilShadowObject::RenderForObject(CStencilShadowObject* object) {
    plugin::Call<0x710310, CStencilShadowObject*>(object);
}
