/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eClothesModelPart.h"
#include "eClothesTexturePart.h"

class CPedClothesDesc {
public:
    uint32 m_anModelKeys[10];
    uint32 m_anTextureKeys[18];
    float  m_fFatStat;
    float  m_fMuscleStat;

public:
    static void InjectHooks();

    CPedClothesDesc();
    CPedClothesDesc* Constructor();

    void Initialise();

    void SetModel(uint32 modelId, eClothesModelPart modelPart);
    void SetModel(char const* model, eClothesModelPart modelPart);
    bool GetIsWearingBalaclava();
    bool HasVisibleNewHairCut(int32 arg1);
    bool HasVisibleTattoo();
    void SetTextureAndModel(uint32 texture, uint32 model, eClothesTexturePart texturePart);
    void SetTextureAndModel(char const* textureName, char const* modelName, eClothesTexturePart texturePart);
};

VALIDATE_SIZE(CPedClothesDesc, 0x78);
