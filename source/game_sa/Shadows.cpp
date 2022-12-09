/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Shadows.h"

void CShadows::InjectHooks() {
    RH_ScopedClass(CShadows);
    RH_ScopedCategory("Shadows");

    RH_ScopedInstall(Init, 0x706CD0);
    RH_ScopedInstall(Shutdown, 0x706ED0);
    RH_ScopedInstall(TidyUpShadows, 0x707770);
    RH_ScopedInstall(AddPermanentShadow, 0x706F60, { .reversed = false });
    RH_ScopedInstall(UpdatePermanentShadows, 0x70C950, { .reversed = false });
    RH_ScopedOverloadedInstall(StoreShadowToBeRendered, "Texture", 0x707390, void(*)(uint8, RwTexture*, CVector*, float, float, float, float, int16, uint8, uint8, uint8, float, bool, float, CRealTimeShadow*, bool));
    RH_ScopedOverloadedInstall(StoreShadowToBeRendered, "Type", 0x707930, void(*)(uint8, CVector*, float, float, float, float, int16, uint8, uint8, uint8));
    RH_ScopedInstall(SetRenderModeForShadowType, 0x707460);
    RH_ScopedInstall(RemoveOilInArea, 0x7074F0);
    RH_ScopedInstall(GunShotSetsOilOnFire, 0x707550, { .reversed = false });
    RH_ScopedInstall(PrintDebugPoly, 0x7076B0);
    RH_ScopedInstall(CalcPedShadowValues, 0x7076C0);
    RH_ScopedInstall(AffectColourWithLighting, 0x707850, { .reversed = false });
    RH_ScopedInstall(StoreShadowForPedObject, 0x707B40, { .reversed = false });
    RH_ScopedInstall(StoreRealTimeShadow, 0x707CA0, { .reversed = false });
    RH_ScopedInstall(UpdateStaticShadows, 0x707F40, { .reversed = false });
    RH_ScopedInstall(RenderExtraPlayerShadows, 0x707FA0, { .reversed = false });
    RH_ScopedInstall(RenderStaticShadows, 0x708300, { .reversed = false });
    RH_ScopedInstall(CastShadowEntityXY, 0x7086B0, { .reversed = false });
    RH_ScopedInstall(CastShadowEntityXYZ, 0x70A040, { .reversed = false });
    RH_ScopedInstall(CastPlayerShadowSectorList, 0x70A470, { .reversed = false });
    RH_ScopedInstall(CastShadowSectorList, 0x70A630, { .reversed = false });
    RH_ScopedInstall(CastRealTimeShadowSectorList, 0x70A7E0, { .reversed = false });
    RH_ScopedInstall(RenderStoredShadows, 0x70A960, { .reversed = false });
    RH_ScopedInstall(GeneratePolysForStaticShadow, 0x70B730, { .reversed = false });
    RH_ScopedInstall(StoreStaticShadow, 0x70BA00, { .reversed = false });
    RH_ScopedInstall(StoreShadowForVehicle, 0x70BDA0, { .reversed = false });
    RH_ScopedInstall(StoreCarLightShadow, 0x70C500, { .reversed = false });
    RH_ScopedInstall(StoreShadowForPole, 0x70C750, { .reversed = false });
    RH_ScopedInstall(RenderIndicatorShadow, 0x70CCB0, { .reversed = false });
    RH_ScopedGlobalInstall(ShadowRenderTriangleCB, 0x709CF0, { .reversed = false });
}

// 0x707670
void CStaticShadow::Free() {
    ((void(__thiscall*)(CStaticShadow*))0x707670)(this);
}

// 0x706CD0
void CShadows::Init() {
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(CTxdStore::FindTxdSlot("particle"));

    gpShadowCarTex         = RwTextureRead("shad_car",     nullptr);
    gpShadowPedTex         = RwTextureRead("shad_ped",     nullptr);
    gpShadowHeliTex        = RwTextureRead("shad_heli",    nullptr);
    gpShadowBikeTex        = RwTextureRead("shad_bike",    nullptr);
    gpShadowBaronTex       = RwTextureRead("shad_rcbaron", nullptr);
    gpShadowExplosionTex   = RwTextureRead("shad_exp",     nullptr);
    gpShadowHeadLightsTex  = RwTextureRead("headlight",    nullptr);
    gpShadowHeadLightsTex2 = RwTextureRead("headlight1",   nullptr);
    gpBloodPoolTex         = RwTextureRead("bloodpool_64", nullptr);
    gpHandManTex           = RwTextureRead("handman",      nullptr);
    gpCrackedGlassTex      = RwTextureRead("wincrack_32",  nullptr);
    gpPostShadowTex        = RwTextureRead("lamp_shad_64", nullptr);

    CTxdStore::PopCurrentTxd();

    g_ShadowVertices = { 0, 2, 1, 0, 3, 2, 0, 4, 3, 0, 5, 4, 0, 6, 5, 0, 7, 6, 0, 8, 7, 0, 9, 8 };

    std::ranges::for_each(aStaticShadows, [&](auto& shadow) { shadow.Init(); });

    pEmptyBunchList = aPolyBunches.data();

    for (auto i = 0u; i < aPolyBunches.size() - 1; i++) {
        aPolyBunches[i].m_pNext = &aPolyBunches[i + 1];
    }
    aPolyBunches.back().m_pNext = nullptr;

    std::ranges::for_each(aPermanentShadows, [&](auto& shadow) { shadow.Init(); });
}

