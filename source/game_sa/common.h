/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <string>

#include "CVector.h"
#include "CEntity.h"
#include "CPlayerPed.h"
#include "CVehicle.h"
#include "CWeaponInfo.h"
#include "CAnimBlendAssociation.h"
#include "CAnimBlendClumpData.h"

const char gta_empty_string[4] = {0, 0, 0, 0};

#define DEFAULT_SCREEN_WIDTH (640.0f)
#define DEFAULT_SCREEN_HEIGHT (448.0f)
#define DEFAULT_SCREEN_HEIGHT_PAL (512.0f)
#define DEFAULT_SCREEN_HEIGHT_NTSC (448.0f)
#define DEFAULT_ASPECT_RATIO (4.0f/3.0f)
#define DEFAULT_VIEWWINDOW (0.7f)

// game uses maximumWidth/Height, but this probably won't work
// with RW windowed mode
#define SCREEN_WIDTH ((float)RsGlobal.maximumWidth)
#define SCREEN_HEIGHT ((float)RsGlobal.maximumHeight)
#define SCREEN_ASPECT_RATIO (CDraw::ms_fAspectRatio)
#define SCREEN_VIEWWINDOW (Tan(DEGTORAD(CDraw::GetScaledFOV() * 0.5f)))
#define SCREEN_WIDTH_UNIT (SCREEN_WIDTH / 640.0f)
#define SCREEN_HEIGHT_UNIT (SCREEN_HEIGHT / 448.0f)

// This scales from PS2 pixel coordinates to the real resolution
#define SCREEN_STRETCH_X(a)   ((a) * (float) SCREEN_WIDTH / DEFAULT_SCREEN_WIDTH)
#define SCREEN_STRETCH_Y(a)   ((a) * (float) SCREEN_HEIGHT / DEFAULT_SCREEN_HEIGHT)
#define SCREEN_STRETCH_FROM_RIGHT(a)  (SCREEN_WIDTH - SCREEN_STRETCH_X(a))
#define SCREEN_STRETCH_FROM_BOTTOM(a) (SCREEN_HEIGHT - SCREEN_STRETCH_Y(a))

// This scales from PS2 pixel coordinates while optionally maintaining the aspect ratio
#define SCREEN_SCALE_X(a) SCREEN_SCALE_AR(SCREEN_STRETCH_X(a))
#define SCREEN_SCALE_Y(a) SCREEN_STRETCH_Y(a)
#define SCREEN_SCALE_FROM_RIGHT(a) (SCREEN_WIDTH - SCREEN_SCALE_X(a))
#define SCREEN_SCALE_FROM_BOTTOM(a) (SCREEN_HEIGHT - SCREEN_SCALE_Y(a))

#define ASPECT_RATIO_SCALE
#ifdef ASPECT_RATIO_SCALE
#define SCREEN_SCALE_AR(a) ((a) * DEFAULT_ASPECT_RATIO / SCREEN_ASPECT_RATIO)
#else
#define SCREEN_SCALE_AR(a) (a)
#endif

extern int32 gDefaultTaskTime;

extern char *gString; // char gString[200]

extern float &GAME_GRAVITY; // default 0.0080000004

extern char(&PC_Scratch)[16384];

extern float& gfLaRiotsLightMult;

const uint32 rwVENDORID_ROCKSTAR = 0x0253F2;
extern uint32 &ClumpOffset;

#define RpClumpGetAnimBlendClumpData(clump) (*(CAnimBlendClumpData **)(((uint32)(clump) + ClumpOffset)))

#define RpGeometryGetMesh(_geometry, _index) (&((RpMesh*)(((char*)(_geometry)->mesh) + sizeof(RpMeshHeader) + ((_geometry)->mesh->firstMeshOffset)))[_index])

constexpr float TWO_PI = 6.28318530718f;
constexpr float PI = 3.14159265358979323846f;
constexpr float HALF_PI = PI / 2.0f;
constexpr float LOG10_2 = 0.30102999566398119802f; // log10(2)
constexpr float SQRT_2 = 1.41421356237309504880f;
constexpr float SIN_PI = 0.0f; // std::sin(PI);
constexpr float COS_PI = -1.0f; // std::cos(PI);

void InjectCommonHooks();

