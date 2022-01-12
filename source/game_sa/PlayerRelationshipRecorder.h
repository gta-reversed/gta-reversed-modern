#pragma once

class CPed;

class CPlayerRelationshipRecorder {
public:
    bool                                RecordRelationshipWithPlayer(CPed* pPed);
    static CPlayerRelationshipRecorder* GetPlayerRelationshipRecorder();
};