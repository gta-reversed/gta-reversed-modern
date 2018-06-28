/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

struct tCarGenPlateText {
    int m_nCarGenId; // -1 - empty
    char m_szPlateText[12];
};

VALIDATE_SIZE(tCarGenPlateText, 0x10);

class CSpecialPlateHandler {
public:
    tCarGenPlateText m_plateTextEntries[15];
    unsigned int m_nCount;

    void Init();
    // Returns -1 if not found, or plate text id if found. outText contain plate text if found, "\0" otherwise.
    int Find(int carGenId, char* outText);
    void Add(int carGenId, char* plateText);
    void Remove(int plateTextId);
};

VALIDATE_SIZE(CSpecialPlateHandler, 0xF4);