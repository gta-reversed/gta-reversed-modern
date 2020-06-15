#pragma once

#include <atomic>
#include <cstdint>

#include <ObjIdl.h>

#include "PluginBase.h"

class CAEDataStream: public IStream
{
public:
    CAEDataStream(std::int32_t trackID, char *filename, std::uint32_t startPosition, std::uint32_t length, int encrypted);
    ~CAEDataStream();

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** objout) override;
    ULONG STDMETHODCALLTYPE AddRef() override;
    ULONG STDMETHODCALLTYPE Release() override;
    HRESULT STDMETHODCALLTYPE Read(void* dest, ULONG size, ULONG* readed) override;
    HRESULT STDMETHODCALLTYPE Write(const void* src, ULONG size, ULONG* written) override;
    HRESULT STDMETHODCALLTYPE Seek(LARGE_INTEGER offset, DWORD whence, ULARGE_INTEGER *newOffset) override;
    HRESULT STDMETHODCALLTYPE SetSize(ULARGE_INTEGER newsize) override;
    HRESULT STDMETHODCALLTYPE CopyTo(IStream *target, ULARGE_INTEGER size, ULARGE_INTEGER *readed, ULARGE_INTEGER *written) override;
    HRESULT STDMETHODCALLTYPE Commit(DWORD flags) override;
    HRESULT STDMETHODCALLTYPE Revert() override;
    HRESULT STDMETHODCALLTYPE LockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, DWORD type) override;
    HRESULT STDMETHODCALLTYPE UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType) override;
    HRESULT STDMETHODCALLTYPE Stat(STATSTG *statout, DWORD flags) override;
    HRESULT STDMETHODCALLTYPE Clone(IStream **target) override;

    size_t FillBuffer(void* dest, size_t size);
    std::uint32_t GetCurrentPosition();
    std::uint32_t Seek(long offset, int whence);
    bool Close();
    bool Initialise();

public:
    FILE *fileHandle;
    char *filename;
    bool isOpen;
    std::uint32_t currentPosition;
    std::uint32_t startPosition;
    std::uint32_t length;
    std::uint32_t trackID;
    bool isEncrypted;
    std::atomic<ULONG> refCount;

private:
    friend void InjectHooksMain(void);

    CAEDataStream *ctor(std::int32_t trackID, char* filename, std::uint32_t startPosition, std::uint32_t length, int encrypted);
    void dtor();

    static void InjectHooks();
};

VALIDATE_SIZE(CAEDataStream, 0x28);
