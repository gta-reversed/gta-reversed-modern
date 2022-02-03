/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CRunningScript;

enum eScriptResourceType {
    RESOURCETYPE_ANIMATION = 1,
    RESOURCETYPE_MODEL_OR_SPECIAL_CHAR,
    RESOURCETYPE_DECISION_MAKER
};

class CScriptResourceManager {
public:
    struct {
        int32  m_nModelId;
        void*  m_pThread;
        uint16 type; // see eScriptResourceType
    } m_aScriptResources[75];

    //! see eScriptResourceType
    void AddToResourceManager(int32 modelID, uint32 ResourceType, CRunningScript* pScript);
    //! see eScriptResourceType
    bool HasResourceBeenRequested(int32 ModelId, uint32 a4);
    //! see eScriptResourceType
    bool RemoveFromResourceManager(int32 modelID, uint32 ResourceType, CRunningScript* pScript);
};

VALIDATE_SIZE(CScriptResourceManager, 0x384);
