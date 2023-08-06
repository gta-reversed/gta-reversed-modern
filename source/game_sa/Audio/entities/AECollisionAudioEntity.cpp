#include "StdInc.h"

#include "AECollisionAudioEntity.h"

#include "AEAudioHardware.h"
#include "AEAudioUtility.h"

void CAECollisionAudioEntity::InjectHooks() {
    RH_ScopedClass(CAECollisionAudioEntity);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Initialise, 0x5B9BD0, { .reversed = false });
    RH_ScopedInstall(InitialisePostLoading, 0x4DA050);
    RH_ScopedInstall(AddCollisionSoundToList, 0x4DAAC0, { .reversed = false });
    RH_ScopedInstall(Reset, 0x4DA320, { .reversed = false });
    RH_ScopedInstall(ReportGlassCollisionEvent, 0x4DA070, { .reversed = false });
    RH_ScopedInstall(UpdateLoopingCollisionSound, 0x4DA540, { .reversed = false });
    RH_ScopedInstall(GetCollisionSoundStatus, 0x4DA830, { .reversed = false });
    RH_ScopedInstall(ReportObjectDestruction, 0x4DAB60, { .reversed = false });
    RH_ScopedInstall(PlayOneShotCollisionSound, 0x4DB150, { .reversed = false });
    RH_ScopedInstall(PlayLoopingCollisionSound, 0x4DB450, { .reversed = false });
    RH_ScopedInstall(PlayBulletHitCollisionSound, 0x4DB7C0, { .reversed = false });
    RH_ScopedInstall(ReportCollision, 0x4DBA10, { .reversed = false });
    RH_ScopedInstall(ReportBulletHit, 0x4DBDF0);

    RH_ScopedOverloadedInstall(ReportWaterSplash, "0", 0x4DA190, void(CAECollisionAudioEntity::*)(CVector, float), { .reversed = false });
    RH_ScopedOverloadedInstall(ReportWaterSplash, "1", 0x4DAE40, void(CAECollisionAudioEntity::*)(CPhysical*, float, bool), { .reversed = false });
}

// 0x5B9BD0
void CAECollisionAudioEntity::Initialise() {
    plugin::CallMethod<0x5B9BD0, CAECollisionAudioEntity*>(this);
}

// 0x4DA050
void CAECollisionAudioEntity::InitialisePostLoading() {
    AEAudioHardware.LoadSoundBank(39, SLOT_LOADING_TUNE_LEFT);
    AEAudioHardware.LoadSoundBank(27, 3);
}

// 0x4DA320
void CAECollisionAudioEntity::Reset() {
    plugin::CallMethod<0x4DA320, CAECollisionAudioEntity*>(this);
}

// 0x4DAAC0
void CAECollisionAudioEntity::AddCollisionSoundToList(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, CAESound* sound, int32 status) {
    plugin::CallMethod<0x4DAAC0, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, CAESound*, int32>(this, entity1, entity2, surf1, surf2, sound, status);
}

// 0x4DA830
int8 CAECollisionAudioEntity::GetCollisionSoundStatus(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, int32* a5) {
    return plugin::CallMethodAndReturn<int8, 0x4DA830, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, int32*>(this, entity1, entity2, surf1, surf2, a5);
}

// 0x4DB150
void CAECollisionAudioEntity::PlayOneShotCollisionSound(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, float a5, CVector& posn) {
    plugin::CallMethod<0x4DB150, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, float, CVector&>(this, entity1, entity2, surf1, surf2, a5, posn);
}

// 0x4DB450
void CAECollisionAudioEntity::PlayLoopingCollisionSound(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, float a5, CVector& posn, uint8 a7) {
    plugin::CallMethod<0x4DB450, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, float, CVector&, uint8>(this, entity1, entity2, surf1, surf2, a5, posn, a7);
}

// 0x4DA540
void CAECollisionAudioEntity::UpdateLoopingCollisionSound() {
    return plugin::CallMethod<0x4DA540, CAECollisionAudioEntity*>(this);
}

