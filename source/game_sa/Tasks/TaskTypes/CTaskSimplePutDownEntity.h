#pragma once
#include "CTaskSimpleHoldEntity.h"

class CTaskSimplePutDownEntity : public CTaskSimpleHoldEntity
{
public:
    float m_fPutDownHeightZ;
    
    static void InjectHooks();

    CTaskSimplePutDownEntity();
    CTaskSimplePutDownEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags, AnimationId animId, AssocGroupId groupId, bool bDisAllowDroppingOnAnimEnd, float fPutDownHeightZ);
    CTaskSimplePutDownEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags, char* pAnimName, char* pAnimBlockName, int animFlags, float fPutDownHeightZ);
    CTaskSimplePutDownEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags, CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags, float fPutDownHeightZ);
    ~CTaskSimplePutDownEntity();
private:
    CTaskSimplePutDownEntity* Constructor();
public:
    CTask* Clone() override;
    eTaskType GetId() override;

    CTask* Clone_Reversed();
    eTaskType GetId_Reversed() { return TASK_SIMPLE_PUTDOWN_ENTITY; };
};

VALIDATE_SIZE(CTaskSimplePutDownEntity, 0x40);