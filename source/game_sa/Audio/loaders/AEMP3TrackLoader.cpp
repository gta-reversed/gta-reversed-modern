#include "StdInc.h"
#include "AEMP3TrackLoader.h"
#include "app.h"
#include "FileMgr.h"
#include "MemoryMgr.h"

void AEMP3TrackLoader::InjectHooks() {
    // TODO
}

// 0x4E0930
AEMP3TrackLoader::AEMP3TrackLoader() {
    m_bInitialised = false;
    m_pszDvdDrivePath = nullptr;
}

// 0x4E0940
AEMP3TrackLoader::~AEMP3TrackLoader() {
    if (m_bInitialised) {
        CMemoryMgr::Free(m_paTrackLookups);
        CMemoryMgr::Free(m_paStreamPacks);
    }

    if (m_pszDvdDrivePath) {
        delete m_pszDvdDrivePath;
    }
}

// 0x4E0C50
bool AEMP3TrackLoader::Initialise() {
    if (!LoadStreamPackTable() || !LoadTrackLookupTable())
        return false;

    m_bStreamingFromDVD = false;

    // NOTSA: Originally used a heap allocated string and strcpy/strcat to make paths.

    // Firstly try loading locally.
    const auto localPath = std::format("AUDIO\\STREAMS\\{}", m_paStreamPacks[0].m_szName);
    if (auto file = CFileMgr::OpenFile(localPath.c_str(), "r")) {
        m_bInitialised = true;
        m_bStreamingFromDVD = false;

        CFileMgr::CloseFile(file);
        return true;
    }

    // Try loading from a DVD.    
    return IsCurrentAudioStreamAvailable();
}

// 0x4E0970
bool AEMP3TrackLoader::LoadStreamPackTable(void) {
    // NOTSA: Originally Win32 file API was used.
    auto* fp = fopen("AUDIO\\CONFIG\\STRMPAKS.DAT", "r");
    if (!fp) {
        // Win32 API creates a file if it doesn't exists, and reads 0 bytes.
        fp = fopen("AUDIO\\CONFIG\\STRMPAKS.DAT", "w");
        fclose(fp);

        m_paStreamPacks = (StreamPack*)CMemoryMgr::Malloc(0); // This is stupid?
        m_nStreamPackCount = 0;
        return false;
    }

    // Get file size.
    fseek(fp, 0, SEEK_END);
    const auto size = ftell(fp);
    const auto numPacks = size / sizeof(StreamPack);
    rewind(fp);

    m_paStreamPacks = (StreamPack*)CMemoryMgr::Malloc(size);
    m_nStreamPackCount = numPacks;

    // NOTE: Win32 API outputs number of bytes read, most likely checking is unnecessary.
    fread(m_paStreamPacks, sizeof(StreamPack), numPacks, fp);

    fclose(fp);
    return true;
}

// 0x4E09F0
bool AEMP3TrackLoader::LoadTrackLookupTable(void) {
    // NOTSA: Originally Win32 file API was used.
    auto* fp = fopen("AUDIO\\CONFIG\\TRAKLKUP.DAT", "r");
    if (!fp) {
        // Win32 API creates a file if it doesn't exists, and reads 0 bytes.
        fp = fopen("AUDIO\\CONFIG\\TRAKLKUP.DAT", "w");
        fclose(fp);

        m_paTrackLookups = (tTrackLookup*)CMemoryMgr::Malloc(0); // This is stupid?
        m_nTrackCount = 0;
        return false;
    }

    // Get file size.
    fseek(fp, 0, SEEK_END);
    const auto size = ftell(fp);
    const auto numPacks = size / sizeof(tTrackLookup);
    rewind(fp);

    m_paTrackLookups = (tTrackLookup*)CMemoryMgr::Malloc(size);
    m_nTrackCount = numPacks;

    // NOTE: Win32 API outputs number of bytes read, most likely checking is unnecessary.
    fread(m_paTrackLookups, sizeof(tTrackLookup), numPacks, fp);

    fclose(fp);
    return true;
}

// 0x4E0A70
tTrackInfo* AEMP3TrackLoader::GetTrackInfo(uint32 trackId) {
    if (trackId >= m_nTrackCount)
        return nullptr;

    const auto packId = m_paTrackLookups[trackId].m_nbPackId;
    if (packId > m_nStreamPackCount)
        return nullptr;

    const auto length = [&] {
        if (m_bStreamingFromDVD) {
            return strlen(m_pszDvdDrivePath) + strlen(m_paStreamPacks[packId].m_szName) + 21;
        }
        return strlen(m_paStreamPacks[packId].m_szName) + 21;
    }();

    char* path = new char[length]; // owned by to be ctor'd CAEDataStream.
    strcpy_s(path, length,
        std::format("{}\\{}",
            !m_bStreamingFromDVD ? "AUDIO\\STREAMS\\" : std::string{m_pszDvdDrivePath} + "AUDIO\\STREAMS\\",
            m_paStreamPacks[packId].m_szName
        ).c_str()
    );

    auto* stream = new CAEDataStream(
        trackId,
        path,
        m_paTrackLookups[trackId].m_nOffset,
        m_paTrackLookups[trackId].m_nSize,
        true
    );
    auto* trackInfo = new tTrackInfo;

    stream->Initialise();
    stream->FillBuffer(trackInfo, sizeof(tTrackInfo));
    delete stream;

    return trackInfo;
}

// 0x4E0BD0
bool AEMP3TrackLoader::IsCurrentAudioStreamAvailable() {
    if (m_pszDvdDrivePath = getDvdGamePath()) {
        const auto dvdPath = std::format("{}\\AUDIO\\STREAMS\\{}", getDvdGamePath(), m_paStreamPacks[0].m_szName);
        if (auto file = CFileMgr::OpenFile(dvdPath.c_str(), "r")) {
            m_bInitialised = true;
            m_bStreamingFromDVD = true;

            CFileMgr::CloseFile(file);
        }
    } else {
        m_bStreamingFromDVD = false;
    }

    return m_bStreamingFromDVD;
}