// returns player coors
CVector FindPlayerCoors(int32 playerId = -1);
// returns player speed
CVector& FindPlayerSpeed(int32 playerId = -1);
// returns player ped or player vehicle if he's driving
CEntity * FindPlayerEntity(int32 playerId = -1);
// returns player train
CTrain* FindPlayerTrain(int32 playerId = -1);
// gets player coords
CVector const& FindPlayerCentreOfWorld(int32 playerId = -1);
// gets player coords with skipping sniper shift
CVector const& FindPlayerCentreOfWorld_NoSniperShift(int32 playerId = -1);
// returns player coords with skipping interior shift
CVector FindPlayerCentreOfWorld_NoInteriorShift(int32 playerId = -1);
// returns player angle in radians
float FindPlayerHeading(int32 playerId = -1);
// returns Z coord for active player
float FindPlayerHeight();
// returns player ped
CPlayerPed * FindPlayerPed(int32 playerId = -1);
CVehicle* FindPlayerVehicle(int32 playerId = -1, bool bIncludeRemote = false);
// returns player wanted
CWanted * FindPlayerWanted(int32 playerId = -1);

CVector Multiply3x3(CMatrix& m, CVector& v);
CVector Multiply3x3(CVector& v, CMatrix& m);

void TransformPoint(RwV3d& point, CSimpleTransform const& placement, RwV3d const& vecPos);
void TransformVectors(RwV3d* vecsOut, int32 numVectors, CMatrix const& matrix, RwV3d const* vecsin);
void TransformVectors(RwV3d* vecsOut, int32 numVectors, CSimpleTransform const& transform, RwV3d const* vecsin);

// Converts degrees to radians
// keywords: 0.017453292 flt_8595EC
constexpr float DegreesToRadians(float angleInDegrees) {
    return angleInDegrees * PI / 180.0F;
}

constexpr float RadiansToDegrees(float angleInRadians) {
    return angleInRadians * 180.0F / PI;
}

template <typename T>
T clamp(T value, T low, T high)
{
    return std::min(std::max(value, low), high);
}

inline const float lerp(float fMin, float fMax, float fProgress) {
    return fMin * (1.0F - fProgress) + fMax * fProgress;
}

inline const float invLerp(float fMin, float fMax, float fVal) {
    return (fVal - fMin) / (fMax - fMin);
}

// 0x4EEA80 - And inlined helluvalot
inline bool approxEqual(float f1, float f2, float epsilon)
{
    return fabs(f1 - f2) < epsilon;
}

// Used in some audio functions, mostly CAESmoothFadeThread
inline bool approxEqual2(float f1, float f2, float epsilon = 0.01F)
{
    return f1 == f2 || fabs(f1 - f2) < epsilon;
}

extern constexpr bool make_fourcc3(const char* line, const char abc[3]) {
    return line[0] == abc[0] &&
           line[1] == abc[1] &&
           line[2] == abc[2];
}

extern constexpr bool make_fourcc4(const char* line, const char abcd[4]) {
    return line[0] == abcd[0] &&
           line[1] == abcd[1] &&
           line[2] == abcd[2] &&
           line[3] == abcd[3];
}

extern constexpr uint32 make_fourcc4(const char fourcc[4]) {
    return fourcc[0] << 0 |
           fourcc[1] << 8 |
           fourcc[2] << 16 |
           fourcc[3] << 24;
}

AnimBlendFrameData *RpAnimBlendClumpFindFrame(RpClump *clump, char *name);

char *MakeUpperCase(char *dest, const char *src);
bool EndsWith(const char* str, const char* with, bool caseSensitive = true);

class CEventGroup* GetEventGlobalGroup();
// dummy function
void CreateDebugFont();
// dummy function
void DestroyDebugFont();
// dummy function
void ObrsPrintfString(char const* arg0, int16 arg1, int16 arg2);
// dummy function
void FlushObrsPrintfs();
void DefinedState();
void DefinedState2d();

