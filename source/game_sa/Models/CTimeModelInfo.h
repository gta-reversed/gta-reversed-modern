/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CAtomicModelInfo.h"

class  CTimeModelInfo : public CAtomicModelInfo {
public:
	tTimeInfo m_timeInfo;

	void FindOtherTimeModel(char *modelName);
};

VALIDATE_SIZE(CTimeModelInfo, 0x24);