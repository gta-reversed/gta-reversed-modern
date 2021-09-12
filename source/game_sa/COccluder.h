#pragma once

#include "CVector2D.h"
#include "CVector.h"
#include "CActiveOccluder.h"

struct COccluder {
    int16 m_wMidX;
    int16 m_wMidY;
    int16 m_wMidZ;
    int16 m_wLength;
    int16 m_wWidth;
    int16 m_wHeight;
    uint8 m_cRotZ;
    uint8 m_cRotY;
    uint8 m_cRotX;
    char  _pad;
    struct {
        int16 m_nNextIndex : 15;
        int16 m_bFarAway : 1;
    };

public:
    static void InjectHooks();

    bool ProcessOneOccluder(CActiveOccluder* activeOccluder);
    bool ProcessLineSegment(int32 iInd1, int32 iInd2, CActiveOccluder* activeOccluder);
    bool NearCamera() const;
};
VALIDATE_SIZE(COccluder, 0x12);