void GetNameAndDamage(const char* nodeName, char* outName, bool& outDamage);
RpAtomic* GetFirstAtomicCallback(RpAtomic* atomic, void* data);
RpAtomic* GetFirstAtomic(RpClump* clump);
RpAtomic* Get2DEffectAtomicCallback(RpAtomic* atomic, void* data);
RpAtomic* Get2DEffectAtomic(RpClump* clump);
RwObject* GetFirstObjectCallback(RwObject* object, void* data);
RwObject* GetFirstObject(RwFrame* frame);
RwFrame* GetFirstFrameCallback(RwFrame* frame, void* data);
RwFrame* GetFirstChild(RwFrame* frame);
RpAtomic* SkinAtomicGetHAnimHierarchCB(RpAtomic* atomic, void* data);
RpHAnimHierarchy* GetAnimHierarchyFromSkinClump(RpClump* clump);
RpHAnimHierarchy* GetAnimHierarchyFromFrame(RwFrame* frame);
RpHAnimHierarchy* GetAnimHierarchyFromClump(RpClump* clump);
RpAtomic* AtomicRemoveAnimFromSkinCB(RpAtomic* atomic, void* data);
bool RpAtomicConvertGeometryToTL(RpAtomic* atomic);
bool RpAtomicConvertGeometryToTS(RpAtomic* atomic);
RpAtomic* atomicConvertGeometryToTL(RpAtomic* atomic, void* data);
bool RpClumpConvertGeometryToTL(RpClump* clump);
RpAtomic* atomicConvertGeometryToTS(RpAtomic* atomic, void* data);
bool RpClumpConvertGeometryToTS(RpClump* clump);
RpMaterial* forceLinearFilteringMatTexturesCB(RpMaterial* material, void* data);
bool SetFilterModeOnAtomicsTextures(RpAtomic* atomic, RwTextureFilterMode filtering);
RpAtomic* forceLinearFilteringAtomicsCB(RpAtomic* atomic, void* data);
bool SetFilterModeOnClumpsTextures(RpClump* clump, RwTextureFilterMode filtering);
bool RpGeometryReplaceOldMaterialWithNewMaterial(RpGeometry* geometry, RpMaterial* oldMaterial, RpMaterial* newMaterial);
RwTexture* RwTexDictionaryFindHashNamedTexture(RwTexDictionary* txd, uint32 hash);
RpClump* RpClumpGetBoundingSphere(RpClump* clump, RwSphere* bound, bool arg2);
void SkinGetBonePositions(RpClump* clump);
void SkinSetBonePositions(RpClump* clump);
void SkinGetBonePositionsToTable(RpClump* clump, RwV3d* table);
void SetLightsWithTimeOfDayColour(RpWorld* world);
// dummy function
void LightsEnable(int32 arg0);
void LightsDestroy(RpWorld* world);
// lighting = [0.0f;1.0f]
void WorldReplaceNormalLightsWithScorched(RpWorld* world, float lighting);
void WorldReplaceScorchedLightsWithNormal(RpWorld* world);
void AddAnExtraDirectionalLight(RpWorld* world, float x, float y, float z, float red, float green, float blue);
void RemoveExtraDirectionalLights(RpWorld* world);
// lighting = [0.0f;1.0f]
void SetAmbientAndDirectionalColours(float lighting);
// lighting = [0.0f;1.0f]
void SetFlashyColours(float lighting);
// lighting = [0.0f;1.0f]
void SetFlashyColours_Mild(float lighting);
// lighting = [0.0f;1.0f], unused
void SetBrightMarkerColours(float lighting);
void ReSetAmbientAndDirectionalColours();
void DeActivateDirectional();
void ActivateDirectional();
void SetAmbientColoursToIndicateRoadGroup(int32 arg0);
void SetFullAmbient();
void SetAmbientColours();
void SetAmbientColours(RwRGBAReal* color);
void SetDirectionalColours(RwRGBAReal* color);
// lighting = [0.0f;1.0f]
void SetLightColoursForPedsCarsAndObjects(float lighting);
void SetLightsForInfraredVisionHeatObjects();
void StoreAndSetLightsForInfraredVisionHeatObjects();
void RestoreLightsForInfraredVisionHeatObjects();
void SetLightsForInfraredVisionDefaultObjects();
void SetLightsForNightVision();
float GetDayNightBalance();

RpAtomic* RemoveRefsCB(RpAtomic* atomic, void* _IGNORED_ data);
void RemoveRefsForAtomic(RpClump* clump);

bool IsGlassModel(CEntity* pEntity);

