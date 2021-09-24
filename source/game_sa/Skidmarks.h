#pragma once

#include "eSurfaceType.h"
#include "CVector.h"

#define SKIDMARKS_COUNT 32

struct CSkidmark {
    CVector m_vPosn[16];    // 00000000
    int32   dwordC0;        // 000000C0
    bool    fC4[60];        // 000000C4
    int32   dword100;       // 00000100
    bool    f104[60];       // 00000104
    int32   dword140;       // 00000140
    int32   dword144;       // 00000144
    int32   time1;          // 00000148
    int32   time2;          // 0000014C
    int32   m_nSurfaceType; // 00000150
    int16   m_nNumParts;    // 00000154
    bool    m_nState;       // 00000156
    bool    byte157;        // 00000157
};

VALIDATE_SIZE(CSkidmark, 0x158);

class CSkidmarks {
public:
    static uint16 (&m_aIndices)[96];
    static RwTexture*& m_pTexture;
    static CSkidmark (&m_aSkidmarks)[SKIDMARKS_COUNT];

public:
    static void InjectHooks();

    static void Clear();
    static void Init();
    static void RegisterOne(uint32 index, const CVector& posn, float dirX, float dirY, const bool* surfaceType, bool* bloodState, float length);
    static void RegisterOne(uint32 index, const CVector& posn, float dirX, float dirY, eSurfaceType surfaceType, bool* bloodState, float length);
    static void Render();
    static void Shutdown();
    static void Update();
};
