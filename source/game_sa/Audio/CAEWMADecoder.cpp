#include "StdInc.h" // TODO: Remove

#include "CAEWMADecoder.h"

#include "CMemoryMgr.h"

// WMA functions
HRESULT(__stdcall *&CAEWMADecoder::WMCreateSyncReader)(IUnknown*, DWORD, IWMSyncReader**) = *(HRESULT(__stdcall **)(IUnknown*, DWORD, IWMSyncReader**)) 0xb6bad8;
HMODULE &CAEWMADecoder::wmvCoreModule = *(HMODULE *) 0xb6bad4;

CAEWMADecoder::CAEWMADecoder(CAEDataStream* dataStream)
: CAEStreamingDecoder(dataStream)
, initialized(false)
, tempBufferUsed(0)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using Constructor = void(__thiscall *)(CAEWMADecoder*, CAEDataStream*);
    ((Constructor) 0x502720)(this, dataStream);
#endif
}

CAEWMADecoder::~CAEWMADecoder()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CAEWMADecoder*)) 0x502760)(this);
#else
    if (initialized)
    {
        syncReader->Close();
        syncReader->Release();
        initialized = false;
    }

    CoUninitialize();
#endif
}

bool CAEWMADecoder::Initialise()
{
#ifdef USE_DEFAULT_FUNCTIONS
    using InitFunc = bool(__thiscall *)(CAEWMADecoder*);
    return ((InitFunc) 0x502c60)(this);
#else
    WMT_STREAM_SELECTION activateStream = WMT_ON;

    CoInitialize(nullptr);

    if (CAEWMADecoder::WMCreateSyncReader)
    {
        if (SUCCEEDED(CAEWMADecoder::WMCreateSyncReader(nullptr, 0, &syncReader)))
        {
            if (SUCCEEDED(syncReader->OpenStream(dataStream)))
            {
                IWMProfile *profile;
                
                if (SUCCEEDED(syncReader->QueryInterface(IID_IWMProfile, (void **) &profile)))
                {
                    HRESULT selectResult = SelectStreamIndex(profile);

                    if (profile)
                    {
                        profile->Release();
                        profile = nullptr;
                    }

                    if (SUCCEEDED(selectResult))
                    {
                        DWORD outputNumber;
                        IWMOutputMediaProps *mediaProps;

                        syncReader->SetStreamsSelected(1, &streamNumber, &activateStream);
                        syncReader->SetReadStreamSamples(streamNumber, FALSE);
                        syncReader->SetRange(0ULL, 0LL);
                        syncReader->GetOutputNumberForStream(streamNumber, &outputNumber);
                        
                        if (SUCCEEDED(syncReader->GetOutputProps(outputNumber, &mediaProps)))
                        {
                            DWORD mediaTypeSize = 0;
                            mediaProps->GetMediaType(nullptr, &mediaTypeSize);
                            
                            WM_MEDIA_TYPE *mediaTypeBase = (WM_MEDIA_TYPE *) CMemoryMgr::Malloc(mediaTypeSize);
                            mediaProps->GetMediaType(mediaTypeBase, &mediaTypeSize);
                            WAVEFORMATEX *mediaMetadata = (WAVEFORMATEX *) mediaTypeBase->pbFormat;

                            if (mediaMetadata && mediaMetadata->nChannels == 2 && mediaMetadata->wBitsPerSample == 16)
                            {
                                IWMHeaderInfo3 *headerInfo;
                                sampleRate = mediaMetadata->nSamplesPerSec;

                                if (SUCCEEDED(syncReader->QueryInterface(IID_IWMHeaderInfo3, (void **) &headerInfo)))
                                {
                                    WORD count;
                                    headerInfo->GetAttributeIndices(0, L"Duration", nullptr, nullptr, &count);

                                    WORD *indices = new WORD[count];
                                    headerInfo->GetAttributeIndices(0, L"Duration", nullptr, indices, &count);

                                    WORD dummyNameLen;
                                    DWORD dummyBufLen = 8;
                                    QWORD duration;
                                    WMT_ATTR_DATATYPE dataType;
                                    headerInfo->GetAttributeByIndexEx(
                                        0,
                                        indices[0],
                                        nullptr,
                                        &dummyNameLen,
                                        &dataType,
                                        nullptr,
                                        (BYTE*)&duration,
                                        &dummyBufLen
                                    );

                                    lengthMs = (long)(duration / 10000ULL);
                                    initialized = lengthMs >= 7000;

                                    delete[] indices;
                                    headerInfo->Release();
                                }
                            }

                            CMemoryMgr::Free(mediaTypeBase);
                            mediaProps->Release();
                        }
                    }
                }
            }
            else if (syncReader)
            {
                syncReader->Release();
                syncReader = nullptr;
            }
        }
    }

    return initialized;
#endif
}

