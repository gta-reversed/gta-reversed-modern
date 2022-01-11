#pragma once

struct CKeyEntry {
    char*  string; // relative to TKEY block; need to call update after reading
    uint32 hash;   // name hash
};

// TKEY block
class CKeyArray {
public:
    CKeyEntry* data;
    uint32   size;

public:
    CKeyArray();
    ~CKeyArray();

    void Unload();
    void Load(uint32 length, FILESTREAM file, uint32* offset, uint8 nSkipBytes);

    void /* inline */ Update(char* offset);

    CKeyEntry* BinarySearch(uint32 key, CKeyEntry* entries, int16 firstIndex, int16 lastIndex);
    char* Search(const char* key, bool* found);
};
