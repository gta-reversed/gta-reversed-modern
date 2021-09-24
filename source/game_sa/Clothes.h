/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPlayerPed.h"
#include "CPedClothesDesc.h"

class CClothes {
public:
    // funcs
    static void                ConstructPedModel(uint32 modelid, CPedClothesDesc& newclothes, CPedClothesDesc const* oldclothes, bool bCutscenePlayer);
    static void                RequestMotionGroupAnims();
    static void                RebuildPlayerIfNeeded(CPlayerPed* player);
    static void                RebuildPlayer(CPlayerPed* player, bool bIgnoreFatAndMuscle);
    static void                RebuildCutscenePlayer(CPlayerPed* player, int32 modelid);
    static void                LoadClothesFile();
    static void                Init();
    static eClothesModelPart   GetTextureDependency(int32 eClothesTexturePart);
    static int32               GetPlayerMotionGroupToLoad();
    static eClothesTexturePart GetDependentTexture(int32 eClothesModelPart);
    static int32               GetDefaultPlayerMotionGroup();
};
