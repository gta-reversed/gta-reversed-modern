/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CObject.h"

class  CHandObject : public CObject {
public:
    class CPed  *m_pPed;
    unsigned int m_nBoneIndex;
    RwTexture   *m_pTexture;
    bool         m_bUpdatedMatricesArray;
    char _pad[3];
};

VALIDATE_SIZE(CHandObject, 0x18C);