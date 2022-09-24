/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimationEnums.h"
#include "eClothesModelPart.h"
#include "eClothesTexturePart.h"

class CPedClothesDesc;
class CPlayerPed;

enum eClothesFileRuleTags : uint8_t {
    RULE_TAG_CUTS,
    RULE_TAG_SETC,
    RULE_TAG_TEX,
    RULE_TAG_HIDE,
    RULE_TAG_END_IGNORE,
    RULE_TAG_IGNORE,
    RULE_TAG_END_EXCLUSIVE,
    RULE_TAG_EXCLUSIVE
};

class CClothes {
public:
    static int32& ms_clothesImageId;
    static uint32_t& ms_numRuleTags;
    static uint32_t (&ms_clothesRules)[600];

public:
    static void InjectHooks();

    static void Init();
    static void LoadClothesFile();

    static void ConstructPedModel(uint32 modelId, CPedClothesDesc& newClothes, const CPedClothesDesc* oldClothes, bool bCutscenePlayer);
    static void RequestMotionGroupAnims();
    static void RebuildPlayerIfNeeded(CPlayerPed* player);
    static void RebuildPlayer(CPlayerPed* player, bool bIgnoreFatAndMuscle);
    static void RebuildCutscenePlayer(CPlayerPed* player, int32 modelId);
    static eClothesModelPart GetTextureDependency(eClothesTexturePart eClothesTexturePart);
    static eClothesTexturePart GetDependentTexture(eClothesModelPart eClothesModelPart);
    static AssocGroupId GetPlayerMotionGroupToLoad();
    static AssocGroupId GetDefaultPlayerMotionGroup();

    // NOTSA
    static void AddRule(uint32_t rule);
};
