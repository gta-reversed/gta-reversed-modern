/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CDebugMenu.h"

int& g_nNumIm3dDrawCalls = *(int*)0xB73708;
int gDefaultTaskTime = 9999999; // or 0x98967F a.k.a (one milllion - 1)
char *gString = (char *)0xB71670;

float &GAME_GRAVITY = *(float *)0x863984;

char(&PC_Scratch)[16384] = *(char(*)[16384])0xC8E0C8;

RpLight* (&ObjectAffectingLights)[6] = *reinterpret_cast<RpLight* (*)[6]>(0xC886F0);
int& numExtraDirectionalLights = *reinterpret_cast<int*>(0xC88708);

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

unsigned int &ClumpOffset = *(unsigned int *)0xB5F878;

// used to convert 0-255 to 0.0f-1.0f, also see RwRGBARealFromRwRGBAMacro
float& flt_859A3C = *(float*)0x859A3C; // 1.0f / 255.0f = 0.0039215689f



void InjectCommonHooks()
{
    HookInstall(0x53E230, &Render2dStuff); // This one shouldn't be reversible, it contains imgui debug menu logic, and makes game unplayable without :D

//    ReversibleHooks::Install("common", "FindPlayerCoors", 0x56E010, &FindPlayerCoors);
//    ReversibleHooks::Install("common", "FindPlayerSpeed", 0x56E090, &FindPlayerSpeed);
    ReversibleHooks::Install("common", "FindPlayerEntity", 0x56E120, &FindPlayerEntity);
    ReversibleHooks::Install("common", "FindPlayerTrain", 0x56E160, &FindPlayerTrain);
//    ReversibleHooks::Install("common", "FindPlayerCentreOfWorld", 0x56E250, &FindPlayerCentreOfWorld);
//    ReversibleHooks::Install("common", "FindPlayerCentreOfWorld_NoSniperShift", 0x56E320, &FindPlayerCentreOfWorld_NoSniperShift);
//    ReversibleHooks::Install("common", "FindPlayerCentreOfWorld_NoInteriorShift", 0x56E400, &FindPlayerCentreOfWorld_NoInteriorShift);
//    ReversibleHooks::Install("common", "FindPlayerHeading", 0x56E450, &FindPlayerHeading);
    ReversibleHooks::Install("common", "FindPlayerPed", 0x56E210, &FindPlayerPed);
//    ReversibleHooks::Install("common", "FindPlayerVehicle", 0x56E0D0, &FindPlayerVehicle);
    ReversibleHooks::Install("common", "FindPlayerWanted", 0x56E230, &FindPlayerWanted);
    ReversibleHooks::Install("common", "InTwoPlayersMode", 0x441390, &InTwoPlayersMode);

//    ReversibleHooks::Install("common", "MakeUpperCase", 0x7186E0, &MakeUpperCase);
//    ReversibleHooks::Install("common", "GetEventGlobalGroup", 0x4ABA50, &GetEventGlobalGroup);
    ReversibleHooks::Install("common", "DefinedState", 0x734650, &DefinedState);
    ReversibleHooks::Install("common", "DefinedState2d", 0x734750, &DefinedState2d);

//    ReversibleHooks::Install("common", "GetFirstAtomicCallback", 0x734810, &GetFirstAtomicCallback);
//    ReversibleHooks::Install("common", "GetFirstAtomic", 0x734820, &GetFirstAtomic);
//    ReversibleHooks::Install("common", "Get2DEffectAtomicCallback", 0x734850, &Get2DEffectAtomicCallback);
//    ReversibleHooks::Install("common", "Get2DEffectAtomic", 0x734880, &Get2DEffectAtomic);
//    ReversibleHooks::Install("common", "GetFirstObjectCallback", 0x7348B0, &GetFirstObjectCallback);
//    ReversibleHooks::Install("common", "GetFirstObject", 0x7348C0, &GetFirstObject);
//    ReversibleHooks::Install("common", "GetFirstFrameCallback", 0x7348F0, &GetFirstFrameCallback);
//    ReversibleHooks::Install("common", "GetFirstChild", 0x734900, &GetFirstChild);
//    ReversibleHooks::Install("common", "GetFirstTextureCallback", 0x734930, &GetFirstTextureCallback);
//    ReversibleHooks::Install("common", "GetFirstTexture", 0x734940, &GetFirstTexture);
//    ReversibleHooks::Install("common", "GetAnimHierarchyFromSkinClump", 0x734A40, &GetAnimHierarchyFromSkinClump);
//    ReversibleHooks::Install("common", "GetAnimHierarchyFromFrame", 0x734AB0, &GetAnimHierarchyFromFrame);
//    ReversibleHooks::Install("common", "GetAnimHierarchyFromClump", 0x734B10, &GetAnimHierarchyFromClump);
//    ReversibleHooks::Install("common", "AtomicRemoveAnimFromSkinCB", 0x734B90, &AtomicRemoveAnimFromSkinCB);

//    ReversibleHooks::Install("common", "SetLightsWithTimeOfDayColour", 0x7354E0, &SetLightsWithTimeOfDayColour);
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
//    ReversibleHooks::Install("common", "SetLightsForInfraredVisionHeatObjects", 0x735E40, &SetLightsForInfraredVisionHeatObjects);
//    ReversibleHooks::Install("common", "StoreAndSetLightsForInfraredVisionHeatObjects", 0x735E70, &StoreAndSetLightsForInfraredVisionHeatObjects);
    ReversibleHooks::Install("common", "RestoreLightsForInfraredVisionHeatObjects", 0x735EF0, &RestoreLightsForInfraredVisionHeatObjects);
    ReversibleHooks::Install("common", "SetLightsForInfraredVisionDefaultObjects", 0x735F20, &SetLightsForInfraredVisionDefaultObjects);
    ReversibleHooks::Install("common", "SetLightsForNightVision", 0x735F70, &SetLightsForNightVision);
//    ReversibleHooks::Install("common", "GetDayNightBalance", 0x6FAB30, &GetDayNightBalance);
//    ReversibleHooks::Install("common", "AsciiToGxtChar", 0x718600, &AsciiToGxtChar);
//    ReversibleHooks::Install("common", "WriteRaster", 0x005A4150, &WriteRaster);
//    ReversibleHooks::Install("common", "CalcScreenCoors_VVff", 0x71DA00, static_cast<bool(*)(CVector const&, CVector*, float*, float*)>(&CalcScreenCoors));
//    ReversibleHooks::Install("common", "CalcScreenCoors_VV", 0x71DAB0, static_cast<bool(*)(CVector const&, CVector*)>(&CalcScreenCoors));
    ReversibleHooks::Install("common", "LittleTest", 0x541330, &LittleTest);

    ReversibleHooks::Install("common", "RemoveRefsCB", 0x7226D0, &RemoveRefsCB);
    ReversibleHooks::Install("common", "IsGlassModel", 0x46A760, &IsGlassModel);
}