// 0x706ED0
void CShadows::Shutdown() {
    RwTextureDestroy(gpShadowCarTex);
    RwTextureDestroy(gpShadowPedTex);
    RwTextureDestroy(gpShadowHeliTex);
    RwTextureDestroy(gpShadowBikeTex);
    RwTextureDestroy(gpShadowBaronTex);
    RwTextureDestroy(gpShadowExplosionTex);
    RwTextureDestroy(gpShadowHeadLightsTex);
    RwTextureDestroy(gpShadowHeadLightsTex2);
    RwTextureDestroy(gpBloodPoolTex);
    RwTextureDestroy(gpHandManTex);
    RwTextureDestroy(gpCrackedGlassTex);
    RwTextureDestroy(gpPostShadowTex);
}

// 0x707770
void CShadows::TidyUpShadows() {
    std::ranges::for_each(aPermanentShadows, [&](auto& shadow) { shadow.m_nType = 0; });
}

// 0x706F60
void CShadows::AddPermanentShadow(uint8 type, RwTexture* texture, CVector* posn, float topX, float topY, float rightX, float rightY, int16 intensity, uint8 red, uint8 greeb, uint8 blue, float drawDistance, uint32 time, float upDistance) {
    ((void(__cdecl*)(uint8, RwTexture*, CVector*, float, float, float, float, int16, uint8, uint8, uint8, float, uint32, float))0x706F60)(type, texture, posn, topX, topY, rightX, rightY, intensity, red, greeb, blue, drawDistance, time, upDistance);
}

// 0x70C950
void CShadows::UpdatePermanentShadows() {
    ((void(__cdecl*)())0x70C950)();
}

// 0x707930
void CShadows::StoreShadowToBeRendered(uint8 type, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue) {
    const auto Store = [=](auto mtype, auto texture) {
        StoreShadowToBeRendered(mtype, texture, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, 15.0f, 0, 1.0f, nullptr, 0);
    };

    switch (type) {
    case SHADOW_DEFAULT:
        Store(SHADOW_TEX_CAR, gpShadowCarTex);
        break;
    case SHADOW_ADDITIVE:
        Store(SHADOW_TEX_CAR, gpShadowPedTex);
        break;
    case SHADOW_INVCOLOR:
        Store(SHADOW_TEX_PED, gpShadowExplosionTex);
        break;
    case SHADOW_OIL_1:
        Store(SHADOW_TEX_CAR, gpShadowHeliTex);
        break;
    case SHADOW_OIL_2:
        Store(SHADOW_TEX_PED, gpShadowHeadLightsTex);
        break;
    case SHADOW_OIL_3:
        Store(SHADOW_TEX_CAR, gpBloodPoolTex);
        break;
    default:
        return;
    }
}

// 0x707390
void CShadows::StoreShadowToBeRendered(uint8 type, RwTexture* texture, CVector* posn, float topX, float topY, float rightX, float rightY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, bool drawOnWater, float scale, CRealTimeShadow* realTimeShadow, bool drawOnBuildings) {
    if (ShadowsStoredToBeRendered >= asShadowsStored.size())
        return;

    auto& shadow = asShadowsStored[ShadowsStoredToBeRendered];

    shadow.m_nType      = type;
    shadow.m_pTexture   = texture;
    shadow.m_vecPosn    = *posn;
    shadow.m_Front.x    = topX;
    shadow.m_Front.y    = topY;
    shadow.m_Side.x     = rightX;
    shadow.m_Side.y     = rightY;
    shadow.m_nIntensity = intensity;
    shadow.m_nRed       = red;
    shadow.m_nGreen     = green;
    shadow.m_nBlue      = blue;
    shadow.m_fZDistance = zDistance;
    shadow.m_bDrawOnWater     = drawOnWater;
    shadow.m_bDrawOnBuildings = drawOnBuildings;
    shadow.m_fScale     = scale;
    shadow.m_pRTShadow  = realTimeShadow;

    ShadowsStoredToBeRendered++;
}

