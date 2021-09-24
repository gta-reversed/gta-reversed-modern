/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CSetPiece.h"

extern uint32 MAX_SET_PIECES; // default 210

class CSetPieces {
public:
    static void AddOne(uint8 type, CVector2D cornerA, CVector2D cornerB, CVector2D spawnCoord1, CVector2D targetCoord1, CVector2D spawnCoord2, CVector2D targetCoord2);
    static void Init();
    static bool Load();
    static bool Save();
    static void Update();

    static bool &bDebug;
    static uint32 &NumSetPieces;
    static CSetPiece *aSetPieces; // static CSetPiece aSetPieces[MAX_SET_PIECES]
};