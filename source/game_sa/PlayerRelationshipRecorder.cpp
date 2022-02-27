#include "StdInc.h"

#include "PlayerRelationshipRecorder.h"

CPlayerRelationshipRecorder::CPlayerRelationshipRecorder() {
    Flush();
}

CPlayerRelationshipRecorder::~CPlayerRelationshipRecorder() {
    Flush();
}

void CPlayerRelationshipRecorder::Flush() {
    printf("missing CPlayerRelationshipRecorder::Flush body\n");
}

// 0x61A1D0
bool CPlayerRelationshipRecorder::RecordRelationshipWithPlayer(const CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x61A1D0, CPlayerRelationshipRecorder*, const CPed*>(this, ped);
}

// 0x61A1D0
void CPlayerRelationshipRecorder::ClearRelationshipWithPlayer(const CPed* ped) {
    return plugin::CallMethod<0x61A1D0, CPlayerRelationshipRecorder*, const CPed*>(this, ped);
}

// 0x61A2E0
CPlayerRelationshipRecorder* GetPlayerRelationshipRecorder() {
    return plugin::CallAndReturn<CPlayerRelationshipRecorder*, 0x61A2E0>();
}
