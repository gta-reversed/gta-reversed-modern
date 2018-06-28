/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CEventHandler {
public:
    class CPed *m_pPed;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    char field_1C;
    char field_1D;
    short field_1E;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
};

VALIDATE_SIZE(CEventHandler, 0x34);