// 0x56E010
CVector FindPlayerCoors(int playerId) {
    return plugin::CallAndReturn<CVector, 0x56E010, int>(playerId);
}

// 0x56E090
CVector& FindPlayerSpeed(int playerId) {
    return plugin::CallAndReturn<CVector&, 0x56E090, int>(playerId);
}

// 0x56E120
CEntity* FindPlayerEntity(int playerId) {
    auto player = FindPlayerPed(playerId);
    if (player->bInVehicle && player->m_pVehicle) 
        return player->m_pVehicle;

    return player;
}

CVehicle* FindPlayerVehicle(int playerId)
{
    auto pPed = FindPlayerPed(playerId);
    if (pPed && pPed->bInVehicle)
        return pPed->m_pVehicle;
    else
        return nullptr;
}

// 0x56E160
CTrain* FindPlayerTrain(int playerId) {
    auto vehicle = FindPlayerVehicle(playerId);
    if (vehicle && vehicle->IsTrain())
        return vehicle->AsTrain();
    else
        return nullptr;
}

// 0x56E250
CVector const& FindPlayerCentreOfWorld(int playerId) {
    return ((CVector const&(__cdecl*)(int))0x56E250)(playerId);
}

// 0x56E320
CVector const& FindPlayerCentreOfWorld_NoSniperShift(int playerId) {
    return ((CVector const&(__cdecl*)(int))0x56E320)(playerId);
}

