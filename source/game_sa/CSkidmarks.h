#pragma once

#include "eSurfaceType.h"
#include "CSkidmark.h"

class CVector;

constexpr auto SKIDMARKS_COUNT{ 32u };
class CSkidmarks {
public:
    static RxVertexIndex (&m_aIndices)[SKIDMARK_NUM_PARTS * 6];
    static RwTexture*& m_pTexture;
    static CSkidmark (&m_aSkidmarks)[SKIDMARKS_COUNT];

public:
    static void InjectHooks();

    static void Clear();
    static void Init();
    static void RegisterOne(uint32_t index, const CVector& posn, float dirX, float dirY, const bool* surfaceType, bool& bloodState, float length);
    static CSkidmark* FindById(uint32_t id);
    static CSkidmark* GetNextFree(bool forceFree);
    static void RegisterOne(uint32_t index, const CVector& posn, float dirX, float dirY, eSkidMarkType type, bool& bloodState, float length);
    static void Render();
    static void Shutdown();
    static void Update();
};
