#pragma once

class CPed;

class CPlayerRelationshipRecorder {
public:
    bool RecordRelationshipWithPlayer(CPed* ped);
    void ClearRelationshipWithPlayer(CPed* ped);
    static CPlayerRelationshipRecorder* GetPlayerRelationshipRecorder();
};
