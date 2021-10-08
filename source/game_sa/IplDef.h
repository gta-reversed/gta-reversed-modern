/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Rect.h"

class IplDef {
public:
    CRect m_boundBox;
    char  m_szName[16];
    int16 _pad20;
    int16 m_nMinBuildingId;
    int16 m_nMaxBuildingId;
    int16 m_nMinDummyId;
    int16 m_nMaxDummyId;
    int16 m_nRelatedIpl; // entity arrays index
    bool  m_bInterior;
    char  field_2D;
    bool  m_bLoadRequest;
    bool  m_bDisableDynamicStreaming;
    char  field_30;
    char  field_31;
    char  _pad32[2];
};

VALIDATE_SIZE(IplDef, 0x34);