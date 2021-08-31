#pragma once

#include "eSurfaceType.h"
#include "CVector.h"

constexpr auto SKIDMARKS_COUNT{ 32u };

struct CSkidmark
{
    CVector m_vPosn[16];
    float m_partDirY[16];
    float m_partDirX[16];
    uint32 m_id;
    uint32 m_timeUpdatedMs;
    int m_timeLow;
    int m_timeHigh;
    eSkidMarkType m_type;
    uint16 m_nNumParts;
    bool m_nState;
    uint8 m_bActive;

    CVector GetPartPosn(unsigned i) const { return m_vPosn[i]; }
    CVector GetLastPartPosn() const { return GetPartPosn(m_nNumParts); }
    CVector GetFirstPartPosn() const { return GetPartPosn(0); }
    CSphere GetBoundingSphere() {
        const CVector center = (GetLastPartPosn() + GetFirstPartPosn()) / 2.0f;
        const float radius = (GetLastPartPosn() - center).Magnitude();
        return { center, radius };
    }
    void Update(CVector posn, CVector2D dir, float length, bool& bloodState);
    void Init(uint32_t id, CVector posn, eSkidMarkType type, bool& bloodState);
};
VALIDATE_SIZE(CSkidmark, 0x158);

class CSkidmarks {
public:
    static RxVertexIndex (&m_aIndices)[96];
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
