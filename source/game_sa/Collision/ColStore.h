#pragma once

#include "CRect.h"
#include "CVector.h"
#include "CPool.h"

// thanks to jte for reversing this
struct ColDef {
    CRect  m_Area;
    uint32 field_10;
    uint32 field_14;
    uint32 field_18;
    uint32 field_1C;
    uint16 field_20;
    int16  m_nModelIdStart;
    int16  m_nModelIdEnd;
    uint16 m_nRefCount;
    bool   m_bActive;
    bool   m_bCollisionIsRequired;
    bool   m_bProcedural;
    bool   m_bInterior;

    static void* operator new(uint32 size);
    static void  operator delete(void* data);
};
VALIDATE_SIZE(ColDef, 0x2C);

class CColStore
{
public:
    static CPool<ColDef>*& ms_pColPool;
    static class CQuadTreeNode*& ms_pQuadTree;

    static CVector& ms_vecCollisionNeeded;
    static bool& ms_bCollisionNeeded;
    static int32 ms_nRequiredCollisionArea;

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static int32 AddColSlot(const char* name);
    static void AddCollisionNeededAtPosn(const CVector& pos);
    static void AddRef(int32 colNum);
    static int32 FindColSlot();
    static void BoundingBoxesPostProcess();
    static void EnsureCollisionIsInMemory(CVector const& pos);
    static CRect* GetBoundingBox(int32 colSlot);
    static void IncludeModelIndex(int32 colSlot, int32 modelId);
    static bool HasCollisionLoaded(CVector const& pos, int32 areaCode);
    static void LoadAllBoundingBoxes();
    static void LoadAllCollision();
    static void LoadCol(int32 colSlot, char const* filename);
    static bool LoadCol(int32 colSlot, uint8* data, int32 dataSize);
    static void LoadCollision(CVector pos, bool bIgnorePlayerVeh);
    static void RemoveAllCollision();
    static void RemoveCol(int32 colSlot);
    static void RemoveColSlot(int32 colSlot);
    static void RemoveRef(int32 colNum);
    static void RequestCollision(CVector const& pos, int32 areaCode);
    static void SetCollisionRequired(const CVector& pos, int32 areaCode);
};

void SetIfCollisionIsRequired(CVector2D const& vecPos, void* data); // data is ColDef*
void SetIfCollisionIsRequiredReducedBB(CVector2D const& vecPos, void* data); // data is ColDef*
