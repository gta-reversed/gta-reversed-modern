/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "RenderWare.h"
#include "Vector.h"
#include "RealTimeShadow.h"
#include "PolyBunch.h"
#include "PtrList.h"

/*
 Shadow rectangle:
         Front
 +---------+---------+
 |         |         |
 |         |         |
 |         | Posn    |
 +---------+---------+ Side
 |         |         |
 |         |         |
 |         |         |
 +---------+---------+

 Posn - world coordinates (x,y,z)
 Front - local coordinates (x,y) relatively to center
 Side - local coordinates (x,y) relatively to center
*/

enum eShadowType {
    SHADOW_DEFAULT = 1,
    SHADOW_ADDITIVE = 2,
    SHADOW_INVCOLOR = 3,
    SHADOW_OIL_1 = 4,
    SHADOW_OIL_2 = 5,
    SHADOW_OIL_3 = 6,
    SHADOW_OIL_4 = 7,
    SHADOW_OIL_5 = 8
};

enum eShadowTextureType {
    SHADOWTEX_CAR = 1,
    SHADOWTEX_PED = 2,
    SHADOWTEX_EXPLOSION = 3,
    SHADOWTEX_HELI = 4,
    SHADOWTEX_HEADLIGHTS = 5,
    SHADOWTEX_BLOOD = 6
};

enum VEH_SHD_TYPE {
    VEH_SHD_CAR = 0,
    VEH_SHD_BIKE = 1,
    VEH_SHD_HELI = 2,
    VEH_SHD_PLANE = 3,
    VEH_SHD_RC = 4,
    VEH_SHD_BIG_PLANE = 5 // AT400; ANDROM
};

class CRegisteredShadow {
public:
    CVector          m_vecPosn;
    float            m_fFrontX;
    float            m_fFrontY;
    float            m_fSideX;
    float            m_fSideY;
    float            m_fZDistance;
    float            m_fScale;
    RwTexture*       m_pTexture;
    CRealTimeShadow* m_pRTShadow;
    uint16           m_nIntensity;
    uint8            m_nType;
    uint8            m_nRed;
    uint8            m_nGreen;
    uint8            m_nBlue;
    struct {
        uint8 bDrawOnWater : 1;
        uint8 bIgnoreMapObjects : 1;
        uint8 bDrawOnBuildings : 1;
    } m_nFlags;
};

VALIDATE_SIZE(CRegisteredShadow, 0x34);

class CPermanentShadow {
public:
    CVector m_vecPosn;
    float m_fFrontX;
    float m_fFrontY;
    float m_fSideX;
    float m_fSideY;
    float m_fZDistance;
    float m_fScale;
    uint32 m_nTimeCreated;
    uint32 m_nTimeDuration;
    RwTexture *m_pTexture;
    uint16 m_nIntensity;
    uint8 m_nType;
    uint8 m_nRed;
    uint8 m_nGreen;
    uint8 m_nBlue;
    struct {
        uint8 bDrawOnWater : 1;
        uint8 bIgnoreMapObjects : 1;
        uint8 bDrawOnBuildings : 1;
    } m_nFlags;
};

VALIDATE_SIZE(CPermanentShadow, 0x38);

class CStaticShadow {
public:
    uint32 m_nId;
    CPolyBunch *m_pPolyBunch;
    uint32 m_nTimeCreated;
    CVector m_vecPosn;
    float m_fFrontX;
    float m_fFrontY;
    float m_fSideX;
    float m_fSideY;
    float m_fZDistance;
    float m_fScale;
    RwTexture *m_pTexture;
    uint16 m_nIntensity;
    uint8 m_nType;
    uint8 m_nRed;
    uint8 m_nGreen;
    uint8 m_nBlue;
    char m_bJustCreated;
    char m_bRendered;
    char m_bTemporaryShadow; // delete after 5000ms
    union {
        struct {
            uint8 m_nDayIntensity : 4;
            uint8 m_nNightIntensity : 4;
        };
        uint8 m_nDayNightIntensity;
    };
private:
    int16 _pad0;
public:

    void Free();
};

VALIDATE_SIZE(CStaticShadow, 0x40);

struct _ProjectionParam {
    RwV3d at; /* Camera at vector */
    RwMatrix invMatrix; /* Transforms to shadow camera space */
    RwUInt8 shadowValue; /* Shadow opacity value */
    RwBool fade; /* Shadow fades with distance */
    RwUInt32 numIm3DBatch; /* Number of buffer flushes */ // unused
    RwMatrix entityMatrix;
};

VALIDATE_SIZE(_ProjectionParam, 0x98);

class CEntity;
class CPhysical;
class CVehicle;

extern uint32 MAX_STORED_SHADOWS; // default: 48
extern uint32 MAX_PERMANENT_SHADOWS; // default: 48
extern uint32 MAX_STATIC_SHADOWS; // default: 48
extern uint32 MAX_SHADOW_POLY_BUNCHES; // default: 360