// 0x56E400
CVector FindPlayerCentreOfWorld_NoInteriorShift(int playerId) {
    return ((CVector(__cdecl*)(int))0x56E400)(playerId);
}

// 0x56E450
float FindPlayerHeading(int playerId) {
    return ((float(__cdecl*)(int))0x56E450)(playerId);
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
CPlayerPed* FindPlayerPed(int playerId) {
    return CWorld::Players[(playerId < 0 ? CWorld::PlayerInFocus : playerId)].m_pPed;
}

// 0x56E0D0
CAutomobile* FindPlayerVehicle(int playerId, bool bIncludeRemote) {
    return ((CAutomobile *(__cdecl *)(int, bool))0x56E0D0)(playerId, bIncludeRemote);

    CPlayerInfo playerInfo = CWorld::Players[(playerId < 0 ? CWorld::PlayerInFocus : playerId)];

    if (!playerInfo.m_pPed || (playerInfo.m_pPed->m_nPedFlags & 0x100) == 0) {
        return nullptr;
    }
    if (!bIncludeRemote || (playerInfo.m_pRemoteVehicle) == nullptr) {
        return static_cast<CAutomobile*>(playerInfo.m_pPed->m_pVehicle);
    }

    return nullptr;
}

// 0x56E230
CWanted* FindPlayerWanted(int playerId) {
    return CWorld::Players[(playerId < 0 ? CWorld::PlayerInFocus : playerId)].m_PlayerData.m_pWanted;
}

// TODO: Rename CGameLogic::IsCoopGameGoingOn
// 0x441390
bool InTwoPlayersMode() {
    return CWorld::Players[0].m_pPed && CWorld::Players[1].m_pPed;
}

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
void TransformVectors(RwV3d* vecsOut, int numVectors, CMatrix const& matrix, RwV3d const* vecsin) {
    plugin::Call<0x54EEA0, RwV3d*, int, CMatrix const&, RwV3d const*>(vecsOut, numVectors, matrix, vecsin);
}

// 0x54EE30
void TransformVectors(RwV3d* vecsOut, int numVectors, CSimpleTransform const& transform, RwV3d const* vecsin) {
    plugin::Call<0x54EE30, RwV3d*, int, CSimpleTransform const&, RwV3d const*>(vecsOut, numVectors, transform, vecsin);
}

// 0x4D62A0
AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, char* name) {
    return ((AnimBlendFrameData * (__cdecl*)(RpClump*, char*))0x4D62A0)(clump, name);
}

// 0x7186E0
char* MakeUpperCase(char* dest, char* src) {
    return ((char*(__cdecl*)(char*, char*))0x7186E0)(dest, src);
}

// 0x734610
void CreateDebugFont() {
    // NOP
}

// 0x4ABA50
CEventGroup* GetEventGlobalGroup() {
    return plugin::CallAndReturn<CEventGroup*, 0x4ABA50>();
}

// 0x734620
void DestroyDebugFont() {
    // NOP
}

// unused
// 0x734630
void ObrsPrintfString(char const* arg0, short arg1, short arg2) {
    // NOP
}

// 0x734640
void FlushObrsPrintfs() {
    // NOP
}

// 0x734650
void DefinedState() {
    CRGBA rgbaFog(
        CTimeCycle::m_CurrentColours.m_nSkyBottomRed,
        CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
        CTimeCycle::m_CurrentColours.m_nSkyBottomBlue
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

// Converted from cdecl RpAtomic* GetFirstAtomicCallback(RpAtomic *atomic,void *data) 0x734810
RpAtomic* GetFirstAtomicCallback(RpAtomic* atomic, void* data) {
    return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x734810)(atomic, data);
}

// Converted from cdecl RpAtomic* GetFirstAtomic(RpClump *clump) 0x734820
RpAtomic* GetFirstAtomic(RpClump* clump) {
    return ((RpAtomic* (__cdecl *)(RpClump*))0x734820)(clump);
}

// Converted from cdecl RpAtomic* Get2DEffectAtomicCallback(RpAtomic *atomic,void *data) 0x734850
RpAtomic* Get2DEffectAtomicCallback(RpAtomic* atomic, void* data) {
    return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x734850)(atomic, data);
}

