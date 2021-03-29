#pragma once

#include "CRect.h"
#include "CVector.h"
#include "CPool.h"

// thanks to jte for reversing this
struct ColDef
{
    CRect m_Area;
    uint32_t field_10;
    uint32_t field_14;
    uint32_t field_18;
    uint32_t field_1C;
    uint16_t field_20;
    int16_t m_nModelIdStart;
    int16_t m_nModelIdEnd;
    uint16_t m_nRefCount;
    bool m_bActive;
    bool m_bCollisionIsRequired;
    bool m_bProcedural;
    bool m_bInterior;

    static void* operator new(unsigned int size);
    static void operator delete(void* data);
};
VALIDATE_SIZE(ColDef, 0x2C);

class CColStore
{
public:
    static CPool<ColDef>*& ms_pColPool;
    static class CQuadTreeNode*& ms_pQuadTree;

    static CVector& ms_vecCollisionNeeded;
    static bool& ms_bCollisionNeeded;
    static int32_t ms_nRequiredCollisionArea;

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static std::int32_t AddColSlot(const char* name);
    static void AddCollisionNeededAtPosn(const CVector& pos);
    static void AddRef(int colNum);
    static std::int32_t FindColSlot();
    static void BoundingBoxesPostProcess();
    static void EnsureCollisionIsInMemory(CVector const& pos);
    static CRect* GetBoundingBox(int colSlot);
    static void IncludeModelIndex(int colSlot, int modelId);
    static bool HasCollisionLoaded(CVector const& pos, int areaCode);
    static void LoadAllBoundingBoxes();
    static void LoadAllCollision();
    static void LoadCol(int colSlot, char const* filename);
    static bool LoadCol(int colSlot, unsigned char* data, int dataSize);
    static void LoadCollision(CVector pos, bool bIgnorePlayerVeh);
    static void RemoveAllCollision();
    static void RemoveCol(int colSlot);
    static void RemoveColSlot(int colSlot);
    static void RemoveRef(int colNum);
    static void RequestCollision(CVector const& pos, int areaCode);
    static void SetCollisionRequired(const CVector& pos, int areaCode);

};

void SetIfCollisionIsRequired(CVector2D const& vecPos, void* data); // data is ColDef*
void SetIfCollisionIsRequiredReducedBB(CVector2D const& vecPos, void* data); // data is ColDef*
