#pragma once

#include "Skidmark.h"

constexpr auto SKIDMARKS_COUNT{ 32u };

class CSkidmarks {
public:
    static RxVertexIndex (&m_aIndices)[SKIDMARK_NUM_PARTS * 6];
    static RwTexture*&   m_pTexture;
    static CSkidmark     (&m_aSkidmarks)[SKIDMARKS_COUNT];

public:
    static void InjectHooks();

    static void Init();
    static void Shutdown();
    static void Clear();
    static void Update();
    static void Render();
    static void RegisterOne(uint32 index, const CVector& posn, float dirX, float dirY, eSkidmarkType type, bool* bloodState, float length);
    static void RegisterOne(uint32 index, const CVector& posn, float dirX, float dirY, bool* isSandy, bool* bloodState, float length);

    static CSkidmark* FindById(uint32 id);
    static CSkidmark* GetNextFree(bool forceFree);
};