// Converted from cdecl RpAtomic* Get2DEffectAtomic(RpClump *clump) 0x734880
RpAtomic* Get2DEffectAtomic(RpClump* clump) {
    return ((RpAtomic* (__cdecl *)(RpClump*))0x734880)(clump);
}

// Converted from cdecl RwObject* GetFirstObjectCallback(RwObject *object,void *data) 0x7348B0
RwObject* GetFirstObjectCallback(RwObject* object, void* data) {
    return ((RwObject* (__cdecl *)(RwObject*, void*))0x7348B0)(object, data);
}

// Converted from cdecl RwObject* GetFirstObject(RwFrame *frame) 0x7348C0
RwObject* GetFirstObject(RwFrame* frame) {
    return ((RwObject* (__cdecl *)(RwFrame*))0x7348C0)(frame);
}

// Converted from cdecl RwFrame* GetFirstFrameCallback(RwFrame *frame,void *data) 0x7348F0
RwFrame* GetFirstFrameCallback(RwFrame* frame, void* data) {
    return ((RwFrame* (__cdecl *)(RwFrame*, void*))0x7348F0)(frame, data);
}

// Converted from cdecl RwFrame* GetFirstChild(RwFrame *frame) 0x734900
RwFrame* GetFirstChild(RwFrame* frame) {
    return ((RwFrame* (__cdecl *)(RwFrame*))0x734900)(frame);
}

// Converted from cdecl RpHAnimHierarchy* GetAnimHierarchyFromSkinClump(RpClump *clump) 0x734A40
RpHAnimHierarchy* GetAnimHierarchyFromSkinClump(RpClump* clump) {
    return ((RpHAnimHierarchy* (__cdecl *)(RpClump*))0x734A40)(clump);
}

// Converted from cdecl RpHAnimHierarchy* GetAnimHierarchyFromFrame(RwFrame *frame) 0x734AB0
RpHAnimHierarchy* GetAnimHierarchyFromFrame(RwFrame* frame) {
    return ((RpHAnimHierarchy* (__cdecl *)(RwFrame*))0x734AB0)(frame);
}

// Converted from cdecl RpHAnimHierarchy* GetAnimHierarchyFromClump(RpClump *clump) 0x734B10
RpHAnimHierarchy* GetAnimHierarchyFromClump(RpClump* clump) {
    return ((RpHAnimHierarchy* (__cdecl *)(RpClump*))0x734B10)(clump);
}

// Converted from cdecl RpAtomic* AtomicRemoveAnimFromSkinCB(RpAtomic *atomic,void *data) 0x734B90
RpAtomic* AtomicRemoveAnimFromSkinCB(RpAtomic* atomic, void* data) {
    return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x734B90)(atomic, data);
}

// Converted from cdecl bool RpAtomicConvertGeometryToTL(RpAtomic *atomic) 0x734BE0
bool RpAtomicConvertGeometryToTL(RpAtomic* atomic) {
    return ((bool(__cdecl *)(RpAtomic*))0x734BE0)(atomic);
}

// Converted from cdecl bool RpAtomicConvertGeometryToTS(RpAtomic *atomic) 0x734C20
bool RpAtomicConvertGeometryToTS(RpAtomic* atomic) {
    return ((bool(__cdecl *)(RpAtomic*))0x734C20)(atomic);
}

// Converted from cdecl bool RpClumpConvertGeometryToTL(RpClump *clump) 0x734CB0
bool RpClumpConvertGeometryToTL(RpClump* clump) {
    return ((bool(__cdecl *)(RpClump*))0x734CB0)(clump);
}

// Converted from cdecl bool RpClumpConvertGeometryToTS(RpClump *clump) 0x734D30
bool RpClumpConvertGeometryToTS(RpClump* clump) {
    return ((bool(__cdecl *)(RpClump*))0x734D30)(clump);
}

// Converted from cdecl RpMaterial* forceLinearFilteringMatTexturesCB(RpMaterial *material,void *data) 0x734D60
RpMaterial* forceLinearFilteringMatTexturesCB(RpMaterial* material, void* data) {
    return ((RpMaterial* (__cdecl *)(RpMaterial*, void*))0x734D60)(material, data);
}

