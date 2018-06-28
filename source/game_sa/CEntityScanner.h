/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CEntityScanner {
protected:
    void *vtable;
public:
    int field_4;
    unsigned int   m_nCount;
    class CEntity *m_apEntities[16];
    int field_4C;
};

VALIDATE_SIZE(CEntityScanner, 0x50);
