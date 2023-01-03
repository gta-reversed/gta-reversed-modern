#pragma once

#include "Base.h"
#include "Vector2D.h"
#include "Vector.h"

struct CActiveOccluderLine {
    CVector2D m_vecOrigin;
    CVector2D m_vecDirection;
    float     m_fLength;
};
VALIDATE_SIZE(CActiveOccluderLine, 0x14);

class CActiveOccluder {
public:
    CActiveOccluderLine m_aLines[6];
    uint16              m_wDepth;
    uint8               m_cLinesCount;
    uint8               m_cNumVectors;
    CVector             m_aVectors[3];
    float               m_afRadiuses[3];

public:
    static void InjectHooks();

    bool IsPointWithinOcclusionArea(float fX, float fY, float fRadius);
    bool IsPointBehindOccluder(CVector vecPos, float fRadius);
    auto GetLines() const { return std::span{ m_aLines, m_cLinesCount }; }
};
VALIDATE_SIZE(CActiveOccluder, 0xAC);
