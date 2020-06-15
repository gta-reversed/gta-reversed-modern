#include "StdInc.h" // TODO: Remove

#include "common.h"

#include "CAEDataStream.h"
#include "CAEStreamTransformer.h"
#include "CFileMgr.h"

CAEDataStream::CAEDataStream(std::int32_t trackID, char* filename, std::uint32_t startPosition, std::uint32_t length, int encrypted)
: fileHandle(nullptr)
, filename(filename)
, isOpen(false)
, currentPosition(0)
, startPosition(startPosition)
, length(length)
, trackID(trackID)
, isEncrypted(encrypted)
, refCount(1)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using Constructor = void(__thiscall*)(CAEDataStream*, std::int32_t, char*, std::uint32_t, std::uint32_t, int);
    ((Constructor) (0x4dc620))(this, trackID, filename, startPosition, length, encrypted);
#endif
}

CAEDataStream::~CAEDataStream()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CAEDataStream*)) (0x4dc490))(this);
#else
    Close();

    if (filename)
    {
        delete[] filename;
        filename = nullptr;
    }
#endif
}

HRESULT CAEDataStream::QueryInterface(REFIID riid, void** objout)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using QIFunc = HRESULT(__stdcall *)(CAEDataStream*, REFIID, void**);
    return ((QIFunc) (0x4dc410))(this, riid, objout);
#else
    // MikuAuahDark: Despite having QueryInterface implemented,
    // I don't think CAEDataStream is meant to be QueryInterface'd.
    // See CAEDataStream::Release
    if (riid == IID_IUnknown || riid == IID_IStream)
    {
        AddRef();
        *objout = this;
        return S_OK;
    }

    return E_NOINTERFACE;
#endif
}

ULONG CAEDataStream::AddRef()
{
#ifdef USE_DEFAULT_FUNCTIONS
    using AddRefFunc = HRESULT(__stdcall *)(CAEDataStream*);
    return ((AddRefFunc) (0x4dc460))(this);
#else
    return ++refCount;
#endif
}

ULONG CAEDataStream::Release()
{
#ifdef USE_DEFAULT_FUNCTIONS
    using ReleaseFunc = HRESULT(__stdcall *)(CAEDataStream*);
    return ((ReleaseFunc) (0x4dc5b0))(this);
#else
    if (--refCount == 0)
    {
        delete this;
        return 0;
    }

    // MikuAuahDark: I think CAEDataStream isn't mean to be
    // QueryInterface'd? 0x4dc608 clearly says "mov eax, 0xbad"
    return 0xbad;
#endif
}

HRESULT CAEDataStream::Read(void* dest, ULONG size, ULONG* readed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using ReadFunc = HRESULT(__stdcall *)(CAEDataStream*, void*, ULONG, ULONG*);
    return ((ReadFunc) (0x4dc320))(this, dest, size, readed);
#else
    *readed = static_cast<ULONG> (FillBuffer(dest, size));
    return S_OK;
#endif
}

HRESULT CAEDataStream::Write(const void* src, ULONG size, ULONG* written)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using WriteFunc = HRESULT(__stdcall *)(CAEDataStream*, const void*, ULONG, ULONG*);
    return ((WriteFunc) 0x4dc4d0)(this, src, size, written);
#else
    return E_NOTIMPL;
#endif
}

HRESULT CAEDataStream::Seek(LARGE_INTEGER offset, DWORD whence, ULARGE_INTEGER* newOffset)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using SeekFunc = HRESULT(__stdcall *)(CAEDataStream*, LARGE_INTEGER, DWORD, ULARGE_INTEGER*);
    return ((SeekFunc) (0x4dc340))(this, offset, whence, newOffset);
#else
    // C-style cast is not a good idea here
    // but I can't figure out which cast is best to preserve
    // the sign-bit of LARGE_INTEGER
    if (isOpen == false)
        return E_INVALIDARG;

    unsigned long pos = Seek((long) offset.QuadPart, static_cast<int> (whence));
    if (newOffset)
        newOffset->QuadPart = pos;

    return S_OK;
