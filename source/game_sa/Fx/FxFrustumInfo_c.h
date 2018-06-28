/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "FxSphere_c.h"
#include "FxPlane_c.h"

class FxFrustumInfo_c {
public:
    FxSphere_c m_sphere;
	FxPlane_c m_planes[4];

    bool IsCollision(FxSphere_c* sphere);
};

VALIDATE_SIZE(FxFrustumInfo_c, 0x54);