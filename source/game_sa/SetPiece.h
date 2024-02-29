#pragma once
#include "extensions/FixedRect.hpp"

class CCopPed;
class CVehicle;

enum eSetPieceType : uint8 {
    /* http://gtaforums.com/topic/194990-gtasa-opcodes/?p=1057374595 */
    SETPIECE_NONE = 0,

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
    int32                      m_nLastGenerationTime{};
    FixedRect<int16, 4.0f>     m_AreaRect;
//    FixedVector2D<int16, 4.0f> m_AreaCorner1{};
//    FixedVector2D<int16, 4.0f> m_AreaCorner2{};
    FixedRect<int16, 4.0f>     m_SpawnRect;
//    FixedVector2D<int16, 4.0f> m_SpawnCoord1{};
//    FixedVector2D<int16, 4.0f> m_SpawnCoord2{};
    FixedRect<int16, 4.0f>     m_TargetRect;
//    FixedVector2D<int16, 4.0f> m_TargetCoord1{};
//    FixedVector2D<int16, 4.0f> m_TargetCoord2{};
    eSetPieceType              m_nType{ SETPIECE_NONE };
    char  _pad1D[3];

public:
    static void InjectHooks();

    CSetPiece() = default; // 0x4993C0
    CCopPed* TryToGenerateCopPed(CVector2D posn);
    CVehicle* TryToGenerateCopCar(CVector2D posn, CVector2D target);
    void Update();

    // Unused shit API, implemented them only because I felt sorry for them.
    CVector2D GetSpawnCoord1() const { return m_SpawnRect.GetXY1(); }
    CVector2D GetSpawnCoord2() const { return m_SpawnRect.GetXY2(); }
    CVector2D GetTargetCoord1() const { return m_TargetRect.GetXY1(); }
    CVector2D GetTargetCoord2() const { return m_TargetRect.GetXY2(); }
    void SetCornerA(CVector2D c) { m_AreaRect.left = c.x; m_AreaRect.top = c.y; }
    void SetCornerB(CVector2D c) { m_AreaRect.right = c.x; m_AreaRect.bottom = c.y; }
    void SetSpawnCoord1(CVector2D c) { m_SpawnRect.left = c.x; m_SpawnRect.top = c.y; }
    void SetSpawnCoord2(CVector2D c) { m_SpawnRect.right = c.x; m_SpawnRect.bottom = c.y; }
    void SetTargetCoord1(CVector2D c) { m_TargetRect.left = c.x; m_TargetRect.top = c.y; }
    void SetTargetCoord2(CVector2D c) { m_TargetRect.right = c.x; m_TargetRect.bottom = c.y; }
    float GetCornerAX() const { return m_AreaRect.left; }
    float GetCornerAY() const { return m_AreaRect.top; }
    float GetCornerBX() const { return m_AreaRect.right; }
    float GetCornerBY() const { return m_AreaRect.bottom; }
    float GetSpawnCoord1X() const { return m_SpawnRect.left; }
    float GetSpawnCoord1Y() const { return m_SpawnRect.top; }
    float GetSpawnCoord2X() const { return m_SpawnRect.right; }
    float GetSpawnCoord2Y() const { return m_SpawnRect.bottom; }
    float GetTargetCoord1X() const { return m_TargetRect.left; }
    float GetTargetCoord1Y() const { return m_TargetRect.top; }
    float GetTargetCoord2X() const { return m_TargetRect.right; }
    float GetTargetCoord2Y() const { return m_TargetRect.bottom; }
};
VALIDATE_SIZE(CSetPiece, 0x20);
