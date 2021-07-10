#pragma once

// TDAT block
class CData {
public:
    char* data;
    uint  size;

public:
    CData();
    ~CData();

    void Unload();
    void Load(uint length, FILESTREAM file, uint* offset, uchar nSkipBytes);
};
