/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

int gDefaultTaskTime = 9999999; // or 0x98967F a.k.a (one milllion - 1)
char *gString = (char *)0xB71670;

float &GAME_GRAVITY = *(float *)0x863984;

char *&PC_Scratch = *reinterpret_cast<char **>(0xC8E0C8);

CVector FindPlayerCoors(int playerId)
{
    return ((CVector(__cdecl *)(int))0x56E010)(playerId);
}

CVector const& FindPlayerSpeed(int playerId)
{
    return ((CVector const& (__cdecl *)(int))0x56E090)(playerId);
}

CEntity * FindPlayerEntity(int playerId)
{
    return ((CEntity *(__cdecl *)(int))0x56E120)(playerId);
}

CVector const& FindPlayerCentreOfWorld(int playerId)
{
    return ((CVector const& (__cdecl *)(int))0x56E250)(playerId);
}

CVector const& FindPlayerCentreOfWorld_NoSniperShift(int playerId)
{
    return ((CVector const& (__cdecl *)(int))0x56E320)(playerId);
}

CVector FindPlayerCentreOfWorld_NoInteriorShift(int playerId)
{
    return ((CVector(__cdecl *)(int))0x56E400)(playerId);
}

float FindPlayerHeading(int playerId)
{
    return ((float(__cdecl *)(int))0x56E450)(playerId);
}

float FindPlayerHeight()
{
    return ((float(__cdecl *)())0x56E520)();
}

CPlayerPed * FindPlayerPed(int playerId)
{
    return ((CPlayerPed *(__cdecl *)(int))0x56E210)(playerId);
}

CAutomobile * FindPlayerVehicle(int playerId, bool bIncludeRemote)
{
    return ((CAutomobile *(__cdecl *)(int, bool))0x56E0D0)(playerId, bIncludeRemote);
}

bool InTwoPlayersMode()
{
    return ((bool(__cdecl *)())0x441390)();
}

CVector * VectorSub(CVector * out, CVector * from, CVector * what)
{
    return ((CVector *(__cdecl *)(CVector *, CVector *, CVector *))0x40FE60)(out, from, what);
}

CVector* MultiplyMatrixWithVector(CVector* outPoint, CMatrix* m, CVector* point)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<CVector*, 0x59C890, CVector*, CMatrix*, CVector*> (outPoint, m, point);
#else
    outPoint->x = m->at.x * point->z + m->up.x * point->y + m->right.x * point->x + m->pos.x;
    outPoint->y = m->at.y * point->z + m->right.y * point->x + m->up.y * point->y + m->pos.y;
    outPoint->z = m->at.z * point->z + m->right.z * point->x + m->up.z * point->y + m->pos.z;
    return outPoint;
#endif
}

CVector Multiply3x3(CMatrix  const& matrix, CVector  const& vec)
{
    return ((CVector(__cdecl *)(CMatrix  const&, CVector  const&))0x59C790)(matrix, vec);
}

CWanted * FindPlayerWanted(int playerId)
{
    return ((CWanted*(__cdecl *)(int))0x56E230)(playerId);
}

unsigned int &ClumpOffset = *(unsigned int *)0xB5F878;

AnimBlendFrameData *RpAnimBlendClumpFindFrame(RpClump *clump, char *name)
{
    return ((AnimBlendFrameData *(__cdecl *)(RpClump *, char *))0x4D62A0)(clump, name);
}

char *MakeUpperCase(char *dest, char *src)
{
    return ((char *(__cdecl *)(char *, char *))0x7186E0)(dest, src);
}

// Converted from cdecl void CreateDebugFont(void) 0x734610
void CreateDebugFont() {
    ((void(__cdecl *)())0x734610)();
}

// Converted from cdecl void DestroyDebugFont(void) 0x734620
void DestroyDebugFont() {
    ((void(__cdecl *)())0x734620)();
}

