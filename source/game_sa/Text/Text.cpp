#include "StdInc.h"

#include "GxtChar.h"

#include "Text.h"
#include "Data.h"
#include "KeyArray.h"
#include "MissionTextOffsets.h"

#include "eLanguage.h"

#define CHUNK_TKEY "TKEY"
#define CHUNK_TDAT "TDAT"
#define CHUNK_TABL "TABL"

CText& TheText = *(CText*)0xC1B340;

// 0x56D3A4
static constexpr uint8 FrenchUpperCaseTable[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x41, 0x41, 0x41, 0x41, 0x84, 0x85, 0x45, 0x45, 0x45,
    0x45, 0x49, 0x49, 0x49, 0x49, 0x4F, 0x4F, 0x4F, 0x4F, 0x55, 0x55, 0x55, 0x55, 0xAD, 0xAD, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,

    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
    0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0xAD, 0xAD, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
};

void CText::InjectHooks() {
    RH_ScopedClass(CText);
    RH_ScopedCategory("Text");


    RH_ScopedInstall(Constructor, 0x6A00F0);
    RH_ScopedInstall(Destructor, 0x6A0140);
    RH_ScopedInstall(Get, 0x6A0050);
    RH_ScopedInstall(GetNameOfLoadedMissionText, 0x69FBD0);
    RH_ScopedInstall(ReadChunkHeader, 0x69F940, { .reversed = false });
    RH_ScopedInstall(LoadMissionPackText, 0x69F9A0, { .reversed = false });
    RH_ScopedInstall(LoadMissionText, 0x69FBF0, { .reversed = false });
    RH_ScopedInstall(Load, 0x6A01A0);
    RH_ScopedInstall(Unload, 0x69FF20);

    //
    // TODO: These should be moved to their respective files...
    //

    {
        RH_ScopedClass(CMissionTextOffsets);
        RH_ScopedInstall(Load, 0x69F670, { .reversed = false });
    }

    {
        RH_ScopedClass(CData);
        RH_ScopedInstall(Unload, 0x69F640);
        RH_ScopedInstall(Load, 0x69F5D0, { .reversed = false });


    }

    {
        RH_ScopedClass(CKeyArray);

        RH_ScopedCategory("Text");
        RH_ScopedInstall(Unload, 0x69F510);

        RH_ScopedInstall(BinarySearch, 0x69F570);
        RH_ScopedInstall(Search, 0x6A0000);
        RH_ScopedInstall(Load, 0x69F490, { .reversed = false });
    }
}

// 0x6A00F0
CText::CText() {
    m_MissionText.Unload();
    m_MissionKeyArray.Unload();
    m_MainText.Unload();
    m_MainKeyArray.Unload();

    m_bIsMissionPackLoaded = false;
    m_bIsMissionTextOffsetsLoaded = false;
    m_nLangCode = 'e'; // english

    m_szCdErrorText[0] = '\0';
    m_szMissionName[0] = '\0';
    GxtErrorString[0] = '\0';
}

// 0x6A0140
CText::~CText() {
    m_MissionText.Unload();
    m_MissionKeyArray.Unload();
    m_MainText.Unload();
    m_MainKeyArray.Unload();
}

// Unloads GXT file
// 0x69FF20
void CText::Unload(bool bUnloadMissionData) {
    CMessages::ClearAllMessagesDisplayedByGame(false);

    m_MainKeyArray.Unload();
    m_MainText.Unload();
    m_bCdErrorLoaded = false;
    if (!bUnloadMissionData) {
        m_MissionKeyArray.Unload();
        m_MissionText.Unload();

        m_bIsMissionPackLoaded = false;
        m_szMissionName[0] = '\0';
    }
}

