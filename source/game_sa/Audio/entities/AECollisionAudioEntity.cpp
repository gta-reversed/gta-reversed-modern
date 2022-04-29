#include "StdInc.h"

#include "AECollisionAudioEntity.h"

#include "AEAudioHardware.h"
#include "AEAudioUtility.h"

void CAECollisionAudioEntity::InjectHooks() {
    RH_ScopedClass(CAECollisionAudioEntity);
    RH_ScopedCategory("Audio/Entities");

    // RH_ScopedInstall(Initialise, 0x5B9BD0);
    RH_ScopedInstall(InitialisePostLoading, 0x4DA050);
    // RH_ScopedInstall(AddCollisionSoundToList, 0x4DAAC0);
    // RH_ScopedInstall(Reset, 0x4DA320);
    // RH_ScopedInstall(ReportGlassCollisionEvent, 0x4DA070);
    // RH_ScopedInstall(ReportWaterSplash, 0x4DA190);
    // RH_ScopedInstall(UpdateLoopingCollisionSound, 0x4DA540);
    // RH_ScopedInstall(GetCollisionSoundStatus, 0x4DA830);
    // RH_ScopedInstall(ReportObjectDestruction, 0x4DAB60);
    // RH_ScopedInstall(ReportWaterSplash, 0x4DAE40);
    // RH_ScopedInstall(PlayOneShotCollisionSound, 0x4DB150);
    // RH_ScopedInstall(PlayLoopingCollisionSound, 0x4DB450);
    // RH_ScopedInstall(PlayBulletHitCollisionSound, 0x4DB7C0);
    // RH_ScopedInstall(ReportCollision, 0x4DBA10);
    RH_ScopedInstall(ReportBulletHit, 0x4DBDF0);
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
void CAECollisionAudioEntity::AddCollisionSoundToList(CEntity* entity1, CEntity* entity2, uint8 a3, uint8 a4, CAESound* sound, int32 a6) {
    plugin::CallMethod<0x4DAAC0, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, CAESound*, int32>(this, entity1, entity2, a3, a4, sound, a6);
}

// 0x4DA830
int8 CAECollisionAudioEntity::GetCollisionSoundStatus(CEntity* a1, CEntity* a2, uint8 a3, uint8 a4, int32* a5) {
    return plugin::CallMethodAndReturn<int8, 0x4DA830, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, int32*>(this, a1, a2, a3, a4, a5);
}

// 0x4DB150
void CAECollisionAudioEntity::PlayOneShotCollisionSound(CEntity* entity1, CEntity* entity2, uint8 a3, uint8 a4, float a5, CVector& posn) {
    plugin::CallMethod<0x4DB150, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, float, CVector&>(this, entity1, entity2, a3, a4, a5, posn);
}

// 0x4DB450
void CAECollisionAudioEntity::PlayLoopingCollisionSound(CEntity* entity1, CEntity* entity2, uint8 a3, uint8 a4, float a5, CVector& posn, uint8 a7) {
    plugin::CallMethod<0x4DB450, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, float, CVector&, uint8>(this, entity1, entity2, a3, a4, a5, posn, a7);
}

// 0x4DA540
void CAECollisionAudioEntity::UpdateLoopingCollisionSound() {
    return plugin::CallMethod<0x4DA540, CAECollisionAudioEntity*>(this);
}

// 0x4DB7C0
void CAECollisionAudioEntity::PlayBulletHitCollisionSound(uint8 surface, CVector& posn, float angleWithColPointNorm) {
    if (surface >= 195)
        return;

    int32 iRand;
    float maxDistance = 1.5f;
    float volume = CAEAudioEntity::m_pAudioEventVolumes[117];
    if (surface == SURFACE_PED)
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(7, 9);
        while (iRand == m_nRandom);
    }
    else if (g_surfaceInfos->IsAudioWater(surface))
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(16, 18);
        while (iRand == m_nRandom);
        maxDistance = 2.0f;
        volume = volume + 6.0f;
    }
    else if (g_surfaceInfos->IsAudioWood(surface))
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(19, 21);
        while (iRand == m_nRandom);
    }
    else if (g_surfaceInfos->IsAudioMetal(surface))
    {
        float probability = (90.0f - angleWithColPointNorm) * 0.0055555557f; // see BoneNode_c::EulerToQuat
        if (CAEAudioUtility::ResolveProbability(probability))
        {
            do
                iRand = CAEAudioUtility::GetRandomNumberInRange(10, 12);
            while (iRand == m_nRandom);
        }
        else
        {
            do
                iRand = CAEAudioUtility::GetRandomNumberInRange(4, 6);
            while (iRand == m_nRandom);
        }
    }
    else if (g_surfaceInfos->IsAudioConcrete(surface) ||
             g_surfaceInfos->IsAudioGravel(surface) ||
             g_surfaceInfos->IsAudioTile(surface)
    )
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(13, 15);
        while (iRand == m_nRandom);
    }
    else
    {
        do
            iRand = CAEAudioUtility::GetRandomNumberInRange(1, 3);
        while (iRand == m_nRandom);
    }

    if (iRand >= 0) {
        CAESound sound;
        sound.Initialise(3, iRand, this, posn, volume, maxDistance, 1.0f, 1.0f, 0, (eSoundEnvironment)0, 0.02f, 0);
        AESoundManager.RequestNewSound(&sound);
        m_nRandom = iRand;
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
void CAECollisionAudioEntity::ReportCollision(CEntity* entity1, CEntity* entity2, uint8 surfaceA, uint8 surfaceB, CVector& colPoint, CVector* normal, float collisionImpact1, float collisionImpact2, bool bOnlyPlayOneShotCollisionSound, bool unknown) {
    return plugin::CallMethod<0x4DBA10, CAECollisionAudioEntity*, CEntity*, CEntity*, uint8, uint8, CVector&, CVector*, float, float, bool, bool>(this, entity1, entity2, surfaceA, surfaceB, colPoint, normal, collisionImpact1, collisionImpact2, bOnlyPlayOneShotCollisionSound, unknown);
}

// 0x4DBDF0
void CAECollisionAudioEntity::ReportBulletHit(CEntity* entity, uint8 surface, CVector& posn, float angleWithColPointNorm) {
    if (AEAudioHardware.IsSoundBankLoaded(27, 3)) {
        if (entity && entity->IsVehicle())
            surface = entity->AsVehicle()->IsSubBMX() ? SURFACE_HAY_BALE | SURFACE_GRASS_SHORT_DRY : SURFACE_CAR; // ? -68 : 63;

        PlayBulletHitCollisionSound(surface, posn, angleWithColPointNorm);
    }
}

// 0x4DA2C0
void CAECollisionAudioEntity::Service() {
    plugin::CallMethod<0x4DA2C0, CAECollisionAudioEntity*>(this);
}
