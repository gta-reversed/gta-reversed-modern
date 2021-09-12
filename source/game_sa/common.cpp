/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"
#include "GxtChar.h"
#include "CDebugMenu.h"

int32& g_nNumIm3dDrawCalls = *(int32*)0xB73708;
int32 gDefaultTaskTime = 9999999; // or 0x98967F a.k.a (one milllion - 1)
char *gString = (char *)0xB71670;

float &GAME_GRAVITY = *(float *)0x863984;

char(&PC_Scratch)[16384] = *(char(*)[16384])0xC8E0C8;

RpLight* (&ObjectAffectingLights)[6] = *reinterpret_cast<RpLight* (*)[6]>(0xC886F0);
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

// used to convert 0-255 to 0.0f-1.0f, also see RwRGBARealFromRwRGBAMacro
float& flt_859A3C = *(float*)0x859A3C; // 1.0f / 255.0f = 0.0039215689f



void InjectCommonHooks()
{
    HookInstall(0x53E230, &Render2dStuff); // This one shouldn't be reversible, it contains imgui debug menu logic, and makes game unplayable without :D

    ReversibleHooks::Install("common", "FindPlayerCoors", 0x56E010, &FindPlayerCoors);
    ReversibleHooks::Install("common", "FindPlayerSpeed", 0x56E090, &FindPlayerSpeed);
    ReversibleHooks::Install("common", "FindPlayerEntity", 0x56E120, &FindPlayerEntity);
    ReversibleHooks::Install("common", "FindPlayerTrain", 0x56E160, &FindPlayerTrain);
    ReversibleHooks::Install("common", "FindPlayerCentreOfWorld", 0x56E250, &FindPlayerCentreOfWorld);
//    ReversibleHooks::Install("common", "FindPlayerCentreOfWorld_NoSniperShift", 0x56E320, &FindPlayerCentreOfWorld_NoSniperShift);
//    ReversibleHooks::Install("common", "FindPlayerCentreOfWorld_NoInteriorShift", 0x56E400, &FindPlayerCentreOfWorld_NoInteriorShift);
    ReversibleHooks::Install("common", "FindPlayerHeading", 0x56E450, &FindPlayerHeading);
    ReversibleHooks::Install("common", "FindPlayerPed", 0x56E210, &FindPlayerPed);
    ReversibleHooks::Install("common", "FindPlayerVehicle", 0x56E0D0, &FindPlayerVehicle);
    ReversibleHooks::Install("common", "FindPlayerWanted", 0x56E230, &FindPlayerWanted);
    ReversibleHooks::Install("common", "InTwoPlayersMode", 0x441390, &InTwoPlayersMode);

    ReversibleHooks::Install("common", "MakeUpperCase", 0x7186E0, &MakeUpperCase);
    ReversibleHooks::Install("common", "GetEventGlobalGroup", 0x4ABA50, &GetEventGlobalGroup);
    ReversibleHooks::Install("common", "DefinedState", 0x734650, &DefinedState);
    ReversibleHooks::Install("common", "DefinedState2d", 0x734750, &DefinedState2d);

    ReversibleHooks::Install("common", "GetNameAndDamage", 0x5370A0, &GetNameAndDamage);
    ReversibleHooks::Install("common", "GetFirstAtomicCallback", 0x734810, &GetFirstAtomicCallback);
    ReversibleHooks::Install("common", "GetFirstAtomic", 0x734820, &GetFirstAtomic);
//    ReversibleHooks::Install("common", "Get2DEffectAtomicCallback", 0x734850, &Get2DEffectAtomicCallback);
    ReversibleHooks::Install("common", "Get2DEffectAtomic", 0x734880, &Get2DEffectAtomic);
    ReversibleHooks::Install("common", "GetFirstObjectCallback", 0x7348B0, &GetFirstObjectCallback);
    ReversibleHooks::Install("common", "GetFirstObject", 0x7348C0, &GetFirstObject);
    ReversibleHooks::Install("common", "GetFirstFrameCallback", 0x7348F0, &GetFirstFrameCallback);
    ReversibleHooks::Install("common", "GetFirstChild", 0x734900, &GetFirstChild);
//    ReversibleHooks::Install("common", "GetFirstTextureCallback", 0x734930, &GetFirstTextureCallback);
//    ReversibleHooks::Install("common", "GetFirstTexture", 0x734940, &GetFirstTexture);
    ReversibleHooks::Install("common", "SkinAtomicGetHAnimHierarchCB", 0x734A20, &SkinAtomicGetHAnimHierarchCB);
    ReversibleHooks::Install("common", "GetAnimHierarchyFromSkinClump", 0x734A40, &GetAnimHierarchyFromSkinClump);
//    ReversibleHooks::Install("common", "GetAnimHierarchyFromFrame", 0x734AB0, &GetAnimHierarchyFromFrame);
    ReversibleHooks::Install("common", "GetAnimHierarchyFromClump", 0x734B10, &GetAnimHierarchyFromClump);
    ReversibleHooks::Install("common", "AtomicRemoveAnimFromSkinCB", 0x734B90, &AtomicRemoveAnimFromSkinCB);
    ReversibleHooks::Install("common", "RpAtomicConvertGeometryToTL", 0x734BE0, &RpAtomicConvertGeometryToTL);
    ReversibleHooks::Install("common", "RpAtomicConvertGeometryToTS", 0x734C20, &RpAtomicConvertGeometryToTS);

    ReversibleHooks::Install("common", "atomicConvertGeometryToTL", 0x734C60, &atomicConvertGeometryToTL);
    ReversibleHooks::Install("common", "RpClumpConvertGeometryToTL", 0x734CB0, &RpClumpConvertGeometryToTL);

    ReversibleHooks::Install("common", "atomicConvertGeometryToTS", 0x734CE0, &atomicConvertGeometryToTS);
    ReversibleHooks::Install("common", "RpClumpConvertGeometryToTS", 0x734D30, &RpClumpConvertGeometryToTS);

    ReversibleHooks::Install("common", "forceLinearFilteringAtomicsCB", 0x734DA0, &forceLinearFilteringAtomicsCB);
    ReversibleHooks::Install("common", "SetFilterModeOnClumpsTextures", 0x734DC0, &SetFilterModeOnClumpsTextures);


    ReversibleHooks::Install("common", "forceLinearFilteringMatTexturesCB", 0x734D60, &forceLinearFilteringMatTexturesCB);
    ReversibleHooks::Install("common", "SetFilterModeOnAtomicsTextures", 0x734D80, &SetFilterModeOnAtomicsTextures);

    ReversibleHooks::Install("common", "SetLightsWithTimeOfDayColour", 0x7354E0, &SetLightsWithTimeOfDayColour);
    ReversibleHooks::Install("common", "LightsDestroy", 0x735730, &LightsDestroy);
    ReversibleHooks::Install("common", "WorldReplaceNormalLightsWithScorched", 0x7357E0, &WorldReplaceNormalLightsWithScorched);
//    ReversibleHooks::Install("common", "AddAnExtraDirectionalLight", 0x735840, &AddAnExtraDirectionalLight);
    ReversibleHooks::Install("common", "RemoveExtraDirectionalLights", 0x7359E0, &RemoveExtraDirectionalLights);
    ReversibleHooks::Install("common", "SetBrightMarkerColours", 0x735BD0, &SetBrightMarkerColours);
    ReversibleHooks::Install("common", "ReSetAmbientAndDirectionalColours", 0x735C40, &ReSetAmbientAndDirectionalColours);
    ReversibleHooks::Install("common", "DeActivateDirectional", 0x735C70, &DeActivateDirectional);
    ReversibleHooks::Install("common", "ActivateDirectional", 0x735C80, &ActivateDirectional);
    ReversibleHooks::Install("common", "SetAmbientColours_void", 0x735D30, static_cast<void(*)()>(&SetAmbientColours));
    ReversibleHooks::Install("common", "SetAmbientColours_color", 0x735D50, static_cast<void(*)(RwRGBAReal* color)>(&SetAmbientColours));
    ReversibleHooks::Install("common", "SetDirectionalColours", 0x735D70, &SetDirectionalColours);
    ReversibleHooks::Install("common", "SetLightColoursForPedsCarsAndObjects", 0x735D90, &SetLightColoursForPedsCarsAndObjects);
    ReversibleHooks::Install("common", "SetLightsForInfraredVisionHeatObjects", 0x735E40, &SetLightsForInfraredVisionHeatObjects);
    ReversibleHooks::Install("common", "StoreAndSetLightsForInfraredVisionHeatObjects", 0x735E70, &StoreAndSetLightsForInfraredVisionHeatObjects);
    ReversibleHooks::Install("common", "RestoreLightsForInfraredVisionHeatObjects", 0x735EF0, &RestoreLightsForInfraredVisionHeatObjects);
    ReversibleHooks::Install("common", "SetLightsForInfraredVisionDefaultObjects", 0x735F20, &SetLightsForInfraredVisionDefaultObjects);
    ReversibleHooks::Install("common", "SetLightsForNightVision", 0x735F70, &SetLightsForNightVision);
    ReversibleHooks::Install("common", "GetDayNightBalance", 0x6FAB30, &GetDayNightBalance);
    ReversibleHooks::Install("common", "AsciiToGxtChar", 0x718600, &AsciiToGxtChar);
    ReversibleHooks::Install("common", "WriteRaster", 0x005A4150, &WriteRaster);
//    ReversibleHooks::Install("common", "CalcScreenCoors_VVff", 0x71DA00, static_cast<bool(*)(CVector const&, CVector*, float*, float*)>(&CalcScreenCoors));
//    ReversibleHooks::Install("common", "CalcScreenCoors_VV", 0x71DAB0, static_cast<bool(*)(CVector const&, CVector*)>(&CalcScreenCoors));
    ReversibleHooks::Install("common", "LittleTest", 0x541330, &LittleTest);

    ReversibleHooks::Install("common", "RemoveRefsCB", 0x7226D0, &RemoveRefsCB);
    ReversibleHooks::Install("common", "IsGlassModel", 0x46A760, &IsGlassModel);
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
CVector const& FindPlayerCentreOfWorld(int32 playerId) {
    if (CCarCtrl::bCarsGeneratedAroundCamera)
        return TheCamera.GetPosition();
    if (CVehicle* veh = FindPlayerVehicle(playerId, true))
        return veh->GetPosition();
    return FindPlayerPed(playerId)->GetPosition();
}

// 0x56E320
CVector const& FindPlayerCentreOfWorld_NoSniperShift(int32 playerId) {
    return ((CVector const&(__cdecl*)(int32))0x56E320)(playerId);
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
    return CWorld::Players[(playerId < 0 ? CWorld::PlayerInFocus : playerId)].m_pPed;
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
    return CWorld::Players[(playerId < 0 ? CWorld::PlayerInFocus : playerId)].m_PlayerData.m_pWanted;
}

// TODO: Rename CGameLogic::IsCoopGameGoingOn
// 0x441390
bool InTwoPlayersMode() {
    return CWorld::Players[0].m_pPed && CWorld::Players[1].m_pPed;
}

// NOTE: This function doesn't add m.GetPosition() like
//       MultiplyMatrixWithVector @ 0x59C890 does.
CVector Multiply3x3(CMatrix& m, CVector& v) {
    return CVector{
        m.GetRight().x * v.x + m.GetForward().x * v.y + m.GetUp().x * v.z,
        m.GetRight().y * v.x + m.GetForward().y * v.y + m.GetUp().y * v.z,
        m.GetRight().z * v.x + m.GetForward().z * v.y + m.GetUp().z * v.z,
    };
}

// vector by matrix mult, resulting in a vector where each component is the dot product of the in vector and a matrix direction
CVector Multiply3x3(CVector& v, CMatrix& m) {
    return CVector(DotProduct(m.GetRight(), v),
                   DotProduct(m.GetForward(), v),
                   DotProduct(m.GetUp(), v));
}

// 0x54ECE0
void TransformPoint(RwV3d& point, CSimpleTransform const& placement, RwV3d const& vecPos) {
    plugin::Call<0x54ECE0, RwV3d&, CSimpleTransform const&, RwV3d const&>(point, placement, vecPos);
}

// 0x54EEA0
void TransformVectors(RwV3d* vecsOut, int32 numVectors, CMatrix const& matrix, RwV3d const* vecsin) {
    plugin::Call<0x54EEA0, RwV3d*, int32, CMatrix const&, RwV3d const*>(vecsOut, numVectors, matrix, vecsin);
}

// 0x54EE30
void TransformVectors(RwV3d* vecsOut, int32 numVectors, CSimpleTransform const& transform, RwV3d const* vecsin) {
    plugin::Call<0x54EE30, RwV3d*, int32, CSimpleTransform const&, RwV3d const*>(vecsOut, numVectors, transform, vecsin);
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

// 0x734610
void CreateDebugFont() {
    // NOP
}

// 0x4ABA50
CEventGroup* GetEventGlobalGroup() {
    static CEventGroup*& globalEvents = *(CEventGroup**)0xA9AF6C;

    if (globalEvents)
        return globalEvents;

    globalEvents = new CEventGroup(nullptr);
    return globalEvents;
}

// 0x734620
void DestroyDebugFont() {
    // NOP
}

// unused
// 0x734630
void ObrsPrintfString(char const* arg0, int16 arg1, int16 arg2) {
    // NOP
}

// 0x734640
void FlushObrsPrintfs() {
    // NOP
}

// 0x734650
void DefinedState() {
    CRGBA rgbaFog(
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomRed,
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomBlue
    );

    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,       (void*)true);
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE,   (void*)true);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          (void*)true);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         (void*)true);
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            (void*)rwSHADEMODEGOURAUD);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        (void*)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEBORDERCOLOR,          (void*)(RWRGBALONG(0, 0, 0, 255)));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEFOGCOLOR,             (void*)rgbaFog.ToIntARGB());
    RwRenderStateSet(rwRENDERSTATEFOGTYPE,              (void*)rwFOGTYPELINEAR);
    RwRenderStateSet(rwRENDERSTATECULLMODE,             (void*)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    (void*)rwALPHATESTFUNCTIONGREATER);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void*)2); // TODO: ?
}

