#pragma once

#include "PluginBase.h"
#include "CQuaternion.h"

class CAnimSequenceRootFrameCompressed
{
public:
    int16_t m_wQuatX;
    int16_t m_wQuatY;
    int16_t m_wQuatZ;
    int16_t m_wQuatW;
    int16_t m_wTime;
    int16_t m_wTranslationX;
    int16_t m_wTranslationY;
    int16_t m_wTranslationZ;
};
VALIDATE_SIZE(CAnimSequenceRootFrameCompressed, 0x10);

class CAnimSequenceChildFrameCompressed
{
public:
    int16_t m_wQuatX;
    int16_t m_wQuatY;
    int16_t m_wQuatZ;
    int16_t m_wQuatW;
    int16_t m_wTime;
};
VALIDATE_SIZE(CAnimSequenceChildFrameCompressed, 0xA);

class CAnimSequenceRootFrameUncompressed
{
public:
    CQuaternion m_quat;
    float m_fTime;
    CVector m_vecTranslation;
};
VALIDATE_SIZE(CAnimSequenceRootFrameUncompressed, 0x20);

class CAnimSequenceChildFrameUncompressed
{
public:
    CQuaternion m_quat;
    float m_fTime;
};
VALIDATE_SIZE(CAnimSequenceChildFrameUncompressed, 0x14);
