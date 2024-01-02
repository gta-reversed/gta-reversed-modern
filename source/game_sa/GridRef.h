#pragma once

class CVector;

// See DATA\GRIDREF.DAT
class CGridRef {
public:
    static bool displayGridRef;
    static bool displayCamCords;
    static bool displayAllTheWalls;
    static bool displayWalls;

public:
    static void InjectHooks();

    static void Init();
    static int32 GetAreaName(uint8 x, uint8 y);
    static char* GetArtistBugstarID(uint8 x, uint8 y);
    static void GetGridRefPositions(CVector pos, uint8* x, uint8* y);
    static void GetGridRefPositions(uint8* x, uint8* y);
};
