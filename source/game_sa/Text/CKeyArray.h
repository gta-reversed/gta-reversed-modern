#pragma once

struct CKeyEntry {
    char* string; // relative to TKEY block; need to call update after reading
    uint  hash;   // name hash
};

// TKEY block
class CKeyArray {
public:
    CKeyEntry* data;
    uint32_t   size;

public:
    CKeyArray();
    ~CKeyArray();

    void Unload();
    void Load(uint length, FILESTREAM file, uint* offset, uchar nSkipBytes);

    void /* inline */ Update(char* offset);

    CKeyEntry* BinarySearch(uint key, CKeyEntry* entries, short firstIndex, short lastIndex);
    char* Search(const char* key, bool* found);
};