// 0x734750
void DefinedState2d() {
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,       (void*)true);
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE,   (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            (void*)rwSHADEMODEGOURAUD);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        (void*)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEBORDERCOLOR,          (void*)(RWRGBALONG(0, 0, 0, 255)));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATECULLMODE,             (void*)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    (void*)rwALPHATESTFUNCTIONGREATER);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void*)2); // TODO: ?
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
    RpGeometry* pGeom = RpAtomicGetGeometry(atomic);

    auto flags = RpGeometryGetFlags(pGeom);
    if (flags & rpGEOMETRYNATIVE || !(flags & rpGEOMETRYTRISTRIP))
        return false;

    RpGeometryLock(pGeom, rpGEOMETRYLOCKALL);
    RpGeometrySetFlags(pGeom, flags & ~rpGEOMETRYTRISTRIP);
    RpGeometryUnlock(pGeom);

    return true;
}

// 0x734C20
bool RpAtomicConvertGeometryToTS(RpAtomic* atomic) {
    RpGeometry* pGeom = RpAtomicGetGeometry(atomic);

    auto flags = RpGeometryGetFlags(pGeom);
    if (flags & rpGEOMETRYNATIVE || flags & rpGEOMETRYTRISTRIP)
        return false;

    RpGeometryLock(pGeom, rpGEOMETRYLOCKALL);
    RpGeometrySetFlags(pGeom, flags | rpGEOMETRYTRISTRIP);
    RpGeometryUnlock(pGeom);

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
    if (pAmbient) {
        AmbientLightColourForFrame.red = CTimeCycle::GetAmbientRed() * CCoronas::LightsMult;
        AmbientLightColourForFrame.green = CTimeCycle::GetAmbientGreen() * CCoronas::LightsMult;
        AmbientLightColourForFrame.blue = CTimeCycle::GetAmbientBlue() * CCoronas::LightsMult;
        AmbientLightColourForFrame_PedsCarsAndObjects.red = CTimeCycle::GetAmbientRed_Obj() * CCoronas::LightsMult;
        AmbientLightColourForFrame_PedsCarsAndObjects.green = CTimeCycle::GetAmbientGreen_Obj() * CCoronas::LightsMult;
        AmbientLightColourForFrame_PedsCarsAndObjects.blue = CTimeCycle::GetAmbientBlue_Obj() * CCoronas::LightsMult;
        if (CWeather::LightningFlash) {
            AmbientLightColourForFrame.blue = 1.0;
            AmbientLightColourForFrame.green = 1.0;
            AmbientLightColourForFrame.red = 1.0;
            AmbientLightColourForFrame_PedsCarsAndObjects.blue = 1.0;
            AmbientLightColourForFrame_PedsCarsAndObjects.green = 1.0;
            AmbientLightColourForFrame_PedsCarsAndObjects.red = 1.0;
        }
        RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
    }

    if (pDirect) {
        DirectionalLightColourForFrame.red = CTimeCycle::m_CurrentColours.m_fIllumination * 0.99609375f * CCoronas::LightsMult;
        DirectionalLightColourForFrame.green = DirectionalLightColourForFrame.red;
        DirectionalLightColourForFrame.blue = DirectionalLightColourForFrame.red;
        RpLightSetColor(pDirect, &DirectionalLightColourForFrame);

        const CVector vertical{ 0.0f, 0.0f, 1.0f };

        // TODO: This is a fairly commonly used thing,
        // would be nice to make a function out of it..
        // Is basically calculates a matrix out of a normal.
       
        RwMatrix mat;

        mat.at = -CTimeCycle::m_vecDirnLightToSun;
        mat.up = Normalized(CrossProduct(vertical, CTimeCycle::m_vecDirnLightToSun));
        mat.right = CrossProduct(mat.up, CTimeCycle::m_vecDirnLightToSun);

        RwFrameTransform(RpClumpGetFrame(pDirect), &mat, RwOpCombineType::rwCOMBINEREPLACE);
    }
}

