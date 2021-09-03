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

bool IKChainManager_c::LookAt(char* strPurpose, CPed* pPed, CEntity* pTargetEntity, int32 time, int32 pedBoneID, RwV3d* pPosition, bool bArg7,
    float fSpeed, int32 blendTime, int32 a10, bool bForceLooking)
{
    return plugin::CallMethodAndReturn<CEntity*, 0x618970, IKChainManager_c*, char*, CPed*, CEntity*, int32, int32, RwV3d*, bool, float, int32, int32, bool>
        (this, strPurpose, pPed, pTargetEntity, time, pedBoneID, pPosition, bArg7, fSpeed, blendTime, a10, bForceLooking);
}

int32 IKChainManager_c::AbortLookAt(CPed* pPed, int32 blendOutTime)
{
    return plugin::CallMethodAndReturn <int32, 0x618280, IKChainManager_c*, CPed*, int32>(this, pPed, blendOutTime);
}

bool IKChainManager_c::IsArmPointing(int32 nSlot, CPed* pPed)
{
    return plugin::CallMethodAndReturn<bool, 0x6182B0, IKChainManager_c*, int32, CPed*>(this, nSlot, pPed);
}
