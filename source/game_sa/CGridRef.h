#pragma once

#include "CVector.h"

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
    static void GetAreaName(unsigned char a1, unsigned char a2);
    static void GetArtistBugstarID(unsigned char a1, unsigned char a2);
    static void GetGridRefPositions(CVector a1, unsigned char* a2, unsigned char* a3);
    static void GetGridRefPositions(unsigned char* a1, unsigned char* a2);
};
