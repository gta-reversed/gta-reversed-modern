/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CRunningScript;

enum eScriptResourceType {
    RESOURCE_TYPE_ANIMATION = 1,
    RESOURCE_TYPE_MODEL_OR_SPECIAL_CHAR,
    RESOURCE_TYPE_DECISION_MAKER
};

struct tScriptResource {
    int32               m_nModelId;
    void*               m_pThread;
    eScriptResourceType m_nType;
};

class CScriptResourceManager {
public:
    tScriptResource m_aScriptResources[75];

public:
    void Initialise();
    void AddToResourceManager(int32 modelId, eScriptResourceType resourceType, CRunningScript* script);
    bool RemoveFromResourceManager(int32 modelId, eScriptResourceType resourceType, CRunningScript* script);
    bool HasResourceBeenRequested(int32 modelId, eScriptResourceType resourceType);
    bool Save();
    bool Load();
};

VALIDATE_SIZE(CScriptResourceManager, 0x384);
VALIDATE_SIZE(tScriptResource, 0xC);
