#pragma once

#include "AEStreamingDecoder.h"
#include "FLAC/stream_decoder.h"
// NOTSA

struct FlacMetadata {
    uint64 totalSamples{};
    uint32 channels{};
    uint32 bps{};
    uint32 sampleRate{};
};

class CAEFlacDecoder : public CAEStreamingDecoder {
public:
    CAEFlacDecoder(CAEDataStream* dataStream) : CAEStreamingDecoder(dataStream) {}
    virtual ~CAEFlacDecoder();

#ifdef USERTRACK_FLAC_SUPPORT
    static bool InitLibrary();
    bool   Initialise() override;
#else
    bool Initialise() override {
        return false;
    }
    static bool InitLibrary() {
        return false;
    }
#endif
    size_t FillBuffer(void* dest, size_t size) override;
    long   GetStreamLengthMs() override;
    long   GetStreamPlayTimeMs() override;
    void   SetCursor(unsigned long pos) override;
    int32  GetSampleRate() override;
    int32  GetStreamID() override;

    // NOTSA
    auto* GetDataStream() { return m_dataStream; }
    auto& GetMetadata() { return m_metadata; }
    auto* GetWriteBuffer() { return m_CurrentWriteBuffer; }

private:
    FLAC__StreamDecoder* m_FlacStreamDecoder{};
    uint8* m_CurrentWriteBuffer{};
    FlacMetadata m_metadata{};
    bool m_bInitialized{};
};
