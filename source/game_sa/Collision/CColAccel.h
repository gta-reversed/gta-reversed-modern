#pragma once

#include "IplDef.h"

struct CColAccelColBound
{
    CRect m_Area;
    int16_t m_wModelStart;
    int16_t m_wModelEnd;
    bool m_bProcedural;
    bool m_bInterior;
};
VALIDATE_SIZE(CColAccelColBound, 0x18);

struct CColAccelColEntry
{
    CBoundingBox m_boundBox;
    CSphere m_boundSphere;
    int16_t m_wModelStart;
    int16_t m_wModelEnd;
    uint8_t m_nColSlot;
    bool m_bUnkn;
};
VALIDATE_SIZE(CColAccelColEntry, 0x30);

struct CColAccelIPLEntry
{
    int32_t m_nLodIndex;
    int32_t m_nEntityIndex;
    int32_t m_nModelId;
    int32_t m_nLodModelId;
    union {
        uint32_t m_nFlags;
        struct {
            uint32_t m_bIsUnderwater  : 1;
            uint32_t m_bHasColModel   : 1;
            uint32_t m_bIsFarDrawDist : 1;
            uint32_t m_bOwnsColModel  : 1;
        };
    };
};
VALIDATE_SIZE(CColAccelIPLEntry, 0x14);

enum eColAccelState : int32_t {
    COLACCEL_ENDED = 0,
    COLACCEL_STARTED = 1,
    COLACCEL_LOADING = 2,
};

struct PackedModelStartEnd {
    int16_t wModelStart;
    int16_t wModelEnd;
};
VALIDATE_SIZE(PackedModelStartEnd, 0x4);

class CColAccel {
public:
    static CColAccelColBound*& m_colBounds;
    static IplDef*& m_iplDefs;
    static int32_t*& m_iSectionSize;
    static int32_t& m_iCachingColSize;
    static eColAccelState& m_iCacheState;
    static CColAccelColEntry*& mp_caccColItems;
    static int32_t& m_iNumColItems;
    static CColAccelIPLEntry*& mp_caccIPLItems;
    static int32_t& m_iNumIPLItems;
    static int32_t& m_iNumSections;
    static int32_t& m_iNumColBounds;
    static char const* mp_cCacheName; // MODELS\CINFO.BIN

public:
    static void InjectHooks();

    static bool isCacheLoading();
    static void endCache();
    static void addCacheCol(PackedModelStartEnd startEnd, CColModel const& colModel);
    static void cacheLoadCol();
    static void addColDef(ColDef colDef);
    static void getColDef(ColDef& colDef);
    static void setIplDef(int iplIndex, IplDef iplDef);
    static IplDef getIplDef(int iplIndex);
    static void cacheIPLSection(CEntity** ppEntities, int entitiesCount);
    static void addIPLEntity(CEntity** ppEntities, int entitiesCount, int entityIndex);
    static void startCache();
};
