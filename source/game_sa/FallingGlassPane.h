#pragma once

class CMatrix;

class CFallingGlassPane {
public:
    CMatrix m_Matrix;
    CVector m_Velocity;
    CVector m_RandomNumbers;
    uint32  m_nCreatedTime;
    float   m_fGroundZ;
    float   m_fSize;
    uint8   m_nPieceIndex;
    bool    m_bExist;
    bool    m_bRenderShatter;
    bool    m_f6F;

public:
    static void InjectHooks();

    CFallingGlassPane() = default;  // 0x71A8B0
    ~CFallingGlassPane() = default; // 0x71A8C0

    void Update();
    void Render();

private: // NOTSA
    RwRGBA CalculateHiLightPolyColor();
    RwRGBA CalculateShatterPolyColor();
};

VALIDATE_SIZE(CFallingGlassPane, 0x70);
