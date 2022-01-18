#include "StdInc.h"

bool CPlayerRelationshipRecorder::RecordRelationshipWithPlayer(CPed* pPed)
{
    return plugin::CallMethodAndReturn<bool, 0x61A1D0, CPlayerRelationshipRecorder*, CPed*>(this, pPed);
}

CPlayerRelationshipRecorder* CPlayerRelationshipRecorder::GetPlayerRelationshipRecorder()
{
    return plugin::CallAndReturn<CPlayerRelationshipRecorder*, 0x61A2E0>();
}