// Converted from cdecl void ObrsPrintfString(char const*,short,short) 0x734630
void ObrsPrintfString(char const* arg0, short arg1, short arg2) {
    ((void(__cdecl *)(char const*, short, short))0x734630)(arg0, arg1, arg2);
}

// Converted from cdecl void FlushObrsPrintfs(void) 0x734640
void FlushObrsPrintfs() {
    ((void(__cdecl *)())0x734640)();
}

// Converted from cdecl void DefinedState(void) 0x734650
void DefinedState() {
    ((void(__cdecl *)())0x734650)();
}

// Converted from cdecl void DefinedState2d(void) 0x734750
void DefinedState2d() {
    ((void(__cdecl *)())0x734750)();
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

// Converted from cdecl RwTexture* GetFirstTextureCallback(RwTexture *texture,void *data) 0x734930
RwTexture* GetFirstTextureCallback(RwTexture* texture, void* data) {
    return ((RwTexture* (__cdecl *)(RwTexture*, void*))0x734930)(texture, data);
}

// Converted from cdecl RwTexture* GetFirstTexture(RwTexDictionary *txd) 0x734940
RwTexture* GetFirstTexture(RwTexDictionary* txd) {
    return ((RwTexture* (__cdecl *)(RwTexDictionary*))0x734940)(txd);
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

// Converted from cdecl void SetLightsWithTimeOfDayColour(RpWorld *world) 0x7354E0
void SetLightsWithTimeOfDayColour(RpWorld* world) {
    ((void(__cdecl *)(RpWorld*))0x7354E0)(world);
}

// Converted from cdecl void LightsEnable(int) 0x735720
void LightsEnable(int arg0) {
    ((void(__cdecl *)(int))0x735720)(arg0);
}

// Converted from cdecl RpWorld* LightsDestroy(RpWorld *world) 0x735730
RpWorld* LightsDestroy(RpWorld* world) {
    return ((RpWorld* (__cdecl *)(RpWorld*))0x735730)(world);
}

// Converted from cdecl void WorldReplaceNormalLightsWithScorched(RpWorld *world,float lighting) 0x7357E0
void WorldReplaceNormalLightsWithScorched(RpWorld* world, float lighting) {
    ((void(__cdecl *)(RpWorld*, float))0x7357E0)(world, lighting);
}

// Converted from cdecl void WorldReplaceScorchedLightsWithNormal(RpWorld *world) 0x735820
void WorldReplaceScorchedLightsWithNormal(RpWorld* world) {
    ((void(__cdecl *)(RpWorld*))0x735820)(world);
}

// Converted from cdecl void AddAnExtraDirectionalLight(RpWorld *world,float x,float y,float z,float red,float green,float blue) 0x735840
void AddAnExtraDirectionalLight(RpWorld* world, float x, float y, float z, float red, float green, float blue) {
    ((void(__cdecl *)(RpWorld*, float, float, float, float, float, float))0x735840)(world, x, y, z, red, green, blue);
}

// Converted from cdecl void RemoveExtraDirectionalLights(RpWorld *world) 0x7359E0
void RemoveExtraDirectionalLights(RpWorld* world) {
    ((void(__cdecl *)(RpWorld*))0x7359E0)(world);
}

// Converted from cdecl void SetAmbientAndDirectionalColours(float lighting) 0x735A20
void SetAmbientAndDirectionalColours(float lighting) {
    ((void(__cdecl *)(float))0x735A20)(lighting);
}

// Converted from cdecl void SetFlashyColours(float lighting) 0x735AB0
void SetFlashyColours(float lighting) {
    ((void(__cdecl *)(float))0x735AB0)(lighting);
}

// Converted from cdecl void SetFlashyColours_Mild(float lighting) 0x735B40
void SetFlashyColours_Mild(float lighting) {
    ((void(__cdecl *)(float))0x735B40)(lighting);
}

// Converted from cdecl void SetBrightMarkerColours(float lighting) 0x735BD0
void SetBrightMarkerColours(float lighting) {
    ((void(__cdecl *)(float))0x735BD0)(lighting);
}

// Converted from cdecl void ReSetAmbientAndDirectionalColours(void) 0x735C40
void ReSetAmbientAndDirectionalColours() {
    ((void(__cdecl *)())0x735C40)();
}

// Converted from cdecl void DeActivateDirectional(void) 0x735C70
void DeActivateDirectional() {
    ((void(__cdecl *)())0x735C70)();
}

// Converted from cdecl void ActivateDirectional(void) 0x735C80
void ActivateDirectional() {
    ((void(__cdecl *)())0x735C80)();
}

// Converted from cdecl void SetAmbientColoursToIndicateRoadGroup(int) 0x735C90
void SetAmbientColoursToIndicateRoadGroup(int arg0) {
    ((void(__cdecl *)(int))0x735C90)(arg0);
}

// Converted from cdecl void SetFullAmbient(void) 0x735D10
void SetFullAmbient() {
    ((void(__cdecl *)())0x735D10)();
}

// Converted from cdecl void SetAmbientColours(void) 0x735D30
void SetAmbientColours() {
    ((void(__cdecl *)())0x735D30)();
}

// Converted from cdecl void SetAmbientColours(RwRGBAReal *color) 0x735D50
void SetAmbientColours(RwRGBAReal* color) {
    ((void(__cdecl *)(RwRGBAReal*))0x735D50)(color);
}

// Converted from cdecl void SetDirectionalColours(RwRGBAReal *color) 0x735D70
void SetDirectionalColours(RwRGBAReal* color) {
    ((void(__cdecl *)(RwRGBAReal*))0x735D70)(color);
}

// Converted from cdecl void SetLightColoursForPedsCarsAndObjects(float lighting) 0x735D90
void SetLightColoursForPedsCarsAndObjects(float lighting) {
    ((void(__cdecl *)(float))0x735D90)(lighting);
}

// Converted from cdecl void SetLightsForInfraredVisionHeatObjects(void) 0x735E40
void SetLightsForInfraredVisionHeatObjects() {
    ((void(__cdecl *)())0x735E40)();
}

// Converted from cdecl void StoreAndSetLightsForInfraredVisionHeatObjects(void) 0x735E70
void StoreAndSetLightsForInfraredVisionHeatObjects() {
    ((void(__cdecl *)())0x735E70)();
}

// Converted from cdecl void RestoreLightsForInfraredVisionHeatObjects(void) 0x735EF0
void RestoreLightsForInfraredVisionHeatObjects() {
    ((void(__cdecl *)())0x735EF0)();
}

// Converted from cdecl void SetLightsForInfraredVisionDefaultObjects(void) 0x735F20
void SetLightsForInfraredVisionDefaultObjects() {
    ((void(__cdecl *)())0x735F20)();
}

// Converted from cdecl void SetLightsForNightVision(void) 0x735F70
void SetLightsForNightVision() {
    ((void(__cdecl *)())0x735F70)();
}

// Converted from cdecl RpAtomic* RemoveRefsCB(RpAtomic *atomic, void *data) 0x7226D0
RpAtomic* RemoveRefsCB(RpAtomic* atomic, void* _IGNORED_ data) {
    return plugin::CallAndReturn<RpAtomic*, 0x7226D0, RpAtomic*, void*>(atomic, data);
}

// Converted from cdecl void RemoveRefsForAtomic(RpClump *clump) 0x7226F0
void RemoveRefsForAtomic(RpClump* clump) {
    plugin::Call<0x7226F0, RpClump*>(clump);
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

void AsciiToGxtChar(char const *src, char *dst) {
    plugin::Call<0x718600, char const *, char *>(src, dst);
}

// US-1.00 @ 0x005A4150
// EU-1.00 @ 0x005A4150
void WriteRaster(RwRaster * pRaster, char const * pszPath) {
    assert(pRaster);
    assert(pszPath && pszPath[0]);
    plugin::Call<0x005A4150>(pRaster, pszPath);
}
