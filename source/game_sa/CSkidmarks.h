#pragma once

#include "eSurfaceType.h"
#include "CVector.h"

constexpr auto SKIDMARKS_COUNT{ 32u };

struct CSkidmark {
    CVector m_vPosn[16]{}; // 00000000
    int dwordC0{};         // 000000C0
    bool fC4[60]{};        // 000000C4
    int dword100{};        // 00000100
    bool f104[60]{};       // 00000104
    int dword140{};        // 00000140
    int dword144{};        // 00000144
    int time1{};           // 00000148
    int time2{};           // 0000014C
    int m_nSurfaceType{};  // 00000150
    short m_nNumParts{};   // 00000154
    bool m_nState{};       // 00000156
    bool byte157{};        // 00000157
};

VALIDATE_SIZE(CSkidmark, 0x158);

class CSkidmarks {
public:
    static unsigned short (&m_aIndices)[96];
    static RwTexture*& m_pTexture;
    static CSkidmark (&m_aSkidmarks)[SKIDMARKS_COUNT];

public:
    static void InjectHooks();

    static void Clear();
    static void Init();
    static void RegisterOne(unsigned int index, const CVector& posn, float dirX, float dirY, const bool* surfaceType, bool* bloodState, float length);
    static void RegisterOne(unsigned int index, const CVector& posn, float dirX, float dirY, eSurfaceType surfaceType, bool* bloodState, float length);
    static void Render();
    static void Shutdown();
    static void Update();
};
