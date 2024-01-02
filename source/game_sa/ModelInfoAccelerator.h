/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CBaseModelInfo;

class CModelInfoAccelerator {
public:
    uint16* m_pIDs;
    uint16  m_nNumIDs;
    char    m_szFilePath[20];
    bool    field_1A; // always false
    bool    m_bFileRead;

    static constexpr int32 BUFFER_SIZE = 41100;

public:
    CModelInfoAccelerator();
    ~CModelInfoAccelerator() = default;

    void Init();
    void AddModelInfoId(uint16 modelId);
    uint16 GetNextModelInfoId();
    void AllocModelInfoIds();
    void FreeModelInfoIds();
    void GetEntry(CBaseModelInfo** mi, int32* arg1, char* arg2);
    bool Begin(const char* filePath);
    void End(const char* filePath);
    bool GetModelInfoIdFile();
    void EndOfLoadPhase();
};
VALIDATE_SIZE(CModelInfoAccelerator, 0x1C);
