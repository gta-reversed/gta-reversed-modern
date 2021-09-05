/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CVector.h"
#include "CAEExplosionAudioEntity.h"

enum eExplosionType {
    EXPLOSION_GRENADE,
    EXPLOSION_MOLOTOV,
    EXPLOSION_ROCKET,
    EXPLOSION_WEAK_ROCKET,
    EXPLOSION_CAR,
    EXPLOSION_QUICK_CAR,
    EXPLOSION_BOAT,
    EXPLOSION_AIRCRAFT,
    EXPLOSION_MINE,
    EXPLOSION_OBJECT,
    EXPLOSION_TANK_FIRE,
    EXPLOSION_SMALL,
    EXPLOSION_RC_VEHICLE
};

class CEntity;

class CExplosion {
public:
    uint32   m_nType; // see eExplosionType
    CVector  m_vecPosition;
    float    m_fRadius;
    float    m_fPropagationRate;
    CEntity* m_pCreator;
    CEntity* m_pVictim;
    int32    m_nExpireTime;
    float    m_fDamagePercentage;
    bool     m_bIsActive;
    uint8    m_nActiveCounter;
    bool     m_bMakeSound;
    int32    m_nCreatedTime;
    int32    m_nParticlesExpireTime;
    float    m_fVisibleDistance;
    float    m_fGroundZ;
    int32    m_nFuelTimer; // goes down
    CVector  m_vecFuelDirection[3];
    float    m_fFuelOffsetDistance[3];
    float    m_fFuelSpeed[3];

    static CAEExplosionAudioEntity &m_ExplosionAudioEntity;

    static void InjectHooks();

    static void ClearAllExplosions();
    // dummy function
    static void Shutdown();
    static uint8 GetExplosionActiveCounter(uint8 explosionId);
    static void ResetExplosionActiveCounter(uint8 explosionId);
    static bool DoesExplosionMakeSound(uint8 explosionId);
    static uint32 GetExplosionType(uint8 explosionId);
    static CVector* GetExplosionPosition(uint8 explosionId);
    static bool TestForExplosionInArea(eExplosionType explosionType, float x1, float y1, float z1, float x2, float y2, float z2);
    static void RemoveAllExplosionsInArea(CVector posn, float radius);
    static void Initialise();
    static bool AddExplosion(CEntity* victim, CEntity* creator, eExplosionType explosionType, const CVector& posn, uint32 time, bool bMakeSound, float camShake, bool bHideExplosion);
    static void Update();
};

VALIDATE_SIZE(CExplosion, 0x7C);

extern uint32 MAX_EXPLOSIONS; // default 16
extern CExplosion *aExplosions; // CExplosion aExplosions[MAX_EXPLOSIONS]