// Converted from cdecl bool SetFilterModeOnAtomicsTextures(RpAtomic *atomic,RwTextureFilterMode filtering) 0x734D80
bool SetFilterModeOnAtomicsTextures(RpAtomic* atomic, RwTextureFilterMode filtering) {
    return ((bool(__cdecl *)(RpAtomic*, RwTextureFilterMode))0x734D80)(atomic, filtering);
}

// Converted from cdecl RpAtomic* forceLinearFilteringAtomicsCB(RpAtomic *atomic,void *data) 0x734DA0
RpAtomic* forceLinearFilteringAtomicsCB(RpAtomic* atomic, void* data) {
    return ((RpAtomic* (__cdecl *)(RpAtomic*, void*))0x734DA0)(atomic, data);
}

// Converted from cdecl bool SetFilterModeOnClumpsTextures(RpClump *clump,RwTextureFilterMode filtering) 0x734DC0
bool SetFilterModeOnClumpsTextures(RpClump* clump, RwTextureFilterMode filtering) {
    return ((bool(__cdecl *)(RpClump*, RwTextureFilterMode))0x734DC0)(clump, filtering);
}

// Converted from cdecl bool RpGeometryReplaceOldMaterialWithNewMaterial(RpGeometry *geometry,RpMaterial *oldMaterial,RpMaterial *newMaterial) 0x734DE0
bool RpGeometryReplaceOldMaterialWithNewMaterial(RpGeometry* geometry, RpMaterial* oldMaterial, RpMaterial* newMaterial) {
    return ((bool(__cdecl *)(RpGeometry*, RpMaterial*, RpMaterial*))0x734DE0)(geometry, oldMaterial, newMaterial);
}

// Converted from cdecl RwTexture* RwTexDictionaryFindHashNamedTexture(RwTexDictionary *txd,uint hash) 0x734E50
RwTexture* RwTexDictionaryFindHashNamedTexture(RwTexDictionary* txd, unsigned int hash) {
    return ((RwTexture* (__cdecl *)(RwTexDictionary*, unsigned int))0x734E50)(txd, hash);
}

// Converted from cdecl RpClump* RpClumpGetBoundingSphere(RpClump *clump,RwSphere *bound,bool) 0x734FC0
RpClump* RpClumpGetBoundingSphere(RpClump* clump, RwSphere* bound, bool arg2) {
    return ((RpClump* (__cdecl *)(RpClump*, RwSphere*, bool))0x734FC0)(clump, bound, arg2);
}

// Converted from cdecl void SkinGetBonePositions(RpClump *clump) 0x735140
void SkinGetBonePositions(RpClump* clump) {
    ((void(__cdecl *)(RpClump*))0x735140)(clump);
}

// Converted from cdecl void SkinSetBonePositions(RpClump *clump) 0x7352D0
void SkinSetBonePositions(RpClump* clump) {
    ((void(__cdecl *)(RpClump*))0x7352D0)(clump);
}

// Converted from cdecl void SkinGetBonePositionsToTable(RpClump *clump,RwV3d *table) 0x735360
void SkinGetBonePositionsToTable(RpClump* clump, RwV3d* table) {
    ((void(__cdecl *)(RpClump*, RwV3d*))0x735360)(clump, table);
}

// 0x7354E0
void SetLightsWithTimeOfDayColour(RpWorld* world) {
    ((void(__cdecl *)(RpWorld*))0x7354E0)(world);
    return;

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

        RwMatrix* out[6];
        /*
        out[0].x = 0.0;
        out[0].y = 0.0;
        out[0].z = 1.0;

        CVector in = CrossProduct({0.0f, 0.0f, 1.0f}, sun2Dir);
        in.Normalise();
        CVector vecCross = CrossProduct(in, sun2Dir);

        out[1].x = vecCross.x;
        out[1].y = vecCross.y;
        out[1].z = vecCross.z;

        out[2] = in;

        out[3].z = -sun2Dir.x;

        out[4].x = -sun2Dir.y;
        out[4].y = -sun2Dir.z;
        */

        auto* parentFrame = static_cast<RwFrame*>(pDirect->object.object.parent);
        RwFrameTransform(parentFrame, reinterpret_cast<const RwMatrix*>(&out), RwOpCombineType::rwCOMBINEREPLACE);
    }
}

