/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVector.h"

constexpr auto MAX_SHINYTEXTS{ 32u };

class CRegisteredShinyText {
public:
    CVector m_vecCornerAA;
    CVector m_vecCornerAB;
    CVector m_vecCornerBA;
    CVector m_vecCornerBB;
    RwTexCoords m_texCoorsAA;
    RwTexCoords m_texCoorsAB;
    RwTexCoords m_texCoorsBA;
    RwTexCoords m_texCoorsBB;
    float m_fDistanceToCamera;
    bool m_bAlwaysTrue;
    uint8 m_colorR;
    uint8 m_colorG;
    uint8 m_colorB;
};

VALIDATE_SIZE(CRegisteredShinyText, 0x58);

class CShinyTexts {
public:
    static uint32_t& NumShinyTexts;
    static CRegisteredShinyText(&aShinyTexts)[MAX_SHINYTEXTS];

public:
    static void InjectHooks();

    static void Init();
    static void RenderOutGeometryBuffer();
    static void Render();
    static void RegisterOne(CVector cornerAA, CVector cornerBA, CVector cornerBB, CVector cornerAB, float u1, float v1, float u2, float v2, float u3, float v3, float u4,
        float v4, bool alwaysTrue, unsigned char red, unsigned char green, unsigned char blue, float maxDistance);
};
