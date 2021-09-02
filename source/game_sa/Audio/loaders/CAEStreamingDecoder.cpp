#include "StdInc.h" // TODO: Remove

#include "CAEStreamingDecoder.h"

// 0x4f2810
CAEStreamingDecoder::CAEStreamingDecoder(CAEDataStream* dataStream) {
    m_dataStream = dataStream;
    if (dataStream)
        dataStream->Initialise();
}

#ifdef USE_DEFAULT_FUNCTIONS
void CAEStreamingDecoder::operator delete(void* mem) {
    ((void(__thiscall*)(void*, int32))(0x4f2860))(mem, 1);
}
#endif

// 0x4f2830
CAEStreamingDecoder::~CAEStreamingDecoder() {
    // The game checks if dataStream is nullptr, but
    // deleting null pointer is perfectly safe.
    delete m_dataStream;
    m_dataStream = nullptr;
}

void CAEStreamingDecoder::InjectHooks() {
    ReversibleHooks::Install("CAEStreamingDecoder", "CAEStreamingDecoder", 0x4f2810, &CAEStreamingDecoder::Constructor);
    ReversibleHooks::Install("CAEStreamingDecoder", "~CAEStreamingDecoder", 0x4f2830, &CAEStreamingDecoder::Destructor);
}

CAEStreamingDecoder* CAEStreamingDecoder::Constructor(CAEDataStream* dataStream) {
    this->CAEStreamingDecoder::CAEStreamingDecoder(dataStream);
    return this;
}

CAEStreamingDecoder* CAEStreamingDecoder::Destructor() {
    this->CAEStreamingDecoder::~CAEStreamingDecoder();
    return this;
}