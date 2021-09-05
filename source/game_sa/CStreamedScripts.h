/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "CRunningScript.h"

class CStreamedScripts {
public:
    struct {
        void* data;
        char  m_nStatus;
        char  field_5;
        int16 m_nScmIndex;
        char  m_Name[20];
        int32 m_nsize;
    } m_aScripts[82];

    int32 m_nLargestExternalSize;
    int16 m_nCountOfScripts;
    int16 field_A46;

    int32           FindStreamedScript(char const* scriptname);
    int32           FindStreamedScriptQuiet(char const* scriptName);
    int16           GetProperIndexFromIndexUsedByScript(int16 scmIndex);
    const char*     GetStreamedScriptFilename(uint16 index);
    uint16          GetStreamedScriptWithThisStartAddress(uint8* dataPtr);
    void            Initialise();
    void            LoadStreamedScript(RwStream* stream, int32 index);
    void            ReInitialise();
    void            ReadStreamedScriptData();
    int32           RegisterScript(char const* scriptName);
    void            RemoveStreamedScriptFromMemory(int32 index);
    CRunningScript* StartNewStreamedScript(int32 index);
};
VALIDATE_SIZE(CStreamedScripts, 0xA48);
