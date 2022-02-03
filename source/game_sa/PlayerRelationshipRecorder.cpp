#include "StdInc.h"

#include "PlayerRelationshipRecorder.h"

bool CPlayerRelationshipRecorder::RecordRelationshipWithPlayer(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x61A1D0, CPlayerRelationshipRecorder*, CPed*>(this, ped);
}

CPlayerRelationshipRecorder* CPlayerRelationshipRecorder::GetPlayerRelationshipRecorder()
{
    return plugin::CallAndReturn<CPlayerRelationshipRecorder*, 0x61A2E0>();
}
