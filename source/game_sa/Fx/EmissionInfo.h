#pragma once

#include "Vector.h"

struct EmissionInfo_t {
    float   m_fRate;
    float   m_fRadius;

    CVector m_Min;
    CVector m_Max;

    float   m_fSpeed;
    float   m_fSpeedBias;
    CVector m_0x28;

    float   m_fAngleMin;
    float   m_fAngleMax;

    float   m_fLife;
    float   m_fLifeBias;
    CVector m_0x44;

    float   m_fRotationMinAngle;
    float   m_fRotationMaxAngle;

    float   m_fMinWind;
    float   m_fMaxWind;

    float   m_fMinRain;
    float   m_fMaxRain;
    
    void Process(float mult) {
        m_fRate   = mult * 10.0f;
        m_fLife   = 1.0f;
        m_fRadius = 0.0f;
        
        m_fSpeed     = 0.0f;
        m_fSpeedBias = 0.0f;

        m_fAngleMin = 0.0f;
        m_fAngleMax = 0.0f;

        m_fLifeBias = 0.0f;

        m_fRotationMinAngle = 0.0f;
        m_fRotationMaxAngle = 0.0f;

        m_fMinWind = 0.0f;
        m_fMaxWind = 2.0f;

        m_fMinRain = 0.0f;
        m_fMaxRain = 2.0f;

        m_Min.Set(0.0f, 0.0f, 0.0f);
        m_Max.Set(0.0f, 0.0f, 0.0f);
        m_0x28.Set(0.0f, 0.0f, 1.0f);
        m_0x44.Set(0.0f, 0.0f, 0.0f);
    }
};
