/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PtrListDoubleLink.h"

enum eRepeatSectorList : int32 {
    REPEATSECTOR_VEHICLES = 0,
    REPEATSECTOR_PEDS     = 1,
    REPEATSECTOR_OBJECTS  = 2
};

class CRepeatSector {
public:
    CPtrListDoubleLink& GetList(eRepeatSectorList type) noexcept {
        return m_lists[type];
    }

    const CPtrListDoubleLink& GetList(eRepeatSectorList type) const noexcept {
        return m_lists[type];
    }
//private: Preferrably use the accessor method
    CPtrListDoubleLink m_lists[3];
};

VALIDATE_SIZE(CRepeatSector, 0xC);
