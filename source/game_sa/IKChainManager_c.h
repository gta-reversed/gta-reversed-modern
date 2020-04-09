#pragma once

#include "PluginBase.h"

class CPed;
class CEntity;
struct RwV3d;

class IKChainManager_c
{
public:
    bool IsLooking(CPed* pPed);
    CEntity* GetLookAtEntity(CPed* pPed);
    bool LookAt(char* strPurpose, CPed* pPed, CEntity* pTargetEntity, int time, int pedBoneID, RwV3d* pPosition, bool bArg7,
                float fSpeed, int blendTime, int a10, bool bForceLooking);
    int AbortLookAt(CPed* pPed, int blendOutTime);
};

extern IKChainManager_c* g_ikChainMan;