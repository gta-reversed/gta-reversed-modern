/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CEntity.h"
#include "CObject.h"
#include "CVector.h"

struct tScriptForBrains
{
    short m_nIMGindex;
    char m_nAttachType;
    char m_nType;
    char m_ucStatus;
private:
    char __pad[3];
public:
    float m_fRadius;
    unsigned short m_nModelID;
    unsigned short m_nPriority;
    int field_10;
};

class  CScriptsForBrains {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CScriptsForBrains)
public:
    static constexpr int NUM_SCRIPTS = 70;
public:
    tScriptForBrains m_aScriptForBrains[NUM_SCRIPTS];

public:
     void AddNewScriptBrain(short ImgIndex, short Model, unsigned short Priority, signed char attachType, signed char Type, float Radius);
     void AddNewStreamedScriptBrainForCodeUse(short a2, char *a3, signed char attachtype);
     void CheckIfNewEntityNeedsScript(CEntity *pEntity, signed char attachType, void *unused);
     signed short GetIndexOfScriptBrainWithThisName(char const *name, signed char Attachtype);
     bool HasAttractorScriptBrainWithThisNameLoaded(char const *name);
     void Init();
     bool IsObjectWithinBrainActivationRange(CObject *entity, CVector const *point);
     void MarkAttractorScriptBrainWithThisNameAsNoLongerNeeded(char const *name);
     void RequestAttractorScriptBrainWithThisName(char const *name);
     void StartAttractorScriptBrainWithThisName(char const *name, CEntity *pEntity, unsigned char bHasAScriptBrain);
     void StartNewStreamedScriptBrain(unsigned char index, CEntity *pEntity, unsigned char bHasAScriptBrain);
     void StartOrRequestNewStreamedScriptBrain(unsigned char index, CEntity *pEntity, signed char attachType, unsigned char bAddToWaitingArray);
     void StartOrRequestNewStreamedScriptBrainWithThisName(char const *name, CEntity *pEntity, signed char attachType);
     void SwitchAllObjectBrainsWithThisID(signed char ID, bool bStatus);
};

//#include "meta/meta.CScriptsForBrains.h"
