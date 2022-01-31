/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CEntity;
class CObject;

struct tScriptForBrains {
    int16  m_nIMGindex;
    char   m_nAttachType;
    char   m_nType;
    char   m_ucStatus;
    char   __pad[3];
    float  m_fRadius;
    uint16 m_nModelID;
    uint16 m_nPriority;
    int32  field_10;
};

class CScriptsForBrains {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CScriptsForBrains)
public:
    static constexpr int32 NUM_SCRIPTS = 70;
public:
    tScriptForBrains m_aScriptForBrains[NUM_SCRIPTS];

public:
     void AddNewScriptBrain(int16 ImgIndex, int16 Model, uint16 Priority, int8 attachType, int8 Type, float Radius);
     void AddNewStreamedScriptBrainForCodeUse(int16 a2, char *a3, int8 attachtype);
     void CheckIfNewEntityNeedsScript(CEntity *pEntity, int8 attachType, void *unused);
     int16 GetIndexOfScriptBrainWithThisName(char const *name, int8 Attachtype);
     bool HasAttractorScriptBrainWithThisNameLoaded(char const *name);
     void Init();
     bool IsObjectWithinBrainActivationRange(CObject *entity, CVector const *point);
     void MarkAttractorScriptBrainWithThisNameAsNoLongerNeeded(char const *name);
     void RequestAttractorScriptBrainWithThisName(char const *name);
     void StartAttractorScriptBrainWithThisName(char const *name, CEntity *pEntity, uint8 bHasAScriptBrain);
     void StartNewStreamedScriptBrain(uint8 index, CEntity *pEntity, uint8 bHasAScriptBrain);
     void StartOrRequestNewStreamedScriptBrain(uint8 index, CEntity *pEntity, int8 attachType, uint8 bAddToWaitingArray);
     void StartOrRequestNewStreamedScriptBrainWithThisName(char const *name, CEntity *pEntity, int8 attachType);
     void SwitchAllObjectBrainsWithThisID(int8 ID, bool bStatus);
};
