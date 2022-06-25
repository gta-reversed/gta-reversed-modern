/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "common.h"
#include "GxtChar.h"
#include "CDebugMenu.h"
#include "CarCtrl.h"
#include "ColourSet.h"
#include "GxtChar.h"
#include "UserDisplay.h"
#include "PostEffects.h"
#include "SpecialFX.h"

int32& g_nNumIm3dDrawCalls = *(int32*)0xB73708;
int32 gDefaultTaskTime = 9999999; // or 0x98967F a.k.a (one milllion - 1)

float &GAME_GRAVITY = *(float *)0x863984;

char(&PC_Scratch)[16384] = *(char(*)[16384])0xC8E0C8;

RpLight* (&pExtraDirectionals)[6] = *reinterpret_cast<RpLight* (*)[6]>(0xC886F0);
int32& numExtraDirectionalLights = *reinterpret_cast<int32*>(0xC88708);

RwV3d& sun2Dir = *reinterpret_cast<RwV3d*>(0xB7CB14);

RwRGBAReal& FullLight = *reinterpret_cast<RwRGBAReal*>(0x8D60C0); //  <1.0, 1.0, 1.0, 1.0>

char (&IndicateR)[8] = *reinterpret_cast<char (*)[8]>(0x8D60D0);
char (&IndicateG)[8] = *reinterpret_cast<char (*)[8]>(0x8D60D8);
char (&IndicateB)[8] = *reinterpret_cast<char (*)[8]>(0x8D60E0);

RpLight*& pAmbient = *reinterpret_cast<RpLight**>(0xC886E8);
RwRGBAReal& AmbientLightColour = *reinterpret_cast<RwRGBAReal*>(0xC886A4);
RwRGBAReal& AmbientLightColourForFrame = *reinterpret_cast<RwRGBAReal*>(0xC886D4);
RwRGBAReal& AmbientLightColourForFrame_PedsCarsAndObjects = *reinterpret_cast<RwRGBAReal*>(0xC886C4);
RpLight*& pDirect = *reinterpret_cast<RpLight**>(0xC886EC);
RwRGBAReal& DirectionalLightColour = *reinterpret_cast<RwRGBAReal*>(0xC88694);
RwRGBAReal& DirectionalLightColourForFrame = *reinterpret_cast<RwRGBAReal*>(0xC886B4);

RwRGBAReal (&DirectAmbientLight)[2] = *reinterpret_cast<RwRGBAReal (*)[2]>(0xC8865C); // Direct, Ambient Light

float& gfLaRiotsLightMult = *(float*)0x8CD060; // 1.0f

uint32 &ClumpOffset = *(uint32 *)0xB5F878;

void InjectCommonHooks() {
    RH_ScopedNamespaceName("Common");
    RH_ScopedCategory("Common");

    RH_ScopedGlobalInstall(FindPlayerCoors, 0x56E010);
    RH_ScopedGlobalInstall(FindPlayerSpeed, 0x56E090);
    RH_ScopedGlobalInstall(FindPlayerEntity, 0x56E120);
    RH_ScopedGlobalInstall(FindPlayerTrain, 0x56E160);
    RH_ScopedGlobalInstall(FindPlayerCentreOfWorld, 0x56E250);
//    RH_ScopedGlobalInstall(FindPlayerCentreOfWorld_NoSniperShift, 0x56E320);
//    RH_ScopedGlobalInstall(FindPlayerCentreOfWorld_NoInteriorShift, 0x56E400);
    RH_ScopedGlobalInstall(FindPlayerHeading, 0x56E450);
    RH_ScopedGlobalInstall(FindPlayerPed, 0x56E210);
    RH_ScopedGlobalInstall(FindPlayerVehicle, 0x56E0D0);
    RH_ScopedGlobalInstall(FindPlayerWanted, 0x56E230);

    RH_ScopedGlobalInstall(MakeUpperCase, 0x7186E0);
    RH_ScopedGlobalInstall(GetEventGlobalGroup, 0x4ABA50);
    RH_ScopedGlobalInstall(DefinedState, 0x734650);
    RH_ScopedGlobalInstall(DefinedState2d, 0x734750);

    RH_ScopedGlobalInstall(GetNameAndDamage, 0x5370A0);
    RH_ScopedGlobalInstall(GetFirstAtomicCallback, 0x734810);
    RH_ScopedGlobalInstall(GetFirstAtomic, 0x734820);
//    RH_ScopedGlobalInstall(Get2DEffectAtomicCallback, 0x734850);
    RH_ScopedGlobalInstall(Get2DEffectAtomic, 0x734880);
    RH_ScopedGlobalInstall(GetFirstObjectCallback, 0x7348B0);
    RH_ScopedGlobalInstall(GetFirstObject, 0x7348C0);
    RH_ScopedGlobalInstall(GetFirstFrameCallback, 0x7348F0);
    RH_ScopedGlobalInstall(GetFirstChild, 0x734900);
//    RH_ScopedGlobalInstall(GetFirstTextureCallback, 0x734930);
//    RH_ScopedGlobalInstall(GetFirstTexture, 0x734940);
    RH_ScopedGlobalInstall(SkinAtomicGetHAnimHierarchCB, 0x734A20);
    RH_ScopedGlobalInstall(GetAnimHierarchyFromSkinClump, 0x734A40);
//    RH_ScopedGlobalInstall(GetAnimHierarchyFromFrame, 0x734AB0);
    RH_ScopedGlobalInstall(GetAnimHierarchyFromClump, 0x734B10);
    RH_ScopedGlobalInstall(AtomicRemoveAnimFromSkinCB, 0x734B90);
    RH_ScopedGlobalInstall(RpAtomicConvertGeometryToTL, 0x734BE0);
    RH_ScopedGlobalInstall(RpAtomicConvertGeometryToTS, 0x734C20);

    RH_ScopedGlobalInstall(atomicConvertGeometryToTL, 0x734C60);
    RH_ScopedGlobalInstall(RpClumpConvertGeometryToTL, 0x734CB0);

    RH_ScopedGlobalInstall(atomicConvertGeometryToTS, 0x734CE0);
    RH_ScopedGlobalInstall(RpClumpConvertGeometryToTS, 0x734D30);

    RH_ScopedGlobalInstall(forceLinearFilteringAtomicsCB, 0x734DA0);
    RH_ScopedGlobalInstall(SetFilterModeOnClumpsTextures, 0x734DC0);


    RH_ScopedGlobalInstall(forceLinearFilteringMatTexturesCB, 0x734D60);
    RH_ScopedGlobalInstall(SetFilterModeOnAtomicsTextures, 0x734D80);

    RH_ScopedGlobalInstall(SetLightsWithTimeOfDayColour, 0x7354E0);
    RH_ScopedGlobalInstall(LightsCreate, 0x5BA520);
    RH_ScopedGlobalInstall(LightsDestroy, 0x735730);
    RH_ScopedGlobalInstall(WorldReplaceNormalLightsWithScorched, 0x7357E0);
//    RH_ScopedGlobalInstall(AddAnExtraDirectionalLight, 0x735840);
    RH_ScopedGlobalInstall(RemoveExtraDirectionalLights, 0x7359E0);
    RH_ScopedGlobalInstall(SetBrightMarkerColours, 0x735BD0);
    RH_ScopedGlobalInstall(ReSetAmbientAndDirectionalColours, 0x735C40);
    RH_ScopedGlobalInstall(DeActivateDirectional, 0x735C70);
    RH_ScopedGlobalInstall(ActivateDirectional, 0x735C80);
    RH_ScopedGlobalOverloadedInstall(SetAmbientColours, "void", 0x735D30, void(*)());
    RH_ScopedGlobalOverloadedInstall(SetAmbientColours, "color", 0x735D50, void(*)(RwRGBAReal* color));
    RH_ScopedGlobalInstall(SetDirectionalColours, 0x735D70);
    RH_ScopedGlobalInstall(SetLightColoursForPedsCarsAndObjects, 0x735D90);
    RH_ScopedGlobalInstall(SetLightsForInfraredVisionHeatObjects, 0x735E40);
    RH_ScopedGlobalInstall(StoreAndSetLightsForInfraredVisionHeatObjects, 0x735E70);
    RH_ScopedGlobalInstall(RestoreLightsForInfraredVisionHeatObjects, 0x735EF0);
    RH_ScopedGlobalInstall(SetLightsForInfraredVisionDefaultObjects, 0x735F20);
    RH_ScopedGlobalInstall(SetLightsForNightVision, 0x735F70);
    RH_ScopedGlobalInstall(GetDayNightBalance, 0x6FAB30);
    RH_ScopedGlobalInstall(AsciiToGxtChar, 0x718600);
    RH_ScopedGlobalInstall(WriteRaster, 0x005A4150);
    // RH_ScopedOverloadedInstall(CalcScreenCoors, "VVff", 0x71DA00, bool(*)(const CVector&, CVector*, float*, float*));
    // RH_ScopedOverloadedInstall(CalcScreenCoors, "VV", 0x71DAB0, bool(*)(const CVector&, CVector*));
    RH_ScopedGlobalInstall(LittleTest, 0x541330);

    RH_ScopedGlobalInstall(RemoveRefsCB, 0x7226D0);
    RH_ScopedGlobalInstall(IsGlassModel, 0x46A760);
}

