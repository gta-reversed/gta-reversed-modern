#pragma once

#include <atomic>
#include <cstdint>

#include <ObjIdl.h>


class CAEDataStream: public IStream {
public:
    FILESTREAM m_pFileHandle;
    char*      m_pszFilename;
    bool       m_bIsOpen;
    uint32_t   m_nCurrentPosition;
    uint32_t   m_nStartPosition;
    uint32_t   m_nLength;
    uint32_t   m_nTrackId;
    bool       m_bIsEncrypted;
    uint32_t   m_lRefCount;
    
public:
    CAEDataStream(int32_t trackId, char* filename, uint32_t startPosition, uint32_t length, bool encrypted);
    ~CAEDataStream();

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** objout) override;
    ULONG STDMETHODCALLTYPE AddRef() override;
    ULONG STDMETHODCALLTYPE Release() override;
    HRESULT STDMETHODCALLTYPE Read(void* dest, ULONG size, ULONG* readed) override;
    HRESULT STDMETHODCALLTYPE Write(const void* src, ULONG size, ULONG* written) override;
    HRESULT STDMETHODCALLTYPE Seek(LARGE_INTEGER offset, DWORD whence, ULARGE_INTEGER* newOffset) override;
    HRESULT STDMETHODCALLTYPE SetSize(ULARGE_INTEGER newSize) override;
    HRESULT STDMETHODCALLTYPE CopyTo(IStream* target, ULARGE_INTEGER size, ULARGE_INTEGER* readed, ULARGE_INTEGER* written) override;
    HRESULT STDMETHODCALLTYPE Commit(DWORD flags) override;
    HRESULT STDMETHODCALLTYPE Revert() override;
    HRESULT STDMETHODCALLTYPE LockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, DWORD type) override;
    HRESULT STDMETHODCALLTYPE UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType) override;
    HRESULT STDMETHODCALLTYPE Stat(STATSTG* statout, DWORD flags) override;
    HRESULT STDMETHODCALLTYPE Clone(IStream** target) override;

    size_t FillBuffer(void* dest, size_t size);
    uint32_t GetCurrentPosition();
    uint32_t Seek(long offset, int32_t whence);
    bool Close();
    bool Initialise();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEDataStream* ctor(int32_t trackID, char* filename, uint32_t startPosition, uint32_t length, int32_t encrypted);
    void dtor();
};

VALIDATE_SIZE(CAEDataStream, 0x28);