// unused
// 0x735720
void LightsEnable(int arg0) {
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

// Converted from cdecl void AddAnExtraDirectionalLight(RpWorld *world,float x,float y,float z,float red,float green,float blue) 0x735840
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
void SetAmbientColoursToIndicateRoadGroup(int arg0) {
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
    ((void(__cdecl *)())0x735E40)();
    return;

//    RpLightSetColor(pAmbient, CPostEffects::m_fInfraredVisionHeatObjectCol);
//    RpLightSetColor(pDirect, CPostEffects::m_fInfraredVisionHeatObjectCol);
}

// 0x735E70
void StoreAndSetLightsForInfraredVisionHeatObjects() {
//    ((void(__cdecl *)())0x735E70)();
//    return;

//    DirectAmbientLight[1] = AmbientLightColour;
//    DirectAmbientLight[0] = DirectionalLightColour;
//    RpLightSetColor(pAmbient, CPostEffects::m_fInfraredVisionHeatObjectCol);
//    RpLightSetColor(pDirect, CPostEffects::m_fInfraredVisionHeatObjectCol);
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
    return plugin::CallAndReturn<float, 0x6FAB30>();
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

// Converted from cdecl CAnimBlendClumpData* RpAnimBlendAllocateData(RpClump *clump) 0x4D5F50
CAnimBlendClumpData* RpAnimBlendAllocateData(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendClumpData*, 0x4D5F50, RpClump*>(clump);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpAddAssociation(RpClump *clump,CAnimBlendAssociation *association,uint flags,float startTime,float blendAmount) 0x4D6790
CAnimBlendAssociation* RpAnimBlendClumpAddAssociation(RpClump* clump, CAnimBlendAssociation* association, unsigned int flags, float startTime, float blendAmount) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6790, RpClump*, CAnimBlendAssociation*, unsigned int, float, float>(clump, association, flags, startTime, blendAmount);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpExtractAssociations(RpClump *clump) 0x4D6BE0
CAnimBlendAssociation* RpAnimBlendClumpExtractAssociations(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6BE0, RpClump*>(clump);
}

// Converted from cdecl void RpAnimBlendClumpFillFrameArray(RpClump *clump,AnimBlendFrameData **frameData) 0x4D64A0
void RpAnimBlendClumpFillFrameArray(RpClump* clump, AnimBlendFrameData** frameData) {
    plugin::Call<0x4D64A0, RpClump*, AnimBlendFrameData**>(clump, frameData);
}

// Converted from cdecl AnimBlendFrameData* RpAnimBlendClumpFindBone(RpClump *clump,uint id) 0x4D6400
AnimBlendFrameData* RpAnimBlendClumpFindBone(RpClump* clump, unsigned int id) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D6400, RpClump*, unsigned int>(clump, id);
}

// Converted from cdecl AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump *clump,char const*name) 0x4D62A0
AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, char const* name) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D62A0, RpClump*, char const*>(clump, name);
}

// Converted from cdecl AnimBlendFrameData* RpAnimBlendClumpFindFrameFromHashKey(RpClump *clump,uint key) 0x4D6370
AnimBlendFrameData* RpAnimBlendClumpFindFrameFromHashKey(RpClump* clump, unsigned int key) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D6370, RpClump*, unsigned int>(clump, key);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump *clump,bool,CAnimBlendHierarchy *hierarchy) 0x4D68E0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, bool arg1, CAnimBlendHierarchy* hierarchy) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D68E0, RpClump*, bool, CAnimBlendHierarchy*>(clump, arg1, hierarchy);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump *clump,char const*name) 0x4D6870
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, char const* name) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6870, RpClump*, char const*>(clump, name);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump *clump,uint animId) 0x4D68B0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, unsigned int animId) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D68B0, RpClump*, unsigned int>(clump, animId);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump *clump) 0x4D15E0
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D15E0, RpClump*>(clump);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump *clump,uint flags) 0x4D6A70
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump, unsigned int flags) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6A70, RpClump*, unsigned int>(clump, flags);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation(RpClump *clump,CAnimBlendAssociation **pAssociation,float *blendAmount) 0x4D6910
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation(RpClump* clump, CAnimBlendAssociation** pAssociation, float* blendAmount) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6910, RpClump*, CAnimBlendAssociation**, float*>(clump, pAssociation, blendAmount);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation_N(RpClump *clump,int n) 0x4D6A30
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation_N(RpClump* clump, int n) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6A30, RpClump*, int>(clump, n);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation(RpClump *clump) 0x4D69A0
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D69A0, RpClump*>(clump);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation_N(RpClump *clump,int n) 0x4D69F0
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation_N(RpClump* clump, int n) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D69F0, RpClump*, int>(clump, n);
}

