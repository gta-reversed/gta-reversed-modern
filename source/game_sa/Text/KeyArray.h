#pragma once

struct CKeyEntry {
    char*  string; // relative to TKEY block; need to call update after reading
    uint32 hash;   // name hash
};

// TKEY block
class CKeyArray {
public:
    CKeyEntry* m_data;
    uint32     m_size;

public:
    CKeyArray();
    ~CKeyArray();

    bool Load(uint32 length, FILESTREAM file, uint32* offset, uint8 unknown);
    void Unload();

    void /* inline */ Update(char* offset);
    char* Search(const char* key, bool& found);

private:
    CKeyEntry* BinarySearch(uint32 key, CKeyEntry* entries, int16 firstIndex, int16 lastIndex);

private:
    friend class CText; // InjectHooks()
};