#endif
}

HRESULT CAEDataStream::SetSize(ULARGE_INTEGER newsize)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using SetSizeFunc = HRESULT(__stdcall *)(CAEDataStream*, ULARGE_INTEGER);
    return ((SetSizeFunc) 0x4dc4e0)(this, newsize);
#else
    return E_NOTIMPL;
#endif
}

HRESULT CAEDataStream::CopyTo(IStream* target, ULARGE_INTEGER size, ULARGE_INTEGER* readed, ULARGE_INTEGER* written)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using CopyToFunc = HRESULT(__stdcall *)(CAEDataStream*, IStream*, ULARGE_INTEGER, ULARGE_INTEGER*, ULARGE_INTEGER*);
    return ((WriteFunc) 0x4dc4f0)(this, target, size, readed, written);
#else
    return E_NOTIMPL;
#endif
}

HRESULT CAEDataStream::Commit(DWORD flags)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using CommitFunc = HRESULT(__stdcall *)(CAEDataStream*, DWORD);
    return ((CommitFunc) 0x4dc500)(this, flags);
#else
    return E_NOTIMPL;
#endif
}

HRESULT CAEDataStream::Revert()
{
#ifdef USE_DEFAULT_FUNCTIONS
    using RevertFunc = HRESULT(__stdcall *)(CAEDataStream*);
    return ((RevertFunc) 0x4dc510)(this);
#else
    return E_NOTIMPL;
#endif
}

HRESULT CAEDataStream::LockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, DWORD type)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using LRFunc = HRESULT(__stdcall *)(CAEDataStream*, ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
    return ((LRFunc) 0x4dc520)(this, offset, size, type);
#else
    return E_NOTIMPL;
#endif
}

HRESULT CAEDataStream::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using URFunc = HRESULT(__stdcall *)(CAEDataStream*, ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
    return ((URFunc) 0x4dc530)(this, libOffset, cb, dwLockType);
#else
    return E_NOTIMPL;
#endif
}

HRESULT CAEDataStream::Stat(STATSTG* statout, DWORD flags)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using StatFunc = HRESULT(__stdcall *)(CAEDataStream*, STATSTG*, DWORD);
    return ((StatFunc) (0x4dc3a0))(this, statout, flags);
#else
    if (isOpen == false || statout == nullptr || flags != STATFLAG_NONAME)
        return E_INVALIDARG;

    DWORD fileSize = static_cast<DWORD> (CFileMgr::GetFileLength(fileHandle));
    memset(statout, 0, sizeof(STATSTG));
    statout->cbSize.LowPart = fileSize;
    statout->type = STGTY_STREAM;
    return S_OK;
#endif
}

HRESULT CAEDataStream::Clone(IStream** target)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using CloneFunc = HRESULT(__stdcall *)(CAEDataStream*, IStream**);
    return ((CloneFunc) 0x4dc540)(this, target);
#else
    return E_NOTIMPL;
#endif
}

size_t CAEDataStream::FillBuffer(void* dest, size_t size)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using FillFunc = int(__thiscall *)(CAEDataStream*, void*, size_t);
    return ((FillFunc) (0x4dc1c0))(this, dest, size);
#else
    if (isOpen == false)
        return 0;

    size_t sizeToRead = static_cast<size_t> ((currentPosition - length) - startPosition);
    if (size < sizeToRead)
        sizeToRead = size;

    size = CFileMgr::Read(fileHandle, dest, sizeToRead);

    if (isEncrypted)
        CAEStreamTransformer::instance.TransformBuffer(dest, size, currentPosition);

    currentPosition += static_cast<std::uint32_t> (size);
    return size;
#endif
}

std::uint32_t CAEDataStream::GetCurrentPosition()
{
#ifdef USE_DEFAULT_FUNCTIONS
    using TellFunc = unsigned long(__thiscall *)(CAEDataStream*);
    return ((TellFunc) (0x4dc230))(this);
#else
    std::uint32_t pos = static_cast<std::uint32_t> (CFileMgr::Tell(fileHandle));
    return pos - startPosition;
#endif
}

