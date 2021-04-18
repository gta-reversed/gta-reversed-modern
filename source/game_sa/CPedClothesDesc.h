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

class CPedClothesDesc {
public:
    unsigned int m_anModelKeys[10];
    unsigned int m_anTextureKeys[18];
    float m_fFatStat;
    float m_fMuscleStat;

    static void InjectHooks();

    CPedClothesDesc();
    CPedClothesDesc* Constructor();

    void Initialise();

    void SetModel(unsigned int modelId, eClothesModelPart modelPart);
    void SetModel(char const* model, eClothesModelPart modelPart);
    bool GetIsWearingBalaclava();
    bool HasVisibleNewHairCut(int arg1);
    bool HasVisibleTattoo();
    void SetTextureAndModel(unsigned int texture, unsigned int model, eClothesTexturePart texturePart);
    void SetTextureAndModel(char const* textureName, char const* modelName, eClothesTexturePart texturePart);
};

VALIDATE_SIZE(CPedClothesDesc, 0x78);
