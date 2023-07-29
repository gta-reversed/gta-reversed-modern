/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "SetPieces.h"

bool& CSetPieces::bDebug = *(bool*)0xA957F8;
uint32& CSetPieces::NumSetPieces = *(uint32*)0xA957FC;
CSetPiece* CSetPieces::aSetPieces = (CSetPiece*)0xA95818;

// 0x499500
void CSetPieces::AddOne(uint8 type, CVector2D cornerA, CVector2D cornerB, CVector2D spawnCoord1, CVector2D targetCoord1, CVector2D spawnCoord2, CVector2D targetCoord2) {
    plugin::Call<0x499500, uint8, CVector2D, CVector2D, CVector2D, CVector2D, CVector2D, CVector2D>(type, cornerA, cornerB, spawnCoord1, targetCoord1, spawnCoord2, targetCoord2);
}

// 0x4994F0
void CSetPieces::Init() {
    ZoneScoped;

    plugin::Call<0x4994F0>();
}

// 0x5D3CA0
bool CSetPieces::Load() {
    return plugin::CallAndReturn<bool, 0x5D3CA0>();
}

// 0x5D3C70
bool CSetPieces::Save() {
    return plugin::CallAndReturn<bool, 0x5D3C70>();
}

// 0x49AA00
void CSetPieces::Update() {
    ZoneScoped;

    plugin::Call<0x49AA00>();
}