std::uint32_t CAEDataStream::Seek(long offset, int whence)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using SeekFunc = unsigned long(__thiscall *)(CAEDataStream*, long, int);
    return ((SeekFunc) 0x4dc250)(this, offset, whence);
#else
    if (isOpen == false)
        return std::uint32_t(-1);

    if (whence == SEEK_SET)
        offset += startPosition;
    else if (whence == SEEK_END)
    {                      
        offset = (length + startPosition) - offset;
        whence = SEEK_SET;
    }

    CFileMgr::Seek(fileHandle, offset, whence);

    currentPosition = static_cast<std::uint32_t> (CFileMgr::Tell(fileHandle));
    return currentPosition - startPosition;
#endif
}

bool CAEDataStream::Close()
{
    if (isOpen)
    {
        isOpen = false;
        return CFileMgr::CloseFile(fileHandle);
    }

    return true;
}

bool CAEDataStream::Initialise()
{
#ifdef USE_DEFAULT_FUNCTIONS
    using InitFunc = bool(__thiscall*)(CAEDataStream*);
    return ((InitFunc) (0x4dc2b0))(this);
#else
    if (isOpen)
        return true;

    // MikuAuahDark: Rewrite it to use CFileMgr
    CFileMgr::SetDir("");
    fileHandle = CFileMgr::OpenFile(filename, "rb");

    if (fileHandle)
    {
        CFileMgr::Seek(fileHandle, startPosition, SEEK_SET);

        currentPosition = static_cast<std::uint32_t> (CFileMgr::Tell(fileHandle));
        length = length == 0 ? CFileMgr::GetFileLength(fileHandle) : length;
        isOpen = true;
    }

    return fileHandle != nullptr;
#endif
}

CAEDataStream *CAEDataStream::ctor(std::int32_t trackID, char *filename, std::uint32_t startPosition, std::uint32_t length, int encrypted)
{
    this->CAEDataStream::CAEDataStream(trackID, filename, startPosition, length, encrypted);
    return this;
}

void CAEDataStream::dtor()
{
    this->CAEDataStream::~CAEDataStream();
}

void CAEDataStream::InjectHooks()
{
#ifndef USE_DEFAULT_FUNCTIONS
    HookInstall(0x4dc1c0, &CAEDataStream::FillBuffer);
    HookInstall(0x4dc230, &CAEDataStream::GetCurrentPosition);
    HookInstall(0x4dc250, (std::uint32_t(CAEDataStream::*)(long offset, int whence)) &CAEDataStream::Seek);
    HookInstall(0x4dc2b0, &CAEDataStream::Initialise);
    HookInstall(0x4dc320, &CAEDataStream::Read);
    HookInstall(0x4dc340, (HRESULT(__stdcall CAEDataStream::*)(LARGE_INTEGER, DWORD, ULARGE_INTEGER*)) &CAEDataStream::Seek);
    HookInstall(0x4dc3a0, &CAEDataStream::Stat);
    HookInstall(0x4dc410, &CAEDataStream::QueryInterface);
    HookInstall(0x4dc460, &CAEDataStream::AddRef);
    HookInstall(0x4dc490, &CAEDataStream::dtor);
    HookInstall(0x4dc4d0, &CAEDataStream::Write);
    HookInstall(0x4dc4e0, &CAEDataStream::SetSize);
    HookInstall(0x4dc4f0, &CAEDataStream::CopyTo);
    HookInstall(0x4dc500, &CAEDataStream::Commit);
    HookInstall(0x4dc510, &CAEDataStream::Revert);
    HookInstall(0x4dc520, &CAEDataStream::LockRegion);
    HookInstall(0x4dc530, &CAEDataStream::UnlockRegion);
    HookInstall(0x4dc540, &CAEDataStream::Clone);
    HookInstall(0x4dc5b0, &CAEDataStream::Release);
    HookInstall(0x4dc620, &CAEDataStream::ctor);

    CAEStreamTransformer::InjectHooks();
#endif
}
