#pragma once
#include <span>
#include "FileMgr.h"

namespace notsa {
// RAII-wrapper for CFileMgr files.
class File {
    FILESTREAM m_file{};
public:
    File(const char* path, const char* mode) :
        m_file(CFileMgr::OpenFile(path, mode))
    {}

    ~File()
    {
        if (m_file)
            CloseFile();
    }

    operator bool() const { return m_file != nullptr; }

    size_t Read(void* buf, size_t size) { return CFileMgr::Read(m_file, buf, size); }
    size_t Write(const void* buf, size_t size) { return CFileMgr::Write(m_file, buf, size); }

    // TODO: template<typaneme T> void Read(T& out);
    // TODO: template<typaneme T> void Write(const T& out);

    bool Seek(long offset, int32 origin) { return CFileMgr::Seek(m_file, offset, origin); }
    bool ReadLine(char* str, int32 num) { return CFileMgr::ReadLine(m_file, str, num); }
    int32 CloseFile() { return CFileMgr::CloseFile(std::exchange(m_file, nullptr)); }
    int32 GetTotalSize() const { return CFileMgr::GetTotalSize(m_file); }
    int32 Tell() const { return CFileMgr::Tell(m_file); }
    bool GetErrorReadWrite() const { return CFileMgr::GetErrorReadWrite(m_file); }
    void SeekNextLine() { return CFileMgr::SeekNextLine(m_file); }
};
};