size_t CAEWMADecoder::FillBuffer(void *dest, size_t size)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using ReadFunc = size_t(__thiscall *)(CAEWMADecoder*, void*, size_t);
    return ((ReadFunc) 0x5027d0)(this, dest, size);
#else
    char *buf = (char *) dest;
    size_t written = 0;

    if (tempBufferUsed > 0)
    {
        size_t sizeToCopy = tempBufferUsed > size ? size : tempBufferUsed;
        memcpy(buf, buffer, sizeToCopy);

        tempBufferUsed -= sizeToCopy;
        size -= sizeToCopy;
        buf += sizeToCopy;
        written += sizeToCopy;

        if (tempBufferUsed > 0)
            // Push buffer
            memmove(buffer, buffer + sizeToCopy, tempBufferUsed);
    }

    while (size > 0)
    {
        INSSBuffer *nssBuffer = nullptr;
        DWORD dummy1 = 0, dummy2 = 0;
        WORD stream = 0;

        if (FAILED(syncReader->GetNextSample(streamNumber, &nssBuffer, &sampleTime, &sampleDuration, &dummy1, &dummy2, &stream)))
            return written;

        if (stream == streamNumber)
        {
            BYTE *byteBuffer;
            DWORD bufferLen = 0;

            if (FAILED(nssBuffer->GetBufferAndLength(&byteBuffer, &bufferLen)))
            {
                nssBuffer->Release();
                return written;
            }

            size_t sizeToCopy = size > bufferLen ? bufferLen : size;
            memcpy(buf, byteBuffer, sizeToCopy);
            bufferLen -= sizeToCopy;
            size -= sizeToCopy;
            written += sizeToCopy;
            buf += sizeToCopy;

            if (size == 0)
            {
                // Store into temporary buffer
                size_t freeTempBufSize = TEMPBUFSIZE - tempBufferUsed;
                byteBuffer += sizeToCopy;
                sizeToCopy = bufferLen > freeTempBufSize ? freeTempBufSize : bufferLen;
                memcpy(buffer + tempBufferUsed, byteBuffer, sizeToCopy);
                tempBufferUsed += sizeToCopy;
            }
        }

        nssBuffer->Release();
    }

    return written;
#endif
}

long CAEWMADecoder::GetStreamLengthMs()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((long(__thiscall *)(CAEWMADecoder*)) 0x502ad0)(this);
#else
    if (initialized)
        return lengthMs;

    return -1;
#endif
}

long CAEWMADecoder::GetStreamPlayTimeMs()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((long(__thiscall *)(CAEWMADecoder*)) 0x502af0)(this);
#else
    if (initialized)
        return (long) ((sampleTime + sampleDuration) / 10000.0);

    return -1;
#endif
}

void CAEWMADecoder::SetCursor(unsigned long pos)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using SeekFunc = void(__thiscall *)(CAEWMADecoder*, unsigned long);
    ((SeekFunc) 0x502b50)(this, pos);
#else
    if (initialized)
        syncReader->SetRange(pos * 10000ULL, 0LL);
#endif
}

int CAEWMADecoder::GetSampleRate()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(__thiscall *)(CAEWMADecoder*)) 0x502ab0)(this);
#else
    if (initialized)
        return sampleRate;

    return -1;
#endif
}

int CAEWMADecoder::GetStreamID()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(__thiscall *)(CAEWMADecoder*)) 0x502750)(this);
#else
    return dataStream->m_nTrackId;
#endif
}

