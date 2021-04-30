#include "StdInc.h"

float& CDraw::ms_fFOV = *(float *) 0x8D5038;
float &CDraw::ms_fLODDistance = *(float *) 0xC3EF98;
float &CDraw::ms_fFarClipZ = *(float *) 0xC3EF9C;
float &CDraw::ms_fNearClipZ = *(float *) 0xC3EFA0;
float &CDraw::ms_fAspectRatio = *(float *) 0xC3EFA4;
unsigned char &CDraw::FadeRed = *(unsigned char *) 0xC3EFA8;
unsigned char &CDraw::FadeGreen = *(unsigned char *) 0xC3EFA9;
unsigned char &CDraw::FadeBlue = *(unsigned char *) 0xC3EFAA;
unsigned char &CDraw::FadeValue = *(unsigned char *) 0xC3EFAB;

void CDraw::InjectHooks() {
    ReversibleHooks::Install("CDraw", "SetFOV", 0x6FF410, &CDraw::SetFOV);
//    ReversibleHooks::Install("CDraw", "CalculateAspectRatio", 0x6FF420, &CDraw::CalculateAspectRatio);
}

// 0x6FF410
void CDraw::SetFOV(float fovValue) {
    CDraw::ms_fFOV = fovValue;
}

// 0x6FF420
float CDraw::CalculateAspectRatio() {
    return plugin::CallAndReturn<float, 0x6FF420>();
}
