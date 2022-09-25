#pragma once

#include "AEAudioEntity.h"

struct tCollisionAudioEntry {
    CEntity*  m_Entity1;
    CEntity*  m_Entity2;
    CAESound* m_Sound;
    int32     m_nTime;
    uint8     m_nStatus;
    eSurfaceType m_nSurface1;
    eSurfaceType m_nSurface2;
};
VALIDATE_SIZE(tCollisionAudioEntry, 0x14);

class NOTSA_EXPORT_VTABLE CAECollisionAudioEntity : public CAEAudioEntity {
public:
    int16                m_aHistory[194]; // NUM_FUCKING_SURFACES
    int16                field_200;
    int16                m_nRandom;
    int32                m_nCurrentId;
    tCollisionAudioEntry m_Entries[300];

public:
    static void InjectHooks();

    void Initialise();
    static void InitialisePostLoading();
    void Reset();

    void AddCollisionSoundToList(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, CAESound* sound, int32 status);

    int8 GetCollisionSoundStatus(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, int32* a5);

    void PlayLoopingCollisionSound(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, float a5, CVector& posn, uint8 a7);
    void UpdateLoopingCollisionSound();

    void PlayOneShotCollisionSound(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, float a5, CVector& posn);
    void PlayBulletHitCollisionSound(eSurfaceType surface, CVector& posn, float angleWithColPointNorm);

    void ReportGlassCollisionEvent(int32 glassSoundType, Const CVector& posn, uint32 time);
    void ReportWaterSplash(CVector posn, float volume);
    void ReportWaterSplash(CPhysical* physical, float height, bool splashMoreThanOnce);
    void ReportObjectDestruction(CEntity* entity);
    void ReportCollision(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, CVector& colPoint, CVector* normal, float collisionImpact1, float collisionImpact2, bool bOnlyPlayOneShotCollisionSound, bool unknown);
    void ReportBulletHit(CEntity* entity, eSurfaceType surface, CVector& posn, float angleWithColPointNorm);

    void Service();
};

VALIDATE_SIZE(CAECollisionAudioEntity, 0x1978);
