/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

unsigned int MAX_STORED_SHADOWS = 48;
unsigned int MAX_PERMANENT_SHADOWS = 48;
unsigned int MAX_STATIC_SHADOWS = 48;
unsigned int MAX_SHADOW_POLY_BUNCHES = 360;

float& MAX_DISTANCE_PED_SHADOWS = *(float*)0x8D5240;
float& MAX_DISTANCE_PED_SHADOWS_SQR = *(float*)0xC4B6B0;
RwTexture*& gpShadowCarTex = *(RwTexture**)0xC403E0;
RwTexture*& gpShadowPedTex = *(RwTexture**)0xC403E4;
RwTexture*& gpShadowHeliTex = *(RwTexture**)0xC403E8;
RwTexture*& gpShadowBikeTex = *(RwTexture**)0xC403EC;
RwTexture*& gpShadowBaronTex = *(RwTexture**)0xC403F0;
RwTexture*& gpShadowExplosionTex = *(RwTexture**)0xC403F4;
RwTexture*& gpShadowHeadLightsTex = *(RwTexture**)0xC403F8;
RwTexture*& gpShadowHeadLightsTex2 = *(RwTexture**)0xC403FC;
RwTexture*& gpBloodPoolTex = *(RwTexture**)0xC40400;
RwTexture*& gpHandManTex = *(RwTexture**)0xC40404;
RwTexture*& gpCrackedGlassTex = *(RwTexture**)0xC40408;
RwTexture*& gpPostShadowTex = *(RwTexture**)0xC4040C;
CPolyBunch*& CShadows::pEmptyBunchList = *(CPolyBunch**)0xC403D8;
unsigned short& CShadows::ShadowsStoredToBeRendered = *(unsigned short*)0xC403DC;
CRegisteredShadow* CShadows::asShadowsStored = (CRegisteredShadow*)0xC40430;
CPolyBunch* CShadows::aPolyBunches = (CPolyBunch*)0xC40DF0;
CStaticShadow* CShadows::aStaticShadows = (CStaticShadow*)0xC4A030;
CPermanentShadow* CShadows::aPermanentShadows = (CPermanentShadow*)0xC4AC30;

// 0x707670
void CStaticShadow::Free() {
    ((void(__thiscall*)(CStaticShadow*))0x707670)(this);
}

// 0x706CD0
void CShadows::Init() {
    ((void(__cdecl*)())0x706CD0)();
}

// 0x706ED0
void CShadows::Shutdown() {
    ((void(__cdecl*)())0x706ED0)();
}

// 0x706F60
void CShadows::AddPermanentShadow(unsigned char type, RwTexture* texture, CVector* posn, float topX, float topY, float rightX, float rightY, short intensity, unsigned char red, unsigned char greeb, unsigned char blue, float drawDistance, unsigned int time, float upDistance) {
    ((void(__cdecl*)(unsigned char, RwTexture*, CVector*, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, unsigned int, float))0x706F60)(type, texture, posn, topX, topY, rightX, rightY, intensity, red, greeb, blue, drawDistance, time, upDistance);
}

// 0x707390
void CShadows::StoreShadowToBeRendered(unsigned char type, RwTexture* texture, CVector* posn, float topX, float topY, float rightX, float rightY, short intensity, unsigned char red, unsigned char green, unsigned char blue, float zDistance, bool drawOnWater, float scale, CRealTimeShadow* realTimeShadow, bool drawOnBuildings) {
    ((void(__cdecl*)(unsigned char, RwTexture*, CVector*, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, bool, float, CRealTimeShadow*, bool))0x707390)(type, texture, posn, topX, topY, rightX, rightY, intensity, red, green, blue, zDistance, drawOnWater, scale, realTimeShadow, drawOnBuildings);
}

// 0x707460
void CShadows::SetRenderModeForShadowType(unsigned char shadowType) {
    ((void(__cdecl*)(unsigned char))0x707460)(shadowType);
}

// 0x7074F0
void CShadows::RemoveOilInArea(float x1, float y1, float x2, float y2) {
    ((void(__cdecl*)(float, float, float, float))0x7074F0)(x1, y1, x2, y2);
}