void MessageLoop() {
    tagMSG msg;
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE | PM_NOYIELD)) {
        if (msg.message == WM_QUIT) {
            RsGlobal.quit = true;
        } else {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }
}

// 0x56E010
CVector FindPlayerCoors(int32 playerId) {
    if (CEntity* e = FindPlayerEntity(playerId))
        return e->GetPosition();
    return {};
}

// 0x56E090
CVector& FindPlayerSpeed(int32 playerId) {
    return static_cast<CPhysical*>(FindPlayerEntity(playerId))->m_vecMoveSpeed;
}

// 0x56E120
CEntity* FindPlayerEntity(int32 playerId) {
    if (auto player = FindPlayerPed(playerId)) {
        if (player->bInVehicle && player->m_pVehicle)
            return player->m_pVehicle;
        return player;
    }
    return nullptr;
}

// 0x56E160
CTrain* FindPlayerTrain(int32 playerId) {
    auto vehicle = FindPlayerVehicle(playerId);
    if (vehicle && vehicle->IsTrain())
        return vehicle->AsTrain();
    else
        return nullptr;
}

// 0x56E250
const CVector& FindPlayerCentreOfWorld(int32 playerId) {
    if (CCarCtrl::bCarsGeneratedAroundCamera)
        return TheCamera.GetPosition();

    if (CVehicle* vehicle = FindPlayerVehicle(playerId, true))
        return vehicle->GetPosition();

    return FindPlayerPed(playerId)->GetPosition();
}

// 0x56E320
const CVector& FindPlayerCentreOfWorld_NoSniperShift(int32 playerId) {
    return ((const CVector&(__cdecl*)(int32))0x56E320)(playerId);
}

// 0x56E400
CVector FindPlayerCentreOfWorld_NoInteriorShift(int32 playerId) {
    return ((CVector(__cdecl*)(int32))0x56E400)(playerId);
}

// 0x56E450
float FindPlayerHeading(int32 playerId) {
    if (CVehicle* veh = FindPlayerVehicle(playerId, true))
        return veh->GetHeading();
    return FindPlayerPed(playerId)->GetHeading();
}

// unused
// 0x56E520
float FindPlayerHeight() {
    CPlayerPed* ped = CWorld::Players[CWorld::PlayerInFocus].m_pPed;
    CMatrixLink* matrix = ped->m_matrix;
    if (matrix)
        return matrix->GetPosition().z;
    else
        return ped->m_placement.m_vPosn.z;
}

// 0x56E210
CPlayerPed* FindPlayerPed(int32 playerId) {
    return FindPlayerInfo(playerId).m_pPed;
}

// Returns player vehicle
// 0x56E0D0
CVehicle* FindPlayerVehicle(int32 playerId, bool bIncludeRemote) {
    CPlayerPed* player = FindPlayerPed(playerId);
    if (!player || !player->bInVehicle)
        return nullptr;

    if (bIncludeRemote) {
        CPlayerInfo* playerInfo = player->GetPlayerInfoForThisPlayerPed();
        if (playerInfo->m_pRemoteVehicle)
            return playerInfo->m_pRemoteVehicle;
    }

    return player->m_pVehicle;
}

// 0x56E230
CWanted* FindPlayerWanted(int32 playerId) {
    return FindPlayerInfo(playerId).m_PlayerData.m_pWanted;
}


CPedGroup& FindPlayerGroup(int32 playerId) {
    return FindPlayerPed()->GetGroup();
}

// NOTSA, inlined
CPlayerInfo& FindPlayerInfo(int playerId) {
    return CWorld::Players[playerId < 0 ? CWorld::PlayerInFocus : playerId];
}

// NOTE: This function doesn't add m.GetPosition() like
//       MultiplyMatrixWithVector @ 0x59C890 does.
CVector Multiply3x3(const CMatrix& constm, const CVector& v) {
    auto& m = const_cast<CMatrix&>(constm);
    return {
        m.GetRight().x * v.x + m.GetForward().x * v.y + m.GetUp().x * v.z,
        m.GetRight().y * v.x + m.GetForward().y * v.y + m.GetUp().y * v.z,
        m.GetRight().z * v.x + m.GetForward().z * v.y + m.GetUp().z * v.z,
    };
}

