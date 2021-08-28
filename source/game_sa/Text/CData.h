#pragma once

// TDAT block
class CData {
public:
    char*  data;
    uint32 size;

public:
    CData();
    ~CData();

    void Unload();
    void Load(uint32 length, FILESTREAM file, uint32* offset, uint8_t nSkipBytes);
};
