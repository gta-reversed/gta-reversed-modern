/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"

class CBaseModelInfo;

class  CModelInfoAccelerator {
public:
    unsigned short *m_pIDs;
    unsigned short  m_nNumIDs;
    char            m_szFilePath[20];
    char field_1A;
    bool m_bFileRead;

    void Init();
    void AddModelInfoId(unsigned short modelId);
    unsigned short GetNextModelInfoId();
    void AllocModelInfoIds();
    void FreeModelInfoIds();
    void GetEntry(CBaseModelInfo** arg0, int* arg1, char* arg2);
    void End(char* arg0);
    CModelInfoAccelerator();
    bool GetModelInfoIdFile();
    void EndOfLoadPhase();
    bool Begin(char* filePath);
};

VALIDATE_SIZE(CModelInfoAccelerator, 0x1C);
