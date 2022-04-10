#pragma once

#include "ListItem_c.h"
#include "Vector.h"

struct RwRGBA;
class FxSystem_c;

class FxEmitterPrt_c : public ListItem_c {
public:
    float       m_fTotalLife;
    float       m_fCurrentLife;
    CVector     m_WaterPos;
    CVector     m_f1C;
    FxSystem_c* m_System;
    RwRGBA      m_Color;
    uint8       m_nSize;
    uint8       field_31;
    uint8       field_32;
    uint8       field_33;
    uint8       field_34;
    uint8       field_35;
    int8        field_36;
    bool        m_bLocalParticles;
    float       m_fRotation;

public:
    FxEmitterPrt_c() = default;  // 0x4A94E0
    ~FxEmitterPrt_c() = default; // 0x4A94F0

    static void* operator new[](uint32 nSize);
};
VALIDATE_SIZE(FxEmitterPrt_c, 60);
