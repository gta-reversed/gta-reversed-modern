#pragma once

#include "CBoundingBox.h"
#include "CVector.h"
#include "CPool.h"

enum class eJumpState : unsigned char {
    START_POINT_INTERSECTED,
    IN_FLIGHT,
    END_POINT_INTERSECTED,
};

struct CStuntJump {
    CBoundingBox start;     // 0x00
    CBoundingBox end;       // 0x24
    CVector      camera;    // 0x30
    int          reward;    // 0x3C
    bool         done;      // 0x40
    bool         found;     // 0x41
    // char         _pad[2];   // 0x42
};

// VALIDATE_SIZE(CStuntJump, 0x44);

class CStuntJumpManager {
public:
    static CPool<CStuntJump>* mp_poolStuntJumps;
    static CStuntJump*        mp_Active;
    static bool               m_bActive;
    static bool               m_bHitReward;
    static int                m_iTimer;
    static eJumpState         m_jumpState;
    static int                m_iNumJumps;
    static unsigned int       m_iNumCompleted;

public:
    static void InjectHooks();

    static void Init();
    static void Shutdown();
    static void ShutdownForRestart();
    static void Save();
    static void Load(int a1, int a2);
    static void AddOne(const CBoundingBox& start, const CBoundingBox& end, const CVector& cameraPosn, int reward);
    static void Update();

    static void SetActive(bool active);
    static void Render();
};

extern void StuntJumpTestCode();