// vector by matrix mult, resulting in a vector where each component is the dot product of the in vector and a matrix direction
CVector Multiply3x3(const CVector& v, const CMatrix& constm) {
    auto& m = const_cast<CMatrix&>(constm);
    return {
        DotProduct(m.GetRight(), v),
        DotProduct(m.GetForward(), v),
        DotProduct(m.GetUp(), v)
    };
}

CVector MultiplyMatrixWithVector(const CMatrix& mat, const CVector& vec) {
    return const_cast<CMatrix&>(mat).GetPosition() + Multiply3x3(const_cast<CMatrix&>(mat), vec);
}

CVector MultiplyMatrixWithVector(CMatrix& m, const CVector& v) {
    return m.GetPosition() + Multiply3x3(m, v);
}

// 0x54ECE0
void TransformPoint(RwV3d& point, const CSimpleTransform& placement, const RwV3d& vecPos) {
    plugin::Call<0x54ECE0, RwV3d&, const CSimpleTransform&, const RwV3d&>(point, placement, vecPos);
}

// 0x54EEA0
void TransformVectors(RwV3d* vecsOut, int32 numVectors, const CMatrix& matrix, const RwV3d* vecsin) {
    plugin::Call<0x54EEA0, RwV3d*, int32, const CMatrix&, const RwV3d*>(vecsOut, numVectors, matrix, vecsin);
}

// 0x54EE30
void TransformVectors(RwV3d* vecsOut, int32 numVectors, const CSimpleTransform& transform, const RwV3d* vecsin) {
    plugin::Call<0x54EE30, RwV3d*, int32, const CSimpleTransform&, const RwV3d*>(vecsOut, numVectors, transform, vecsin);
}

// 0x4D62A0
AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, char* name) {
    return ((AnimBlendFrameData * (__cdecl*)(RpClump*, char*))0x4D62A0)(clump, name);
}

char ToUpper(char ch) {
    return (ch >= 'a' && ch <= 'z') ? ch - ('a' - 'A') : ch;
}

// 0x7186E0
char* MakeUpperCase(char* dest, const char * src) {
    for (; *src; src++, dest++)
        *dest = ToUpper(*src);
    *dest = 0;
    return dest;
}

// NOTSA
bool EndsWith(const char* str, const char* with, bool caseSensitive) {
    const auto strsz = strlen(str), withsz = strlen(with);
    assert(strsz >= withsz);
    return (caseSensitive ? strncmp : _strnicmp)(str + strsz - withsz, with, withsz) == 0;
}

// 0x4ABA50
CEventGlobalGroup* GetEventGlobalGroup() {
    static CEventGlobalGroup*& globalEvents = *(CEventGlobalGroup**)0xA9AF6C;

    if (globalEvents)
        return globalEvents;

    globalEvents = new CEventGlobalGroup(nullptr);
    return globalEvents;
}

// 0x734650
void DefinedState() {
    CRGBA rgbaFog(
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomRed,
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomBlue
    );

    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE,   RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            RWRSTATE(rwSHADEMODEGOURAUD));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEBORDERCOLOR,          RWRSTATE((RWRGBALONG(0, 0, 0, 255))));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEFOGCOLOR,             RWRSTATE(rgbaFog.ToIntARGB()));
    RwRenderStateSet(rwRENDERSTATEFOGTYPE,              RWRSTATE(rwFOGTYPELINEAR));
    RwRenderStateSet(rwRENDERSTATECULLMODE,             RWRSTATE(rwCULLMODECULLNONE));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(2)); // TODO: ?
}

// 0x734750
void DefinedState2d() {
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE,   RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            RWRSTATE(rwSHADEMODEGOURAUD));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEBORDERCOLOR,          RWRSTATE((RWRGBALONG(0, 0, 0, 255))));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATECULLMODE,             RWRSTATE(rwCULLMODECULLNONE));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(2)); // TODO: ?
}

// todo: move
// 0x53D690
void DoRWStuffStartOfFrame(int16 nR1, int16 nG1, int16 nB1, int16 nR2, int16 nG2, int16 nB2, int16 nA) {
    plugin::Call<0x53D690, int16, int16, int16, int16, int16, int16, int16>(nR1, nG1, nB1, nR2, nG2, nB2, nA);
}

// todo: move
// 0x53D840
void DoRWStuffEndOfFrame() {
    plugin::Call<0x53D840>();
}

// TODO: Check `outName` size (to avoid buffer overflow)
// 0x5370A0
void GetNameAndDamage(const char* nodeName, char* outName, bool& outDamage) {
    const size_t nodesz = strlen(nodeName);

    const auto TerminatedCopy = [=](size_t offset) {
        strncpy(outName, nodeName, nodesz - offset);
        outName[nodesz - offset] = 0;
    };

    // EndsWith "_dam"
    if (nodeName[nodesz - 4] == '_' &&
        nodeName[nodesz - 3] == 'd' &&
        nodeName[nodesz - 2] == 'a' &&
        nodeName[nodesz - 1] == 'm'
    ) {
        outDamage = true;
        TerminatedCopy(sizeof("_dam") - 1);
    }
    else {
        outDamage = false;
        // EndsWith "_l0" or "_L0"
        if (
            nodeName[nodesz - 3] == '_' &&
            (nodeName[nodesz - 2] == 'L' || nodeName[nodesz - 2] == 'l') &&
            nodeName[nodesz - 1] == '0'
        ) {
            TerminatedCopy(sizeof("_l0") - 1);
        } else
            strcpy(outName, nodeName);
    }
}

// 0x734810
RpAtomic* GetFirstAtomicCallback(RpAtomic* atomic, void* data) {
    *(RpAtomic**)(data) = atomic;
    return nullptr;
}

// 0x734820
RpAtomic* GetFirstAtomic(RpClump* clump) {
    RpAtomic* atomic{};
    RpClumpForAllAtomics(clump, GetFirstAtomicCallback, &atomic);
    return atomic;
}

// 0x734850
RpAtomic* Get2DEffectAtomicCallback(RpAtomic* atomic, void* data) {
    return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x734850)(atomic, data);
}

// 0x734880
RpAtomic* Get2DEffectAtomic(RpClump* clump) {
    RpAtomic* atomic{};
    RpClumpForAllAtomics(clump, Get2DEffectAtomicCallback, &atomic);
    return atomic;
}

// 0x7348B0
RwObject* GetFirstObjectCallback(RwObject* object, void* data) {
    *(RwObject**)(data) = object;
    return nullptr;
}

// 0x7348C0
RwObject* GetFirstObject(RwFrame* frame) {
    RwObject* obj{};
    RwFrameForAllObjects(frame, GetFirstObjectCallback, &obj);
    return obj;
}

// 0x7348F0
RwFrame* GetFirstFrameCallback(RwFrame* frame, void* data) {
    *(RwFrame**)(data) = frame;
    return nullptr;
}

// 0x734900
RwFrame* GetFirstChild(RwFrame* frame) {
    RwFrame* child{};
    RwFrameForAllChildren(frame, GetFirstFrameCallback, &child);
    return child;
}