// unused
// 0x735720
void LightsEnable(int32 arg0) {
    // NOP
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
        auto* parentFrame = static_cast<RwFrame*>(pDirect->object.object.parent);
        RwFrameDestroy(parentFrame);
        RpLightDestroy(pDirect);
        pDirect = nullptr;
    }

    for (auto& light : ObjectAffectingLights) {
        if (light) {
            RpWorldRemoveLight(world, light);
            auto* parentFrame = static_cast<RwFrame*>(light->object.object.parent);
            RwFrameDestroy(parentFrame);
            RpLightDestroy(light);
            light = nullptr;
        }
    }
}

// 0x7357E0
void WorldReplaceNormalLightsWithScorched(RpWorld* world, float lighting) {
    RwRGBAReal color{lighting, lighting, lighting};
    RpLightSetColor(pAmbient, &color);
    pDirect->object.object.flags = 0;
}

// unused
// 0x735820
void WorldReplaceScorchedLightsWithNormal(RpWorld* world) {
    RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
    pDirect->object.object.flags = 1;
}

// 0x735840
void AddAnExtraDirectionalLight(RpWorld* world, float x, float y, float z, float red, float green, float blue) {
    ((void(__cdecl *)(RpWorld*, float, float, float, float, float, float))0x735840)(world, x, y, z, red, green, blue);
}

