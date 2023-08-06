#pragma once

#ifdef USERTRACK_FLAC_SUPPORT
#include "AEWaveDecoder.h"
#include "FLAC/stream_decoder.h"

// NOTSA
struct FlacMetadata {
    uint64 totalSamples{};
    uint32 channels{};
    uint32 bps{};
    uint32 sampleRate{};
};

class CAEFlacDecoder : public CAEWaveDecoder {
public:
    CAEFlacDecoder(CAEDataStream* dataStream) : CAEWaveDecoder(dataStream) {}
    virtual ~CAEFlacDecoder();

    static bool InitLibrary();
    bool Initialise() override;

    // NOTSA
    auto& GetMetadata() {
        return m_Metadata;
    }
    auto* GetDataStream() {
        return m_dataStream;
    }
    void AssignWaveFile(FILESTREAM fp, char* filename, size_t length) {
        m_WaveFile = fp;
        m_WaveFileNameHeap = filename;
        m_WaveFileLength = length;
    }
    FILESTREAM GetWaveFile() {
        return m_WaveFile;
    }

private:
    FILESTREAM m_WaveFile{};
    char* m_WaveFileNameHeap{};
    std::string m_WaveFileName{};
    size_t m_WaveFileLength{};
    FlacMetadata m_Metadata{};
};
#endif
