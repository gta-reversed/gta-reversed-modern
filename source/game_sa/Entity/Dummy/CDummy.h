/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CEntity.h"


class  CDummy : public CEntity {
public:
};


VALIDATE_SIZE(CDummy, 0x38);

bool IsDummyPointerValid(CDummy* pDummy);