// 0x7359E0
void RemoveExtraDirectionalLights(RpWorld* world) {
    for (auto& light : ObjectAffectingLights) {
        light->object.object.flags = 0;
    }
    numExtraDirectionalLights = 0;
}

// used in SetFlashyColours and SetFlashyColours_Mild which unused
// 0x735A20
void SetAmbientAndDirectionalColours(float lighting) {
    AmbientLightColour.red = AmbientLightColourForFrame.red * lighting;
    AmbientLightColour.green = AmbientLightColourForFrame.green * lighting;
    AmbientLightColour.blue = AmbientLightColourForFrame.blue * lighting;

    DirectionalLightColour.red = DirectionalLightColourForFrame.red * lighting;
    DirectionalLightColour.green = DirectionalLightColourForFrame.green * lighting;
    DirectionalLightColour.blue = DirectionalLightColourForFrame.blue * lighting;

    RpLightSetColor(pAmbient, &AmbientLightColour);
    RpLightSetColor(pDirect, &DirectionalLightColour);
}

// unused
// 0x735AB0
void SetFlashyColours(float lighting) {
    if ((CTimer::m_snTimeInMilliseconds & 0x100) != 0) {
        AmbientLightColour.red = 1.0f;
        AmbientLightColour.green = 1.0f;
        AmbientLightColour.blue = 1.0f;
        DirectionalLightColour.red = DirectionalLightColourForFrame.red;
        DirectionalLightColour.green = DirectionalLightColourForFrame.green;
        DirectionalLightColour.blue = DirectionalLightColourForFrame.blue;
        RpLightSetColor(pAmbient, &AmbientLightColour);
        RpLightSetColor(pDirect, &DirectionalLightColour);
    } else {
        SetAmbientAndDirectionalColours(lighting * 0.75f);
    }
}

