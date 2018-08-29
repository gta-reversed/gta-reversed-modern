/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

RwRaster *&CMirrors::pBuffer = *(RwRaster **)0xC7C71C;
RwRaster *&CMirrors::pZBuffer = *(RwRaster **)0xC7C720;
unsigned int &CMirrors::TypeOfMirror = *(unsigned int *)0xC7C724;
bool &CMirrors::bRenderingReflection = *(bool *)0xC7C728;
bool &CMirrors::d3dRestored = *(bool *)0xC7C729;
unsigned int &CMirrors::MirrorFlags = *(unsigned int *)0xC7C618;
float &CMirrors::MirrorV = *(float *)0xC7C61C;
CVector &CMirrors::MirrorNormal = *(CVector *)0xC803D8;
bool &bFudgeNow = *(bool *)0xC7C72A;
float *Screens8Track = (float *)0x8D5DD8;

// Converted from cdecl void CMirrors::BeforeConstructRenderList(void) 0x726DF0
void CMirrors::BeforeConstructRenderList() {
    plugin::Call<0x726DF0>();
}

// Converted from cdecl void CMirrors::BeforeMainRender(void) 0x727140
void CMirrors::BeforeMainRender() {
    plugin::Call<0x727140>();
}

// Converted from cdecl void CMirrors::BuildCamMatrix(CMatrix *mat,CVector pointA,CVector pointB) 0x723150
void CMirrors::BuildCamMatrix(CMatrix* mat, CVector pointA, CVector pointB) {
    plugin::Call<0x723150, CMatrix*, CVector, CVector>(mat, pointA, pointB);
}

// Converted from cdecl void CMirrors::BuildCameraMatrixForScreens(CMatrix *mat) 0x7266B0
void CMirrors::BuildCameraMatrixForScreens(CMatrix* mat) {
    plugin::Call<0x7266B0, CMatrix*>(mat);
}

// Converted from cdecl void CMirrors::CreateBuffer(void) 0x7230A0
void CMirrors::CreateBuffer() {
    plugin::Call<0x7230A0>();
}

// Converted from cdecl void CMirrors::Init(void) 0x723000
void CMirrors::Init() {
    plugin::Call<0x723000>();
}

// Converted from cdecl void CMirrors::RenderMirrorBuffer(void) 0x726090
void CMirrors::RenderMirrorBuffer() {
    plugin::Call<0x726090>();
}

// Converted from cdecl void CMirrors::ShutDown(void) 0x723050
void CMirrors::ShutDown() {
    plugin::Call<0x723050>();
}