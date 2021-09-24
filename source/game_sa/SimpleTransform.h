/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "CVector.h"

class CSimpleTransform {
public:
    CSimpleTransform() : m_vPosn(), m_fHeading(0.0F) {}

public:
    CVector m_vPosn;
    float m_fHeading;

    void UpdateRwMatrix(RwMatrix* out);
    void Invert(CSimpleTransform const& base);
    void UpdateMatrix(class CMatrix* out);
};

VALIDATE_SIZE(CSimpleTransform, 0x10);
