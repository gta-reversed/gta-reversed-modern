#pragma once

#include "PluginBase.h"

class CPed;

class CPlayerRelationshipRecorder
{
public:
    bool RecordRelationshipWithPlayer(CPed* pPed);
    static CPlayerRelationshipRecorder* GetPlayerRelationshipRecorder();
};