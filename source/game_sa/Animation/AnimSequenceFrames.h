#pragma once

#include "CQuaternion.h"

class CAnimSequenceRootFrameCompressed {
public:
    int16 m_wQuatX;
    int16 m_wQuatY;
    int16 m_wQuatZ;
    int16 m_wQuatW;
    int16 m_wTime;
    int16 m_wTranslationX;
    int16 m_wTranslationY;
    int16 m_wTranslationZ;
};
VALIDATE_SIZE(CAnimSequenceRootFrameCompressed, 0x10);

class CAnimSequenceChildFrameCompressed {
public:
    int16 m_wQuatX;
    int16 m_wQuatY;
    int16 m_wQuatZ;
    int16 m_wQuatW;
    int16 m_wTime;
};
VALIDATE_SIZE(CAnimSequenceChildFrameCompressed, 0xA);

class CAnimSequenceRootFrameUncompressed {
public:
    CQuaternion m_quat;
    float       m_fTime;
    CVector     m_vecTranslation;
};
VALIDATE_SIZE(CAnimSequenceRootFrameUncompressed, 0x20);

class CAnimSequenceChildFrameUncompressed {
public:
    CQuaternion m_quat;
    float       m_fTime;
};
VALIDATE_SIZE(CAnimSequenceChildFrameUncompressed, 0x14);
