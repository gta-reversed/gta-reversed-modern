/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

struct tCarGenPlateText {
    int32 m_nCarGenId; // -1 - empty
    char m_szPlateText[12];
};

VALIDATE_SIZE(tCarGenPlateText, 0x10);

class CSpecialPlateHandler {
public:
    static constexpr uint32 PLATES_COUNT = 15;
    tCarGenPlateText m_plateTextEntries[PLATES_COUNT];
    uint32 m_nCount;

public:
    static void InjectHooks();

    void Init();
    void Find(int32 carGenId, char* outText);
    void Add(int32 carGenId, const char* plateText);
    void Remove(int32 plateTextId);
};

VALIDATE_SIZE(CSpecialPlateHandler, 0xF4);
