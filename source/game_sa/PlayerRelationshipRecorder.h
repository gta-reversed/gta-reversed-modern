#pragma once

class CPed;

class CPlayerRelationshipRecorder {
public:
    bool RecordRelationshipWithPlayer(CPed* ped);
    static CPlayerRelationshipRecorder* GetPlayerRelationshipRecorder();
};