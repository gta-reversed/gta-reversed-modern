/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CAnimBlendAssociation.h"
#include "RenderWare.h"
#include "CAnimBlock.h"

class CAnimBlendStaticAssociation;


class CAnimBlendAssocGroup
{
public:
    CAnimBlock *m_pAnimBlock;
    CAnimBlendStaticAssociation *m_pAssociations;
    unsigned int m_nNumAnimations;
    int m_nIdOffset;
    int m_nGroupID;

	CAnimBlendAssocGroup();
	CAnimBlendAssociation* CopyAnimation(char const* AnimName);
	CAnimBlendAssociation* CopyAnimation(unsigned int ID);
	void CreateAssociations(char const* szBlockName);
	void CreateAssociations(char const* AnimName, RpClump* pClump, char** arg3, int NumAnimations);
	void CreateAssociations(char const* AnimName, char const* arg2, char const* arg3, int arg4);
	void DestroyAssociations();
	CAnimBlendAssociation* GetAnimation(char const* AnimName);
	CAnimBlendAssociation* GetAnimation(unsigned int ID);
	unsigned int GetAnimationId(char const* AnimName);
	void InitEmptyAssociations(RpClump* pClump);
	~CAnimBlendAssocGroup();	
};

VALIDATE_SIZE(CAnimBlendAssocGroup, 0x14);
