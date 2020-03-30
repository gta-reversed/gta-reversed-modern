#pragma once

class CEntity;
class CColPoint;
class CVector;

class CAudioEngine
{
public:
    void ReportCollision(CEntity* pEntity1, CEntity* pEntity2, int surface1, int surface2, CColPoint* pColPoint, CVector* normal, float fCollisionImpact1, float fCollisionImpact2, int bOnlyPlayOneShotCollisionSound, bool bUnknown);
    void ReportMissionAudioEvent(int eventId, CObject* pObject);
};

extern CAudioEngine& AudioEngine;