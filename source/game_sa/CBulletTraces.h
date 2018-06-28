/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CBulletTrace.h"
#include "CEntity.h"

extern unsigned int MAX_NUM_BULLETTRACES; // default 16

class  CBulletTraces {
public:
	static CBulletTrace *aTraces; // static CBulletTrace aTraces[16]
	
	static void AddTrace(CVector *start, CVector *end, int weaponType, CEntity *entity);
	static void AddTrace(CVector *start, CVector *end, float radius, unsigned int time, unsigned char transparency);
	static void Render();
	static void Update();
	static void Init();
};