// Converted from cdecl uint RpAnimBlendClumpGetNumAssociations(RpClump *clump) 0x4D6B60
unsigned int RpAnimBlendClumpGetNumAssociations(RpClump* clump) {
    return plugin::CallAndReturn<unsigned int, 0x4D6B60, RpClump*>(clump);
}

// Converted from cdecl uint RpAnimBlendClumpGetNumNonPartialAssociations(RpClump *clump) 0x4D6BB0
unsigned int RpAnimBlendClumpGetNumNonPartialAssociations(RpClump* clump) {
    return plugin::CallAndReturn<unsigned int, 0x4D6BB0, RpClump*>(clump);
}

// Converted from cdecl uint RpAnimBlendClumpGetNumPartialAssociations(RpClump *clump) 0x4D6B80
unsigned int RpAnimBlendClumpGetNumPartialAssociations(RpClump* clump) {
    return plugin::CallAndReturn<unsigned int, 0x4D6B80, RpClump*>(clump);
}

// Converted from cdecl void RpAnimBlendClumpGiveAssociations(RpClump *clump,CAnimBlendAssociation *association) 0x4D6C30
void RpAnimBlendClumpGiveAssociations(RpClump* clump, CAnimBlendAssociation* association) {
    plugin::Call<0x4D6C30, RpClump*, CAnimBlendAssociation*>(clump, association);
}

// Converted from cdecl void RpAnimBlendClumpInit(RpClump *clump) 0x4D6720
void RpAnimBlendClumpInit(RpClump* clump) {
    plugin::Call<0x4D6720, RpClump*>(clump);
}

// Converted from cdecl bool RpAnimBlendClumpIsInitialized(RpClump *clump) 0x4D6760
bool RpAnimBlendClumpIsInitialized(RpClump* clump) {
    return plugin::CallAndReturn<bool, 0x4D6760, RpClump*>(clump);
}

// Converted from cdecl void RpAnimBlendClumpPauseAllAnimations(RpClump *clump) 0x4D6B00
void RpAnimBlendClumpPauseAllAnimations(RpClump* clump) {
    plugin::Call<0x4D6B00, RpClump*>(clump);
}

// Converted from cdecl void RpAnimBlendClumpRemoveAllAssociations(RpClump *clump) 0x4D6C00
void RpAnimBlendClumpRemoveAllAssociations(RpClump* clump) {
    plugin::Call<0x4D6C00, RpClump*>(clump);
}

// Converted from cdecl void RpAnimBlendClumpRemoveAssociations(RpClump *clump,uint flags) 0x4D6820
void RpAnimBlendClumpRemoveAssociations(RpClump* clump, unsigned int flags) {
    plugin::Call<0x4D6820, RpClump*, unsigned int>(clump, flags);
}

// Converted from cdecl void RpAnimBlendClumpSetBlendDeltas(RpClump *clump,uint flags,float delta) 0x4D67E0
void RpAnimBlendClumpSetBlendDeltas(RpClump* clump, unsigned int flags, float delta) {
    plugin::Call<0x4D67E0, RpClump*, unsigned int, float>(clump, flags, delta);
}

// Converted from cdecl void RpAnimBlendClumpUnPauseAllAnimations(RpClump *clump) 0x4D6B30
void RpAnimBlendClumpUnPauseAllAnimations(RpClump* clump) {
    plugin::Call<0x4D6B30, RpClump*>(clump);
}

