#pragma once

#include "ListItem_c.h"
#include "Vector.h"

struct RwRGBA;
class FxSystem_c;

class FxEmitterPrt_c : public ListItem_c { // ListItem_c > Particle_c
public:
    float       m_fTotalLife;
    float       m_fCurrentLife;
    CVector     m_Pos;
    CVector     m_Velocity;
    FxSystem_c* m_System;
    RwRGBA      m_MultColor;
    uint8       m_MultSize;
    uint8       m_MultRot;
    uint8       m_RandR;
    uint8       m_RandG;
    uint8       m_RandB;
    uint8       m_Brightness;
    int8        m_RotZ;
    bool        m_bLocalToSystem;
    float       m_CurrentRotation;

public:
    FxEmitterPrt_c() = default;  // 0x4A94E0
    ~FxEmitterPrt_c() = default; // 0x4A94F0

    static void* operator new[](size_t size);
};
VALIDATE_SIZE(FxEmitterPrt_c, 60);
