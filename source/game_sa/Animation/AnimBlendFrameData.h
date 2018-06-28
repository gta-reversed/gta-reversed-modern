/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class  AnimBlendFrameData {
public:
    unsigned char  m_nFlags;
    CVector        m_vecOffset;
    class IFrame  *m_pIFrame;
    unsigned int   m_nNodeId;
};

VALIDATE_SIZE(AnimBlendFrameData, 0x18);