// Converted from cdecl void RpAnimBlendClumpUpdateAnimations(RpClump *clump,float step,bool onScreen) 0x4D34F0
void RpAnimBlendClumpUpdateAnimations(RpClump* clump, float step, bool onScreen) {
    plugin::Call<0x4D34F0, RpClump*, float, bool>(clump, step, onScreen);
}

// Converted from cdecl RtAnimAnimation* RpAnimBlendCreateAnimationForHierarchy(RpHAnimHierarchy *hierarchy) 0x4D60E0
RtAnimAnimation* RpAnimBlendCreateAnimationForHierarchy(RpHAnimHierarchy* hierarchy) {
    return plugin::CallAndReturn<RtAnimAnimation*, 0x4D60E0, RpHAnimHierarchy*>(hierarchy);
}

// Converted from cdecl char* RpAnimBlendFrameGetName(RwFrame *frame) 0x4D5EF0
char* RpAnimBlendFrameGetName(RwFrame* frame) {
    return plugin::CallAndReturn<char*, 0x4D5EF0, RwFrame*>(frame);
}

// Converted from cdecl void RpAnimBlendFrameSetName(RwFrame *frame,char *name) 0x4D5F00
void RpAnimBlendFrameSetName(RwFrame* frame, char* name) {
    plugin::Call<0x4D5F00, RwFrame*, char*>(frame, name);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation *association) 0x4D6AB0
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6AB0, CAnimBlendAssociation*>(association);
}

// Converted from cdecl CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation *association,uint flags) 0x4D6AD0
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association, unsigned int flags) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6AD0, CAnimBlendAssociation*, unsigned int>(association, flags);
}

// Converted from cdecl void RpAnimBlendKeyFrameInterpolate(void *voidOut,void *voidIn1,void *voidIn2,float time,void *customData) 0x4D60C0
void RpAnimBlendKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, float time, void* customData) {
    plugin::Call<0x4D60C0, void*, void*, void*, float, void*>(voidOut, voidIn1, voidIn2, time, customData);
}

// Converted from cdecl bool RpAnimBlendPluginAttach(void) 0x4D6150
bool RpAnimBlendPluginAttach() {
    return plugin::CallAndReturn<bool, 0x4D6150>();
}

// US-1.00 @ 0x005A4150
// EU-1.00 @ 0x005A4150
void WriteRaster(RwRaster * pRaster, char const * pszPath) {
    assert(pRaster);
    assert(pszPath && pszPath[0]);
    plugin::Call<0x005A4150>(pRaster, pszPath);
}

// 0x71DA00
bool CalcScreenCoors(CVector const& vecPoint, CVector* pVecOutPos, float* pScreenX, float* pScreenY)
{
    return plugin::CallAndReturn<bool, 0x71DA00, CVector const&, CVector*, float*, float*>(vecPoint, pVecOutPos, pScreenX, pScreenY);
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

// 0x53E230
void Render2dStuff() {
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)false);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)false);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)true);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)rwRENDERSTATENARENDERSTATE);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
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

    int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.data(), str.length(), nullptr, 0);
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

    int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str.data(), str.length(), nullptr, 0, nullptr, nullptr);
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

int WindowsCharset = static_cast<int>(GetACP());

unsigned short& uiTempBufferIndicesStored = *(unsigned short*)0xC4B954;
unsigned short& uiTempBufferVerticesStored = *(unsigned short*)0xC4B950;
RxVertexIndex(&aTempBufferIndices)[TOTAL_TEMP_BUFFER_INDICES] = *(RxVertexIndex(*)[TOTAL_TEMP_BUFFER_INDICES])0xC4B958;
RxObjSpace3DVertex(&aTempBufferVertices)[TOTAL_TEMP_BUFFER_VERTICES] = *(RxObjSpace3DVertex(*)[TOTAL_TEMP_BUFFER_VERTICES])0xC4D958; // size 1024 - after this there are 2 more arrays like this, both sized 512
RwD3D9Vertex(&aRadiosityVertexBuffer)[TOTAL_RADIOSITY_VERTEX_BUFFER] = *reinterpret_cast<RwD3D9Vertex(*)[TOTAL_RADIOSITY_VERTEX_BUFFER]>(0xC5F958);
