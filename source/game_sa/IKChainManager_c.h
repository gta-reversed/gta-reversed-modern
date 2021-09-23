#pragma once

class CPed;
class CEntity;
struct RwV3d;

class IKChainManager_c {
public:
    bool     IsLooking(CPed* pPed);
    CEntity* GetLookAtEntity(CPed* pPed);
    bool     LookAt(char* strPurpose, CPed* pPed, CEntity* pTargetEntity, int32 time, int32 pedBoneID, RwV3d* pPosition, bool bArg7, float fSpeed, int32 blendTime, int32 a10, bool bForceLooking);
    int32    AbortLookAt(CPed* pPed, int32 blendOutTime);
    bool     IsArmPointing(int32 nSlot, CPed* pPed);
};

extern IKChainManager_c* g_ikChainMan;
