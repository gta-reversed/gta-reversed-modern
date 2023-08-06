#pragma once

#ifdef USERTRACK_FLAC_SUPPORT
#include "AEStreamingDecoder.h"
#include "FLAC/stream_decoder.h"

// NOTSA
struct FlacMetadata {
    uint64 totalSamples{};
    uint32 channels{};
    uint32 bps{};
    uint32 sampleRate{};
};

struct FlacFillBufferInfo {
    int16* writeBuffer{};
    size_t maxBytes{};
    size_t writeWrittenBytes{};
    int16* leftoverBuffer{};
    size_t leftoverWrittenBytes{};
};

class CAEFlacDecoder : public CAEStreamingDecoder {
public:
    static constexpr auto LEFTOVER_SAMPLES_SIZE = 80'000u;

    CAEFlacDecoder(CAEDataStream* dataStream) : CAEStreamingDecoder(dataStream) {}
    virtual ~CAEFlacDecoder();

    static bool InitLibrary();
    bool Initialise() override;

    size_t FillBuffer(void* dest, size_t size) override;
    long GetStreamLengthMs() override;
    long GetStreamPlayTimeMs() override;
    void SetCursor(unsigned long pos) override;
    int32 GetSampleRate() override;
    int32 GetStreamID() override;

    // NOTSA
    auto* GetDataStream() {
        return m_dataStream;
    }
    auto& GetMetadata() {
        return m_metadata;
    }
    auto& GetFillBufferInfo() {
        return m_fillBufferInfo;
    }

private:
    FLAC__StreamDecoder* m_FlacStreamDecoder{};
    FlacFillBufferInfo m_fillBufferInfo{};
    FlacMetadata m_metadata{};
    bool m_bInitialized{};

    int16* m_bufferLeftoverSamples{};
    size_t m_leftoverSamplesSize{};
};
#endif