// name not from Android
// 0x734A20
RpAtomic* SkinAtomicGetHAnimHierarchCB(RpAtomic* atomic, void* data) {
    *(RpHAnimHierarchy**)(data) = RpSkinAtomicGetHAnimHierarchy(atomic);
    return nullptr;
}

// 0x734A40
RpHAnimHierarchy* GetAnimHierarchyFromSkinClump(RpClump* clump) {
    RpHAnimHierarchy* bugstarDevFrom2003{};
    RpClumpForAllAtomics(clump, SkinAtomicGetHAnimHierarchCB, &bugstarDevFrom2003);
    return bugstarDevFrom2003;
}

// 0x734AB0
RpHAnimHierarchy* GetAnimHierarchyFromFrame(RwFrame* frame) {
    return ((RpHAnimHierarchy* (__cdecl *)(RwFrame*))0x734AB0)(frame);
}

// 0x734B10
RpHAnimHierarchy* GetAnimHierarchyFromClump(RpClump* clump) {
    return GetAnimHierarchyFromFrame(RpClumpGetFrame(clump));
}

// 0x734B90
RpAtomic* AtomicRemoveAnimFromSkinCB(RpAtomic* atomic, void* data) {
    if (RpSkinGeometryGetSkin(RpAtomicGetGeometry(atomic))) {
        if (RpHAnimHierarchy* hier = RpSkinAtomicGetHAnimHierarchy(atomic)) {
            RtAnimAnimation*& pCurrAnim = hier->currentAnim->pCurrentAnim;
            if (pCurrAnim)
                RtAnimAnimationDestroy(pCurrAnim);
            pCurrAnim = nullptr;
        }
    }
    return atomic;
}

// 0x734BE0
bool RpAtomicConvertGeometryToTL(RpAtomic* atomic) {
    RpGeometry* geometry = RpAtomicGetGeometry(atomic);

    auto flags = RpGeometryGetFlags(geometry);
    if (flags & rpGEOMETRYNATIVE || !(flags & rpGEOMETRYTRISTRIP))
        return false;

    RpGeometryLock(geometry, rpGEOMETRYLOCKALL);
    RpGeometrySetFlags(geometry, flags & ~rpGEOMETRYTRISTRIP);
    RpGeometryUnlock(geometry);

    return true;
}

// 0x734C20
bool RpAtomicConvertGeometryToTS(RpAtomic* atomic) {
    RpGeometry* geometry = RpAtomicGetGeometry(atomic);

    auto flags = RpGeometryGetFlags(geometry);
    if (flags & rpGEOMETRYNATIVE || flags & rpGEOMETRYTRISTRIP)
        return false;

    RpGeometryLock(geometry, rpGEOMETRYLOCKALL);
    RpGeometrySetFlags(geometry, flags | rpGEOMETRYTRISTRIP);
    RpGeometryUnlock(geometry);

    return true;
}

// 0x734C60
RpAtomic* atomicConvertGeometryToTL(RpAtomic* atomic, void* data) {
    if (!RpAtomicConvertGeometryToTL(atomic)) {
        *(bool*)(data) = false;
    }
    return atomic;
}

// 0x734CB0
bool RpClumpConvertGeometryToTL(RpClump* clump) {
    bool success{ true };
    RpClumpForAllAtomics(clump, atomicConvertGeometryToTL, &success);
    return success;
}

// 0x734CE0
RpAtomic* atomicConvertGeometryToTS(RpAtomic* atomic, void* data) {
    if (!RpAtomicConvertGeometryToTS(atomic)) {
        *(bool*)(data) = false;
    }
    return atomic;
}

// 0x734D30
bool RpClumpConvertGeometryToTS(RpClump* clump) {
    bool success{ true };
    RpClumpForAllAtomics(clump, atomicConvertGeometryToTS, &success);
    return success;
}

// 0x734D60
RpMaterial* forceLinearFilteringMatTexturesCB(RpMaterial* material, void* data) {
    if (RwTexture* tex = RpMaterialGetTexture(material))
        RwTextureSetFilterMode(tex, (RwTextureFilterMode)((unsigned)data));
    return material;
}

// 0x734D80
bool SetFilterModeOnAtomicsTextures(RpAtomic* atomic, RwTextureFilterMode filtering) {
    RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), forceLinearFilteringMatTexturesCB, (void*)(unsigned)filtering);
    return true;
}

// 0x734DA0
RpAtomic* forceLinearFilteringAtomicsCB(RpAtomic* atomic, void* data) {
    SetFilterModeOnAtomicsTextures(atomic, (RwTextureFilterMode)((unsigned)data));
    return atomic;
}

// 0x734DC0
bool SetFilterModeOnClumpsTextures(RpClump* clump, RwTextureFilterMode filtering) {
    RpClumpForAllAtomics(clump, forceLinearFilteringAtomicsCB, (void*)(unsigned)filtering);
    return true;
}

// 0x734DE0
bool RpGeometryReplaceOldMaterialWithNewMaterial(RpGeometry* geometry, RpMaterial* oldMaterial, RpMaterial* newMaterial) {
    return ((bool(__cdecl *)(RpGeometry*, RpMaterial*, RpMaterial*))0x734DE0)(geometry, oldMaterial, newMaterial);
}

// 0x734E50
RwTexture* RwTexDictionaryFindHashNamedTexture(RwTexDictionary* txd, uint32 hash) {
    return ((RwTexture* (__cdecl *)(RwTexDictionary*, uint32))0x734E50)(txd, hash);
}

// 0x734FC0
RpClump* RpClumpGetBoundingSphere(RpClump* clump, RwSphere* bound, bool arg2) {
    return ((RpClump* (__cdecl *)(RpClump*, RwSphere*, bool))0x734FC0)(clump, bound, arg2);
}

// 0x735140
void SkinGetBonePositions(RpClump* clump) {
    ((void(__cdecl *)(RpClump*))0x735140)(clump);
}

// 0x7352D0
void SkinSetBonePositions(RpClump* clump) {
    ((void(__cdecl *)(RpClump*))0x7352D0)(clump);
}

// 0x735360
void SkinGetBonePositionsToTable(RpClump* clump, RwV3d* table) {
    ((void(__cdecl *)(RpClump*, RwV3d*))0x735360)(clump, table);
}

