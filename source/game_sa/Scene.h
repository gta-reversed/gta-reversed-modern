/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"

class CScene {
public:
    RpWorld*  m_pRpWorld;
    RwCamera* m_pRwCamera;
};

VALIDATE_SIZE(CScene, 0x8);

extern CScene& Scene;