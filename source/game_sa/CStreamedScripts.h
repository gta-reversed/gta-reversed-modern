/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include "CRunningScript.h"

class CStreamedScripts {
public:
    struct
    {
        void *data;
        char m_nStatus;
        char field_5;
        short m_nScmIndex;
        char m_Name[20];
        int m_nsize;
    } m_aScripts[82];

    int m_nLargestExternalSize;
    short m_nCountOfScripts;
    short field_A46;

     signed int FindStreamedScript(char const *scriptname);
     signed int FindStreamedScriptQuiet(char const *scriptName);
     signed short GetProperIndexFromIndexUsedByScript(short scmIndex);
     char const *GetStreamedScriptFilename(unsigned short index);
     unsigned short GetStreamedScriptWithThisStartAddress(unsigned char *dataPtr);
     void Initialise();
     void LoadStreamedScript(RwStream *stream, int index);
     void ReInitialise();
     void ReadStreamedScriptData();
     int RegisterScript(char const *scriptName);
     void RemoveStreamedScriptFromMemory(int index);
     CRunningScript *StartNewStreamedScript(int index);
};
VALIDATE_SIZE(CStreamedScripts, 0xA48);

//#include "meta/meta.CStreamedScripts.h"