// 0x7354E0
void SetLightsWithTimeOfDayColour(RpWorld* world) {
    assert(world);
    if (pAmbient) {
        AmbientLightColourForFrame.red   = CTimeCycle::GetAmbientRed() * CCoronas::LightsMult;
        AmbientLightColourForFrame.green = CTimeCycle::GetAmbientGreen() * CCoronas::LightsMult;
        AmbientLightColourForFrame.blue  = CTimeCycle::GetAmbientBlue() * CCoronas::LightsMult;

        AmbientLightColourForFrame_PedsCarsAndObjects.red   = CTimeCycle::GetAmbientRed_Obj()   * CCoronas::LightsMult;
        AmbientLightColourForFrame_PedsCarsAndObjects.green = CTimeCycle::GetAmbientGreen_Obj() * CCoronas::LightsMult;
        AmbientLightColourForFrame_PedsCarsAndObjects.blue  = CTimeCycle::GetAmbientBlue_Obj()  * CCoronas::LightsMult;

        if (CWeather::LightningFlash) {
            AmbientLightColourForFrame.blue  = 1.0f;
            AmbientLightColourForFrame.green = 1.0f;
            AmbientLightColourForFrame.red   = 1.0f;
            AmbientLightColourForFrame_PedsCarsAndObjects.blue  = 1.0f;
            AmbientLightColourForFrame_PedsCarsAndObjects.green = 1.0f;
            AmbientLightColourForFrame_PedsCarsAndObjects.red   = 1.0f;
        }
        RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
    }

    if (pDirect) {
        const float color = CTimeCycle::m_CurrentColours.m_fIllumination * 0.99609375f * CCoronas::LightsMult;
        DirectionalLightColourForFrame.red   = color;
        DirectionalLightColourForFrame.green = color;
        DirectionalLightColourForFrame.blue  = color;
        RpLightSetColor(pDirect, &DirectionalLightColourForFrame);

        CVector vecDir   = CTimeCycle::m_vecDirnLightToSun;
        CVector vecUp    = CrossProduct(CVector(0, 0, 1), vecDir);
        vecUp.Normalise();
        CVector vecRight = CrossProduct(vecUp, vecDir);

        RwMatrix mxTransform;
        mxTransform.right = vecRight;
        mxTransform.up    = vecUp;
        mxTransform.at    = -vecDir;
        RwFrameTransform(RpLightGetFrame(pDirect), &mxTransform, rwCOMBINEREPLACE);
    }
}

// 0x735720 unused
void LightsEnable(int32 arg0) {
    // NOP
}

// 0x5BA520
void LightsCreate(RpWorld* world) {
    if (!world) {
        return;
    }

    RwRGBAReal color;

    pAmbient = RpLightCreate(rpLIGHTAMBIENT);
    RpLightSetFlags(pAmbient, rpLIGHTLIGHTATOMICS);
    color.red   = 0.25f;
    color.green = 0.25f;
    color.blue  = 0.20f;
    RpLightSetColor(pAmbient, &color);

    pDirect = RpLightCreate(rpLIGHTDIRECTIONAL);
    RpLightSetFlags(pDirect, rpLIGHTLIGHTATOMICS);
    color.red   = 1.00f;
    color.green = 0.85f;
    color.blue  = 0.45f;
    RpLightSetColor(pDirect, &color);
    RpLightSetRadius(pDirect, 2.0f);

    RwFrame* frame = RwFrameCreate();
    rwObjectHasFrameSetFrame(pDirect, frame);
    RwV3d _vecLight = { 1.0f, 1.0f, 0.0f };
    RwFrameRotate(frame, &_vecLight, 160.0f, rwCOMBINEPRECONCAT);

    RpWorldAddLight(world, pAmbient);
    RpWorldAddLight(world, pDirect);

    for (auto& light : pExtraDirectionals) {
        light = RpLightCreate(rpLIGHTDIRECTIONAL);
        RpLightSetFlags(light, NULL);

        color.red   = 1.0f;
        color.green = 0.5f;
        color.blue  = 0.0f;
        RpLightSetColor(light, &color);
        RpLightSetRadius(light, 2.0f);
        rwObjectHasFrameSetFrame(light, RwFrameCreate());

        RpWorldAddLight(world, light);
    }
}

// 0x735730
void LightsDestroy(RpWorld* world) {
    if (!world) {
        return;
    }

    if (pAmbient) {
        RpWorldRemoveLight(world, pAmbient);
        RpLightDestroy(pAmbient);
        pAmbient = nullptr;
    }

    if (pDirect) {
        RpWorldRemoveLight(world, pDirect);
        RwFrameDestroy(RpLightGetFrame(pDirect));
        RpLightDestroy(pDirect);
        pDirect = nullptr;
    }

    for (auto& light : pExtraDirectionals) {
        RpWorldRemoveLight(world, light);
        RwFrameDestroy(RpLightGetFrame(light));
        RpLightDestroy(light);
        light = nullptr;
    }
}

// lighting = [ 0.0f; 1.0f ]
// 0x7357E0
void WorldReplaceNormalLightsWithScorched(RpWorld* world, float lighting) {
    RwRGBAReal color{lighting, lighting, lighting};
    RpLightSetColor(pAmbient, &color);
    DeActivateDirectional();
}

// unused
// 0x735820
void WorldReplaceScorchedLightsWithNormal(RpWorld* world) {
    RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
    ActivateDirectional();
}

// 0x735840
void AddAnExtraDirectionalLight(RpWorld* world, float x, float y, float z, float red, float green, float blue) {
    ((void(__cdecl *)(RpWorld*, float, float, float, float, float, float))0x735840)(world, x, y, z, red, green, blue);
}

// 0x7359E0
void RemoveExtraDirectionalLights(RpWorld* world) {
    for (auto& light : pExtraDirectionals) {
        RpLightSetFlags(light, 0x0);
    }
    numExtraDirectionalLights = 0;
}

// fMult = [ 0.0f; 1.0f ]
// used in SetFlashyColours and SetFlashyColours_Mild which unused
// 0x735A20
void SetAmbientAndDirectionalColours(float fMult) {
    AmbientLightColour.red       = fMult * AmbientLightColourForFrame.red;
    AmbientLightColour.green     = fMult * AmbientLightColourForFrame.green;
    AmbientLightColour.blue      = fMult * AmbientLightColourForFrame.blue;

    DirectionalLightColour.red   = fMult * DirectionalLightColourForFrame.red;
    DirectionalLightColour.green = fMult * DirectionalLightColourForFrame.green;
    DirectionalLightColour.blue  = fMult * DirectionalLightColourForFrame.blue;

    RpLightSetColor(pAmbient, &AmbientLightColour);
    RpLightSetColor(pDirect, &DirectionalLightColour);
}

// fMult = [ 0.0f; 1.0f ]
// 0x735AB0 unused
void SetFlashyColours(float fMult) {
    if (CTimer::GetTimeInMS() & 0x100) {
        AmbientLightColour.red   = 1.0f;
        AmbientLightColour.green = 1.0f;
        AmbientLightColour.blue  = 1.0f;
        DirectionalLightColour = DirectionalLightColourForFrame;

        RpLightSetColor(pAmbient, &AmbientLightColour);
        RpLightSetColor(pDirect, &DirectionalLightColour);
        return;
    }
    SetAmbientAndDirectionalColours(fMult * 0.75f);
}