// 0x707550
void CShadows::GunShotSetsOilOnFire(CVector const* shotOrigin, CVector const* shotTarget) {
    ((void(__cdecl*)(CVector const*, CVector const*))0x707550)(shotOrigin, shotTarget);
}

// 0x7076B0
void CShadows::PrintDebugPoly(CVector* a, CVector* b, CVector* c) {
    ((void(__cdecl*)(CVector*, CVector*, CVector*))0x7076B0)(a, b, c);
}

// 0x7076C0
void CShadows::CalcPedShadowValues(CVector sunPosn, float* displacementX, float* displacementY, float* frontX, float* frontY, float* sideX, float* sideY) {
    ((void(__cdecl*)(CVector, float*, float*, float*, float*, float*, float*))0x7076C0)(sunPosn, displacementX, displacementY, frontX, frontY, sideX, sideY);
}

// 0x707770
void CShadows::TidyUpShadows() {
    ((void(__cdecl*)())0x707770)();
}

// 0x707850
void CShadows::AffectColourWithLighting(unsigned char shadowType, unsigned char dayNightIntensity, unsigned char red, unsigned char green, unsigned char blue, unsigned char* outRed, unsigned char* outGreen, unsigned char* outBlue) {
    ((void(__cdecl*)(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char*, unsigned char*, unsigned char*))0x707850)(shadowType, dayNightIntensity, red, green, blue, outRed, outGreen, outBlue);
}

// 0x707930
void CShadows::StoreShadowToBeRendered(unsigned char shadowTextureType, CVector* posn, float frontX, float frontY, float sideX, float sideY, short intensity, unsigned char red, unsigned char green, unsigned char blue) {
    ((void(__cdecl*)(unsigned char, CVector*, float, float, float, float, short, unsigned char, unsigned char, unsigned char))0x707930)(shadowTextureType, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue);
}

// 0x707B40
void CShadows::StoreShadowForPedObject(CEntity* ped, float displacementX, float displacementY, float frontX, float frontY, float sideX, float sideY) {
    plugin::Call<0x707B40, CEntity*, float, float, float, float, float, float>
        (ped, displacementX, displacementY, frontX, frontY, sideX, sideY);
}

// 0x707CA0
void CShadows::StoreRealTimeShadow(CPhysical* physical, float displacementX, float displacementY, float frontX, float frontY, float sideX, float sideY) {
    ((void(__cdecl*)(CPhysical*, float, float, float, float, float, float))0x707CA0)(physical, displacementX, displacementY, frontX, frontY, sideX, sideY);
}

// 0x707F40
void CShadows::UpdateStaticShadows() {
    ((void(__cdecl*)())0x707F40)();
}

// 0x707FA0
void CShadows::RenderExtraPlayerShadows() {
    ((void(__cdecl*)())0x707FA0)();
}

// 0x708300
void CShadows::RenderStaticShadows() {
    ((void(__cdecl*)())0x708300)();
}

// 0x7086B0
void CShadows::CastShadowEntityXY(CEntity* entity, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, short intensity, unsigned char red, unsigned char green, unsigned char blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, unsigned char* pDayNightIntensity, int shadowType) {
    ((void(__cdecl*)(CEntity*, float, float, float, float, CVector*, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, float, CPolyBunch**, unsigned char*, int))0x7086B0)(entity, conrerAX, cornerAY, cornerBX, cornerBY, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, pDayNightIntensity, shadowType);
}

// 0x70A040
void CShadows::CastShadowEntityXYZ(CEntity* entity, CVector* posn, float frontX, float frontY, float sideX, float sideY, short intensity, unsigned char red, unsigned char green, unsigned char blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, CRealTimeShadow* realTimeShadow) {
    ((void(__cdecl*)(CEntity*, CVector*, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, float, CPolyBunch**, CRealTimeShadow*))0x70A040)(entity, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, realTimeShadow);
}

// 0x70A470
void CShadows::CastPlayerShadowSectorList(CPtrList& ptrList, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, short intensity, unsigned char red, unsigned char green, unsigned char blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, unsigned char* pDayNightIntensity, int shadowType) {
    ((void(__cdecl*)(CPtrList&, float, float, float, float, CVector*, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, float, CPolyBunch**, unsigned char*, int))0x70A470)(ptrList, conrerAX, cornerAY, cornerBX, cornerBY, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, pDayNightIntensity, shadowType);
}

