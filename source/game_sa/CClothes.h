/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CPlayerPed.h"
#include "CPedClothesDesc.h"


class  CClothes
{
public:	
	//funcs
	static void ConstructPedModel(unsigned int modelid, CPedClothesDesc& newclothes, CPedClothesDesc const* oldclothes, bool bCutscenePlayer);
    static void RequestMotionGroupAnims();
    static void RebuildPlayerIfNeeded(CPlayerPed* player);
    static void RebuildPlayer(CPlayerPed* player, bool bIgnoreFatAndMuscle);
    static void RebuildCutscenePlayer(CPlayerPed* player, int modelid);
    static void LoadClothesFile();
    static void Init();
    static eClothesModelPart GetTextureDependency(int eClothesTexturePart);
    static int GetPlayerMotionGroupToLoad();
    static eClothesTexturePart GetDependentTexture(int eClothesModelPart);
    static int GetDefaultPlayerMotionGroup();
};
