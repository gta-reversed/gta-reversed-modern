#include "StdInc.h"

CAudioEngine& AudioEngine = *reinterpret_cast<CAudioEngine*>(0xB6BC90);

void CAudioEngine::ReportCollision(CEntity* pEntity1, CEntity* pEntity2, int surface1, int surface2, CColPoint* pColPoint, CVector* normal, float fCollisionImpact1, float fCollisionImpact2, int bOnlyPlayOneShotCollisionSound, bool bUnknown)
{
    return plugin::CallMethod<0x506EB0, CAudioEngine*, CEntity*, CEntity*, int, int, CColPoint*, CVector*, float, float, int, bool>(this,
        pEntity1, pEntity2, surface1, surface2, pColPoint, normal, fCollisionImpact1, fCollisionImpact2, bOnlyPlayOneShotCollisionSound, bUnknown);
}

void CAudioEngine::ReportMissionAudioEvent(ushort eventId, CObject* pObject)
{
    return plugin::CallMethod <0x507350, CAudioEngine*, ushort, CObject*>(this, eventId, pObject);
}

void CAudioEngine::DisplayRadioStationName()
{
    plugin::CallMethod<0x507030, CAudioEngine*>(this);
}

void CAudioEngine::ReportWaterSplash(CPhysical* pPhysical, float volume, bool forcePlaySplashSound) {
    return plugin::CallMethod<0x506F00, CAudioEngine*, CPhysical*, float, unsigned char>(this, pPhysical, volume, forcePlaySplashSound);
}

void CAudioEngine::ReportWeaponEvent(int32_t audioEvent, eWeaponType weaponType, CPhysical* physical)
{
    return plugin::CallMethod<0x506F40, CAudioEngine*, int32_t, eWeaponType, CPhysical*>(this, audioEvent, weaponType, physical);
}

void CAudioEngine::ReportDoorMovement(CPhysical* pPhysical)
{
    plugin::CallMethod<0x506F50, CAudioEngine*, CPhysical*>(this, pPhysical);
}

void CAudioEngine::ReportObjectDestruction(CEntity* pEntity)
{
    plugin::CallMethod<0x506ED0, CAudioEngine*, CEntity*>(this, pEntity);
}

void CAudioEngine::StopRadio(tVehicleAudioSettings* audioSettings, unsigned char bDuringPause)
{
    plugin::CallMethod<0x506F70, CAudioEngine*, tVehicleAudioSettings*, unsigned char>(this, audioSettings, bDuringPause);
}

bool CAudioEngine::IsCutsceneTrackActive() {
    return plugin::CallMethodAndReturn<bool, 0x507150>(this);
}

void CAudioEngine::RetuneRadio(signed char radioId) {
    plugin::CallMethod<0x507E10, CAudioEngine*>(this, radioId);
}

// 0x506EA0
void CAudioEngine::ReportFrontendAudioEvent(eAudioEvents audioEventId, float a2, float a3) {
    plugin::CallMethod<0x506EA0, CAudioEngine*, int, float, float>(this, audioEventId, a2, a3);
}
