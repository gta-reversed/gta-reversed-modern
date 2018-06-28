/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CRunningScript.h"

enum eScriptResourceType
{
    RESOURCETYPE_ANIMATION = 1,
    RESOURCETYPE_MODEL_OR_SPECIAL_CHAR,
    RESOURCETYPE_DECISION_MAKER
};


class  CScriptResourceManager {
public:

    struct {
        int m_nModelId;
        void *m_pThread;
        unsigned short type; //see eScriptResourceType
    } m_aScriptResources[75];

    //! see eScriptResourceType
     void AddToResourceManager(int modelID, unsigned int ResourceType, CRunningScript *pScript);
    //! see eScriptResourceType
     bool HasResourceBeenRequested(int ModelId, unsigned int a4);
    //! see eScriptResourceType
     bool RemoveFromResourceManager(int modelID, unsigned int ResourceType, CRunningScript *pScript);
};

VALIDATE_SIZE(CScriptResourceManager,0x384);

//#include "meta/meta.CScriptResourceManager.h"
