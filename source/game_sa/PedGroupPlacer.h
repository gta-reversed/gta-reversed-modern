/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"
#include "ePedType.h"

enum ePedGroupPlacerType {
    GROUP_PLACER_FORMATION1 = 0,
    GROUP_PLACER_FORMATION2 = 0x1, //!< same as FORMATION1
    GROUP_PLACER_CHAT1 = 0x2,
    GROUP_PLACER_CHAT2 = 0x3, //!< same as CHAT1
    GROUP_PLACER_RANDOM = 0x4
};

class CPedGroupPlacer {
public:
    static const int32& ms_minGangSize; // 1
    static const int32& ms_maxGangSize; // 5

    bool PlaceChatGroup(ePedType type, int32 numOfPeds, const CVector* origin, int32 unused);
    bool PlaceFormationGroup(ePedType type, int32 numOfPeds, const CVector* origin, int32 unused);
    //! see ePedGroupPlacerType
    bool PlaceGroup(ePedType type, int32 numOfPeds, const CVector* origin, int32 nGroupPlacerType);
    bool PlaceRandomGroup(ePedType type, int32 numOfPeds, CVector* origin, int32 unused);
};
