#pragma once

#include "AEAudioEntity.h"

struct tCollisionAudioEntry_field_4 {
    int32 dword0;
    int32 dword4;
    int32 dword8;
    bool  byteC;
    bool  byteD;
    bool  byteE;
};

// VALIDATE_SIZE(tCollisionAudioEntry_field_4, 0xF); // 0x14

struct tCollisionAudioEntry {
    int32                         field_0;
    tCollisionAudioEntry_field_4* field_4; // length: 300
    int32                         field_8;
    int32                         field_C;
    int32                         field_10;
};

// VALIDATE_SIZE(tCollisionAudioEntry, 0x14);

class CAECollisionAudioEntity : public CAEAudioEntity {
public:
    char                 field_7C[388];
    int16                field_200;
    int16                m_nRandom;
    int32                field_204;
    tCollisionAudioEntry field_208[300];

public:
    static void InjectHooks();

    void Initialise();
    static void InitialisePostLoading();
    void Reset();

    void AddCollisionSoundToList(CEntity* entity1, CEntity* entity2, uint8 a3, uint8 a4, CAESound* sound, int32 a6);

    int8 GetCollisionSoundStatus(CEntity* a1, CEntity* a2, uint8 a3, uint8 a4, int32* a5);

    void PlayLoopingCollisionSound(CEntity* entity1, CEntity* entity2, uint8 a3, uint8 a4, float a5, CVector& posn, uint8 a7);
    void UpdateLoopingCollisionSound();

    void PlayOneShotCollisionSound(CEntity* entity1, CEntity* entity2, uint8 a3, uint8 a4, float a5, CVector& posn);
    void PlayBulletHitCollisionSound(uint8 surface, CVector& posn, float angleWithColPointNorm);

    void ReportGlassCollisionEvent(int32 glassSoundType, CVector& posn, uint32 time);
    void ReportWaterSplash(CVector posn, float volume);
    void ReportWaterSplash(CPhysical* physical, float height, bool splashMoreThanOnce);
    void ReportObjectDestruction(CEntity* entity);
    void ReportCollision(CEntity* entity1, CEntity* entity2, uint8 surfaceA, uint8 surfaceB, CVector& colPoint, CVector* normal, float collisionImpact1, float collisionImpact2, bool bOnlyPlayOneShotCollisionSound, bool unknown);
    void ReportBulletHit(CEntity* entity, uint8 surface, CVector& posn, float angleWithColPointNorm);

    void Service();
};

VALIDATE_SIZE(CAECollisionAudioEntity, 0x1978);
