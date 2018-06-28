/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "CQuaternion.h"

class  CFileObjectInstance {
public:
    CVector     m_vecPosition;
    CQuaternion m_qRotation;
    int         m_nModelId;
    union {
        struct { // CFileObjectInstanceType
            unsigned int m_nAreaCode : 8;
            unsigned int m_bRedundantStream : 1;
            unsigned int m_bDontStream : 1; // Merely assumed, no countercheck possible.
            unsigned int m_bUnderwater : 1;
            unsigned int m_bTunnel : 1;
            unsigned int m_bTunnelTransition : 1;
            unsigned int m_nReserved : 19;
        };
        unsigned int m_nInstanceType;
    };
    int     m_nLodInstanceIndex; // -1 - without LOD model
};

VALIDATE_SIZE(CFileObjectInstance, 0x28);