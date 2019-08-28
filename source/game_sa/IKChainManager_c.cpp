#include "StdInc.h"

IKChainManager_c* g_ikChainMan = reinterpret_cast<IKChainManager_c*>(0xC15448);

bool IKChainManager_c::IsLooking(CPed* pPed)
{
    return plugin::CallMethodAndReturn<bool, 0x6181A0, IKChainManager_c*, CPed*>(this, pPed);
}

CEntity* IKChainManager_c::GetLookAtEntity(CPed* pPed)
{
    return plugin::CallMethodAndReturn<CEntity*, 0x6181D0, IKChainManager_c*, CPed*>(this, pPed);
}

bool IKChainManager_c::LookAt(char* strPurpose, CPed* pPed, CPed* pTargetPed, int time, int pedBoneID, RwV3d* pPosition, bool bArg7,
    float fSpeed, int blendTime, int a10, bool bForceLooking)
{
    return plugin::CallMethodAndReturn<CEntity*, 0x618970, IKChainManager_c*, char*, CPed*, CPed*, int, int, RwV3d*, bool, float, int, int, bool>
        (this, strPurpose, pPed, pTargetPed, time, pedBoneID, pPosition, bArg7, fSpeed, blendTime, a10, bForceLooking);
}

int IKChainManager_c::AbortLookAt(CPed* pPed, int blendOutTime)
{
    return plugin::CallMethodAndReturn <int, 0x618280, IKChainManager_c*, CPed*, int>(this, pPed, blendOutTime);
}