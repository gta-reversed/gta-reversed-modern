#include "StdInc.h" // TODO: Remove

#include "CAEStreamingDecoder.h"

CAEStreamingDecoder::CAEStreamingDecoder(CAEDataStream* dataStream)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using Constructor = void(__thiscall *)(CAEStreamingDecoder*, CAEDataStream*);
    ((Constructor) (0x4f2810))(this, dataStream);
#else
    this->dataStream = dataStream;
    if (dataStream)
        dataStream->Initialise();
#endif
}

#ifdef USE_DEFAULT_FUNCTIONS
void CAEStreamingDecoder::operator delete(void* mem)
{
    ((void(__thiscall *)(void*, int)) (0x4f2860))(mem, 1);
}
#endif

CAEStreamingDecoder::~CAEStreamingDecoder()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CAEStreamingDecoder*)) (0x4f2830))(this);
#else
    // The game checks if dataStream is nullptr, but
    // deleting null pointer is perfectly safe.
    delete dataStream;
    dataStream = nullptr;
#endif
}

CAEStreamingDecoder *CAEStreamingDecoder::ctor(CAEDataStream *dataStream)
{
    this->CAEStreamingDecoder::CAEStreamingDecoder(dataStream);
    return this;
}

void CAEStreamingDecoder::dtor()
{
    this->CAEStreamingDecoder::~CAEStreamingDecoder();
}

void CAEStreamingDecoder::InjectHooks()
{
#ifndef USE_DEFAULT_FUNCTIONS
    HookInstall(0x4f2810, &CAEStreamingDecoder::ctor);
    HookInstall(0x4f2830, &CAEStreamingDecoder::dtor);
#endif
}