bool CAEWMADecoder::InitLibrary()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(*)()) 0x502b80)();
#else
    if (CAEWMADecoder::WMCreateSyncReader != nullptr)
        return true;

    wmvCoreModule = LoadLibraryA("wmvcore.dll");
    if (wmvCoreModule != nullptr)
    {
        using WMCreateSyncReaderFunc = HRESULT(__stdcall *)(IUnknown*, DWORD, IWMSyncReader**);
        CAEWMADecoder::WMCreateSyncReader = (WMCreateSyncReaderFunc) GetProcAddress(wmvCoreModule, "WMCreateSyncReader");

        if (CAEWMADecoder::WMCreateSyncReader)
        {
            IWMSyncReader *reader = nullptr;

            // MikuAuahDark: GTASA tests if WMCreateSyncReader actually works
            if (SUCCEEDED(WMCreateSyncReader(nullptr, 0, &reader)))
            {
                reader->Release();
                return true;
            }

            WMCreateSyncReader = nullptr;
        }

        FreeLibrary(wmvCoreModule);
        wmvCoreModule = nullptr;
    }

    return false;
#endif
}

void CAEWMADecoder::Shutdown()
{
    // Free WMV core
    if (CAEWMADecoder::WMCreateSyncReader)
    {
        FreeLibrary(wmvCoreModule);
        CAEWMADecoder::WMCreateSyncReader = nullptr;
        wmvCoreModule = nullptr;
    }
}

HRESULT CAEWMADecoder::SelectStreamIndex(IWMProfile *profile)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using SelectStreamFunc = HRESULT(__thiscall *)(CAEWMADecoder*, IWMProfile*);
    return ((SelectStreamFunc) 0x502990)(this, profile);
#else
    if (profile == nullptr)
        return E_INVALIDARG;

    DWORD streams = 0;
    if (SUCCEEDED(profile->GetStreamCount(&streams)))
    {
        IWMStreamConfig *streamConfig = nullptr;
        GUID streamGUID;

        streamNumber = 0;

        for (DWORD i = 0; i < streams; i++)
        {
            WORD index;

            if (FAILED(profile->GetStream(i, &streamConfig)))
                break;
            
            if (FAILED(streamConfig->GetStreamNumber(&index)))
                break;

            if (FAILED(streamConfig->GetStreamType(&streamGUID)))
                break;

            streamConfig->Release();
            streamConfig = nullptr;

            if (streamGUID == WMMEDIATYPE_Audio)
            {
                streamNumber = index;
                break;
            }
        }

        if (streamConfig)
        {
            streamConfig->Release();
            streamConfig = nullptr;
        }
    }

    if (streamNumber == 0)
        return E_INVALIDARG;

    return S_OK;
#endif
}

CAEWMADecoder *CAEWMADecoder::ctor(CAEDataStream *dataStream)
{
    this->CAEWMADecoder::CAEWMADecoder(dataStream);
    return this;
}

void CAEWMADecoder::dtor()
{
    this->CAEWMADecoder::~CAEWMADecoder();
}

void CAEWMADecoder::InjectHooks()
{
    ReversibleHooks::Install("CAEWMADecoder", "CAEWMADecoder", 0x502720, &CAEWMADecoder::ctor);
    ReversibleHooks::Install("CAEWMADecoder", "~CAEWMADecoder", 0x502760, &CAEWMADecoder::dtor);
    ReversibleHooks::Install("CAEWMADecoder", "Initialise", 0x502c60, &CAEWMADecoder::Initialise);
    ReversibleHooks::Install("CAEWMADecoder", "FillBuffer", 0x5027d0, &CAEWMADecoder::FillBuffer);
    ReversibleHooks::Install("CAEWMADecoder", "GetStreamLengthMs", 0x502ad0, &CAEWMADecoder::GetStreamLengthMs);
    ReversibleHooks::Install("CAEWMADecoder", "GetStreamPlayTimeMs", 0x502af0, &CAEWMADecoder::GetStreamPlayTimeMs);
    ReversibleHooks::Install("CAEWMADecoder", "SetCursor", 0x502b50, &CAEWMADecoder::SetCursor);
    ReversibleHooks::Install("CAEWMADecoder", "GetSampleRate", 0x502ab0, &CAEWMADecoder::GetSampleRate);
    ReversibleHooks::Install("CAEWMADecoder", "GetStreamID", 0x502750, &CAEWMADecoder::GetStreamID);
    ReversibleHooks::Install("CAEWMADecoder", "SelectStreamIndex", 0x502990, &CAEWMADecoder::SelectStreamIndex);
    ReversibleHooks::Install("CAEWMADecoder", "InitLibrary", 0x502b80, &CAEWMADecoder::InitLibrary);
}