// Loads GXT file
// 0x6A01A0
void CText::Load(bool bKeepMissionPack) {
    m_bIsMissionTextOffsetsLoaded = false;
    Unload(bKeepMissionPack);

    char filename[32] = {0};
    switch (static_cast<eLanguage>(FrontEndMenuManager.m_nPrefsLanguage)) {
    case eLanguage::AMERICAN:
        sprintf(filename, "AMERICAN.GXT");
        break;
        case eLanguage::FRENCH:
            sprintf(filename, "FRENCH.GXT");
            break;
            case eLanguage::GERMAN:
                sprintf(filename, "GERMAN.GXT");
                break;
                case eLanguage::ITALIAN:
                    sprintf(filename, "ITALIAN.GXT");
                    break;
                    case eLanguage::SPANISH:
                        sprintf(filename, "SPANISH.GXT");
                        break;
#ifdef MORE_LANGUAGES
                        case eLanguage::RUSSIAN:
                            sprintf(filename, "RUSSIAN.GXT");
                            break;
                            case eLanguage::JAPANESE:
                                sprintf(filename, "JAPANESE.GXT");
                                break;
#endif
    }

    CFileMgr::SetDir("TEXT");
    auto file = CFileMgr::OpenFile(filename, "rb");

    uint16 version = 0;
    uint16 encoding = 0;
    CFileMgr::Read(file, &version, sizeof(version));
    CFileMgr::Read(file, &encoding, sizeof(encoding));

    uint32 offset = sizeof(uint16) * 2; // skip version and encoding
    bool bTKEY = false;
    bool bTDAT = false;
    ChunkHeader header{};
    while (!bTKEY || !bTDAT) {
        ReadChunkHeader(&header, file, &offset, 0);
        if (header.size == 0)
            continue;

        if (strncmp(header.magic, CHUNK_TABL, sizeof(header.magic)) == 0) {
            m_MissionTextOffsets.Load(header.size, file, &offset, 0x58000); // todo: magic
            m_bIsMissionTextOffsetsLoaded = true;
        }
        else if (strncmp(header.magic, CHUNK_TKEY, sizeof(header.magic)) == 0) {
            m_MainKeyArray.Load(header.size, file, &offset, 0);
            bTKEY = true;
        }
        else if (strncmp(header.magic, CHUNK_TDAT, sizeof(header.magic)) == 0) {
            m_MainText.Load(header.size, file, &offset, 0);
            bTDAT = true;
        }
        else {
            CFileMgr::Seek(file, header.size, SEEK_CUR);
            offset += header.size;
        }
    }

    m_MainKeyArray.Update(m_MainText.data);
    CFileMgr::CloseFile(file);

    const auto text = TheText.Get("CDERROR");
    strcpy(m_szCdErrorText, GxtCharToAscii(text, 0));
    m_bCdErrorLoaded = true;

    CFileMgr::SetDir("");

    if (bKeepMissionPack)
        return;

    while (!m_bIsMissionPackLoaded && CGame::bMissionPackGame) {
        if (FrontEndMenuManager.CheckMissionPackValidMenu()) {
            CTimer::Suspend();
            LoadMissionPackText();
            CFileMgr::SetDir("");
            CTimer::Resume();
        }
    }
}

// 0x69FBF0
void CText::LoadMissionText(char* mission) {
    plugin::CallMethod<0x69FBF0, CText*, char*>(this, mission);
}

// Loads mission table from GXT file
// 0x69F9A0
void CText::LoadMissionPackText() {
    return plugin::CallMethod<0x69F9A0, CText*>(this);
}

// Returns text pointer by GXT key
// 0x6A0050
char* CText::Get(const char* key) {
    if (key[0] && key[0] != ' ') {
        bool found = false;

        char* str = m_MainKeyArray.Search(key, &found);
        if (found) {
            return str;
        }

        // check mission keys block if no entry found yet
        if ((CGame::bMissionPackGame || m_bIsMissionTextOffsetsLoaded) && m_bIsMissionPackLoaded) {
            str = m_MissionKeyArray.Search(key, &found);
            if (found) {
                return str;
            }
        }
    }

    char buf[32];
    sprintf(buf, "");
    AsciiToGxtChar(buf, GxtErrorString);
    return GxtErrorString;
}

// Writes loaded mission text into outStr
// 0x69FBD0
void CText::GetNameOfLoadedMissionText(char* outStr) {
    strcpy(outStr, m_szMissionName);
}

// 0x69F940
bool CText::ReadChunkHeader(ChunkHeader* header, FILESTREAM file, uint32* offset, uint8 nSkipBytes) {
    return plugin::CallMethodAndReturn<bool, 0x69F940, CText*, ChunkHeader*, FILESTREAM, uint32*, uint8>(this, header, file, offset, nSkipBytes);

#ifdef USE_ORIGINAL_CODE
    // Taken from re3. That not same as original, but do same thing
    char* _header = (char*)header;
    for (int32 i = 0; i < sizeof(ChunkHeader); i++) {
        CFileMgr::Read(file, &_header[i], 1);
        (*offset)++;
    }
    delete _header;
    return true;
#else
    // re3: original code loops 8 times to read 1 byte with CFileMgr::Read, that's retarded
    CFileMgr::Read(file, header, sizeof(ChunkHeader));
    *offset += sizeof(ChunkHeader);

    return true;
#endif
}

// unused
// 0x69F750
char CText::GetUpperCase(char unk) {
    switch (m_nLangCode) {
    case 'e': // english
    if (unk > 0x7A)
        return unk;

    return unk - 0x20;

    case 'g': // german
    case 'i': // italian
    case 's': // spanish
    if (unk <= 0x7A)
        return unk - 0x20;

    if (unk > 0xFF)
        return unk;

    return FrenchUpperCaseTable[unk];

    case 'f':
        if (unk <= 0x7A)
            return unk - 0x20;

        if (unk > 0xFF)
            return unk;

        return FrenchUpperCaseTable[unk - 0x80];
    }

    return unk;
}

CText* CText::Constructor() {
    this->CText::CText();
    return this;
}

CText* CText::Destructor() {
    this->CText::~CText();
    return this;
}