// 0x70A630
void CShadows::CastShadowSectorList(CPtrList& ptrList, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, short intensity, unsigned char red, unsigned char green, unsigned char blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, unsigned char* pDayNightIntensity, int shadowType) {
    ((void(__cdecl*)(CPtrList&, float, float, float, float, CVector*, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, float, CPolyBunch**, unsigned char*, int))0x70A630)(ptrList, conrerAX, cornerAY, cornerBX, cornerBY, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, pDayNightIntensity, shadowType);
}

// 0x70A7E0
void CShadows::CastRealTimeShadowSectorList(CPtrList& ptrList, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, short intensity, unsigned char red, unsigned char green, unsigned char blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, CRealTimeShadow* realTimeShadow, unsigned char* pDayNightIntensity) {
    ((void(__cdecl*)(CPtrList&, float, float, float, float, CVector*, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, float, CPolyBunch**, CRealTimeShadow*, unsigned char*))0x70A7E0)(ptrList, conrerAX, cornerAY, cornerBX, cornerBY, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, realTimeShadow, pDayNightIntensity);
}

// 0x70A960
void CShadows::RenderStoredShadows() {
    ((void(__cdecl*)())0x70A960)();
}

// 0x70B730
void CShadows::GeneratePolysForStaticShadow(short staticShadowIndex) {
    ((void(__cdecl*)(short))0x70B730)(staticShadowIndex);
}

// 0x70BA00
bool CShadows::StoreStaticShadow(unsigned int id, unsigned char type, RwTexture* texture, CVector* posn, float frontX, float frontY, float sideX, float sideY, short intensity, unsigned char red, unsigned char green, unsigned char blue, float zDistane, float scale, float drawDistance, bool temporaryShadow, float upDistance) {
    return ((bool(__cdecl*)(unsigned int, unsigned char, RwTexture*, CVector*, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, float, float, bool, float))0x70BA00)(id, type, texture, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistane, scale, drawDistance, temporaryShadow, upDistance);
}

// 0x70BDA0
void CShadows::StoreShadowForVehicle(CVehicle* vehicle, VEH_SHD_TYPE vehShadowType) {
    ((void(__cdecl*)(CVehicle*, VEH_SHD_TYPE))0x70BDA0)(vehicle, vehShadowType);
}

// 0x70C500
void CShadows::StoreCarLightShadow(CVehicle* vehicle, int id, RwTexture* texture, CVector* posn, float frontX, float frontY, float sideX, float sideY, unsigned char red, unsigned char green, unsigned char blue, float maxViewAngle) {
    ((void(__cdecl*)(CVehicle*, int, RwTexture*, CVector*, float, float, float, float, unsigned char, unsigned char, unsigned char, float))0x70C500)(vehicle, id, texture, posn, frontX, frontY, sideX, sideY, red, green, blue, maxViewAngle);
}

// 0x70C750
void CShadows::StoreShadowForPole(CEntity* entity, float offsetX, float offsetY, float offsetZ, float poleHeight, float poleWidth, unsigned int localId) {
    ((void(__cdecl*)(CEntity*, float, float, float, float, float, unsigned int))0x70C750)(entity, offsetX, offsetY, offsetZ, poleHeight, poleWidth, localId);
}

// 0x70C950
void CShadows::UpdatePermanentShadows() {
    ((void(__cdecl*)())0x70C950)();
}

// 0x70CCB0
void CShadows::RenderIndicatorShadow(unsigned int id, unsigned char shadowType, RwTexture* texture, CVector* posn, float frontX, float frontY, float sideX, float sideY, short intensity) {
    ((void(__cdecl*)(unsigned int, unsigned char, RwTexture*, CVector*, float, float, float, float, short))0x70CCB0)(id, shadowType, texture, posn, frontX, frontY, sideX, sideY, intensity);
}

#ifdef _MSC_VER
RwV3d* ShadowRenderTriangleCB(RwV3d* pNormal, RwV3d* pTrianglePos, _ProjectionParam* param) {
    RwV3d* result = 0;
    __asm mov eax, pNormal
    __asm mov ebx, pTrianglePos
    __asm mov edi, param
    __asm mov ecx, 0x709CF0
    __asm call ecx
    __asm mov result, eax
    return result;
}
#endif
