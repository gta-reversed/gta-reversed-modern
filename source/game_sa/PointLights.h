/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CEntity;

enum ePointLightType : uint8 {
    PLTYPE_POINTLIGHT = 0,
    PLTYPE_SPOTLIGHT = 1,
    PLTYPE_DARKLIGHT = 2,
};

class CPointLight {
public:
    CVector         m_vecPosn;
    CVector         m_vecDirection;
    float           m_fRange;
    float           m_fColorRed;
    float           m_fColorGreen;
    float           m_fColorBlue;
    CEntity*        m_pEntityToLight;
    ePointLightType m_nType; // see ePointLightType
    uint8           m_nFogType;
    bool            m_bGenerateShadows;

private:
    char _pad0;
};

VALIDATE_SIZE(CPointLight, 0x30);

class CPointLights {
public:
    // static variables

    // num of registered lights in frame
    static uint32& NumLights;
    // lights array. Count: MAX_POINTLIGHTS (32)
    static CPointLight* aLights;

    static float*   aCachedMapReadResults; // static float aCachedMapReadResults[MAX_POINTLIGHTS];
    static uint32&  NextCachedValue;       // static int32 NextCachedValue;
    static CVector* aCachedMapReads;       // static CVector aCachedMapReads[MAX_POINTLIGHTS];

    // static functions

    static void  Init();
    static float GenerateLightsAffectingObject(const CVector* point, float* totalLighting, CEntity* entity);
    static float GetLightMultiplier(const CVector* point);
    static void  RemoveLightsAffectingObject();
    static bool  ProcessVerticalLineUsingCache(CVector point, float* outZ);
    static void  AddLight(uint8 lightType, CVector point, CVector direction, float radius, float red, float green, float blue, uint8 fogType, bool generateExtraShadows, CEntity* entityAffected);
    static void  RenderFogEffect();
};

extern uint32 MAX_POINTLIGHTS; // default: 32