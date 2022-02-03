/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CCopPed;
class CVehicle;

enum eSetPieceType {
    /* http://gtaforums.com/topic/194990-gtasa-opcodes/?p=1057374595 */

    SETPIECE_2CARS_SLOW_SPEED = 1,
    SETPIECE_1CAR_QUICK_SPEED = 2,
    SETPIECE_1CAR_MEDIUM_SPEED = 3,
    SETPIECE_1PED = 4,
    SETPIECE_2PEDS = 5,
    SETPIECE_2CARS_QUICK_SPEED_BEFORE_HIT = 6,
    SETPIECE_2CARS_QUICK_SPEED = 7,
    SETPIECE_2CARS_MEDIUM_SPEED = 8
};

class CSetPiece {
public:
    int32 m_nLastGenerationTime;
    int16 m_nAreaCornerX1;
    int16 m_nAreaCornerY1;
    int16 m_nAreaCornerX2;
    int16 m_nAreaCornerY2;
    int16 m_nSpawnCoord1X;
    int16 m_nSpawnCoord1Y;
    int16 m_nSpawnCoord2X;
    int16 m_nSpawnCoord2Y;
    int16 m_nTargetCoord1X;
    int16 m_nTargetCoord1Y;
    int16 m_nTargetCoord2X;
    int16 m_nTargetCoord2Y;
    uint8 m_nType; // see eSetPieceType
    char  _pad1D[3];

public:

    CSetPiece();
    CVector2D GetSpawnCoord1();
    CVector2D GetSpawnCoord2();
    CVector2D GetTargetCoord1();
    CVector2D GetTargetCoord2();
    void SetCornerA(CVector2D coord);
    void SetCornerB(CVector2D coord);
    void SetSpawnCoord1(CVector2D coord);
    void SetSpawnCoord2(CVector2D coord);
    void SetTargetCoord1(CVector2D coord);
    void SetTargetCoord2(CVector2D coord);
    float GetCornerAX();
    float GetCornerAY();
    float GetCornerBX();
    float GetCornerBY();
    float GetSpawnCoord1X();
    float GetSpawnCoord1Y();
    float GetSpawnCoord2X();
    float GetSpawnCoord2Y();
    float GetTargetCoord1X();
    float GetTargetCoord1Y();
    float GetTargetCoord2X();
    float GetTargetCoord2Y();
    CCopPed* TryToGenerateCopPed(CVector2D posn);
    CVehicle* TryToGenerateCopCar(CVector2D posn, CVector2D target);
    void Update();
};

VALIDATE_SIZE(CSetPiece, 0x20);