// unused
// 0x735B40
void SetFlashyColours_Mild(float lighting) {
    if ((CTimer::m_snTimeInMilliseconds & 0x100) != 0) {
        AmbientLightColour.red = 1.0f;
        AmbientLightColour.green = 1.0f;
        AmbientLightColour.blue = 1.0f;
        DirectionalLightColour.red = DirectionalLightColourForFrame.red;
        DirectionalLightColour.green = DirectionalLightColourForFrame.green;
        DirectionalLightColour.blue = DirectionalLightColourForFrame.blue;
        RpLightSetColor(pAmbient, &AmbientLightColour);
        RpLightSetColor(pDirect, &DirectionalLightColour);
    } else {
        SetAmbientAndDirectionalColours(lighting * 0.9f);
    }
}

// 0x735BD0
void SetBrightMarkerColours(float lighting) {
    AmbientLightColour.red = 0.6f;
    AmbientLightColour.green = 0.6f;
    AmbientLightColour.blue = 0.6f;
    DirectionalLightColour.red = 1.0f;
    DirectionalLightColour.green = 1.0f;
    DirectionalLightColour.blue = 1.0f;
    RpLightSetColor(pAmbient, &AmbientLightColour);
    RpLightSetColor(pDirect, &DirectionalLightColour);
}

