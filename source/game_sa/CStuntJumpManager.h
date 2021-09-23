#pragma once

#include "CBoundingBox.h"
#include "CVector.h"
#include "CPool.h"

enum class eJumpState : uint8 {
    START_POINT_INTERSECTED,
    IN_FLIGHT,
    END_POINT_INTERSECTED,
};

struct CStuntJump {
    CBoundingBox start;  // 0x00
    CBoundingBox end;    // 0x24
    CVector      camera; // 0x30
    int32        reward; // 0x3C
    bool         done;   // 0x40
    bool         found;  // 0x41
    // char         _pad[2];   // 0x42
};

// VALIDATE_SIZE(CStuntJump, 0x44);

class CStuntJumpManager {
public:
    static CPool<CStuntJump>* mp_poolStuntJumps;
    static CStuntJump*        mp_Active;
    static bool               m_bActive;
    static bool               m_bHitReward;
    static uint32             m_iTimer;
    static eJumpState         m_jumpState;
    static int32              m_iNumJumps;
    static uint32             m_iNumCompleted;

public:
    static void InjectHooks();

    static void Init();
    static void Shutdown();
    static void ShutdownForRestart();
    static void Save();
    static void Load(int32 a1, int32 a2);
    static void AddOne(const CBoundingBox& start, const CBoundingBox& end, const CVector& cameraPosn, int32 reward);
    static void Update();

    static void SetActive(bool active);
    static void Render();
};

extern void StuntJumpTestCode();