class CShadows {
public:
    static void Init();
    static void Shutdown();
    static void AddPermanentShadow(uint8 type, RwTexture* texture, CVector* posn, float topX, float topY, float rightX, float rightY, int16 intensity, uint8 red, uint8 greeb, uint8 blue, float drawDistance, uint32 time, float upDistance);
    static void StoreShadowToBeRendered(uint8 type, RwTexture* texture, CVector* posn, float topX, float topY, float rightX, float rightY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, bool drawOnWater, float scale, CRealTimeShadow* realTimeShadow, bool drawOnBuildings);
    static void SetRenderModeForShadowType(uint8 shadowType);
    static void RemoveOilInArea(float x1, float y1, float x2, float y2);
    static void GunShotSetsOilOnFire(CVector const*shotOrigin, CVector const*shotTarget);
    static void PrintDebugPoly(CVector* a, CVector* b, CVector* c); // dummy function
    static void CalcPedShadowValues(CVector sunPosn, float* displacementX, float* displacementY, float* frontX, float* frontY, float* sideX, float* sideY);
    static void TidyUpShadows();
    static void AffectColourWithLighting(uint8 shadowType, uint8 dayNightIntensity, uint8 red, uint8 green, uint8 blue, uint8* outRed, uint8* outGreen, uint8* outBlue);
    static void StoreShadowToBeRendered(uint8 shadowTextureType, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue);
    static void StoreShadowForPedObject(CEntity* ped, float displacementX, float displacementY, float frontX, float frontY, float sideX, float sideY);
    static void StoreRealTimeShadow(CPhysical* physical, float displacementX, float displacementY, float frontX, float frontY, float sideX, float sideY);
    static void UpdateStaticShadows();
    static void RenderExtraPlayerShadows();
    static void RenderStaticShadows();
    static void CastShadowEntityXY(CEntity* entity, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, uint8* pDayNightIntensity, int32 shadowType);
    static void CastShadowEntityXYZ(CEntity* entity, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, CRealTimeShadow* realTimeShadow);
    static void CastPlayerShadowSectorList(CPtrList& ptrList, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, uint8* pDayNightIntensity, int32 shadowType);
    static void CastShadowSectorList(CPtrList& ptrList, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, uint8* pDayNightIntensity, int32 shadowType);
    static void CastRealTimeShadowSectorList(CPtrList& ptrList, float conrerAX, float cornerAY, float cornerBX, float cornerBY, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, CPolyBunch** ppPolyBunch, CRealTimeShadow* realTimeShadow, uint8* pDayNightIntensity);
    static void RenderStoredShadows();
    static void GeneratePolysForStaticShadow(int16 staticShadowIndex);
    static bool StoreStaticShadow(uint32 id, uint8 type, RwTexture* texture, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistane, float scale, float drawDistance, bool temporaryShadow, float upDistance);
    static void StoreShadowForVehicle(CVehicle* vehicle, VEH_SHD_TYPE vehShadowType);
    static void StoreCarLightShadow(CVehicle* vehicle, int32 id, RwTexture* texture, CVector* posn, float frontX, float frontY, float sideX, float sideY, uint8 red, uint8 green, uint8 blue, float maxViewAngle);
    static void StoreShadowForPole(CEntity* entity, float offsetX, float offsetY, float offsetZ, float poleHeight, float poleWidth, uint32 localId);
    static void UpdatePermanentShadows();
    static void RenderIndicatorShadow(uint32 id, uint8 shadowType, RwTexture* texture, CVector* posn, float frontX, float frontY, float sideX, float sideY, int16 intensity);

    static CPolyBunch *&pEmptyBunchList;
    static uint16 &ShadowsStoredToBeRendered;
    static CRegisteredShadow *asShadowsStored; // static CRegisteredShadow asShadowsStored[default: 48]
    static CPolyBunch *aPolyBunches; // static CPolyBunch aPolyBunches[default: 360]
    static CStaticShadow *aStaticShadows; // static CStaticShadow aStaticShadows[default: 48]
    static CPermanentShadow *aPermanentShadows; // static CPermanentShadow aPermanentShadows[default: 48]
};

#ifdef _MSC_VER
RwV3d *ShadowRenderTriangleCB(RwV3d *pNormal, RwV3d *pTrianglePos, _ProjectionParam *param);
#endif

extern float &MAX_DISTANCE_PED_SHADOWS; // const 15.0f
extern float &MAX_DISTANCE_PED_SHADOWS_SQR;
extern RwTexture *&gpShadowCarTex;
extern RwTexture *&gpShadowPedTex;
extern RwTexture *&gpShadowHeliTex;
extern RwTexture *&gpShadowBikeTex;
extern RwTexture *&gpShadowBaronTex;
extern RwTexture *&gpShadowExplosionTex;
extern RwTexture *&gpShadowHeadLightsTex;
extern RwTexture *&gpShadowHeadLightsTex2;
extern RwTexture *&gpBloodPoolTex;
extern RwTexture *&gpHandManTex;
extern RwTexture *&gpCrackedGlassTex;
extern RwTexture *&gpPostShadowTex;