// 0x735C40
void ReSetAmbientAndDirectionalColours() {
    RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
    RpLightSetColor(pDirect, &DirectionalLightColourForFrame);
}

// 0x735C70
void DeActivateDirectional() {
    pDirect->object.object.flags = 0;
}

// 0x735C80
void ActivateDirectional() {
    pDirect->object.object.flags = 1;
}

// unused
// 0x735C90
void SetAmbientColoursToIndicateRoadGroup(int32 arg0) {
    AmbientLightColour.red = IndicateR[arg0 % 7] * flt_859A3C;
    AmbientLightColour.green = IndicateG[arg0 % 7] * flt_859A3C;
    AmbientLightColour.blue = IndicateB[arg0 % 7] * flt_859A3C;
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
    RpLightSetColor(pAmbient, color);
}

// 0x735D70
void SetDirectionalColours(RwRGBAReal* color) {
    RpLightSetColor(pDirect, color);
}

// 0x735D90
void SetLightColoursForPedsCarsAndObjects(float lighting) {
    DirectionalLightColour.red = DirectionalLightColourForFrame.red * lighting;
    DirectionalLightColour.green = DirectionalLightColourForFrame.green * lighting;
    DirectionalLightColour.blue = DirectionalLightColourForFrame.blue * lighting;

    AmbientLightColour.red = CTimeCycle::m_BrightnessAddedToAmbientRed + AmbientLightColourForFrame_PedsCarsAndObjects.red * lighting;
    AmbientLightColour.green = CTimeCycle::m_BrightnessAddedToAmbientGreen + AmbientLightColourForFrame_PedsCarsAndObjects.green * lighting;
    AmbientLightColour.blue = CTimeCycle::m_BrightnessAddedToAmbientBlue + AmbientLightColourForFrame_PedsCarsAndObjects.blue * lighting;

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
    if (minutes < 360)
        return 1.0f;
    if (minutes < 420)
        return (float)(420 - minutes) / 60.0f;
    if (minutes < 1200)
        return 0.0f;
    if (minutes >= 1260)
        return 1.0f;
    return 1.0f - (float)(1260 - minutes) / 60.0f;
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
bool IsGlassModel(CEntity* pEntity) {
    if (!pEntity->IsObject())
        return false;

    auto pModelInfo = CModelInfo::GetModelInfo(pEntity->m_nModelIndex);
    if (!pModelInfo->AsAtomicModelInfoPtr())
        return false;

    return pModelInfo->IsGlass();
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
AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, char const* name) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D62A0, RpClump*, char const*>(clump, name);
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
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, char const* name) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6870, RpClump*, char const*>(clump, name);
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

