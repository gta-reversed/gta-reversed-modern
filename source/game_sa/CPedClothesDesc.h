/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "eClothesModelPart.h"
#include "eClothesTexturePart.h"

class  CPedClothesDesc {
public:
    unsigned int m_anModelKeys[10];
    unsigned int m_anTextureKeys[18];
    float m_fFatStat;
    float m_fMuscleStat;

    void Initialise();
    void SetModel(unsigned int modelid, int eClothesModelPart);
    void SetModel(char const* model, int eClothesModelPart);
    bool GetIsWearingBalaclava();
    bool HasVisibleNewHairCut(int arg1);
    bool HasVisibleTattoo();
    CPedClothesDesc();
    void SetTextureAndModel(unsigned int texture, unsigned int model, int eClothesTexturePart);
    void SetTextureAndModel(char const* texturename, char const* modelname, int eClothesTexturePart);
};

VALIDATE_SIZE(CPedClothesDesc, 0x78);
