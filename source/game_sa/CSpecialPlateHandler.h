/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

struct tCarGenPlateText {
    int m_nCarGenId; // -1 - empty
    char m_szPlateText[12];
};

VALIDATE_SIZE(tCarGenPlateText, 0x10);

class CSpecialPlateHandler {
public:
    static constexpr unsigned int PLATES_COUNT = 15;
    tCarGenPlateText m_plateTextEntries[PLATES_COUNT];
    unsigned int m_nCount;

public:
    static void InjectHooks();

    void Init();
    void Find(int carGenId, char* outText);
    void Add(int carGenId, const char* plateText);
    void Remove(int plateTextId);
};

VALIDATE_SIZE(CSpecialPlateHandler, 0xF4);
