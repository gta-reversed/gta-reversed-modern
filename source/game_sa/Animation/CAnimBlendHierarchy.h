/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CAnimBlendSequence.h"

class CAnimBlendHierarchy {
public:
    unsigned int m_hashKey;
    CAnimBlendSequence *m_pSequences;
    unsigned short m_nSeqCount;
    bool m_bRunningCompressed;
    char field_B;
    int m_nAnimBlockId;
    float m_fTotalTime;
    int field_14;

	//funcs

	void* AllocSequenceBlock(bool arg1);
	CAnimBlendHierarchy();
	void CalcTotalTime();
	void CalcTotalTimeCompressed();
	void RemoveAnimSequences();
	void RemoveQuaternionFlips();
	void RemoveUncompressedData();
	void SetName(char const* string);
	void Shutdown();
	void Uncompress();

};

VALIDATE_SIZE(CAnimBlendHierarchy, 0x18);