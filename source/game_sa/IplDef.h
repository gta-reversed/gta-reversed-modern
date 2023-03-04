/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Rect.h"

class IplDef {
public:
    CRect m_boundBox{};
    char  m_szName[18]; // Changed to 18 (from 16) (also had to remove padding after it).. Unsure what the actual length was, but `strcpy_s` asserts if it's 16

    int16 m_nMinBuildingId{ SHRT_MAX };
    int16 m_nMaxBuildingId{ SHRT_MIN };

    int16 m_nMinDummyId{ SHRT_MAX };
    int16 m_nMaxDummyId{ SHRT_MIN };

    int16 m_nRelatedIpl{ -1 }; // entity arrays index
    bool  m_bInterior{};
    char  m_IsLoaded{}; // Seemingly something like `m_bIsLoaded`
    bool  m_bLoadRequest{};
    bool  m_bDisableDynamicStreaming{ true };
    char  field_30{};
    char  field_31{}; // Makes bounding box bigger. (+350 vs +200 units). See `CIplStore::LoadIpl`

    constexpr IplDef() = default;

    IplDef(const char* name) {
        strcpy_s(m_szName, name); // Using `_s` variant here
    }
};
VALIDATE_SIZE(IplDef, 0x34);
