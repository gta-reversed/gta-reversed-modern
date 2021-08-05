#include "StdInc.h"

CAudioEngine& AudioEngine = *reinterpret_cast<CAudioEngine*>(0xB6BC90);

void CAudioEngine::ReportCollision(CEntity* entity1, CEntity* entity2, int32 surface1, int32 surface2, CColPoint* pColPoint, CVector* normal, float fCollisionImpact1, float fCollisionImpact2, int32 bOnlyPlayOneShotCollisionSound, bool bUnknown) {
    return plugin::CallMethod<0x506EB0, CAudioEngine*, CEntity*, CEntity*, int32, int32, CColPoint*, CVector*, float, float, int32, bool>(this, entity1, entity2, surface1, surface2, pColPoint, normal, fCollisionImpact1, fCollisionImpact2, bOnlyPlayOneShotCollisionSound, bUnknown);
}

void CAudioEngine::ReportBulletHit(CEntity* entity, uint8 surfaceType, const CVector& point, float angleWithColPointNorm) {
    plugin::CallMethod<0x506EC0, CAudioEngine*, CEntity*, uint8, const CVector&, float>(this, entity, surfaceType, point, angleWithColPointNorm);
}

void CAudioEngine::ReportMissionAudioEvent(uint16 eventId, CObject* pObject) {
    return plugin::CallMethod<0x507350, CAudioEngine*, uint16, CObject*>(this, eventId, pObject);
}

void CAudioEngine::DisplayRadioStationName() {
    plugin::CallMethod<0x507030, CAudioEngine*>(this);
}

void CAudioEngine::ReportWaterSplash(CPhysical* pPhysical, float volume, bool forcePlaySplashSound) {
    return plugin::CallMethod<0x506F00, CAudioEngine*, CPhysical*, float, uint8>(this, pPhysical, volume, forcePlaySplashSound);
}

void CAudioEngine::ReportWeaponEvent(int32 audioEvent, eWeaponType weaponType, CPhysical* physical) {
    return plugin::CallMethod<0x506F40, CAudioEngine*, int32, eWeaponType, CPhysical*>(this, audioEvent, weaponType, physical);
}

void CAudioEngine::ReportDoorMovement(CPhysical* pPhysical) {
    plugin::CallMethod<0x506F50, CAudioEngine*, CPhysical*>(this, pPhysical);
}

void CAudioEngine::ReportObjectDestruction(CEntity* pEntity) {
    plugin::CallMethod<0x506ED0, CAudioEngine*, CEntity*>(this, pEntity);
}

void CAudioEngine::StopRadio(tVehicleAudioSettings* audioSettings, uint8 bDuringPause) {
    plugin::CallMethod<0x506F70, CAudioEngine*, tVehicleAudioSettings*, uint8>(this, audioSettings, bDuringPause);
}

bool CAudioEngine::IsCutsceneTrackActive() {
    return plugin::CallMethodAndReturn<bool, 0x507150>(this);
}

void CAudioEngine::RetuneRadio(int8 radioId) {
    plugin::CallMethod<0x507E10, CAudioEngine*>(this, radioId);
}

// 0x506EA0
void CAudioEngine::ReportFrontendAudioEvent(eAudioEvents audioEventId, float a2, float a3) {
    plugin::CallMethod<0x506EA0, CAudioEngine*, int32, float, float>(this, audioEventId, a2, a3);
}
