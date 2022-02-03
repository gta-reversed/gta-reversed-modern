/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Data.h"
#include "KeyArray.h"
#include "MissionTextOffsets.h"

static inline char(&gGxtString2)[552] = *(char(*)[552])0xC1AED8;
static inline char (&gGxtString)[552] = *(char(*)[552])0xC1B100;

struct ChunkHeader {
    char  magic[4];
    int32 size;
};

VALIDATE_SIZE(ChunkHeader, 0x8);

class CText {
  public:
    CKeyArray           m_MainKeyArray;
    CData               m_MainText;

    CKeyArray           m_MissionKeyArray;
    CData               m_MissionText;

    uint8             m_nLangCode;
    bool                m_bIsMissionTextOffsetsLoaded;
    bool                m_bCdErrorLoaded;
    bool                m_bIsMissionPackLoaded;
    char                m_szMissionName[8];
    char                m_szCdErrorText[256];
    CMissionTextOffsets m_MissionTextOffsets;

  public:
    static void InjectHooks();

    CText();
    ~CText();

    void Load(bool bKeepMissionPack);
    void Unload(bool bUnloadMissionData);

    char* Get(const char* key);
    void GetNameOfLoadedMissionText(char* outStr);

    void LoadMissionText(char* mission);
    void LoadMissionPackText();

  private:
    bool ReadChunkHeader(ChunkHeader* header, FILESTREAM file, uint32* offset, uint8 nSkipBytes);
    char GetUpperCase(char unk);

  private:
    CText* Constructor();
    CText* Destructor();
};

VALIDATE_SIZE(CText, 0xA90);

extern CText& TheText;
