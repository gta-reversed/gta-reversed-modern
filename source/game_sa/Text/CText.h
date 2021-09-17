/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CData.h"
#include "CKeyArray.h"
#include "CMissionTextOffsets.h"

namespace TextDebugModule { void ProcessImgui(); };

struct ChunkHeader {
    char  magic[4];
    int32 size;
};

VALIDATE_SIZE(ChunkHeader, 0x8);

enum eTextLangCode : char {
    ENGLISH = 'e',
    GERMAN  = 'g',
    ITALIAN = 'i',
    SPANISH = 's',
    FRENCH  = 'f',
};

class CText {
public:
    CText();
    ~CText();

    void Load(bool bKeepMissionPack);
    void Unload(bool bUnloadMissionData);

    char* Get(const char* key);
    void GetNameOfLoadedMissionText(char* outStr);

    void LoadMissionText(char* mission);
    void LoadMissionPackText();

private:
    CKeyArray           m_MainKeyArray;
    CData               m_MainText;

    CKeyArray           m_MissionKeyArray;
    CData               m_MissionText;

    uint8               m_nLangCode;
    bool                m_bIsMissionTextOffsetsLoaded;
    bool                m_bCdErrorLoaded;
    bool                m_bIsMissionPackLoaded;
    char                m_szMissionName[8];
    char                m_szCdErrorText[256];
    CMissionTextOffsets m_MissionTextOffsets;

private:
    bool ReadChunkHeader(ChunkHeader* header, FILESTREAM file, uint32* offset, uint8 unknown);
    char GetUpperCase(char c) const;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CText* Constructor();
    CText* Destructor();

    friend void TextDebugModule::ProcessImgui();
};

VALIDATE_SIZE(CText, 0xA90);

extern CText& TheText;