// 0x5A4150
void WriteRaster(RwRaster* raster, char const* path) {
    assert(raster);
    assert(path && path[0]);

    RwImage* img = RwImageCreate(RwRasterGetWidth(raster), RwRasterGetHeight(raster), RwRasterGetDepth(raster));
    RwImageAllocatePixels(img);
    RwImageSetFromRaster(img, raster);
    RtPNGImageWrite(img, path);
    RwImageDestroy(img);
}

// 0x71DA00
bool CalcScreenCoors(CVector const& vecPoint, CVector* pVecOutPos, float* pScreenX, float* pScreenY)
{
    return plugin::CallAndReturn<bool, 0x71DA00, CVector const&, CVector*, float*, float*>(vecPoint, pVecOutPos, pScreenX, pScreenY);

    // TODO: Figure out how to get screen size..
    //CVector screen =  TheCamera.m_mViewMatrix * vecPoint;
    //if (screen.z <= 1.0f)
    //    return false;

    //const float depth = 1.0f / screen.z;

    //CVector2D screenSize{}; // TODO..

    //*pVecOutPos = screen * depth * CVector(screenSize.x, screenSize.y, 1.0f);

    //*pScreenX = screenSize.x * depth / CDraw::ms_fFOV * 70.0f;
    //*pScreenY = screenSize.y * depth / CDraw::ms_fFOV * 70.0f;

    //return true;
}

// 0x71DAB0
bool CalcScreenCoors(CVector const& vecPoint, CVector* pVecOutPos)
{
    return plugin::CallAndReturn<bool, 0x71DAB0, CVector const&, CVector*>(vecPoint, pVecOutPos);
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

// 0x53E230
void Render2dStuff() {
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       (void*)false);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void*)false);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)true);
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         (void*)rwRENDERSTATENARENDERSTATE);
    RwRenderStateSet(rwRENDERSTATECULLMODE,          (void*)rwCULLMODECULLNONE);
    CReplay::Display();
    CPickups::RenderPickUpText();
    if (TheCamera.m_bWideScreenOn && !FrontEndMenuManager.m_bWidescreenOn)
        TheCamera.DrawBordersForWideScreen();
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
    if ((weaponType == WEAPON_SNIPERRIFLE || weaponType == WEAPON_ROCKET) && firstPersonWeapon)
    {
        CRGBA black(0, 0, 0, 255);
        if (weaponType == WEAPON_ROCKET)
        {
            CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT / 2 - SCREEN_SCALE_Y(180)), black);
            CSprite2d::DrawRect(CRect(0.0f, SCREEN_HEIGHT / 2 + SCREEN_SCALE_Y(170), SCREEN_WIDTH, SCREEN_HEIGHT), black);
        }
        else
        {
            CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT / 2 - SCREEN_SCALE_Y(210)), black);
            CSprite2d::DrawRect(CRect(0.0f, SCREEN_HEIGHT / 2 + SCREEN_SCALE_Y(210), SCREEN_WIDTH, SCREEN_HEIGHT), black);
        }
        CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH / 2 - SCREEN_SCALE_X(210), SCREEN_HEIGHT), black);
        CSprite2d::DrawRect(CRect(SCREEN_WIDTH / 2 + SCREEN_SCALE_X(210), 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT), black);
    }
    AudioEngine.DisplayRadioStationName();
    CHud::Draw();
    CSpecialFX::Render2DFXs();
    CUserDisplay::OnscnTimer.ProcessForDisplay();
    CMessages::Display(true);
    CDarkel::DrawMessages();
    CGarages::PrintMessages();
    CFont::DrawFonts();

    // NOTSA: ImGui menu draw loop
    CDebugMenu::ImguiDrawLoop();
    CDebugMenu::ImGuiDrawMouse();
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