// 0x4DB7C0
void CAECollisionAudioEntity::PlayBulletHitCollisionSound(eSurfaceType surface, CVector& posn, float angleWithColPointNorm) {
    if (surface >= NUM_FUCKING_SURFACES)
        return;

    int32 iRand;
    float maxDistance = 1.5f;
    float volume = GetDefaultVolume(AE_BULLET_HIT);
    if (surface == SURFACE_PED)
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(7, 9);
        while (iRand == m_nLastBulletHitSoundID);
    }
    else if (g_surfaceInfos.IsAudioWater(surface))
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(16, 18);
        while (iRand == m_nLastBulletHitSoundID);
        maxDistance = 2.0f;
        volume = volume + 6.0f;
    }
    else if (g_surfaceInfos.IsAudioWood(surface))
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(19, 21);
        while (iRand == m_nLastBulletHitSoundID);
    }
    else if (g_surfaceInfos.IsAudioMetal(surface))
    {
        float probability = (90.0f - angleWithColPointNorm) / 180.0f; // see BoneNode_c::EulerToQuat
        if (CAEAudioUtility::ResolveProbability(probability))
        {
            do
                iRand = CAEAudioUtility::GetRandomNumberInRange(10, 12);
            while (iRand == m_nLastBulletHitSoundID);
        }
        else
        {
            do
                iRand = CAEAudioUtility::GetRandomNumberInRange(4, 6);
            while (iRand == m_nLastBulletHitSoundID);
        }
    } else if (g_surfaceInfos.IsAudioGravelConcreteOrTile(surface))
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(13, 15);
        while (iRand == m_nLastBulletHitSoundID);
    }
    else
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(1, 3);
        while (iRand == m_nLastBulletHitSoundID);
    }

    if (iRand >= 0) {
        CAESound sound;
        sound.Initialise(3, iRand, this, posn, volume, maxDistance, 1.0f, 1.0f, 0, SOUND_DEFAULT, 0.02f, 0);
        AESoundManager.RequestNewSound(&sound);
        m_nLastBulletHitSoundID = iRand;
    }
}

// 0x4DA070
void CAECollisionAudioEntity::ReportGlassCollisionEvent(int32 glassSoundType, Const CVector& posn, uint32 time) {
    plugin::CallMethod<0x4DA070, CAECollisionAudioEntity*, int32, const CVector&, uint32>(this, glassSoundType, posn, time);
}

// 0x4DA190
void CAECollisionAudioEntity::ReportWaterSplash(CVector posn, float volume) {
    return plugin::CallMethod<0x4DA190, CAECollisionAudioEntity*, CVector, float>(this, posn, volume);
}

// 0x4DAE40
void CAECollisionAudioEntity::ReportWaterSplash(CPhysical* physical, float height, bool splashMoreThanOnce) {
    return plugin::CallMethod<0x4DAE40, CAECollisionAudioEntity*, CPhysical*, float, bool>(this, physical, height, splashMoreThanOnce);
}

// 0x4DAB60
void CAECollisionAudioEntity::ReportObjectDestruction(CEntity* entity) {
    return plugin::CallMethod<0x4DAB60, CAECollisionAudioEntity*, CEntity*>(this, entity);
}

// 0x4DBA10
void CAECollisionAudioEntity::ReportCollision(CEntity* entity1, CEntity* entity2, eSurfaceType surf1, eSurfaceType surf2, CVector& colPoint, CVector* normal, float collisionImpact1, float collisionImpact2, bool bOnlyPlayOneShotCollisionSound, bool unknown) {
    return plugin::CallMethod<0x4DBA10, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, CVector&, CVector*, float, float, bool, bool>(this, entity1, entity2, surf1, surf2, colPoint, normal, collisionImpact1, collisionImpact2, bOnlyPlayOneShotCollisionSound, unknown);
}

// 0x4DBDF0
void CAECollisionAudioEntity::ReportBulletHit(CEntity* entity, eSurfaceType surface, CVector& posn, float angleWithColPointNorm) {
    if (AEAudioHardware.IsSoundBankLoaded(27, 3)) {
        if (entity && entity->IsVehicle()) {
            surface = entity->AsVehicle()->IsSubBMX() ? eSurfaceType(188) : SURFACE_CAR; // todo: C* Surface
        }

        PlayBulletHitCollisionSound(surface, posn, angleWithColPointNorm);
    }
}

// 0x4DA2C0
void CAECollisionAudioEntity::Service() {
    plugin::CallMethod<0x4DA2C0, CAECollisionAudioEntity*>(this);
}