CAnimBlendClumpData* RpAnimBlendAllocateData(RpClump* clump);
CAnimBlendAssociation* RpAnimBlendClumpAddAssociation(RpClump* clump, CAnimBlendAssociation* association, uint32 flags, float startTime, float blendAmount);
CAnimBlendAssociation* RpAnimBlendClumpExtractAssociations(RpClump* clump);
void RpAnimBlendClumpFillFrameArray(RpClump* clump, AnimBlendFrameData** frameData);
AnimBlendFrameData* RpAnimBlendClumpFindBone(RpClump* clump, uint32 id);
AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, char const* name);
AnimBlendFrameData* RpAnimBlendClumpFindFrameFromHashKey(RpClump* clump, uint32 key);
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, bool arg1, CAnimBlendHierarchy* hierarchy);
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, char const* name);
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, uint32 animId);
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump);
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump, uint32 flags);
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation(RpClump* clump, CAnimBlendAssociation** pAssociation, float* blendAmount);
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation_N(RpClump* clump, int32 n);
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation(RpClump* clump);
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation_N(RpClump* clump, int32 n);
uint32 RpAnimBlendClumpGetNumAssociations(RpClump* clump);
uint32 RpAnimBlendClumpGetNumNonPartialAssociations(RpClump* clump);
uint32 RpAnimBlendClumpGetNumPartialAssociations(RpClump* clump);
void RpAnimBlendClumpGiveAssociations(RpClump* clump, CAnimBlendAssociation* association);
void RpAnimBlendClumpInit(RpClump* clump);
bool RpAnimBlendClumpIsInitialized(RpClump* clump);
void RpAnimBlendClumpPauseAllAnimations(RpClump* clump);
void RpAnimBlendClumpRemoveAllAssociations(RpClump* clump);
void RpAnimBlendClumpRemoveAssociations(RpClump* clump, uint32 flags);
void RpAnimBlendClumpSetBlendDeltas(RpClump* clump, uint32 flags, float delta);
void RpAnimBlendClumpUnPauseAllAnimations(RpClump* clump);
void RpAnimBlendClumpUpdateAnimations(RpClump* clump, float step, bool onScreen);
RtAnimAnimation* RpAnimBlendCreateAnimationForHierarchy(RpHAnimHierarchy* hierarchy);
char* RpAnimBlendFrameGetName(RwFrame* frame);
void RpAnimBlendFrameSetName(RwFrame* frame, char* name);
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association);
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association, uint32 flags);
void RpAnimBlendKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, float time, void* customData);
bool RpAnimBlendPluginAttach();

/**
 * Writes given raster to PNG file using RtPNGImageWrite
 */
void Render2dStuff();
void WriteRaster(RwRaster* raster, char const* path);
bool CalcScreenCoors(CVector const& vecPoint, CVector* pVecOutPos, float* pScreenX, float* pScreenY);
bool CalcScreenCoors(CVector const& vecPoint, CVector* pVecOutPos);
bool DoesInfiniteLineTouchScreen(float fX, float fY, float fXDir, float fYDir);
bool IsPointInsideLine(float fLineX, float fLineY, float fXDir, float fYDir, float fPointX, float fPointY, float fTolerance);

void LittleTest();

/* Convert UTF-8 string to Windows Unicode. Free pointer using delete[] */
std::wstring UTF8ToUnicode(const std::string& str);
/* Convert Windows Unicode to UTF-8. Free pointer using delete[] */
std::string UnicodeToUTF8(const std::wstring& str);

extern int32 WindowsCharset;

extern uint16& uiTempBufferIndicesStored;
extern uint16& uiTempBufferVerticesStored;
constexpr int32 TOTAL_TEMP_BUFFER_INDICES = 4096;
extern RxVertexIndex (&aTempBufferIndices)[TOTAL_TEMP_BUFFER_INDICES]; // size 4096
constexpr int32 TOTAL_TEMP_BUFFER_VERTICES = 2048;
extern RxObjSpace3DVertex (&aTempBufferVertices)[TOTAL_TEMP_BUFFER_VERTICES];
constexpr int32 TOTAL_RADIOSITY_VERTEX_BUFFER = 1532;
extern RwD3D9Vertex (&aRadiosityVertexBuffer)[TOTAL_RADIOSITY_VERTEX_BUFFER];