// fMult = [ 0.0f; 1.0f ]
// 0x735B40 unused
void SetFlashyColours_Mild(float fMult) {
    if ((CTimer::GetTimeInMS() & 0x100) != 0) {
        AmbientLightColour.red   = 0.65f;
        AmbientLightColour.green = 0.65f;
        AmbientLightColour.blue  = 0.65f;
        DirectionalLightColour = DirectionalLightColourForFrame;

        RpLightSetColor(pAmbient, &AmbientLightColour);
        RpLightSetColor(pDirect, &DirectionalLightColour);
        return;
    }
    SetAmbientAndDirectionalColours(fMult * 0.9f);
}

// 0x735BD0
void SetBrightMarkerColours(float lighting) {
    AmbientLightColour.red   = 0.6f;
    AmbientLightColour.green = 0.6f;
    AmbientLightColour.blue  = 0.6f;

    DirectionalLightColour.red   = 1.0f;
    DirectionalLightColour.green = 1.0f;
    DirectionalLightColour.blue  = 1.0f;

    RpLightSetColor(pAmbient, &AmbientLightColour);
    RpLightSetColor(pDirect, &DirectionalLightColour);
}

// 0x735C40
void ReSetAmbientAndDirectionalColours() {
    RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
    RpLightSetColor(pDirect, &DirectionalLightColourForFrame);
}

// 0x735C80
void ActivateDirectional() {
    RpLightSetFlags(pDirect, rpLIGHTLIGHTATOMICS);
}

// 0x735C70
void DeActivateDirectional() {
    RpLightSetFlags(pDirect, 0x0);
}

/*!
 * @addr 0x735C90
 * @param idx Color index 0..8
 */
void SetAmbientColoursToIndicateRoadGroup(int32 idx) {
    // used to convert 0-255 to 0.0f-1.0f

    AmbientLightColour.red   = (float)IndicateR[idx % 7] * 255.0f;
    AmbientLightColour.green = (float)IndicateG[idx % 7] * 255.0f;
    AmbientLightColour.blue  = (float)IndicateB[idx % 7] * 255.0f;
    RpLightSetColor(pAmbient, &AmbientLightColour);
}

// unused
// 0x735D10
void SetFullAmbient() {
    RpLightSetColor(pAmbient, &FullLight);
}

// 0x735D30
void SetAmbientColours() {
    RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
}

// 0x735D50
void SetAmbientColours(RwRGBAReal* color) {
    assert(color);
    RpLightSetColor(pAmbient, color);
}

// 0x735D70
void SetDirectionalColours(RwRGBAReal* color) {
    assert(color);
    RpLightSetColor(pDirect, color);
}

// fMult = [ 0.0f; 1.0f ]
// 0x735D90
void SetLightColoursForPedsCarsAndObjects(float fMult) {
    DirectionalLightColour.red   = fMult * DirectionalLightColourForFrame.red;
    DirectionalLightColour.green = fMult * DirectionalLightColourForFrame.green;
    DirectionalLightColour.blue  = fMult * DirectionalLightColourForFrame.blue;

    AmbientLightColour.red       = fMult * AmbientLightColourForFrame_PedsCarsAndObjects.red;
    AmbientLightColour.green     = fMult * AmbientLightColourForFrame_PedsCarsAndObjects.green;
    AmbientLightColour.blue      = fMult * AmbientLightColourForFrame_PedsCarsAndObjects.blue;

    AmbientLightColour.red      += CTimeCycle::m_BrightnessAddedToAmbientRed;
    AmbientLightColour.green    += CTimeCycle::m_BrightnessAddedToAmbientRed;
    AmbientLightColour.blue     += CTimeCycle::m_BrightnessAddedToAmbientRed;

    RpLightSetColor(pAmbient, &AmbientLightColour);
    RpLightSetColor(pDirect, &DirectionalLightColour);
}

// 0x735E40
void SetLightsForInfraredVisionHeatObjects() {
    RpLightSetColor(pAmbient, &CPostEffects::m_fInfraredVisionHeatObjectCol);
    RpLightSetColor(pDirect, &CPostEffects::m_fInfraredVisionHeatObjectCol);
}

// 0x735E70
void StoreAndSetLightsForInfraredVisionHeatObjects() {
    DirectAmbientLight[1] = AmbientLightColour;
    DirectAmbientLight[0] = DirectionalLightColour;
    SetLightsForInfraredVisionHeatObjects();
}

// 0x735EF0
void RestoreLightsForInfraredVisionHeatObjects() {
    RpLightSetColor(pAmbient, &DirectAmbientLight[1]);
    RpLightSetColor(pDirect, &DirectAmbientLight[0]);
}

// 0x735F20
void SetLightsForInfraredVisionDefaultObjects() {
    RwRGBAReal color{0.0f, 0.0f, 1.0f, 1.0f};
    RpLightSetColor(pAmbient, &color);
    RpLightSetColor(pDirect, &color);
}

// 0x735F70
void SetLightsForNightVision() {
    RwRGBAReal color{0.0f, 1.0f, 0.0f, 1.0f};
    RpLightSetColor(pAmbient, &color);
    RpLightSetColor(pDirect, &color);
}

// 0x6FAB30
float GetDayNightBalance() {
    const auto minutes = CClock::GetMinutesToday();

    if (minutes < 360.0f)
        return 1.0f;

    if (minutes < 420.0f)
        return (420.0f - minutes) * (1.0f / 60.0f);

    if (minutes < 1200.0f)
        return 0.0f;

    if (minutes >= 1260.0f)
        return 1.0f;

    return 1.0f - (1260.0f - minutes) * (1.0f / 60.0f);
}

// 0x7226D0
RpAtomic* RemoveRefsCB(RpAtomic* atomic, void* _IGNORED_ data) {
    auto* modelInfo = CVisibilityPlugins::GetAtomicModelInfo(atomic);
    modelInfo->RemoveRef();
    return atomic;
}

// unused
// 0x7226F0
void RemoveRefsForAtomic(RpClump* clump) {
    plugin::Call<0x7226F0, RpClump*>(clump);
}

// 0x46A760
bool IsGlassModel(CEntity* entity) {
    if (!entity->IsObject())
        return false;

    auto mi = CModelInfo::GetModelInfo(entity->m_nModelIndex);
    if (!mi->AsAtomicModelInfoPtr())
        return false;

    return mi->IsGlass();
}

// 0x4D5F50
CAnimBlendClumpData* RpAnimBlendAllocateData(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendClumpData*, 0x4D5F50, RpClump*>(clump);
}

// 0x4D6790
CAnimBlendAssociation* RpAnimBlendClumpAddAssociation(RpClump* clump, CAnimBlendAssociation* association, uint32 flags, float startTime, float blendAmount) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6790, RpClump*, CAnimBlendAssociation*, uint32, float, float>(clump, association, flags, startTime, blendAmount);
}

