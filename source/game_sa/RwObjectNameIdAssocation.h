/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"


struct  RwObjectNameIdAssocation
{
	char *m_pName;
	unsigned int m_dwHierarchyId;
	unsigned int m_dwFlags;
};

VALIDATE_SIZE(RwObjectNameIdAssocation, 0xC);