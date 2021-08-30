#include "StdInc.h"
#include "CBrightLights.h"

int32_t& CBrightLights::NumBrightLights = *(int32_t*)0xC7C6FC;
tBrightLight (&CBrightLights::aBrightLights)[MAX_NUM_BRIGHTLIGHTS] = *(tBrightLight(*)[MAX_NUM_BRIGHTLIGHTS])0xC7CB58;

void CBrightLights::InjectHooks() {
    ReversibleHooks::Install("CBrightLights", "Init", 0x722140, &CBrightLights::Init);
    // ReversibleHooks::Install("CBrightLights", "RenderOutGeometryBuffer", 0x722150, &CBrightLights::RenderOutGeometryBuffer);
    // ReversibleHooks::Install("CBrightLights", "Render", 0x7241C0, &CBrightLights::Render);
    // ReversibleHooks::Install("CBrightLights", "RegisterOne", 0x724770, &CBrightLights::RegisterOne);
}

// 0x722140
void CBrightLights::Init() {
    NumBrightLights = 0;
}

// 0x722150
void CBrightLights::RenderOutGeometryBuffer() {
    plugin::Call<0x722150>();
}

// 0x7241C0
void CBrightLights::Render() {
    plugin::Call<0x7241C0>();
}

// 0x724770
void CBrightLights::RegisterOne(CVector posn, CVector top, CVector right, CVector at, uint8_t color, uint8_t arg5, uint8_t arg6, uint8_t arg7) {
    plugin::Call<0x724770, CVector, CVector, CVector, CVector, uint8_t, uint8_t, uint8_t, uint8_t>(posn, top, right, at, color, arg5, arg6, arg7);
}
