#pragma once

class CPed;

class CPlayerRelationshipRecorder {
public:
    CPlayerRelationshipRecorder();
    ~CPlayerRelationshipRecorder();

    void Flush();
    void ClearRelationshipWithPlayer(const CPed* ped);
    void AddRelationship(const CPed* ped, int32);
    void GetRelationshipWithPlayer(const CPed* ped);
    bool RecordRelationshipWithPlayer(const CPed* ped);
};

CPlayerRelationshipRecorder* GetPlayerRelationshipRecorder();
