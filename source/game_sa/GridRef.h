#pragma once

#include "Vector.h"

class CGridRef {
public:
    static bool displayGridRef;
    static bool displayCamCords;
    static bool displayAllTheWalls;
    static bool displayWalls;
    static char (&GridRefList)[3200];

public:
    static void InjectHooks();

    static void Init();
    static void GetAreaName(uint8 a1, uint8 a2);
    static void GetArtistBugstarID(uint8 a1, uint8 a2);
    static void GetGridRefPositions(CVector a1, uint8* a2, uint8* a3);
    static void GetGridRefPositions(uint8* a1, uint8* a2);
};