// 0x4D6BE0
CAnimBlendAssociation* RpAnimBlendClumpExtractAssociations(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6BE0, RpClump*>(clump);
}

// 0x4D64A0
void RpAnimBlendClumpFillFrameArray(RpClump* clump, AnimBlendFrameData** frameData) {
    plugin::Call<0x4D64A0, RpClump*, AnimBlendFrameData**>(clump, frameData);
}

// 0x4D6400
AnimBlendFrameData* RpAnimBlendClumpFindBone(RpClump* clump, uint32 id) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D6400, RpClump*, uint32>(clump, id);
}

// 0x4D62A0
AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, const char* name) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D62A0, RpClump*, const char*>(clump, name);
}

// 0x4D6370
AnimBlendFrameData* RpAnimBlendClumpFindFrameFromHashKey(RpClump* clump, uint32 key) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D6370, RpClump*, uint32>(clump, key);
}

// 0x4D68E0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, bool arg1, CAnimBlendHierarchy* hierarchy) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D68E0, RpClump*, bool, CAnimBlendHierarchy*>(clump, arg1, hierarchy);
}

// 0x4D6870
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, const char* name) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6870, RpClump*, const char*>(clump, name);
}

// AnimationId animId
// 0x4D68B0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, uint32 animId) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D68B0, RpClump*, uint32>(clump, animId);
}

// 0x4D15E0
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D15E0, RpClump*>(clump);
}

// 0x4D6A70
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump, uint32 flags) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6A70, RpClump*, uint32>(clump, flags);
}

// 0x4D6910
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation(RpClump* clump, CAnimBlendAssociation** pAssociation, float* blendAmount) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6910, RpClump*, CAnimBlendAssociation**, float*>(clump, pAssociation, blendAmount);
}

// 0x4D6A30
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation_N(RpClump* clump, int32 n) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6A30, RpClump*, int32>(clump, n);
}

// 0x4D69A0
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D69A0, RpClump*>(clump);
}

// 0x4D69F0
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation_N(RpClump* clump, int32 n) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D69F0, RpClump*, int32>(clump, n);
}

// 0x4D6B60
uint32 RpAnimBlendClumpGetNumAssociations(RpClump* clump) {
    return plugin::CallAndReturn<uint32, 0x4D6B60, RpClump*>(clump);
}

// 0x4D6BB0
uint32 RpAnimBlendClumpGetNumNonPartialAssociations(RpClump* clump) {
    return plugin::CallAndReturn<uint32, 0x4D6BB0, RpClump*>(clump);
}

// 0x4D6B80
uint32 RpAnimBlendClumpGetNumPartialAssociations(RpClump* clump) {
    return plugin::CallAndReturn<uint32, 0x4D6B80, RpClump*>(clump);
}

// 0x4D6C30
void RpAnimBlendClumpGiveAssociations(RpClump* clump, CAnimBlendAssociation* association) {
    plugin::Call<0x4D6C30, RpClump*, CAnimBlendAssociation*>(clump, association);
}

// 0x4D6720
void RpAnimBlendClumpInit(RpClump* clump) {
    plugin::Call<0x4D6720, RpClump*>(clump);
}

// 0x4D6760
bool RpAnimBlendClumpIsInitialized(RpClump* clump) {
    return plugin::CallAndReturn<bool, 0x4D6760, RpClump*>(clump);
}

// 0x4D6B00
void RpAnimBlendClumpPauseAllAnimations(RpClump* clump) {
    plugin::Call<0x4D6B00, RpClump*>(clump);
}

// 0x4D6C00
void RpAnimBlendClumpRemoveAllAssociations(RpClump* clump) {
    plugin::Call<0x4D6C00, RpClump*>(clump);
}

// 0x4D6820
void RpAnimBlendClumpRemoveAssociations(RpClump* clump, uint32 flags) {
    plugin::Call<0x4D6820, RpClump*, uint32>(clump, flags);
}

// 0x4D67E0
void RpAnimBlendClumpSetBlendDeltas(RpClump* clump, uint32 flags, float delta) {
    plugin::Call<0x4D67E0, RpClump*, uint32, float>(clump, flags, delta);
}

// 0x4D6B30
void RpAnimBlendClumpUnPauseAllAnimations(RpClump* clump) {
    plugin::Call<0x4D6B30, RpClump*>(clump);
}

// 0x4D34F0
void RpAnimBlendClumpUpdateAnimations(RpClump* clump, float step, bool onScreen) {
    plugin::Call<0x4D34F0, RpClump*, float, bool>(clump, step, onScreen);
}

// 0x4D60E0
RtAnimAnimation* RpAnimBlendCreateAnimationForHierarchy(RpHAnimHierarchy* hierarchy) {
    return plugin::CallAndReturn<RtAnimAnimation*, 0x4D60E0, RpHAnimHierarchy*>(hierarchy);
}

// 0x4D5EF0
char* RpAnimBlendFrameGetName(RwFrame* frame) {
    return plugin::CallAndReturn<char*, 0x4D5EF0, RwFrame*>(frame);
}

// 0x4D5F00
void RpAnimBlendFrameSetName(RwFrame* frame, char* name) {
    plugin::Call<0x4D5F00, RwFrame*, char*>(frame, name);
}

// 0x4D6AB0
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6AB0, CAnimBlendAssociation*>(association);
}

// 0x4D6AD0
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association, uint32 flags) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6AD0, CAnimBlendAssociation*, uint32>(association, flags);
}

// 0x4D60C0
void RpAnimBlendKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, float time, void* customData) {
    plugin::Call<0x4D60C0, void*, void*, void*, float, void*>(voidOut, voidIn1, voidIn2, time, customData);
}

// 0x4D6150
bool RpAnimBlendPluginAttach() {
    return plugin::CallAndReturn<bool, 0x4D6150>();
}

// 0x70F9B0
bool GraphicsLowQuality() {
    if (g_fx.GetFxQuality() < FxQuality_e::FXQUALITY_MEDIUM)
        return false;
    if (RwRasterGetDepth(RwCameraGetRaster(Scene.m_pRwCamera)) < 32)
        return false;
    return true;
}

// 0x5A4150
void WriteRaster(RwRaster* raster, const char* path) {
    assert(raster);
    assert(path && path[0]);

    RwImage* img = RwImageCreate(RwRasterGetWidth(raster), RwRasterGetHeight(raster), RwRasterGetDepth(raster));
    RwImageAllocatePixels(img);
    RwImageSetFromRaster(img, raster);
    RtPNGImageWrite(img, path);
    RwImageDestroy(img);
}