// 0x707460
void CShadows::SetRenderModeForShadowType(eShadowType type) {
    switch (type) {
    case SHADOW_DEFAULT:
    case SHADOW_OIL_1:
    case SHADOW_OIL_2:
    case SHADOW_OIL_3:
    /* case SHADOW_OIL_4: */ // missing
    case SHADOW_OIL_5:
        RwRenderStateSet(rwRENDERSTATESRCBLEND,  RWRSTATE(rwBLENDSRCALPHA));
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDINVSRCALPHA));
        break;
    case SHADOW_ADDITIVE:
        RwRenderStateSet(rwRENDERSTATESRCBLEND,  RWRSTATE(rwBLENDONE));
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDONE));
        break;
    case SHADOW_INVCOLOR:
        RwRenderStateSet(rwRENDERSTATESRCBLEND,  RWRSTATE(rwBLENDZERO));
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDINVSRCCOLOR));
        break;
    default:
        return;
    }
}

// 0x7074F0
void CShadows::RemoveOilInArea(float x1, float x2, float y1, float y2) {
    for (auto& shadow : aPermanentShadows) {
        if (shadow.m_nType == 8 || shadow.m_nType == 4) {
            if (shadow.m_vecPosn.x > x1 &&
                shadow.m_vecPosn.x < x2 &&
                shadow.m_vecPosn.y > y1 &&
                shadow.m_vecPosn.y < y2
            ) {
                shadow.m_nType = 0;
            }
        }
    }
}

// 0x707550
void CShadows::GunShotSetsOilOnFire(const CVector* shotOrigin, const CVector* shotTarget) {
    ((void(__cdecl*)(const CVector*, const CVector*))0x707550)(shotOrigin, shotTarget);
}

// 0x7076B0
void CShadows::PrintDebugPoly(CVector* a, CVector* b, CVector* c) {
    // NOP
}

// 0x7076C0
void CShadows::CalcPedShadowValues(CVector sunPosn, float& displacementX, float& displacementY, float& frontX, float& frontY, float& sideX, float& sideY) {
    const auto sunDist = sunPosn.Magnitude2D();
    const auto recip = 1.0f / sunDist;
    const auto mult = (sunDist + 1.0f) * recip;

    displacementX = -sunPosn.x * mult / 2.0f;
    displacementY = -sunPosn.y * mult / 2.0f;

    frontX = -sunPosn.y * recip / 2.0f;
    frontY = +sunPosn.x * recip / 2.0f;

    sideX = -sunPosn.x / 2.0f;
    sideY = -sunPosn.y / 2.0f;
}