// 0x71DA00
bool CalcScreenCoors(const CVector& vecPoint, CVector* vecOutPos, float* screenX, float* screenY)
{
    return plugin::CallAndReturn<bool, 0x71DA00, const CVector&, CVector*, float*, float*>(vecPoint, vecOutPos, screenX, screenY);

    // TODO: Figure out how to get screen size..
    //CVector screen =  TheCamera.m_mViewMatrix * vecPoint;
    //if (screen.z <= 1.0f)
    //    return false;

    //const float depth = 1.0f / screen.z;

    //CVector2D screenSize{}; // TODO..

    //*vecOutPos = screen * depth * CVector(screenSize.x, screenSize.y, 1.0f);

    //*screenX = screenSize.x * depth / CDraw::ms_fFOV * 70.0f;
    //*screenY = screenSize.y * depth / CDraw::ms_fFOV * 70.0f;

    //return true;
}

// 0x71DAB0
bool CalcScreenCoors(const CVector& vecPoint, CVector* vecOutPos)
{
    return plugin::CallAndReturn<bool, 0x71DAB0, const CVector&, CVector*>(vecPoint, vecOutPos);
}

// 0x541330
void LittleTest() {
    ++g_nNumIm3dDrawCalls;
}

// used only in COccluder::ProcessLineSegment
// 0x71DB80
bool DoesInfiniteLineTouchScreen(float fX, float fY, float fXDir, float fYDir) {
    return plugin::CallAndReturn<bool, 0x71DB80, float, float, float, float>(fX, fY, fXDir, fYDir);
}

// Used only in COcclusion, COccluder, CActiveOccluder
// 0x71E050
bool IsPointInsideLine(float fLineX, float fLineY, float fXDir, float fYDir, float fPointX, float fPointY, float fTolerance) {
    return (fPointX - fLineX) * fYDir - (fPointY - fLineY) * fXDir >= fTolerance;
}

// 0x53E160
void RenderDebugShit() {
    PUSH_RENDERGROUP("RenderDebugShit");
    CTheScripts::RenderTheScriptDebugLines();
#ifndef FINAL
    // if(gbShowCollisionLines) CRenderer::RenderCollisionLines();
    // ThePaths.DisplayPathData();
    // CDebug::DrawLines();
    DefinedState();
#endif
    POP_RENDERGROUP();
}

// 0x53E230
void Render2dStuff() {
    RenderDebugShit(); // NOTSA, temp

    const auto DrawOuterZoomBox = []() {
        CPed* player = FindPlayerPed();
        eWeaponType weaponType = WEAPON_UNARMED;
        if (player)
            weaponType = player->GetActiveWeapon().m_nType;
        eCamMode camMode = CCamera::GetActiveCamera().m_nMode;
        bool firstPersonWeapon = false;
        if (camMode == MODE_SNIPER
            || camMode == MODE_SNIPER_RUNABOUT
            || camMode == MODE_ROCKETLAUNCHER
            || camMode == MODE_ROCKETLAUNCHER_RUNABOUT
            || camMode == MODE_CAMERA
            || camMode == MODE_HELICANNON_1STPERSON)
        {
            firstPersonWeapon = true;
        }

        if ((weaponType == WEAPON_SNIPERRIFLE || weaponType == WEAPON_ROCKET) && firstPersonWeapon) {
            CRGBA black(0, 0, 0, 255);
            if (weaponType == WEAPON_ROCKET)
            {
                CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT / 2 - SCREEN_SCALE_Y(180.0f)), black);
                CSprite2d::DrawRect(CRect(0.0f, SCREEN_HEIGHT / 2 + SCREEN_SCALE_Y(170.0f), SCREEN_WIDTH, SCREEN_HEIGHT), black);
            }
            else
            {
                CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT / 2 - SCREEN_SCALE_Y(210.0f)), black);
                CSprite2d::DrawRect(CRect(0.0f, SCREEN_HEIGHT / 2 + SCREEN_SCALE_Y(210.0f), SCREEN_WIDTH, SCREEN_HEIGHT), black);
            }
            CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH / 2 - SCREEN_SCALE_X(210.0f), SCREEN_HEIGHT), black);
            CSprite2d::DrawRect(CRect(SCREEN_WIDTH / 2 + SCREEN_SCALE_X(210.0f), 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT), black);
        }
    };

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(rwRENDERSTATENARENDERSTATE));
    RwRenderStateSet(rwRENDERSTATECULLMODE,          RWRSTATE(rwCULLMODECULLNONE));

    CReplay::Display();
    CPickups::RenderPickUpText();
    if (TheCamera.m_bWideScreenOn && !FrontEndMenuManager.m_bWidescreenOn) TheCamera.DrawBordersForWideScreen();
    DrawOuterZoomBox();
    AudioEngine.DisplayRadioStationName();
    CHud::Draw();
    CSpecialFX::Render2DFXs();
    CUserDisplay::OnscnTimer.ProcessForDisplay();
    CMessages::Display(true);
    CDarkel::DrawMessages();
    CGarages::PrintMessages();
    CFont::DrawFonts();

    // NOTSA: ImGui menu draw loop
    CDebugMenu::ImGuiDrawLoop();
}

// NOTSA
std::wstring UTF8ToUnicode(const std::string &str)
{
    std::wstring out;

    int32 size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.data(), str.length(), nullptr, 0);
    if (size)
    {
        std::vector<wchar_t> temp;
        temp.resize(size, 0);

        if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.data(), str.length(), temp.data(), size))
        {
            out.resize(size);
            std::copy(temp.begin(), temp.end(), out.begin());
        }
    }

    return out;
}

// NOTSA
std::string UnicodeToUTF8(const std::wstring &str)
{
    std::string out;

    int32 size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str.data(), str.length(), nullptr, 0, nullptr, nullptr);
    if (size)
    {
        std::vector<char> temp;
        temp.resize(size, 0);

        if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str.data(), str.length(), temp.data(), size, nullptr, nullptr))
        {
            out.resize(size);
            std::copy(temp.begin(), temp.end(), out.begin());
        }
    }

    return out;
}

int32 WindowsCharset = static_cast<int32>(GetACP());

uint16& uiTempBufferIndicesStored = *(uint16*)0xC4B954;
uint16& uiTempBufferVerticesStored = *(uint16*)0xC4B950;
RxVertexIndex(&aTempBufferIndices)[TOTAL_TEMP_BUFFER_INDICES] = *(RxVertexIndex(*)[TOTAL_TEMP_BUFFER_INDICES])0xC4B958;
RxObjSpace3DVertex(&aTempBufferVertices)[TOTAL_TEMP_BUFFER_VERTICES] = *(RxObjSpace3DVertex(*)[TOTAL_TEMP_BUFFER_VERTICES])0xC4D958; // size 1024 - after this there are 2 more arrays like this, both sized 512
RwD3D9Vertex(&aRadiosityVertexBuffer)[TOTAL_RADIOSITY_VERTEX_BUFFER] = *reinterpret_cast<RwD3D9Vertex(*)[TOTAL_RADIOSITY_VERTEX_BUFFER]>(0xC5F958);