// 0x707850
void CShadows::AffectColourWithLighting(uint8 shadowType, uint8 dayNightIntensity, uint8 red, uint8 green, uint8 blue, uint8* outRed, uint8* outGreen, uint8* outBlue) {
    ((void(__cdecl*)(uint8, uint8, uint8, uint8, uint8, uint8*, uint8*, uint8*))0x707850)(shadowType, dayNightIntensity, red, green, blue, outRed, outGreen, outBlue);
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
void CShadows::CastShadowEntityXY(CEntity* entity, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, uint8* pDayNightIntensity, int32 shadowType) {
    ((void(__cdecl*)(CEntity*, float, float, float, float, CVector*, float, float, float, float, int16, uint8, uint8, uint8, float, float, CPolyBunch**, uint8*, int32))0x7086B0)(entity, conrerAX, cornerAY, cornerBX, cornerBY, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, pDayNightIntensity, shadowType);
}

// 0x70A040
void CShadows::CastShadowEntityXYZ(CEntity* entity, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, CRealTimeShadow* realTimeShadow) {
    ((void(__cdecl*)(CEntity*, CVector*, float, float, float, float, int16, uint8, uint8, uint8, float, float, CPolyBunch**, CRealTimeShadow*))0x70A040)(entity, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, realTimeShadow);
}

// 0x70A470
void CShadows::CastPlayerShadowSectorList(CPtrList& ptrList, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, uint8* pDayNightIntensity, int32 shadowType) {
    ((void(__cdecl*)(CPtrList&, float, float, float, float, CVector*, float, float, float, float, int16, uint8, uint8, uint8, float, float, CPolyBunch**, uint8*, int32))0x70A470)(ptrList, conrerAX, cornerAY, cornerBX, cornerBY, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, pDayNightIntensity, shadowType);
}

// 0x70A630
void CShadows::CastShadowSectorList(CPtrList& ptrList, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, uint8* pDayNightIntensity, int32 shadowType) {
    ((void(__cdecl*)(CPtrList&, float, float, float, float, CVector*, float, float, float, float, int16, uint8, uint8, uint8, float, float, CPolyBunch**, uint8*, int32))0x70A630)(ptrList, conrerAX, cornerAY, cornerBX, cornerBY, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, pDayNightIntensity, shadowType);
}

// 0x70A7E0
void CShadows::CastRealTimeShadowSectorList(CPtrList& ptrList, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, CRealTimeShadow* realTimeShadow, uint8* pDayNightIntensity) {
    ((void(__cdecl*)(CPtrList&, float, float, float, float, CVector*, float, float, float, float, int16, uint8, uint8, uint8, float, float, CPolyBunch**, CRealTimeShadow*, uint8*))0x70A7E0)(ptrList, conrerAX, cornerAY, cornerBX, cornerBY, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistance, scale, ppPolyBunch, realTimeShadow, pDayNightIntensity);
}

// 0x70A960
void CShadows::RenderStoredShadows() {
    ((void(__cdecl*)())0x70A960)();
}

// 0x70B730
void CShadows::GeneratePolysForStaticShadow(int16 staticShadowIndex) {
    ((void(__cdecl*)(int16))0x70B730)(staticShadowIndex);
}

// 0x70BA00
bool CShadows::StoreStaticShadow(uint32 id, eShadowType type, RwTexture* texture, const CVector& posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistane, float scale, float drawDistance, bool temporaryShadow, float upDistance) {
    return ((bool(__cdecl*)(uint32, eShadowType, RwTexture*, const CVector&, float, float, float, float, int16, uint8, uint8, uint8, float, float, float, bool, float))0x70BA00)(
        id, type, texture, posn, frontX, frontY, sideX, sideY, intensity, red, green, blue, zDistane, scale, drawDistance, temporaryShadow, upDistance);
}

// 0x70BDA0
void CShadows::StoreShadowForVehicle(CVehicle* vehicle, VEH_SHD_TYPE vehShadowType) {
    ((void(__cdecl*)(CVehicle*, VEH_SHD_TYPE))0x70BDA0)(vehicle, vehShadowType);
}

// 0x70C500
void CShadows::StoreCarLightShadow(CVehicle* vehicle, int32 id, RwTexture* texture, CVector* posn, float frontX, float frontY, float sideX, float sideY, uint8 red, uint8 green, uint8 blue, float maxViewAngle) {
    ((void(__cdecl*)(CVehicle*, int32, RwTexture*, CVector*, float, float, float, float, uint8, uint8, uint8, float))0x70C500)(vehicle, id, texture, posn, frontX, frontY, sideX, sideY, red, green, blue, maxViewAngle);
}

// 0x70C750
void CShadows::StoreShadowForPole(CEntity* entity, float offsetX, float offsetY, float offsetZ, float poleHeight, float poleWidth, uint32 localId) {
    ((void(__cdecl*)(CEntity*, float, float, float, float, float, uint32))0x70C750)(entity, offsetX, offsetY, offsetZ, poleHeight, poleWidth, localId);
}

// 0x70CCB0
void CShadows::RenderIndicatorShadow(uint32 id, uint8 shadowType, RwTexture* texture, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity) {
    ((void(__cdecl*)(uint32, uint8, RwTexture*, CVector*, float, float, float, float, int16))0x70CCB0)(id, shadowType, texture, posn, frontX, frontY, sideX, sideY, intensity);

    /*
    CVector out = posn;
    float size  = frontX <= (float)(-sideY) ? -sideY : frontX;

    C3dMarkers::PlaceMarkerSet(id, 1u, out, size * 0.8f, 255, 0, 0, 255u, 2048, 0.2f, 0);
    C3dMarkers::PlaceMarkerSet(id, 1u, out, size * 0.9f, 255, 0, 0, 255u, 2048, 0.2f, 0);
    C3dMarkers::PlaceMarkerSet(id, 1u, out, size,        255, 0, 0, 255u, 2048, 0.2f, 0);
    */
}

// 0x709CF0
#ifdef _MSC_VER
CVector* ShadowRenderTriangleCB(CVector* normal, CVector* trianglePos, _ProjectionParam* param) {
    CVector* result = nullptr;
    __asm mov eax, normal
    __asm mov ebx, trianglePos
    __asm mov edi, param
    __asm mov ecx, 0x709CF0
    __asm call ecx
    __asm mov result, eax
    return result;
}
#endif
